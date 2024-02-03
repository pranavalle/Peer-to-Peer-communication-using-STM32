/*
 * STM32F407_LCD_DRIVER.h
 *
 *  Created on: Nov 19, 2022
 *      Author: LENOVO PC
 */

#ifndef INC_STM32F407_LCD_DRIVER_H_
#define INC_STM32F407_LCD_DRIVER_H_

#include <stdint.h>
#include <stm32f407xx.h>

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

//char to binary
void Character_To_Binary(char data);


#endif /* INC_STM32F407_LCD_DRIVER_H_ */
