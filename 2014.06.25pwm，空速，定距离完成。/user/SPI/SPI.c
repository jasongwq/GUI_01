/*
              SPI 模块配置初始化


 */
#include "SPI.h"
#include "stm32f10x.h"

static SPI_InitTypeDef  SPI1_InitStructure,SPI2_InitStructure,SPI3_InitStructure;

//串行外设接口SPI的初始化，SPI配置成主模式							  
//本例程选用神舟系列开发板处理器的SPI对NRF24L01进行读写操作，先对SPI进行初始化
void SPI1_Init(void)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
    
    // Enable SPI and GPIO clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 ,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /* Configure SPI1 pins: SCK, MISO and MOSI */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* SPI1 configuration */                                            //初始化SPI结构体
	SPI1_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI设置为两线全双工
	SPI1_InitStructure.SPI_Mode = SPI_Mode_Master;		                //设置SPI为主模式
	SPI1_InitStructure.SPI_DataSize = SPI_DataSize_8b;		            //SPI发送接收8位帧结构
	SPI1_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                    //串行时钟在不操作时，时钟为低电平
	SPI1_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                    //第一个时钟沿开始采样数据
	SPI1_InitStructure.SPI_NSS = SPI_NSS_Soft;		                    //NSS信号由软件（使用SSI位）管理
	SPI1_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //SPI波特率预分频值为8
	SPI1_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //数据传输从MSB位开始
	SPI1_InitStructure.SPI_CRCPolynomial = 7;	                        //CRC值计算的多项式

	SPI_Init(SPI1, &SPI1_InitStructure);   //根据SPI_InitStruct中指定的参数初始化外设SPI2寄存器
	
	/* Enable SPI1  */
	SPI_Cmd(SPI1, ENABLE);                                      //使能SPI外设
	
	SPI1_ReadWriteByte(0xff);                                            //启动传输		 
}  
void SPI1_SetSpeed(u16 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI1_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler; 
	SPI_Init(SPI1, &SPI1_InitStructure);
	SPI_Cmd(SPI1,ENABLE); 
}
u8 SPI1_ReadWriteByte(u8 TxData)                                        //SPI读写数据函数
{		
	u8 retry=0;				 	
	/* Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)      //发送缓存标志位为空
	{
		retry++;
		if(retry>200)return 0;
	}			  
	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI1, TxData);                                    //通过外设SPI1发送一个数据
	retry=0;
	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);   //接收缓存标志位不为空
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI1);                                 //通过SPI1返回接收数据				    
}

void SPI2_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );             //PORTB时钟使能 
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );             //SPI2时钟使能 	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                     //PB13/14/15复用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);                              //初始化GPIOB

 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);            //PB13/14/15上拉

	SPI2_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI2_InitStructure.SPI_Mode = SPI_Mode_Master;		                //设置SPI工作模式:设置为主SPI
	SPI2_InitStructure.SPI_DataSize = SPI_DataSize_8b;		            //设置SPI的数据大小:SPI发送接收8位帧结构
	SPI2_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                    //串行同步时钟的空闲状态为高电平
	SPI2_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                    //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI2_InitStructure.SPI_NSS = SPI_NSS_Soft;		                    //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI2_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //定义波特率预分频的值:波特率预分频值为8
	SPI2_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI2_InitStructure.SPI_CRCPolynomial = 7;	                        //CRC值计算的多项式
	SPI_Init(SPI2, &SPI2_InitStructure);                                 //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI2, ENABLE); //使能SPI外设
	
	SPI2_ReadWriteByte(0xff);//启动传输		 
 

}   
//SPI 速度设置函数
//SpeedSet:
//SPI_BaudRatePrescaler_2   2分频   
//SPI_BaudRatePrescaler_8   8分频   
//SPI_BaudRatePrescaler_16  16分频  
//SPI_BaudRatePrescaler_256 256分频 
  
void SPI2_SetSpeed(u16 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler; 
	SPI_Init(SPI2, &SPI2_InitStructure);
	SPI_Cmd(SPI2,ENABLE); 
} 

//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)//检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据					    
}
void SPI3_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	Disable_SWJ();

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );             //PORTB时钟使能 
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI3,  ENABLE );             //SPI2时钟使能 	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                     //PB3/4/5复用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);                              //初始化GPIOB

 	GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);            //PB13/14/15上拉

	SPI3_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI3_InitStructure.SPI_Mode = SPI_Mode_Master;		                //设置SPI工作模式:设置为主SPI
	SPI3_InitStructure.SPI_DataSize = SPI_DataSize_8b;		            //设置SPI的数据大小:SPI发送接收8位帧结构
	SPI3_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                    //串行同步时钟的空闲状态为高电平
	SPI3_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                    //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI3_InitStructure.SPI_NSS = SPI_NSS_Soft;		                    //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI3_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //定义波特率预分频的值:波特率预分频值为8
	SPI3_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI3_InitStructure.SPI_CRCPolynomial = 7;	                        //CRC值计算的多项式
	SPI_Init(SPI3, &SPI3_InitStructure);                                 //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI3, ENABLE); //使能SPI外设
	
	SPI3_ReadWriteByte(0xff);//启动传输		 
 

}   
//SPI 速度设置函数
//SpeedSet:
//SPI_BaudRatePrescaler_2   2分频   
//SPI_BaudRatePrescaler_8   8分频   
//SPI_BaudRatePrescaler_16  16分频  
//SPI_BaudRatePrescaler_256 256分频 
  
void SPI3_SetSpeed(u16 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI3_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler; 
	SPI_Init(SPI3, &SPI3_InitStructure);
	SPI_Cmd(SPI3,ENABLE); 
} 

//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI3_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI3, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET)//检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI3); //返回通过SPIx最近接收的数据					    
}

void Disable_SWJ(void)
{																  
	//GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);		 	  // PB3 PB4 		 这样之后才可以用
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		  // PA13 PA14 PA15  这样之后才可以用

}

void SPI0_Init(void)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
    
	RCC_APB2PeriphClockCmd(SPI0_RCC_SCK | SPI0_RCC_MOSI | SPI0_RCC_MISO, ENABLE);
  
    GPIO_InitStructure.GPIO_Pin =SPI0_SCK;		  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 
    GPIO_Init(SPI0_GPIO_SCK, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =SPI0_MOSI;				 
    GPIO_Init(SPI0_GPIO_MOSI, &GPIO_InitStructure);
						 
    GPIO_InitStructure.GPIO_Pin = SPI0_MISO;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU  ;     //上拉输入
	GPIO_Init(SPI0_GPIO_MISO, &GPIO_InitStructure);
	
	SPI0_ReadWriteByte(0xff);                                            //启动传输		 
} 
/*写一个 byte 到芯片，并返回一个 byte*/ 
u8 SPI0_ReadWriteByte(u8 TxData)                                        //SPI读写数据函数
{			                                                                 
	u8 i;
	for(i=0;i<8;i++)   
	{
		if(TxData & 0x80){Set_SPI0_MOSI}
		else{Clr_SPI0_MOSI}

		TxData = (TxData << 1);                    // shift next bit into MSB..
		Set_SPI0_SCK						     // Set SCK high..
		TxData |= MISO_SPI0;       		         // capture current MISO bit
		Clr_SPI0_SCK            		         // ..then set SCK low again
	}
	return(TxData);           		             // return read UINT8				    
}
