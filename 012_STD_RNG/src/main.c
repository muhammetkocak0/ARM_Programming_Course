
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

RNG_TypeDef rng_set;


void create_randomNumber()
{

	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_RNG, ENABLE);

	RNG_Cmd(ENABLE);

}

float oran = 0;

uint32_t random_number = 0,yazi=0,tura=0;
int main(void)
{
	 create_randomNumber();

  while (1)
  {
	  random_number = RNG_GetRandomNumber();
if(random_number>4294967296/2)
{
	yazi++;
}
else
{
	tura++;
}
for(int i = 0; i<1680*6;i++);
oran = ((float)tura)/((float)yazi);

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
