#ifndef LM75B_H
#define LM75B_H

#include "main.h"

extern I2C_HandleTypeDef hi2c2;
//  LM75B IIC address
#define    LM75B_ADDR 0x92 

//  LM75B registers
#define    LM75B_Conf        0x01
#define    LM75B_Temp        0x00
#define    LM75B_Tos         0x03
#define    LM75B_Thyst       0x02

void LM75B_INIT();
float LM75B_READ();

#endif


