#include <stdint.h>
#include "ADC_int.h"
#include "ADC_config.h"
#include "ADC_private.h"

void ADC_voidInit(void)
{
    ADMUX = (uint8_t)(ADC_VREF << 6);
    ADCSRA = (1 << ADEN) | ADC_PRESCALER;
}

uint16_t ADC_u16Read(uint8_t Copy_u8Channel)
{
    if (Copy_u8Channel > ADC_MAX_CHANNEL)
    {
        return 0u;
    }
    ADMUX = (ADMUX & ADC_CHANNEL_MASK) | Copy_u8Channel;

    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
    {
        /* busy wait */
    }

    return ADCW;
}

float ADC_f32GetLM35Temperature(void)
{
    uint32_t Local_u32Sum = 0;
    uint8_t  Local_u8Index;
    float    Local_f32AvgRaw;
    float    Local_f32VoltageMv;
    float    Local_f32TemperatureC;

    for (Local_u8Index = 0; Local_u8Index < LM35_SAMPLE_COUNT; Local_u8Index++)
    {
        Local_u32Sum += ADC_u16Read(LM35_ADC_CHANNEL);
    }

    Local_f32AvgRaw = (float)Local_u32Sum / (float)LM35_SAMPLE_COUNT;

    Local_f32VoltageMv = Local_f32AvgRaw * (ADC_VREF_MILLIVOLT / ADC_RESOLUTION);

    Local_f32TemperatureC = Local_f32VoltageMv / LM35_MV_PER_DEGREE;

    return Local_f32TemperatureC;
}

uint8_t ADC_u8IsHumanPresent(void)
{
    float Local_f32Temp = ADC_f32GetLM35Temperature();

    if (Local_f32Temp >= LM35_HUMAN_TEMP_THRESHOLD)
    {
        return 1u;
    }
    else
    {
        return 0u;
    }
}
