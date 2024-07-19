//#include "config.h"

////<<< Use Configuration Wizard in Context Menu >>>


#define PRODUCTION 				0
#define TEST_ALL  				1
#define TEST_RC 					2
#define TEST_LIGHT_SENS 	3
#define TEST_BKP 					4

// <o>Select type works
// <0=> PRODUCTION
// <1=> TEST_ALL
// <2=> TEST_RC
// <3=> TEST_LIGHT_SENS
// <4=> TEST_BKP
#define STYLE 2


#define RIGHTECH 		0
#define RTK 				1
#define DUMP 				2
// <o>Select broker
 //<0=> RIGHTECH
 //<1=> RTK
 //<2=> DUMP
#define MODE 				0


#define BAND_ALL 					0
#define BAND_3						1
#define BAND_8						2
#define BAND_20					 	3
// <o>Select band
// <0=> ALL
// <1=> B3 (UL: 1710-1785, DL: 1805-1880 MHz)
// <2=> B8 (UL: 880-915, DL: 925-960 MHz)
// <3=> B20 (UL: 832-862, DL: 791-821 MHz)
#define BAND_STYLE 1



#define FIRST 0
#define nFIRST 1

// <o>Select type start
// <0=> FIRST
// <1=> nFIRST
#ifndef STYLE_BKP
	#define STYLE_BKP 1
#endif

#define ONLY_ALARM 2
#define GSM 1
#define WO_GSM 0
// <o>Select type works
// <0=> WO_GSM
// <1=> GSM
// <2=> ONLY_ALARM
#ifndef STYLE_GSM
	#define STYLE_GSM 1
#endif 


// остаток от делени€ равен нулю, т.е. пришло врем€ дл€ отправки сообщени€
#define TIME_HAS_COME 0

//   <o>TimeMessage [cycles] <1-1000>
//   <i> Cycles between send.
//   <i> Default: 40 cycles
// цикл дл€ отправки данных брокеру
#ifndef TIME_MESS
	#define TIME_MESS 80
#endif


//   <o>StandBy [sec] <1-1000>
//   <i> Defines StandBy time.
//   <i> Default: 40 sec
#ifndef STANDBY_TIME
 #define STANDBY_TIME       40
#endif


//   <o>Value light warning [parrot] <1-5000>
//   <i> Default: 175
#ifndef VALUE_WARNING
#define VALUE_WARNING 205
#endif	


// врем€ оставшеес€ до забвени€ открыти€
//   <o>Time before erasing open <1-49>
//   <i> Min: 2
//   <i> Default: 3
//   <i> Max: 48
#ifndef TIME_BEFORE_ERASING_OPEN
#define TIME_BEFORE_ERASING_OPEN	3
#endif	


//   <o>Time before start [ms] <1-5000>
//   <i> Defines time before start.
//   <i> Default: 1000 ms
#ifndef TIME_BF_START
 #define TIME_BF_START       1000
#endif

////<<< end of configuration section >>>

