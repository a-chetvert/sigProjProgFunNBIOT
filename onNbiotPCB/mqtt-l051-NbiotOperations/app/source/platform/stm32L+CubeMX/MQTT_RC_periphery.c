#include "MQTT_RC_periphery.h"

void RcUartInit(void)
{
	hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 9600;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	
	HAL_Delay(DELAY_AFTER_RC_UART_INIT);	
}

void RcUartFstRecieve(uint8_t *tmpRxData)
{
	HAL_UART_Receive_IT(UART_RC, tmpRxData, 1);
}

void rcPwrOn(void)
{
	HAL_GPIO_WritePin(RC_PWR_GPIO_Port, RC_PWR_Pin, GPIO_PIN_SET);
}

void rcPwrOff(void)
{
	HAL_GPIO_WritePin(RC_PWR_GPIO_Port, RC_PWR_Pin, GPIO_PIN_RESET);
}

void rcCapOn(void)
{
	HAL_GPIO_WritePin(RC_CAP_GPIO_Port, RC_CAP_Pin, GPIO_PIN_SET);
}

void rcCapOff(void)
{
	HAL_GPIO_WritePin(RC_CAP_GPIO_Port, RC_CAP_Pin, GPIO_PIN_RESET);
}

void rcTurnOn(void)
{
	rcCapOn();
	HAL_Delay(DELAY_CAP_2_PWR_ON);
	rcPwrOn();
	HAL_Delay(DELAY_PWR_ON_2_PWR_OFF);
	rcPwrOff();
}

