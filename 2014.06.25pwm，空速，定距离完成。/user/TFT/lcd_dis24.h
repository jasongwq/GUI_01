#ifndef __LCD_DIS24_H
#define __LCD_DIS24_H

#include "stm32f10x.h"
#include "FSMC_TFT.h"
#include "GPIO.h"

extern const unsigned char asc2_1206[95][12];


#define BL_Init      PC0_OUT// ±≥π‚≥ı ºªØ
#define Rest_Init    PE6_OUT

#define Set_BL       Set_C0
#define Clr_BL       Clr_C0
#define Set_Rest     Set_E6
#define Clr_Rest     Clr_E6
    

void LCD_Init(void);
void LCD_WR_Data(unsigned int val);
void TFT_Window(u16 x,u16 y,u16 lenth,u16 wide) ;
void TFT_CLEAR(u16 x,u16 y,u16 len,u16 wid,u16 z);
void TFT_DrawPoint(u16 x,u16 y,u16 z);
u32  TFT_GetPoint(u16 x,u16 y);
void TFT_ShowBmp(u16 x,u16 y,u16 lenth,u16 wide,const u8 *p,u32 n);


#endif
