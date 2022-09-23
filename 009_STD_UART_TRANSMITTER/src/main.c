
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


USART_InitTypeDef usart_init_typ;
GPIO_InitTypeDef gpio_for_usart;
void gpio_for_usart_cfg()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	gpio_for_usart.GPIO_Mode = GPIO_Mode_AF;
	gpio_for_usart.GPIO_OType = GPIO_OType_PP;
	gpio_for_usart.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio_for_usart.GPIO_Speed = GPIO_Speed_100MHz;
	gpio_for_usart.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_Init(GPIOA, &gpio_for_usart);
}



void usart()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	usart_init_typ.USART_BaudRate = 115200;
	usart_init_typ.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_init_typ.USART_Mode = USART_Mode_Tx;
	usart_init_typ.USART_Parity =USART_Parity_No;
	usart_init_typ.USART_StopBits = USART_StopBits_1;
	usart_init_typ.USART_WordLength = USART_WordLength_8b;

	USART_Cmd(USART2, ENABLE);
	USART_Init(USART2, &usart_init_typ);

}


void USART_Puts(USART_InitTypeDef* USARTx, volatile char *s)
{
while(*s)
{
	while(!(USART2->SR & 0x00000040));

		USART_SendData(USARTx, *s);
		*s++;


}
}
char str[50];
int main(void)
{
	gpio_for_usart_cfg();
	usart();
  while (1)
  {
sprintf(&str,"hello world\n");
USART_Puts(USART2, str);
for(int i = 0; i<1680000; i++);
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
