

#include "BMP180_HAL.h"
#define BMP180_CALIBRATION_START_ADDRESS 0xAA

void BMP180_Init()
{
if(HAL_I2C_IsDeviceReady(&hi2c2, BMP180_WRITE_ADDRESS, 1, 100)==HAL_OK)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, ENABLE);
}
BMP180_Calibrate();
}

int8_t calib_buff[22];

int16_t AC1, AC2, AC3, B1, B2, MB, MC, MD;
uint16_t AC4, AC5, AC6;

void BMP180_Calibrate()
{
	HAL_I2C_Mem_Read(&hi2c2, BMP180_READ_ADDRESS, BMP180_CALIBRATION_START_ADDRESS, 1, calib_buff, 22, 30);

	AC1=(int16_t)((calib_buff[0]<<8)|calib_buff[1]);
	AC2=(int16_t)((calib_buff[2]<<8)|calib_buff[3]);
	AC3=(int16_t)((calib_buff[4]<<8)|calib_buff[5]);
	AC4=(uint16_t)((calib_buff[6]<<8)|calib_buff[7]);
	AC5=(uint16_t)((calib_buff[8]<<8)|calib_buff[9]);
	AC6=(uint16_t)((calib_buff[10]<<8)|calib_buff[11]);
	B1=(int16_t)((calib_buff[12]<<8)|calib_buff[13]);
	B2=(int16_t)((calib_buff[14]<<8)|calib_buff[15]);
	MB=(int16_t)((calib_buff[16]<<8)|calib_buff[17]);
	MC=(int16_t)((calib_buff[18]<<8)|calib_buff[19]);
	MD=(int16_t)((calib_buff[20]<<8)|calib_buff[21]);
}


int16_t X1, X2,X3, B5,B6,B3;
uint16_t B4,B7;
int16_t UT;
int16_t BMP180_True_Temperature()
{
	uint8_t uncompensated_tmp_address[1];
	uint8_t UT_Da[2];
	uncompensated_tmp_address[0] = 0x2E;
	HAL_I2C_Mem_Write(&hi2c2, BMP180_WRITE_ADDRESS, 0xF4, 1, uncompensated_tmp_address, 1, 100000);
	HAL_Delay(5);

	HAL_I2C_Mem_Read(&hi2c2, BMP180_READ_ADDRESS, 0xF6, 1, UT_Da, 2, 100000);
	HAL_Delay(5);


	UT= (int16_t)((UT_Da[0]<<8) | UT_Da[1]);

	X1 = (( (int16_t)UT-(int16_t)AC6 )*(int16_t)AC5)/32768;

	X2 = ((int16_t)MC*2048)/(X1+(int32_t)MD);
	B5 = X1+X2;
	return ((B5+8)/16/10);
}

int16_t UP;

int16_t BMP180_True_Pressure()
{
	int16_t p;
	uint8_t uncompensated_prs_address[1];
	uint8_t UT_Da[3];
	uncompensated_prs_address[0] = 0x34|(3<<6);
	HAL_I2C_Mem_Write(&hi2c2, BMP180_WRITE_ADDRESS, 0xF4, 1, uncompensated_prs_address, 1, 100000);
	HAL_Delay(5);

	HAL_I2C_Mem_Read(&hi2c2, BMP180_READ_ADDRESS, 0xF6, 1, UT_Da, 3, 100000);
	HAL_Delay(5);


	UP= (int16_t)(((UT_Da[0]<<16) | (UT_Da[1]<<8)|UT_Da[2])>>5);
	B6=B5-4000;
	X1 = ((int16_t)B2*(int16_t)B6*(int16_t)B6/4096)/2048;

	X2 = (int16_t)AC2*(int16_t)B6/2048;
	X3 = X1+X2;
	B3 = (((AC1*4+(int32_t)X3)<<3)+2)/4;
	X1 = (int16_t)AC3*(int16_t)B6/8192;
	X2 = (int16_t)B1*(int16_t)B6*(int16_t)B6/4096/65536;
	X3 = ((int16_t)X1+(int16_t)X2+2)/4;
	B4 = (int16_t)AC4*(uint16_t)(X3+32768)/32768;
	B7 = ((uint16_t)UP-(int16_t)B3)*(50000>>3);
	if(B7<0x80000000)
	{
		p = (int16_t)(B7*2)/(int16_t)B4;
	}
	else
	{
		p = (int16_t)(B7*B4)*2;
	}

	X1=(p/256)*(p/256);
	X1=(X1*3038)/65536 ;
	X2=(p*-7357)/65536 ;
	p=p+(X1+X2+3791)/16;
	return p*0.00000986923;
}








