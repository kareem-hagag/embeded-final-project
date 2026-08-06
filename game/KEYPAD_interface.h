#ifndef KEYPAD_INTERFACE_H
#define KEYPAD_INTERFACE_H

#define KEYPAD_NO_KEY   0xFF

void KEYPAD_voidInit(void);
u8   KEYPAD_u8GetPressedKey(void);   /* Non-blocking: returns KEYPAD_NO_KEY if nothing pressed */
u8   KEYPAD_u8WaitForKey(void);      /* Blocking: waits until a key is pressed */

#endif /* KEYPAD_INTERFACE_H */
