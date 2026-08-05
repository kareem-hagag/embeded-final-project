/*************************************************************/
/************ Auther : kareem hagag ******************/
/************ date : 29/7/2026 ******************/
/************ Title: interface ********************/
/**************************************************************/
#ifndef TIM0_PRIVATE_H
#define TIM0_PRIVATE_H

/* Registers */
#define TCCR0   *((volatile u8*)0x53)
#define TCNT0   *((volatile u8*)0x52)
#define OCR0    *((volatile u8*)0x51)
#define TIMSK   *((volatile u8*)0x59)
#define TIFR    *((volatile u8*)0x58)

/* Modes */
#define TIM0_NORMAL_MODE            0
#define TIM0_PWM_PHASE_CORRECT_MODE 1
#define TIM0_CTC_MODE               2
#define TIM0_FAST_PWM_MODE          3

/* Clock Prescalers */
#define TIM0_NO_CLOCK               0
#define TIM0_PRESCALER_1            1
#define TIM0_PRESCALER_8            2
#define TIM0_PRESCALER_64           3
#define TIM0_PRESCALER_256          4
#define TIM0_PRESCALER_1024         5
#define TIM0_EXT_CLK_FALLING        6
#define TIM0_EXT_CLK_RISING         7

#endif
