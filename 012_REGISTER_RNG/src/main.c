
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void RNG_Init()
{
	RCC->AHB2ENR |= 1<<6;
	RNG->CR |= (1<<2);
}
uint32_t random_number()
{

	while(!(RNG->SR & (1<<0)));
	return RNG->DR;
}

uint32_t sayi=0;

int main(void)
{
	RNG_Init();
  while (1)
  {
	  sayi = random_number() % 100;
	  for(int i = 0; i<1680000; i++);
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
