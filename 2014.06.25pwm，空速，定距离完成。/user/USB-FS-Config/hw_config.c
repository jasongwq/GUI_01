/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : hw_config.c
* Author             : MCD Application Team
* Version            : V3.3.0
* Date               : 21-March-2011
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/

#ifdef STM32L1XX_MD
 #include "stm32l1xx_it.h"
#else
 #include "stm32f10x_it.h"
#endif /* STM32L1XX_MD */
 
#include "hw_config.h"
#include "platform_config.h"
#include "mass_mal.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "usb_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



void Set_USBClock(void)
{
    /* Set the device clock */
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode
* Description    : Power-off system clocks and power while entering suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
  /* Set the device state to suspend */
  bDeviceState = SUSPENDED;
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode
* Description    : Restores system clocks and power while exiting suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else
  {
    bDeviceState = ATTACHED;
  }

}

/*******************************************************************************
* Function Name  : Led_Config
* Description    : configure the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Led_Config(void)
{
  /* Configure the LEDs */
//   STM_EVAL_LEDInit(LED1);
//   STM_EVAL_LEDInit(LED2);  
//   STM_EVAL_LEDInit(LED3);
//   STM_EVAL_LEDInit(LED4);  
}

/*******************************************************************************
* Function Name  : Led_RW_ON
* Description    : Turn ON the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Led_RW_ON(void)
{
//   STM_EVAL_LEDOn(LED3);
}

/*******************************************************************************
* Function Name  : Led_RW_OFF
* Description    : Turn off the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Led_RW_OFF(void)
{
//   STM_EVAL_LEDOff(LED3);
}
/*******************************************************************************
* Function Name  : USB_Configured_LED
* Description    : Turn ON the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Configured_LED(void)
{
//   STM_EVAL_LEDOn(LED1);
}

/*******************************************************************************
* Function Name  : USB_NotConfigured_LED
* Description    : Turn off the Read/Write LEDs.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_NotConfigured_LED(void)
{
//   STM_EVAL_LEDOff(LED1);
}

/*******************************************************************************
* Function Name  : USB_Cable_Config
* Description    : Software Connection/Disconnection of USB Cable.
* Input          : None.
* Return         : Status
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{
#ifdef STM32L1XX_MD
  if (NewState != DISABLE)
  {
    STM32L15_USB_CONNECT;
  }
  else
  {
    STM32L15_USB_DISCONNECT;
  }  

#elif defined(STM32F10X_CL) 
  if (NewState != DISABLE)
  {
    USB_DevConnect();
  }
  else
  {
    USB_DevDisconnect();
  }
  
#else 
  if (NewState != DISABLE)
  {
    Set_Pull_Up
  }
  else
  {
    Clr_Pull_Up
  }
#endif /* STM32L1XX_MD */
}

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
  uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

#ifdef STM32L1XX_MD
  Device_Serial0 = *(uint32_t*)(0x1FF80050);
  Device_Serial1 = *(uint32_t*)(0x1FF80054);
  Device_Serial2 = *(uint32_t*)(0x1FF80064);
#else  
  Device_Serial0 = *(__IO uint32_t*)(0x1FFFF7E8);
  Device_Serial1 = *(__IO uint32_t*)(0x1FFFF7EC);
  Device_Serial2 = *(__IO uint32_t*)(0x1FFFF7F0);
#endif /* STM32L1XX_MD */

  if (Device_Serial0 != 0)
  {
    MASS_StringSerial[2] = (uint8_t)(Device_Serial0 & 0x000000FF);
    MASS_StringSerial[4] = (uint8_t)((Device_Serial0 & 0x0000FF00) >> 8);
    MASS_StringSerial[6] = (uint8_t)((Device_Serial0 & 0x00FF0000) >> 16);
    MASS_StringSerial[8] = (uint8_t)((Device_Serial0 & 0xFF000000) >> 24);

    MASS_StringSerial[10] = (uint8_t)(Device_Serial1 & 0x000000FF);
    MASS_StringSerial[12] = (uint8_t)((Device_Serial1 & 0x0000FF00) >> 8);
    MASS_StringSerial[14] = (uint8_t)((Device_Serial1 & 0x00FF0000) >> 16);
    MASS_StringSerial[16] = (uint8_t)((Device_Serial1 & 0xFF000000) >> 24);

    MASS_StringSerial[18] = (uint8_t)(Device_Serial2 & 0x000000FF);
    MASS_StringSerial[20] = (uint8_t)((Device_Serial2 & 0x0000FF00) >> 8);
    MASS_StringSerial[22] = (uint8_t)((Device_Serial2 & 0x00FF0000) >> 16);
    MASS_StringSerial[24] = (uint8_t)((Device_Serial2 & 0xFF000000) >> 24);
  }
}



#ifdef STM32F10X_CL
/*******************************************************************************
* Function Name  : USB_OTG_BSP_uDelay.
* Description    : provide delay.
* Input          : Delay in micro seconds.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_OTG_BSP_uDelay (const uint32_t usec)
{
  RCC_ClocksTypeDef  RCC_Clocks;  
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);  
  RCC_GetClocksFreq(&RCC_Clocks); 
  SysTick_Config(usec * (RCC_Clocks.HCLK_Frequency / 1000000));   
  SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk ;
  while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
}
#endif

void USB_Interrupts_Config(u8 PriorityGroup,u8 PreemptionPriority,u8 SubPriority0,u8 SubPriority1)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	Set_USBClock();         // 开启USB时钟
  USB_Pull_Up_Init        // 设置USB连接控制线
	
	if(PriorityGroup==0)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	else if(PriorityGroup==1)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	else if(PriorityGroup==2)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	else if(PriorityGroup==3)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	else if(PriorityGroup==4)NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	else {}	  
	
	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	                        //USB低优先级中断请求
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;			//抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority0;				        //子优先级为1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USB_HP_CAN1_TX_IRQn;			                //USB高优先级中断请求
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;			//抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority1;				        //子优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
