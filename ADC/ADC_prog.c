#include "Std_Types.h"
#include "Bit_Math.h"

#include "ADC_int.h"
#include "ADC_private.h"
#include "ADC_config.h"

pf ADC_CallBack = 0;

void ADC_voidInit(void)
{
	CLR_BIT(ADCSRA, ADEN);

	CLR_BIT(ADCSRA, ADSC);

	CLR_BIT(ADCSRA, ADATE);

	SET_BIT(ADCSRA, ADIF);

	CLR_BIT(ADCSRA, ADIE);

#if REG_ADJ == LEFT_ADJUSTMEN
	SET_BIT(ADMUX, ADLAR);
#elif REG_ADJ == RIGHT_ADJUSTMEN
	CLR_BIT(ADMUX, ADLAR);
#endif

	ADMUX &= 0xE0;
	ADMUX |= ADC_CHANNEL;

	SET_BIT(ADCSRA, ADPS2);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS0);
}

void ADC_voidADCEnable(void)
{
	SET_BIT(ADCSRA, ADEN);
}

void ADC_voidADCDisable(void)
{
	CLR_BIT(ADCSRA, ADEN);
}

u16 ADC_u16Read(void)
{
#if REG_ADJ == LEFT_ADJUSTMEN

	return ADCH;

#elif REG_ADJ == RIGHT_ADJUSTMEN

	return ADC;

#endif
}

void ADC_voidStartConverstion(void)
{
	SET_BIT(ADCSRA, ADSC);

	while(GET_BIT(ADCSRA, ADIF) == 0);

	SET_BIT(ADCSRA, ADIF);
}

void ADC_voidAutoTrigger(void)
{
	SET_BIT(ADCSRA, ADATE);

	SFIOR &= 0x1F;
	SFIOR |= (TRIGGER_SELECT << 5);
}

void ADC_voidInterruptEnable(void)
{
	SET_BIT(ADCSRA, ADIE);
}

void ADC_voidSetCallBack(pf FunctionAddress)
{
	ADC_CallBack = FunctionAddress;
}

void __vector_20(void) __attribute__((signal, used));

void __vector_20(void)
{
	if(ADC_CallBack != 0)
	{
		ADC_CallBack();
	}
}
