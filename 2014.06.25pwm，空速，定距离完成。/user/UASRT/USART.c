#include "stm32f10x.h"
#include "USART.h"
#include <stdio.h>

#ifdef __GNUC__
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif


#ifdef USE_USART1
u8 RxCounter1=0;
u8 RxBuffer1[100]={"1ce shi \t"};
#endif
#ifdef USE_USART2
u8 RxCounter2=0;
u8 RxBuffer2[100]={"2ce shi "};
#endif
#ifdef USE_USART3
u8 RxCounter3=0;
u8 RxBuffer3[100]={"3ce shi "};
#endif
#ifdef USE_UART4
u8 RxCounter4=0;
u8 RxBuffer4[100]={"4ce shi "};
#endif
#ifdef USE_UART5
u8 RxCounter5=0;
u8 RxBuffer5[100]={"5ce shi "};
#endif

void USART1_Configuration(u32 BaudRate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

    /* Enable GPIOx clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
    /* Configure the USARTx */ 
    USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /* Enable the USARTx */
    USART_Cmd(USART1, ENABLE);
}
void USART2_Configuration(u32 BaudRate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

    /* Enable GPIOx clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /* Enable AFIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* Enable the USART2 Pins Software Remapping */
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);

	/* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
    /* Configure the USARTx */ 
    USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    /* Enable the USARTx */
    USART_Cmd(USART2, ENABLE);
}
void USART3_Configuration(u32 BaudRate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

    /* Enable GPIOx clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
    /* Configure the USARTx */ 
    USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    /* Enable the USARTx */
    USART_Cmd(USART3, ENABLE);
}
void USART4_Configuration(u32 BaudRate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

    /* Enable GPIOx clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	/* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);



    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
    /* Configure the USARTx */ 
    USART_Init(UART4, &USART_InitStructure);
	USART_ITConfig(UART4,USART_IT_RXNE, ENABLE);
    /* Enable the USARTx */
    USART_Cmd(UART4, ENABLE);
 
}
void USART5_Configuration(u32 BaudRate)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

    /* Enable GPIOx clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);


	/* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);


    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
    /* Configure the USARTx */ 
    USART_Init(UART5, &USART_InitStructure);
	USART_ITConfig(UART5,USART_IT_RXNE, ENABLE);
    /* Enable the USARTx */
    USART_Cmd(UART5, ENABLE);
}
void USART_NVIC_Configuration(u8 USART ,u8 PriorityGroup,u8 PreemptionPriority,u8 SubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure;

    if(PriorityGroup==0)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	else if(PriorityGroup==1)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	else if(PriorityGroup==2)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	else if(PriorityGroup==3)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	else if(PriorityGroup==4)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	else {}
  
    // Enable the USART1_3_IRQn Interrupt 
    if(USART==1)NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//EXTI9_5_IRQn; //EXTI2_IRQn EXTI4_IRQn EXTI15_10_IRQn
	else if(USART==2)NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	else if(USART==3)NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	else if(USART==4)NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	else if(USART==5)NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	else {}
    if(PreemptionPriority!=0)NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/*************************发送ASCII码制**********************************************/
void Send_ASCII(u8 USART , u8 *b)         
{	
    if(USART==1)
	{
	    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        for (;*b!='\0';b++)
   	    {
		    USART_SendData(USART1, *b);
		    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	 //必须加
	    }
	}
	else if(USART==2)
	{
	    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
        for (;*b!='\0';b++)
   	    {
		    USART_SendData(USART2, *b);
		    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	 //必须加
	    }
	}
	else if(USART==3)
	{
	    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
        for (;*b!='\0';b++)
   	    {
		    USART_SendData(USART3, *b);
		    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	 //必须加
	    }
	}
	else if(USART==4)
	{
	    while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
        for (;*b!='\0';b++)
   	    {
		    USART_SendData(UART4, *b);
		    while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);	 //必须加
	    }
	}
	else if(USART==5)
	{
	    while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
        for (;*b!='\0';b++)
   	    {
		    USART_SendData(UART5, *b);
		    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);	 //必须加
	    }
	}	   
}

/*************************发送16进制数**********************************************/
void Send_Hex(u8 USART,u8 c)         
{
    if(USART==1)
	{
	    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	  //发送区为空
        USART_SendData(USART1, c);
	    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);	 //发送完成
	}
	else if(USART==2)
	{
	    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	  //发送区为空
        USART_SendData(USART2, c);
	    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);	 //发送完成
	}
	else if(USART==3)
	{
	    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	  //发送区为空
        USART_SendData(USART3, c);
	    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	 //发送完成
	}
	else if(USART==4)
	{
	    while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);	  //发送区为空
        USART_SendData(UART4, c);
	    while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);	 //发送完成
	}
	else if(USART==5)
	{
	    while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);	  //发送区为空
        USART_SendData(UART5, c);
	    while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET);	 //发送完成
	}
}
void Send_USART_Hex(u8 USART,u8 *b,u8 i)
{
	u8 j;
    for(j=0;j<i;j++)Send_Hex(USART,*(b+j));
}
/***********************************************************************************/
/*                            串口接收中断程序                                     */
/***********************************************************************************/
#ifdef USE_USART1
void USART1_IRQHandler(void)
{

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        RxBuffer1[RxCounter1++] = USART_ReceiveData(USART1);
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
        if(RxCounter1 == 100)
            USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    }
}
#endif
#ifdef USE_USART2
void USART2_IRQHandler(void)
{

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        RxBuffer2[RxCounter2++] = USART_ReceiveData(USART2);
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
        if(RxCounter2 == 100)
            USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
    }
}
#endif
#ifdef USE_USART3
void USART3_IRQHandler(void)
{

    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        RxBuffer3[RxCounter3++] = USART_ReceiveData(USART3);
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
        if(RxCounter3 == 100)
            USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
    }
}
#endif
#ifdef USE_UART4
void UART4_IRQHandler(void)
{

    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
    {
        RxBuffer4[RxCounter4++] = USART_ReceiveData(UART4);
        USART_ClearITPendingBit(UART4, USART_IT_RXNE);
        if(RxCounter4 == 100)
            USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);
    }
}
#endif
#ifdef USE_UART5
void UART5_IRQHandler(void)
{

    if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
    {
        RxBuffer5[RxCounter5++] = USART_ReceiveData(UART5);
        USART_ClearITPendingBit(UART5, USART_IT_RXNE);
        if(RxCounter5 == 100)
            USART_ITConfig(UART5, USART_IT_RXNE, DISABLE);
    }
}
#endif
/***********************************************************************************/
/***********************************************************************/
PUTCHAR_PROTOTYPE
{
    USART_SendData(Print_USART, (uint8_t) ch);
    while (USART_GetFlagStatus(Print_USART, USART_FLAG_TC) == RESET){}
    return ch;
}
