

/********/
/*       Author: Mariam Shaban      */
/*        Date  : 4/08/2026        */
/*        File: Program File        */
/********/


#include "../../STD/Std_Types.h"
#include "../../STD/Bit_Math.h"
#include "Dio_Int.h"

#include "PWM_private.h"
#include "PWM_config.h"
#include "PWM_int.h"

pf FunctionAddress1 = 0;
pf FunctionAddress2 = 0;

void TIM0_voidinit(void)
{
    // Select Prescaler (Prescaler 8)
    SET_BIT(TCCR0, CS01);
    CLR_BIT(TCCR0, CS00);
    CLR_BIT(TCCR0, CS02);

    CLR_BIT(TCCR0, WGM00);
    CLR_BIT(TCCR0, WGM01);

    CLR_BIT(TCCR0, COM00);
    CLR_BIT(TCCR0, COM01);

    CLR_BIT(TIMSK, TOIE0);

    CLR_BIT(TIMSK, OCIE0);

    SET_BIT(TIFR, TOV0);

    SET_BIT(TIFR, OCF0);

    TCNT0 = 0x00;

    OCR0 = 0x00;
}

/****************/
// Normal Mode
void TIM0_voidEnableOVInterrupt(void)
{
    SET_BIT(TIMSK, TOIE0);
}

void TIM0_voidDisableOVInterrupt(void)
{
    CLR_BIT(TIMSK, TOIE0);
}

void TIM0_voidSetOVReg(u8 u8OVRegValue)
{
    TCNT0 = u8OVRegValue;
}

u8 TIM0_u8ReadOVReg(void)
{
    return TCNT0;
}

void TIM0_voidOVSetCallBack(pf OVFunctionAddress)
{
    FunctionAddress1 = OVFunctionAddress;
}

// For Overflow ISR
void __vector_11(void) __attribute__((signal, used));
void __vector_11(void)
{
    if (FunctionAddress1 != 0)
    {
        FunctionAddress1();
    }
}

/****************/
// CTC Mode
void TIM0_voidEnableCTCInterrupt(void)
{
    SET_BIT(TIMSK, OCIE0);
}

void TIM0_voidDisableCTCInterrupt(void)
{
    CLR_BIT(TIMSK, OCIE0);
}

void TIM0_voidSetCTCReg(u8 u8CTCRegValue)
{
    OCR0 = u8CTCRegValue;
}

u8 TIM0_u8ReadCTCCTCReg(void)
{
    return OCR0;
}

void TIM0_voidCTCSetCallBack(pf CTCFunctionAddress)
{
    FunctionAddress2 = CTCFunctionAddress;
}

// For On Compare Match ISR
void __vector_10(void) __attribute__((signal, used));
void __vector_10(void)
{
    if (FunctionAddress2 != 0)
    {
        FunctionAddress2();
    }
}
/****************/
// FAST PWM Mode
void TIM0_voidStartFastPWM(u8 u8DutyCycle)
{
    SET_BIT(TCCR0, WGM00);
    SET_BIT(TCCR0, WGM01);

    SET_BIT(TCCR0, COM01);
    CLR_BIT(TCCR0, COM00);

    SET_BIT(TCCR0, CS00);
    SET_BIT(TCCR0, CS01);
    CLR_BIT(TCCR0, CS02);

    OCR0 = (u8)(((u16)u8DutyCycle * 255) / 100);
}
/****************/
// PHASE CORRECT Mode
void TIM0_voidStartPhaseCorrectPWM(u8 u8DutyCycle)
{
    SET_BIT(TCCR0, WGM00);
    CLR_BIT(TCCR0, WGM01);

    SET_BIT(TCCR0, COM01);
    CLR_BIT(TCCR0, COM00);

    SET_BIT(TCCR0, CS00);
    SET_BIT(TCCR0, CS01);
    CLR_BIT(TCCR0, CS02);

    OCR0 = (u8)(((u16)u8DutyCycle * 255) / 100);
}




















