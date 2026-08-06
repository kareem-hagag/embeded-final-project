#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

void LCD_voidInit(void);
void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidSendChar(u8 Copy_u8Char);
void LCD_voidSendString(u8 *Copy_pu8String);
void LCD_voidGoToXY(u8 Copy_u8Row, u8 Copy_u8Col);
void LCD_voidClear(void);
void LCD_voidSendNumber(s32 Copy_s32Number);

#endif /* LCD_INTERFACE_H */
