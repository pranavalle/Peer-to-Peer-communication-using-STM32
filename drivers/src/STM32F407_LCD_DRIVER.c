  /*
 * STM32F407_LCD_Driver.c
 *
 *  Created on: Nov 19, 2022
 *      Author: LENOVO PC
 */

#include "STM32F407_LCD_DRIVER.h"
#include <stdint.h>

//delay function
void DelayMs(uint32_t n)
{
	uint32_t i;
	for(; n>0; n--)
		for(i=0; i<3195; i++);
}


//lcd data function
void LCD_Data(char data)
{
	GPIO_WriteToOutputPin(GPIOC, 0, 1);  //RS set to 1 -> send data input
	GPIO_WriteToOutputPin(GPIOC, 1, 0);	 //Read/Write -> Read is set to 1, Write is set to 0
	Character_To_Binary(data); 			 //character to ascii value conversion
	GPIO_WriteToOutputPin(GPIOC, 2, 1);	 //enable pin high
	DelayMs(10);						 //delay
	GPIO_WriteToOutputPin(GPIOC, 2, 0);	 //enable pin low
	DelayMs(20);						 //delay
}

//lcd initialisation
void LCD_INIT()
{
	Ports_INIT();	//initialisation of ports
	LCD_CMD(0x1);	//clear display
	LCD_CMD(0x38);	//mode 2
	LCD_CMD(0xF);	//cursor blink
	LCD_CMD(0x80);	//cursor to start/home
}

//ports initialisation
void Ports_INIT()
{
	//Port D and Port C RCC clock enable
	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_PeriClockControl(GPIOC, ENABLE);

	//DB0 to DB7 Data Ports
	GPIO_Handle_t GPIOPD0;
	GPIOPD0.pGPIOx = GPIOD;
	GPIOPD0.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOPD0.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPD0.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPD0.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOPD0.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIO_Handle_t GPIOPD1;
	GPIOPD1.pGPIOx = GPIOD;
	GPIOPD1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GPIOPD1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPD1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPD1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOPD1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIO_Handle_t GPIOPD2;
	GPIOPD2.pGPIOx = GPIOD;
	GPIOPD2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	GPIOPD2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPD2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPD2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOPD2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIO_Handle_t GPIOPD3;
	GPIOPD3.pGPIOx = GPIOD;
	GPIOPD3.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIOPD3.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPD3.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPD3.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOPD3.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIO_Handle_t GPIOPD4;
	GPIOPD4.pGPIOx = GPIOD;
	GPIOPD4.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIOPD4.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPD4.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPD4.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOPD4.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIO_Handle_t GPIOPD5;
	GPIOPD5.pGPIOx = GPIOD;
	GPIOPD5.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIOPD5.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPD5.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPD5.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOPD5.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIO_Handle_t GPIOPD6;
	GPIOPD6.pGPIOx = GPIOD;
	GPIOPD6.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIOPD6.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPD6.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPD6.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOPD6.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIO_Handle_t GPIOPD7;
	GPIOPD7.pGPIOx = GPIOD;
	GPIOPD7.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIOPD7.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPD7.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPD7.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOPD7.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;


	//Ports for Read/Write, Register Select, Enable
	GPIO_Handle_t GPIOPC0;
	GPIOPC0.pGPIOx = GPIOC;
	GPIOPC0.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOPC0.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPC0.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPC0.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOPC0.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIO_Handle_t GPIOPC1;
	GPIOPC1.pGPIOx = GPIOC;
	GPIOPC1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	GPIOPC1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPC1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPC1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOPC1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIO_Handle_t GPIOPC2;
	GPIOPC2.pGPIOx = GPIOC;
	GPIOPC2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	GPIOPC2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOPC2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOPC2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOPC2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;

	GPIO_Init(&GPIOPD0);
	GPIO_Init(&GPIOPD1);
	GPIO_Init(&GPIOPD2);
	GPIO_Init(&GPIOPD3);
	GPIO_Init(&GPIOPD4);
	GPIO_Init(&GPIOPD5);
	GPIO_Init(&GPIOPD6);
	GPIO_Init(&GPIOPD7);

	GPIO_Init(&GPIOPC0);
	GPIO_Init(&GPIOPC1);
	GPIO_Init(&GPIOPC2);
}

void LCD_CMD(unsigned char data)
{
	//Command Register RS = 0
	GPIO_WriteToOutputPin(GPIOC, 0, 0);

	//Clear screen
	if(data == 0x1)
	{
		GPIO_WriteToOutputPin(GPIOD, 0, 1);
		GPIO_WriteToOutputPin(GPIOD, 1, 0);
		GPIO_WriteToOutputPin(GPIOD, 2, 0);
		GPIO_WriteToOutputPin(GPIOD, 3, 0);
		GPIO_WriteToOutputPin(GPIOD, 4, 0);
		GPIO_WriteToOutputPin(GPIOD, 5, 0);
		GPIO_WriteToOutputPin(GPIOD, 6, 0);
		GPIO_WriteToOutputPin(GPIOD, 7, 0);
	}

	//Cursor returns back
	if(data == 0x2)
	{
		GPIO_WriteToOutputPin(GPIOD, 0, 0);
		GPIO_WriteToOutputPin(GPIOD, 1, 1);
		GPIO_WriteToOutputPin(GPIOD, 2, 0);
		GPIO_WriteToOutputPin(GPIOD, 3, 0);
		GPIO_WriteToOutputPin(GPIOD, 4, 0);
		GPIO_WriteToOutputPin(GPIOD, 5, 0);
		GPIO_WriteToOutputPin(GPIOD, 6, 0);
		GPIO_WriteToOutputPin(GPIOD, 7, 0);
	}

	//Cursor shift to right
	if(data == 0x6)
	{
		GPIO_WriteToOutputPin(GPIOD, 0, 0);
		GPIO_WriteToOutputPin(GPIOD, 1, 1);
		GPIO_WriteToOutputPin(GPIOD, 2, 1);
		GPIO_WriteToOutputPin(GPIOD, 3, 0);
		GPIO_WriteToOutputPin(GPIOD, 4, 0);
		GPIO_WriteToOutputPin(GPIOD, 5, 0);
		GPIO_WriteToOutputPin(GPIOD, 6, 0);
		GPIO_WriteToOutputPin(GPIOD, 7, 0);

	}

	//Cursor Blinking
	if(data == 0xF)
	{
		GPIO_WriteToOutputPin(GPIOD, 0, 1);
		GPIO_WriteToOutputPin(GPIOD, 1, 1);
		GPIO_WriteToOutputPin(GPIOD, 2, 1);
		GPIO_WriteToOutputPin(GPIOD, 3, 1);
		GPIO_WriteToOutputPin(GPIOD, 4, 0);
		GPIO_WriteToOutputPin(GPIOD, 5, 0);
		GPIO_WriteToOutputPin(GPIOD, 6, 0);
		GPIO_WriteToOutputPin(GPIOD, 7, 0);
	}

	//Shift cursor to beginning of first line
	if(data == 0x80)
	{
		GPIO_WriteToOutputPin(GPIOD, 7, 1);
		GPIO_WriteToOutputPin(GPIOD, 6, 0);
		GPIO_WriteToOutputPin(GPIOD, 5, 0);
		GPIO_WriteToOutputPin(GPIOD, 4, 0);
		GPIO_WriteToOutputPin(GPIOD, 3, 0);
		GPIO_WriteToOutputPin(GPIOD, 2, 0);
		GPIO_WriteToOutputPin(GPIOD, 1, 0);
		GPIO_WriteToOutputPin(GPIOD, 0, 0);
	}

	//Shift cursor to beginning of second line
	if(data == 0xC0)
	{
		GPIO_WriteToOutputPin(GPIOD, 7, 1);
		GPIO_WriteToOutputPin(GPIOD, 6, 1);
		GPIO_WriteToOutputPin(GPIOD, 5, 0);
		GPIO_WriteToOutputPin(GPIOD, 4, 0);
		GPIO_WriteToOutputPin(GPIOD, 3, 0);
		GPIO_WriteToOutputPin(GPIOD, 2, 0);
		GPIO_WriteToOutputPin(GPIOD, 1, 0);
		GPIO_WriteToOutputPin(GPIOD, 0, 0);
	}

	//2 lines and 5*7 Characters 8bit data
	if(data == 0x38)
	{
		GPIO_WriteToOutputPin(GPIOD, 7, 0);
		GPIO_WriteToOutputPin(GPIOD, 6, 0);
		GPIO_WriteToOutputPin(GPIOD, 5, 1);
		GPIO_WriteToOutputPin(GPIOD, 4, 1);
		GPIO_WriteToOutputPin(GPIOD, 3, 1);
		GPIO_WriteToOutputPin(GPIOD, 2, 0);
		GPIO_WriteToOutputPin(GPIOD, 1, 0);
		GPIO_WriteToOutputPin(GPIOD, 0, 0);
	}

	//2 lines and 5*7 Characters 4bit data
	if(data == 0x28)
	{
		GPIO_WriteToOutputPin(GPIOD, 7, 0);
		GPIO_WriteToOutputPin(GPIOD, 6, 0);
		GPIO_WriteToOutputPin(GPIOD, 5, 1);
		GPIO_WriteToOutputPin(GPIOD, 4, 0);
		GPIO_WriteToOutputPin(GPIOD, 3, 1);
		GPIO_WriteToOutputPin(GPIOD, 2, 0);
		GPIO_WriteToOutputPin(GPIOD, 1, 0);
		GPIO_WriteToOutputPin(GPIOD, 0, 0);
	}

	//cmd initialising
	if(data == 0x30)
	{
		GPIO_WriteToOutputPin(GPIOD, 7, 0);
		GPIO_WriteToOutputPin(GPIOD, 6, 0);
		GPIO_WriteToOutputPin(GPIOD, 5, 1);
		GPIO_WriteToOutputPin(GPIOD, 4, 1);
		GPIO_WriteToOutputPin(GPIOD, 3, 0);
		GPIO_WriteToOutputPin(GPIOD, 2, 0);
		GPIO_WriteToOutputPin(GPIOD, 1, 0);
		GPIO_WriteToOutputPin(GPIOD, 0, 0);
	}

	//Enable pin set
	GPIO_WriteToOutputPin(GPIOC, 2, 1);

	DelayMs(10);

	//Enable pin reset
	GPIO_WriteToOutputPin(GPIOC, 2, 0);

	DelayMs(20);
}

//Character to Binary
void Character_To_Binary(char data)
{
	int binary;
	char ch = data;
	for(uint32_t i=0; i<8; i++)
	{
		binary = ((ch << i) & 0x80) ? 1 : 0;
		GPIO_WriteToOutputPin(GPIOD, (7-i), binary);
		binary = 0;
	}
}
