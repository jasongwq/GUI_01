#include "PWM.h"
#include "PWM_comp.h"
#include "stm32f10x.h"

/*			  ���ռ�ձȼ��㹫ʽ��TIM_Pulse/(TIM_Period	+ 1) * 100%
*			  
*/

static GPIO_InitTypeDef GPIO_InitStructure;


static TIM_TimeBaseInitTypeDef  TIM1_TimeBaseStructure,TIM2_TimeBaseStructure,TIM3_TimeBaseStructure,TIM4_TimeBaseStructure,TIM5_TimeBaseStructure,TIM8_TimeBaseStructure;
static TIM_OCInitTypeDef  TIM1_OCInitStructure,TIM2_OCInitStructure,TIM3_OCInitStructure,TIM4_OCInitStructure,TIM5_OCInitStructure,TIM8_OCInitStructure;
//static TIM_BDTRInitTypeDef TIM8_BDTRInitStructure;

/*******************************************************************************
*					TIM1�ĺ���
*******************************************************************************/
void TIM1_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4)							   // PA8    PA9    PA10    PA11
{  

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	//����AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//����TIM1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    if(OC1==1)
    {
	    /* GPIOC Configuration: TIM1 Channel 1 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			  //IO�˿ڵĵ�6λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	      //�˿�ģʽΪ�������������ʽ
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  //��ת�ٶ�Ϊ50M
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	if(OC2==1)
    {
	    /* GPIOC Configuration: TIM1 Channel 2 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			  //IO�˿ڵĵ�7λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	      //�˿�ģʽΪ�������������ʽ
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  //��ת�ٶ�Ϊ50M
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	if(OC3==1)
    {
	    /* GPIOC Configuration: TIM1 Channel 3 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			  //IO�˿ڵĵ�8λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	      //�˿�ģʽΪ�������������ʽ
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  //��ת�ٶ�Ϊ50M
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	if(OC4==1)
    {
	    /* GPIOC Configuration: TIM1 Channel 4 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			  //IO�˿ڵĵ�8λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	      //�˿�ģʽΪ�������������ʽ
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  //��ת�ٶ�Ϊ50M
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }


    TIM_DeInit(TIM1);												 //��λ��ʱ��8���мĴ���

    /* Time Base configuration */
    TIM1_TimeBaseStructure.TIM_Prescaler = Prescaler-1;						 //Ԥ��Ƶ��Ϊ0,����Ƶ
    TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //��¦��ʽΪ˳�����ģʽ��������
    TIM1_TimeBaseStructure.TIM_Period = Period-1;					     //���ü��������������س�ֵ
    TIM1_TimeBaseStructure.TIM_ClockDivision =  0x00;				 //����ʱ�ӷָ�ֵ
    TIM1_TimeBaseStructure.TIM_RepetitionCounter = 0x0;			     //ѭ����������ֵ

    TIM_TimeBaseInit(TIM1,&TIM1_TimeBaseStructure);				     //�����ϲ�����ʼ����ʱ��ʱ�����ģ��
  
    /* Channel 1 Configuration in PWM mode */
    TIM1_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			     //�����ʽΪPWMģʽ1
 
    TIM1_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ������Ƚ�״̬
    TIM1_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ�ܶ�ʱ���������               
    TIM1_OCInitStructure.TIM_Pulse = 5000; 							 //��������
    TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   	 //����Ƚϼ���Ϊ��
    TIM1_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	     //�򿪿���״̬ѡ��ر�
  
    /* ��ʼ��TM1ͨ��1*/
    if(OC1==1)TIM_OC1Init(TIM1,&TIM1_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��1
	if(OC2==1)TIM_OC2Init(TIM1,&TIM1_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��2
	if(OC3==1)TIM_OC3Init(TIM1,&TIM1_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��3
	if(OC4==1)TIM_OC4Init(TIM1,&TIM1_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��4
 
    /* TIM1 counter enable */
    TIM_Cmd(TIM1,ENABLE);							   //ʹ�ܶ�ʱ��8

    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM1,ENABLE);				   //ʹ�ܶ�ʱ��8��PWM���	 Ƶ��

}  

void TIM1_Change_Period(u16 NoteSet)
{
     TIM1_TimeBaseStructure.TIM_Period = NoteSet ;
	 TIM_TimeBaseInit(TIM1,&TIM1_TimeBaseStructure);
}
/*******************************���Ƹ���ͨ��������*****************************************************/
void Change_TIM1_OC1_Pulse(u16 Pulse)
{
     TIM1_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC1Init(TIM1,&TIM1_OCInitStructure);
}
void Change_TIM1_OC2_Pulse(u16 Pulse)
{
     TIM1_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC2Init(TIM1,&TIM1_OCInitStructure);
}
void Change_TIM1_OC3_Pulse(u16 Pulse)
{
     TIM1_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC3Init(TIM1,&TIM1_OCInitStructure);
}
void Change_TIM1_OC4_Pulse(u16 Pulse)
{
     TIM1_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC4Init(TIM1,&TIM1_OCInitStructure);
}
/*********************************��ͨ�����Կ���*****************************************************/
void Change_TIM1_OC1_Polarity(u8 i)
{
     if(i==1)TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC1Init(TIM1,&TIM1_OCInitStructure);
}
void Change_TIM1_OC2_Polarity(u8 i)
{
     if(i==1)TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC2Init(TIM1,&TIM1_OCInitStructure);
}
void Change_TIM1_OC3_Polarity(u8 i)
{
     if(i==1)TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC3Init(TIM1,&TIM1_OCInitStructure);
}
void Change_TIM1_OC4_Polarity(u8 i)
{
     if(i==1)TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC4Init(TIM1,&TIM1_OCInitStructure);
}

/*******************************************************************************
*					TIM2�ĺ���
*******************************************************************************/
void TIM2_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4)							   // PA0    PA1    PA2    PA3
{  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    if(OC1==1)
    {
	    /* GPIOA Configuration: TIM2 Channel 1 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	    
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	if(OC2==1)
    {
	    /* GPIOA Configuration: TIM2 Channel 2 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	if(OC3==1)
    {
	    /* GPIOA Configuration: TIM2 Channel 3 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	if(OC4==1)
    {
	    /* GPIOA Configuration: TIM2 Channel 4 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }


    TIM_DeInit(TIM2);												 //��λ��ʱ��8���мĴ���

    /* Time Base configuration */
    TIM2_TimeBaseStructure.TIM_Prescaler = Prescaler-1;						 //Ԥ��Ƶ��Ϊ0,����Ƶ
    TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //��¦��ʽΪ˳�����ģʽ��������
    TIM2_TimeBaseStructure.TIM_Period = Period-1;					     //���ü��������������س�ֵ
    TIM2_TimeBaseStructure.TIM_ClockDivision =  0x00;				 //����ʱ�ӷָ�ֵ
    TIM2_TimeBaseStructure.TIM_RepetitionCounter = 0x0;			     //ѭ����������ֵ

    TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseStructure);				     //�����ϲ�����ʼ����ʱ��ʱ�����ģ��
  
    /* Channel 1 Configuration in PWM mode */
    TIM2_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			     //�����ʽΪPWMģʽ1
 
    TIM2_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ������Ƚ�״̬
    TIM2_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ�ܶ�ʱ���������               
    TIM2_OCInitStructure.TIM_Pulse = 5000; 							 //��������
    TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   	 //����Ƚϼ���Ϊ��
    TIM2_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	     //�򿪿���״̬ѡ��ر�
  
    /* ��ʼ��TM5ͨ��1*/
    if(OC1==1)TIM_OC1Init(TIM2,&TIM2_OCInitStructure); 		         //�����ϲ�����ʼ��TIM2��ͨ��1
	if(OC2==1)TIM_OC2Init(TIM2,&TIM2_OCInitStructure); 		         //�����ϲ�����ʼ��TIM2��ͨ��2
	if(OC3==1)TIM_OC3Init(TIM2,&TIM2_OCInitStructure); 		         //�����ϲ�����ʼ��TIM2��ͨ��3
	if(OC4==1)TIM_OC4Init(TIM2,&TIM2_OCInitStructure); 		         //�����ϲ�����ʼ��TIM2��ͨ��4
 
    /* TIM5 counter enable */
    TIM_Cmd(TIM2,ENABLE);							   //ʹ�ܶ�ʱ��2

    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM2,ENABLE);				   //ʹ�ܶ�ʱ��2��PWM���	 Ƶ��

}  

void TIM2_Change_Period(u16 NoteSet)
{
     TIM2_TimeBaseStructure.TIM_Period = NoteSet ;
	 TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseStructure);
}
/*******************************���Ƹ���ͨ��������*****************************************************/
void Change_TIM2_OC1_Pulse(u16 Pulse)
{
     TIM2_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC1Init(TIM2,&TIM2_OCInitStructure);
}
void Change_TIM2_OC2_Pulse(u16 Pulse)
{
     TIM2_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC2Init(TIM2,&TIM2_OCInitStructure);
}
void Change_TIM2_OC3_Pulse(u16 Pulse)
{
     TIM2_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC3Init(TIM2,&TIM2_OCInitStructure);
}
void Change_TIM2_OC4_Pulse(u16 Pulse)
{
     TIM2_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC4Init(TIM2,&TIM2_OCInitStructure);
}
/*********************************��ͨ�����Կ���*****************************************************/
void Change_TIM2_OC1_Polarity(u8 i)
{
     if(i==1)TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC1Init(TIM2,&TIM2_OCInitStructure);
}
void Change_TIM2_OC2_Polarity(u8 i)
{
     if(i==1)TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC2Init(TIM2,&TIM2_OCInitStructure);
}
void Change_TIM2_OC3_Polarity(u8 i)
{
     if(i==1)TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC3Init(TIM2,&TIM2_OCInitStructure);
}
void Change_TIM2_OC4_Polarity(u8 i)
{
     if(i==1)TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC4Init(TIM2,&TIM2_OCInitStructure);
}

/*******************************************************************************
*					TIM3�ĺ���
*******************************************************************************/
void TIM3_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4)							   // PA6    PA7    PB0    PB1
{  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    if(OC1==1)
    {
	    /* GPIOA Configuration: TIM3 Channel 1 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	    
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	if(OC2==1)
    {
	    /* GPIOA Configuration: TIM3 Channel 2 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	if(OC3==1)
    {
	    /* GPIOB Configuration: TIM3 Channel 3 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	if(OC4==1)
    {
	    /* GPIOB Configuration: TIM3 Channel 4 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }


    TIM_DeInit(TIM3);												 //��λ��ʱ��8���мĴ���

    /* Time Base configuration */
    TIM3_TimeBaseStructure.TIM_Prescaler = Prescaler-1;						 //Ԥ��Ƶ��Ϊ0,����Ƶ
    TIM3_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //��¦��ʽΪ˳�����ģʽ��������
    TIM3_TimeBaseStructure.TIM_Period =Period-1;					     //���ü��������������س�ֵ
    TIM3_TimeBaseStructure.TIM_ClockDivision =  0x00;				 //����ʱ�ӷָ�ֵ
    TIM3_TimeBaseStructure.TIM_RepetitionCounter = 0x0;			     //ѭ����������ֵ

    TIM_TimeBaseInit(TIM3,&TIM3_TimeBaseStructure);				     //�����ϲ�����ʼ����ʱ��ʱ�����ģ��
  
    /* Channel 1 Configuration in PWM mode */
    TIM3_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			     //�����ʽΪPWMģʽ1
 
    TIM3_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ������Ƚ�״̬
    TIM3_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ�ܶ�ʱ���������               
    TIM3_OCInitStructure.TIM_Pulse = 5000; 							 //��������
    TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   	 //����Ƚϼ���Ϊ��
    TIM3_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	     //�򿪿���״̬ѡ��ر�
  
    /* ��ʼ��TM3ͨ��1*/
    if(OC1==1)TIM_OC1Init(TIM3,&TIM3_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��1
	if(OC2==1)TIM_OC2Init(TIM3,&TIM3_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��2
	if(OC3==1)TIM_OC3Init(TIM3,&TIM3_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��3
	if(OC4==1)TIM_OC4Init(TIM3,&TIM3_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��4
 
    /* TIM3 counter enable */
    TIM_Cmd(TIM3,ENABLE);							   //ʹ�ܶ�ʱ��8

    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM3,ENABLE);				   //ʹ�ܶ�ʱ��8��PWM���	 Ƶ��

}  

void TIM3_Change_Period(u16 NoteSet)
{
     TIM3_TimeBaseStructure.TIM_Period = NoteSet ;
	 TIM_TimeBaseInit(TIM3,&TIM3_TimeBaseStructure);
}
/*******************************���Ƹ���ͨ��������*****************************************************/
void Change_TIM3_OC1_Pulse(u16 Pulse)
{
     TIM3_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC1Init(TIM3,&TIM3_OCInitStructure);
}
void Change_TIM3_OC2_Pulse(u16 Pulse)
{
     TIM3_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC2Init(TIM3,&TIM3_OCInitStructure);
}
void Change_TIM3_OC3_Pulse(u16 Pulse)
{
     TIM3_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC3Init(TIM3,&TIM3_OCInitStructure);
}
void Change_TIM3_OC4_Pulse(u16 Pulse)
{
     TIM3_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC4Init(TIM3,&TIM3_OCInitStructure);
}
/*********************************��ͨ�����Կ���*****************************************************/
void Change_TIM3_OC1_Polarity(u8 i)
{
     if(i==1)TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC1Init(TIM3,&TIM3_OCInitStructure);
}
void Change_TIM3_OC2_Polarity(u8 i)
{
     if(i==1)TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC2Init(TIM3,&TIM3_OCInitStructure);
}
void Change_TIM3_OC3_Polarity(u8 i)
{
     if(i==1)TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC3Init(TIM3,&TIM3_OCInitStructure);
}
void Change_TIM3_OC4_Polarity(u8 i)
{
     if(i==1)TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM3_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC4Init(TIM3,&TIM3_OCInitStructure);
}


/*******************************************************************************
*					TIM4�ĺ���
*******************************************************************************/
void TIM4_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4)							   // PB6    PB7    PB8    PB9
{  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    if(OC1==1)
    {
	    /* GPIOB Configuration: TIM3 Channel 1 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	    
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	if(OC2==1)
    {
	    /* GPIOB Configuration: TIM3 Channel 2 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	if(OC3==1)
    {
	    /* GPIOB Configuration: TIM3 Channel 3 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
	if(OC4==1)
    {
	    /* GPIOB Configuration: TIM3 Channel 4 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }


    TIM_DeInit(TIM4);												 //��λ��ʱ��8���мĴ���

    /* Time Base configuration */
    TIM4_TimeBaseStructure.TIM_Prescaler =Prescaler-1;						 //Ԥ��Ƶ��Ϊ0,����Ƶ
    TIM4_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //��¦��ʽΪ˳�����ģʽ��������
    TIM4_TimeBaseStructure.TIM_Period = Period-1;					     //���ü��������������س�ֵ
    TIM4_TimeBaseStructure.TIM_ClockDivision =  0x00;				 //����ʱ�ӷָ�ֵ
    TIM4_TimeBaseStructure.TIM_RepetitionCounter = 0x0;			     //ѭ����������ֵ

    TIM_TimeBaseInit(TIM4,&TIM4_TimeBaseStructure);				     //�����ϲ�����ʼ����ʱ��ʱ�����ģ��
  
    /* Channel 1 Configuration in PWM mode */
    TIM4_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			     //�����ʽΪPWMģʽ1
 
    TIM4_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ������Ƚ�״̬
    TIM4_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ�ܶ�ʱ���������               
    TIM4_OCInitStructure.TIM_Pulse = 5000; 							 //��������
    TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   	 //����Ƚϼ���Ϊ��
    TIM4_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	     //�򿪿���״̬ѡ��ر�
  
    /* ��ʼ��TM4ͨ��1*/
    if(OC1==1)TIM_OC1Init(TIM4,&TIM4_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��1
	if(OC2==1)TIM_OC2Init(TIM4,&TIM4_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��2
	if(OC3==1)TIM_OC3Init(TIM4,&TIM4_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��3
	if(OC4==1)TIM_OC4Init(TIM4,&TIM4_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��4
 
    /* TIM4 counter enable */
    TIM_Cmd(TIM4,ENABLE);							   //ʹ�ܶ�ʱ��8

    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM4,ENABLE);				   //ʹ�ܶ�ʱ��8��PWM���	 Ƶ��

}  

void TIM4_Change_Period(u16 NoteSet)
{
     TIM4_TimeBaseStructure.TIM_Period = NoteSet ;
	 TIM_TimeBaseInit(TIM4,&TIM4_TimeBaseStructure);
}
/*******************************���Ƹ���ͨ��������*****************************************************/
void Change_TIM4_OC1_Pulse(u16 Pulse)
{
     TIM4_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC1Init(TIM4,&TIM4_OCInitStructure);
}
void Change_TIM4_OC2_Pulse(u16 Pulse)
{
     TIM4_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC2Init(TIM4,&TIM4_OCInitStructure);
}
void Change_TIM4_OC3_Pulse(u16 Pulse)
{
     TIM4_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC3Init(TIM4,&TIM4_OCInitStructure);
}
void Change_TIM4_OC4_Pulse(u16 Pulse)
{
     TIM4_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC4Init(TIM4,&TIM4_OCInitStructure);
}
/*********************************��ͨ�����Կ���*****************************************************/
void Change_TIM4_OC1_Polarity(u8 i)
{
     if(i==1)TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC1Init(TIM4,&TIM4_OCInitStructure);
}
void Change_TIM4_OC2_Polarity(u8 i)
{
     if(i==1)TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC2Init(TIM4,&TIM4_OCInitStructure);
}
void Change_TIM4_OC3_Polarity(u8 i)
{
     if(i==1)TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC3Init(TIM4,&TIM4_OCInitStructure);
}
void Change_TIM4_OC4_Polarity(u8 i)
{
     if(i==1)TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC4Init(TIM4,&TIM4_OCInitStructure);
}





/*******************************************************************************
*					TIM5�ĺ���
*******************************************************************************/
void TIM5_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4)							   // PA0    PA1    PA2    PA3
{  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    if(OC1==1)
    {
	    /* GPIOA Configuration: TIM5 Channel 1 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	    
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	if(OC2==1)
    {
	    /* GPIOA Configuration: TIM5 Channel 2 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	if(OC3==1)
    {
	    /* GPIOA Configuration: TIM5 Channel 3 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
	if(OC4==1)
    {
	    /* GPIOA Configuration: TIM5 Channel 4 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			  
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	     
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }


    TIM_DeInit(TIM5);												 //��λ��ʱ��8���мĴ���

    /* Time Base configuration */
    TIM5_TimeBaseStructure.TIM_Prescaler = Prescaler-1;						 //Ԥ��Ƶ��Ϊ0,����Ƶ
    TIM5_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //��¦��ʽΪ˳�����ģʽ��������
    TIM5_TimeBaseStructure.TIM_Period = Period-1;					     //���ü��������������س�ֵ
    TIM5_TimeBaseStructure.TIM_ClockDivision =  0x00;				 //����ʱ�ӷָ�ֵ
    TIM5_TimeBaseStructure.TIM_RepetitionCounter = 0x0;			     //ѭ����������ֵ

    TIM_TimeBaseInit(TIM5,&TIM5_TimeBaseStructure);				     //�����ϲ�����ʼ����ʱ��ʱ�����ģ��
  
    /* Channel 1 Configuration in PWM mode */
    TIM5_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			     //�����ʽΪPWMģʽ1
 
    TIM5_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ������Ƚ�״̬
    TIM5_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ�ܶ�ʱ���������               
    TIM5_OCInitStructure.TIM_Pulse = 5000; 							 //��������
    TIM5_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   	 //����Ƚϼ���Ϊ��
    TIM5_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	     //�򿪿���״̬ѡ��ر�
  
    /* ��ʼ��TM5ͨ��1*/
    if(OC1==1)TIM_OC1Init(TIM5,&TIM5_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��1
	if(OC2==1)TIM_OC2Init(TIM5,&TIM5_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��2
	if(OC3==1)TIM_OC3Init(TIM5,&TIM5_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��3
	if(OC4==1)TIM_OC4Init(TIM5,&TIM5_OCInitStructure); 		         //�����ϲ�����ʼ��TIM3��ͨ��4
 
    /* TIM5 counter enable */
    TIM_Cmd(TIM5,ENABLE);							   //ʹ�ܶ�ʱ��8

    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM5,ENABLE);				   //ʹ�ܶ�ʱ��8��PWM���	 Ƶ��

}  

void TIM5_Change_Period(u16 NoteSet)
{
     TIM5_TimeBaseStructure.TIM_Period = NoteSet ;
	 TIM_TimeBaseInit(TIM5,&TIM5_TimeBaseStructure);
}
/*******************************���Ƹ���ͨ��������*****************************************************/
void Change_TIM5_OC1_Pulse(u16 Pulse)
{
     TIM5_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC1Init(TIM5,&TIM5_OCInitStructure);
}
void Change_TIM5_OC2_Pulse(u16 Pulse)
{
     TIM5_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC2Init(TIM5,&TIM5_OCInitStructure);
}
void Change_TIM5_OC3_Pulse(u16 Pulse)
{
     TIM5_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC3Init(TIM5,&TIM5_OCInitStructure);
}
void Change_TIM5_OC4_Pulse(u16 Pulse)
{
     TIM5_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC4Init(TIM5,&TIM5_OCInitStructure);
}
/*********************************��ͨ�����Կ���*****************************************************/
void Change_TIM5_OC1_Polarity(u8 i)
{
     if(i==1)TIM5_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM5_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC1Init(TIM5,&TIM5_OCInitStructure);
}
void Change_TIM5_OC2_Polarity(u8 i)
{
     if(i==1)TIM5_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM5_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC2Init(TIM5,&TIM5_OCInitStructure);
}
void Change_TIM5_OC3_Polarity(u8 i)
{
     if(i==1)TIM5_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM5_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC3Init(TIM5,&TIM5_OCInitStructure);
}
void Change_TIM5_OC4_Polarity(u8 i)
{
     if(i==1)TIM5_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM5_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC4Init(TIM5,&TIM5_OCInitStructure);
}
/*******************************************************************************
*					TIM8�ĺ���
*******************************************************************************/
void TIM8_PWM_init(u16 Prescaler,u16 Period,u8 OC1 ,u8 OC2 ,u8 OC3 ,u8 OC4)							   // PC6    PC7    PC8    PC9
{  

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 | RCC_APB2Periph_GPIOC, ENABLE);

    if(OC1==1)
    {
	    /* GPIOC Configuration: TIM8 Channel 1 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			  //IO�˿ڵĵ�6λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	      //�˿�ģʽΪ�������������ʽ
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  //��ת�ٶ�Ϊ50M
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
	if(OC2==1)
    {
	    /* GPIOC Configuration: TIM8 Channel 2 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;			  //IO�˿ڵĵ�7λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	      //�˿�ģʽΪ�������������ʽ
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  //��ת�ٶ�Ϊ50M
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
	if(OC3==1)
    {
	    /* GPIOC Configuration: TIM8 Channel 3 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			  //IO�˿ڵĵ�8λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	      //�˿�ģʽΪ�������������ʽ
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  //��ת�ٶ�Ϊ50M
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
	if(OC4==1)
    {
	    /* GPIOC Configuration: TIM8 Channel 4 Output */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;			  //IO�˿ڵĵ�8λ
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	      //�˿�ģʽΪ�������������ʽ
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	  //��ת�ٶ�Ϊ50M
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }


    TIM_DeInit(TIM8);												 //��λ��ʱ��8���мĴ���

    /* Time Base configuration */
    TIM8_TimeBaseStructure.TIM_Prescaler = Prescaler-1;						 //Ԥ��Ƶ��Ϊ0,����Ƶ
    TIM8_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 //��¦��ʽΪ˳�����ģʽ��������
    TIM8_TimeBaseStructure.TIM_Period = Period-1;					     //���ü��������������س�ֵ
    TIM8_TimeBaseStructure.TIM_ClockDivision =  0x00;				 //����ʱ�ӷָ�ֵ
    TIM8_TimeBaseStructure.TIM_RepetitionCounter = 0x0;			     //ѭ����������ֵ

    TIM_TimeBaseInit(TIM8,&TIM8_TimeBaseStructure);				     //�����ϲ�����ʼ����ʱ��ʱ�����ģ��
  
    /* Channel 1 Configuration in PWM mode */
    TIM8_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 			     //�����ʽΪPWMģʽ1
 
    TIM8_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //ʹ������Ƚ�״̬
    TIM8_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; //ʹ�ܶ�ʱ���������               
    TIM8_OCInitStructure.TIM_Pulse = 5000; 							 //��������
    TIM8_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   	 //����Ƚϼ���Ϊ��
    TIM8_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;	     //�򿪿���״̬ѡ��ر�
  
    /* ��ʼ��TM8ͨ��1*/
    if(OC1==1)TIM_OC1Init(TIM8,&TIM8_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��1
	if(OC2==1)TIM_OC2Init(TIM8,&TIM8_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��2
	if(OC3==1)TIM_OC3Init(TIM8,&TIM8_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��3
	if(OC4==1)TIM_OC4Init(TIM8,&TIM8_OCInitStructure); 		         //�����ϲ�����ʼ��TIM8��ͨ��4
 
    /* TIM8 counter enable */
    TIM_Cmd(TIM8,ENABLE);							   //ʹ�ܶ�ʱ��8

    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM8,ENABLE);				   //ʹ�ܶ�ʱ��8��PWM���	 Ƶ��

}  

void TIM8_Change_Period(u16 NoteSet)
{
     TIM8_TimeBaseStructure.TIM_Period = NoteSet ;
	 TIM_TimeBaseInit(TIM8,&TIM8_TimeBaseStructure);
}
/*******************************���Ƹ���ͨ��������*****************************************************/
void Change_TIM8_OC1_Pulse(u16 Pulse)
{
     TIM8_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC1Init(TIM8,&TIM8_OCInitStructure);
}
void Change_TIM8_OC2_Pulse(u16 Pulse)
{
     TIM8_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC2Init(TIM8,&TIM8_OCInitStructure);
}
void Change_TIM8_OC3_Pulse(u16 Pulse)
{
     TIM8_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC3Init(TIM8,&TIM8_OCInitStructure);
}
void Change_TIM8_OC4_Pulse(u16 Pulse)
{
     TIM8_OCInitStructure.TIM_Pulse = Pulse;
	 TIM_OC4Init(TIM8,&TIM8_OCInitStructure);
}
/*********************************��ͨ�����Կ���*****************************************************/
void Change_TIM8_OC1_Polarity(u8 i)
{
     if(i==1)TIM8_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM8_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC1Init(TIM8,&TIM8_OCInitStructure);
}
void Change_TIM8_OC2_Polarity(u8 i)
{
     if(i==1)TIM8_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM8_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC2Init(TIM8,&TIM8_OCInitStructure);
}
void Change_TIM8_OC3_Polarity(u8 i)
{
     if(i==1)TIM8_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM8_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC3Init(TIM8,&TIM8_OCInitStructure);
}
void Change_TIM8_OC4_Polarity(u8 i)
{
     if(i==1)TIM8_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	 else 	 TIM8_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	 TIM_OC4Init(TIM8,&TIM8_OCInitStructure);
}
