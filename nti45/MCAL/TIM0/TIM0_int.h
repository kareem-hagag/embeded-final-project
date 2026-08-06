#ifndef TIM0_INT_H
#define TIM0_INT_H

typedef void (*pf)(void);

void TIM0_voidInit(void);

void TIM0_voidEnableOVInterrupt(void);
void TIM0_voidDisableOVInterrupt(void);

void TIM0_voidSetOVReg(u8 Copy_u8OVRegValue);
u8 TIM0_u8ReadOVReg(void);

void TIM0_voidOVSetCallBack(pf OVFunctionAddress);

void TIM0_voidEnableCTCInterrupt(void);
void TIM0_voidDisableCTCInterrupt(void);

void TIM0_voidSetCTCReg(u8 Copy_u8CTCRegValue);
u8 TIM0_u8ReadCTCReg(void);

void TIM0_voidCTCSetCallBack(pf CTCFunctionAddress);

#endif
