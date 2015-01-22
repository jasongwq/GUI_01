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

	   // 不涉及高级应用 定义在定时器时钟(CK_INT)频率与数字滤波器(ETR,TIx)
    --------------------------------------------------------------- */

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = Period; 	                 //这个就是自动装载的计数值，由于计数是从0开始的，计数10000次后为9999
    TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;             // 这个就是预分频系数，当由于为0时表示不分频所以要减1  
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	             // 使用的采样频率之间的分频比例
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
    TIM_TimeBaseInit(TIMER, &TIM_TimeBaseStructure);             //初始化定时器

    TIM_ClearITPendingBit(TIMER, TIM_IT_Update);             	 //Clear TIM5 update pending flag[清除TIM5溢出中断标志] 
    TIM_ITConfig(TIMER, TIM_IT_Update, ENABLE);				     //打开溢出中断
    TIM_Cmd(TIMER, ENABLE);  //计数器使能，开始工作
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
/*		  输出比较触发模式
 *        此功能是用来控制一个输出波形，或者只是一段给定的时间已经到达。
 *        在此模式下 TIM_TImeBaseStructure.TIM_Period配置大小对输出波形的频率没有任何影响
 *       (但是一定要大于TIM_OCInitStructure.TIM_Pulse)不然还没到更新时间就产生中断，这样结果肯定会错误
 *
 *		  TIM_SetCompare4(TIM2, capture + CCR4_Val); 这里已经将比较值设置为了两倍
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
    TIM_TimeBaseStructure.TIM_Period = 65535;		 //只要不为零 TIM计数时钟就是系统时钟的一般即36M
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
