
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


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
GPIO_InitTypeDef gpio_exti;
void gpio_ayar()
{

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
gpio_exti.GPIO_Mode = GPIO_Mode_IN;
gpio_exti.GPIO_OType = GPIO_OType_PP;
gpio_exti.GPIO_Pin = GPIO_Pin_0;
gpio_exti.GPIO_PuPd = GPIO_PuPd_DOWN;
gpio_exti.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_Init(GPIOA,&gpio_exti);

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
RCC->AHB1ENR |=(1<<1);
RCC->APB2ENR = 0x00004000;


NVIC_EnableIRQ(EXTI15_10_IRQn);
NVIC_EnableIRQ(EXTI0_IRQn);

RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
gpio_exti.GPIO_Mode = GPIO_Mode_OUT;
gpio_exti.GPIO_OType = GPIO_OType_PP;
gpio_exti.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
gpio_exti.GPIO_PuPd = GPIO_PuPd_NOPULL;
gpio_exti.GPIO_Speed = GPIO_Speed_100MHz;
GPIO_Init(GPIOD,&gpio_exti);



SYSCFG->EXTICR[0] = 0x00000000;
SYSCFG->EXTICR[3] = 0x00000000;
SYSCFG->EXTICR[3] |= (1<<6);
NVIC_SetPriority(EXTI0_IRQn,0);
NVIC_SetPriority(EXTI15_10_IRQn,1);
EXTI->IMR |= (1<<13)|(1<<0);
EXTI->RTSR |=(1<<13)|(1<<0);


}

void EXTI0_IRQHandler()
{
	if(EXTI->PR & (1 << 0))
	{
		for(int i = 0; i<1680000;i++);
		GPIO_ToggleBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		EXTI->PR  |= (1<<0);
	}


}
void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & (1 << 13))
	{
		for(int i = 0; i<1680000;i++);
		GPIO_ToggleBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		EXTI->PR  |= (1<<13);
	}


}





int main(void)
{

	gpio_ayar();
	RCC_Configuration_Registers();

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
