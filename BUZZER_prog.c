
/****/
/*       Author: Mariam Shaban      */
/*        Date  : 5/08/2026        */
/*        File: Program File        */
/****/

#include "std__types.h"
#include "bit_math.h"
#include <util/delay.h>


#include "DIO_int.h"
#include "PWM_int.h"


#include "BUZZER_config.h"
#include "BUZZER_int.h"

void BUZZER_voidInit(void)
{
    /* Set Buzzer Pin (PB3 / OC0) as Output */
    DIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, OUTPUT);
}

void BUZZER_voidSetTone(u8 u8DutyCycle)
{
    /* Start Fast PWM on Timer0 with given Duty Cycle */
    TIM0_voidStartFastPWM(u8DutyCycle);
}

void BUZZER_voidStop(void)
{
    /* Stop PWM Output by setting Duty Cycle to 0% */
    TIM0_voidStartFastPWM(0);
}

void BUZZER_voidStartGradualAlarm(void)
{
    u8 local_u8DutyCycle = 0;

    /* Gradual Increase in Duty Cycle (Tone Ramp Up) */
    for (local_u8DutyCycle = 10; local_u8DutyCycle <= 90; local_u8DutyCycle += 5)
    {
        TIM0_voidStartFastPWM(local_u8DutyCycle);
        _delay_ms(30);
    }

    /* Gradual Decrease in Duty Cycle (Tone Ramp Down) */
    for (local_u8DutyCycle = 90; local_u8DutyCycle >= 10; local_u8DutyCycle -= 5)
    {
        TIM0_voidStartFastPWM(local_u8DutyCycle);
        _delay_ms(30);
    }
}
