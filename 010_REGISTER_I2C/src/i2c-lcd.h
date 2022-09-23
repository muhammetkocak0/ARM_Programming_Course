
/*
 * i2c-lcd.h
 *
 *  Created on: 26 Eyl 2019
 *      Author: ATSON
 */
#include "stm32f4xx.h"

#ifndef I2C_LCD_H_
#define I2C_LCD_H_

void lcd_init(void);				// initialize
void lcd_send_cmd(char cmd);		// send command to the
void lcd_send_data(char data);		// send data to the
void lcd_sende_string(char *str);	// send string to the

#endif /* I2C_LCD_H_ */
