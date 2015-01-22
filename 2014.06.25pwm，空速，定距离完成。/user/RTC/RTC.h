#ifndef _RTC_H
#define _RTC_H

#include "stm32f10x.h"
#include "date.h"
#include <stdio.h>

extern u8 TimeDisplay;
extern u8 RTC_Alarm_Mode;
extern u8 RTC_Alarm_Yue;
extern u8 RTC_Alarm_Ri;
extern u8 RTC_Alarm_Shi;
extern u8 RTC_Alarm_Fen;
extern u8 RTC_Alarm_Miao;
extern u8 RTC_Alarm_Time;

void RTC_init(u16 year,u8 mon,u8 mday,u8 hour,u8 min,u8 sec);
void RTC_Configuration(void);    
void Time_Regulate(struct rtc_time *tm,u16 year,u8 mon,u8 mday,u8 hour,u8 min,u8 sec);
void Time_Adjust(u16 year,u8 mon,u8 mday,u8 hour,u8 min,u8 sec);						//申明时钟初始化函数
void Get_Time(u16 *nian,u8 *yue,u8 *ri,u8 *xingqi,u8 *shi,u8 *fen,u8 *miao,u8 mode);	
void RTC_NVIC_Configuration(u8 PriorityGroup,u8 PreemptionPriority,u8 SubPriority);					//申明时钟初始化函数
void Set_Alarm_Clock(u8 yue,u8 ri,u8 shi,u8 fen,u8 miao,u8 mode,u8 time);
void Printf_Time(void);
#endif
