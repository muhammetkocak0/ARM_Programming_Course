#include "stm32f4xx.h"
#include "stm32f4_discovery.h"



void RCC_Config()
{
	RCC->CR |= 0x00010000;		// HEON
	while(!(RCC->CR & 0x00020000));	// HSEON Ready Flag wait
	RCC->CR |= 0x00080000;			// CSS Enable
	RCC->CR |= 0x01000000;			// PLL On
	RCC->PLLCFGR |= 0x00400000;		// PLL HSE Selected
	RCC->PLLCFGR |= 0x00000004;		// PLL M = 4
	RCC->PLLCFGR |= 0x00005A00;		// PLL N = 168
	RCC->PLLCFGR |= 0x00000000;		// PLL P = 2
	RCC->CFGR |= 0x00000000;		// AHB Prescaler 1
	RCC->CFGR |= 0x00080000;		// APB2 Prescaler 2
	RCC->CFGR |= 0x00001400;		// AHB1 Prescaler 4
	RCC->CIR |= 0x00080000;			// HSERDY Flag Clear
	RCC->CIR |= 0x00800000;			// CSS Flag Clear
}

void gpio_for_uart()
{
	RCC->AHB1ENR |=(1<<0);
	GPIOA->MODER |=(1<<5)|(1<<7);
	GPIOA->AFR[0] |=(1<<8)|(1<<9)|(1<<10)|(1<<12)|(1<<13)|(1<<14);

}
void uart_transmitter_cfg()
{
	RCC->APB1ENR |=(1<<17);
	USART2->CR1|=(1<<3);
	USART2->CR1|=(1<<2)|(1<<5);
    USART2->CR1 |= USART_CR1_RXNEIE | USART_CR1_RXNEIE;
	USART2->BRR = 0x1112;
	USART2->CR1|=(1<<13);
}
void uart_receiver_cfg()
{

}
void NVIC_settings()
{
	 NVIC_EnableIRQ(USART2_IRQn);
	 NVIC_SetPriority(USART2_IRQn,0);
}

void send_string(char *s)
{
	while(*s)
	{
		while(!(USART2->SR &1<<7));
		USART2->DR = *s;
		*s++;

	}
}
char rx_buffer[100];
int i = 0;
void USART2_IRQHandler()
{

	if(USART2->SR & USART_SR_RXNE)
	{
		volatile char str;
		str = USART2->DR;
		rx_buffer[i] = str;


		if(rx_buffer[i]=='\n')
		{
			i=0;

		}
		else
		{

			i++;

		}
	}
}

int main(void)
{
	RCC_Config();
	gpio_for_uart();
	uart_receiver_cfg();
	NVIC_settings();
    //strcpy(rx_buffer,"asss");
	uart_transmitter_cfg();

  while (1)
  {
	  send_string(rx_buffer);
	  memset(rx_buffer,'\0',100);
	  for(int i = 0; i<16080000/3; i++);

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
