/*
              SPI ģ�����ó�ʼ��


 */
#include "SPI.h"
#include "stm32f10x.h"

static SPI_InitTypeDef  SPI1_InitStructure,SPI2_InitStructure,SPI3_InitStructure;

//��������ӿ�SPI�ĳ�ʼ����SPI���ó���ģʽ							  
//������ѡ������ϵ�п����崦������SPI��NRF24L01���ж�д�������ȶ�SPI���г�ʼ��
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

	/* SPI1 configuration */                                            //��ʼ��SPI�ṹ��
	SPI1_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI����Ϊ����ȫ˫��
	SPI1_InitStructure.SPI_Mode = SPI_Mode_Master;		                //����SPIΪ��ģʽ
	SPI1_InitStructure.SPI_DataSize = SPI_DataSize_8b;		            //SPI���ͽ���8λ֡�ṹ
	SPI1_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                    //����ʱ���ڲ�����ʱ��ʱ��Ϊ�͵�ƽ
	SPI1_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                    //��һ��ʱ���ؿ�ʼ��������
	SPI1_InitStructure.SPI_NSS = SPI_NSS_Soft;		                    //NSS�ź��������ʹ��SSIλ������
	SPI1_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //SPI������Ԥ��ƵֵΪ8
	SPI1_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //���ݴ����MSBλ��ʼ
	SPI1_InitStructure.SPI_CRCPolynomial = 7;	                        //CRCֵ����Ķ���ʽ

	SPI_Init(SPI1, &SPI1_InitStructure);   //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPI2�Ĵ���
	
	/* Enable SPI1  */
	SPI_Cmd(SPI1, ENABLE);                                      //ʹ��SPI����
	
	SPI1_ReadWriteByte(0xff);                                            //��������		 
}  
void SPI1_SetSpeed(u16 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI1_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler; 
	SPI_Init(SPI1, &SPI1_InitStructure);
	SPI_Cmd(SPI1,ENABLE); 
}
u8 SPI1_ReadWriteByte(u8 TxData)                                        //SPI��д���ݺ���
{		
	u8 retry=0;				 	
	/* Loop while DR register in not emplty */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)      //���ͻ����־λΪ��
	{
		retry++;
		if(retry>200)return 0;
	}			  
	/* Send byte through the SPI1 peripheral */
	SPI_I2S_SendData(SPI1, TxData);                                    //ͨ������SPI1����һ������
	retry=0;
	/* Wait to receive a byte */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);   //���ջ����־λ��Ϊ��
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	/* Return the byte read from the SPI bus */
	return SPI_I2S_ReceiveData(SPI1);                                 //ͨ��SPI1���ؽ�������				    
}

void SPI2_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );             //PORTBʱ��ʹ�� 
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );             //SPI2ʱ��ʹ�� 	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                     //PB13/14/15����������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);                              //��ʼ��GPIOB

 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);            //PB13/14/15����

	SPI2_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI2_InitStructure.SPI_Mode = SPI_Mode_Master;		                //����SPI����ģʽ:����Ϊ��SPI
	SPI2_InitStructure.SPI_DataSize = SPI_DataSize_8b;		            //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI2_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                    //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI2_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                    //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI2_InitStructure.SPI_NSS = SPI_NSS_Soft;		                    //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI2_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ8
	SPI2_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI2_InitStructure.SPI_CRCPolynomial = 7;	                        //CRCֵ����Ķ���ʽ
	SPI_Init(SPI2, &SPI2_InitStructure);                                 //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����
	
	SPI2_ReadWriteByte(0xff);//��������		 
 

}   
//SPI �ٶ����ú���
//SpeedSet:
//SPI_BaudRatePrescaler_2   2��Ƶ   
//SPI_BaudRatePrescaler_8   8��Ƶ   
//SPI_BaudRatePrescaler_16  16��Ƶ  
//SPI_BaudRatePrescaler_256 256��Ƶ 
  
void SPI2_SetSpeed(u16 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler; 
	SPI_Init(SPI2, &SPI2_InitStructure);
	SPI_Cmd(SPI2,ENABLE); 
} 

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����					    
}
void SPI3_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;

	Disable_SWJ();

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );             //PORTBʱ��ʹ�� 
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI3,  ENABLE );             //SPI2ʱ��ʹ�� 	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                     //PB3/4/5����������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);                              //��ʼ��GPIOB

 	GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);            //PB13/14/15����

	SPI3_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI3_InitStructure.SPI_Mode = SPI_Mode_Master;		                //����SPI����ģʽ:����Ϊ��SPI
	SPI3_InitStructure.SPI_DataSize = SPI_DataSize_8b;		            //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI3_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                    //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI3_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                    //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI3_InitStructure.SPI_NSS = SPI_NSS_Soft;		                    //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI3_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;  //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ8
	SPI3_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI3_InitStructure.SPI_CRCPolynomial = 7;	                        //CRCֵ����Ķ���ʽ
	SPI_Init(SPI3, &SPI3_InitStructure);                                 //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	SPI_Cmd(SPI3, ENABLE); //ʹ��SPI����
	
	SPI3_ReadWriteByte(0xff);//��������		 
 

}   
//SPI �ٶ����ú���
//SpeedSet:
//SPI_BaudRatePrescaler_2   2��Ƶ   
//SPI_BaudRatePrescaler_8   8��Ƶ   
//SPI_BaudRatePrescaler_16  16��Ƶ  
//SPI_BaudRatePrescaler_256 256��Ƶ 
  
void SPI3_SetSpeed(u16 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI3_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler; 
	SPI_Init(SPI3, &SPI3_InitStructure);
	SPI_Cmd(SPI3,ENABLE); 
} 

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI3_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI3, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI3); //����ͨ��SPIx������յ�����					    
}

void Disable_SWJ(void)
{																  
	//GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_AFIO, ENABLE );
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);		 	  // PB3 PB4 		 ����֮��ſ�����
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		  // PA13 PA14 PA15  ����֮��ſ�����

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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU  ;     //��������
	GPIO_Init(SPI0_GPIO_MISO, &GPIO_InitStructure);
	
	SPI0_ReadWriteByte(0xff);                                            //��������		 
} 
/*дһ�� byte ��оƬ��������һ�� byte*/ 
u8 SPI0_ReadWriteByte(u8 TxData)                                        //SPI��д���ݺ���
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
