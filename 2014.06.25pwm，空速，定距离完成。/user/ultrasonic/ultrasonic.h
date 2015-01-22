#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H 

#include "stm32f10x.h"
#include "TIMER.h"
#include "delay.h"
#include "GPIO.h"


#define TRIG_Init        PE2_OUT								
#define ECHO_Init        PE1_In			

#define Set_TRIG	Set_E2
#define Clr_TRIG	Clr_E2

#define Set_ECHO	Set_E1
#define Clr_ECHO	Clr_E1

#define Read_ECHO	C2


#define USE_TIM  TIM5
#define USE_TIM_TIM5

//#define USE_TIM  TIM6
//#define USE_TIM_TIM6
//#define USE_TIM  TIM7
//#define USE_TIM_TIM7

void Ult_Init(void);
void Get_Distance(u16 *date);

#endif
