#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

void ADC_voidInit(void)
{
    ADMUX  = (ADC_VOLTAGE_REF << 6);
    ADCSRA = (1 << ADEN) | ADC_PRESCALER;
}

u16 ADC_u16Read(u8 Copy_u8Channel)
{
    ADMUX = (ADMUX & 0xE0) | (Copy_u8Channel & 0x1F);
    SET_BIT(ADCSRA, ADSC);
    while(GET_BIT(ADCSRA, ADSC));
    return ADC;
}
