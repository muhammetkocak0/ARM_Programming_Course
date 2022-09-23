
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void timer_settings()
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM2->CR1 |= (1<<0);
	TIM2->CR1 |= (1<<4);
	TIM2->CR1 |= (1<<7);
	TIM2->CR1 |= (1<<8);
	TIM2->EGR |=(1<<0);
	TIM2->PSC = 41000;
	TIM2->ARR = 20000;

}











uint16_t count=0;

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
	timer_settings();
	//RCC_Configuration_Registers();
  while (1)
  {
   count=TIM2->CNT;
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
