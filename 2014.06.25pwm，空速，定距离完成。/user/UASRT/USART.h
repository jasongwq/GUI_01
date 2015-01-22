#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>


#define Print_USART USART1

#define USE_USART1
//#define USE_USART2
//#define USE_USART3
//#define USE_UART4
//#define USE_UART5

/*				TX       RX
   USART1	  PA9		 PA10
	 USART2		PD5		 PD6
	 USART3		PB10     PB11
	 UART4		PC10     PC11
	 UART5		PC12     PD2

extern u8 RxCounter1;
extern u8 RxBuffer1[100];
extern u8 RxCounter2;
extern u8 RxBuffer2[100];
extern u8 RxCounter3;
extern u8 RxBuffer3[100];
extern u8 RxCounter4;
extern u8 RxBuffer4[100];
extern u8 RxCounter5;
extern u8 RxBuffer5[100];

 */
#ifdef USE_USART1
extern u8 RxCounter1;
extern u8 RxBuffer1[100];
#endif
#ifdef USE_USART2
extern u8 RxCounter2;
extern u8 RxBuffer2[100];
#endif
#ifdef USE_USART3
extern u8 RxCounter3;
extern u8 RxBuffer3[100];
#endif
#ifdef USE_UART4
extern u8 RxCounter4;
extern u8 RxBuffer4[100];
#endif
#ifdef USE_UART5
extern u8 RxCounter5;
extern u8 RxBuffer5[100];
#endif



#endif 
void USART_NVIC_Configuration(u8 USART ,u8 PriorityGroup,u8 PreemptionPriority,u8 SubPriority);
/*
 *	 USART_NVIC_Configuration(1 ,1,0,2);   ��һλ 1 ��USART1_IRQn         �ڶ�λ 1 ��ʾ�жϷ���1 
 *                                          ����λ 0 ��ʾ��ռ���ȼ� 0λ    ����λ 2 ��ʾ�����ȼ� 2λ
 */
void USART1_Configuration(u32 BaudRate);
void USART2_Configuration(u32 BaudRate);
void USART3_Configuration(u32 BaudRate);
void USART4_Configuration(u32 BaudRate);
void USART5_Configuration(u32 BaudRate);

void Send_ASCII(u8 USART , u8 *b);
void Send_Hex(u8 USART,u8 c);
void Send_USART_Hex(u8 USART,u8 *b,u8 i);
