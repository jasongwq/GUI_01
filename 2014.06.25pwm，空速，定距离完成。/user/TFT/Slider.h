#ifndef __SLIDER_H
#define __SLIDER_H    		 

#include "stm32f10x.h"
#include "TFT_Show.h"

typedef struct
{
   u16 x0;      // �����������Ͻǵ�xֵ
	 u16 y0;      // �����������Ͻǵ�yֵ
	 u16 lenth;   // ����������
	 u16 wide;    // ���������
	 u16 startdat;// ��ʼ����
	 u16 enddat;  // �������
	 u16 datnow;  // ��ǰ����
	 u16 Lastx0;  // ��һ�ε������x����
}Slider;

/*
       ����һ����������Creat_Sq(20,100,150,20,0,50,0);
       ����һ����������Adjust_Slider(x,y,0);
       �������ʱ�� Ҫ�õ�  Dorw_Slider(u8 N); ���»�������
*/

u32 Adjust_Slider(u16 x,u16 y,u8 N);                                        //  �ж�  x ��Χ����������
u8 Creat_Sq(u16 x0,u16 y0,u16 lenth,u16 wide,u16 startdat,u16 datnow,u16 enddat,u8 N); //  ����һ�������� 
void Dorw_Slider(u8 N);                                                     // ��һ�������� 
void Slider_Updat(u16 dat,u8 N);
void Dorw_S(u8 N,u16 j,u32 *dat);                                           // ������������λ�� 

#endif
