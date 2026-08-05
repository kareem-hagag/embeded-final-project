/*
 ============================================================================
 File Name   : main.c
 Module      : APP - Smart Safe / Smart Vault
 Description : Final integration code that orchestrates all HAL drivers
               (KEYPAD, LCD, ADC/LM35, TIM0, TIMER1-Servo, BUZZER, LED)
               into a single non-blocking state machine.

 State Machine:
   IDLE              -> waits for ADC_u8IsHumanPresent() before doing anything
   ENTER_PASSWORD     -> reads keypad digits, '*' = clear, '#' = confirm
   WRONG_PASSWORD_MSG  -> shows "Wrong Password" + tries left for a short time
   UNLOCKED            -> servo open, auto re-locks after UNLOCK_DURATION_SEC
   LOCKED_OUT          -> after 3 wrong tries: LCD "Locked!", buzzer gradual
                          alarm, auto-clears after LOCKOUT_DURATION_SEC

 Non-blocking timing is implemented with a software "tick" counter that is
 incremented inside TIM0's overflow interrupt callback (TIM0_voidOVSetCallBack).
 No _delay_ms() is used anywhere in the state machine.
 ============================================================================
 !!! PLEASE READ - THINGS YOU MUST VERIFY / ADJUST BEFORE BUILDING !!!
 ============================================================================
 1) Include paths below are placeholders (LED_interface.h, LCD_interface.h,
    ...). Rename them to match your actual driver file names/paths.

 2) KEYPAD_NO_KEY: I assumed KEYPAD_u8GetPressedKey() returns 0xFF when no
    key is pressed. If your driver uses a different "no key" value (or if
    it BLOCKS until a key is pressed), update KEYPAD_NO_KEY accordingly /
    confirm the blocking behavior is acceptable in ENTER_PASSWORD state.

 3) TICKS_PER_SECOND: this depends entirely on how TIM0_voidinit() configures
    the prescaler + F_CPU in your MCAL config. Formula (8-bit timer, Normal
    mode overflow at 256): ticks/sec = F_CPU / (Prescaler * 256).
    The placeholder value below (1000) is almost certainly wrong for your
    setup -> compute the real value and update it, otherwise UNLOCK_DURATION
    and LOCKOUT_DURATION will not equal real seconds.

 4) IMPORTANT INTEGRATION RISK: BUZZER_voidStartGradualAlarm() most likely
    reprograms TIM0 (mode / OCR / prescaler) internally to generate the tone
    sweep, while we are ALSO using TIM0's overflow interrupt as our system
    tick. While OVF and Compare-Match are separate interrupt vectors (so the
    callbacks themselves won't clash), changing TIM0's mode or prescaler
    WILL change how fast the overflow interrupt fires, which will make the
    LOCKOUT_DURATION_SEC timing inaccurate for as long as the buzzer plays.
    -> Test the actual lockout duration on hardware and re-tune
       LOCKOUT_DURATION_SEC, or coordinate with whoever wrote BUZZER.c to
       confirm it does not touch TIM0's prescaler/mode.

 5) Correct password (g_au8CorrectPassword) is a placeholder "1234" -> change it.

 6) Servo locked/open angles are placeholders -> adjust to your lock mechanism.
 ============================================================================
*/

#include <avr/interrupt.h>
#include <string.h>

#include "../../STD/Std_Types.h"
#include "../../STD/Bit_Math.h"


#include "Dio_Int.h"         /* lowest MCAL layer, used internally by the drivers below */
#include "../HAL/4_LED/LED_int.h"
#include "../HAL/3_LCD/LCD_int.h"
#include "../HAL/2_KEYPAD/KEYPAD_int.h"
#include "../2_ADC/ADC_int.h"
#include "../1_PWM/PWM_int.h"      /* TIM0_voidinit / OV interrupt / callback */
#include "../3_TIMER1/TIMER1_int.h"      /* Servo */
#include "../HAL/1_BUZZER/BUZZER_int.h"

/* ===================== CONFIGURATION - ADJUST THESE ===================== */
#define PASSWORD_LENGTH         4u
#define MAX_WRONG_ATTEMPTS      3u

#define TICKS_PER_SECOND        1000u   /* TODO: verify vs your TIM0 config */

#define UNLOCK_DURATION_SEC     5u      /* how long the safe stays open      */
#define LOCKOUT_DURATION_SEC    15u     /* how long the safe stays locked out */
#define WRONG_MSG_DURATION_SEC  2u      /* how long "Wrong Password" is shown */
#define TEMP_UPDATE_PERIOD_SEC  1u      /* LM35 readout refresh on idle screen */

#define SERVO_LOCKED_ANGLE      0u
#define SERVO_UNLOCKED_ANGLE    90u

#define KEYPAD_NO_KEY           0xFFu   /* TODO: verify with KEYPAD driver   */
#define KEYPAD_CLEAR_KEY        '*'
#define KEYPAD_ENTER_KEY        '#'

#define ENABLE_TEMP_DISPLAY     1       /* optional bonus feature, set 0 to disable */
/* =========================================================================*/

typedef enum
{
    SAFE_STATE_IDLE = 0,
    SAFE_STATE_ENTER_PASSWORD,
    SAFE_STATE_WRONG_PASSWORD_MSG,
    SAFE_STATE_UNLOCKED,
    SAFE_STATE_LOCKED_OUT
} SafeState_t;

/* ============================ Global State =============================*/
static volatile u32 g_u32SystemTicks = 0;

static SafeState_t  g_enuSafeState        = SAFE_STATE_IDLE;
static u32           g_u32StateStartTick   = 0;

static u8 g_au8PasswordBuffer[PASSWORD_LENGTH];
static u8 g_u8PasswordIndex   = 0;
static u8 g_u8WrongAttempts   = 0;

static const u8 g_au8CorrectPassword[PASSWORD_LENGTH] = {'1','2','3','4'}; /* TODO: change */

static u8  g_u8IdleScreenDrawn   = 0;
static u32 g_u32LastTempUpdateTick = 0;

/* ======================= Static Function Prototypes =====================*/
static void APP_voidInit(void);
static void APP_voidSystemTickCallback(void);
static u32  APP_u32GetTicks(void);
static u8   APP_u8IsTimeElapsed(u32 Copy_u32StartTick, u32 Copy_u32DurationTicks);

static void APP_voidHandleIdleState(void);
static void APP_voidHandleEnterPasswordState(void);
static void APP_voidHandleWrongPasswordMsgState(void);
static void APP_voidHandleUnlockedState(void);
static void APP_voidHandleLockedOutState(void);

static void APP_voidOnCorrectPassword(void);
static void APP_voidOnWrongPassword(void);
static void APP_voidResetPasswordBuffer(void);

/* ================================ main ===================================*/
int main(void)
{
    APP_voidInit();

    while (1)
    {
        switch (g_enuSafeState)
        {
            case SAFE_STATE_IDLE:
                APP_voidHandleIdleState();
                break;

            case SAFE_STATE_ENTER_PASSWORD:
                APP_voidHandleEnterPasswordState();
                break;

            case SAFE_STATE_WRONG_PASSWORD_MSG:
                APP_voidHandleWrongPasswordMsgState();
                break;

            case SAFE_STATE_UNLOCKED:
                APP_voidHandleUnlockedState();
                break;

            case SAFE_STATE_LOCKED_OUT:
                APP_voidHandleLockedOutState();
                break;

            default:
                g_enuSafeState = SAFE_STATE_IDLE;
                break;
        }
    }

    return 0;
}

/* ============================ Init / Tick ================================*/
static void APP_voidInit(void)
{
    /* DIO must be initialized first: every other driver below (LED, LCD,
       KEYPAD, BUZZER, TIM0, TIMER1) configures its own pins on top of DIO */
    DIO_voidInitialization();

    /* LEDs */
    LED_voidInit(LED_GREEN);
    LED_voidInit(LED_YELLOW);
    LED_voidInit(LED_RED);

    /* LCD */
    LCD_voidLCDInit();

    /* Keypad */
    KEYPAD_voidInit();

    /* ADC (LM35 + presence check) */
    ADC_voidInit();

    /* TIM0 -> used here purely as a system tick source via overflow ISR */
    TIM0_voidinit();
    TIM0_voidOVSetCallBack(APP_voidSystemTickCallback);
    TIM0_voidEnableOVInterrupt();

    /* Servo (lock mechanism) */
    TIMER1_voidServoInit();
    TIMER1_voidServoSetAngle(SERVO_LOCKED_ANGLE);

    /* Buzzer */
    BUZZER_voidInit();

    /* Global interrupt enable */
    sei();

    g_enuSafeState = SAFE_STATE_IDLE;
}

static void APP_voidSystemTickCallback(void)
{
    g_u32SystemTicks++;
}

static u32 APP_u32GetTicks(void)
{
    u32 Local_u32Ticks;

    /* atomic read: g_u32SystemTicks is 4 bytes and modified inside an ISR */
    cli();
    Local_u32Ticks = g_u32SystemTicks;
    sei();

    return Local_u32Ticks;
}

static u8 APP_u8IsTimeElapsed(u32 Copy_u32StartTick, u32 Copy_u32DurationTicks)
{
    u8 Local_u8Result = 0;

    if ((APP_u32GetTicks() - Copy_u32StartTick) >= Copy_u32DurationTicks)
    {
        Local_u8Result = 1;
    }

    return Local_u8Result;
}

static void APP_voidResetPasswordBuffer(void)
{
    g_u8PasswordIndex = 0;
    memset(g_au8PasswordBuffer, 0, sizeof(g_au8PasswordBuffer));
}

/* ============================ State Handlers ==============================*/
static void APP_voidHandleIdleState(void)
{
    if (g_u8IdleScreenDrawn == 0)
    {
        LCD_voidSendCommand(0x01); /* clear display */
        LCD_GotoXY(0, 0);
        LCD_voidWriteString((u8*)"  Smart Safe");
        g_u8IdleScreenDrawn = 1;
        g_u32LastTempUpdateTick = 0;
    }

#if ENABLE_TEMP_DISPLAY
    if (APP_u8IsTimeElapsed(g_u32LastTempUpdateTick, TEMP_UPDATE_PERIOD_SEC * TICKS_PER_SECOND))
    {
        float Local_f32Temp = ADC_f32GetLM35Temperature();

        LCD_GotoXY(0, 1);
        LCD_voidWriteString((u8*)"Temp:");
        LCD_voidWriteNumber((u8)Local_f32Temp);
        LCD_voidWriteString((u8*)" C   ");

        g_u32LastTempUpdateTick = APP_u32GetTicks();
    }
#endif

    if (ADC_u8IsHumanPresent())
    {
        APP_voidResetPasswordBuffer();

        LCD_voidSendCommand(0x01);
        LCD_GotoXY(0, 0);
        LCD_voidWriteString((u8*)"Enter Pass:");
        LCD_GotoXY(0, 1);

        LED_voidTurnOn(LED_YELLOW);
        LED_voidTurnOff(LED_GREEN);
        LED_voidTurnOff(LED_RED);

        g_u8IdleScreenDrawn = 0;
        g_enuSafeState = SAFE_STATE_ENTER_PASSWORD;
    }
}

static void APP_voidHandleEnterPasswordState(void)
{
    u8 Local_u8Key = KEYPAD_u8GetPressedKey();

    if (Local_u8Key == KEYPAD_NO_KEY)
    {
        return; /* nothing pressed, stay non-blocking */
    }

    if (Local_u8Key == KEYPAD_ENTER_KEY)
    {
        if (g_u8PasswordIndex == PASSWORD_LENGTH)
        {
            if (memcmp(g_au8PasswordBuffer, g_au8CorrectPassword, PASSWORD_LENGTH) == 0)
            {
                APP_voidOnCorrectPassword();
            }
            else
            {
                APP_voidOnWrongPassword();
            }
        }
        /* else: not enough digits yet, ignore '#' */
    }
    else if (Local_u8Key == KEYPAD_CLEAR_KEY)
    {
        APP_voidResetPasswordBuffer();
        LCD_GotoXY(0, 1);
        LCD_voidWriteString((u8*)"                "); /* clear line */
        LCD_GotoXY(0, 1);
    }
    else if ((Local_u8Key >= '0') && (Local_u8Key <= '9'))
    {
        if (g_u8PasswordIndex < PASSWORD_LENGTH)
        {
            g_au8PasswordBuffer[g_u8PasswordIndex] = Local_u8Key;
            g_u8PasswordIndex++;
            LCD_voidSendData('*'); /* mask the digit on screen */
        }
    }
    /* any other key (A/B/C/D...) is ignored */
}

static void APP_voidHandleWrongPasswordMsgState(void)
{
    if (APP_u8IsTimeElapsed(g_u32StateStartTick, WRONG_MSG_DURATION_SEC * TICKS_PER_SECOND))
    {
        LCD_voidSendCommand(0x01);
        LCD_GotoXY(0, 0);
        LCD_voidWriteString((u8*)"Enter Pass:");
        LCD_GotoXY(0, 1);

        g_enuSafeState = SAFE_STATE_ENTER_PASSWORD;
    }
}

static void APP_voidHandleUnlockedState(void)
{
    if (APP_u8IsTimeElapsed(g_u32StateStartTick, UNLOCK_DURATION_SEC * TICKS_PER_SECOND))
    {
        TIMER1_voidServoSetAngle(SERVO_LOCKED_ANGLE);
        LED_voidTurnOff(LED_GREEN);

        g_u8IdleScreenDrawn = 0;
        g_enuSafeState = SAFE_STATE_IDLE;
    }
}

static void APP_voidHandleLockedOutState(void)
{
    if (APP_u8IsTimeElapsed(g_u32StateStartTick, LOCKOUT_DURATION_SEC * TICKS_PER_SECOND))
    {
        BUZZER_voidStop();
        LED_voidTurnOff(LED_RED);

        g_u8WrongAttempts = 0;
        g_u8IdleScreenDrawn = 0;
        g_enuSafeState = SAFE_STATE_IDLE;
    }
}

/* ============================ Transitions =================================*/
static void APP_voidOnCorrectPassword(void)
{
    g_u8WrongAttempts = 0;

    LCD_voidSendCommand(0x01);
    LCD_GotoXY(0, 0);
    LCD_voidWriteString((u8*)"Access Granted");

    LED_voidTurnOff(LED_YELLOW);
    LED_voidTurnOff(LED_RED);
    LED_voidTurnOn(LED_GREEN);

    TIMER1_voidServoSetAngle(SERVO_UNLOCKED_ANGLE);

    g_u32StateStartTick = APP_u32GetTicks();
    g_enuSafeState = SAFE_STATE_UNLOCKED;
}

static void APP_voidOnWrongPassword(void)
{
    g_u8WrongAttempts++;

    if (g_u8WrongAttempts >= MAX_WRONG_ATTEMPTS)
    {
        LCD_voidSendCommand(0x01);
        LCD_GotoXY(0, 0);
        LCD_voidWriteString((u8*)"Locked!");

        LED_voidTurnOff(LED_YELLOW);
        LED_voidTurnOff(LED_GREEN);
        LED_voidTurnOn(LED_RED);

        BUZZER_voidStartGradualAlarm();

        g_u32StateStartTick = APP_u32GetTicks();
        g_enuSafeState = SAFE_STATE_LOCKED_OUT;
    }
    else
    {
        LCD_voidSendCommand(0x01);
        LCD_GotoXY(0, 0);
        LCD_voidWriteString((u8*)"Wrong Password");
        LCD_GotoXY(0, 1);
        LCD_voidWriteNumber((u8)(MAX_WRONG_ATTEMPTS - g_u8WrongAttempts));
        LCD_voidWriteString((u8*)" tries left");

        APP_voidResetPasswordBuffer();

        g_u32StateStartTick = APP_u32GetTicks();
        g_enuSafeState = SAFE_STATE_WRONG_PASSWORD_MSG;
    }
}
