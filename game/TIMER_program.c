#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "TIMER_config.h"

void TIMER_voidInit(void)
{
    /* Normal mode, free running counter - also used later as a random seed source */
    TIMER0_REG_TCCR0 = TIMER0_PRESCALER;
    TIMER0_REG_TCNT0 = 0;
}

u8 TIMER_u8GetCounterValue(void)
{
    return TIMER0_REG_TCNT0;
}

void TIMER_voidDelayMs(u16 Copy_u16Ms)
{
    u16 Local_u16Counter;
    for(Local_u16Counter = 0; Local_u16Counter < Copy_u16Ms; Local_u16Counter++)
    {
        _delay_ms(1);
    }
}
