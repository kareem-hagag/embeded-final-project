/*************************************************************/
/************ Auther : kareem hagag ******************/
/************ date : 29/7/2026 ******************/
/************ Title: private file ********************/
/**************************************************************/
#include "../../STD/Std_Types.h"
#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H
/*********** port A ****************/
#define DDRA     (*(volatile u8*)0x3A)
#define PORTA    (*(volatile u8*)0x3B)
#define PINA     (*(volatile u8*)0x39)
/*********** port B ****************/
#define DDRB     (*(volatile u8*)0x37)
#define PORTB    (*(volatile u8*)0x38)
#define PINB     (*(volatile u8*)0x36)
/*********** port C ****************/
#define DDRC     (*(volatile u8*)0x34)
#define PORTC    (*(volatile u8*)0x35)
#define PINC     (*(volatile u8*)0x33)
/*********** port D ****************/
#define DDRD     (*(volatile u8*)0x31)
#define PORTD    (*(volatile u8*)0x32)
#define PIND     (*(volatile u8*)0x30)

#endif
