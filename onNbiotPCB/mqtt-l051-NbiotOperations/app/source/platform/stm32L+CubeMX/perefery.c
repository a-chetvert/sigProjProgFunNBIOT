#include "perefery.h"


//	порог срабатывания, в схеме DRAWIO указан, как ValueWarning 
#define POROG 50

//	???
#define CLK_MIN 3

//	состояния люка
#define TRAPDOOR_OPEN 1
#define TRAPDOOR_CLOSE 0


//	состояние люка
uint32_t stateTrapdoor = 0;  

//	вскрытия за последние M часов
uint32_t someTimeOpen = 0;

// условное время с момента старта мк
uint32_t timeNow = 0;


////	временный массив для съема данных с АЦП
//volatile uint16_t adc[4] = {0,};

#define VALUE_LIGHT adc[1]

//	временный массив для съема данных с АЦП
volatile uint16_t adc[3] = {0,};

#define ADC_REFERENCE_VOLTAGE                                           1.224
#define ADC_MAX                                                         0xFFF

#define VREFINT_CAL_ADDR 0x1FF80078

float oneParrotAdcVal=0;
//float cellVoltage=0;
uint16_t cellVoltage=0;

//	флаг для работы ADC
volatile uint8_t flagADC = 0;
//	флаг для хранения предыдущего состояния ADC
volatile uint8_t flagPrevADC = 0;

//	массив для отладки
char trans_str[64] = {0,};

void standbyStart(void)
{
		__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
		__HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);
		HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, STANDBY_START, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
		HAL_PWR_EnterSTANDBYMode();
}

void adcWork(void)
{
		apdsPwrOn();
		checkBatOn();
		HAL_Delay(100);
		HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED);
		HAL_ADC_Start_DMA(&hadc, (uint32_t*)&adc, 3); 
		
		while(flagPrevADC==0)
		{
			flagPrevADC = flagADC;
			if(flagADC)
			{
						HAL_ADC_Stop_DMA(&hadc); 
						checkBatOff();
						apdsPwrOff();
				
						flagADC = 0;
						flagPrevADC = 1;
				
						#define CONV_FOR_CELL	(ADC_REFERENCE_VOLTAGE*1200.f)
						cellVoltage = CONV_FOR_CELL / adc[2] * adc[0];
				
						snprintf(trans_str, 63, "\nSENS %d %d\n", (uint16_t)VALUE_LIGHT, cellVoltage);
						HAL_UART_Transmit(&huart2, (uint8_t*)trans_str, strlen(trans_str),5000);
			}		
		}	
		flagPrevADC = 0;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
   flagADC = 1;
}


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
