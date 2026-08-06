#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/* Voltage reference (REFS1:REFS0): 0=AREF pin, 1=AVCC, 3=Internal 2.56V */
#define ADC_VOLTAGE_REF     1

/* Prescaler bits (ADPS2:ADPS0): 7 = /128 (good for 8MHz -> 62.5KHz ADC clock) */
#define ADC_PRESCALER       7

#endif /* ADC_CONFIG_H */
