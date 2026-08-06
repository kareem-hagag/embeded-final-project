#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"
#include "KEYPAD_config.h"

static const u8 KEYPAD_au8RowPins[4] = {KEYPAD_ROW0_PIN, KEYPAD_ROW1_PIN, KEYPAD_ROW2_PIN, KEYPAD_ROW3_PIN};
static const u8 KEYPAD_au8ColPins[4] = {KEYPAD_COL0_PIN, KEYPAD_COL1_PIN, KEYPAD_COL2_PIN, KEYPAD_COL3_PIN};

void KEYPAD_voidInit(void)
{
    u8 Local_u8Idx;
    for(Local_u8Idx = 0; Local_u8Idx < 4; Local_u8Idx++)
    {
        /* Rows: output, idle HIGH */
        DIO_voidSetPinDirection(KEYPAD_PORT, KEYPAD_au8RowPins[Local_u8Idx], DIO_OUTPUT);
        DIO_voidSetPinValue(KEYPAD_PORT, KEYPAD_au8RowPins[Local_u8Idx], DIO_HIGH);

        /* Columns: input with internal pull-up (pressed key reads LOW) */
        DIO_voidSetPinDirection(KEYPAD_PORT, KEYPAD_au8ColPins[Local_u8Idx], DIO_INPUT);
        DIO_voidSetPinValue(KEYPAD_PORT, KEYPAD_au8ColPins[Local_u8Idx], DIO_HIGH);
    }
}

u8 KEYPAD_u8GetPressedKey(void)
{
    u8 Local_u8Row, Local_u8Col;
    u8 Local_u8Pressed = KEYPAD_NO_KEY;

    for(Local_u8Row = 0; Local_u8Row < 4; Local_u8Row++)
    {
        DIO_voidSetPinValue(KEYPAD_PORT, KEYPAD_au8RowPins[Local_u8Row], DIO_LOW);

        for(Local_u8Col = 0; Local_u8Col < 4; Local_u8Col++)
        {
            if(DIO_u8GetPinValue(KEYPAD_PORT, KEYPAD_au8ColPins[Local_u8Col]) == DIO_LOW)
            {
                Local_u8Pressed = KEYPAD_au8Keys[Local_u8Row][Local_u8Col];
                TIMER_voidDelayMs(20); /* debounce */
                while(DIO_u8GetPinValue(KEYPAD_PORT, KEYPAD_au8ColPins[Local_u8Col]) == DIO_LOW)
                {
                    /* wait for key release */
                }
            }
        }
        DIO_voidSetPinValue(KEYPAD_PORT, KEYPAD_au8RowPins[Local_u8Row], DIO_HIGH);
    }
    return Local_u8Pressed;
}

u8 KEYPAD_u8WaitForKey(void)
{
    u8 Local_u8Key;
    do
    {
        Local_u8Key = KEYPAD_u8GetPressedKey();
    } while(Local_u8Key == KEYPAD_NO_KEY);
    return Local_u8Key;
}
