
/********/
/*       Author: Mariam Shaban      */
/*        Date  : 4/08/2026        */
/*        File: private File        */
/********/


#ifndef TIM0_PRIVATE_H_
#define TIM0_PRIVATE_H_


#define TCCR0   *((volatile u8*)0x53)
#define TCNT0   *((volatile u8*)0x52)
#define OCR0    *((volatile u8*)0x51)
#define TIMSK   *((volatile u8*)0x59)
#define TIFR    *((volatile u8*)0x58)
#define SREG    *((volatile u8*)0x5F)

/* TCCR0 Register Bits */
#define CS00    0
#define CS01    1
#define CS02    2
#define WGM01   3
#define COM00   4
#define COM01   5
#define WGM00   6
#define FOC00   7

/* TIMSK Register Bits */
#define TOIE0   0
#define OCIE0   1

/* TIFR Register Bits */
#define TOV0    0
#define OCF0    1

#endif
