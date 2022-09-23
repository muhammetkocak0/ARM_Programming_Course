
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


void GPIO_SETTINGS()
{
	RCC->AHB1ENR |=(1<<0) | (1<<3);
	GPIOD->MODER |=(1<<30) |(1<<28) | (1<<26) | (1<<24);
	GPIOD->OSPEEDR |= (1<<30) |(1<<28) | (1<<26) | (1<<24)|(1<<31) |(1<<29) |(1<<27) |(1<<25);

	GPIOA->OSPEEDR |=(1<<1) |(1<<0);
	GPIOA->PUPDR |=(1<<1) ;
}



int main(void)
{

	GPIO_SETTINGS();

  while (1)
  {

	  if((GPIOA->IDR & (1<<0))==1)
	  {
		  while((GPIOA->IDR & (1<<0))==1)
		  for(int i = 0; i<1680000; i++);
		  GPIOD->ODR ^= (1<<12)|(1<<13)|(1<<14);
	  }



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
