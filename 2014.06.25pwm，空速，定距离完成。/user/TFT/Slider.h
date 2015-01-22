#ifndef __SLIDER_H
#define __SLIDER_H    		 

#include "stm32f10x.h"
#include "TFT_Show.h"

typedef struct
{
   u16 x0;      // 滑动条最左上角的x值
	 u16 y0;      // 滑动条最左上角的y值
	 u16 lenth;   // 滑动条长度
	 u16 wide;    // 滑动条宽度
	 u16 startdat;// 起始数据
	 u16 enddat;  // 最大数据
	 u16 datnow;  // 当前数据
	 u16 Lastx0;  // 上一次调整后的x坐标
}Slider;

/*
       创建一个滑动条：Creat_Sq(20,100,150,20,0,50,0);
       调整一个滑动条：Adjust_Slider(x,y,0);
       多层界面的时候 要用到  Dorw_Slider(u8 N); 重新画滑动条
*/

u32 Adjust_Slider(u16 x,u16 y,u8 N);                                        //  判断  x 范围调整滑动条
u8 Creat_Sq(u16 x0,u16 y0,u16 lenth,u16 wide,u16 startdat,u16 datnow,u16 enddat,u8 N); //  创建一个滑动条 
void Dorw_Slider(u8 N);                                                     // 话一个滑动条 
void Slider_Updat(u16 dat,u8 N);
void Dorw_S(u8 N,u16 j,u32 *dat);                                           // 调整滑动条的位置 

#endif
