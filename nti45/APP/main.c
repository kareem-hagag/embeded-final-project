#include "Std_Types.h"
#include "../MCAL/DIO_1/DIO_int.h"
#include "../MCAL/LCD_1/LCD_int.h"
#include "../MCAL/KEYPAD/KEYPAD_int.h"

#include <util/delay.h>

int main(void)
{
	u8 Key;
	DIO_voidInitialization();
	LCD_voidLCDInit();
while(1)
{
	Key=KEYPAD_u8GetPressedKey();
	if(Key!=0xFF)
	{
LCD_voidSendData(Key);
_delay_ms(250);
}
}
return 0;
}
