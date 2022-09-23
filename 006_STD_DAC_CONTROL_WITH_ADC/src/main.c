
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

ADC_InitTypeDef adc1;

ADC_CommonInitTypeDef adc1_common;
GPIO_InitTypeDef gpio_forAdc1;

DAC_InitTypeDef dac1;
GPIO_InitTypeDef gpio_forDac1;


void gpio_settings()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	gpio_forAdc1.GPIO_Mode = GPIO_Mode_AN;
	gpio_forAdc1.GPIO_OType = GPIO_OType_PP;
	gpio_forAdc1.GPIO_Pin = GPIO_Pin_0;
	gpio_forAdc1.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_forAdc1.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio_forAdc1);


	gpio_forDac1.GPIO_Mode = GPIO_Mode_AN;
	gpio_forDac1.GPIO_OType = GPIO_OType_PP;
	gpio_forDac1.GPIO_Pin = GPIO_Pin_5;
	gpio_forDac1.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_forDac1.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&gpio_forDac1);
}
void adc1_settings()
{
	/*adc1.ADC_ContinuousConvMode = ENABLE;
	adc1.ADC_DataAlign = ADC_DataAlign_Right;
	adc1.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	adc1.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;*/




RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

adc1_common.ADC_Mode = ADC_Mode_Independent;
adc1_common.ADC_Prescaler = ADC_Prescaler_Div4;

ADC_CommonInit(&adc1_common);


adc1.ADC_Resolution = ADC_Resolution_8b;
ADC_Init(ADC1,&adc1);
ADC_Cmd(ADC1,ENABLE);


}

uint16_t adc_read()
{

	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	return ADC_GetConversionValue(ADC1);


}

void DAC1_settings()
{    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	dac1.DAC_OutputBuffer=DAC_OutputBuffer_Enable;
	dac1.DAC_Trigger = DAC_Trigger_None;
	DAC_Init(DAC_Channel_1,&dac1);
	DAC_Cmd(DAC_Channel_1,ENABLE);





}

uint32_t adc_value = 0;;

int main(void)
{
	gpio_settings();
	adc1_settings();
	DAC1_settings();
  while (1)
  {
DAC_SetChannel1Data(DAC_Align_8b_R,adc_read());
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
