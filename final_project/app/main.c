/***      Auther : kareem hagag    ***/
/***      title : final project             ***/
/***      file : timer 1 main   ***/
/*
#include <avr/delay.h>
#include "mcal/TIMER for servo/Timer1_Int.h"
int main(void)
{
    TIMER1_voidServoInit();

    TIMER1_voidServoSetAngle(0);
    _delay_ms(2000);

    TIMER1_voidServoSetAngle(90);
    _delay_ms(2000);

    while (1)
    {
        //the read of password
    }
}


//LED CODE
 * #include "../../std_lib/Std_Types.h"
#include "../../std_lib/Bit_Math.h"
#include "mcal/DIO/Dio_Int.h"
#include "hall/LED/led_int.h"

int main(void)
{
    DIO_voidInitialization();
    LED_voidInit(LED_GREEN);
    LED_voidInit(LED_YELLOW);
    LED_voidInit(LED_RED);

    while (1)
    {
        LED_voidTurnOn(LED_GREEN);
        _delay_ms(1000);
        LED_voidTurnOff(LED_GREEN);

        LED_voidTurnOn(LED_YELLOW);
        _delay_ms(1000);
        LED_voidTurnOff(LED_YELLOW);

        LED_voidTurnOn(LED_RED);
        _delay_ms(1000);
        LED_voidTurnOff(LED_RED);
    }

    return 0;
}






*/
