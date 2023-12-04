#ifndef UI_h
#define UI_h

#include "Time.h"
#include "LCD_Nokia1202.h"
#include "stdio.h"

#define Graph_Yh	 	30
#define Graph_Y0		46
#define Graph_Ymax	Graph_Y0-Graph_Yh
#define Graph_X0		0
#define Graph_Xmax	96
#define sym_0				25
#define sym_1				31
#define sym_2				37
#define sym_3				43
#define sym_4				49
#define sym_5				55


void printTime(RTC_TimeTypeDef *rtc_time);
void menu_print(uint8_t KEY[]);
void menu_key(uint8_t KEY[]);
void LightEnable(void);
void FirstBoot(void);
int get_en_key();
uint8_t UI(uint8_t KEY[]);

#endif
