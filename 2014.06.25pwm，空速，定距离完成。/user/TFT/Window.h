
#ifndef __WINDOW_H
#define __WINDOW_H 

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
   u16 colourback;  //	  
	 u16 colour;      // 
	 u8  Str[300];    
	 u16 zx;          //当前字在窗口内的横个数
	 u16 zy;          //当前字在窗口内的列数
	 u16 zl;          //
	 u16 zn;          // 第一个位置显示第几个字
	 u16 location;    // 光标位置
	 u8  sign;        // 
}My_Window;         

u8 Adjust_Window(u16 x,u16 y,u8 N);
u8 Creat_Window(u16 x0,u16 y0,u16 lenth,u16 wide,u8 *name,u16 colourback,u16 colour,u8 N);
void Drow_Window(u8 N);
void Show_Win_Str(u8 N);
void Win_Str(u8 N,u8 *p);
void Win_Str_0(u16 x0,u16 y0,u16 lenth,u16 wide,u8 *p,u8 N);

#endif
