
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void gpio_ayarlari()
{
	RCC->AHB1ENR |=(1<<0);

	GPIOA->MODER |= (1<<0) |(1<<1);
	GPIOA->OSPEEDR |= (1<<0) |(1<<1);


}
void adc_ayarlari()
{
	RCC->APB2ENR |= (1<<9);
	ADC2->CR1 |= (1<<25);
	ADC2->CR2 |=(1<<0);


	ADC2->CR2 &=  ~(1<<11);

	ADC2->SMPR2 |=(1<<0) |(1<<1);

	ADC->CCR |= (1<<16);


	   //READ DA KULLAN
	 //READ DA KULLAN
	 //READ DA KULLAN
}

uint8_t adc_read()
{
	ADC2->CR2 |=(1<<30);
	while((ADC->CSR & (1<<9))==0);



	return ADC2->DR;

}

uint8_t adc_degeri = 0;







int main(void)
{
	adc_ayarlari();
	gpio_ayarlari();
    while (1)
  {
    	adc_degeri = adc_read();
  }


}










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
