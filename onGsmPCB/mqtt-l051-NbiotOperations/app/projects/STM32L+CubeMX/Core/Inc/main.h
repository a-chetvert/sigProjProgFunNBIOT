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


void check1BatOn(void);
void check1BatOff(void);
void check2BatOn(void);
void check2BatOff(void);
void simSupOn(void);
void simSupOff(void);
void testPinOn(void);
void testPinOff(void);
void apdsPwrOn(void);
void apdsPwrOff(void);
void simSupOn(void);
void simSupOff(void);
void sim800Start(void);

//	включение режима Standby
void standbyStart(void);
void sim800Sending(void);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define APDS_SIGNAL_Pin GPIO_PIN_0
#define APDS_SIGNAL_GPIO_Port GPIOA
#define BAT2_SENS_ADC_IN1_Pin GPIO_PIN_1
#define BAT2_SENS_ADC_IN1_GPIO_Port GPIOA
#define BAT1_SENS_ADC_IN2_Pin GPIO_PIN_2
#define BAT1_SENS_ADC_IN2_GPIO_Port GPIOA
#define DCDC_EN_Pin GPIO_PIN_3
#define DCDC_EN_GPIO_Port GPIOA
#define BH1750_PWR_Pin GPIO_PIN_5
#define BH1750_PWR_GPIO_Port GPIOA
#define BH1750_RESET_Pin GPIO_PIN_6
#define BH1750_RESET_GPIO_Port GPIOA
#define MCU_TIM_TIM22_CH2_Pin GPIO_PIN_7
#define MCU_TIM_TIM22_CH2_GPIO_Port GPIOA
#define BAT2_CHECK_Pin GPIO_PIN_0
#define BAT2_CHECK_GPIO_Port GPIOB
#define MCU_GPIO_Pin GPIO_PIN_1
#define MCU_GPIO_GPIO_Port GPIOB
#define APDS_SHDN_Pin GPIO_PIN_2
#define APDS_SHDN_GPIO_Port GPIOB
#define BAT1_CHECK_Pin GPIO_PIN_15
#define BAT1_CHECK_GPIO_Port GPIOB
#define APDS_PWR_Pin GPIO_PIN_8
#define APDS_PWR_GPIO_Port GPIOA
#define GSM_CAP_TIM22_CH1_Pin GPIO_PIN_4
#define GSM_CAP_TIM22_CH1_GPIO_Port GPIOB
#define GSM_RESET_Pin GPIO_PIN_5
#define GSM_RESET_GPIO_Port GPIOB
#define GSM_PWR_Pin GPIO_PIN_6
#define GSM_PWR_GPIO_Port GPIOB
#define GSM_STATUS_Pin GPIO_PIN_8
#define GSM_STATUS_GPIO_Port GPIOB
#define BAT_DEPASS_Pin GPIO_PIN_9
#define BAT_DEPASS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
