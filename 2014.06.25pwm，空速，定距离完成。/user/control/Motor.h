#ifndef __MOTOR_H
#define __MOTOR_H 

#include "stm32f10x.h"
#include "CC1101.h"
#include "delay.h"
#include "PWM.h"
#include "eeprom.h"
#include "GPIO.h"
#include <stdio.h>
#include <math.h>

#define Motor1_PWM(x)  Change_TIM5_OC1_Pulse(x) // PA0
#define Motor2_PWM(x)  Change_TIM8_OC1_Pulse(x/2) // PC6
#define Motor3_PWM(x)  Change_TIM8_OC2_Pulse(x) // PC7
#define Motor4_PWM(x)  Change_TIM5_OC2_Pulse(x) // PA1

extern u16 speed1;
extern u16 PM1;
extern u16 PM2;
extern u16 PM3;
extern u16 PM4;
extern u16 PMM;
extern u16 MinPWM;
extern u16 MaxPWM;
extern u8  MON;
extern u16 MaxMM;

/* 角度数据 */
extern float angx;
extern float comx;
extern float qx;
extern float angy;
extern float comy;
extern float qy;
extern float qz;
/*  期望角度 */
extern float AngX;
extern float AngY;
extern float AngZ;


extern u16 A;
extern u16 B;
extern u16 C;


void Motor_PWM(u16 p1,u16 p2,u16 p3,u16 p4);
void Adjust_Motor(float AngX,float AngY,float AngZ);



#endif
