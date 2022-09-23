
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void RCC_Config()
{
	RCC->CR |= 0x00030000;	// HSEON and HSEONRDY enable
	while(!(RCC->CR & 0x00020000));	// HSEON Ready Flag wait
	RCC->CR |= 0x00080000;	// CSS Enable
	RCC->CR |= 0x01000000;	// PLL ON
	RCC->PLLCFGR |= 0x00400000;	// PLL e HSE seçtik
	RCC->PLLCFGR |= 0x00000004;	// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;	// Pll N = 168
	RCC->PLLCFGR |= 0x00000000;	// PLL p = 2
	RCC->CFGR |= 0x00000000;	// AHB Prescaler = 1
	RCC->CFGR |= 0x00080000;	// APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400;	// APB1 Prescaler = 4
	RCC->CIR |= 0x00800000;		// CSS Flag clear
}
void gpio_for_adc_cfg()
{
	RCC->AHB1ENR |=(1<<2);
    GPIOC->MODER |=(1<<2)|(1<<3);
    GPIOC->OSPEEDR |=(1<<2)|(1<<3);
}
void adc_for_dma_cfg()
{
	RCC->APB2ENR |= (1<<10);
	ADC->CCR 	|= 1 << 16;		// ADC Clock Divided By 4
	//ADC1->SMPR2 |= 6 << 0;	// 144 Cycles for Channel 0
	ADC3->CR1 	|= 0 << 24;		// ADC Resolution 12 bit
	ADC3->CR1	|= 1 << 8;		// Scan conversion mode enable
	ADC3->CR2   |= 1 << 0;		// ADC enable
	ADC3->CR2   |= 1 << 1;		// Continuous conversion mode enable
	ADC3->CR2   |= 1 << 8;		// DMA Enable
	ADC3->CR2   |= 1 << 9;		// DDS
	ADC3->CR2   |= 1 << 10;		// EOCS
	//ADC1->CR2   |= 1 << 30;	//
	ADC3->SQR1 	|= 0 << 20;		// L = 1 conversion number
	ADC3->SQR3  |= 11 << 0;		// put channel number CH0


}

uint32_t degisken[8];

void dma_with_adc_cfg()
{   RCC->AHB1ENR |=(1<<22);
	while((DMA2_Stream0->CR & 0x00000001) == 1);
	DMA2_Stream0->PAR|= (uint32_t) &ADC3->DR;
	DMA2_Stream0->M0AR |= (uint32_t) &degisken;
	DMA2_Stream0->NDTR = 1;
	DMA2_Stream0->CR |= 0 << 6;	 	// Peripheral to Memory
	DMA2_Stream0->CR |= 1 << 8;		// Circular mode
	DMA2_Stream0->CR |= 1 << 10;		// memory incremented
	DMA2_Stream0->CR |= 2 << 11;		// peripheral data size 32 bit (word)
	DMA2_Stream0->CR |= 2 << 13;		// memory data size 32 bit (word)
	DMA2_Stream0->CR |= 2 << 16;		// priority level high
	DMA2_Stream0->CR |= 1 << 26;		// channel 0 selected
	DMA2_Stream0->FCR |= 0 << 2;		// direct mode enable
	DMA2_Stream0->CR |= 1 << 0;
}




uint32_t adc_val = 0;


int main(void)
{
	//RCC_Config();
 	gpio_for_adc_cfg();
	adc_for_dma_cfg();
	dma_with_adc_cfg();
	ADC3->CR2 |= ADC_CR2_SWSTART;
  while (1)
  {


	  adc_val = degisken[0];



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
