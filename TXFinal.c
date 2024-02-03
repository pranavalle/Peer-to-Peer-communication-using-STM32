/*
 * TXFinal.c
 *
 *  Created on: Dec 5, 2022
 *      Author: LENOVO PC
 */
/*
 * TX_FINAL.c
 *
 *  Created on: Nov 29, 2022
 *      Author: LENOVO PC
 */

#include <stdio.h>
#include <string.h>
#include <stm32f407xx.h>
#include <STM32F407_LCD_DRIVER.h>

#define BUTTON_TRIGGERED 1															//defining a function for setting macro 1

USART_Handle_t USART2_handle;

void USART2_Init(void)																//initialise the USART2 port
{
	USART2_handle.pUSARTx = USART2;													//assign usart 2 pin
	USART2_handle.USART_Config.USART_Baud = USART_STD_BAUD_1200;					//set baud rate to 1200bps for better data flow
	USART2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;		//set hardware control flow to none
	USART2_handle.USART_Config.USART_Mode = USART_MODE_TXRX;						//set usart mode to transmit and receive
	USART2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;				//number of stop bits is 1
	USART2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;				//use 8bit word length
	USART2_handle.USART_Config.USART_ParityControl = USART_PARITY_EN_EVEN;
	USART_Init(&USART2_handle);														//initialise the handle
}

void USART2_GPIOInit(void)															//initialise the usart2 and gpio interface
{
	GPIO_PeriClockControl(GPIOA, ENABLE);											//enable the clock control
	GPIO_Handle_t USART_GPIOs;														//give the usart handle a name
	USART_GPIOs.pGPIOx = GPIOA;														//assign the GPIO port to GPIOA
	USART_GPIOs.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;						//Set the gpio mode to alternate function since it either does transmission or receiving
	USART_GPIOs.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;					//set the output type as push pull
	USART_GPIOs.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;					//set pin control to pull up
	USART_GPIOs.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;						//set output speed to fast
	USART_GPIOs.GPIO_PinConfig.GPIO_PinAltFunMode = 7;

	//USART2 tx
	USART_GPIOs.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	GPIO_Init(&USART_GPIOs);

	//USART2 rx
	USART_GPIOs.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&USART_GPIOs);
}

void LED(void)																		//initialising the LED during transmission
{
	GPIO_PeriClockControl(GPIOD, ENABLE);											//enable clock to GPIOD port
	GPIO_Handle_t GPIO_led;															//give a name to the handle
	//led
	GPIO_led.pGPIOx = GPIOD;
	GPIO_led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;						//enable PD12 LED
	GPIO_led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


	GPIO_Init(&GPIO_led);
}

void KeyPad(void)																	//initialise keypad
{
	GPIO_PeriClockControl(GPIOD, ENABLE);											//enable clock in GPIOD

	//row configuration
	GPIO_Handle_t ROW1; //pd0

	ROW1.pGPIOx = GPIOD;
	ROW1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	ROW1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;								//set pin mode as output
	ROW1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	ROW1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	ROW1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Handle_t ROW2;  //pd1

	ROW2.pGPIOx = GPIOD;
	ROW2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
	ROW2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	ROW2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	ROW2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	ROW2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Handle_t ROW3;  //pd2

	ROW3.pGPIOx = GPIOD;
	ROW3.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	ROW3.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	ROW3.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	ROW3.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	ROW3.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Handle_t ROW4;  //pd3

	ROW4.pGPIOx = GPIOD;
	ROW4.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	ROW4.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	ROW4.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	ROW4.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	ROW4.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	//column configuration
	GPIO_Handle_t COL1;  //pd8

	COL1.pGPIOx = GPIOD;
	COL1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	COL1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;							//pin mode set to input
	COL1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	COL1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	COL1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;						//pin control set to pull up

	GPIO_Handle_t COL2;  //pd9

	COL2.pGPIOx = GPIOD;
	COL2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	COL2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	COL2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	COL2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	COL2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_Handle_t COL3;  //pd10

	COL3.pGPIOx = GPIOD;
	COL3.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_10;
	COL3.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	COL3.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	COL3.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	COL3.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_Handle_t COL4;  //pd11

	COL4.pGPIOx = GPIOD;
	COL4.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_11;
	COL4.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	COL4.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	COL4.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	COL4.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;



	GPIO_Init(&ROW1);
	GPIO_Init(&ROW2);
	GPIO_Init(&ROW3);
	GPIO_Init(&ROW4);
	GPIO_Init(&COL1);
	GPIO_Init(&COL2);
	GPIO_Init(&COL3);
	GPIO_Init(&COL4);
}

int main(void)
{
	//call all the functions defined earlier
	USART2_Init();
	USART2_GPIOInit();
	KeyPad();
	LED();
	USART_PeriClockControl(USART2, ENABLE);

	//given data
	uint8_t data[1];

	while(1)
	{
		//set all the rows to high and then reset pin PD0 as R0 is set to 0
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_0, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_1, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_2, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_3, GPIO_PIN_SET);

		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_0, GPIO_PIN_RESET);

		if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_8)) == BUTTON_TRIGGERED)) 			//check whether ther is input from PD8
		{
			DelayMs(100);
			GPIO_WriteToOutputPin(GPIOD, 12, 1);											//turn on the led during transmission
			data[0] = '1';																	//give data value
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);							//send the data to receiver
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);											//turn the led off after transmission

		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_9)) == BUTTON_TRIGGERED))		//PD9
		{
			DelayMs(100);
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			data[0] = '2';
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);

		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_10)) == BUTTON_TRIGGERED))		//PD10
		{
			DelayMs(100);
			data[0] = '3';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);

		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_11)) == BUTTON_TRIGGERED))		//PD11
		{
			DelayMs(100);
			data[0] = 'A';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}

		//Set all the rows and reset R1 (pin PD1)
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_0, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_1, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_2, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_3, GPIO_PIN_SET);

		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_1, GPIO_PIN_RESET);

		if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_8)) == BUTTON_TRIGGERED))  			//check whether input from PD8
		{
			DelayMs(100);
			data[0] = '4';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_9)) == BUTTON_TRIGGERED))		//PD9
		{
			DelayMs(100);
			data[0] = '5';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_10)) == BUTTON_TRIGGERED))		//PD10
		{
			DelayMs(100);
			data[0] = '6';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_11)) == BUTTON_TRIGGERED))		//PD11
		{
			DelayMs(100);
			data[0] = 'B';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}


		//set the rows to high and then reset R2 to low (pin PD2)
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_0, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_1, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_2, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_3, GPIO_PIN_SET);

		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_2, GPIO_PIN_RESET);

		if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_8)) == BUTTON_TRIGGERED))			//PD8
		{
			DelayMs(100);
			data[0] = '7';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_9)) == BUTTON_TRIGGERED))		//PD9
		{
			DelayMs(100);
			data[0] = '8';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_10)) == BUTTON_TRIGGERED))		//PD10
		{
			DelayMs(100);
			data[0] = '9';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_11)) == BUTTON_TRIGGERED))		//PD11
		{
			DelayMs(100);
			data[0] = 'C';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}

		//set all the rows to high, Reset R4 pin PD3
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_0, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_1, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_2, GPIO_PIN_SET);
		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_3, GPIO_PIN_SET);

		GPIO_WriteToOutputPin(GPIOD, GPIO_PIN_NO_3, GPIO_PIN_RESET);

		if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_8)) == BUTTON_TRIGGERED))		//PD8
		{
			DelayMs(100);
			data[0] = '*';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_9)) == BUTTON_TRIGGERED))	//PD9
		{
			DelayMs(100);
			data[0] = '0';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_10)) == BUTTON_TRIGGERED))	//PD10
		{
			DelayMs(100);
			data[0] = '#';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}
		else if(!((GPIO_ReadFromInputPin(GPIOD, GPIO_PIN_NO_11)) == BUTTON_TRIGGERED))	//PD11
		{
			DelayMs(100);
			data[0] = 'D';
			GPIO_WriteToOutputPin(GPIOD, 12, 1);
			for(int z = 0; z < 1; z++)
			{
				//data[0] = data[z];
				USART_SendData(&USART2_handle, (uint8_t*)data, 1);
			}
			GPIO_WriteToOutputPin(GPIOD, 12, 0);
		}
	}
}


