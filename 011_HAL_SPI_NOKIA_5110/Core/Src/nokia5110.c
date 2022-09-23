/*
 * nokia5110.c
 *
 *  Created on: 22 Eyl 2022
 *      Author: muham
 */
#include "nokia5110.h"
void Nokia5110_Init(void)
{
	Nokia5110_Reset();

	Nokia5110_Write_Command(0x21);
	Nokia5110_Write_Command(0xB8);
	Nokia5110_Write_Command(0x04);
	Nokia5110_Write_Command(0x14);
	Nokia5110_Write_Command(0x20);
	Nokia5110_Write_Command(0x0C);


}
void Nokia5110_Reset(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
}
void Nokia5110_Write_Data(uint8_t x_Value,uint8_t y_Value)
{

	y_Value = y_Value | 0x40;
	x_Value = x_Value | 0x80;


	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

	HAL_SPI_Transmit(&hspi1, x_Value, 1, 10);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);



	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &y_Value, 1, 10);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
}

void Nokia5110_Write_Command(uint8_t data)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

	HAL_SPI_Transmit(&hspi1, &data, 1, 10);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
}








