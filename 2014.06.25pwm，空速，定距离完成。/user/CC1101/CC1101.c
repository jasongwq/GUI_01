#include "delay.h"
#include "CC1101.h"
#include "stm32f10x.h"

//u8 PaTabel[8] = {0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04 ,0x04};  //-30dBm   功率最小
u8 PaTabel[8] = {0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60};  //0dBm		              //很稳定
//u8 PaTabel[8] = {0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0 ,0xC0};   //10dBm     功率最大	  //不是很稳定
// RF_SETTINGS is a data structure which contains all relevant CCxxx0 registers
typedef struct S_RF_SETTINGS
{
	u8 FSCTRL2;		//自已加的
    u8 FSCTRL1;   // Frequency synthesizer control.
    u8 FSCTRL0;   // Frequency synthesizer control.
    u8 FREQ2;     // Frequency control word, high INT8U.
    u8 FREQ1;     // Frequency control word, middle INT8U.
    u8 FREQ0;     // Frequency control word, low INT8U.
    u8 MDMCFG4;   // Modem configuration.
    u8 MDMCFG3;   // Modem configuration.
    u8 MDMCFG2;   // Modem configuration.
    u8 MDMCFG1;   // Modem configuration.
    u8 MDMCFG0;   // Modem configuration.
    u8 CHANNR;    // Channel number.
    u8 DEVIATN;   // Modem deviation setting (when FSK modulation is enabled).
    u8 FREND1;    // Front end RX configuration.
    u8 FREND0;    // Front end RX configuration.
    u8 MCSM0;     // Main Radio Control State Machine configuration.
    u8 FOCCFG;    // Frequency Offset Compensation Configuration.
    u8 BSCFG;     // Bit synchronization Configuration.
    u8 AGCCTRL2;  // AGC control.
	u8 AGCCTRL1;  // AGC control.
    u8 AGCCTRL0;  // AGC control.
    u8 FSCAL3;    // Frequency synthesizer calibration.
    u8 FSCAL2;    // Frequency synthesizer calibration.
	u8 FSCAL1;    // Frequency synthesizer calibration.
    u8 FSCAL0;    // Frequency synthesizer calibration.
    u8 FSTEST;    // Frequency synthesizer calibration control
    u8 TEST2;     // Various test settings.
    u8 TEST1;     // Various test settings.
    u8 TEST0;     // Various test settings.
    u8 IOCFG2;    // GDO2 output pin configuration
    u8 IOCFG0;    // GDO0 output pin configuration
    u8 PKTCTRL1;  // Packet automation control.
    u8 PKTCTRL0;  // Packet automation control.
    u8 ADDR;      // Device address.
    u8 PKTLEN;    // Packet length.
} RF_SETTINGS;
const RF_SETTINGS rfSettings = 
{
	0x00,
    0x08,   // FSCTRL1   Frequency synthesizer control.
    0x00,   // FSCTRL0   Frequency synthesizer control.
    0x10,   // FREQ2     Frequency control word, high byte.
    0xA7,   // FREQ1     Frequency control word, middle byte.
    0x62,   // FREQ0     Frequency control word, low byte.
    0x5B,   // MDMCFG4   Modem configuration.
    0xF8,   // MDMCFG3   Modem configuration.
    0x03,   // MDMCFG2   Modem configuration.
    0x22,   // MDMCFG1   Modem configuration.
    0xF8,   // MDMCFG0   Modem configuration.

    0x00,   // CHANNR    Channel number.
    0x47,   // DEVIATN   Modem deviation setting (when FSK modulation is enabled).
    0xB6,   // FREND1    Front end RX configuration.
    0x10,   // FREND0    Front end RX configuration.
    0x18,   // MCSM0     Main Radio Control State Machine configuration.
    0x1D,   // FOCCFG    Frequency Offset Compensation Configuration.
    0x1C,   // BSCFG     Bit synchronization Configuration.
    0xC7,   // AGCCTRL2  AGC control.
    0x00,   // AGCCTRL1  AGC control.
    0xB2,   // AGCCTRL0  AGC control.

    0xEA,   // FSCAL3    Frequency synthesizer calibration.
    0x2A,   // FSCAL2    Frequency synthesizer calibration.
    0x00,   // FSCAL1    Frequency synthesizer calibration.
    0x11,   // FSCAL0    Frequency synthesizer calibration.
    0x59,   // FSTEST    Frequency synthesizer calibration.
    0x81,   // TEST2     Various test settings.
    0x35,   // TEST1     Various test settings.
    0x09,   // TEST0     Various test settings.
    0x0B,   // IOCFG2    GDO2 output pin configuration.
    0x06,   // IOCFG0D   GDO0 output pin configuration. Refer to SmartRF?Studio User Manual for detailed pseudo register explanation.

    0x04,   // PKTCTRL1  Packet automation control.
    0x05,   // PKTCTRL0  Packet automation control.
    0x00,   // ADDR      Device address.
    0x40    // PKTLEN    Packet length.			   这就是 发送数据包的长度  原来是 0x0c 最大只有 12 字节	现在为 0x40但是64字节不行，60还稳定，再上去也不稳定了
};
void CC1101_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
//控制写数据是否允许，低电平有效
    RCC_APB2PeriphClockCmd(RCC_CC1101_GDO0 | RCC_CC1101_GDO2 | RCC_CC1101_MISO
	                     | RCC_CC1101_MOSI | RCC_CC1101_SCK | RCC_CC1101_CSN, ENABLE);    //使能GPIO的时钟	
 
  GPIO_InitStructure.GPIO_Pin = CC1101_GDO2 ;                       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;              //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_CC1101_GDO2, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = CC1101_MOSI ;                       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;              //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_CC1101_MOSI, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = CC1101_SCK ;                       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;              //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_CC1101_SCK, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = CC1101_CSN ;                       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;              //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_CC1101_CSN, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = CC1101_MISO ;                       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				  //上啦输入
	GPIO_Init(GPIO_CC1101_MISO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = CC1101_GDO0 ;                       
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				  //上啦输入
	GPIO_Init(GPIO_CC1101_GDO0, &GPIO_InitStructure);
}
//*****************************************************************************************
//函数名：SpisendByte(INT8U dat)
//输入：发送的数据
//输出：无
//功能描述：SPI发送一个字节
//*****************************************************************************************
u8 SpiTxRxByte(u8 dat)
{
	u8 i,temp;
	temp = 0;
	
	Clr_CC1101_SCK
	for(i=0; i<8; i++)
	{
		if(dat & 0x80)
			Set_CC1101_MOSI
		else Clr_CC1101_MOSI
		dat <<= 1;
		Set_CC1101_SCK 
		temp <<= 1;
		if(CC1101MISO)temp++; 
		Clr_CC1101_SCK	
	}
	return temp;
}
//检测模块是否和单片机连接正常
u8 Check_CC1101(void)
{
    SpiWriteReg(0x00, 33);
	  if(SpiReadReg(0x00)==33){SpiWriteReg(0x00, 41);return 1 ;}
	  else {SpiWriteReg(0x00, 41);return 0 ;}
}
//功能描述：SPI写寄存器
void SpiWriteReg(u8 addr, u8 value) 
{
    Clr_CC1101_CSN
    SpiTxRxByte(addr);		//写地址
    SpiTxRxByte(value);		//写入配置
    Set_CC1101_CSN
}
//功能描述：SPI连续写配置寄存器
void SpiWriteBurstReg(u8 addr, u8 *buffer, u8 count) 
{
    u8 i, temp;
	temp = addr | WRITE_BURST;
    Clr_CC1101_CSN
    SpiTxRxByte(temp);
    for (i = 0; i < count; i++)
        SpiTxRxByte(buffer[i]);

    Set_CC1101_CSN
}
//功能描述：SPI写命令
void SpiStrobe(u8 strobe) 
{
    Clr_CC1101_CSN
    SpiTxRxByte(strobe);		                                     //写入命令
    Set_CC1101_CSN
}
//功能描述：SPI读寄存器
u8 SpiReadReg(u8 addr) 
{
	u8 temp, value;
    temp = addr|READ_SINGLE;                                         //读寄存器命令
	Clr_CC1101_CSN
	SpiTxRxByte(temp);
	value = SpiTxRxByte(0);
	Set_CC1101_CSN
	return value;
}
//功能描述：SPI连续写配置寄存器
void SpiReadBurstReg(u8 addr, u8 *buffer, u8 count) 
{
    u8 i,temp;
	temp = addr | READ_BURST;		                                 //写入要读的配置寄存器地址和读命令
    Clr_CC1101_CSN
	SpiTxRxByte(temp);   
    for (i = 0; i < count; i++)
		buffer[i] = SpiTxRxByte(0);

    Set_CC1101_CSN
}
//功能描述：SPI读状态寄存器
u8 SpiReadStatus(u8 addr) 
{
    u8 value,temp;
	temp = addr | READ_BURST;		                                 //写入要读的状态寄存器的地址同时写入读命令
    Clr_CC1101_CSN
    SpiTxRxByte(temp);
	value = SpiTxRxByte(0);
	Set_CC1101_CSN
	return value;
}
//功能描述：复位CC1100
void RESET_CC1100(void) 
{
	Clr_CC1101_CSN 
    SpiTxRxByte(CCxxx0_SRES); 		                                 //写入复位命令
    Set_CC1101_CSN 
}
//功能描述：上电复位CC1100
void POWER_UP_RESET_CC1100(void) 
{
	Set_CC1101_CSN 
	delay_ms(1); 
	Clr_CC1101_CSN 
	delay_ms(1); 
	Set_CC1101_CSN 
	delay_ms(5); 
	RESET_CC1100();                                                  //复位CC1100
}
//功能描述：配置CC1100的寄存器
void CC1101_Init(void) 
{
	POWER_UP_RESET_CC1100();

	SpiWriteReg(CCxxx0_FSCTRL0,  rfSettings.FSCTRL2);                //自已加的
    // Write register settings
    SpiWriteReg(CCxxx0_FSCTRL1,  rfSettings.FSCTRL1);
    SpiWriteReg(CCxxx0_FSCTRL0,  rfSettings.FSCTRL0);
    SpiWriteReg(CCxxx0_FREQ2,    rfSettings.FREQ2);
    SpiWriteReg(CCxxx0_FREQ1,    rfSettings.FREQ1);
    SpiWriteReg(CCxxx0_FREQ0,    rfSettings.FREQ0);
    SpiWriteReg(CCxxx0_MDMCFG4,  rfSettings.MDMCFG4);
    SpiWriteReg(CCxxx0_MDMCFG3,  rfSettings.MDMCFG3);
    SpiWriteReg(CCxxx0_MDMCFG2,  rfSettings.MDMCFG2);
    SpiWriteReg(CCxxx0_MDMCFG1,  rfSettings.MDMCFG1);
    SpiWriteReg(CCxxx0_MDMCFG0,  rfSettings.MDMCFG0);
    SpiWriteReg(CCxxx0_CHANNR,   rfSettings.CHANNR);
    SpiWriteReg(CCxxx0_DEVIATN,  rfSettings.DEVIATN);
    SpiWriteReg(CCxxx0_FREND1,   rfSettings.FREND1);
    SpiWriteReg(CCxxx0_FREND0,   rfSettings.FREND0);
    SpiWriteReg(CCxxx0_MCSM0 ,   rfSettings.MCSM0 );
    SpiWriteReg(CCxxx0_FOCCFG,   rfSettings.FOCCFG);
    SpiWriteReg(CCxxx0_BSCFG,    rfSettings.BSCFG);
    SpiWriteReg(CCxxx0_AGCCTRL2, rfSettings.AGCCTRL2);
	SpiWriteReg(CCxxx0_AGCCTRL1, rfSettings.AGCCTRL1);
    SpiWriteReg(CCxxx0_AGCCTRL0, rfSettings.AGCCTRL0);
    SpiWriteReg(CCxxx0_FSCAL3,   rfSettings.FSCAL3);
	SpiWriteReg(CCxxx0_FSCAL2,   rfSettings.FSCAL2);
	SpiWriteReg(CCxxx0_FSCAL1,   rfSettings.FSCAL1);
    SpiWriteReg(CCxxx0_FSCAL0,   rfSettings.FSCAL0);
    SpiWriteReg(CCxxx0_FSTEST,   rfSettings.FSTEST);
    SpiWriteReg(CCxxx0_TEST2,    rfSettings.TEST2);
    SpiWriteReg(CCxxx0_TEST1,    rfSettings.TEST1);
    SpiWriteReg(CCxxx0_TEST0,    rfSettings.TEST0);
    SpiWriteReg(CCxxx0_IOCFG2,   rfSettings.IOCFG2);
    SpiWriteReg(CCxxx0_IOCFG0,   rfSettings.IOCFG0);    
    SpiWriteReg(CCxxx0_PKTCTRL1, rfSettings.PKTCTRL1);
    SpiWriteReg(CCxxx0_PKTCTRL0, rfSettings.PKTCTRL0);
    SpiWriteReg(CCxxx0_ADDR,     rfSettings.ADDR);
    SpiWriteReg(CCxxx0_PKTLEN,   rfSettings.PKTLEN);

	SpiWriteBurstReg(CCxxx0_PATABLE, PaTabel, 8);                    //发射功率设置
}
u8 ReceivePacket(u8 *rxBuffer, u8 *length) 
{
    u8 status[2];
    u8 packetLength;
	u8 i=(*length)*4;                                                // 具体多少要根据datarate和length来决定

    SpiStrobe(CCxxx0_SRX);		                                     //进入接收状态
	while (CC1101GDO0)
	{
		delay_us(4);
		--i;
		if(i<1)
		   return 0; 	    
	}	 
    if ((SpiReadStatus(CCxxx0_RXBYTES) & BYTES_IN_RXFIFO))           //如果接的字节数不为0
	{
        packetLength = SpiReadReg(CCxxx0_RXFIFO);                    //读出第一个字节，此字节为该帧数据长度
        if (packetLength <= *length) 		                         //如果所要的有效数据长度小于等于接收到的数据包的长度
		{
            SpiReadBurstReg(CCxxx0_RXFIFO, rxBuffer, packetLength);  //读出所有接收到的数据
            *length = packetLength;				                     //把接收数据长度的修改为当前数据的长度
        
            // Read the 2 appended status bytes (status[0] = RSSI, status[1] = LQI)
            SpiReadBurstReg(CCxxx0_RXFIFO, status, 2); 	             //读出CRC校验位
			SpiStrobe(CCxxx0_SFRX);		                             //清洗接收缓冲区
            return (status[1] & CRC_OK);			                 //如果校验成功返回接收成功
        }
		 else 
		{
            *length = packetLength;
            SpiStrobe(CCxxx0_SFRX);		                             //清洗接收缓冲区
            return 0;
        }
    } 
	else
 	return 0;
}
//功能描述：CC1100发送一组数据
//*****************************************************************************************
void SendPacket(u8 *txBuffer, u8 size) 
{
	SpiWriteReg(CCxxx0_TXFIFO, size);
    SpiWriteBurstReg(CCxxx0_TXFIFO, txBuffer, size);	            //写入要发送的数据

    SpiStrobe(CCxxx0_STX);		                                    //进入发送模式发送数据

    // Wait for GDO0 to be set -> sync transmitted
    while (!CC1101GDO0);
    // Wait for GDO0 to be cleared -> end of packet
    while (CC1101GDO0);
	SpiStrobe(CCxxx0_SFTX);
}
