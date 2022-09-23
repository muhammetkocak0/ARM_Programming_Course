
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint32_t SystemCoreClock ;
uint32_t sistem_clock_hizi;


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


sistem_clock_hizi=SystemCoreClock;
RCC_DeInit();
SystemCoreClockUpdate();
sistem_clock_hizi=SystemCoreClock;


RCC_Configuration_Registers();
SystemCoreClockUpdate();
sistem_clock_hizi=SystemCoreClock;




  while (1)
  {

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
