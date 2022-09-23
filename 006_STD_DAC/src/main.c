
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

DAC_InitTypeDef dac1;
GPIO_InitTypeDef gpioForDAC;


void dac1_settings()
{

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
    gpioForDAC.GPIO_Mode = GPIO_Mode_AN;
    gpioForDAC.GPIO_OType = GPIO_OType_PP;
    gpioForDAC.GPIO_Pin = GPIO_Pin_4;
    gpioForDAC.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpioForDAC.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOA,&gpioForDAC);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
    dac1.DAC_WaveGeneration = DAC_WaveGeneration_None;

	dac1.DAC_Trigger = DAC_Trigger_None;
	dac1.DAC_OutputBuffer = DAC_OutputBuffer_Enable;

	DAC_Init(DAC_Channel_1,&dac1);
    DAC_Cmd(DAC_Channel_1,ENABLE);
}




void RCC_Configuration_Registers()
{
	RCC->CR &= ~(1<<0);  //HSI kapattik
    RCC->CR |= (1<<16);  //HSE actik
    while(!(RCC->CR & 1<<17)); //HSE'nin acilip acilmadigini kontrol eder
    RCC->CR |= (1<<19);  //CSS ON bitini aktif eder bu bit clock korumasý saglar

    RCC->PLLCFGR= 0x00000000; //register'ý sýfýrlar

    RCC->PLLCFGR |=(4<<0); //PLLM 4 olarak ayarlar
    RCC->PLLCFGR |=(168<<6); // PLLN 168 olarak ayarlar
    RCC->PLLCFGR |=(1<<22); //PLL'i HSE icin aktif eder

    RCC->CR |= (1<<24); //PLL ON aktif eder
    while(!(RCC->CR & 1<<25)); //PLL acilip acilmadigini kontrol eder

    RCC->CFGR |= (1<<1); //clock'un hangi modda çalýþacaðýný seçer biz PLL yaptýk
    while(!(RCC->CFGR & 1<<1)); //modun kabul edilip edilmediðini sorgular
}


int main(void)
{
	dac1_settings();
	RCC_Configuration_Registers();
	int i = 0;
  while (1)
  {
	  DAC_SetChannel1Data(DAC_Align_8b_R,i);
	  i++;
	  for(int a = 0; a<100000; a++);
	  if(i==255)
	  {
		  i=0;
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
