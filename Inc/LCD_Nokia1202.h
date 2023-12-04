#ifndef __LCD
#define __LCD

#include "stm32f10x.h"
#include "LCD_Nokia1202.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stdlib.h"
#include "stdio.h"
#include "main.h"


//+=====+================+===========+
//|	PIN	|			HX1230		 | Nokia1202 |
//+=====+================+===========+
//|	1		|			Reset			 |		N/C		 |
//|	2		|			CE(CS)		 |		Reset	 |
//|	3		|			N/C			   |		CS		 |
//|	4		|DIN(SDA or MOSI)|		GND		 |
//|	5		|			SCLK(CLK)	 |		MOSI	 |
//|	6		|			3V3				 |		SCK	 	 |
//|	7		|			LED+			 |		3V3		 |
//|	8		|			GND			   |		3V3		 |
//|	9		|			-					 |		GND		 |
//|	10	|			-					 |		LED-	 |
//|	11	|			-			 		 |		LED+	 |
//|	12	|			-					 |		N/C		 |
//+=====+================+===========+

//			Конфигурация порта
//	используемый порт
#define LCD_port				GPIOB
//	используемые выводы
#define LCD_LED_pin				GPIO_Pin_9
#define LCD_SCLK_pin			GPIO_Pin_8
#define LCD_MOSI_pin			GPIO_Pin_7
#define LCD_CS_pin				GPIO_Pin_6
#define LCD_RST_pin				GPIO_Pin_5
//	включить тактирование порта
#define LCD_RCC						RCC_APB2Periph_GPIOB

//	Используемые биты для работы с дисплеем. 
//	Так же в основном коде программы выводы нужно инициализировать
#define LCD_BlueLED_on 		GPIO_SetBits	(LCD_port, LCD_LED_pin);	
#define LCD_BlueLED_off 	GPIO_ResetBits(LCD_port, LCD_LED_pin);	
#define LCD_SCLK_on 			GPIO_SetBits	(LCD_port, LCD_SCLK_pin);	
#define LCD_MOSI_on 			GPIO_SetBits	(LCD_port, LCD_MOSI_pin);	
#define LCD_CS_on 				GPIO_SetBits	(LCD_port, LCD_CS_pin);	
#define LCD_RST_on 				GPIO_SetBits	(LCD_port, LCD_RST_pin);	
#define LCD_SCLK_off 			GPIO_ResetBits(LCD_port, LCD_SCLK_pin);	
#define LCD_MOSI_off 			GPIO_ResetBits(LCD_port, LCD_MOSI_pin);	
#define LCD_CS_off 				GPIO_ResetBits(LCD_port, LCD_CS_pin);	
#define LCD_RST_off 			GPIO_ResetBits(LCD_port, LCD_RST_pin);	


#define Graph_Yh	 				30
#define Graph_Y0					46
#define Graph_Ymax				Graph_Y0-Graph_Yh
#define Graph_X0					0
#define Graph_Xmax				96


#define LCD_X        			96
#define LCD_Y        			68
#define LCD_String    		9
#define LCD_D         		1			// Данные
#define LCD_C         		0   	// Команда
#define SetYAddr   				0xB0
#define SetXAddr4  				0x00
#define SetXAddr3  				0x10

#define swap(a, b) {uint8_t t = a; a = b; b = t; }

extern uint8_t _LCD_RAM[LCD_X*LCD_String]; // Память нашего LCD

void LCD_SendByte(uint8_t mode, uint8_t c);
void LCD_Clear(void);
void LCD_Update(void);
void LCD_Init(void);
void LCD_DrawPixel(uint8_t x, uint8_t y, uint8_t color);
void LCD_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
void LCD_DrawFastVLine(uint8_t x, uint8_t y, uint8_t h, uint8_t color);
void LCD_DrawFastHLine(uint8_t x, uint8_t y, uint8_t w, uint8_t color);
void LCD_DrawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
void LCD_FillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
void LCD_FillScreen(uint8_t color);
void LCD_DrawChar(uint8_t x, uint8_t y, uint8_t color, unsigned char c);
void LCD_print(uint8_t x, uint8_t y, uint8_t color, char *str);
void LCD_write(uint8_t x, uint8_t y, uint8_t color, uint8_t num);
void LCD_write_float(uint8_t x, uint8_t y, uint8_t color, float num);
void LCD_DrawBitmap(uint8_t x, uint8_t y, const char *bitmap, uint8_t w, uint8_t h, uint8_t color);

void LCD_delay(uint16_t p);

#endif
