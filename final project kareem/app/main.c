/**************************************************************/
/************ Author : Kareem Hagag *****************************/
/************ Date   : 29/7/2026 ********************************/
/************ Title  : MAIN *************************************/
/**************************************************************/

#include <avr/delay.h>
#include "std_lib/Std_Types.h"
#include "std_lib/Bit_Math.h"

#include "mcal/DIO/Dio_Int.h"
#include "hall/LCD/Lcd_Int.h"

int main(void)
{
    DIO_voidInitialization();
    LCD_voidInit();
    LCD_voidClearScreen();
    LCD_voidGoToXY(0, 0);
    LCD_voidSendString((u8 *)"my name is Kareem!");
    LCD_voidGoToXY(1, 0);
    LCD_voidSendString((u8 *)"Val: ");
    LCD_voidSendNumber(2026);

    while (1)
    {
        /* Loop is running */
    }

    return 0;
}
