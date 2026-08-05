#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include <stdint.h>

#define ADC_CHANNEL0        0u
#define ADC_CHANNEL1        1u
#define ADC_CHANNEL2        2u
#define ADC_CHANNEL3        3u
#define ADC_CHANNEL4        4u
#define ADC_CHANNEL5        5u
#define ADC_CHANNEL6        6u
#define ADC_CHANNEL7        7u

void ADC_voidInit(void);

uint16_t ADC_u16Read(uint8_t Copy_u8Channel);

float ADC_f32GetLM35Temperature(void);

uint8_t ADC_u8IsHumanPresent(void);

#endif
