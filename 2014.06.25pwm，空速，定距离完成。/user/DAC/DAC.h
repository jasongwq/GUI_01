#include "stm32f10x.h"
#ifndef __DAC_H
#define __DAC_H 
			   
void DAC1_Init(u16 digital);   //PA4		  ×î¸ßÎ» 4095-3.3V 
void DAC2_Init(u16 digital);   //PA5  
void Set_DAC1(u16 digital);
void Set_DAC2(u16 digital);

#endif
