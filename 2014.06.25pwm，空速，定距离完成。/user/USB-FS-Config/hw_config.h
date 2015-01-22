/* 



*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "GPIO.h"

#define USB_Pull_Up_Init  PC7_OUT
#define Set_Pull_Up       Set_C7
#define Clr_Pull_Up       Clr_C7


#define BULK_MAX_PACKET_SIZE  0x00000040
//#define BULK_MAX_PACKET_SIZE  256
/* Exported functions ------------------------------------------------------- */
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void Led_Config(void);
void Led_RW_ON(void);
void Led_RW_OFF(void);
void USB_Configured_LED(void);
void USB_NotConfigured_LED(void);
void USB_Cable_Config (FunctionalState NewState);
void Get_SerialNum(void);
void USB_Interrupts_Config(u8 PriorityGroup,u8 PreemptionPriority,u8 SubPriority0,u8 SubPriority1);// 分组  抢占优先级   从优先级  从优先级
/* External variables --------------------------------------------------------*/

#endif  

