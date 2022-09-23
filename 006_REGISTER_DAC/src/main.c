
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void GPIO_DAC_Config()
{

	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= (1<<11)|(1<<10);
	GPIOA->OSPEEDR |= (1<<11)|(1<<10);


}

void DAC_ConfigG()
{
	RCC->APB1ENR |= (1<<29);
	DAC->CR |= (1<<16);
	DAC->SWTRIGR &= ~(1<<1);
}














int main(void)
{

	//GPIO_DAC_Config();
	DAC_ConfigG();
	int i = 0;
  while (1)
  {
	  DAC->DHR12R2 = i;
	  i++;
	  for(int a = 0; a<16800*2; a++);
	  if(i==4095)
	  {
		  i=0;
	  }

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
