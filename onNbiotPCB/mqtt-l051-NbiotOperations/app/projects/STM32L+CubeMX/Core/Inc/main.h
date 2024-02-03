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
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tim.h"
#include "usart.h"
#include "perefery.h"
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




//void simSupOn(void);
//void simSupOff(void);
void sim800Start(void);

//	включение режима Standby
void standbyStart(void);
void sim800Sending(void);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BAT_SENS_ADC_IN0_Pin GPIO_PIN_0
#define BAT_SENS_ADC_IN0_GPIO_Port GPIOA
#define APDS_SIGNAL_Pin GPIO_PIN_1
#define APDS_SIGNAL_GPIO_Port GPIOA
#define MCU_GPIO_Pin GPIO_PIN_5
#define MCU_GPIO_GPIO_Port GPIOA
#define APDS_SHDN_Pin GPIO_PIN_2
#define APDS_SHDN_GPIO_Port GPIOB
#define RC_STATUS_Pin GPIO_PIN_12
#define RC_STATUS_GPIO_Port GPIOB
#define RC_CAP_Pin GPIO_PIN_13
#define RC_CAP_GPIO_Port GPIOB
#define RC_PWR_Pin GPIO_PIN_14
#define RC_PWR_GPIO_Port GPIOB
#define BAT_CHECK_Pin GPIO_PIN_15
#define BAT_CHECK_GPIO_Port GPIOB
#define APDS_PWR_Pin GPIO_PIN_8
#define APDS_PWR_GPIO_Port GPIOA
#define APDS_SHDNA9_Pin GPIO_PIN_9
#define APDS_SHDNA9_GPIO_Port GPIOA
#define BACKUP_EN_Pin GPIO_PIN_15
#define BACKUP_EN_GPIO_Port GPIOA
#define CHRG_FAULT_Pin GPIO_PIN_3
#define CHRG_FAULT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
