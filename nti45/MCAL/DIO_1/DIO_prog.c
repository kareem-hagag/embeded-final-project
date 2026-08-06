/***program file***/
/***Ahmed***/

#include "Bit_Math.h"
#include "Std_Types.h"

#include "DIO_config.h"
#include "DIO_int.h"
#include "DIO_private.h"


void DIO_voidInitialization(void)
{
	DDRA_REG = DIO_PORTA_DIRECTIONS;
	DDRB_REG = DIO_PORTB_DIRECTIONS;
	DDRC_REG = DIO_PORTC_DIRECTIONS;
	DDRD_REG = DIO_PORTD_DIRECTIONS;
}
void DIO_voidSetPinDirection(u8 PortID, u8 PinID, u8 Direction)
{
	if(PortID<4 && PinID<8)
	{
		if(Direction==OUTPUT)
		{
			switch(PortID)
			{
			case PORTA:
			SET_BIT(DDRA_REG,PinID);
			break;
			case PORTB:
			SET_BIT(DDRB_REG,PinID);
			break;
			case PORTC:
			SET_BIT(DDRC_REG,PinID);
			break;
			case PORTD:
			SET_BIT(DDRD_REG,PinID);
			break;
			}
		}
		else if(Direction==INPUT)
		{
			switch(PortID)
			{
			case PORTA:
			CLR_BIT(DDRA_REG,PinID);
			break;
			case PORTB:
			CLR_BIT(DDRB_REG,PinID);
			break;
			case PORTC:
			CLR_BIT(DDRC_REG,PinID);
		     break;
			case PORTD:
			CLR_BIT(DDRD_REG,PinID);
			break;
			}
		}
		else
		{
			/*no comment*/
		}
	}
}
#define CONC_BIT(b7,b6,b5,b4,b3,b2,b1,b0) CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0)
#define CONC_HELP(b7,b6,b5,b4,b3,b2,b1,b0) 0b##b7##b6##b5##b4##b3##b2##b1##b0


void DIO_voidSetPinValue(u8 PortID, u8 PinID, u8 Value)
{
	if(PortID<4 && PinID<8)
	{
		if(Value==HIGH)
		{
			switch(PortID)
			{
			case PORTA:
			SET_BIT(PORTA_REG,PinID);
			break;
			case PORTB:
			SET_BIT(PORTB_REG,PinID);
			break;
			case PORTC:
			SET_BIT(PORTC_REG,PinID);
			break;
			case PORTD:
			SET_BIT(PORTD_REG,PinID);
			break;
			}
		}
		else if(Value==LOW)
		{
			switch(PortID)
			{
			case PORTA:
			CLR_BIT(PORTA_REG,PinID);
			break;
			case PORTB:
			CLR_BIT(PORTB_REG,PinID);
			break;
			case PORTC:
			CLR_BIT(PORTC_REG,PinID);
		     break;
			case PORTD:
			CLR_BIT(PORTD_REG,PinID);
			break;
			}
		}
	}
}
u8 DIO_u8GetPinValue(u8 PortID, u8 PinID)
{
    u8 Local_u8PinValue = 0;
    if(PortID<4 && PinID<8)
    {
    switch(PortID)
    {
        case PORTA:
        Local_u8PinValue = GET_BIT(PINA_REG, PinID);
        break;

        case PORTB:
        Local_u8PinValue = GET_BIT(PINB_REG, PinID);
        break;

        case PORTC:
        Local_u8PinValue = GET_BIT(PINC_REG, PinID);
        break;

        case PORTD:
        Local_u8PinValue = GET_BIT(PIND_REG, PinID);
        break;
    }
    }
    return Local_u8PinValue;
}
void DIO_voidTogglePin(u8 PortID, u8 PinID)
{
	if(PortID<4 && PinID<8)
	{
    switch(PortID)
    {
        case PORTA:
        TOGGLE_BIT(PORTA_REG, PinID);
        break;

        case PORTB:
        TOGGLE_BIT(PORTB_REG, PinID);
        break;

        case PORTC:
        TOGGLE_BIT(PORTC_REG, PinID);
        break;

        case PORTD:
        TOGGLE_BIT(PORTD_REG, PinID);
        break;
    }
    }
}
void DIO_voidSetPortDirection(u8 PortID, u8 Direction)
{
	if(PortID<4)
	{
    switch(PortID)
    {
        case PORTA:
        DDRA_REG = Direction;
        break;

        case PORTB:
        DDRB_REG = Direction;
        break;

        case PORTC:
        DDRC_REG = Direction;
        break;

        case PORTD:
        DDRD_REG = Direction;
        break;
    }
    }
}
void DIO_voidSetPortValue(u8 PortID, u8 Value)
{
	if(PortID<4)
	{
    switch(PortID)
    {
        case PORTA:
        PORTA_REG = Value;
        break;

        case PORTB:
        PORTB_REG = Value;
        break;

        case PORTC:
        PORTC_REG = Value;
        break;

        case PORTD:
        PORTD_REG = Value;
        break;
    }
    }
}
