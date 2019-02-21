/*
 * lcd.h
 *
 *  Created on: 21 de fev de 2019
 *      Author: Ariel
 */

#include "stm32f1xx_hal.h"

#ifndef LCD_H_
#define LCD_H_

//#define LCD_8_BITS

#define LCD_PIN_E		GPIO_PIN_0
#define LCD_GPIO_E		GPIOA

#define LCD_PIN_RS		GPIO_PIN_1
#define LCD_GPIO_RS		GPIOA

#define LCD_PIN_D7		GPIO_PIN_9
#define LCD_GPIO_D7		GPIOA

#define LCD_PIN_D6		GPIO_PIN_8
#define LCD_GPIO_D6		GPIOA

#define LCD_PIN_D5		GPIO_PIN_7
#define LCD_GPIO_D5		GPIOA

#define LCD_PIN_D4		GPIO_PIN_6
#define LCD_GPIO_D4		GPIOA

#ifdef LCD_8_BITS

#define LCD_PIN_D3		GPIO_PIN_5
#define LCD_GPIO_D3		GPIOA

#define LCD_PIN_D2		GPIO_PIN_4
#define LCD_GPIO_D2		GPIOA

#define LCD_PIN_D1		GPIO_PIN_3
#define LCD_GPIO_D1		GPIOA

#define LCD_PIN_D0		GPIO_PIN_2
#define LCD_GPIO_D0		GPIOA

#endif

void lcd_send_command(uint32_t cmd);
void lcd_init(void);
void lcd_write(const char *txt);

#endif /* LCD_H_ */
