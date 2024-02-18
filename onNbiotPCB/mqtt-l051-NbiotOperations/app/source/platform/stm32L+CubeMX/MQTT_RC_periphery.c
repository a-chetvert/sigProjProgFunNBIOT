#include "MQTT_RC_periphery.h"

////	Инициализация для работы с GSM
//SIM800_t SIM800;


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
	rcPwrOff();
	HAL_Delay(2000);
//	HAL_Delay(DELAY_CAP_2_PWR_ON);
	rcPwrOn();
	HAL_Delay(DELAY_PWR_ON_2_PWR_OFF);
	rcPwrOff();
	
}

void rcTurnOff(void){
	

	rcPwrOn();
	HAL_Delay(1000);
	rcPwrOff();
	
} 

void rcSending(void)
{
	rcCapOn();
	rcTurnOn();
	HAL_Delay(5000);	
	
	char str[62] = {0};
	char str_[128] = {0};

	
	HAL_Delay(12000);		
	
	MX_LPUART1_UART_Init();
//	RcUartInit();
//	MQTT_Init();	
	HAL_Delay(100);	
	
	MQTT_Init();

	HAL_Delay(10000);			
	

	
	
	//	Set phone functionality
//	SIM800_SendCommand("AT+CFUN=0\r\n", "OK\r\n", CMD_DELAY);
//	HAL_Delay(1800);			
//	//	Set Default PSD Connection Settings
//	SIM800_SendCommand("AT*MCGDEFCONT=\"IP\",\"iot\"\r\n", "OK\r\n", CMD_DELAY);
//	HAL_Delay(100);
//	SIM800_SendCommand("AT+CFUN=1\r\n", "OK\r\n", CMD_DELAY);
//	HAL_Delay(1500);	
//	
//	
////	//Get mobile operation band
////	SIM800_SendCommand("AT+CBAND=?\r\n", "OK\r\n", CMD_DELAY);
////	HAL_Delay(1000);			

//	//Get mobile operation band
//	SIM800_SendCommand("AT+CBAND=3,8,20\r\n", "OK\r\n", CMD_DELAY);
//	HAL_Delay(300);			

//	//	Control the Data Output Format
//	SIM800_SendCommand("AT+CREVHEX=0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(300);		
//// тест досюда провел		

//	SIM800_SendCommand("AT+CSQ\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(500);	
//	SIM800_SendCommand("AT+CGREG?\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(500);			
//	SIM800_SendCommand("AT+CGACT?\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(500);			
//	SIM800_SendCommand("AT+COPS?\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(500);	
//	SIM800_SendCommand("AT+CGCONTRDP\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(500);		
//	SIM800_SendCommand("AT+CFUN=0\r\n", "OK\r\n", CMD_DELAY);
//	HAL_Delay(1000);	
//	SIM800_SendCommand("AT*MCGDEFCONT=\"IP\",\"cmnbiot\"\r\n", "OK\r\n", CMD_DELAY);
//	HAL_Delay(900);
//	SIM800_SendCommand("AT+CFUN=1\r\n", "OK\r\n", CMD_DELAY);
//	HAL_Delay(1000);	
//	SIM800_SendCommand("AT+CGREG?\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(500);			
//	SIM800_SendCommand("AT+CGCONTRDP\r\n", "OK\r\n", 100/*CMD_DELAY*/);

//	HAL_Delay(1300);
//	
//	SIM800_SendCommand("AT+CMQTSYNC=1\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(3000);		

//	SIM800_SendCommand("AT+CMQNEW=""dev.rightech.io"",\"1883\",12000,1024\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(1300);		

//	SIM800_SendCommand("AT+CMQCON=0,3,\"mqtt-a_chetvert-3he0ww21\",600,0,0,\"krsn\",\"pw275PG668\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);		

//	SIM800_SendCommand("AT+CMQSUB=0,\"mqtt-a_chetvert-3he0ww21/lgt\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);
//	SIM800_SendCommand("AT+CMQPUB=0,\"mqtt-a_chetvert-3he0ww21/lgt\",0,0,0,4,\"1025\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);	
//	SIM800_SendCommand("AT+CMQUNSUB=0,\"mqtt-a_chetvert-3he0ww21/lgt\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);	
//	
//	SIM800_SendCommand("AT+CMQSUB=0,\"trapdoor\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);
//	SIM800_SendCommand("AT+CMQPUB=0,\"trapdoor\",0,0,0,4,\"1023\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);	
//	SIM800_SendCommand("AT+CMQUNSUB=0,\"trapdoor\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);	
//	
//	SIM800_SendCommand("AT+CMQSUB=0,\"somehouropen\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);
//	SIM800_SendCommand("AT+CMQPUB=0,\"somehouropen\",0,0,0,4,\"1023\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);	
//	SIM800_SendCommand("AT+CMQUNSUB=0,\"somehouropen\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);	
//	
//	SIM800_SendCommand("AT+CMQSUB=0,\"timeNow\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);
//	SIM800_SendCommand("AT+CMQPUB=0,\"timeNow\",0,0,0,4,\"1023\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);	
//	SIM800_SendCommand("AT+CMQUNSUB=0,\"timeNow\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);		
//	
//	SIM800_SendCommand("AT+CMQSUB=0,\"timeNow\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);
//	SIM800_SendCommand("AT+CMQPUB=0,\"timeNow\",0,0,0,4,\"1023\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);	
//	SIM800_SendCommand("AT+CMQUNSUB=0,\"timeNow\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);		
//	
//	SIM800_SendCommand("AT+CMQSUB=0,\"vCell\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);
//	SIM800_SendCommand("AT+CMQPUB=0,\"vCell\",0,0,0,4,\"1023\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);	
//	SIM800_SendCommand("AT+CMQUNSUB=0,\"vCell\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(800);	
//		
//		
//		
//	//	Disconnect MQTT	
//	SIM800_SendCommand("AT+CMQDISCON=0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(900);	

//// заменить значение на 0
//// срочное выключение
//	SIM800_SendCommand("AT+CPOWD=1\r\n", "OK\r\n", 100/*CMD_DELAY*/);
//	HAL_Delay(5000);	
//	rcTurnOff();
	rcCapOff();
	HAL_Delay(15000);		
	           
	
	
/*
	testPinOn();

//перенести в отдельную функцию

// HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
// HAL_RTCEx_SetWakeUpTimer(&hrtc);

*/
}

