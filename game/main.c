#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "ADC_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"

#define BUZZER_PORT     DIO_PORTD
#define BUZZER_PIN      7

#define MAX_LEVEL       20

static u8 GenerateRandomNumber(void);
static void DisplaySequence(u8 *Copy_pu8Seq, u8 Copy_u8Level);
static u8 GetPlayerInput(u8 *Copy_pu8Seq, u8 Copy_u8Level);
static void GameOver(u8 Copy_u8Level);

int main(void)
{
    u8 Local_u8Level = 1;
    u8 Local_au8Sequence[MAX_LEVEL];
    u8 Local_u8Result;

    /* ---- Initialization ---- */
    DIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, DIO_OUTPUT);
    DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_LOW);

    TIMER_voidInit();
    ADC_voidInit();
    LCD_voidInit();
    KEYPAD_voidInit();

    LCD_voidSendString((u8*)"Simon Game");
    LCD_voidGoToXY(1, 0);
    LCD_voidSendString((u8*)"Press any key");
    KEYPAD_u8WaitForKey();
    LCD_voidClear();

    while(1)
    {
        /* Step 2: generate a new random number and append it to the sequence */
        Local_au8Sequence[Local_u8Level - 1] = GenerateRandomNumber();

        /* Step 3: display the whole sequence so far */
        DisplaySequence(Local_au8Sequence, Local_u8Level);

        /* Step 4: read player input and compare */
        Local_u8Result = GetPlayerInput(Local_au8Sequence, Local_u8Level);

        if(Local_u8Result == 1)
        {
            if(Local_u8Level < MAX_LEVEL)
            {
                Local_u8Level++;
            }
            LCD_voidClear();
            LCD_voidSendString((u8*)"Correct!");
            TIMER_voidDelayMs(500);
            LCD_voidClear();
        }
        else
        {
            /* Step 5: game over */
            GameOver(Local_u8Level);
            Local_u8Level = 1;
        }
    }

    return 0;
}

/* Uses the free-running Timer0 counter as an entropy source, since AVR
   has no hardware random number generator. */
static u8 GenerateRandomNumber(void)
{
    static u16 Local_u16Seed = 0;
    Local_u16Seed += (u16)TIMER_u8GetCounterValue() + 17;
    return (u8)((Local_u16Seed % 9) + 1); /* number from 1 to 9 */
}

/* Displays the sequence digit by digit. The delay between digits is
   controlled live by the potentiometer connected to ADC channel 0. */
static void DisplaySequence(u8 *Copy_pu8Seq, u8 Copy_u8Level)
{
    u8  Local_u8Idx;
    u16 Local_u16AdcValue;
    u16 Local_u16Delay;

    Local_u16AdcValue = ADC_u16Read(0);
    Local_u16Delay = 200 + (Local_u16AdcValue / 2); /* ~200ms .. ~711ms */

    LCD_voidClear();
    LCD_voidSendString((u8*)"Watch:");

    for(Local_u8Idx = 0; Local_u8Idx < Copy_u8Level; Local_u8Idx++)
    {
        LCD_voidGoToXY(1, 0);
        LCD_voidSendNumber(Copy_pu8Seq[Local_u8Idx]);
        TIMER_voidDelayMs(Local_u16Delay);

        LCD_voidGoToXY(1, 0);
        LCD_voidSendString((u8*)"  "); /* blink off before next digit */
        TIMER_voidDelayMs(200);
    }
    LCD_voidClear();
}

/* Waits for Copy_u8Level digit key presses and compares them, in order,
   against the stored sequence. Returns 1 on full match, 0 on first mismatch. */
static u8 GetPlayerInput(u8 *Copy_pu8Seq, u8 Copy_u8Level)
{
    u8 Local_u8Idx;
    u8 Local_u8Key;

    LCD_voidSendString((u8*)"Your turn:");
    LCD_voidGoToXY(1, 0);

    for(Local_u8Idx = 0; Local_u8Idx < Copy_u8Level; Local_u8Idx++)
    {
        do
        {
            Local_u8Key = KEYPAD_u8WaitForKey();
        } while(Local_u8Key < '0' || Local_u8Key > '9'); /* digits only */

        LCD_voidSendChar(Local_u8Key);

        if((u8)(Local_u8Key - '0') != Copy_pu8Seq[Local_u8Idx])
        {
            return 0; /* wrong digit */
        }
    }
    return 1; /* full sequence correct */
}

static void GameOver(u8 Copy_u8Level)
{
    LCD_voidClear();
    LCD_voidSendString((u8*)"Game Over!");
    LCD_voidGoToXY(1, 0);
    LCD_voidSendString((u8*)"Score:");
    LCD_voidSendNumber(Copy_u8Level - 1);

    DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_HIGH);
    TIMER_voidDelayMs(1000);
    DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_LOW);

    LCD_voidGoToXY(1, 10);
    LCD_voidSendString((u8*)"Key?");
    KEYPAD_u8WaitForKey();
    LCD_voidClear();
}
