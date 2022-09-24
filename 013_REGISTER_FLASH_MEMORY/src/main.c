
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void RCC_Configuration_Registers()
{
	RCC->CR &= ~(1<<0);  //HSI kapattik
    RCC->CR |= (1<<16);  //HSE actik
    while(!(RCC->CR & 1<<17)); //HSE'nin acilip acilmadigini kontrol eder
    RCC->CR |= (1<<19);  //CSS ON bitini aktif eder bu bit clock korumasý saglar

    RCC->PLLCFGR= 0x00000000; //register'ý sýfýrlar

    RCC->PLLCFGR |=(4<<0); //PLLM 4 olarak ayarlar
    RCC->PLLCFGR |=(168<<6); // PLLN 168 olarak ayarlar
    RCC->PLLCFGR |=(1<<22); //PLL'i HSE icin aktif eder

    RCC->CR |= (1<<24); //PLL ON aktif eder
    while(!(RCC->CR & 1<<25)); //PLL acilip acilmadigini kontrol eder

    RCC->CFGR |= (1<<1); //clock'un hangi modda çalýþacaðýný seçer biz PLL yaptýk
    while(!(RCC->CFGR & 1<<1)); //modun kabul edilip edilmediðini sorgular
}





void FLASH_Unlock()
{
	while(FLASH->SR & 0x00010000);

	FLASH->KEYR = 0x45670123;
	FLASH->KEYR = 0xCDEF89AB;


}

void FLASH_Erase()
{
	while(FLASH->SR & 0x00010000);
	FLASH->CR |= 1<<1;
	FLASH->CR |= 11<<3;
	FLASH->CR |= 1<<16;
	while(FLASH->SR & 0x00010000);
}
void FLASH_Write(uint32_t address,uint32_t data)
{
	while(FLASH->SR & 0x00010000);
	FLASH->CR |=1<<0;
	FLASH->CR |=2<<8;
	while(FLASH->SR & 0x00010000);
	*(__IO uint32_t*)address = data;
	while(FLASH->SR & 0x00010000);

}
uint32_T FLASH_Read(uint32_t address)
{
	uint32_t myFlashData;
	myFlashData = *(uint32_t*)address;
	return myFlashData;
}

void FLASH_Locker()
{
	while(FLASH->SR & 0x00010000);
	FLASH->CR |=1<<31;
}



int main(void)
{
	RCC_Configuration_Registers();
	FLASH_Unlock();
	FLASH_Erase();
	FLASH_Write(0x080E0000,0xCC);
	FLASH_Locker();


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
