#include "steppers.h"
#include "LCD_Nokia1202.h"
#include "main.h"

int length_to_step(float length, uint8_t mode)
{
	if (mode == 0) return (int)(length/0.0025);
	else 					 return (int)(length/0.000695);
}

//Функция намотки
uint8_t Winding_do(float wire_diam, float karkas_diam, float karkas_lenght, uint16_t rounds)
{
	uint8_t progress = 0;
	uint16_t steps = 0;
	uint8_t dir = 0;
	uint8_t rounds_of_lenght = karkas_lenght/wire_diam;
	LCD_print(43,50,1,"/100%");
	//Вращаем нужное количество витков
	for (uint16_t i = 0; i < rounds; i++)
	{
		Motion_stepper(1, 0, STEP_spind, DIR_spind, 4);	//вращаем шпиндель на 1 оборот
		if ((steps < rounds_of_lenght) & (dir == 0))
		{
			Motion_stepper(1, 1, STEP_uklad, DIR_uklad, wire_diam); 	//движение укладчика на толщину проволки
			steps++;
		}
		else
		{
			Motion_stepper(0, 1, STEP_uklad, DIR_uklad, wire_diam); 	//движение укладчика на толщину проволки
			steps--;
			if (steps != 0) dir = 1;
			else dir = 0;
		}
		progress = i / (rounds/100);
		LCD_FillRect(1,60,progress,8,1);
		LCD_write(25,50,1,progress);
		LCD_Update();
	}
	progress = 100;
	LCD_write(25,50,1,progress);
	LCD_Update();
	//LCD_print(25,50,1,"   ГОТОВО   ");
	return 0;
}


void Motion_stepper(uint8_t dir, uint8_t mode, uint8_t pin_step, uint8_t pin_dir, float length)
{
	int step = 0; //шаги
	uint8_t count = 1;
	if (dir == 0){GPIO_ResetBits(GPIOC, pin_dir);}
	else				 {GPIO_SetBits(GPIOC, pin_dir);}
	while (step < length_to_step(length, mode))
	{
		if (count == 0){
			GPIO_ResetBits(GPIOC, pin_step);
			count = 1;
		}
		else{
			GPIO_SetBits(GPIOC, pin_step);
			count = 0;
		}
		step++;
		delay_ms(450); // скорость намотки 400 - максимальная, 1200 - для отладки
	}
}


int Stepper_do(int key, char* STR, int direct, int rounds, int pin_direct, int pin_step)
{
	LCD_print(50, 0, 1, STR);
	LCD_Update();
	GPIO_SetBits(GPIOC, GPIO_Pin_8);
	if (direct == 1)
	{
		GPIO_SetBits(GPIOC, pin_direct);
	}
	else
	{
		GPIO_ResetBits(GPIOC, pin_direct);
	}
	
	return 0;
}

