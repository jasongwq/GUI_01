#include "TIMER.h"
#include "TIMCap.h"
#include "stm32f10x.h"

#include "MPU6050.h"
#include "Motor.h"


static u16 TIM1_Prescaler,TIM2_Prescaler,TIM3_Prescaler,TIM4_Prescaler,TIM5_Prescaler,TIM8_Prescaler;

u16 frequency0, percent0;
u16 frequency1, percent1;
u16 frequency2, percent2;
u16 frequency3, percent3;

void TIM1_BRK_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Break) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Break); 	    
	 	//printf("\r\n TIM8");
	}
}
void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update); //����жϱ�־λ	    
	 	printf("\r\n TIM1");
	}
}
void TIM1_TRG_COM_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Trigger) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM1,TIM_IT_Trigger); 	    
	 	//printf("\r\n TIM8");
	}
}
void TIM1_CC_IRQHandler(void)
{
	//printf("TIM1\r\n");
	TIM1_CO1_Check(&frequency0,&percent0);
	TIM1_CO2_Check(&frequency1,&percent1);
	TIM1_CO3_Check(&frequency2,&percent2);
	TIM1_CO4_Check(&frequency3,&percent3);
}

//��ʱ��2�жϷ������	 
void TIM2_IRQHandler(void)
{ 
		  
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //����жϱ�־λ	    
	 
	}
	TIM2_CO1_Check(&frequency0,&percent0);
	TIM2_CO2_Check(&frequency1,&percent1);
	TIM2_CO3_Check(&frequency2,&percent2);
	TIM2_CO4_Check(&frequency3,&percent3);			     	    					    	    
}
//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 
		  
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //����жϱ�־λ	    
	 
	}
	TIM3_CO1_Check(&frequency0,&percent0);
	TIM3_CO2_Check(&frequency1,&percent1);
	TIM3_CO3_Check(&frequency2,&percent2);
	TIM3_CO4_Check(&frequency3,&percent3);			     	    					    	    
}
//��ʱ��4�жϷ������	 
void TIM4_IRQHandler(void)
{ 
		  
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //����жϱ�־λ	    
	 
	}
	TIM4_CO1_Check(&frequency0,&percent0);
	TIM4_CO2_Check(&frequency1,&percent1);
	TIM4_CO3_Check(&frequency2,&percent2);
	TIM4_CO4_Check(&frequency3,&percent3);			     	    					    	    
}
//��ʱ��5�жϷ������	

extern u32 leng;
void TIM5_IRQHandler(void)
{ 
		static u16 sum=0; //static u16 t=3000;
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)		 
	{	    
	 	TIM_ClearITPendingBit(TIM5,TIM_IT_Update); //����жϱ�־λ
		sum++;
		leng=sum;
//		if(t>speed1)
//		{
//			t=3000-2*t-10;
//			TIM8_Change_Period(t);
//	  	Change_TIM8_OC1_Pulse(t/2);
//		}
//		if(t<=speed1)
//		{
//			TIM8_Change_Period(speed1);
//			Change_TIM8_OC1_Pulse(speed1/2);
//		}
	  
		
		if(sum>=24)
			{
        
				sum=0;
       // t=3000;			
			  TIM8_PWM_init(72,3000,0,0,0,0);
			  delay_ms(1000);
			  TIM8_PWM_init(72,3000,1,1,0,0);
      }
		
	}
	TIM5_CO1_Check(&frequency0,&percent0);
	TIM5_CO2_Check(&frequency1,&percent1);
	TIM5_CO3_Check(&frequency2,&percent2);
	TIM5_CO4_Check(&frequency3,&percent3);			     	    					    
}
extern u16 timetic;
extern u8 Init_All;
/* �Ƕ����� */
extern float angx;
extern float comx;
extern float qx;
extern float angy;
extern float comy;
extern float qy;
extern float qz;
/* PWM ����*/
extern u16 PM1;
extern u16 PM2;
extern u16 PM3;
extern u16 PM4;
extern u16 MinPWM;
extern u16 MaxPWM;
extern u8  MON;

extern float AngX;
extern float AngY;
extern float AngZ;

//��ʱ��6�жϷ������	 
void TIM6_IRQHandler(void)
{ 		  
	static u16 t0=0;
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update); //����жϱ�־λ		     		        
		if(Init_All)
		{
			  Get_Signs(&angx,&angy,&comx,&comy,&qx,&qy,&qz);
			  Adjust_Motor(AngX,AngY,AngZ);
				if(MON) Motor_PWM(PM1,PM2,PM3,PM4);else Motor_PWM(MinPWM,MinPWM,MinPWM,MinPWM);
	  }else {}
		
    if(t0>=600)
		{
			 printf(" %d\r\n",timetic);
		   timetic=0;
			 t0=0;
    }else t0++;			 	
	}			     	    					    	    
}
//��ʱ��7�жϷ������	 
void TIM7_IRQHandler(void)
{ 		  
	static u16 tic=0;
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM7,TIM_IT_Update); //����жϱ�־λ
		
		//if(Init_All)Get_All_q(&qx,&qy,&qz);else {}
			
		if(tic>400)
	  {
				tic=0;//printf("\r\n TIM7");
	  }else tic++;
			    	 
	}			     	    					    	    
}
//��ʱ��8�жϷ������
void TIM8_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM8,TIM_IT_Update); //����жϱ�־λ	    
	 	printf("\r\n TIM8");
	}
}	 
void TIM8_CC_IRQHandler(void)
{ 	
	//printf("TIM8_In \r\n");
	TIM8_CO1_Check(&frequency0,&percent0);
	TIM8_CO2_Check(&frequency1,&percent1);
	TIM8_CO3_Check(&frequency2,&percent2);
	TIM8_CO4_Check(&frequency3,&percent3);			     	    					    	    
}
void TIM8_TRG_COM_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM8, TIM_IT_Trigger) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM8,TIM_IT_Trigger); 	    
	 	//printf("\r\n TIM8");
	}
}
void TIM8_BRK_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM8, TIM_IT_Break) != RESET)		 
	{
		TIM_ClearITPendingBit(TIM8,TIM_IT_Break); 	    
	 	//printf("\r\n TIM8");
	}
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM1_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM1_ICInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	//����AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//����TIM1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM1_Prescaler=Prescaler;//TIM5_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);				 
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			  //IO�˿ڵĵ�1λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==3)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			  //IO�˿ڵĵ�2λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			  //IO�˿ڵĵ�3λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	
	//��ʼ����ʱ��1 TIM1	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);              //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM2���벶�����
	if(OC==1)TIM1_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	else  if(OC==2)TIM1_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM1_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM1_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //�����ز���
  	TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //���������Ƶ,����Ƶ 
  	TIM1_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM1, &TIM1_ICInitStructure);
	
	//TIM_SelectInputTrigger(TIM1, TIM_TS_TI2FP2);

  /* Select the slave Mode: Reset Mode */
    //TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);

  /* Enable the Master/Slave Mode */
    //TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

	if(OC==1)TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //��������ж� ,����CC1IE�����ж�
	else if(OC==2)TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	
	
   	TIM_Cmd(TIM1,ENABLE ); 	//ʹ�ܶ�ʱ��5
}
/*  ���ڹ���  PWM  ���� Ƶ�� �� ����  ���   */
u8 	TIM1_CO1_Check(u16 *frequency,u16 *percent)		// PA8
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET)//����1���������¼�
	{	
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//��ǲ�����������
			Bas_Val=TIM_GetCapture1(TIM1);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM1_Prescaler/All_Val);
				*percent=Up_Val*1000 / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM1)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM1_CO2_Check(u16 *frequency,u16 *percent)		// PA9
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM1, TIM_IT_CC2) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC2);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture2(TIM1);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM1_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC2PolarityConfig(TIM1,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM1)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM1,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
} 
u8 	TIM1_CO3_Check(u16 *frequency,u16 *percent)		// PA10
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM1, TIM_IT_CC3) != RESET)               //����2���������¼�
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC3);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture3(TIM1);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM1_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC3PolarityConfig(TIM1,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM1)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM1,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM1_CO4_Check(u16 *frequency,u16 *percent)		// PA11
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM1, TIM_IT_CC4) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC4);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture4(TIM1);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM1_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM1)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM2_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM2_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ��TIM5ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��

	TIM2_Prescaler=Prescaler;//TIM5_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			  //IO�˿ڵĵ�6λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);				 //PA0 ����
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			  //IO�˿ڵĵ�1λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==3)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			  //IO�˿ڵĵ�2λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			  //IO�˿ڵĵ�3λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	
	//��ʼ����ʱ��2 TIM2	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);              //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM2���벶�����
	if(OC==1)TIM2_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	else  if(OC==2)TIM2_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM2_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM2_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM2_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //�����ز���
  	TIM2_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM2_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //���������Ƶ,����Ƶ 
  	TIM2_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM2, &TIM2_ICInitStructure);
	
	
	if(OC==1)TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //��������ж� ,����CC1IE�����ж�
	else if(OC==2)TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	
	
   	TIM_Cmd(TIM2,ENABLE ); 	//ʹ�ܶ�ʱ��5
}
/*  ���ڹ���  PWM  ���� Ƶ�� �� ����  ���   */
u8 	TIM2_CO1_Check(u16 *frequency,u16 *percent)		// PA0
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//����1���������¼�
	{	
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//��ǲ�����������
			Bas_Val=TIM_GetCapture1(TIM2);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM2_Prescaler/All_Val);
				*percent=Up_Val*1000 / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM2)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM2_CO2_Check(u16 *frequency,u16 *percent)		// PA1
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture2(TIM2);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM2_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM2)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
} 
u8 	TIM2_CO3_Check(u16 *frequency,u16 *percent)		// PA2
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)               //����2���������¼�
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture3(TIM2);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM2_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM2)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM2_CO4_Check(u16 *frequency,u16 *percent)		// PA3
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture4(TIM2);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM2_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM2)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM3_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM3_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ��TIM3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOAʱ��

	TIM3_Prescaler=Prescaler;//TIM3_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			  //IO�˿ڵĵ�6λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);						 //PA6 ����
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;			  //IO�˿ڵĵ�7λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==3)   //PB0
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			  //IO�˿ڵĵ�8λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	
	//��ʼ����ʱ��3 TIM3	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);              //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM2���벶�����
	if(OC==1)TIM3_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	else  if(OC==2)TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM3_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM3_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //�����ز���
  	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //���������Ƶ,����Ƶ 
  	TIM3_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM3, &TIM3_ICInitStructure);
	
	
	if(OC==1)TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //��������ж� ,����CC1IE�����ж�
	else if(OC==2)TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	
	
   	TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��5
}
/*  ���ڹ���  PWM  ���� Ƶ�� �� ����  ���   */
u8 	TIM3_CO1_Check(u16 *frequency,u16 *percent)		// PA0
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//����1���������¼�
	{	
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//��ǲ�����������
			Bas_Val=TIM_GetCapture1(TIM3);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM3_Prescaler/All_Val);
				*percent=Up_Val*1000 / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM3)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM3_CO2_Check(u16 *frequency,u16 *percent)		// PA1
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture2(TIM3);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM3_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM3)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
} 
u8 	TIM3_CO3_Check(u16 *frequency,u16 *percent)		// PA2
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)               //����2���������¼�
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture3(TIM3);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM3_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM3)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM3_CO4_Check(u16 *frequency,u16 *percent)		// PA3
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM3, TIM_IT_CC4);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture4(TIM3);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM3_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM3)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM4_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM4_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ��TIM3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //ʹ��GPIOAʱ��

	TIM4_Prescaler=Prescaler;//TIM4_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			  //IO�˿ڵĵ�6λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);						 //PB6 ����
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;			  //IO�˿ڵĵ�7λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	else if(OC==3)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			  //IO�˿ڵĵ�8λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			  //IO�˿ڵĵ�8λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	
	//��ʼ����ʱ��4 TIM4	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);              //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM2���벶�����
	if(OC==1)TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	else  if(OC==2)TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //�����ز���
  	TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //���������Ƶ,����Ƶ 
  	TIM4_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM4, &TIM4_ICInitStructure);
	
	
	if(OC==1)TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //��������ж� ,����CC1IE�����ж�
	else if(OC==2)TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	
	
   	TIM_Cmd(TIM4,ENABLE ); 	//ʹ�ܶ�ʱ��5
}
/*  ���ڹ���  PWM  ���� Ƶ�� �� ����  ���   */
u8 	TIM4_CO1_Check(u16 *frequency,u16 *percent)		// PB6
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)//����1���������¼�
	{	
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC1);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//��ǲ�����������
			Bas_Val=TIM_GetCapture1(TIM4);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM4_Prescaler/All_Val);
				*percent=Up_Val*1000 / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM4)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM4_CO2_Check(u16 *frequency,u16 *percent)		// PB7
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture2(TIM4);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM4_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM4)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
} 
u8 	TIM4_CO3_Check(u16 *frequency,u16 *percent)		// PB8
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)               //����2���������¼�
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC3);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture3(TIM4);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM4_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM4)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM4_CO4_Check(u16 *frequency,u16 *percent)		// PB9
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC4);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture4(TIM4);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM4_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM4)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM5_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM5_ICInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��

	TIM5_Prescaler=Prescaler;//TIM5_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			  //IO�˿ڵĵ�6λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);				 //PA0 ����
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			  //IO�˿ڵĵ�1λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==3)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			  //IO�˿ڵĵ�2λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			  //IO�˿ڵĵ�3λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	
	//��ʼ����ʱ��5 TIM5	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);              //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM5���벶�����
	if(OC==1)TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	else  if(OC==2)TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //�����ز���
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //���������Ƶ,����Ƶ 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
	
	
	if(OC==1)TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //��������ж� ,����CC1IE�����ж�
	else if(OC==2)TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	
	
   	TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
} 
/*  ���ڹ���  PWM  ���� Ƶ�� �� ����  ���   */
u8 	TIM5_CO1_Check(u16 *frequency,u16 *percent)		// PA0
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
	{	
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC1);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//��ǲ�����������
			Bas_Val=TIM_GetCapture1(TIM5);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM5_Prescaler/All_Val);
				*percent=Up_Val*1000 / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM5)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM5_CO2_Check(u16 *frequency,u16 *percent)		// PA1
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture2(TIM5);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM5_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM5)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
} 
u8 	TIM5_CO3_Check(u16 *frequency,u16 *percent)		// PA2
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture3(TIM5);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM5_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM5)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM5_CO4_Check(u16 *frequency,u16 *percent)		// PA3
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture4(TIM5);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM5_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM5)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
/*******************************************************************************************************************/
/*******************************************************************************************************************/
/*******************************************************************************************************************/
void TIM8_Cap_Init(u16 Prescaler,u16 Period,u8 OC)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef  TIM8_ICInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 | RCC_APB2Periph_GPIOC, ENABLE);

	TIM8_Prescaler=Prescaler;//TIM5_Period=Period;

	if(OC==1)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			  //IO�˿ڵĵ�6λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);						 //PC6 ����
    }
	else if(OC==2)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;			  //IO�˿ڵĵ�7λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
	else if(OC==3)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			  //IO�˿ڵĵ�8λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
	else if(OC==4)
    {
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			  //IO�˿ڵĵ�8λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
	
	//��ʼ����ʱ��8 TIM8	 
	TIM_TimeBaseStructure.TIM_Period = Period; 				     //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler =Prescaler-1; 	         //Ԥ��Ƶ��   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);              //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	//��ʼ��TIM8���벶�����
	if(OC==1)TIM8_ICInitStructure.TIM_Channel = TIM_Channel_1;   //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	else  if(OC==2)TIM8_ICInitStructure.TIM_Channel = TIM_Channel_2;
	else  if(OC==3)TIM8_ICInitStructure.TIM_Channel = TIM_Channel_3; 
	else  if(OC==4)TIM8_ICInitStructure.TIM_Channel = TIM_Channel_4;  
	else  {}
  	TIM8_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	 //�����ز���
  	TIM8_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM8_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	         //���������Ƶ,����Ƶ 
  	TIM8_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM8, &TIM8_ICInitStructure);
	
	TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);

  /* Select the slave Mode: Reset Mode */
    TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_Reset);

  /* Enable the Master/Slave Mode */
    TIM_SelectMasterSlaveMode(TIM8, TIM_MasterSlaveMode_Enable);
	
	if(OC==1)TIM_ITConfig(TIM8,TIM_IT_Update|TIM_IT_CC1,ENABLE);     //��������ж� ,����CC1IE�����ж�
	else if(OC==2)TIM_ITConfig(TIM8,TIM_IT_Update|TIM_IT_CC2,ENABLE);
	else if(OC==3)TIM_ITConfig(TIM8,TIM_IT_Update|TIM_IT_CC3,ENABLE);
	else if(OC==4)TIM_ITConfig(TIM8,TIM_IT_Update|TIM_IT_CC4,ENABLE);
	else {}	

   	TIM_Cmd(TIM8,ENABLE ); 	//ʹ�ܶ�ʱ��5
} 
/*  ���ڹ���  PWM  ���� Ƶ�� �� ����  ���   */
u8 	TIM8_CO1_Check(u16 *frequency,u16 *percent)		// PC6
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM8, TIM_IT_CC1) != RESET)//����1���������¼�
	{	
		TIM_ClearITPendingBit(TIM8, TIM_IT_CC1);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		//��ǲ�����������
			Bas_Val=TIM_GetCapture1(TIM8);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;
				*frequency=(72000000/TIM8_Prescaler/All_Val);
				*percent=Up_Val*1000 / All_Val;
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC1PolarityConfig(TIM8,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture1(TIM8)-Bas_Val;
	   		TIM_OC1PolarityConfig(TIM8,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM8_CO2_Check(u16 *frequency,u16 *percent)		// PA1
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM8, TIM_IT_CC2) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM8, TIM_IT_CC2);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture2(TIM8);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM8_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC2PolarityConfig(TIM8,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture2(TIM8)-Bas_Val;
	   		TIM_OC2PolarityConfig(TIM8,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
} 
u8 	TIM8_CO3_Check(u16 *frequency,u16 *percent)		// PA2
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM8, TIM_IT_CC3) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM8, TIM_IT_CC3);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture3(TIM8);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM8_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC3PolarityConfig(TIM8,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture3(TIM8)-Bas_Val;
	   		TIM_OC3PolarityConfig(TIM8,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}
u8 	TIM8_CO4_Check(u16 *frequency,u16 *percent)		// PA3
{
	static u8 OC_STA=0;
	static u16 Last_Bas_Val=1,Bas_Val=0,All_Val,Up_Val;
	if (TIM_GetITStatus(TIM8, TIM_IT_CC4) != RESET)               //����2���������¼�
	{	
		TIM_ClearITPendingBit(TIM8, TIM_IT_CC4);                  //����жϱ�־λ
	    if(OC_STA==0)  								
		{	
			OC_STA=1;		                                      //��ǲ�����������
			Bas_Val=TIM_GetCapture4(TIM8);
			if(Bas_Val>Last_Bas_Val)
			{
				All_Val=Bas_Val-Last_Bas_Val;					  // ���������ص�ʱ��� Ҳ����һ�����ڵ�ʱ��
				*frequency=(72000000/TIM8_Prescaler/All_Val);	  // Ƶ��
				*percent=Up_Val*1000 / All_Val;	                  // �Ŵ�һ�ٱ���Ҳ����С���������λ
			}
			Last_Bas_Val=Bas_Val;				                  // ���»�׼ʱ��
	   		TIM_OC4PolarityConfig(TIM8,TIM_ICPolarity_Falling);	  //CC1P=1 ����Ϊ�½��ز��

			return 1;
		}
		else if(OC_STA==1)		                                  //����һ���½��� 		
		{	  			
			OC_STA=0;		
			Up_Val=TIM_GetCapture4(TIM8)-Bas_Val;
	   		TIM_OC4PolarityConfig(TIM8,TIM_ICPolarity_Rising);    //CC1P=0 ����Ϊ�����ز���
		}
		else {OC_STA=0;}			                              //���				    
	}
	return 0 ;
}





