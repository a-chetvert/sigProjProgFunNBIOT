#include "config.h"

//<<< Use Configuration Wizard in Context Menu >>>


// <o>���������� �������� �� ��� ��������
// <0=> 10^3
// <1=> 10^5	(�������� 4�)
// <2=> 15*10^5		(�������� 6�)
// <3=> 25*10^5		(�������� 12�)
#define TIME_2_START 3

#if TIME_2_START==0
	#undef TIME_START 
	#define TIME_START 1000	// ������� �����
#endif
#if TIME_2_START==1
	#undef TIME_START 
	#define TIME_START 100000 //�������� 4�
#endif
#if TIME_2_START==2
	#undef TIME_START 
	#define TIME_START 150000	//�������� 6�
#endif
#if TIME_2_START==3
	#undef TIME_START 
	#define TIME_START 250000	//�������� 12�
#endif

	

//<<< end of configuration section >>>

	
	