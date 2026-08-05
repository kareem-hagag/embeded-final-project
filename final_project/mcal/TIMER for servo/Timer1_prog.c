/***      Auther : kareem hagag    ***/
/***      title : final project             ***/
/***      file : timer 1 program   ***/
//#include <stddef.h>
#include "../../std_lib/Std_Types.h"
#include "../../std_lib/Bit_Math.h"
#include "../DIO/Dio_Int.h"
#include "Timer1_Config.h"
#include "Timer1_Private.h"
#include "Timer1_Int.h"

void TIMER1_voidServoInit(void)
{
    DIO_voidSetPinDirection(DIO_PORTC, PIN1, OUTPUT);

    SET_BIT(TCCR1A, TIMER1_WGM11);
    CLR_BIT(TCCR1A, TIMER1_WGM10);
    SET_BIT(TCCR1B, TIMER1_WGM13);
    SET_BIT(TCCR1B, TIMER1_WGM12);

    SET_BIT(TCCR1A, TIMER1_COM1A1);
    CLR_BIT(TCCR1A, TIMER1_COM1A0);

    ICR1 = TIMER1_TOP_VALUE;

    TCCR1B |= TIMER1_PRESCALER_BITS;

    TIMER1_voidServoSetAngle(90);
}

void TIMER1_voidServoSetAngle(u8 u8Angle)
{
    u16 u16PulseTicks;

    if (u8Angle > 180)
    {
        u8Angle = 180;
    }

    u16PulseTicks = 2000 + (((u32)u8Angle * 2000) / 180);

    OCR1A = u16PulseTicks;
}
