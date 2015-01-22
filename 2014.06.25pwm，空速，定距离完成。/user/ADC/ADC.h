#include "stm32f10x.h"
#ifndef __ADC_H
#define __ADC_H 

/*
	 ADC_init(10);ADC_init(0);ADC_init(1);	   //初始化 10  0  1 通道

     0x0001		 PA0	   0
	 0x0002		 PA1	   1
	 0x0004		 PA2	   2
	 0x0008		 PA3	   3
	 0x0010		 PA4	   4
	 0x0020		 PA5	   5
	 0x0040		 PA6	   6
	 0x0080		 PA7	   7
	 0x0100		 PB0	   8
	 0x0200		 PB1	   9
	 0x0400		 PC0	   10
	 0x0800		 PC1	   11
	 0x1000		 PC2	   12
	 0x2000		 PC3	   13
	 0x4000		 PC4	   14
	 0x8000		 PC5	   15
*/


void ADC_init(u16 x);
u16 ADC1_Configuration(u16 ADC_Channel,u8 ADC_SampleTime);
u16 ADC2_Configuration(u16 ADC_Channel,u8 SampleTime);
u16 ADC3_Configuration(u16 ADC_Channel,u8 SampleTime);
void Choose_ADC(u8 ADC);
void fx(u8 ADC);
u8 ADC_Time(u8 ADC_SampleTime);

#endif
