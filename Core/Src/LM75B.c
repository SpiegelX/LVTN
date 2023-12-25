#include "LM75B.h"

typedef struct
{
		char temp_rx[2];
		char temp_tx[2];
}LM75B_DATA;
LM75B_DATA LM75;

void LM75B_INIT()
{
   char cmd[2];
   uint8_t data    = 0x1;   
   HAL_I2C_Mem_Write(&hi2c2,LM75B_ADDR, LM75B_Conf, I2C_MEMADD_SIZE_8BIT, &data,1,0x10000);
}

float LM75B_READ()
{
    HAL_I2C_Mem_Read(&hi2c2,LM75B_ADDR, LM75B_Temp, I2C_MEMADD_SIZE_8BIT, (uint8_t*)&LM75.temp_rx,1,0x10000);  
    return ((float)((LM75.temp_rx[0]<<8) | (LM75.temp_rx[1])) / 256.0   );
}