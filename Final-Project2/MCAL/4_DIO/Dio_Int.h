/*************************************************************/
/************ Auther : kareem hagag ******************/
/************ date : 29/7/2026 ******************/
/************ Title: interface ********************/
/**************************************************************/
//#include "../std_lib/Std_Types.h"
#ifndef DIO_INT_H
#define DIO_INT_H
/**************** define ports ******************/
#define DIO_PORTA     0
#define DIO_PORTB     1
#define DIO_PORTC     2
#define DIO_PORTD     3
/**************** define pins ******************/
#define PIN0      0
#define PIN1      1
#define PIN2      2
#define PIN3      3
#define PIN4      4
#define PIN5      5
#define PIN6      6
#define PIN7      7
/**************** direction ******************/
#define INPUT     0
#define OUTPUT    1
/**************** +5/0 ******************/
#define LOW       0
#define HIGH      1
/*************** function prototypes that use in program ********************/
void DIO_voidInitialization(void); 
void DIO_voidSetPinDirection(u8 PortID, u8 PinID, u8 Direction);
void DIO_voidSetpinValue(u8 PortID, u8 PinID, u8 Value);          //output value
u8   DIO_u8GetPinValue(u8 PortID, u8 PinID);                      //input value 
void DIO_voidTogglePinValue(u8 PortID, u8 PinID);                 //Toggle Pin Value Function
void DIO_voidSetPortDirection(u8 PortID, u8 Direction);          //Set Port Direction Function
void DIO_voidSetPortValue(u8 PortID, u8 Value);                  //Set Port Value Function

#endif
