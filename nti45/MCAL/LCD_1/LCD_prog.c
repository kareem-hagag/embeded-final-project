#include "Std_Types.h"
#include "Bit_Math.h"
#include <util/delay.h>

#include "../DIO_1/DIO_int.h"

#include "LCD_config.h"
#include "LCD_private.h"
#include "LCD_int.h"

void LCD_voidLCDInit(void)
{
    _delay_ms(30);

    LCD_voidSendCommand(0x38);
    _delay_ms(1);

    LCD_voidSendCommand(0x0C);
    _delay_ms(1);

    LCD_voidSendCommand(0x01);
    _delay_ms(2);

    LCD_voidSendCommand(0x06);
    _delay_ms(1);
}

void LCD_voidSendCommand(u8 u8CMD)
{
    DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,LOW);
    DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,LOW);

    LCD_voidPutonBus(u8CMD);

    DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,LOW);
}

void LCD_voidSendData(u8 u8Data)
{
    DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,HIGH);
    DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,LOW);

    LCD_voidPutonBus(u8Data);

    DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,HIGH);
    _delay_ms(2);
    DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN,LOW);
}

static void LCD_voidPutonBus(u8 u8Char)
{
    DIO_voidSetPortValue(LCD_DATA_PORT,u8Char);
}

void LCD_GotoXY(u8 x,u8 y)
{
    if(x==0)
        LCD_voidSendCommand(0x80+y);

    else if(x==1)
        LCD_voidSendCommand(0xC0+y);
}

void LCD_voidWriteString(u8 *u8String)
{
    while(*u8String!='\0')
    {
        LCD_voidSendData(*u8String);
        u8String++;
    }
}

void LCD_voidWriteNumber(u8 u8Number)
{
    if(u8Number>=100)
    {
        LCD_voidSendData((u8Number/100)+'0');
        LCD_voidSendData(((u8Number%100)/10)+'0');
        LCD_voidSendData((u8Number%10)+'0');
    }
    else if(u8Number>=10)
    {
        LCD_voidSendData((u8Number/10)+'0');
        LCD_voidSendData((u8Number%10)+'0');
    }
    else
    {
        LCD_voidSendData(u8Number+'0');
    }
}
