/*
 * BMP180_HAL.h
 *
 *  Created on: 18 Eyl 2022
 *      Author: muhammed kocak
 */

#ifndef SRC_BMP180_HAL_H_
#define SRC_BMP180_HAL_H_

#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c2;

#define BMP180_READ_ADDRESS 0xEF
#define BMP180_WRITE_ADDRESS 0xEE

void BMP180_Init();

void BMP180_Calibrate();
#endif /* SRC_BMP180_HAL_H_ */
