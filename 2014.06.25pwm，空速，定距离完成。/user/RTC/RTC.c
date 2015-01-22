#include "RTC.h"

struct rtc_time systmtime;
u8 TimeDisplay = 0;

u8 RTC_Alarm_Sign=0;
u8 RTC_Alarm_Mode=0;	// 警报模式
u8 RTC_Alarm_Yue=23;
u8 RTC_Alarm_Ri=23;
u8 RTC_Alarm_Shi=23;
u8 RTC_Alarm_Fen=23;
u8 RTC_Alarm_Miao=23;	// 
u8 RTC_Alarm_Time=10;	// 警报时间

void RTC_init(u16 year,u8 mon,u8 mday,u8 hour,u8 min,u8 sec)
{
	if(BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		RTC_Configuration();
		Time_Adjust(year,mon,mday,hour,min,sec);
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);    
	}
	else
	{
		if(RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET){}
		else if(RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET){}
		RTC_WaitForSynchro(); 
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		RTC_WaitForLastTask();
	}
	RCC_ClearFlag();
}

/*  RTC配置 */
void RTC_Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE); 
	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSEConfig(RCC_LSE_ON);
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);  
	RCC_RTCCLKCmd(ENABLE); 
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	RTC_WaitForLastTask();
	RTC_SetPrescaler(32767);
	RTC_WaitForLastTask();
}

/*  设置初始化时间 */
void Time_Regulate(struct rtc_time *tm,u16 year,u8 mon,u8 mday,u8 hour,u8 min,u8 sec)
{
	tm->tm_year = year;                           
	tm->tm_mon= mon;                          
	tm->tm_mday= mday;
	tm->tm_hour= hour;
	tm->tm_min= min;
	tm->tm_sec= sec;
}
/*  调整时间  */
void Time_Adjust(u16 year,u8 mon,u8 mday,u8 hour,u8 min,u8 sec)
{ 
	RTC_WaitForLastTask();
	Time_Regulate(&systmtime,year,mon,mday,hour,min,sec);
	GregorianDay(&systmtime);
	RTC_SetCounter(mktimev(&systmtime));
	RTC_WaitForLastTask();
}

/*  获得当前时间 */
void Get_Time(u16 *nian,u8 *yue,u8 *ri,u8 *xingqi,u8 *shi,u8 *fen,u8 *miao,u8 mode)
{                  
	//to_tm(RTC_GetCounter(), &systmtime);
	if(mode==0)
	{
		nian[0]=systmtime.tm_year/1000+'0';
		nian[1]=systmtime.tm_year%1000/100+'0';
		nian[2]=systmtime.tm_year%1000%100/10+'0';
		nian[3]=systmtime.tm_year%1000%100%10+'0';
		nian[4]='\0'; 		
		yue[0]=systmtime.tm_mon/10+'0';
		yue[1]=systmtime.tm_mon%10+'0';
		yue[2]='\0';			
		ri[0]=systmtime.tm_mday/10+'0';
		ri[1]=systmtime.tm_mday%10+'0';
		ri[2]='\0';	
		xingqi[0]=systmtime.tm_wday+'0';
		xingqi[1]='\0';		
		shi[0]=systmtime.tm_hour/10+'0';
		shi[1]=systmtime.tm_hour%10+'0';
		shi[2]='\0';		
		fen[0]=systmtime.tm_min/10+'0';
		fen[1]=systmtime.tm_min%10+'0';
		fen[2]='\0';		
		miao[0]=systmtime.tm_sec/10+'0';
		miao[1]=systmtime.tm_sec%10+'0';
		miao[2]='\0';
	}   
	else if(mode==1)
	{
		 *nian=systmtime.tm_year;
		 *yue=systmtime.tm_mon;
		 *ri=systmtime.tm_mday;
		 *xingqi=systmtime.tm_wday;
		 *shi=systmtime.tm_hour;
		 *fen=systmtime.tm_min;
		 *miao=systmtime.tm_sec;
	}
}
void RTC_NVIC_Configuration(u8 PriorityGroup,u8 PreemptionPriority,u8 SubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure;

    if(PriorityGroup==0)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	else if(PriorityGroup==1)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	else if(PriorityGroup==2)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	else if(PriorityGroup==3)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	else if(PriorityGroup==4)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	else {}
 
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    if(PreemptionPriority!=0)NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/*  RTC中断函数 */
void RTC_IRQHandler(void)
{
	static u8 alarm_time=0;

	if(RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		RTC_ClearITPendingBit(RTC_IT_SEC);
		
		TimeDisplay = 1;
		RTC_WaitForLastTask();

		to_tm(RTC_GetCounter(), &systmtime);          // 获得当前的时间
		if(RTC_Alarm_Mode==0){}					      // 不报警
		else if(RTC_Alarm_Mode==1 && !RTC_Alarm_Sign) // 年月日报警 
		{
			if(RTC_Alarm_Yue ==systmtime.tm_mon  &&
			   RTC_Alarm_Ri  ==systmtime.tm_mday &&
			   RTC_Alarm_Shi ==systmtime.tm_hour &&
			   RTC_Alarm_Fen ==systmtime.tm_min  &&
			   RTC_Alarm_Miao==systmtime.tm_sec
			   )
			 RTC_Alarm_Sign=1;
		}
		else if(RTC_Alarm_Mode==2 && !RTC_Alarm_Sign) // 时分秒报警
		{
			if(RTC_Alarm_Shi ==systmtime.tm_hour &&
			   RTC_Alarm_Fen ==systmtime.tm_min  &&
			   RTC_Alarm_Miao==systmtime.tm_sec
			   )
			 RTC_Alarm_Sign=1;
		}
		else {}
		if(RTC_Alarm_Sign)
		{
			if(alarm_time<RTC_Alarm_Time)alarm_time++;
			else {RTC_Alarm_Sign=0;alarm_time=0;}
			printf("In_Alarm_\r\n");
		}

		if(RTC_GetCounter() %86400L== 75060)
		{
		//GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)0x01);
		}
		if(RTC_GetCounter() == 0x00015180)		           // 23:59:59
		{
			RTC_SetCounter(0x0);
			RTC_WaitForLastTask();
		}	
	}
}
/*  设置闹钟  */
void Set_Alarm_Clock(u8 yue,u8 ri,u8 shi,u8 fen,u8 miao,u8 mode,u8 time)
{	
	RTC_Alarm_Mode=mode;
	RTC_Alarm_Yue=yue;
	RTC_Alarm_Ri=ri;
	RTC_Alarm_Shi=shi;
	RTC_Alarm_Fen=fen;
	RTC_Alarm_Miao=miao;
	RTC_Alarm_Time=time;
}
void Printf_Time(void)
{
	u16 nian;
	u8 yue,ri,xingqi,shi,fen,miao;

	if(TimeDisplay==1)
	{
		TimeDisplay = 0;
		Get_Time(&nian,&yue,&ri,&xingqi,&shi,&fen,&miao,1);
		printf("  %d %d %d %d   %d:%d:%d\r\n",nian,yue,ri,xingqi,shi,fen,miao);
	}else {}
}
