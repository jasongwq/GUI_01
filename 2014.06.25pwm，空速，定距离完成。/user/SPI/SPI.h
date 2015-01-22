#ifndef __SPI_H
#define __SPI_H
#include "stm32f10x.h"


#define GPIO_SPI1     GPIOA
#define RCC_SPI1      RCC_APB2Periph_GPIOA
#define SPI1_SCK      GPIO_Pin_5
#define SPI1_MISO     GPIO_Pin_6
#define SPI1_MOSI     GPIO_Pin_7

#define GPIO_SPI2     GPIOB
#define RCC_SPI2      RCC_APB2Periph_GPIOB
#define SPI2_SCK      GPIO_Pin_13
#define SPI2_MISO     GPIO_Pin_14
#define SPI2_MOSI     GPIO_Pin_15

#define GPIO_SPI3     GPIOB
#define RCC_SPI3      RCC_APB2Periph_GPIOB
#define SPI3_SCK      GPIO_Pin_3
#define SPI3_MISO     GPIO_Pin_4
#define SPI3_MOSI     GPIO_Pin_5


/********************  软件SPI  ***************************************/


#define SPI0_SCK	    GPIO_Pin_5
#define SPI0_GPIO_SCK	GPIOA
#define SPI0_RCC_SCK	RCC_APB2Periph_GPIOA

#define SPI0_MISO		GPIO_Pin_6
#define SPI0_GPIO_MISO	GPIOA
#define SPI0_RCC_MISO	RCC_APB2Periph_GPIOA

#define SPI0_MOSI	    GPIO_Pin_7
#define SPI0_GPIO_MOSI	GPIOA
#define SPI0_RCC_MOSI	RCC_APB2Periph_GPIOA

#define Clr_SPI0_SCK    {GPIO_ResetBits(SPI0_GPIO_SCK, SPI0_SCK);}		//SPI接口 SPI输入
#define Set_SPI0_SCK    {GPIO_SetBits(SPI0_GPIO_SCK, SPI0_SCK);}

#define Clr_SPI0_MOSI   {GPIO_ResetBits(SPI0_GPIO_MOSI, SPI0_MOSI);}		//SPI接口 SPI时钟
#define Set_SPI0_MOSI   {GPIO_SetBits(SPI0_GPIO_MOSI, SPI0_MOSI);}

#define MISO_SPI0 	    GPIO_ReadInputDataBit(SPI0_GPIO_MISO, SPI0_MISO)

																					  
void SPI1_Init(void);			 //初始化SPI口 
void SPI1_SetSpeed(u16 SPI_BaudRatePrescaler);
u8   SPI1_ReadWriteByte(u8 TxData);//SPI总线读写一个字节

void SPI2_Init(void);
void SPI2_SetSpeed(u16 SPI_BaudRatePrescaler);
u8   SPI2_ReadWriteByte(u8 TxData);

void SPI3_Init(void);
void SPI3_SetSpeed(u16 SPI_BaudRatePrescaler);
u8   SPI3_ReadWriteByte(u8 TxData);

void Disable_SWJ(void);

void SPI0_Init(void);
u8   SPI0_ReadWriteByte(u8 TxData);
		 
#endif

