
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
EXTI_InitTypeDef exti_ayarlari;
GPIO_InitTypeDef gpio_exti;
NVIC_InitTypeDef nvic_ayarlari;

void interrupt_with_button()
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	gpio_exti.GPIO_Mode = GPIO_Mode_IN;
	gpio_exti.GPIO_OType = GPIO_OType_PP;
	gpio_exti.GPIO_Pin = GPIO_Pin_0;
	gpio_exti.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio_exti.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio_exti);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	gpio_exti.GPIO_Mode = GPIO_Mode_OUT;
	gpio_exti.GPIO_OType = GPIO_OType_PP;
	gpio_exti.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	gpio_exti.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_exti.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&gpio_exti);




	nvic_ayarlari.NVIC_IRQChannel = EXTI0_IRQn;
	nvic_ayarlari.NVIC_IRQChannelCmd = ENABLE;
	nvic_ayarlari.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Init(&nvic_ayarlari);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);



	exti_ayarlari.EXTI_Line = EXTI_Line0;
	exti_ayarlari.EXTI_LineCmd = ENABLE;
	exti_ayarlari.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_ayarlari.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&exti_ayarlari);



}


void EXTI0_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET);
	{
		for(int i = 0; i<1680000;i++);
		GPIO_ToggleBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}




}


int main(void)
{
	interrupt_with_button();
  while (1)
  {

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
