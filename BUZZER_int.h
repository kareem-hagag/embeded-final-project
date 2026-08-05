

/****/
/*       Author: Mariam Shaban      */
/*        Date  : 5/08/2026        */
/*        File: Interface File      */
/****/

#ifndef BUZZER_INT_H_
#define BUZZER_INT_H_


void BUZZER_voidInit(void);
void BUZZER_voidSetTone(u8 u8DutyCycle);
void BUZZER_voidStop(void);
void BUZZER_voidStartGradualAlarm(void);

#endif /* BUZZER_INT_H_ */
