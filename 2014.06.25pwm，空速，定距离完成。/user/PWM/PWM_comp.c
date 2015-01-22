#include "PWM_comp.h"
#include "stm32f10x.h"

static 	TIM_OCInitTypeDef    TIM1_OC1InitStructure,TIM1_OC2InitStructure,TIM1_OC3InitStructure;
static 	TIM_OCInitTypeDef    TIM8_OC1InitStructure,TIM8_OC2InitStructure,TIM8_OC3InitStructure;

void TIM1_Init(u16 Prescaler,u16 Period,u8 OC1,u8 OC2,u8 OC3,u8 DeadTime,u8 Open)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
    TIM_BDTRInitTypeDef     TIM_BDTRInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	//����AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//����TIM1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	//Step2. GPIO����Ӧ���ã�ΪAF���
	//PA.8/9������ΪTIM1��OC1�����
	if(OC1)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
	if(OC2)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
	if(OC3)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}

	//TIM1�������������ã�����PWMƵ�ʣ�
    //Ƶ��=TIM1_CLK/(ARR+1)
	TIM_BaseInitStructure.TIM_Prescaler = Prescaler-1;				 //Ԥ��Ƶ	  0 ��ʾ����Ƶ
    TIM_BaseInitStructure.TIM_Period = Period-1;				     //���ü��������������س�ֵ
    TIM_BaseInitStructure.TIM_ClockDivision = 0;					 //����ʱ�ӷָ�ֵ
    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		 //��¦��ʽΪ˳�����ģʽ��������
    TIM_BaseInitStructure.TIM_RepetitionCounter = 0;				 //ѭ����������ֵ
    TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);
    //����ARR��Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    TIM_ARRPreloadConfig(TIM1, ENABLE);

	if(OC1)
	{
    	//TIM1_OC1ģ�����ã�����1ͨ��ռ�ձȣ�
    	TIM1_OC1InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM1_OC1InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	TIM1_OC1InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    	TIM1_OC1InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM1_OC1InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    	TIM1_OC1InitStructure.TIM_Pulse = 5000;
    	TIM_OC1Init(TIM1, &TIM1_OC1InitStructure);
    	//����CCR1�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	}
	if(OC2)
	{
    	//TIM1_OC2ģ�����ã�����2ͨ��ռ�ձȣ�
		TIM1_OC2InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM1_OC2InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	TIM1_OC2InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM1_OC2InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM1_OC2InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    	TIM1_OC2InitStructure.TIM_Pulse = 680;
    	TIM_OC2Init(TIM1, &TIM1_OC2InitStructure);
    	//����CCR2�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	}
	if(OC3)
	{
    	//TIM1_OC3ģ�����ã�����3ͨ��ռ�ձȣ�
		TIM1_OC3InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM1_OC3InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	TIM1_OC3InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM1_OC3InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM1_OC3InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    	TIM1_OC3InitStructure.TIM_Pulse = 1000;
    	TIM_OC3Init(TIM1, &TIM1_OC3InitStructure);
    	//����CCR2�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	}
	if(Open)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;			
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
    
    //��������
    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStructure.TIM_DeadTime = DeadTime;  //�������������С0-0xff
    if(Open)TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	else 	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
    if(Open==1)TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low; //ɲ������͵�ƽ��Ч
	else TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High; //ɲ������ߵ�ƽ��Ч
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
    
	if(Open)TIM_ITConfig(TIM1,TIM_IT_Break,ENABLE);
    //TIM1����
    TIM_Cmd(TIM1, ENABLE);
    //TIM1_OCͨ�����PWM��һ��Ҫ�ӣ�
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

}
void TIM1_OC1_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse)
{
    if(OCPolarity) TIM1_OC1InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else 		   TIM1_OC1InitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    if(OCNPolarity)TIM1_OC1InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	else 		   TIM1_OC1InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM1_OC1InitStructure.TIM_Pulse = TIM_Pulse ;

    TIM_OC1Init(TIM1, &TIM1_OC1InitStructure);
    //����CCR1�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
}
void TIM1_OC2_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse)
{
    if(OCPolarity) TIM1_OC2InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else 		   TIM1_OC2InitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    if(OCNPolarity)TIM1_OC2InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	else 		   TIM1_OC2InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM1_OC2InitStructure.TIM_Pulse = TIM_Pulse ;

    TIM_OC2Init(TIM1, &TIM1_OC2InitStructure);
    //����CCR1�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
}
void TIM1_OC3_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse)
{
    if(OCPolarity) TIM1_OC3InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else 		   TIM1_OC3InitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    if(OCNPolarity)TIM1_OC3InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	else 		   TIM1_OC3InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM1_OC3InitStructure.TIM_Pulse = TIM_Pulse ;

    TIM_OC3Init(TIM1, &TIM1_OC3InitStructure);
    //����CCR1�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
}
/***************************************************************************/
void TIM1_OC_Init(u16 Prescaler,u16 Period,u8 OC1,u8 OCN1,u8 OC2,u8 OCN2,u8 OC3,u8 OCN3)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
    //TIM_BDTRInitTypeDef     TIM_BDTRInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	//����AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//����TIM1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	//Step2. GPIO����Ӧ���ã�ΪAF���
	//PA.8/9������ΪTIM1��OC1�����
	if(OC1)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	if(OCN1)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
	if(OC2)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	if(OCN2)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
	if(OC3)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	if(OCN3)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}

	//TIM1�������������ã�����PWMƵ�ʣ�
    //Ƶ��=TIM1_CLK/(ARR+1)
	TIM_BaseInitStructure.TIM_Prescaler = Prescaler-1;				 //Ԥ��Ƶ	  0 ��ʾ����Ƶ
    TIM_BaseInitStructure.TIM_Period = Period-1;				     //���ü��������������س�ֵ
    TIM_BaseInitStructure.TIM_ClockDivision = 0;					 //����ʱ�ӷָ�ֵ
    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		 //��¦��ʽΪ˳�����ģʽ��������
    TIM_BaseInitStructure.TIM_RepetitionCounter = 0;				 //ѭ����������ֵ
    TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);
    //����ARR��Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    TIM_ARRPreloadConfig(TIM1, ENABLE);

	if(OC1 || OCN1)
	{
    	//TIM1_OC1ģ�����ã�����1ͨ��ռ�ձȣ�
    	TIM1_OC1InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM1_OC1InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	if(OCN1)TIM1_OC1InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		else 	TIM1_OC1InitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    	TIM1_OC1InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM1_OC1InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    	TIM1_OC1InitStructure.TIM_Pulse = 5000;
    	TIM_OC1Init(TIM1, &TIM1_OC1InitStructure);
    	//����CCR1�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	}
	if(OC2 || OCN2)
	{
    	//TIM1_OC2ģ�����ã�����2ͨ��ռ�ձȣ�
		TIM1_OC2InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM1_OC2InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	if(OCN2)TIM1_OC2InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		else 	TIM1_OC2InitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
		TIM1_OC2InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM1_OC2InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    	TIM1_OC2InitStructure.TIM_Pulse = 680;
    	TIM_OC2Init(TIM1, &TIM1_OC2InitStructure);
    	//����CCR2�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	}
	if(OC3 || OCN3)
	{
    	//TIM1_OC3ģ�����ã�����3ͨ��ռ�ձȣ�
		TIM1_OC3InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM1_OC3InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	if(OCN3)TIM1_OC3InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		else 	TIM1_OC3InitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
		TIM1_OC3InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM1_OC3InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    	TIM1_OC3InitStructure.TIM_Pulse = 1000;
    	TIM_OC3Init(TIM1, &TIM1_OC3InitStructure);
    	//����CCR2�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	}
    
    //TIM1����
    TIM_Cmd(TIM1, ENABLE);
    //TIM1_OCͨ�����PWM��һ��Ҫ�ӣ�
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

}










void TIM8_Init(u16 Prescaler,u16 Period,u8 OC1,u8 OC2,u8 OC3,u8 DeadTime,u8 Open)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
    TIM_BDTRInitTypeDef     TIM_BDTRInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 | RCC_APB2Periph_GPIOC, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	//����AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	//Step2. GPIO����Ӧ���ã�ΪAF���
	if(OC1)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	if(OC2)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
	if(OC3)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}

	//TIM8�������������ã�����PWMƵ�ʣ�
    //Ƶ��=TIM8_CLK/(ARR+1)
	TIM_BaseInitStructure.TIM_Prescaler = Prescaler-1;				 //Ԥ��Ƶ	  0 ��ʾ����Ƶ
    TIM_BaseInitStructure.TIM_Period = Period-1;				     //���ü��������������س�ֵ
    TIM_BaseInitStructure.TIM_ClockDivision = 0;					 //����ʱ�ӷָ�ֵ
    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		 //��¦��ʽΪ˳�����ģʽ��������
    TIM_BaseInitStructure.TIM_RepetitionCounter = 0;				 //ѭ����������ֵ
    TIM_TimeBaseInit(TIM8, &TIM_BaseInitStructure);
    //����ARR��Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    TIM_ARRPreloadConfig(TIM8, ENABLE);

	if(OC1)
	{
    	//TIM8_OC1ģ�����ã�����1ͨ��ռ�ձȣ�
    	TIM8_OC1InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM8_OC1InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	TIM8_OC1InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    	TIM8_OC1InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM8_OC1InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    	TIM8_OC1InitStructure.TIM_Pulse = 5000;
    	TIM_OC1Init(TIM8, &TIM8_OC1InitStructure);
    	//����CCR1�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	}
	if(OC2)
	{
    	//TIM8_OC2ģ�����ã�����2ͨ��ռ�ձȣ�
		TIM8_OC2InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM8_OC2InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	TIM8_OC2InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM8_OC2InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM8_OC2InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    	TIM8_OC2InitStructure.TIM_Pulse = 680;
    	TIM_OC2Init(TIM8, &TIM8_OC2InitStructure);
    	//����CCR2�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	}
	if(OC3)
	{
    	//TIM8_OC3ģ�����ã�����3ͨ��ռ�ձȣ�
		TIM8_OC3InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM8_OC3InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	TIM8_OC3InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		TIM8_OC3InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM8_OC3InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    	TIM8_OC3InitStructure.TIM_Pulse = 1000;
    	TIM_OC3Init(TIM8, &TIM8_OC3InitStructure);
    	//����CCR2�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	}
	if(Open)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;			
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
    
    //��������
    TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
    TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
    TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStructure.TIM_DeadTime = DeadTime;  //�������������С0-0xff
    if(Open)TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
	else 	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
    if(Open==1)TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low; //ɲ������͵�ƽ��Ч
	else TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High; //ɲ������ߵ�ƽ��Ч
    TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);
    
	if(Open)TIM_ITConfig(TIM8,TIM_IT_Break,ENABLE);
    //TIM8����
    TIM_Cmd(TIM8, ENABLE);
    //TIM8_OCͨ�����PWM��һ��Ҫ�ӣ�
    TIM_CtrlPWMOutputs(TIM8, ENABLE);

}
void TIM8_OC1_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse)
{
    if(OCPolarity) TIM8_OC1InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else 		   TIM8_OC1InitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    if(OCNPolarity)TIM8_OC1InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	else 		   TIM8_OC1InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM8_OC1InitStructure.TIM_Pulse = TIM_Pulse ;

    TIM_OC1Init(TIM8, &TIM8_OC1InitStructure);
    //����CCR1�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
}
void TIM8_OC2_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse)
{
    if(OCPolarity) TIM8_OC2InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else 		   TIM8_OC2InitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    if(OCNPolarity)TIM8_OC2InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	else 		   TIM8_OC2InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM8_OC2InitStructure.TIM_Pulse = TIM_Pulse ;

    TIM_OC2Init(TIM8, &TIM8_OC2InitStructure);
    //����CCR1�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
}
void TIM8_OC3_Pulse(u8 OCPolarity,u8 OCNPolarity,u16 TIM_Pulse)
{
    if(OCPolarity) TIM8_OC3InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	else 		   TIM8_OC3InitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

    if(OCNPolarity)TIM8_OC3InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	else 		   TIM8_OC3InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM8_OC3InitStructure.TIM_Pulse = TIM_Pulse ;

    TIM_OC3Init(TIM8, &TIM8_OC3InitStructure);
    //����CCR1�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
}
/***************************************************************************/
void TIM8_OC_Init(u16 Prescaler,u16 Period,u8 OC1,u8 OCN1,u8 OC2,u8 OCN2,u8 OC3,u8 OCN3)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
    //TIM_BDTRInitTypeDef     TIM_BDTRInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8 | RCC_APB2Periph_GPIOC, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	//����AFIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	//Step2. GPIO����Ӧ���ã�ΪAF���
	if(OC1)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	}
	if(OCN1)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	}
	if(OC2)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	}
	if(OCN2)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
	if(OC3)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	}
	if(OCN3)
	{
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}

	//TIM1�������������ã�����PWMƵ�ʣ�
    //Ƶ��=TIM1_CLK/(ARR+1)
	TIM_BaseInitStructure.TIM_Prescaler = Prescaler-1;				 //Ԥ��Ƶ	  0 ��ʾ����Ƶ
    TIM_BaseInitStructure.TIM_Period = Period-1;				     //���ü��������������س�ֵ
    TIM_BaseInitStructure.TIM_ClockDivision = 0;					 //����ʱ�ӷָ�ֵ
    TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		 //��¦��ʽΪ˳�����ģʽ��������
    TIM_BaseInitStructure.TIM_RepetitionCounter = 0;				 //ѭ����������ֵ
    TIM_TimeBaseInit(TIM8, &TIM_BaseInitStructure);
    //����ARR��Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    TIM_ARRPreloadConfig(TIM8, ENABLE);

	if(OC1 || OCN1)
	{
    	//TIM1_OC1ģ�����ã�����1ͨ��ռ�ձȣ�
    	TIM8_OC1InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM8_OC1InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	if(OCN1)TIM8_OC1InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		else 	TIM8_OC1InitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    	TIM8_OC1InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM8_OC1InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    	TIM8_OC1InitStructure.TIM_Pulse = 5000;
    	TIM_OC1Init(TIM8, &TIM8_OC1InitStructure);
    	//����CCR1�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	}
	if(OC2 || OCN2)
	{
    	//TIM1_OC2ģ�����ã�����2ͨ��ռ�ձȣ�
		TIM8_OC2InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM8_OC2InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	if(OCN2)TIM8_OC2InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		else 	TIM8_OC2InitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
		TIM8_OC2InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM8_OC2InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    	TIM8_OC2InitStructure.TIM_Pulse = 680;
    	TIM_OC2Init(TIM8, &TIM8_OC2InitStructure);
    	//����CCR2�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	}
	if(OC3 || OCN3)
	{
    	//TIM1_OC3ģ�����ã�����3ͨ��ռ�ձȣ�
		TIM8_OC3InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    	TIM8_OC3InitStructure.TIM_OutputState = TIM_OutputState_Enable;
    	if(OCN3)TIM8_OC3InitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
		else 	TIM8_OC3InitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
		TIM8_OC3InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    	TIM8_OC3InitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    	TIM8_OC3InitStructure.TIM_Pulse = 1000;
    	TIM_OC3Init(TIM8, &TIM8_OC3InitStructure);
    	//����CCR2�Ĵ�����Ӱ�ӼĴ�����ֱ�����������¼��Ÿ������ã�
    	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);
	}
    
    //TIM1����
    TIM_Cmd(TIM8, ENABLE);
    //TIM1_OCͨ�����PWM��һ��Ҫ�ӣ�
    TIM_CtrlPWMOutputs(TIM8, ENABLE);

}


