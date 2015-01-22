#ifndef __TFT_SHOW_H
#define __TFT_SHOW_H 

#include "stm32f10x.h"
#include "lcd_dis24.h"
#include <stdio.h>

void My_TFT_WR_Data(u32 dat);
void My_Dorw_Point(u16 x,u16 y,u16 z);
void My_TFT_Sq(u16 x,u16 y,u16 len,u16 wid,u16 z);
void TFT_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2 ,u16 z);
void TFT_ShowChar(u16 x,u16 y,u8 num,u16 z,u16 l);                        // 显示字符     带背景颜色
void TFT_SwCr_0(u16 x,u16 y,u8 num,u16 z,u16 l,u8 start,u8 end,u8 mode);
void TFT_ShStri(u16 x,u16 y,const u8 *p,u8 start,u8 end,u16 z);
void TFT_ShowChar1(u16 x,u16 y,u8 num,u16 z);                             // 显示字符     不带背景颜色
void TFT_ShowString(u16 x,u16 y,const u8 *p,u16 z,u16 l);                 // 显示字符串   带背景颜色
void TFT_ShowString1(u16 x,u16 y,const u8 *p,u16 z);                      // 显示字符串   不带背景颜色
void TFT_Show_Num(u16 x,u16 y,u32 date,u8 num,u16 z,u16 l);               // 显示数字     带窗口
void TFT_Show_Num1(u16 x,u16 y,u32 date,u8 win,u16 z);
void TFT_Show_Float(u16 x,u16 y,u32 date,u8 n,u8 win,u16 z,u16 l);        // 模拟显示小数 带窗口
void TFT_Show_Float1(u16 x,u16 y,   u32 date,u8 n,   u8 win, u16 z);
void TFT_Show_Float2(u16 x,u16 y,float fdat,u8 n, u8 win, u16 z);
void TFT_Chinese_1612(u16 x,u16 y,const u8 (*p)[24] ,u8 num,u16 z,u16 l,u8 mode);  // 显示中文
void TFT_Chin_16120(u16 x,u16 y,const u8 (*p)[24] ,u8 n,u16 z,u16 l);
void TFT_Chin_16121(u16 x,u16 y,const u8 (*p)[24] ,u8 n,u16 z);


void TFT_Sq_Chin_1612(u16 x,u16 y,u16 len,u16 wid,const u8 (*p)[24] ,u8 n,u16 z,u16 l); // 矩形区域内居中显示 中文
void TFT_Sq_Str(u16 x,u16 y,u16 len,u16 wid,u8 *p ,u16 z,u16 l);                        // 矩形区域内居中显示 字符串              
void TFT_Sq_Num(u16 x,u16 y,u16 len,u16 wid,u32 date,u8 win,u16 z,u16 l);               // 矩形区域内居中显示 数字
void TFT_Sq_Float(u16 x,u16 y,u16 len,u16 wid,u32 date,u8 m,u8 win,u16 z,u16 l);        // 矩形区域内居中显示 小数
void TFT_Sq_Float1(u16 x,u16 y,u16 len,u16 wid,float fdat,u8 n,u8 win,u16 z,u16 l);
u8 In_Sq(u16 x,u16 y,u16 x0,u16 y0,u16 length ,u16 wide);

#endif
