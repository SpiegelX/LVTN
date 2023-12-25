/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SD_MOSI_Pin GPIO_PIN_1
#define SD_MOSI_GPIO_Port GPIOC
#define SD_MISO_Pin GPIO_PIN_2
#define SD_MISO_GPIO_Port GPIOC
#define USER_BUTTON_Pin GPIO_PIN_0
#define USER_BUTTON_GPIO_Port GPIOA
#define ESP_TX_Pin GPIO_PIN_2
#define ESP_TX_GPIO_Port GPIOA
#define ESP_RX_Pin GPIO_PIN_3
#define ESP_RX_GPIO_Port GPIOA
#define LED3_Pin GPIO_PIN_4
#define LED3_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOB
#define CH340_TX_Pin GPIO_PIN_14
#define CH340_TX_GPIO_Port GPIOB
#define CH340_RX_Pin GPIO_PIN_15
#define CH340_RX_GPIO_Port GPIOB
#define RS485_TX_Pin GPIO_PIN_8
#define RS485_TX_GPIO_Port GPIOD
#define RS485_RX_Pin GPIO_PIN_9
#define RS485_RX_GPIO_Port GPIOD
#define LORA_TX_Pin GPIO_PIN_6
#define LORA_TX_GPIO_Port GPIOC
#define LORA_RX_Pin GPIO_PIN_7
#define LORA_RX_GPIO_Port GPIOC
#define SD_SCK_Pin GPIO_PIN_9
#define SD_SCK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */
#define ADS1115_IC1_ADDRESS 0x48
#define ADS1115_IC2_ADDRESS 0x49

#define ADS1115_REG_CONVERSION 0x00
#define ADS1115_REG_CONFIG     0x01
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
