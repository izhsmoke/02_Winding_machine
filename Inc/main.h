#ifndef MAIN_H
#define MAIN_H
#include "stm32f10x.h"


#define UI_do 		0
#define KEY_do 		1
#define KEY_down	2
#define KEY_right	4
#define KEY_ok		8
#define KEY_up		16
#define KEY_left	32
#define KEY_left	32



void LED_Blink(void);
void delay_ms(uint16_t delay_temp);


#endif
