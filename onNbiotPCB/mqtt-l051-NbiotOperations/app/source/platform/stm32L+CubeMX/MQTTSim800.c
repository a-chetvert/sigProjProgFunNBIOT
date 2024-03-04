/*
 * MQTTSim800.c
 *
 *  Created on: Jan 4, 2020
 *      Author: Bulanov Konstantin
 *
 *  Contact information
 *  -------------------
 *
 * e-mail   :   leech001@gmail.com
 * telegram :   https://t.me/leech001
 *
 */

/*
 * -----------------------------------------------------------------------------------------------------------------------------------------------
           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2020 Bulanov Konstantin <leech001@gmail.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.

  MQTT packet https://github.com/eclipse/paho.mqtt.embedded-c/tree/master/MQTTPacket
 * ------------------------------------------------------------------------------------------------------------------------------------------------
*/




#include "MQTTSim800.h"

//	Инициализация для работы с GSM
SIM800_t SIM800;


//#ifndef
#define UART_RC &hlpuart1
//#endif

uint8_t rx_data = 0;

// буффер для приема
uint8_t rx_buffer[1460] = {0};
uint16_t rx_index = 0;

uint8_t mqtt_receive = 0;
char mqtt_buffer[1460] = {0};
uint16_t mqtt_index = 0;

/**
 * Call back function for release read SIM800 UART buffer.
 * @param NONE
 * @return NONE
 */
void Sim800_RxCallBack(void)
{
    rx_buffer[rx_index++] = rx_data;

		
    if (SIM800.mqttServer.connect == 0)
    {
        if (strstr((char *)rx_buffer, "\r\n") != NULL && rx_index == 2)
        {
            rx_index = 0;
        }
        else if (strstr((char *)rx_buffer, "\r\n") != NULL)
        {
            memcpy(mqtt_buffer, rx_buffer, sizeof(rx_buffer));
            clearRxBuffer();
            if (strstr(mqtt_buffer, "DY CONNECT\r\n"))
            {
                SIM800.mqttServer.connect = 0;
            }
            else if (strstr(mqtt_buffer, "CONNECT\r\n"))
            {
                SIM800.mqttServer.connect = 1;
            }
        }
    }
		

    if (strstr((char *)rx_buffer, "CLOSED\r\n") || strstr((char *)rx_buffer, "ERROR\r\n") || strstr((char *)rx_buffer, "DEACT\r\n"))
    {
        SIM800.mqttServer.connect = 0;
    }
    if (SIM800.mqttServer.connect == 1 && rx_data == 48)
    {
        mqtt_receive = 1;
    }

    if (mqtt_receive == 1)
    {
        mqtt_buffer[mqtt_index++] = rx_data;
        if (mqtt_index > 1 && mqtt_index - 1 > mqtt_buffer[1])
        {
            MQTT_Receive((unsigned char *)mqtt_buffer);
            clearRxBuffer();
            clearMqttBuffer();
        }
        if (mqtt_index >= sizeof(mqtt_buffer))
        {
            clearMqttBuffer();
        }
    }
    if (rx_index >= sizeof(mqtt_buffer))
    {
        clearRxBuffer();
        clearMqttBuffer();
    }
		
		
    HAL_UART_Receive_IT(UART_RC, &rx_data, 1);
}

/**
 * Clear SIM800 UART RX buffer.
 * @param NONE
 * @return NONE
 */
void clearRxBuffer(void)
{
    rx_index = 0;
    memset(rx_buffer, 0, sizeof(rx_buffer));
}

/**
 * Clear MQTT buffer.
 * @param NONE
 * @return NONE
 */
void clearMqttBuffer(void)
{
    mqtt_receive = 0;
    mqtt_index = 0;
    memset(mqtt_buffer, 0, sizeof(mqtt_buffer));
}

/**
 * Send AT command to RC over UART.
 * @param command the command to be used the send AT command
 * @param reply to be used to set the correct answer to the command
 * @param delay to be used to the set pause to the reply
 * @return error, 0 is OK
 */
int SIM800_SendCommand(char *command, char *reply, uint16_t delay)
{
		// выполняем отправку сообщения 
		// проверь здесь тайминг! 	
    HAL_UART_Transmit_IT(UART_RC, (unsigned char *)command,
                         (uint16_t)strlen(command));

		
#if FREERTOS == 1
    osDelay(delay);
#else
    HAL_Delay(delay);
#endif


		//	если в буффере есть ответ (reply)
    if (strstr(mqtt_buffer, reply) != NULL)
    {
        clearRxBuffer();
        return 0;
    }
    clearRxBuffer();
    return 1;
}

/**
 * initialization SIM800.
 * @param NONE
 * @return error status, 0 - OK
 */

// REF 


//int MQTT_Init(void)
//{
//    SIM800.mqttServer.connect = 0;
//    int error = 0;
//    char str[32] = {0};
//    HAL_UART_Receive_IT(UART_RC, &rx_data, 1);
//		
//    SIM800_SendCommand("AT\r\n", "OK\r\n", CMD_DELAY);
//    SIM800_SendCommand("ATE0\r\n", "OK\r\n", CMD_DELAY);
//    error += SIM800_SendCommand("AT+CIPSHUT\r\n", "SHUT OK\r\n", CMD_DELAY);
//    error += SIM800_SendCommand("AT+CGATT=1\r\n", "OK\r\n", CMD_DELAY);
//    error += SIM800_SendCommand("AT+CIPMODE=1\r\n", "OK\r\n", CMD_DELAY);
//    snprintf(str, sizeof(str), "AT+CSTT=\"%s\",\"%s\",\"%s\"\r\n", SIM800.sim.apn, SIM800.sim.apn_user,
//             SIM800.sim.apn_pass);
//    error += SIM800_SendCommand(str, "OK\r\n", CMD_DELAY);

//    error += SIM800_SendCommand("AT+CIICR\r\n", "OK\r\n", CMD_DELAY);
//    SIM800_SendCommand("AT+CIFSR\r\n", "", CMD_DELAY);
//		MQTT_Connect();
//}

int MQTT_Init(void)
{
		SIM800.sim.apn = "internet";
		SIM800.sim.apn_user = "";
		SIM800.sim.apn_pass = "";
		SIM800.mqttServer.host = "dev.rightech.io";
		SIM800.mqttServer.port = 1883;
		SIM800.mqttClient.username = "krsn";
		SIM800.mqttClient.pass = "pw275PG668";
		SIM800.mqttClient.clientID = "3he0ww21";
		SIM800.mqttClient.keepAliveInterval = 20;		
	
    SIM800.mqttServer.connect = 0;
    int error_l = 0;
		char str[62] = {0};

		// не понимаю зачем нужен этот прием
		HAL_UART_Receive_IT(UART_RC, &rx_data, 1);

		SIM800_SendCommand("AT\r\n", "OK\r\n", CMD_DELAY);
		HAL_Delay(15000);		


		
		
    
		for (char i=0; i<3; i++ )
		{
			error_l = SIM800_SendCommand("AT\r\n", "OK\r\n", CMD_DELAY);
			HAL_Delay(CMD_DELAY);		
			if(error_l == 0)
			{
				break;
			}
			
		}
		

		// отключение эхо
    SIM800_SendCommand("ATE0\r\n", "OK\r\n", CMD_DELAY);
		
		
		
		char localCnt = 1;
		
		while(localCnt)
		{
			//	Checking SIM card
			for (char i=0; i<3; i++ )
			{
				error_l = SIM800_SendCommand("AT+CPIN?\r\n", "OK\r\n", 100/*CMD_DELAY*/);
				
				if(error_l == 0)
				{
					break;
				}
				HAL_Delay(CMD_DELAY);		
			}
			
			// задефайнить
			// если симку не определяет, то сделать так:
			// проверь работу этого алгоритма

			if(error_l == 1)
			{
				SIM800_SendCommand("AT+CFUN=0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
				HAL_Delay(5000);		
				SIM800_SendCommand("AT+CFUN=1\r\n", "OK\r\n", 100/*CMD_DELAY*/);
				continue;
			}
			//если ошибок нет
			else if(error_l == 0)
			{
				localCnt = 0;
			}
		}
		
		SIM800_SendCommand("AT*MCGDEFCONT=\"IP\",\"iot\"\r\n", "OK\r\n", CMD_DELAY);
		HAL_Delay(100);				
		SIM800_SendCommand("AT+CREVHEX=0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
		HAL_Delay(300);				
		
		localCnt = 1;
		
		while(localCnt)
		{
			//	Checking SIM card
			for (char i=0; i<3; i++ )
			{
				//Set mobile operation band
				error_l = SIM800_SendCommand("AT+CBAND=3,8,20\r\n", "OK\r\n", CMD_DELAY);
				
				if(error_l == 0)
				{
					break;
				}
				HAL_Delay(CMD_DELAY);		
			}
			
			// задефайнить
			// если симку не определяет, то сделать так:
			// проверь работу этого алгоритма

			if(error_l == 1)
			{
				SIM800_SendCommand("AT+CFUN=0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
				HAL_Delay(5000);		
				SIM800_SendCommand("AT+CFUN=1\r\n", "OK\r\n", 100/*CMD_DELAY*/);
				continue;
			}
			//если ошибок нет
			else if(error_l == 0)
			{
				localCnt = 0;
			}
		}		
		
		
		
		
		localCnt = 1;
		
		while(localCnt)
		{
			//	Checking SIM card
			for (char i=0; i<3; i++ )
			{
				error_l = SIM800_SendCommand("AT+CSQ\r\n", "OK\r\n", 100/*CMD_DELAY*/);
				
				if(error_l == 0)
				{
					break;
				}
				HAL_Delay(CMD_DELAY);		
			}
			
			// задефайнить
			// если симку не определяет, то сделать так:
			// проверь работу этого алгоритма

			if(error_l == 1)
			{
				SIM800_SendCommand("AT+CFUN=0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
				HAL_Delay(5000);		
				SIM800_SendCommand("AT+CFUN=1\r\n", "OK\r\n", 100/*CMD_DELAY*/);
				continue;
			}
			//если ошибок нет
			else if(error_l == 0)
			{
				localCnt = 0;
			}
		}		
		
		localCnt = 3;
		while(localCnt--)
		{
			//	Checking SIM card
			for (char i=0; i<3; i++ )
			{
				error_l = SIM800_SendCommand("AT+CGREG?\r\n", "OK\r\n", 100/*CMD_DELAY*/);
			
				if(error_l == 0)
				{
					break;
				}
				HAL_Delay(CMD_DELAY);		
			}
			
			// задефайнить
			// если симку не определяет, то сделать так:
			// проверь работу этого алгоритма

			if(error_l == 1)
			{
				//	Set phone functionality
				SIM800_SendCommand("AT+CFUN=0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
				HAL_Delay(5000);		
				//	Set phone functionality
				SIM800_SendCommand("AT+CFUN=1\r\n", "OK\r\n", 100/*CMD_DELAY*/);
				HAL_Delay(10000);
				continue;
			}
			//если ошибок нет
			else if(error_l == 0)
			{
				localCnt = 0;
			}
		}		

		//возможно добавить для проверки
//	SIM800_SendCommand("AT+CGACT\r\n", "OK\r\n", 100/*CMD_DELAY*/);		
//	SIM800_SendCommand("AT+COPS?\r\n", "OK\r\n", 100/*CMD_DELAY*/);	
//  SIM800_SendCommand("AT+CGCONTRDP\r\n", "OK\r\n", 100/*CMD_DELAY*/);		
		

    if (error_l == 0)
    {
        MQTT_Connect();
        return 0;
    }
    else
    {
        return error_l;
    }
}

uint32_t clk=1001;

/**
 * Connect to MQTT server in Internet over TCP.
 * @param NONE
 * @return NONE
 */
void MQTT_Connect(void)
{
    char str[128] = {0};
	
		SIM800_SendCommand("AT+CMQTSYNC=1\r\n", "OK\r\n", 100/*CMD_DELAY*/);
		HAL_Delay(3000);		

//		snprintf(str, sizeof(str), "AT+CSTT=\"%s\",\"%s\",\"%s\"\r\n", SIM800.sim.apn, SIM800.sim.apn_user,
//             SIM800.sim.apn_pass);
		SIM800_SendCommand("AT+CMQNEW=""dev.rightech.io"",\"1883\",12000,1024\r\n", "OK\r\n", 100/*CMD_DELAY*/);
		HAL_Delay(1300);			

		SIM800_SendCommand("AT+CMQCON=0,3,\"mqtt-a_chetvert-3he0ww21\",600,0,0,\"krsn\",\"pw275PG668\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
		HAL_Delay(800);		
		HAL_Delay(3000);	
			
		SIM800_SendCommand("AT+CMQSUB=0,\"mqtt-a_chetvert-3he0ww21/lgt\",0\r\n", "OK\r\n", 100/*CMD_DELAY*/);
		HAL_Delay(800);
		
		
		sprintf(str , "AT+CMQPUB=0,\"mqtt-a_chetvert-3he0ww21/lgt\",0,0,0,4,\"%lu\"\r\n", clk++);
		
		SIM800_SendCommand(str, "OK\r\n", 100/*CMD_DELAY*/);
		
//		SIM800_SendCommand("AT+CMQPUB=0,\"mqtt-a_chetvert-3he0ww21/lgt\",0,0,0,4,\"1024\"\r\n", "OK\r\n", 100/*CMD_DELAY*/);
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
	
}

/**
 * Public on the MQTT broker of the message in a topic
 * @param topic to be used to the set topic
 * @param payload to be used to the set message for topic
 * @return NONE
 */
void MQTT_Pub(char *topic, char *payload)
{
    unsigned char buf[256] = {0};

    MQTTString topicString = MQTTString_initializer;
    topicString.cstring = topic;

		// good variant 4 ache
//		int mqtt_len = MQTTSerialize_publish(buf, sizeof(buf), 0, 0, 1, 0,
//                                         topicString, (unsigned char *)payload, (int)strlen(payload));
		
    int mqtt_len = MQTTSerialize_publish(buf, sizeof(buf), 0, 0, 1, 0,
                                         topicString, (unsigned char *)payload, (int)strlen(payload));
    HAL_UART_Transmit_IT(UART_RC, buf, mqtt_len);
#if FREERTOS == 1
    osDelay(100);
#else
    HAL_Delay(100);
#endif
}

/**
 * Public on the MQTT broker of the message in a topic
 * @param topic (uint8_t)  to be used to the set topic
 * @param payload to be used to the set message for topic
 * @return NONE
 */
void MQTT_PubUint8(char *topic, uint8_t payload)
{
    char str[32] = {0};
    sprintf(str, "%u", payload);
    MQTT_Pub(topic, str);
}

/**
 * Public on the MQTT broker of the message in a topic
 * @param topic (uint16_t)  to be used to the set topic
 * @param payload to be used to the set message for topic
 * @return NONE
 */
void MQTT_PubUint16(char *topic, uint16_t payload)
{
    char str[32] = {0};
    sprintf(str, "%u", payload);
    MQTT_Pub(topic, str);
}

/**
 * Public on the MQTT broker of the message in a topic
 * @param topic (uint32_t)  to be used to the set topic
 * @param payload to be used to the set message for topic
 * @return NONE
 */
void MQTT_PubUint32(char *topic, uint32_t payload)
{
    char str[32] = {0};
    sprintf(str, "%lu", payload);
    MQTT_Pub(topic, str);
}

/**
 * Public on the MQTT broker of the message in a topic
 * @param topic (float)  to be used to the set topic
 * @param payload to be used to the set message for topic
 * @return NONE
 */
void MQTT_PubFloat(char *topic, float payload)
{
    char str[32] = {0};
    sprintf(str, "%f", payload);
    MQTT_Pub(topic, str);
}

/**
 * Public on the MQTT broker of the message in a topic
 * @param topic (double)  to be used to the set topic
 * @param payload to be used to the set message for topic
 * @return NONE
 */
void MQTT_PubDouble(char *topic, double payload)
{
    char str[32] = {0};
    sprintf(str, "%f", payload);
    MQTT_Pub(topic, str);
}

/**
 * Send a PINGREQ to the MQTT broker (active session)
 * @param NONE
 * @return NONE
 */
void MQTT_PingReq(void)
{
    unsigned char buf[16] = {0};

    int mqtt_len = MQTTSerialize_pingreq(buf, sizeof(buf));
    HAL_UART_Transmit_IT(UART_RC, buf, mqtt_len);
}

/**
 * Subscribe on the MQTT broker of the message in a topic
 * @param topic to be used to the set topic
 * @return NONE
 */
void MQTT_Sub(char *topic)
{
    unsigned char buf[256] = {0};

    MQTTString topicString = MQTTString_initializer;
    topicString.cstring = topic;

    int mqtt_len = MQTTSerialize_subscribe(buf, sizeof(buf), 0, 1, 1,
                                           &topicString, 0);
    HAL_UART_Transmit_IT(UART_RC, buf, mqtt_len);
#if FREERTOS == 1
    osDelay(100);
#else
    HAL_Delay(100);
#endif
}

/**
 * Receive message from MQTT broker
 * @param receive mqtt bufer
 * @return NONE
 */
void MQTT_Receive(unsigned char *buf)
{
    memset(SIM800.mqttReceive.topic, 0, sizeof(SIM800.mqttReceive.topic));
    memset(SIM800.mqttReceive.payload, 0, sizeof(SIM800.mqttReceive.payload));
    MQTTString receivedTopic;
    unsigned char *payload;
    MQTTDeserialize_publish(&SIM800.mqttReceive.dup, &SIM800.mqttReceive.qos, &SIM800.mqttReceive.retained,
                            &SIM800.mqttReceive.msgId,
                            &receivedTopic, &payload, &SIM800.mqttReceive.payloadLen, buf,
                            sizeof(buf));
    memcpy(SIM800.mqttReceive.topic, receivedTopic.lenstring.data, receivedTopic.lenstring.len);
    SIM800.mqttReceive.topicLen = receivedTopic.lenstring.len;
    memcpy(SIM800.mqttReceive.payload, payload, SIM800.mqttReceive.payloadLen);
    SIM800.mqttReceive.newEvent = 1;
}

void rcSending(void)
{
		SIM800.sim.apn = "internet";
		SIM800.sim.apn_user = "";
		SIM800.sim.apn_pass = "";
		SIM800.mqttServer.host = "dev.rightech.io";
		SIM800.mqttServer.port = 1883;
		SIM800.mqttClient.username = "krsn";
		SIM800.mqttClient.pass = "pw275PG668";
		SIM800.mqttClient.clientID = "3he0ww21";
		SIM800.mqttClient.keepAliveInterval = 20;		
		
		
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

		SIM800_SendCommand("AT+CPOWD=1\r\n", "OK\r\n", 100/*CMD_DELAY*/);
		HAL_Delay(5000);	
		rcTurnOff();	
		rcCapOff();			
		HAL_Delay(5000);	

		
		HAL_Delay(47000);		
							 
		
		
	/*
		testPinOn();

	//перенести в отдельную функцию

	// HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
	// HAL_RTCEx_SetWakeUpTimer(&hrtc);

	*/
}
