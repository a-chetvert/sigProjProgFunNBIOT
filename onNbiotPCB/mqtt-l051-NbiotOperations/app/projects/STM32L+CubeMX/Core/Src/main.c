/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "usart.h"
#include "rtc.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include <stdio.h>

#include "MQTTSim800.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define STANDBY_START 5

#define TEST_BKP 2
#define TEST_ADC 0
#define PRODUCTION 1

//#define STYLE TEST
#define STYLE PRODUCTION


#define FIRST 0
#define nFIRST 1

//#define STYLE TEST
#define STYLE_BKP nFIRST

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

//	Инициализация для работы с GSM
SIM800_t SIM800;



//	порог срабатывания, в схеме DRAWIO указан, как ValueWarning 
#define POROG 50

//	???
#define CLK_MIN 3

//	состояния люка
#define TRAPDOOR_OPEN 1
#define TRAPDOOR_CLOSE 0

//	флаг для работы ADC
volatile uint8_t flagADC = 0;
//	флаг для хранения предыдущего состояния ADC
volatile uint8_t flagPrevADC = 0;

//	состояние люка
uint32_t stateTrapdoor = 0;  

//	вскрытия за последние M часов
uint32_t someTimeOpen = 0;

// условное время с момента старта мк
uint32_t timeNow = 0;

//	массив для отладки
char trans_str[64] = {0,};

//	временный массив для съема данных с АЦП
volatile uint16_t adc[4] = {0,};


//	что то для отладки
//	убери!
//volatile uint16_t btmp = 0;

/*
uint32_t bufCnt;
uint16_t state_sig;
uint8_t sendSmsFlag_open=0;
uint8_t sendSmsFlag_close=0;
uint8_t flagStart;
uint32_t Value_Light=0;
	
uint32_t ValueWarning=POROG;
uint32_t stateTrapdoor=0;
uint32_t hourOpen=0;


float twoBanksVoltage = 0;
float mcuVoltage = 0;
	
uint32_t bufCnt=0;
uint16_t min_cnt=0;

char trans_str[64] = {0,};

volatile uint16_t adc_tmp = 0;

volatile uint8_t flag_prev = 0;

*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart1) 
{
    if (&hlpuart1 == UART_RC) 
		{
        Sim800_RxCallBack();
    }
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
   flagADC = 1;
}



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	
	SIM800.sim.apn = "internet";
	SIM800.sim.apn_user = "";
	SIM800.sim.apn_pass = "";
	SIM800.mqttServer.host = "dev.rightech.io";
	SIM800.mqttServer.port = 1883;
	SIM800.mqttClient.username = "krsn";
	SIM800.mqttClient.pass = "pw275PG668";
	SIM800.mqttClient.clientID = "3he0ww21";
	SIM800.mqttClient.keepAliveInterval = 20;		
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
		
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_RTC_Init();
  MX_ADC_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */






  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
  while (1)
  {
		

		sim800Sending();

		HAL_Delay(5000);
		//	включение режима Standby
	//	standbyStart();

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_LPUART1
                              |RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Lpuart1ClockSelection = RCC_LPUART1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void standbyStart(void)
{
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
		__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);
		HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, STANDBY_START, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
		HAL_PWR_EnterSTANDBYMode();
}

void startCapGsm(void)
{	
	//	включаем питание
//	simSupOn();
	//	инициализация таймера
	HAL_Delay(10);

	MX_TIM22_Init();
	//	выставление скважности		
	__HAL_TIM_SET_COMPARE(&htim22, TIM_CHANNEL_1, 12);
	//	стартуем шим
	HAL_TIM_PWM_Start(&htim22, TIM_CHANNEL_1);
	HAL_Delay(15);
	__HAL_TIM_SET_COMPARE(&htim22, TIM_CHANNEL_1, 9);
	HAL_Delay(15);	
	__HAL_TIM_SET_COMPARE(&htim22, TIM_CHANNEL_1, 4);
	HAL_Delay(40);
	__HAL_TIM_SET_COMPARE(&htim22, TIM_CHANNEL_1, 99);
	HAL_Delay(10);
}

void sim800Sending(void)
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
	
	SIM800_SendCommand("AT\r\n", "OK\r\n", CMD_DELAY);
	HAL_Delay(10000);			
	
	
	//	Set phone functionality
	SIM800_SendCommand("AT+CFUN=0\r\n", "OK\r\n", CMD_DELAY);
	HAL_Delay(1800);			
	//	Set Default PSD Connection Settings
	SIM800_SendCommand("AT*MCGDEFCONT=\"IP\",\"iot\"\r\n", "OK\r\n", CMD_DELAY);
	HAL_Delay(100);
	SIM800_SendCommand("AT+CFUN=1\r\n", "OK\r\n", CMD_DELAY);
	HAL_Delay(1500);	
	
	
//	//Get mobile operation band
//	SIM800_SendCommand("AT+CBAND=?\r\n", "OK\r\n", CMD_DELAY);
//	HAL_Delay(1000);			

	//Get mobile operation band
	SIM800_SendCommand("AT+CBAND=3,8,20\r\n", "OK\r\n", CMD_DELAY);
	HAL_Delay(300);			

	//	Control the Data Output Format
	SIM800_SendCommand("AT+CREVHEX=0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(300);		
// тест досюда провел		

	SIM800_SendCommand("AT+CSQ\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(500);	
	SIM800_SendCommand("AT+CGREG?\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(500);			
	SIM800_SendCommand("AT+CGACT?\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(500);			
	SIM800_SendCommand("AT+COPS?\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(500);	
	SIM800_SendCommand("AT+CGCONTRDP\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(500);		
	SIM800_SendCommand("AT+CFUN=0\r\n", "OK\r\n", CMD_DELAY);
	HAL_Delay(1000);	
	SIM800_SendCommand("AT*MCGDEFCONT=\"IP\",\"cmnbiot\"\r\n", "OK\r\n", CMD_DELAY);
	HAL_Delay(900);
	SIM800_SendCommand("AT+CFUN=1\r\n", "OK\r\n", CMD_DELAY);
	HAL_Delay(1000);	
	SIM800_SendCommand("AT+CGREG?\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(500);			
	SIM800_SendCommand("AT+CGCONTRDP\r\n", "OK\r\n", 100/*CMD_DELAY*/);

	HAL_Delay(1300);
	
	SIM800_SendCommand("AT+CMQTSYNC=1\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(300);		

	SIM800_SendCommand("AT+CMQNEW=""dev.rightech.io"",\"1883\",12000,1024\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(1300);		

	SIM800_SendCommand("AT+CMQCON=0,3,\"mqtt-a_chetvert-3he0ww21\",600,0,0,\"krsn\",\"pw275PG668\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);		

	SIM800_SendCommand("AT+CMQSUB=0,\"mqtt-a_chetvert-3he0ww21/lgt\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);
	SIM800_SendCommand("AT+CMQPUB=0,\"mqtt-a_chetvert-3he0ww21/lgt\",0,0,0,4,\"1025\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);	
	SIM800_SendCommand("AT+CMQUNSUB=0,\"mqtt-a_chetvert-3he0ww21/lgt\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);	
	
	SIM800_SendCommand("AT+CMQSUB=0,\"trapdoor\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);
	SIM800_SendCommand("AT+CMQPUB=0,\"trapdoor\",0,0,0,4,\"1023\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);	
	SIM800_SendCommand("AT+CMQUNSUB=0,\"trapdoor\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);	
	
	SIM800_SendCommand("AT+CMQSUB=0,\"somehouropen\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);
	SIM800_SendCommand("AT+CMQPUB=0,\"somehouropen\",0,0,0,4,\"1023\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);	
	SIM800_SendCommand("AT+CMQUNSUB=0,\"somehouropen\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);	
	
	SIM800_SendCommand("AT+CMQSUB=0,\"timeNow\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);
	SIM800_SendCommand("AT+CMQPUB=0,\"timeNow\",0,0,0,4,\"1023\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);	
	SIM800_SendCommand("AT+CMQUNSUB=0,\"timeNow\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);		
	
	SIM800_SendCommand("AT+CMQSUB=0,\"timeNow\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);
	SIM800_SendCommand("AT+CMQPUB=0,\"timeNow\",0,0,0,4,\"1023\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);	
	SIM800_SendCommand("AT+CMQUNSUB=0,\"timeNow\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);		
	
	SIM800_SendCommand("AT+CMQSUB=0,\"vCell\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);
	SIM800_SendCommand("AT+CMQPUB=0,\"vCell\",0,0,0,4,\"1023\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);	
	SIM800_SendCommand("AT+CMQUNSUB=0,\"vCell\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(800);	
		
		
		
	//	Disconnect MQTT	
	SIM800_SendCommand("AT+CMQDISCON=0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(900);	

// заменить значение на 0
// срочное выключение
	SIM800_SendCommand("AT+CPOWD=1\r\n", "OK\r\n", 100/*CMD_DELAY*/);
	HAL_Delay(5000);	
//	rcTurnOff();
	rcCapOff();
	HAL_Delay(15000);		
	
	
	
/*
	

	testPinOn();

// HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
	
// HAL_RTCEx_SetWakeUpTimer(&hrtc);

	HAL_Delay(4000);
	simSupOff();
	testPinOff();
	*/
}




/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
