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

/** @defgroup Selecting configuration options
  * @{
  */
	
/**
  * @brief  Choosing a UART to communicate with the module
  */
#define UART_RC &hlpuart1

/**
  * @brief  Using 
  */
#define FREERTOS    0
#define CMD_DELAY   10

/**
 * @}
 */
// ==============

#endif /* PEREFERY_H_ */
