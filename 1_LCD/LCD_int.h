#ifndef LCD_INT_H
#define LCD_INT_H
 
void LCD_voidInit(void);    
void LCD_voidSendCommand(u8 u8CMD);
void LCD_voidSendData(u8 u8DATA);
void LCD_voidClearScreen(void);
void LCD_voidGoToXY(u8 u8XPos, u8 u8YPos);
void LCD_voidSendString(const u8 *pu8String);
void LCD_voidSendLongNumber(s32 s32Number);



#endif // LCD_INT_H



