
#ifndef __BUTTON_H
#define __BUTTON_H 


#include "stm32f10x.h"
#include "TFT_Show.h"
#include "XPT2046.h"
#include "delay.h"

typedef struct
{
   u16  x0;        // 
	 u16  y0;        //
	 u8   name[4];
	 u16  startdat; //
	 u16  enddat;   //
	 u16  datnow;   //
	 u8   step;   // 
}Button_0;

typedef struct
{
   u16 x0;       // 
	 u16 y0;       //
	 u16 colour;   //
	 u8  Name[4];  // 
	 u8  startdat; //
	 u8  enddat;   //
	 u8  datnow;   //
	 u8  LastDat;  // 
}Button_1;

typedef struct
{
   u16 x0;       // 
	 u16 y0;       //
	 u16 colour0;  //
	 u8  Name0[6]; // 
	 u16 colour1;  //
	 u8  Name1[6]; // 
	 u8  datnow;   // 
}Button_2;

typedef struct
{
   u16 x0;       // 
	 u16 y0;       //
	 u16 lenth;
	 u16 wide;
	 u16 colour0;  //
	 u8  Name0[7]; // 
	 u16 colour1;  //
	 u8  Name1[7]; // 
}Button_3;


u8 Creat_Buuton_0(u16 x0,u16 y0,u8 *name,u16 startdat,u16 enddat,u16 datnow,u8 step,u8 N);
void Dorw_But0(u8 N);
void But0_Updat(u16 dat,u8 N);
u16 But0_Deal(u16 x,u16 y,u8 N);

u8 Creat_Buuton_1(u16 x0,u16 y0,u16 colour,u8 *name,u8 startdat,u8 enddat,u8 datnow,u8 N);
void Dorw_But1(u8 N);
u8 But1_Deal(u16 x,u16 y,u8 N);

u8 Creat_Buuton_2(u16 x0,u16 y0,u16 colour0,u8 *name0,u16 colour1,u8 *name1,u8 datnow,u8 N);
void Dorw_But2(u8 N);
u8 But2_Deal(u16 x,u16 y,u8 N);

u8 Creat_Buuton_3(u16 x0,u16 y0,u16 lenth,u16 wide,u16 colour0,u8 *name0,u16 colour1,u8 *name1,u8 N);
void Dorw_But3(u8 N);
u8 But3_Deal(u16 x,u16 y,u8 N);

#endif
