#include "config.h"

//<<< Use Configuration Wizard in Context Menu >>>


// <o>Количество попугаев до вкл драйвера
// <0=> 10^3
// <1=> 10^5	(примерно 4с)
// <2=> 15*10^5		(примерно 6с)
// <3=> 25*10^5		(примерно 12с)
#define TIME_2_START 3

#if TIME_2_START==0
	#undef TIME_START 
	#define TIME_START 1000	// штатный режим
#endif
#if TIME_2_START==1
	#undef TIME_START 
	#define TIME_START 100000 //примерно 4с
#endif
#if TIME_2_START==2
	#undef TIME_START 
	#define TIME_START 150000	//примерно 6с
#endif
#if TIME_2_START==3
	#undef TIME_START 
	#define TIME_START 250000	//примерно 12с
#endif

	

//<<< end of configuration section >>>

	
	