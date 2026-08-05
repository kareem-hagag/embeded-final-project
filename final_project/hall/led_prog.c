/***      Auther : kareem hagag    ***/
/***      title : final project             ***/
/***      file : timer 1 interface   ***/

#include "../../std_lib/Std_Types.h"
#include "../../std_lib/Bit_Math.h"
#include "../DIO/Dio_Int.h"
#include "led_int.h"

void LED_voidInit(u8 u8LedColor)
{

    switch (u8LedColor)
    {
        case LED_GREEN:  DIO_voidSetPinDirection(DIO_PORTB, PIN0, OUTPUT); break;
        case LED_YELLOW: DIO_voidSetPinDirection(DIO_PORTB, PIN1, OUTPUT); break;
        case LED_RED:    DIO_voidSetPinDirection(DIO_PORTB, PIN2, OUTPUT); break;
    }
}

void LED_voidTurnOn(u8 u8LedColor)
{
    switch (u8LedColor)
    {
        case LED_GREEN:  DIO_voidSetPinValue(DIO_PORTB, PIN0, HIGH); break;
        case LED_YELLOW: DIO_voidSetPinValue(DIO_PORTB, PIN1, HIGH); break;
        case LED_RED:    DIO_voidSetPinValue(DIO_PORTB, PIN2, HIGH); break;
    }
}

void LED_voidTurnOff(u8 u8LedColor)
{
    switch (u8LedColor)
    {
        case LED_GREEN:  DIO_voidSetPinValue(DIO_PORTB, PIN0, LOW); break;
        case LED_YELLOW: DIO_voidSetPinValue(DIO_PORTB, PIN1, LOW); break;
        case LED_RED:    DIO_voidSetPinValue(DIO_PORTB, PIN2, LOW); break;
    }
}

void LED_voidToggle(u8 u8LedColor)
{
    switch (u8LedColor)
    {
        case LED_GREEN:  DIO_voidTogglePinValue(DIO_PORTB, PIN0); break;
        case LED_YELLOW: DIO_voidTogglePinValue(DIO_PORTB, PIN1); break;
        case LED_RED:    DIO_voidTogglePinValue(DIO_PORTB, PIN2); break;
    }
}
