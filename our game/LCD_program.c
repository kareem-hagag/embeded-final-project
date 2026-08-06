#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_config.h"

static void LCD_voidEnablePulse(void)
{
    DIO_voidSetPinValue(LCD_PORT, LCD_EN_PIN, DIO_HIGH);
    TIMER_voidDelayMs(1);
    DIO_voidSetPinValue(LCD_PORT, LCD_EN_PIN, DIO_LOW);
    TIMER_voidDelayMs(1);
}

static void LCD_voidSendNibble(u8 Copy_u8Nibble)
{
    DIO_voidSetPinValue(LCD_PORT, LCD_D4_PIN, GET_BIT(Copy_u8Nibble, 0));
    DIO_voidSetPinValue(LCD_PORT, LCD_D5_PIN, GET_BIT(Copy_u8Nibble, 1));
    DIO_voidSetPinValue(LCD_PORT, LCD_D6_PIN, GET_BIT(Copy_u8Nibble, 2));
    DIO_voidSetPinValue(LCD_PORT, LCD_D7_PIN, GET_BIT(Copy_u8Nibble, 3));
    LCD_voidEnablePulse();
}

void LCD_voidSendCommand(u8 Copy_u8Command)
{
    DIO_voidSetPinValue(LCD_PORT, LCD_RS_PIN, DIO_LOW);
    LCD_voidSendNibble(Copy_u8Command >> 4);
    LCD_voidSendNibble(Copy_u8Command & 0x0F);
    TIMER_voidDelayMs(2);
}

void LCD_voidSendChar(u8 Copy_u8Char)
{
    DIO_voidSetPinValue(LCD_PORT, LCD_RS_PIN, DIO_HIGH);
    LCD_voidSendNibble(Copy_u8Char >> 4);
    LCD_voidSendNibble(Copy_u8Char & 0x0F);
    TIMER_voidDelayMs(1);
}

void LCD_voidInit(void)
{
    DIO_voidSetPinDirection(LCD_PORT, LCD_RS_PIN, DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_PORT, LCD_EN_PIN, DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_PORT, LCD_D4_PIN, DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_PORT, LCD_D5_PIN, DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_PORT, LCD_D6_PIN, DIO_OUTPUT);
    DIO_voidSetPinDirection(LCD_PORT, LCD_D7_PIN, DIO_OUTPUT);

    TIMER_voidDelayMs(30); /* power-on delay */

    /* Forced 4-bit init sequence (HD44780 datasheet) */
    DIO_voidSetPinValue(LCD_PORT, LCD_RS_PIN, DIO_LOW);
    LCD_voidSendNibble(0x03);
    TIMER_voidDelayMs(5);
    LCD_voidSendNibble(0x03);
    TIMER_voidDelayMs(1);
    LCD_voidSendNibble(0x03);
    TIMER_voidDelayMs(1);
    LCD_voidSendNibble(0x02);

    LCD_voidSendCommand(LCD_CMD_4BIT_2LINE);
    LCD_voidSendCommand(LCD_CMD_DISPLAY_ON);
    LCD_voidSendCommand(LCD_CMD_CLEAR);
    LCD_voidSendCommand(LCD_CMD_ENTRY_MODE);
}

void LCD_voidSendString(u8 *Copy_pu8String)
{
    u8 Local_u8Idx = 0;
    while(Copy_pu8String[Local_u8Idx] != '\0')
    {
        LCD_voidSendChar(Copy_pu8String[Local_u8Idx]);
        Local_u8Idx++;
    }
}

void LCD_voidGoToXY(u8 Copy_u8Row, u8 Copy_u8Col)
{
    u8 Local_u8Address;
    if(Copy_u8Row == 0) { Local_u8Address = LCD_CMD_DDRAM_LINE1 + Copy_u8Col; }
    else                { Local_u8Address = LCD_CMD_DDRAM_LINE2 + Copy_u8Col; }
    LCD_voidSendCommand(Local_u8Address);
}

void LCD_voidClear(void)
{
    LCD_voidSendCommand(LCD_CMD_CLEAR);
    TIMER_voidDelayMs(2);
}

void LCD_voidSendNumber(s32 Copy_s32Number)
{
    u8 Local_au8Buffer[12];
    s8 Local_s8Idx = 0;
    u8 Local_u8IsNegative = 0;

    if(Copy_s32Number == 0)
    {
        LCD_voidSendChar('0');
        return;
    }
    if(Copy_s32Number < 0)
    {
        Local_u8IsNegative = 1;
        Copy_s32Number = -Copy_s32Number;
    }
    while(Copy_s32Number > 0)
    {
        Local_au8Buffer[Local_s8Idx++] = (u8)((Copy_s32Number % 10) + '0');
        Copy_s32Number /= 10;
    }
    if(Local_u8IsNegative) { LCD_voidSendChar('-'); }
    while(Local_s8Idx > 0)
    {
        LCD_voidSendChar(Local_au8Buffer[--Local_s8Idx]);
    }
}
