#ifndef LCD_INT_H
#define LCD_INT_H

#include "Std_Types.h"

void LCD_voidLCDInit(void);
void LCD_voidSendCommand(u8 u8CMD);
void LCD_voidSendData(u8 u8Data);
void LCD_GotoXY(u8 x,u8 y);
void LCD_voidWriteString(u8 *u8String);
void LCD_voidWriteNumber(u8 u8Number);

#endif
