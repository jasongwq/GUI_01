#ifndef __TFT_M_H
#define __TFT_M_H 

#include "stm32f10x.h"
#include "TFT_Show.h"
#include "BMP.h"
#include "XPT2046.h"
#include "Slider.h"
#include "button.h"
#include "Window.h"
#include "WindowP.h"
#include "MPU6050.h"
#include "Motor.h"
#include <stdio.h>

extern u32 leng;
extern u16 PWM4;
extern u8 Menu_Sign;
extern u8 Menu_Step;

extern u8 ShowMode;
/* 显示图形参数 */
extern u8 ShowMode;
extern u8 stic;
extern int picda_0[120];
extern int picda_1[120];
/* 角度数据 */
extern float angx;
extern float comx;
extern float qx;
extern float angy;
extern float comy;
extern float qy;
extern float qz;
/* 电机的PWM */
extern u16 PM1;
extern u16 PM2;
extern u16 PM3;
extern u16 PM4;
extern u16 PMM;
extern u16 MaxMM;
extern u16 MinPWM;
extern u16 MaxPWM;
extern u8  MON;

extern float AngX;
extern float AngY;
extern float AngZ;

extern u8  AdAng;


void TFT_Touch_Deal(u16 x,u16 y);
void M_S0(void);

void Creat_All(void);
void M1_S1_P(void);
void M1_S2_P(void);
void M1_S3_P(void);
void M1_S4_P(void);
void M1_S1(u16 x,u16 y);
void M1_S2(u16 x,u16 y);
void M1_S3(u16 x,u16 y);
void M1_S4(u16 x,u16 y);

void M1_S2_m00(void);
void M1_S2_m0(void); 

#endif
