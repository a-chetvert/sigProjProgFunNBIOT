/**
  ******************************************************************************
  * @file    MQTT_RC_periphery.h
  * @author  Chetvertukhin Alexander
  * @brief   This file contains all the functions prototypes for the RC (radio 
  *          communication module).
  ******************************************************************************
  */

#ifndef MQTT_RC_PERIPHERY_H_
#define MQTT_RC_PERIPHERY_H_

#include <main.h>
#include "usart.h"
#include <string.h>
#include "stm32l0xx_hal.h"


/** @defgroup Selecting configuration options
  * @{
  */
	
/**
  * @brief  Choosing a UART to communicate with the module
  */
#define UART_RC &hlpuart1

/**
  * @brief  Using FREERTOS
  */
#define FREERTOS    0

/**
  * @brief  Delay between commands
  */
#define CMD_DELAY   10

/**
 * @}
 */

 
/** @defgroup Turn On RC
  * @brief    RC Turn on
  * @{
  */

/**
  * @brief  Delay between Cap on and rc Pwr On
  */
#define DELAY_CAP_2_PWR_ON   3000

/**
  * @brief  Delay between rc Pwr On and rc Pwr Off
  */
#define DELAY_PWR_ON_2_PWR_OFF   1000

void rcPwrOn(void);
void rcPwrOff(void);
void rcCapOn(void);
void rcCapOff(void);

void rcTurnOn(void);	 

 /**
  * @}
  */	

/** @defgroup HAL based function
  * @brief   	This functhion duplicate actual content HAL's function
  * @{
  */
	
/**
  * @brief  Delay between rc Pwr On and rc Pwr Off
  */
#define DELAY_AFTER_RC_UART_INIT   100	
	
/**	
  * @brief    Init RC uart	
	*/
void RcUartInit(void);

/**	
  * @brief    I don,t now why!!!!
	* @param    pointer RxData
	*/
void RcUartFstRecieve(uint8_t* tmpRxData);	

	
 /**
  * @}
  */	
 
// ==============

#endif /* PEREFERY_H_ */
