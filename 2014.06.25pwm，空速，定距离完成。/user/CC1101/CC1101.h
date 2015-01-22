#ifndef __CC1101_H
#define __CC1101_H

#include "stm32f10x.h"

#define Fast_CC1101_GPIO  0
// GDO0 一般用途的数字输出脚： 测试信号FIFO状态信号时钟输出，
// 从XOSC向下分割连续输入TX数据,也用作原型/产品测试的模拟测试I/O
#define CC1101_GDO0        GPIO_Pin_0
#define GPIO_CC1101_GDO0   GPIOB
#define RCC_CC1101_GDO0    RCC_APB2Periph_GPIOB
// GDO2 数字输出 一般用途的数字输出脚： 测试信号FIFO状态信号时钟输出，从XOSC向下分割连续输入TX数据
#define CC1101_GDO2        GPIO_Pin_10
#define GPIO_CC1101_GDO2   GPIOB
#define RCC_CC1101_GDO2    RCC_APB2Periph_GPIOB
//SPI接口 SPI输入
#define CC1101_MISO        GPIO_Pin_14
#define GPIO_CC1101_MISO   GPIOB
#define RCC_CC1101_MISO    RCC_APB2Periph_GPIOB
//SPI接口 SPI输出
#define CC1101_MOSI        GPIO_Pin_15
#define GPIO_CC1101_MOSI   GPIOB
#define RCC_CC1101_MOSI    RCC_APB2Periph_GPIOB
//SPI接口 SPI时钟
#define CC1101_SCK         GPIO_Pin_13
#define GPIO_CC1101_SCK    GPIOB
#define RCC_CC1101_SCK     RCC_APB2Periph_GPIOB
//SPI时能
#define CC1101_CSN         GPIO_Pin_5
#define GPIO_CC1101_CSN    GPIOC
#define RCC_CC1101_CSN     RCC_APB2Periph_GPIOC

#if    Fast_CC1101_GPIO==0

#define Clr_CC1101_GDO2    {GPIO_ResetBits(GPIO_CC1101_GDO2, CC1101_GDO2);}		
#define Set_CC1101_GDO2    {GPIO_SetBits(GPIO_CC1101_GDO2, CC1101_GDO2);}
//SPI接口 SPI输出
#define Clr_CC1101_MOSI    {GPIO_ResetBits(GPIO_CC1101_MOSI, CC1101_MOSI);}		
#define Set_CC1101_MOSI    {GPIO_SetBits(GPIO_CC1101_MOSI, CC1101_MOSI);}
//SPI接口 SPI时钟
#define Clr_CC1101_SCK     {GPIO_ResetBits(GPIO_CC1101_SCK, CC1101_SCK);}		
#define Set_CC1101_SCK     {GPIO_SetBits(GPIO_CC1101_SCK, CC1101_SCK);}
//SPI时能
#define Clr_CC1101_CSN     {GPIO_ResetBits(GPIO_CC1101_CSN, CC1101_CSN);}		
#define Set_CC1101_CSN     {GPIO_SetBits(GPIO_CC1101_CSN, CC1101_CSN);}
//SPI接口 SPI输入
#define CC1101MISO 	   GPIO_ReadInputDataBit(GPIO_CC1101_MISO, CC1101_MISO)

#define CC1101GDO0     GPIO_ReadInputDataBit(GPIO_CC1101_GDO0, CC1101_GDO0)		
#elif  Fast_CC1101_GPIO==1

#define Clr_CC1101_GDO2    GPIOE->BRR=1<<11 ;		
#define Set_CC1101_GDO2    GPIOE->BSRR=1<<11 ;
//SPI接口 SPI输出
#define Clr_CC1101_MOSI    GPIOE->BRR=1<<8 ;		
#define Set_CC1101_MOSI    GPIOE->BSRR=1<<8 ;
//SPI接口 SPI时钟
#define Clr_CC1101_SCK     GPIOE->BRR=1<<9 ;		
#define Set_CC1101_SCK     GPIOE->BSRR=1<<9 ;
//SPI时能
#define Clr_CC1101_CSN     GPIOE->BRR=1<<12 ;		
#define Set_CC1101_CSN     GPIOE->BSRR=1<<12 ;
//SPI接口 SPI输入
#define CC1101MISO		   ((GPIOE->IDR&(1<<10))?1:0)
#define CC1101GDO0         ((GPIOE->IDR&(1<<13))?1:0)
#else
#endif


void   CC1101_GPIO_Init(void);
u8     SpiTxRxByte(u8 dat);
u8     Check_CC1101(void);
void   SpiWriteReg(u8 addr, u8 value);
void   SpiWriteBurstReg(u8 addr, u8 *buffer, u8 count) ;
void   SpiStrobe(u8 strobe);
u8     SpiReadReg(u8 addr);
void   SpiReadBurstReg(u8 addr, u8 *buffer, u8 count);
u8     SpiReadStatus(u8 addr);
void   RESET_CC1100(void);
void   POWER_UP_RESET_CC1100(void);
void   CC1101_Init(void);
u8     ReceivePacket(u8 *rxBuffer, u8 *length);
void   SendPacket(u8 *txBuffer, u8 size);
/*
 *     作为发射      CC1101_GPIO_Init();							     作为接收 	  CC1101_GPIO_Init();
 *					 if(Check_CC1101())printf("\r\n Check_CC1101_OK");				  if(Check_CC1101())printf("\r\n Check_CC1101_OK");
 *					 else printf("\r\n Check_CC1101_Fail");							  else printf("\r\n Check_CC1101_Fail");
 *
 *					 CC1101_Init();													  CC1101_Init();
 *					 SendPacket(TxBuf, 60);			 //发射不需要延时				  if(ReceivePacket(RxBuf,&len))			 内部必须加延时 确保稳定
 *																						   printf("\r\n RxBuf= %s",RxBuf);
 *
 *
 */


// CC1100 STROBE, CONTROL AND STATUS REGSITER
#define CCxxx0_IOCFG2       0x00        // GDO2 output pin configuration
#define CCxxx0_IOCFG1       0x01        // GDO1 output pin configuration
#define CCxxx0_IOCFG0       0x02        // GDO0 output pin configuration
#define CCxxx0_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define CCxxx0_SYNC1        0x04        // Sync word, high INT8U
#define CCxxx0_SYNC0        0x05        // Sync word, low INT8U
#define CCxxx0_PKTLEN       0x06        // Packet length
#define CCxxx0_PKTCTRL1     0x07        // Packet automation control
#define CCxxx0_PKTCTRL0     0x08        // Packet automation control
#define CCxxx0_ADDR         0x09        // Device address
#define CCxxx0_CHANNR       0x0A        // Channel number
#define CCxxx0_FSCTRL1      0x0B        // Frequency synthesizer control
#define CCxxx0_FSCTRL0      0x0C        // Frequency synthesizer control
#define CCxxx0_FREQ2        0x0D        // Frequency control word, high INT8U
#define CCxxx0_FREQ1        0x0E        // Frequency control word, middle INT8U
#define CCxxx0_FREQ0        0x0F        // Frequency control word, low INT8U
#define CCxxx0_MDMCFG4      0x10        // Modem configuration
#define CCxxx0_MDMCFG3      0x11        // Modem configuration
#define CCxxx0_MDMCFG2      0x12        // Modem configuration
#define CCxxx0_MDMCFG1      0x13        // Modem configuration
#define CCxxx0_MDMCFG0      0x14        // Modem configuration
#define CCxxx0_DEVIATN      0x15        // Modem deviation setting
#define CCxxx0_MCSM2        0x16        // Main Radio Control State Machine configuration
#define CCxxx0_MCSM1        0x17        // Main Radio Control State Machine configuration
#define CCxxx0_MCSM0        0x18        // Main Radio Control State Machine configuration
#define CCxxx0_FOCCFG       0x19        // Frequency Offset Compensation configuration
#define CCxxx0_BSCFG        0x1A        // Bit Synchronization configuration
#define CCxxx0_AGCCTRL2     0x1B        // AGC control
#define CCxxx0_AGCCTRL1     0x1C        // AGC control
#define CCxxx0_AGCCTRL0     0x1D        // AGC control
#define CCxxx0_WOREVT1      0x1E        // High INT8U Event 0 timeout
#define CCxxx0_WOREVT0      0x1F        // Low INT8U Event 0 timeout
#define CCxxx0_WORCTRL      0x20        // Wake On Radio control
#define CCxxx0_FREND1       0x21        // Front end RX configuration
#define CCxxx0_FREND0       0x22        // Front end TX configuration
#define CCxxx0_FSCAL3       0x23        // Frequency synthesizer calibration
#define CCxxx0_FSCAL2       0x24        // Frequency synthesizer calibration
#define CCxxx0_FSCAL1       0x25        // Frequency synthesizer calibration
#define CCxxx0_FSCAL0       0x26        // Frequency synthesizer calibration
#define CCxxx0_RCCTRL1      0x27        // RC oscillator configuration
#define CCxxx0_RCCTRL0      0x28        // RC oscillator configuration
#define CCxxx0_FSTEST       0x29        // Frequency synthesizer calibration control
#define CCxxx0_PTEST        0x2A        // Production test
#define CCxxx0_AGCTEST      0x2B        // AGC test
#define CCxxx0_TEST2        0x2C        // Various test settings
#define CCxxx0_TEST1        0x2D        // Various test settings
#define CCxxx0_TEST0        0x2E        // Various test settings

#define 	WRITE_BURST     	0x40						//连续写入
#define 	READ_SINGLE     	0x80						//读
#define 	READ_BURST      	0xC0						//连续读
#define 	BYTES_IN_RXFIFO     0x7F  						//接收缓冲区的有效字节数
#define 	CRC_OK              0x80 						//CRC校验通过位标志
// Strobe commands
#define CCxxx0_SRES         0x30        // Reset chip.
#define CCxxx0_SFSTXON      0x31        // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
                                        // If in RX/TX: Go to a wait state where only the synthesizer is
                                        // running (for quick RX / TX turnaround).
#define CCxxx0_SXOFF        0x32        // Turn off crystal oscillator.
#define CCxxx0_SCAL         0x33        // Calibrate frequency synthesizer and turn it off
                                        // (enables quick start).
#define CCxxx0_SRX          0x34        // Enable RX. Perform calibration first if coming from IDLE and
                                        // MCSM0.FS_AUTOCAL=1.
#define CCxxx0_STX          0x35        // In IDLE state: Enable TX. Perform calibration first if
                                        // MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
                                        // Only go to TX if channel is clear.
#define CCxxx0_SIDLE        0x36        // Exit RX / TX, turn off frequency synthesizer and exit
                                        // Wake-On-Radio mode if applicable.
#define CCxxx0_SAFC         0x37        // Perform AFC adjustment of the frequency synthesizer
#define CCxxx0_SWOR         0x38        // Start automatic RX polling sequence (Wake-on-Radio)
#define CCxxx0_SPWD         0x39        // Enter power down mode when CSn goes high.
#define CCxxx0_SFRX         0x3A        // Flush the RX FIFO buffer.
#define CCxxx0_SFTX         0x3B        // Flush the TX FIFO buffer.
#define CCxxx0_SWORRST      0x3C        // Reset real time clock.
#define CCxxx0_SNOP         0x3D        // No operation. May be used to pad strobe commands to two
                                        // INT8Us for simpler software.

#define CCxxx0_PARTNUM      0x30
#define CCxxx0_VERSION      0x31
#define CCxxx0_FREQEST      0x32
#define CCxxx0_LQI          0x33
#define CCxxx0_RSSI         0x34
#define CCxxx0_MARCSTATE    0x35
#define CCxxx0_WORTIME1     0x36
#define CCxxx0_WORTIME0     0x37
#define CCxxx0_PKTSTATUS    0x38
#define CCxxx0_VCO_VC_DAC   0x39
#define CCxxx0_TXBYTES      0x3A
#define CCxxx0_RXBYTES      0x3B

#define CCxxx0_PATABLE      0x3E
#define CCxxx0_TXFIFO       0x3F
#define CCxxx0_RXFIFO       0x3F




#endif
