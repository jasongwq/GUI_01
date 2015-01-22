#ifndef __PWM_COMP_H
#define __PWM_COMP_H 

#include "stm32f10x.h"
#include "PWM.h"

/*
	TIM1
	  B13    A8
		B14    A9
		B15    A10
		Break  B12	  刹车控制
	TIM8	
		C6     A7
		C7     B0
		C8     B1
		Break  A6	  刹车控制

		TIM1_Init(1,40000,0,1,1,10,1);     // 开启了后面两个互补通道  死区时间为10  开启刹车控制 低电平输入有效 并有中断
		TIMER_NVIC_Configuration(12,1,0,0);// 为TIM1的刹车中断设置中断分组  中断在void TIM1_BRK_IRQHandler(void)里面

		while(1)
        { 
			printf(" %s, k= %d\t\n",RxBuffer2,k);
			k=(RxBuffer2[0]-'0')*10000+(RxBuffer2[1]-'0')*1000+(RxBuffer2[2]-'0')*100+(RxBuffer2[3]-'0')*10+(RxBuffer2[4]-'0');
			RxCounter2=0;
			TIM1_OC2_Pulse(1,1,k);
			TIM1_OC3_Pulse(1,1,k);
			delay_ms(300);
        }

 */



void TIM1_Init(u16 Prescaler,u16 Period,u8 OC1,u8 OC2,u8 OC3,u8 DeadTime,u8 Open);

void TIM1_OC1_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);
/*	   
	  TIM1_Init(1,10000,1,0,0,100,0);		 1->第一次分频  10000->第二次分频  1->OC1 开  0->OC2 关	 0->OC3 关  100->死区时间 0-> 刹车控制关闭

	  TIM1_OC1_Pulse(1,1,k);   	B13 A8   1-> + 占空比  1-> - 占空比
	  TIM1_OC2_Pulse(1,1,k);   	B14 A9   1-> + 占空比  1-> - 占空比 
	  TIM1_OC3_Pulse(1,1,k);   	B15 A10  1-> + 占空比  1-> - 占空比 
 */
void TIM1_OC2_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);
void TIM1_OC3_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);

//										   PA8    PB13    PA9    PB14    PA10   PB15
void TIM1_OC_Init(u16 Prescaler,u16 Period,u8 OC1,u8 OCN1,u8 OC2,u8 OCN2,u8 OC3,u8 OCN3);

/*			   TIM1_OC_Init(1,40000,1,0,0,0,0,1);     //   OCx 和 OCNx  不可以同时打开
			   TIM1_OC1_Pulse(1,0,k);

 */



void TIM8_Init(u16 Prescaler,u16 Period,u8 OC1,u8 OC2,u8 OC3,u8 DeadTime,u8 Open);

void TIM8_OC1_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);
/*	   
	  TIM8_Init(1,10000,1,0,0,100,1);		 1->第一次分频  10000->第二次分频  1->OC1 开  0->OC2 关	 0->OC3 关  100->死区时间

	  TIM8_OC1_Pulse(1,1,k);   	C6 A7   1-> + 占空比  1-> - 占空比
	  TIM8_OC2_Pulse(1,1,k);   	C7 B0   1-> + 占空比  1-> - 占空比 
	  TIM8_OC3_Pulse(1,1,k);   	C8 B1  1-> + 占空比  1-> - 占空比 
 */
void TIM8_OC2_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);
void TIM8_OC3_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse);

//										   PC6    PC7    PC8    PA7    PB0   PB1
void TIM8_OC_Init(u16 Prescaler,u16 Period,u8 OC1,u8 OCN1,u8 OC2,u8 OCN2,u8 OC3,u8 OCN3);

/*			   TIM8_OC_Init(1,40000,1,0,0,0,0,1);     //   OCx 和 OCNx  不可以同时打开
			   TIM8_OC1_Pulse(1,0,k);

 */


#endif
