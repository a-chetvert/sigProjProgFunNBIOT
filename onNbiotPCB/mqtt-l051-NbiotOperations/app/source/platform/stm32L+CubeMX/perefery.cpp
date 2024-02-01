#include "midd.h"
#include "midd.hpp"
#include "gpio.h"
#include "config.h"
#include "i2c.h"
#include "usart.h"
#include "string.h"


#include "stdio.h"
#include "GY302.h"


//#include "gpio.h"
//#include "tim.h"
//#include "adc.h"
//#include "freemaster/robosd_fm.hpp"
//#include "net/serial/robosd_serial.hpp"
//
////#include "stm32f4xx_hal_gpio.h"
//#define abs(x) ( (x)<0?(-(x)):(x))
//#define sign(x) ( (x)<0? (-1):(1))

#define TIME_START 0	//примерно 12с

//----------------
extern I2C_HandleTypeDef hi2c1;


//void midd::ilcd_display::DelayMicro(uint32_t micros)
//{
//	micros *=(SystemCoreClock / 1000000) / 5;
//	while (micros--);
//}

//void midd::ilcd_display::Delay(uint32_t Time)
//{
//	HAL_Delay(Time);
//}




/**
  * @brief This functions for class ibutton_menu
  *        from lib button.hpp.
  * @note 
  */


uint8_t butt_[6]={0};
uint8_t butt_prev[6]={0};
uint8_t butt_st[6]={0};
uint32_t butt_st_cnt[6]={0};

#define BUT_DELAY 25000

//----------------


void midd::iperefery::pwrkey_on(void)
{
//	HAL_GPIO_WritePin(SIM_PWR_GPIO_Port, SIM_PWR_Pin, GPIO_PIN_SET);
}

void midd::iperefery::pwrkey_off(void)
{
//	HAL_GPIO_WritePin(SIM_PWR_GPIO_Port, SIM_PWR_Pin, GPIO_PIN_RESET);
}

//uint16_t Value_Light=0;


//uint32_t Value_Light=0;


void midd::iperefery::begin_()
{
	//	выключаем прерывания
//__disable_irq();



////	HAL_TIM_Base_Start(&htim1);
////	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);


////	delay_2_start=-10;	
//__enable_irq();
	
	

//	Value_Light=Value_GY30();
}

void midd::iperefery::permanent_loop_()
{	
	
}



void midd::iperefery::prioritet_loop_()
{
	
	
}

#define TIME_BLINK 500

//uint8_t TxData[64];
//uint8_t RxData[64]={0};



//uint16_t state_sig=0;
//uint8_t sendSmsFlag_open=0;
//uint8_t sendSmsFlag_close=0;
//uint8_t flagStart=1;

void midd::iperefery::background_loop_()
{
	
	/*
	Value_Light=Value_GY30();
	if((Value_Light>110)&&(bufCnt==0))
	{
		HAL_Delay(50);
		if(Value_GY30()>110)
		{
			state_sig=1;
			bufCnt=2;
		}
	}
	else if((Value_Light<=110)&& (state_sig==1)&& (bufCnt>0))
	{
		bufCnt--;
	}
	else if((state_sig==1)&& (bufCnt==0))
	{
		state_sig=0;
	}
	
	if((state_sig==1)&&(sendSmsFlag_open==0))
	{
				strcpy((char *)TxData, "ATI\n");
				HAL_Delay(5000);
				HAL_UART_Transmit(&hlpuart1, TxData, 4, 400);
				HAL_Delay(11000);

				strcpy((char *)TxData, "AT+CMGS=\"+79817219264\"\r");
				HAL_UART_Transmit(&hlpuart1, TxData, 23, 200);

				HAL_Delay(32);
				strcpy((char *)TxData, "Open\r");
				HAL_UART_Transmit(&hlpuart1, TxData, 5, 100);
					
				HAL_Delay(12);
				uint8_t tmp[]={26};
				HAL_UART_Transmit(&hlpuart1, tmp, 1, 100);
				HAL_Delay(500);	
				sendSmsFlag_open=1;
				sendSmsFlag_close=0;
	}
	if((state_sig==0)&&(sendSmsFlag_close==0))
	{
			if(flagStart)
			{
				strcpy((char *)TxData, "ATI\n");
				HAL_Delay(5000);
				HAL_UART_Transmit(&hlpuart1, TxData, 4, 400);
				HAL_Delay(11000);

				strcpy((char *)TxData, "AT+CMGS=\"+79817219264\"\r");
				HAL_UART_Transmit(&hlpuart1, TxData, 23, 200);

				HAL_Delay(32);
				strcpy((char *)TxData, "Ini\r");
				HAL_UART_Transmit(&hlpuart1, TxData, 5, 100);
					
				HAL_Delay(12);
				uint8_t tmp[]={26};
				HAL_UART_Transmit(&hlpuart1, tmp, 1, 100);
				HAL_Delay(500);	
				sendSmsFlag_close=1;
				sendSmsFlag_open=0;
				flagStart=0;
			}
			else
			{
				strcpy((char *)TxData, "ATI\n");
				HAL_Delay(5000);
				HAL_UART_Transmit(&hlpuart1, TxData, 4, 400);
				HAL_Delay(11000);

				strcpy((char *)TxData, "AT+CMGS=\"+79817219264\"\r");
				HAL_UART_Transmit(&hlpuart1, TxData, 23, 200);

				HAL_Delay(32);
				strcpy((char *)TxData, "Close\r");
				HAL_UART_Transmit(&hlpuart1, TxData, 5, 100);
					
				HAL_Delay(12);
				uint8_t tmp[]={26};
				HAL_UART_Transmit(&hlpuart1, tmp, 1, 100);
				HAL_Delay(500);	
				sendSmsFlag_close=1;
				sendSmsFlag_open=0;
			}
	}	*/
}

void midd::iperefery::start_()
{
//	while(delay_2_start!=0) delay_2_start--;
	
//	Init_BH1750();
}
