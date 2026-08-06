#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H

/* CPU frequency used for _delay_ms() - change to match your Proteus crystal (e.g. 1MHz, 8MHz, 16MHz) */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define TIMER0_REG_TCCR0   TCCR0
#define TIMER0_REG_TCNT0   TCNT0

#endif /* TIMER_PRIVATE_H */
