#ifndef ADC_INT_H
#define ADC_INT_H

#define ADC0    0
#define ADC1    1
#define ADC2    2
#define ADC3    3
#define ADC4    4
#define ADC5    5
#define ADC6    6
#define ADC7    7

void ADC_voidInit(void);

void ADC_voidADCEnable(void);
void ADC_voidADCDisable(void);

void ADC_voidStartConverstion(void);

u16 ADC_u16Read(void);

void ADC_voidAutoTrigger(void);

void ADC_voidInterruptEnable(void);

typedef void (*pf)(void);

void ADC_voidSetCallBack(pf FunctionAddress);

#endif
