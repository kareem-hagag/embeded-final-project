#ifndef TIM0_PRIVATE_H
#define TIM0_PRIVATE_H

#define TCCR0   *((volatile u8*)0x53)
#define TCNT0   *((volatile u8*)0x52)
#define OCR0    *((volatile u8*)0x5C)
#define TIMSK   *((volatile u8*)0x59)
#define TIFR    *((volatile u8*)0x58)

#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

#define OCIE0   1
#define TOIE0   0

#define OCF0    1
#define TOV0    0

#define NORMAL_MODE        0
#define PWM_PHASE_MODE     1
#define CTC_MODE           2
#define FAST_PWM_MODE      3

#define NO_CLOCK           0
#define NO_PRESCALER       1
#define PRESCALER_8        2
#define PRESCALER_64       3
#define PRESCALER_256      4
#define PRESCALER_1024     5
#define EXT_FALLING        6
#define EXT_RISING         7

#endif
