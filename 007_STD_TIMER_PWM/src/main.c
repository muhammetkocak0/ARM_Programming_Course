
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


GPIO_InitTypeDef Pin_settings;
TIM_TimeBaseInitTypeDef pwm_Set_time_base;
TIM_OCInitTypeDef pwm_set_oc;;
void PWM_TIM_config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);


	Pin_settings.GPIO_Mode = GPIO_Mode_AF;
	Pin_settings.GPIO_OType = GPIO_OType_PP;

	Pin_settings.GPIO_Pin = GPIO_Pin_12;
	Pin_settings.GPIO_PuPd = GPIO_PuPd_NOPULL;
	Pin_settings.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &Pin_settings);


	pwm_Set_time_base.TIM_ClockDivision = TIM_CKD_DIV1;
	pwm_Set_time_base.TIM_CounterMode = TIM_CounterMode_Up;
	pwm_Set_time_base.TIM_Period = 50000;
	pwm_Set_time_base.TIM_Prescaler = 16;
	pwm_Set_time_base.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &pwm_Set_time_base);


	pwm_set_oc.TIM_OCMode = TIM_OCMode_PWM1;
	pwm_set_oc.TIM_OutputState = TIM_OutputState_Enable;
	pwm_set_oc.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_Cmd(TIM4, ENABLE);



}





int main(void)
{




 int i = 0;
  PWM_TIM_config();
  while (1)
  {
	  pwm_set_oc.TIM_Pulse = i;
	  TIM_OC1Init(TIM4, &pwm_set_oc);
	  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
      for(int i = 0; i<1680*4; i++);
      i++;
      if(i==49999)
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
