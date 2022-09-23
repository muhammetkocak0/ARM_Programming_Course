
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "i2c-lcd.h"
void gpio_for_i2c_cfg()
{
	RCC->AHB1ENR |=(1<<1);
	GPIOB->MODER |= (1<<21)|(1<<23);
	GPIOB->OTYPER |= (1<<10)|(1<<11);
	GPIOB->OSPEEDR |=(1<<20)|(1<<21)|(1<<22)|(1<<23);
	GPIOB->PUPDR |=(1<<20)|(1<<22);
	GPIOB->AFR[1] |=(1<<14)|(1<<10);
}

void i2c_cfg()
{   RCC->APB1ENR |= (1<<22);


	I2C2->CR2 |= 0x0008;
	I2C2->CCR |=0x0028;
	I2C2->TRISE |=0x09;
	I2C2->CR1 |=(1<<0);

	//START GENERATION
//STOP GENERATION

}


void i2c_write(uint8_t adress,uint8_t data)
{

	I2C2->CR1|=(1<<8);
	while(!(I2C2->SR1 & 1<<0));
	I2C2->DR = adress;
	while(!(I2C2->SR1 & 0x0002));
	while(!(I2C2->SR2 & 1<<0));
	while(!(I2C2->SR1 & 1<<7));
	I2C2->DR = data;
	while(!(I2C2->SR1 & 1<<7));
	while(!(I2C2->SR1 & 0x0004));
	I2C2->CR1|=(1<<9);



}













int main(void)
{
	gpio_for_i2c_cfg();
	i2c_cfg();
	lcd_init();
	lcd_sende_string("muh22amed");
  while (1)
  {

  }
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
