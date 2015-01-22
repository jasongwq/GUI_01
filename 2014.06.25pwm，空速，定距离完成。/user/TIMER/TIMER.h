#ifndef __TIMER_H
#define __TIMER_H 

#include "stm32f10x.h"
#include <stdio.h>

void TIM_Init(TIM_TypeDef* TIMER,u16 Period,u16 Prescaler);
/*
 *			 TIM_Init(TIM5,10000-1,7200-1);		   72M/7200=0.1ms 0.1*10000=1s
 *			 TIM_Init(TIM5,10000-1,72-1);		   72M/72=1us * 10000=10ms
 */

void TIMER_NVIC_Configuration(u8 TIMER ,u8 PriorityGroup,u8 PreemptionPriority,u8 SubPriority);
/*
 *			 TIMER_NVIC_Configuration(5 ,1,0,0);   ��һλ 5  ��ʾ TIM5 �ж�    �ڶ�λ 1 ��ʾ ��һ��
 *												   ����λ 0  ��ռ���ȼ� 0 λ   ����λ 0 �����ȼ� 0 λ
 *
 *			 TIM_Init(TIM5,10000-1,7200-1);		   һ���Ӳ���һ���ж�
 *           TIMER_NVIC_Configuration(5 ,1,0,0);
 */

void TIM_Timing_Init(TIM_TypeDef* TIMER,u16 T);
/*
 *			 TIM_Timing_Init(TIM2,36000);
 */
void TIM_OC_Timing_Init(TIM_TypeDef* TIMER,u8 OC,u16 CCR_Val);
/*												  TIMER_NVIC_Configuration(2 ,1,0,0);
 *												  TIM_Timing_Init(TIM2,36000);		    TIM2  yufenping 36000    36M/36000=1000Hz
 *           TIM_OC_Timing_Init(TIM2,1,250 );	  TIM_OC_Timing_Init(TIM2,1,250 );		pinlv 250/1000=0.25 
 *	         TIM_OC_Timing_Init(TIM2,2,500 );	  TIM_OC_Timing_Init(TIM2,2,500 );		500/1000=0.5
 *	         TIM_OC_Timing_Init(TIM2,3,1000);	  TIM_OC_Timing_Init(TIM2,3,1000);
 *	         TIM_OC_Timing_Init(TIM2,4,1500);	  TIM_OC_Timing_Init(TIM2,4,1500);
 */

#endif
