#include "stm32f10x.h"
#include "LCD_Nokia1202.h"
#include "stm32f10x_rtc.h"
#include "main.h"
#include "Time.h"
#include "InitAll.h"
#include "UI.h"
#include "Steppers.h"


uint8_t 	_LCD_RAM[LCD_X*LCD_String];
uint16_t 	delay_count;


RTC_TimeTypeDef	RTC_Time;	//структура для часов

//режим работы
uint8_t 	Mode 						= 0;
uint32_t 	RTC_Counter 		= 0;
uint8_t 	KEY[2]					= {0, 0}; //KEY[0]-предыдущее нажатие, KEY[1]-кнопка которая нажата
uint8_t 	run							= 1;



void SysTick_Handler(void)
{
	if (delay_count > 0)
	{
		delay_count--;
	}
}


void delay_ms(uint16_t delay_temp)
{
	delay_count = delay_temp;
	while(delay_count--){}
}


int main(void)
{	
//инициализация	
	InitAll();
	FirstBoot();
	GPIO_ResetBits(GPIOC, GPIO_Pin_8);
  GPIO_SetBits(GPIOC, GPIO_Pin_9);
	
	
	while(1)
	{	
		KEY[1] = get_en_key();
		if (run == 1)
		{
			run = UI(KEY);
		}
		
		if (KEY[1] == 0)
		{
			LCD_print(0, 0, 1, "  ");
			KEY[0] = KEY[1];
			GPIO_ResetBits(GPIOC, GPIO_Pin_8);
		}
		else if (KEY[0] != KEY[1])
		{
			run = 1;
			//иначе удаляем текст с экрана и вырубаем светодиод PC8
			LCD_print(0, 0, 1, "  ");
			GPIO_ResetBits(GPIOC, GPIO_Pin_8);
			GPIO_ResetBits(GPIOC, GPIO_Pin_0);
			GPIO_ResetBits(GPIOC, GPIO_Pin_1);
			GPIO_ResetBits(GPIOC, GPIO_Pin_2);
			GPIO_ResetBits(GPIOC, GPIO_Pin_3);
		}
		LCD_Update();	
	}
}
	
