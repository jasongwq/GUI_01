#include "stm32f10x.h"
#ifndef __PWM_H
#define __PWM_H 

//频率计算  ： 72M / Prescaler / Period 		  
//													   TIM8_PWM_init(36,40000,1,1,1,0); 频率= 72M /36 /40000 =50 Hz
//													   TIM8_PWM_init(1,3600,1,1,1,0); 频率= 72M /1 /3600 =20 KHz
//输出占空比计算公式：TIM_Pulse /  Period  * 100%


void TIM1_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
/*
 *	 TIM1_PWM_init(1,1,1,0);	PA8 PA9 PA10 PA11	  初始化了前三个通道
 */
void TIM1_Change_Period(u16 NoteSet);
void Change_TIM1_OC1_Pulse(u16 Pulse);
void Change_TIM1_OC2_Pulse(u16 Pulse);
void Change_TIM1_OC3_Pulse(u16 Pulse);
void Change_TIM1_OC4_Pulse(u16 Pulse);
void Change_TIM1_OC1_Polarity(u8 i);
void Change_TIM1_OC2_Polarity(u8 i);
void Change_TIM1_OC3_Polarity(u8 i);
void Change_TIM1_OC4_Polarity(u8 i);


void TIM2_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
/*
 *	 TIM2_PWM_init(1,1,1,0);	PA0 PA1 PA2 PA3	  初始化了前三个通道
 */
void TIM2_Change_Period(u16 NoteSet);
void Change_TIM2_OC1_Pulse(u16 Pulse);
void Change_TIM2_OC2_Pulse(u16 Pulse);
void Change_TIM2_OC3_Pulse(u16 Pulse);
void Change_TIM2_OC4_Pulse(u16 Pulse);
void Change_TIM2_OC1_Polarity(u8 i);
void Change_TIM2_OC2_Polarity(u8 i);
void Change_TIM2_OC3_Polarity(u8 i);
void Change_TIM2_OC4_Polarity(u8 i);


void TIM3_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
/*
 *	 TIM3_PWM_init(1,1,1,0);	PA6 PA7 PB0 PB1	  初始化了前三个通道
 */
void TIM3_Change_Period(u16 NoteSet);
void Change_TIM3_OC1_Pulse(u16 Pulse);
void Change_TIM3_OC2_Pulse(u16 Pulse);
void Change_TIM3_OC3_Pulse(u16 Pulse);
void Change_TIM3_OC4_Pulse(u16 Pulse);
void Change_TIM3_OC1_Polarity(u8 i);
void Change_TIM3_OC2_Polarity(u8 i);
void Change_TIM3_OC3_Polarity(u8 i);
void Change_TIM3_OC4_Polarity(u8 i);


void TIM4_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
/*
 *	 TIM4_PWM_init(1,1,1,0);	PB6 PB7 PB8 PB9	  初始化了前三个通道
 */
void TIM4_Change_Period(u16 NoteSet);
void Change_TIM4_OC1_Pulse(u16 Pulse);
void Change_TIM4_OC2_Pulse(u16 Pulse);
void Change_TIM4_OC3_Pulse(u16 Pulse);
void Change_TIM4_OC4_Pulse(u16 Pulse);
void Change_TIM4_OC1_Polarity(u8 i);
void Change_TIM4_OC2_Polarity(u8 i);
void Change_TIM4_OC3_Polarity(u8 i);
void Change_TIM4_OC4_Polarity(u8 i);


void TIM5_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
/*
 *	 TIM5_PWM_init(1,1,1,0);	PA0 PA1 PA2 PA3	  初始化了前三个通道
 */
void TIM5_Change_Period(u16 NoteSet);
void Change_TIM5_OC1_Pulse(u16 Pulse);
void Change_TIM5_OC2_Pulse(u16 Pulse);
void Change_TIM5_OC3_Pulse(u16 Pulse);
void Change_TIM5_OC4_Pulse(u16 Pulse);
void Change_TIM5_OC1_Polarity(u8 i);
void Change_TIM5_OC2_Polarity(u8 i);
void Change_TIM5_OC3_Polarity(u8 i);
void Change_TIM5_OC4_Polarity(u8 i);

void TIM8_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4);
/*
 *	 TIM8_PWM_init(36,40000,1,1,1,0);	PC6 PC7 PC8 PC9	  初始化了前三个通道	
 */
void TIM8_Change_Period(u16 NoteSet);
/*
 *	 TIM8_Change_Period(9999);	设置计数器溢出后的重载初值 
 */
void Change_TIM8_OC1_Pulse(u16 Pulse);					   //	  TIM5_Change_Period(999);
void Change_TIM8_OC2_Pulse(u16 Pulse);					   //	  Change_TIM5_OC1_Pulse(800);	 占空比为80%   频率为 72  KHz
void Change_TIM8_OC3_Pulse(u16 Pulse);					   //	  TIM5_Change_Period(9999);
void Change_TIM8_OC4_Pulse(u16 Pulse);					   //	  Change_TIM5_OC1_Pulse(8000);	 占空比为80%   频率为 7.2 KHz
void Change_TIM8_OC1_Polarity(u8 i);
void Change_TIM8_OC2_Polarity(u8 i);
void Change_TIM8_OC3_Polarity(u8 i);
void Change_TIM8_OC4_Polarity(u8 i);

#endif
