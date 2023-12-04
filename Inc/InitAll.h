#ifndef __Init
#define __Init

#include "stm32f10x.h"

void InitAll(void);
unsigned char RTC_Init(void);
void ADC_Init_(void);
void PWM_Init(void);
void LED_Init(void);
void Stepper_Init(void);
void BUTTON_Init(void);


#endif
