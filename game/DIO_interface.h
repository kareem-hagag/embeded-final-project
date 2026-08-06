#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#define DIO_PORTA   0
#define DIO_PORTB   1
#define DIO_PORTC   2
#define DIO_PORTD   3

#define DIO_INPUT   0
#define DIO_OUTPUT  1

#define DIO_LOW     0
#define DIO_HIGH    1

void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);
u8   DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin);
void DIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);
void DIO_voidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);

#endif /* DIO_INTERFACE_H */
