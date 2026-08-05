#include "Std_Types.h"
#include "Bit_Math.h"
#include "../DIO_1/DIO_int.h"

#include "KEYPAD_config.h"
#include "KEYPAD_private.h"
#include "KEYPAD_int.h"

void KEYPAD_voidInit(void)
{
	DIO_voidSetPinValue(KEYPAD_ROW0,HIGH);
	DIO_voidSetPinValue(KEYPAD_ROW1,HIGH);
	DIO_voidSetPinValue(KEYPAD_ROW2,HIGH);
	DIO_voidSetPinValue(KEYPAD_ROW3,HIGH);

	DIO_voidSetPinValue(KEYPAD_COL0,HIGH);
	DIO_voidSetPinValue(KEYPAD_COL1,HIGH);
	DIO_voidSetPinValue(KEYPAD_COL2,HIGH);
	DIO_voidSetPinValue(KEYPAD_COL3,HIGH);
}

u8 KEYPAD_u8GetPressedKey(void)
{
	u8 RowValue;
	u8 PressedKey=0xFF;

	DIO_voidSetPinValue(KEYPAD_COL0,LOW);
	DIO_voidSetPinValue(KEYPAD_COL1,HIGH);
	DIO_voidSetPinValue(KEYPAD_COL2,HIGH);
	DIO_voidSetPinValue(KEYPAD_COL3,HIGH);

	RowValue=DIO_u8GetPinValue(KEYPAD_ROW0);
	RowValue|=DIO_u8GetPinValue(KEYPAD_ROW1)<<1;
	RowValue|=DIO_u8GetPinValue(KEYPAD_ROW2)<<2;
	RowValue|=DIO_u8GetPinValue(KEYPAD_ROW3)<<3;


	switch(RowValue)
	{
	case 0b00001110:
	PressedKey='1';
	break;

	case 0b00001101:
	PressedKey='4';
	break;

	case 0b00001011:
	PressedKey='7';
	break;

	case 0b00000111:
	PressedKey='*';
	break;

	default:
		PressedKey=0xFF;
		break;
	}

		DIO_voidSetPinValue(KEYPAD_COL0,HIGH);
		DIO_voidSetPinValue(KEYPAD_COL1,LOW);
		DIO_voidSetPinValue(KEYPAD_COL2,HIGH);
		DIO_voidSetPinValue(KEYPAD_COL3,HIGH);

		RowValue=DIO_u8GetPinValue(KEYPAD_ROW0);
		RowValue|=DIO_u8GetPinValue(KEYPAD_ROW1)<<1;
		RowValue|=DIO_u8GetPinValue(KEYPAD_ROW2)<<2;
		RowValue|=DIO_u8GetPinValue(KEYPAD_ROW3)<<3;


		switch(RowValue)
		{
		case 0b00001110:
		PressedKey='2';
		break;

		case 0b00001101:
		PressedKey='5';
		break;

		case 0b00001011:
		PressedKey='8';
		break;

		case 0b00000111:
		PressedKey='0';
		break;

		default:
			PressedKey=0xFF;
			break;
		}

			DIO_voidSetPinValue(KEYPAD_COL0,HIGH);
			DIO_voidSetPinValue(KEYPAD_COL1,HIGH);
			DIO_voidSetPinValue(KEYPAD_COL2,LOW);
			DIO_voidSetPinValue(KEYPAD_COL3,HIGH);

			RowValue=DIO_u8GetPinValue(KEYPAD_ROW0);
			RowValue|=DIO_u8GetPinValue(KEYPAD_ROW1)<<1;
			RowValue|=DIO_u8GetPinValue(KEYPAD_ROW2)<<2;
			RowValue|=DIO_u8GetPinValue(KEYPAD_ROW3)<<3;


			switch(RowValue)
			{
			case 0b00001110:
			PressedKey='3';
			break;

			case 0b00001101:
			PressedKey='6';
			break;

			case 0b00001011:
			PressedKey='9';
			break;

			case 0b00000111:
			PressedKey='#';
			break;

			default:
				PressedKey=0xFF;
				break;
			}

				DIO_voidSetPinValue(KEYPAD_COL0,HIGH);
				DIO_voidSetPinValue(KEYPAD_COL1,HIGH);
				DIO_voidSetPinValue(KEYPAD_COL2,HIGH);
				DIO_voidSetPinValue(KEYPAD_COL3,LOW);

				RowValue=DIO_u8GetPinValue(KEYPAD_ROW0);
				RowValue|=DIO_u8GetPinValue(KEYPAD_ROW1)<<1;
				RowValue|=DIO_u8GetPinValue(KEYPAD_ROW2)<<2;
				RowValue|=DIO_u8GetPinValue(KEYPAD_ROW3)<<3;


				switch(RowValue)
				{
				case 0b00001110:
				PressedKey='/';
				break;

				case 0b00001101:
				PressedKey='+';
				break;

				case 0b00001011:
				PressedKey='-';
				break;

				case 0b00000111:
				PressedKey='*';
				break;

				default:
					PressedKey=0xFF;
					break;
				}
	return PressedKey;
}


