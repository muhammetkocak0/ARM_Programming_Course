
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


FLASH_TypeDef F4_FLASH;

void FLASH_Write(uint32_t flashAddress,uint32_t flashData)
{
	FLASH_Unlock();
	FLASH_EraseSector(FLASH_Sector_11,VoltageRange_3);
	FLASH_ProgramWord(flashAddress,flashData);
	FLASH_Lock();

}

uint32_t FLASH_Read(uint32_t flashAddress)
{
	uint32_t myflashData = *(uint32_t*)flashAddress;
	return myflashData;
}




int main(void)
{

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
