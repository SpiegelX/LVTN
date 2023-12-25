#include "ads1115.h"
extern I2C_HandleTypeDef hi2c2;
const float voltageConv = 6.114 / 32768.0;
float ADS1115_RVAL(int channel)
	{
		
		unsigned char ADSwrite[6];
		int16_t readval;
		static float voltage_ads1115;

		
			ADSwrite[0] = 0x01;
			
			switch(channel){
				case(0):
					ADSwrite[1] = 0xC1; //11000001
				break;
				case(1):
					ADSwrite[1] = 0xD1; //11010001
				break;
				case(2):
					ADSwrite[1] = 0xE1;
				break;
				case(3):
					ADSwrite[1] = 0xF1;
				break;
			}
			
			ADSwrite[2] = 0x83; //10000011 LSB
			HAL_I2C_Master_Transmit(&hi2c2, ADS1115_ADDRESS << 1, ADSwrite, 3, 100);
			ADSwrite[0] = 0x00;
			HAL_I2C_Master_Transmit(&hi2c2, ADS1115_ADDRESS << 1 , ADSwrite, 1 ,100);
			HAL_Delay(20);
			HAL_I2C_Master_Receive(&hi2c2, ADS1115_ADDRESS <<1, ADSwrite, 2, 100);
			readval = (ADSwrite[0] << 8 | ADSwrite[1] );
			if(readval < 0) {
				readval = 0;
			}
			voltage_ads1115= readval * voltageConv;
		
		return voltage_ads1115;
	}