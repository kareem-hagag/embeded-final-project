/*
 * TIMER_int.h
 *
 *  Created on: Aug 2, 2026
 *      Author: EL-Mostwred
 */
/********/
/*       Author: Mariam Shaban      */
/*        Date  : 4/08/2026        */
/*        File: interface File        */
/********/



#ifndef TIM0_INTERFACE_H_
#define TIM0_INTERFACE_H_

typedef void (*pf)(void);
void TIM0_voidinit(void);

/* Overflow Mode Functions */
void TIM0_voidEnableOVInterrupt(void);
void TIM0_voidDisableOVInterrupt(void);
void TIM0_voidSetOVReg(u8 u8OVRegValue);
u8   TIM0_u8ReadOVReg(void);
void TIM0_voidOVSetCallBack(pf OVFunctionAddress);

/* CTC Mode Functions */
void TIM0_voidEnableCTCInterrupt(void);
void TIM0_voidDisableCTCInterrupt(void);
void TIM0_voidSetCTCReg(u8 u8CTCRegValue);
u8   TIM0_u8ReadCTCCTCReg(void);
void TIM0_voidCTCSetCallBack(pf CTCFunctionAddress);
/* PWM functions*/
void TIM0_voidStartFastPWM(u8 u8DutyCycle);
void TIM0_voidStartPhaseCorrectPWM(u8 u8DutyCycle);



#endif
