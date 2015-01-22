
#ifndef __WINDOWP_H
#define __WINDOWP_H 

#include "stm32f10x.h"
#include "TFT_Show.h"
#include "delay.h"
#include "XPT2046.h"
#include <stdio.h>


typedef struct
{
   u16 x0;     
	 u16 y0;     
	 u16 lenth; 
	 u16 wide;
	 u8  Name[20];    //
	 float tx;        // ��ʾ������
	 u8 txnum;
	 u16 txcolour;    // ������ɫ
	 u8  tic;         // ���¶��ٸ����ص� ����һ����ʾ
	 u8  nowtic;      // �����һ��������
	 int p0[130];
	 int p1[130];
   u16 colourback;  // ������ɫ  
	 u16 colour;      // ������ɫ
	 u16  Max_y;      // ���������   
}My_WindowP;         


u8 Creat_PWindow(u16 x0,u16 y0,u16 lenth,u16 wide,u8 *name,u16 txcolour,u8 txnum,u8  tic,u16 colourback,u16 colour,u16  Max_y,u8 N);
void Drow_PWindow(u8 N);
void Updat_PWin(int x1,int x2,u8 mode,u8 N);


#endif
