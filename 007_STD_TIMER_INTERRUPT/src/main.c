#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
TIM_TimeBaseInitTypeDef timer_ayar;
NVIC_InitTypeDef NVIC_Timer;

void timer_interrupt_configes()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	timer_ayar.TIM_ClockDivision = TIM_CKD_DIV1;
	timer_ayar.TIM_CounterMode = TIM_CounterMode_Up;
	timer_ayar.TIM_Period = 41999;
	timer_ayar.TIM_Prescaler = 1999;
	timer_ayar.TIM_RepetitionCounter = 0;

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	TIM_TimeBaseInit(TIM2,&timer_ayar);
	TIM_Cmd(TIM2,ENABLE);

	NVIC_Timer.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_Timer.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Timer.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Timer.NVIC_IRQChannelSubPriority = 1;

	NVIC_Init(&NVIC_Timer);







}
GPIO_InitTypeDef GPIO_ayarlari;



void GPIO_ayar_fonksiyonu()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_ayarlari.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_ayarlari.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_ayarlari.GPIO_OType = GPIO_OType_PP;
	GPIO_ayarlari.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_ayarlari.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_ayarlari);
}
uint32_t count=0;
void TIM2_IRQHandler()
{

	GPIO_ToggleBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	count++;

   TIM_ClearITPendingBit(TIM2,TIM_IT_Update);


}




int main(void)
{
	timer_interrupt_configes();
	 GPIO_ayar_fonksiyonu();
  while (1)
  {

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
