#include "TIMER.h"
#include "stm32f10x.h"

void TIM_Init(TIM_TypeDef* TIMER,u16 Period,u16 Prescaler)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    if(TIMER==TIM1)     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	else if(TIMER==TIM2)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	else if(TIMER==TIM3)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	else if(TIMER==TIM4)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	else if(TIMER==TIM5)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	else if(TIMER==TIM6)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	else if(TIMER==TIM7)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	else if(TIMER==TIM8)RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
  
    /* ---------------------------------------------------------------
      TIM4 Configuration: Output Compare Timing Mode:
      TIM2CLK = 36 MHz, Prescaler = 7200, TIM2 counter clock = 7.2 MHz

	  72M/7200=0.1ms 0.1*10000=1s

	   // ���漰�߼�Ӧ�� �����ڶ�ʱ��ʱ��(CK_INT)Ƶ���������˲���(ETR,TIx)
    --------------------------------------------------------------- */

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = Period; 	                 //��������Զ�װ�صļ���ֵ�����ڼ����Ǵ�0��ʼ�ģ�����10000�κ�Ϊ9999
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;             // �������Ԥ��Ƶϵ����������Ϊ0ʱ��ʾ����Ƶ����Ҫ��1  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	             // ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
    TIM_TimeBaseInit(TIMER, &TIM_TimeBaseStructure);             //��ʼ����ʱ��

    TIM_ClearITPendingBit(TIMER, TIM_IT_Update);             	 //Clear TIM5 update pending flag[���TIM5����жϱ�־] 
    TIM_ITConfig(TIMER, TIM_IT_Update, ENABLE);				     //������ж�
    TIM_Cmd(TIMER, ENABLE);  //������ʹ�ܣ���ʼ����
}

void TIMER_NVIC_Configuration(u8 TIMER ,u8 PriorityGroup,u8 PreemptionPriority,u8 SubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure;

    if(PriorityGroup==0)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	else if(PriorityGroup==1)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	else if(PriorityGroup==2)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	else if(PriorityGroup==3)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	else if(PriorityGroup==4)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	else {}
   
    if(TIMER==10)NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	else if(TIMER==11)NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	else if(TIMER==12)NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_IRQn;
	else if(TIMER==13)NVIC_InitStructure.NVIC_IRQChannel = TIM1_TRG_COM_IRQn;
    else if(TIMER==2)NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	else if(TIMER==3)NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	else if(TIMER==4)NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	else if(TIMER==5)NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	else if(TIMER==6)NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	else if(TIMER==7)NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	else if(TIMER==80)NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;
	else if(TIMER==81)NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQn;
	else if(TIMER==82)NVIC_InitStructure.NVIC_IRQChannel = TIM8_BRK_IRQn;
	else if(TIMER==83)NVIC_InitStructure.NVIC_IRQChannel = TIM8_TRG_COM_IRQn;
	else {}
    if(PreemptionPriority!=0)NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/*
void TIM5_IRQHandler(void)
{ 
    static u32 counter = 0;
    if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
    {
    	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
    	if(counter==0)GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)0x01);
		if(counter==1)GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)0x00);
    	counter++;
		if(counter==2){counter=0;}
    }
}

*/
/*		  ����Ƚϴ���ģʽ
 *        �˹�������������һ��������Σ�����ֻ��һ�θ�����ʱ���Ѿ����
 *        �ڴ�ģʽ�� TIM_TImeBaseStructure.TIM_Period���ô�С��������ε�Ƶ��û���κ�Ӱ��
 *       (����һ��Ҫ����TIM_OCInitStructure.TIM_Pulse)��Ȼ��û������ʱ��Ͳ����жϣ���������϶������
 *
 *		  TIM_SetCompare4(TIM2, capture + CCR4_Val); �����Ѿ����Ƚ�ֵ����Ϊ������
 */
void TIM_Timing_Init(TIM_TypeDef* TIMER,u16 T)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
	//if(TIMER==TIM1)     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	if(TIMER==TIM2)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	else if(TIMER==TIM3)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	else if(TIMER==TIM4)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	else if(TIMER==TIM5)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	else if(TIMER==TIM6)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	else if(TIMER==TIM7)RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	else if(TIMER==TIM8)RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 65535;		 //ֻҪ��Ϊ�� TIM����ʱ�Ӿ���ϵͳʱ�ӵ�һ�㼴36M
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIMER, &TIM_TimeBaseStructure);

    /* Prescaler configuration */
    TIM_PrescalerConfig(TIMER, T, TIM_PSCReloadMode_Immediate);		//
}
void TIM_OC_Timing_Init(TIM_TypeDef* TIMER,u8 OC,u16 CCR_Val)
{
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR_Val;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;


       if(OC==1){TIM_OC1Init(TIMER, &TIM_OCInitStructure);	TIM_OC1PreloadConfig(TIMER, TIM_OCPreload_Disable);}
  else if(OC==2){TIM_OC2Init(TIMER, &TIM_OCInitStructure);TIM_OC2PreloadConfig(TIMER, TIM_OCPreload_Disable);}
	else if(OC==3){TIM_OC3Init(TIMER, &TIM_OCInitStructure);TIM_OC3PreloadConfig(TIMER, TIM_OCPreload_Disable);}
	else if(OC==4){TIM_OC4Init(TIMER, &TIM_OCInitStructure);TIM_OC4PreloadConfig(TIMER, TIM_OCPreload_Disable);}

    //TIM IT enable 
       if(OC==1)TIM_ITConfig(TIMER, TIM_IT_CC1, ENABLE);
	else if(OC==2)TIM_ITConfig(TIMER, TIM_IT_CC2, ENABLE);
	else if(OC==3)TIM_ITConfig(TIMER, TIM_IT_CC3, ENABLE);
	else if(OC==4)TIM_ITConfig(TIMER, TIM_IT_CC4, ENABLE);
	else {}

    //TIM2 enable counter 
    TIM_Cmd(TIMER, ENABLE);
}
/*
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
    {
    	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);

    	GPIO_WriteBit(GPIOC, GPIO_Pin_6, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_6)));
    	capture = TIM_GetCapture1(TIM2);
    	TIM_SetCompare1(TIM2, capture + CCR1_Val);
    }
    else if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
    {
    	TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);

    	GPIO_WriteBit(GPIOC, GPIO_Pin_7, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7)));
    	capture = TIM_GetCapture2(TIM2);
    	TIM_SetCompare2(TIM2, capture + CCR2_Val);
    }
    else if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
    {
    	TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);

    	GPIO_WriteBit(GPIOC, GPIO_Pin_8, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_8)));
    	capture = TIM_GetCapture3(TIM2);
    	TIM_SetCompare3(TIM2, capture + CCR3_Val);
    }
    else
    {
    	TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);

   		GPIO_WriteBit(GPIOC, GPIO_Pin_9, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9)));
    	capture = TIM_GetCapture4(TIM2);
    	TIM_SetCompare4(TIM2, capture + CCR4_Val);
    }
}

*/
