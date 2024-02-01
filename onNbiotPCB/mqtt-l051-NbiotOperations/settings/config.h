#ifndef __CONFIG_H	
#define __CONFIG_H 

//����� �������� ���� ������ ��������� �� ���������

#define NUMBER_MOTOR     2					// 	����� ����������

//#define TIME_2_START

/**
  * ������� ��������� �������
  * @param  
	���������!!!!!!!!!
	* MOTOR_TIM_*		����� �������, ����������� �� * �����
  * REF_CURRENT_*_MOTOR
  */

	//#define CURRENT_GAIN (1.f/2048*1.65f/0.2f)
	
	#if CURRENT_SENS_MODE_0==0
		#define CURRENT_GAIN_0 (1.f/2048*1.65f/0.25f)
	#endif
	
	#if CURRENT_SENS_MODE_0==1
		#define CURRENT_GAIN_0 (1.f/2048*1.65f/0.5f)
	#endif	
	
	#if CURRENT_SENS_MODE_1==0
		#define CURRENT_GAIN_1 (1.f/2048*1.65f/0.25f)
	#endif		
	
	#if CURRENT_SENS_MODE_1==1
		#define CURRENT_GAIN_1 (1.f/2048*1.65f/0.5f)
	#endif		
	
	
	
	
//	#define VOLTAGE_GAIN (8400.f/24)
#define VOLTAGE_GAIN (84000.f/VOLTAGE_MAX)
	
//	#if NUMBER_MOTOR>=1
//		#define MOTOR_CURRENT_SATURATION_0        1500		// ������������ ��� � �������
//		#define CURRENT_AMPLITUDE_MOTOR_0 				4.95 			// ����������� ��������� ������� (�� ������)		
//		#define REF_CURRENT_0_MOTOR     					360		
//		#define START_CURRENT_SCALE_0							3.f
//	#endif
//	#if NUMBER_MOTOR>=2
//		#define MOTOR_CURRENT_SATURATION_1        1500		// ������������ ��� � �������
//		#define CURRENT_AMPLITUDE_MOTOR_1 				4.95
//		#define REF_CURRENT_1_MOTOR     					360		
//		#define START_CURRENT_SCALE_0							3.f
//#endif
//	#if NUMBER_MOTOR==3
//		#define MOTOR_TIM_3												0			
//		#define AMPLITUDE_START_3_MOTOR     			100		
//		#define REF_CURRENT_3_MOTOR     					360		
//	#endif

// �� �����������: ����� �������� �� ����� ���� �������
// ���� ���  ASS722 ��� �����������, �� ���������� �������� ������� �����

// ����� �������� �� ������� �������, ���� ��� ������
// ������� ifndef, ���� ������� ������ ��� ��� ����������


#endif
