#include "UI.h"
#include "main.h"
#include "Steppers.h"


//параметры намотки
//											 		   |диам.провода| диам.каркаса|ширина каркаса| кол.витков |		
uint8_t winding_value[5][4] = {  {0,3,5,0}  ,  {0,0,5,8}  ,  {0,0,8,5}   , {0,1,5,0}  ,{0,0,0,0}}; 

uint8_t lvl     = 0;
float   symbol  = 4;
uint8_t number  = 0;
uint8_t winding = 1;
uint8_t steps		= 0;

void FirstBoot(void)
{
	//первый запуск дисплея	
		LCD_Clear();
	//надпись НАЗВАНИЕ
		LCD_print(30,20,1,"Станок");
		LCD_print(20,30,1,"намоточный");
		LCD_print(12,45,1,"СНО-01-альфа");
		LCD_Update();
		for (int i = 0; i<500; i++)
		{
			delay_ms(5000);
		}
		LCD_Clear();		
}


int get_en_key()
{
	return GPIOA->IDR & 0x003e; //проверяем состояние PA по маске с 1 по 5 пин 
}


uint8_t UI(uint8_t KEY[])
{
	menu_key(KEY);
	menu_print(KEY);
	return 0;
}
	
//ФУНКЦИЯ ВЫВОДА НА ЭКРАН
void menu_print(uint8_t KEY[])
{
	LCD_Clear();
	switch (lvl)
	{
		//ЭКРАН НАСТРОЙКИ ДИАМЕТРА КАРКАСА
		case 0:
			LCD_print(25,5,1,"Диаметр");
			LCD_print(25,15,1,"провода:");
			LCD_write(25,35,1, winding_value[lvl][0]);
			LCD_print(31,35,1, ",");
			LCD_write(37,35,1, winding_value[lvl][1]);
			LCD_write(43,35,1, winding_value[lvl][2]);
			LCD_write(49,35,1, winding_value[lvl][3]);
			LCD_print(60,35,1,"   ");
			LCD_print(65,35,1,"[мм]");
			LCD_print(60,60,1,"Далее");
			break;
		//ЭКРАН НАСТРОЙКИ ДИАМЕТРА КАРКАСА
		case 1:
			LCD_print(25,5,1,"Диаметр");
			LCD_print(25,15,1,"каркаса:");
			LCD_write(25,35,1, winding_value[lvl][0]);
			LCD_write(31,35,1, winding_value[lvl][1]);
			LCD_write(37,35,1, winding_value[lvl][2]);
			LCD_print(43,35,1, ",");
			LCD_write(49,35,1, winding_value[lvl][3]);
			LCD_print(60,35,1,"   ");
			LCD_print(65,35,1,"[мм]");
			LCD_print(6,60,1,"Назад");
			LCD_print(60,60,1,"Далее");
			break;
		//ЭКРАН НАСТРОЙКИ ШИРИНЫ КАРКАСА
		case 2:
			LCD_print(27,5,1,"Ширина");
			LCD_print(25,15,1,"намотки:");
			LCD_write(25,35,1, winding_value[lvl][0]);
			LCD_write(31,35,1, winding_value[lvl][1]);
			LCD_write(37,35,1, winding_value[lvl][2]);
			LCD_print(43,35,1, ",");
			LCD_write(49,35,1, winding_value[lvl][3]);
			LCD_print(60,35,1,"   ");
			LCD_print(65,35,1,"[мм]");
			LCD_print(6,60,1,"Назад");
			LCD_print(60,60,1,"Далее");
			break;
		//ЭКРАН НАСТРОЙКИ КОЛ-ВА ВИТКОВ
		case 3:
			LCD_print(20,5,1,"Количество");
			LCD_print(30,15,1,"витков:");
			LCD_write(25,35,1, winding_value[lvl][0]);
			LCD_write(31,35,1, winding_value[lvl][1]);
			LCD_write(37,35,1, winding_value[lvl][2]);
			LCD_write(43,35,1, winding_value[lvl][3]);
			LCD_print(60,35,1,"   ");
			LCD_print(65,35,1,"[шт]");
			LCD_print(6,60,1,"Назад");
			LCD_print(60,60,1,"СТАРТ");
			break;
		//ЭКРАН НАЧАЛЬНОЙ ВЫСТАВКИ
		case 4:
			LCD_print(20,5,1,"Начальная");
			LCD_print(20,15,1,"выставка:");
			break;
		
		//ЭКРАН ПРОГРЕССА
		case 5:
			LCD_Clear();
			LCD_print(25,5,1,"ПРОГРЕСС");
			LCD_DrawRect(1,60,94,8,1);
			float wire_diam 	= (float)(winding_value[0][0] * 1000  + winding_value[0][1] * 100  + winding_value[0][2] * 10	+ winding_value[0][3])/1000;
			float karkas_diam = (float)(winding_value[1][0] * 1000  + winding_value[1][1] * 100  + winding_value[1][2] * 10	+ winding_value[1][3])/10;
			float karkas_len 	= (float)(winding_value[2][0] * 1000  + winding_value[2][1] * 100  + winding_value[2][2] * 10	+ winding_value[2][3])/10;
			uint16_t rounds 	= 			  winding_value[3][0] * 1000  + winding_value[3][1] * 100  + winding_value[3][2] * 10	+ winding_value[3][3];
			if (winding == 1)
			{
				winding = Winding_do(wire_diam, karkas_diam, karkas_len, rounds);
			}
			break;
	}
	switch (KEY[1])
	{
		case KEY_up:
			LCD_print(0,0,1,"^ ");
			break;
		case KEY_down:
			LCD_print(0,0,1,"v ");
			break;
		case KEY_left:
			LCD_print(0,0,1,"< ");
			break;
		case KEY_right:
			LCD_print(0,0,1,"> ");
			break;
		case KEY_ok:
			LCD_print(0,0,1,"ОК");
			break;
	}
	if (lvl != 4 & lvl != 5)
	{
		LCD_print(20,27,1,"     ");				//Очистили отметку "^"
		LCD_print(20,42,1,"     ");				//Очистили отметку "v"
	}
	
	
	//Перемещение курсора вправо/влево </>	
	if (lvl == 0)
	{
		if (symbol == 0)
		{
			LCD_print(sym_0,27,1,"^");
			LCD_print(sym_0,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 1)
		{
			LCD_print(sym_2,27,1,"^");
			LCD_print(sym_2,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 2)
		{
			LCD_print(sym_3,27,1,"^");
			LCD_print(sym_3,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 3)
		{
			LCD_print(sym_4,27,1,"^");
			LCD_print(sym_4,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 4)
		{
			LCD_print(54,60,1,"<Далее>");
		}
		else if (lvl != 4 & lvl != 5)
		{
			if (symbol == -1)
			{
				LCD_print(0,60,1,"<Назад>");
				LCD_print(54,60,1," Далее ");
			}
		}
	}
	else if (lvl == 1 | lvl == 2)
	{
		if (symbol == 0)
		{
			LCD_print(sym_0,27,1,"^");
			LCD_print(sym_0,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 1)
		{
			LCD_print(sym_1,27,1,"^");
			LCD_print(sym_1,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 2)
		{
			LCD_print(sym_2,27,1,"^");
			LCD_print(sym_2,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 3)
		{
			LCD_print(sym_4,27,1,"^");
			LCD_print(sym_4,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 4)
		{
			LCD_print(54,60,1,"<Далее>");
		}
	}
	else if (lvl == 3)
	{
		if (symbol == 0)
		{
			LCD_print(sym_0,27,1,"^");
			LCD_print(sym_0,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 1)
		{
			LCD_print(sym_1,27,1,"^");
			LCD_print(sym_1,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 2)
		{
			LCD_print(sym_2,27,1,"^");
			LCD_print(sym_2,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 3)
		{
			LCD_print(sym_3,27,1,"^");
			LCD_print(sym_3,42,1,"v");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 4)
		{
			LCD_print(54,60,1,"<Далее>");
		}
	}
	//Уровень НАЧАЛЬНОЙ ВЫСТАВКИ
	else if (lvl == 4)
	{
		if (symbol == -1)
		{
			LCD_print(sym_3,27,1,"^");
			LCD_print(sym_3,42,1,"v");
			LCD_print(sym_1,34,1,"<");
			LCD_print(sym_5,34,1,">");
			LCD_print(0,60,1,"<Назад>");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 3)
		{
			LCD_print(sym_3,27,1,"^");
			LCD_print(sym_3,42,1,"v");
			LCD_print(sym_1,34,1,"<");
			LCD_print(sym_5,34,1,">");
			LCD_print(0,60,1," Назад ");
			LCD_print(54,60,1," Далее ");
			symbol = 0;
		}
		else if (symbol == 0)
		{
			LCD_print(sym_3,27,1,"^");
			LCD_print(sym_3,42,1,"v");
			LCD_print(sym_1,34,1,"<");
			LCD_print(sym_5,34,1,">");
			LCD_print(0,60,1," Назад ");
			LCD_print(54,60,1," Далее ");
		}
		else if (symbol == 1)
		{
			symbol = 4;
			LCD_print(sym_3,27,1,"^");
			LCD_print(sym_3,42,1,"v");
			LCD_print(sym_1,34,1,"<");
			LCD_print(sym_5,34,1,">");
			LCD_print(0,60,1," Назад ");
			LCD_print(54,60,1,"<Далее>");
		}
		else if (symbol == 4)
		{
			LCD_print(sym_3,27,1,"^");
			LCD_print(sym_3,42,1,"v");
			LCD_print(sym_1,34,1,"<");
			LCD_print(sym_5,34,1,">");
			LCD_print(0,60,1," Назад ");
			LCD_print(54,60,1,"<Далее>");
		}
	}
	
	else if (symbol == 4 & lvl == 3)
	{
		LCD_print(54,60,1,"<СТАРТ>");
		LCD_print(0,60,1," Назад ");
	}
	
	else if (symbol == 4 & lvl != 5)
	{
		LCD_print(54,60,1,"<Далее>");
		LCD_print(0,60,1," Назад ");
	}
}


void menu_key(uint8_t KEY[])
{
	KEY[0] = KEY[1];
	if (symbol != -1)
	{
		uint8_t sym = (uint8_t) symbol;
		switch (KEY[1])
		{
			case KEY_up:
				LCD_print(0,0,1,"^ ");
				if (lvl == 4){Motion_stepper(0, 0, STEP_spind, DIR_spind, 4);}//вращаем шпиндель по часовой стрелке
				if ((winding_value[lvl][sym]) < 9 & lvl != 4)
				{
					winding_value[lvl][sym]++;
					number = winding_value[lvl][sym];
				}
				break;
			case KEY_down:
				LCD_print(0,0,1,"v ");
				if (lvl == 4){Motion_stepper(1, 0, STEP_spind, DIR_spind, 4);}//вращаем шпиндель по часовой стрелке
				if ((winding_value[lvl][sym])  > 0 & lvl != 4)
				{
					winding_value[lvl][sym]--;
					number = winding_value[lvl][sym];
				}
				break;
			case KEY_left:
				LCD_print(0,0,1,"< ");
				if (lvl == 4){Motion_stepper(0, 1, STEP_uklad, DIR_uklad, 1);}//передвигаем укладчик влево
				if (symbol > -1 & lvl != 4)
				{
					symbol--;
				}
				break;
			case KEY_right:
				LCD_print(0,0,1,"> ");
				if (lvl == 4){Motion_stepper(1, 1, STEP_uklad, DIR_uklad, 1);}//передвигаем укладчик вправо
				if (symbol < 4 & lvl != 4){symbol++;}
				break;
			case KEY_ok:
				if (symbol == 4)
				{
					if (lvl < 5)
					{
						lvl++;
						symbol = 4;
					}
				}
				LCD_print(0,0,1,"ОК");
				break;
		}
	}
	else
	{
		switch (KEY[1])
		{
			case KEY_ok:
				if (symbol == -1 & lvl != 0)
				{
					lvl--;
					symbol = 0;
				}
				LCD_print(0,0,1,"ОК");
				break;
			case KEY_right:
				LCD_print(0,0,1,"> ");
				if (symbol <= 4)
				{
					symbol++;
				}
				break;
			case KEY_left:
				if (lvl == 4){Motion_stepper(0, 1, STEP_uklad, DIR_uklad,10);}//передвигаем укладчик влево
				break;
		}
	}
	GPIO_SetBits(GPIOC, GPIO_Pin_8);	//Зажгли синий светодиод
}


	
		
		
		
		
/*
switch(KEY)
{
	case 2: //0b00000010 - пин PA1
		//run =  1;
		break;
	case 4:	//0b00000100 - пин PA2
		//run = Stepper_do(4, "ВПЕРЕД", 0, 1, GPIO_Pin_0, GPIO_Pin_1); 
		break;
	case 8: //0b00001000 - пин PA3
		//run = Stepper_do(8, "ВЛЕВО", 1, 1, GPIO_Pin_2, GPIO_Pin_3); 
		break;
	case 16: //0b00010000 - пин PA4
		//run = Stepper_do(16, "ВПРАВО", 0, 1, GPIO_Pin_2, GPIO_Pin_3);
		break;
	case 32: //0b10000000 - пин PA5
		LCD_print(50, 0, 1, "ОК");
		LCD_Update();
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
		break;	
}
*/
	

/*void printBatteryLevel(void)
{
	char buffer[6];
	sprintf(buffer,"%d", ADC1->JDR1);
	//LCD_print(0,0,1,buffer);
	LCD_FillRect(86,52,8,14,1);
	LCD_FillRect(86,52,8,((ADC1->JDR1)-1400)/32,0); 					//выводим первое измерение батареи
}*/


/*
void printTime(RTC_TimeTypeDef *rtc_time) 
{
	char buffer[80] = {'\0'};
	sprintf(buffer,"%02d:%02d:%02d", rtc_time->RTC_Hours, rtc_time->RTC_Minutes, rtc_time->RTC_Seconds);
	LCD_print(45,61,1,buffer);		
	LCD_Update();
}
*/



