/***      Auther : kareem hagag    ***/
/***      title : final project             ***/
/***      file : timer 1 private   ***/
#ifndef TIMER1_PRIVATE_H
#define TIMER1_PRIVATE_H

/* Timer1 Registers Addresses */
#define TCCR1A   *((volatile u8*)0x4F)
#define TCCR1B   *((volatile u8*)0x4E)
#define TCNT1    *((volatile u16*)0x4C)
#define OCR1A    *((volatile u16*)0x4A)
#define OCR1B    *((volatile u16*)0x48)
#define ICR1     *((volatile u16*)0x46)

/* TCCR1A Bits */
#define TIMER1_WGM10    0
#define TIMER1_WGM11    1
#define TIMER1_COM1A0   6
#define TIMER1_COM1A1   7

/* TCCR1B Bits */
#define TIMER1_WGM12    3
#define TIMER1_WGM13    4

#endif
