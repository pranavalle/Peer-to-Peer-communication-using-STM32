/*
 * RX.c
 *
 *  Created on: Nov 25, 2022
 *      Author: LENOVO PC
 */


#include <stdio.h>
#include <stdint.h>
#include <stm32f407xx.h>
#include <string.h>


#define RS 0x0001 //register select
#define RW 0x0002 //read and write pin
#define EN 0x0004

uint32_t *const pRccRegPortEnable = (uint32_t*)0x40023830; //RCC register port enable pin base address
uint32_t *const pPortDModeReg = (uint32_t*)0x40020C00; //port D mode register base address
uint32_t *const pPortCModeReg = (uint32_t*)0x40020800; //port C mode register base address

uint32_t *const pPortDDataReg = (uint32_t*)0x40020C14; //port D mode data register base address
uint32_t *const pPortCDataReg = (uint32_t*)0x40020814; //port C mode data register base address

//delay
void DelayMs(uint32_t n);

//lcd command
void LCD_CMD(unsigned char cmd);

//lcd data
void LCD_Data(char data);

//lcd init
void LCD_INIT(void);

//init ports
void Ports_INIT(void);

char data[120];

USART_Handle_t USART2_handle;

//configuring USART pin for IR communication
void USART2_Init(void)
{
	USART2_handle.pUSARTx = USART2; 											//assigned a usart pin
	USART2_handle.USART_Config.USART_Baud = USART_STD_BAUD_1200;				//set the baud rate to 1200bps since the input signal is 38 KHz modulation
	USART2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;	//set hardware flow control to none
	USART2_handle.USART_Config.USART_Mode = USART_MODE_TXRX;					//set usart mode to transmit and receive mode
	USART2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;			//number of stop bits is 1
	USART2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;			//since we're transmitting 8bit data, we set the word length as 8bit
	USART2_handle.USART_Config.USART_ParityControl = USART_PARITY_EN_EVEN;
	USART_Init(&USART2_handle);													//initialize the usart
}

//configuring USART and GPIO pins for data from keypad to get transmitted using usart
void USART2_GPIOInit(void)
{
	GPIO_Handle_t USART_GPIOs;

	USART_GPIOs.pGPIOx = GPIOA;													//assigned GPIOA port
	USART_GPIOs.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;					//set GPIO mode to alternate function since it either transmits or receives
	USART_GPIOs.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;				//set the output type to push pull
	USART_GPIOs.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;				//set the pin control to pull up
	USART_GPIOs.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;					//set the pin speed to fast
	USART_GPIOs.GPIO_PinConfig.GPIO_PinAltFunMode = 7;

	//USART2 tx
	USART_GPIOs.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	GPIO_Init(&USART_GPIOs);

	//USART2 rx
	USART_GPIOs.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&USART_GPIOs);
}

int main(void)
{
	char data[1];													//assign a variable of character type and put array  length as 1
	GPIO_PeriClockControl(GPIOA, ENABLE);							//enable gpioA clock
	LCD_INIT();														//initialize the LCD
	DelayMs(100);													//delay
	USART2_Init();													//usart2 initialization for IR communication
	USART2_GPIOInit();												//usart2 and gpio initialization for data transmission from keypad

	USART_PeriClockControl(USART2, ENABLE);							//enable clock to usart

	while(1)
	{
		GPIO_WriteToOutputPin(GPIOD, 15, 1);						//turn LED ON during transmission
		USART_ReceiveData(&USART2_handle, (uint8_t*)data, 1);		//receives the data from the keypad
		LCD_Data((uint8_t)*data);									//directs the data towards the LCD data
		DelayMs(100);												//delay
		GPIO_WriteToOutputPin(GPIOD, 15, 0);						//led off
	}
	return 0;
}


