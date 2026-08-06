#include "Bit_Math.h"
#include "Std_Types.h"

#include "DIO_int.h"
#include "LCD_config.h"
#include "LCD_int.h"
#include <avr/delay.h>
#include "LCD_private.h"

static void LCD_voidPutOnBus(u8 u8Char)
{
    // set each value of u8Char to each value of LCD
    DIO_voidSetPinValue(LCD_D0, GET_BIT(u8Char, 0));
    DIO_voidSetPinValue(LCD_D1, GET_BIT(u8Char, 1));
    DIO_voidSetPinValue(LCD_D2, GET_BIT(u8Char, 2));
    DIO_voidSetPinValue(LCD_D3, GET_BIT(u8Char, 3));
    DIO_voidSetPinValue(LCD_D4, GET_BIT(u8Char, 4));
    DIO_voidSetPinValue(LCD_D5, GET_BIT(u8Char, 5));
    DIO_voidSetPinValue(LCD_D6, GET_BIT(u8Char, 6));
    DIO_voidSetPinValue(LCD_D7, GET_BIT(u8Char, 7));

    // activate enable and wait 2 ms
    DIO_voidSetPinValue(LCD_EN, HIGH);
    _delay_ms(2);

    // disactivate enable and wait 2 ms
    DIO_voidSetPinValue(LCD_EN, LOW);
    _delay_ms(2);
}

void LCD_voidInit(void)
{
    // wait 30 ms
    _delay_ms(35);
    // send home command and wait 1 ms
    LCD_voidSendCommand(LCD_HOME);
    _delay_ms(1);    
    // send function set command and wait 1 ms
    LCD_voidSendCommand(LCD_FUNCTIONSET_8BIT);
    _delay_ms(1);
    // send display on/off command and wait 1 ms
    LCD_voidSendCommand(LCD_DISPLAYON);
    _delay_ms(1);
    // send display clear command and wait 1ms 
    LCD_voidSendCommand(LCD_CLEAR);
    _delay_ms(2);
    // send entry mode command and wait 1ms
    LCD_voidSendCommand(LCD_ENTRY_MODE);
    _delay_ms(1);

}

void LCD_voidSendCommand(u8 u8CMD)
{
    // command register
    DIO_voidSetPinValue(LCD_RS, LOW); 
    DIO_voidSetPinValue(LCD_RW, LOW); 

    LCD_voidPutOnBus(u8CMD);
}
void LCD_voidSendData(u8 u8DATA)
{
    // Data register
    DIO_voidSetPinValue(LCD_RS, HIGH); 
    DIO_voidSetPinValue(LCD_RW, LOW); 

    LCD_voidPutOnBus(u8DATA);

}

void LCD_voidGoToXY(u8 u8XPos, u8 u8YPos)
{
    u8 Local_u8Address;

    switch(u8YPos)
    {
        case 0: Local_u8Address = 0x00 + u8XPos; break;
        case 1: Local_u8Address = 0x40 + u8XPos; break;
        case 2: Local_u8Address = 0x14 + u8XPos; break;
        case 3: Local_u8Address = 0x54 + u8XPos; break;
        default: Local_u8Address = 0x00 + u8XPos; break;
    }

    LCD_voidSendCommand(LCD_SETCURSOR | Local_u8Address);
}

void LCD_voidSendString(const u8 *pu8String)
{
    u8 Local_u8Iterator = 0;

    while(pu8String[Local_u8Iterator] != '\0')
    {
        LCD_voidSendData(pu8String[Local_u8Iterator]);
        Local_u8Iterator++;
    }
}

void LCD_voidSendLongNumber(s32 s32Number)
{
    if(s32Number < 0)
    {
        LCD_voidSendData('-');
        s32Number = -s32Number;
    }

    if(s32Number > 9)
    {
        LCD_voidSendLongNumber(s32Number / 10);
    }

    LCD_voidSendData((s32Number % 10) + '0');
}

void LCD_voidClearScreen(void)
{
    LCD_voidSendCommand(LCD_CLEAR);
    _delay_ms(2);
}

