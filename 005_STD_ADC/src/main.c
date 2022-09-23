
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef adc_gpio_ayar;
ADC_InitTypeDef adc_ayar;
ADC_CommonInitTypeDef adc_cayar;
void adc_setup()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	adc_gpio_ayar.GPIO_Mode = GPIO_Mode_AN;
	adc_gpio_ayar.GPIO_Pin = GPIO_Pin_7;
	adc_gpio_ayar.GPIO_OType = GPIO_OType_PP;
	adc_gpio_ayar.GPIO_PuPd = GPIO_PuPd_NOPULL;
	adc_gpio_ayar.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&adc_gpio_ayar);




	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

	adc_cayar.ADC_Mode = ADC_Mode_Independent;
	adc_cayar.ADC_Prescaler = ADC_Prescaler_Div4;

	ADC_CommonInit(&adc_cayar);


	adc_ayar.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1,&adc_ayar);
	ADC_Cmd(ADC1,ENABLE);

}


uint16_t adc_read()
{

	ADC_RegularChannelConfig(ADC1,ADC_Channel_7,1,ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	return ADC_GetConversionValue(ADC1);


}


uint16_t adc_deger=0;



int main(void)
{
	adc_setup();
  while (1)
  {
	  adc_deger = adc_read();
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
