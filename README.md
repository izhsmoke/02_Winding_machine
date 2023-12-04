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
![stm32vldiscovery](http://wiki.amperka.ru/_media/%D0%BF%D1%80%D0%BE%D0%B4%D1%83%D0%BA%D1%82%D1%8B:stm32-f100-discovery:stm32-f100-discovery_pinout.png)

### LCD дисплей HX1230
Это полный аналог LCD Nokia 1202

<img src="https://i.pinimg.com/originals/91/d9/13/91d913262d0ba1195b196997b4dbf317.jpg" alt="drawing" style="width:500px;"/>


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
