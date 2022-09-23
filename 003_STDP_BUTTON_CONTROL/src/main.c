
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

GPIO_InitTypeDef ButonKontrol;
GPIO_InitTypeDef LedKontrol;
void led_gpio_ayarlari()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	LedKontrol.GPIO_Mode = GPIO_Mode_OUT;
	LedKontrol.GPIO_OType = GPIO_OType_PP;
	LedKontrol.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	LedKontrol.GPIO_PuPd = GPIO_PuPd_NOPULL;
	LedKontrol.GPIO_Speed =GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&LedKontrol);

}
void buton_gpio_ayarlari()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	ButonKontrol.GPIO_Mode = GPIO_Mode_IN;
	ButonKontrol.GPIO_OType = GPIO_OType_PP;
	ButonKontrol.GPIO_Pin = GPIO_Pin_0;
	ButonKontrol.GPIO_PuPd = GPIO_PuPd_DOWN;
	ButonKontrol.GPIO_Speed =GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&ButonKontrol);

}




int main(void)
{
RCC_Configuration_Registers();
SystemCoreClockUpdate();
led_gpio_ayarlari();
buton_gpio_ayarlari();

  while (1)
  {
	  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)
	  {
		  while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1);
		  for(int i = 0; i<1680000;i++);
		  GPIO_ToggleBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	  }


  }
}















void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
