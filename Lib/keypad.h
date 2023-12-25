#ifndef _KEYPAD_H
#define _KEYPAD_H

#include "stm32h7xx_hal.h"

GPIO_TypeDef* ROW_1_Port = GPIOA;
GPIO_TypeDef* ROW_2_Port = GPIOA;
GPIO_TypeDef* ROW_3_Port = GPIOA;
GPIO_TypeDef* ROW_4_Port = GPIOA;
GPIO_TypeDef* COL_1_Port = GPIOB;
GPIO_TypeDef* COL_2_Port = GPIOB;
GPIO_TypeDef* COL_3_Port = GPIOB;

void keypad_init(void);
char keypad_scan(void);

#endif