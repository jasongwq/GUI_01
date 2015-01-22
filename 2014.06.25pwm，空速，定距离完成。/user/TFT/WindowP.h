
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
	 float tx;        // 显示的数字
	 u8 txnum;
	 u16 txcolour;    // 字体颜色
	 u8  tic;         // 更新多少个像素点 更新一次显示
	 u8  nowtic;      // 配合上一个参数用
	 int p0[130];
	 int p1[130];
   u16 colourback;  // 背景颜色  
	 u16 colour;      // 曲线颜色
	 u16  Max_y;      // 最大纵坐标   
}My_WindowP;         


u8 Creat_PWindow(u16 x0,u16 y0,u16 lenth,u16 wide,u8 *name,u16 txcolour,u8 txnum,u8  tic,u16 colourback,u16 colour,u16  Max_y,u8 N);
void Drow_PWindow(u8 N);
void Updat_PWin(int x1,int x2,u8 mode,u8 N);


#endif
