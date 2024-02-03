#include "perefery.h"
//#include "stm32l1xx_hal.h"

void checkBatOn(void)
{
	HAL_GPIO_WritePin(BAT_CHECK_GPIO_Port, BAT_CHECK_Pin, GPIO_PIN_SET);
}

void checkBatOff(void)
{
	HAL_GPIO_WritePin(BAT_CHECK_GPIO_Port, BAT_CHECK_Pin, GPIO_PIN_RESET);
}

void backupOn(void)
{
	HAL_GPIO_WritePin(BACKUP_EN_GPIO_Port, BACKUP_EN_Pin, GPIO_PIN_SET);
}

void backupOff(void)
{
	HAL_GPIO_WritePin(BACKUP_EN_GPIO_Port, BACKUP_EN_Pin, GPIO_PIN_RESET);
}

void testPinOn(void)
{
	HAL_GPIO_WritePin(MCU_GPIO_GPIO_Port, MCU_GPIO_Pin, GPIO_PIN_RESET);
}

void testPinOff(void)
{
	HAL_GPIO_WritePin(MCU_GPIO_GPIO_Port, MCU_GPIO_Pin, GPIO_PIN_SET);
}

void apdsPwrOn(void)
{
	HAL_GPIO_WritePin(APDS_PWR_GPIO_Port, APDS_PWR_Pin, GPIO_PIN_SET);
}

void apdsPwrOff(void)
{
	HAL_GPIO_WritePin(APDS_PWR_GPIO_Port, APDS_PWR_Pin, GPIO_PIN_RESET);
}

void apdsShdnOn(void)
{
	HAL_GPIO_WritePin(APDS_SHDN_GPIO_Port, APDS_SHDN_Pin, GPIO_PIN_RESET);
}

void apdsShdnOff(void)
{
	HAL_GPIO_WritePin(APDS_SHDN_GPIO_Port, APDS_SHDN_Pin, GPIO_PIN_SET);
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
