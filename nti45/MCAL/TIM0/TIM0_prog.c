#include "Std_Types.h"
#include "Bit_Math.h"

#include "TIM0_int.h"
#include "TIM0_private.h"
#include "TIM0_config.h"

static pf FunctionAddress1 = 0;
static pf FunctionAddress2 = 0;

void TIM0_voidInit(void)
{
#if (TIMER0_MODE == NORMAL_MODE)

	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);

#elif (TIMER0_MODE == CTC_MODE)

	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);

#endif

	TCCR0 &= 0xF8;
	TCCR0 |= TIMER0_PRESCALER;

	CLR_BIT(TIMSK,TOIE0);
	CLR_BIT(TIMSK,OCIE0);

	SET_BIT(TIFR,TOV0);
	SET_BIT(TIFR,OCF0);

	TCNT0 = 0;
	OCR0 = 0;
}

void TIM0_voidEnableOVInterrupt(void)
{
	SET_BIT(TIMSK,TOIE0);
}

void TIM0_voidDisableOVInterrupt(void)
{
	CLR_BIT(TIMSK,TOIE0);
}

void TIM0_voidSetOVReg(u8 Copy_u8OVRegValue)
{
	TCNT0 = Copy_u8OVRegValue;
}

u8 TIM0_u8ReadOVReg(void)
{
	return TCNT0;
}

void TIM0_voidEnableCTCInterrupt(void)
{
	SET_BIT(TIMSK,OCIE0);
}

void TIM0_voidDisableCTCInterrupt(void)
{
	CLR_BIT(TIMSK,OCIE0);
}

void TIM0_voidSetCTCReg(u8 Copy_u8CTCRegValue)
{
	OCR0 = Copy_u8CTCRegValue;
}

u8 TIM0_u8ReadCTCReg(void)
{
	return OCR0;
}

void TIM0_voidOVSetCallBack(pf OVFunctionAddress)
{
	FunctionAddress1 = OVFunctionAddress;
}

void TIM0_voidCTCSetCallBack(pf CTCFunctionAddress)
{
	FunctionAddress2 = CTCFunctionAddress;
}

void __vector_11(void) __attribute__((signal,used));
void __vector_11(void)
{
	if(FunctionAddress1 != 0)
	{
		FunctionAddress1();
	}
}

void __vector_10(void) __attribute__((signal,used));
void __vector_10(void)
{
	if(FunctionAddress2 != 0)
	{
		FunctionAddress2();
	}
}
