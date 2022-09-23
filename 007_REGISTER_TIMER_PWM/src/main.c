
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void gpio_for_pwm()
{
	RCC->AHB1ENR |= (1<<1);
    GPIOB->MODER |= (1<<29);
    GPIOB->OSPEEDR |= (1<<28)|(1<<29);
    GPIOB->AFR[1] |=(1<<24)|(1<<27);
}

void pwm_settings()
{
	RCC->APB1ENR |= (1<<6);
	TIM12->CR1 |= (1<<0);

	TIM12->CCMR1 |=(1<<5)|(1<<6);
	TIM12->BDTR  |=(1<<15);
	TIM12->CCER |=(1<<0);
	TIM12->PSC = 84;
	TIM12->ARR = 20000;
	SysTick_Config(SystemCoreClock/1000);

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




int main(void)
{   gpio_for_pwm();
	pwm_settings();

  while (1)
  {

	  for(int i = 500; i<2500; i++)
	  {
		  TIM12->CCR1 =i ;
		  if(i%2==0)
		  {
			  delay_ms(1);
		  }

	  }
	  for(int i = 2500; i>500; i--)
	  {
		  TIM12->CCR1 =i ;
		  if(i%2==0)
				  {
					  delay_ms(1);
				  }
	  }

	 // TIM12->CCR1 =1500;



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
