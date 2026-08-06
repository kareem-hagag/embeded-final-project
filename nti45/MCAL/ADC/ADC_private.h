#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H


#define ADMUX   *((volatile u8*)0x27)
#define ADCSRA  *((volatile u8*)0x26)
#define ADCH    *((volatile u8*)0x25)
#define ADCL    *((volatile u8*)0x24)
#define ADC     *((volatile u16*)0x24)
#define SFIOR   *((volatile u8*)0x50)


#define REFS1   7
#define REFS0   6
#define ADLAR   5


#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0


#define ADTS2   7
#define ADTS1   6
#define ADTS0   5


#define LEFT_ADJUSTMEN     0
#define RIGHT_ADJUSTMEN    1


#define FREE_RUNNING                 0
#define ANALOG_COMPARATOR            1
#define EXTERNAL_INTERRUPT0          2
#define TIMER0_COMPARE_MATCH         3
#define TIMER0_OVERFLOW              4
#define TIMER1_COMPARE_MATCH_B       5
#define TIMER1_OVERFLOW              6
#define TIMER1_CAPTURE_EVENT         7

#endif
