#ifndef PEREFERY_H_
#define PEREFERY_H_
//------------------------------------------------
#include "main.h"
#include "MQTT_RC_periphery.h"


//#include "lcd.h"
//#include "button.h"

////------------------------------------------------
//typedef enum {
//  MENU_STATE_IDLE = 0,
//  MENU_STATE_WAIT,
//  MENU_STATE_MAIN,
//}MENU_StateTypeDef;


void checkBatOn(void);
void checkBatOff(void);
void backupOn(void);
void backupOff(void);
void testPinOn(void);
void testPinOff(void);
void apdsPwrOn(void);
void apdsPwrOff(void);
void apdsShdnOn(void);
void apdsShdnOff(void);

//typedef enum {
//  MAIN_MENU_STATE_IDLE = 0,
//  MAIN_MENU_STATE_WAIT,
//  MAIN_MENU_STATE_MM1,
//  MAIN_MENU_STATE_MM2,
//  MAIN_MENU_STATE_MM3,
//  MAIN_MENU_STATE_MM4,
//  MAIN_MENU_STATE_MM5,
//  MAIN_MENU_STATE_EXIT,
//  MAIN_MENU_STATE_MM1_WAIT,
//  MAIN_MENU_STATE_MM2_WAIT,
//  MAIN_MENU_STATE_MM3_WAIT,
//  MAIN_MENU_STATE_MM4_WAIT,
//  MAIN_MENU_STATE_MM5_WAIT,
//  MAIN_MENU_STATE_EXIT_WAIT
//}MAIN_MENU_StateTypeDef;
////------------------------------------------------
//void MenuProcess(void);
//------------------------------------------------
#endif /* PEREFERY_H_ */
