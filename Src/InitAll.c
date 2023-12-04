#include "InitAll.h"
#include "stm32f10x.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_gpio.h"
#include "system_stm32f10x.h"
#include "LCD_Nokia1202.h"

void InitAll(void)
{		
	//инициализация тайминга
		RCC_DeInit(); //	сброс настроек тактового генератора
		RCC_HSICmd(DISABLE); //	выключение внутреннего RC HSI 8МГц генератора
		RCC_HSEConfig(RCC_HSE_ON); //	включение внешнего тактового генератора
		RCC_PREDIV1Config(RCC_PREDIV1_Source_HSE, RCC_PREDIV1_Div1);//	Предделитель PREDIV1: HSE перед множителем PLLMUL
		RCC_PLLConfig(RCC_PLLSource_PREDIV1 ,RCC_PLLMul_3); //	тактирование от HSE с PREDIV1 8/1*3 = 24МГц
		RCC_PLLCmd(ENABLE); //	Включаем PLL
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //	На системную шину подаем тактирование с множителя PLLMUL
	
	//инициализируем встроенные светодиоды
		LED_Init();
	
	//инициализация дисплея
		BUTTON_Init();
	
	//инициализация дисплея
		LCD_Init();
	
	//инициализация шаговых двигателей
		Stepper_Init();
	
	//инициализация PWM
		//PWM_Init();
}



void ADC_Init_(void)
{
	//Порт A настраивать смысла нет, все его ноги по умолчанию входы что нам и нужно
  RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC1EN, ENABLE); //Включаем тактирование АЦП
}


void LED_Init()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef gpio;
  GPIO_StructInit(&gpio);
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  gpio.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &gpio);
}


void Stepper_Init()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef gpio;
  GPIO_StructInit(&gpio);
  gpio.GPIO_Mode = GPIO_Mode_Out_PP;
  gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  gpio.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &gpio);
}


void BUTTON_Init()
{
  RCC->APB2ENR 	|= RCC_APB2ENR_IOPAEN;
  /* Всё то же, что и со светодиодами, только конфигурируем
   * на вход без подтяжки (GPIO_Mode_IN_FLOATING).
   */
  GPIO_InitTypeDef gpio;
  GPIO_StructInit(&gpio);
  gpio.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
  gpio.GPIO_Pin 	= GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  gpio.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &gpio);
}


void PWM_Init(void)
{
	//Включаем Таймер 2
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//Включем порт А
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
		
	GPIO_InitTypeDef PORT;
	// Настроим ноги со светодиодами на выход
  PORT.GPIO_Pin = GPIO_Pin_2;
  //Будем использовать альтернативный режим а не обычный GPIO
  PORT.GPIO_Mode = GPIO_Mode_AF_PP;
  PORT.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &PORT);
  //Разрешаем таймеру использовать ноги PA2 для ШИМа
  TIM2->CCER |= TIM_CCER_CC3E;
	// Задаем инверсный ШИМ.
  TIM2->CCMR2|=(TIM_CCMR2_OC3M_0 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2);
	//Запускаем таймер!
  TIM2->CR1 |= TIM_CR1_CEN;
	TIM2->CCR3=0xF000; //скважность 50%
}
