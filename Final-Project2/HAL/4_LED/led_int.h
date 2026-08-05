/***      Auther : kareem hagag    ***/
/***      title : final project             ***/
/***      file : timer 1 interface   ***/
#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H
#include "../../STD/Std_Types.h"
/* LED Colors Definition */
#define LED_GREEN   0
#define LED_YELLOW  1
#define LED_RED     2

void LED_voidInit(u8 u8LedColor);
void LED_voidTurnOn(u8 u8LedColor);
void LED_voidTurnOff(u8 u8LedColor);
void LED_voidToggle(u8 u8LedColor);

#endif
