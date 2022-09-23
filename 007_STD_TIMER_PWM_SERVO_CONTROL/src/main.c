
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

ADC_InitTypeDef adc_for_pwm;
GPIO_InitTypeDef pin_for_adc;
ADC_CommonInitTypeDef adc_for_pwm_common;

TIM_TimeBaseInitTypeDef tim_base_init;
TIM_OCInitTypeDef tim_oc_int;
GPIO_InitTypeDef pin_for_pwm;

void pwm_settings()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);

	pin_for_pwm.GPIO_Mode = GPIO_Mode_AF;
	pin_for_pwm.GPIO_Pin = GPIO_Pin_13;
	 pin_for_pwm.GPIO_OType=GPIO_OType_PP;
	 pin_for_pwm.GPIO_PuPd = GPIO_PuPd_NOPULL;
	pin_for_pwm.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &pin_for_pwm);


	tim_base_init.TIM_ClockDivision = TIM_CKD_DIV4;
	tim_base_init.TIM_CounterMode = TIM_CounterMode_Up;
	tim_base_init.TIM_Period = 19999;
	tim_base_init.TIM_Prescaler = 84;
	tim_base_init.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &tim_base_init);


	tim_oc_int.TIM_OCMode = TIM_OCMode_PWM1;
	tim_oc_int.TIM_OCPolarity = TIM_OCPolarity_High;
	tim_oc_int.TIM_OutputState = TIM_OutputState_Enable;
	SysTick_Config(SystemCoreClock/1000);


    TIM_Cmd(TIM4, ENABLE);

}


uint32_t delay_count;
void SysTick_Handler()
{
	if(delay_count > 0)
		delay_count--;
}

void delay_ms(uint32_t time)
{
	delay_count = time;
	while(delay_count);
}




void pwm_control_with_adc()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	pin_for_adc.GPIO_Mode = GPIO_Mode_AN;
	pin_for_adc.GPIO_Pin = GPIO_Pin_4;
	 pin_for_adc.GPIO_OType=GPIO_OType_PP;
	 pin_for_adc.GPIO_PuPd = GPIO_PuPd_NOPULL;
	pin_for_adc.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &pin_for_adc);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	adc_for_pwm_common.ADC_Mode = ADC_Mode_Independent;
    adc_for_pwm_common.ADC_Prescaler = ADC_Prescaler_Div8;

    ADC_CommonInit(&adc_for_pwm_common);

	adc_for_pwm.ADC_ContinuousConvMode = ENABLE;
	adc_for_pwm.ADC_DataAlign = ADC_DataAlign_Right;
	adc_for_pwm.ADC_NbrOfConversion = 1;
	adc_for_pwm.ADC_Resolution = ADC_Resolution_12b;




    ADC_Init(ADC1, &adc_for_pwm);
    ADC_Cmd(ADC1, ENABLE);

}

uint32_t adc_read()
{

	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(!(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)));
	return ADC_GetConversionValue(ADC1);
}

uint32_t adc_value = 0;

int main(void)
{

	pwm_control_with_adc();
	pwm_settings();

	  while (1)
	  {

			  tim_oc_int.TIM_Pulse = adc_read()/2+500;
			  TIM_OC2Init(TIM4, &tim_oc_int);
			  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
			  delay_ms(3);


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
