/*
 * LCD1.c
 *
 *  Created on: Nov 25, 2022
 *      Author: LENOVO PC
 */



#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f407xx.h"

int main(void)
{
	LCD_INIT();
	char str[] = "HELLO PROFESSOR!";
	while(1)
	{
		for(uint32_t i = 0; i<strlen(str);i++)
		{
			LCD_Data(str[i]);
		}
		DelayMs(1000);//Delay for 1 sec
		LCD_CMD(0x1);//Clears the LCD Display
		DelayMs(500);//Delay for 0.5 sec
	}

}
