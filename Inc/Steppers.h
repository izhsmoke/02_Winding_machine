#ifndef __STEPPERS
#define __STEPPERS
#include "stm32f10x.h"

#define DIR_uklad  GPIO_Pin_0 
#define STEP_uklad GPIO_Pin_1 
#define DIR_spind  GPIO_Pin_2 
#define STEP_spind GPIO_Pin_3 

void Motion_stepper(uint8_t dir, uint8_t mode, uint8_t pin_step, uint8_t pin_dir, float length);
int Stepper_do(int key, char* STR, int direct, int rounds, int pin_direct, int pin_step);
int length_to_step(float length, uint8_t mode);
uint8_t Winding_do(float wire_diam, float karkas_diam, float karkas_lenght, uint16_t rounds);


//+=====+===========+=======+======+
//|	PIN	| 	A4988 	| type	| LVL	 |
//+=====+===========+=======+======+
//|	1		|	ENABLE	 	| input |1 or 0|
//|	2		|	MS1			  | input |1 or 0|
//|	3		|	MS2 		  | input |1 or 0|
//|	4		|	MS3       | input |1 or 0|
//|	5		|	nRESET	  | input |1 or 0|
//|	6		|	nSLEEP	  | input |1 or 0|
//|	7		|	STEP  	  | input |1 or 0|
//|	8		|	DIRECTION | input |1 or 0|
//|	9		|	GND		    | power |	GND  |
//|	10	|	VDD	      | power |3...5V|
//|	11	|	1B	      |output |			 |
//|	12	|	1A		    |output |			 |
//|	13	|	2A	      |output |			 |
//|	14	|	2B		    |output |			 |
//|	13	|	GND_motor | power |	GND  |
//|	14	|	V_motor	  | power |8...  |
//+=====+===========+=======+======+


#endif
