# 02_Winding_machine
*Станок рядной намотки*

---

## Задачи:
- [x] Меню   *//как-то работает, GUI написан, можно лучше*
- [ ] Опрос кнопок, через прерывания   *//сейчас опрашиваются GPIO*
- [ ] Управление шаговыми двигателями, через ШИМ (таймеры)   *//сейчас задержка между шагами - **delayms***
- [ ] Выставка нулевого положения укладчика

---

## Описание
### Микроконтроллер
В основе проекта изначально лежит отладочная плата STM32VLDISCOVERY.
MK - STM32F100RB
![stm32vldiscovery](https://github.com/izhsmoke/02_Winding_machine/assets/151672007/88ae1bfb-2def-4c5c-9891-3339cb098d8f)

### LCD дисплей HX1230
Это полный аналог LCD Nokia 1202

|	PIN	|			HX1230		 | Nokia1202 |
|---|:---:|:---:|
|	1		|			Reset			 |		N/C		 |
|	2		|			CE(CS)		 |		Reset	 |
|	3		|			N/C			   |		CS		 |
|	4		|DIN(SDA or MOSI)|		GND		 |
|	5		|			SCLK(CLK)	 |		MOSI	 |
|	6		|			3V3				 |		SCK	 	 |
|	7		|			LED+			 |		3V3		 |
|	8		|			GND			   |		3V3		 |
|	9		|			-					 |		GND		 |
|	10	|			-					 |		LED-	 |
|	11	|			-			 		 |		LED+	 |
|	12	|			-					 |		N/C		 |

```
//			Конфигурация порта
//используемый порт
#define LCD_port    GPIOB
//используемые выводы
#define LCD_LED_pin    GPIO_Pin_9
#define LCD_SCLK_pin    GPIO_Pin_8
#define LCD_MOSI_pin    GPIO_Pin_7
#define LCD_CS_pin    GPIO_Pin_6
#define LCD_RST_pin    GPIO_Pin_5
```

<img src="https://github.com/izhsmoke/02_Winding_machine/assets/151672007/2043f6d6-39bf-47ed-bc37-30ee69989f0b" alt="drawing" style="width:300px;"/>

### Питания 
- 12В - для питания "силовой" части шаговых двигателей
- 3.3В - для питания логики

### Драйверы шаговых двигателей
Были использованы бюджетные драйверы **A4988**

<img src="https://iarduino.ru/img/upload/f88ad51fdacaed49511871d49cecb77a.png" alt="drawing" style="width:900px;"/>

### Шаговые двигатели
1. Шпиндель
2. Укладчик


### Кнопки
Кнопки подтянуты вверх чарез резистор 10кОм (нашлись только такие)
- Вверх ```[PA1]```
- Вниз ```[PA2]```
- Вправо ```[PA3]```
- Влево ```[PA4]```
- ОК ```[PA5]```
- Концевик нулевого положения укладчика ```[???]```
