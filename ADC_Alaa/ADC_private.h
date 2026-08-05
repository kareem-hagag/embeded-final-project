#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#include <avr/io.h> 

#define ADC_VREF_AREF               0x00u
#define ADC_VREF_AVCC               0x01u
#define ADC_VREF_INTERNAL_2_56      0x03u

#define ADC_PRESCALER_2             0x01u
#define ADC_PRESCALER_4             0x02u
#define ADC_PRESCALER_8             0x03u
#define ADC_PRESCALER_16            0x04u
#define ADC_PRESCALER_32            0x05u
#define ADC_PRESCALER_64            0x06u
#define ADC_PRESCALER_128           0x07u

#define ADC_MAX_CHANNEL             7u

#define ADC_CHANNEL_MASK            0xE0u

#define ADC_VREF_MILLIVOLT          5000.0f   
#define ADC_RESOLUTION              1024.0f
#define LM35_MV_PER_DEGREE          10.0f   

#endif 
