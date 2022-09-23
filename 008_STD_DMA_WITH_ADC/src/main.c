
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

ADC_InitTypeDef adc_for_dma;
ADC_CommonInitTypeDef adc_for_dma_common;
DMA_InitTypeDef dma_with_adc;
DMA_Stream_TypeDef dma_with_adc_stream;
GPIO_InitTypeDef gpio_for_adc;
uint16_t adc_value[5];



void gpio_for_adc_cfg()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	gpio_for_adc.GPIO_Mode = GPIO_Mode_AN;
	gpio_for_adc.GPIO_OType = GPIO_OType_PP;
	gpio_for_adc.GPIO_Pin = GPIO_Pin_0;
	gpio_for_adc.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_for_adc.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &gpio_for_adc);



}

void adc_cfg_for_dma()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

	 adc_for_dma_common.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	 adc_for_dma_common.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
     adc_for_dma_common.ADC_Mode = ADC_Mode_Independent;
	 adc_for_dma_common.ADC_Prescaler = ADC_Prescaler_Div8;
	ADC_CommonInit(&adc_for_dma_common);

	adc_for_dma.ADC_ContinuousConvMode = ENABLE;
	adc_for_dma.ADC_NbrOfConversion = 1;
	adc_for_dma.ADC_Resolution = ADC_Resolution_12b;
	adc_for_dma.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	adc_for_dma.ADC_ExternalTrigConv = 0;
	adc_for_dma.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC3, &adc_for_dma);
    ADC_Cmd(ADC3, ENABLE);
    ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);
    ADC_RegularChannelConfig(ADC3, ADC_Channel_10, 1, ADC_SampleTime_56Cycles);
    ADC_DMACmd(ADC3, ENABLE);

}

void dma_with_adc_cfg()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	dma_with_adc.DMA_BufferSize = 1;
	dma_with_adc.DMA_Channel = DMA_Channel_2;
	dma_with_adc.DMA_DIR = DMA_DIR_PeripheralToMemory;
	dma_with_adc.DMA_Priority = DMA_Priority_VeryHigh;
	dma_with_adc.DMA_PeripheralBaseAddr = (uint32_t)(&ADC3->DR);
	dma_with_adc.DMA_Memory0BaseAddr = (uint32_t)(&adc_value);

	dma_with_adc.DMA_FIFOMode = DMA_FIFOMode_Enable;
	dma_with_adc.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	dma_with_adc.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	dma_with_adc.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	dma_with_adc.DMA_Mode = DMA_Mode_Circular;
	dma_with_adc.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dma_with_adc.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dma_with_adc.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma_with_adc.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_Init(DMA2_Stream0, &dma_with_adc);

	DMA_Cmd(DMA2_Stream0, ENABLE);
}











int main(void)
{

gpio_for_adc_cfg();
adc_cfg_for_dma();
dma_with_adc_cfg();


ADC_SoftwareStartConv(ADC3);

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
