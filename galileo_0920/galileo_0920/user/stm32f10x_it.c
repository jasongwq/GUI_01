/***************************************************************/
#include "stm32f10x_it.h"
#include "gpio.h"
#include "delay.h"
#include "usart.h"
/***************************************************************/
extern u8 USART_RX[60];
extern u8 USART_mark;
extern int USART_control;

/***************************************************************/
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)     //Check whether receiving interrupt
	{
		USART_RX[USART_mark++] = USART_ReceiveData(USART1);   // Read one byte from the receive data register
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		if(USART_mark ==60){USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);}			
	}
}

/***************************************************************/
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)     //Check whether receiving interrupt
	{
		USART_RX[USART_mark++] = USART_ReceiveData(USART2);     // Read one byte from the receive data register
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		if(USART_mark ==60){USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);}			
	}
}

/***************************************************************/
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)     //Check whether receiving interrupt
	{
		USART_RX[USART_mark++] = USART_ReceiveData(USART3);     // Read one byte from the receive data register
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		if(USART_mark ==60){USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);}			
	}
}
/***************************************************************/


