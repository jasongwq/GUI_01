#include "stm32f10x.h"
#include"delay.h"
#include "ADC.h"

#define TIME ADC_SampleTime=ADC_Time(SampleTime);

void ADC_init(u16 x)
{
     GPIO_InitTypeDef GPIO_InitStructure;

     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

     if(x==0){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOA, &GPIO_InitStructure);} //端口模式为模拟输入方式
	 else if(x==1){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOA, &GPIO_InitStructure);}
	 else if(x==2){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOA, &GPIO_InitStructure);}
	 else if(x==3){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOA, &GPIO_InitStructure);}
	 else if(x==4){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOA, &GPIO_InitStructure);}
	 else if(x==5){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOA, &GPIO_InitStructure);}
	 else if(x==6){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOA, &GPIO_InitStructure);}
	 else if(x==7){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOA, &GPIO_InitStructure);}
	 else if(x==8){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOB, &GPIO_InitStructure);}
	 else if(x==9){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOB, &GPIO_InitStructure);}
	 else if(x==10){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOC, &GPIO_InitStructure);}
	 else if(x==11){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOC, &GPIO_InitStructure);}
	 else if(x==12){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOC, &GPIO_InitStructure);}
	 else if(x==13){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOC, &GPIO_InitStructure);}
	 else if(x==14){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOC, &GPIO_InitStructure);}
	 else if(x==15){GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;GPIO_Init(GPIOC, &GPIO_InitStructure);}
	 else {}
}


u16 ADC1_Configuration(u16 ADC_Channel ,u8 SampleTime)
{
	 u8 ADC_SampleTime;
     static u8 i=5,insign=0;

	 if(i==5 || insign!=ADC_Channel){Choose_ADC(1);i=0;}				 //对于 后面那个条件必须加 不加会出现 偶尔会死在fx(1);里的状况
     	 
	 if(insign==ADC_Channel){return ADC_GetConversionValue(ADC1);}
     else if(ADC_Channel==0) {TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime);fx(1);}	//  PA0
	 else if(ADC_Channel==1) {TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime);fx(1);}	//  PA1
	 else if(ADC_Channel==2) {TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime);fx(1);}	//  PA2
	 else if(ADC_Channel==3) {TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime);fx(1);}	//  PA3
	 else if(ADC_Channel==4) {TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime);fx(1);}	//  PA4
	 else if(ADC_Channel==5) {TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime);fx(1);}	//  PA5
	 else if(ADC_Channel==6) {TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 1, ADC_SampleTime);fx(1);}	//  PA6
	 else if(ADC_Channel==7) {TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime);fx(1);}	//  PA7
	 else if(ADC_Channel==8) {TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime);fx(1);}	//  PB0
	 else if(ADC_Channel==9) {TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime);fx(1);}	//  PB1
	 else if(ADC_Channel==10){TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_10,1, ADC_SampleTime);fx(1);}	//  PC0
	 else if(ADC_Channel==11){TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_11,1, ADC_SampleTime);fx(1);}	//	PC1
	 else if(ADC_Channel==12){TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_12,1, ADC_SampleTime);fx(1);}	//	PC2
	 else if(ADC_Channel==13){TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_13,1, ADC_SampleTime);fx(1);}	//	PC3
	 else if(ADC_Channel==14){TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_14,1, ADC_SampleTime);fx(1);}	//	PC4
	 else if(ADC_Channel==15){TIME ADC_RegularChannelConfig(ADC1, ADC_Channel_15,1, ADC_SampleTime);fx(1);}	//	PC5
	 	
	 if(insign!=ADC_Channel){insign=ADC_Channel;delay_us(2);}			//对于这个延时必须加，不加延时会出现得到的值不对
	 return ADC_GetConversionValue(ADC1);
}
u16 ADC2_Configuration(u16 ADC_Channel,u8 SampleTime)
{
	 u8 ADC_SampleTime;
     static u8 i=5,insign=0;

	 if(i==5|| insign!=ADC_Channel){Choose_ADC(2);i=0;}
	 
	 if(insign==ADC_Channel){return ADC_GetConversionValue(ADC2);}
     else if(ADC_Channel==0) {TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_0, 1, ADC_SampleTime);fx(2);}	//  PA0
	 else if(ADC_Channel==1) {TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_1, 1, ADC_SampleTime);fx(2);}	//  PA1
	 else if(ADC_Channel==2) {TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 1, ADC_SampleTime);fx(2);}	//  PA2
	 else if(ADC_Channel==3) {TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_3, 1, ADC_SampleTime);fx(2);}	//  PA3
	 else if(ADC_Channel==4) {TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_4, 1, ADC_SampleTime);fx(2);}	//  PA4
	 else if(ADC_Channel==5) {TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_5, 1, ADC_SampleTime);fx(2);}	//  PA5
	 else if(ADC_Channel==6) {TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_6, 1, ADC_SampleTime);fx(2);}	//  PA6
	 else if(ADC_Channel==7) {TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_7, 1, ADC_SampleTime);fx(2);}	//  PA7
	 else if(ADC_Channel==8) {TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_8, 1, ADC_SampleTime);fx(2);}	//  PB0
	 else if(ADC_Channel==9) {TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_9, 1, ADC_SampleTime);fx(2);}	//  PB1
	 else if(ADC_Channel==10){TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_10,1, ADC_SampleTime);fx(2);}	//  PC0
	 else if(ADC_Channel==11){TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_11,1, ADC_SampleTime);fx(2);}	//	PC1
	 else if(ADC_Channel==12){TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_12,1, ADC_SampleTime);fx(2);}	//	PC2
	 else if(ADC_Channel==13){TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_13,1, ADC_SampleTime);fx(2);}	//	PC3
	 else if(ADC_Channel==14){TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_14,1, ADC_SampleTime);fx(2);}	//	PC4
	 else if(ADC_Channel==15){TIME ADC_RegularChannelConfig(ADC2, ADC_Channel_15,1, ADC_SampleTime);fx(2);}	//	PC5
	 	
	 if(insign!=ADC_Channel){insign=ADC_Channel;delay_us(2);}
	 return ADC_GetConversionValue(ADC2);
}
u16 ADC3_Configuration(u16 ADC_Channel,u8 SampleTime)
{
	 u8 ADC_SampleTime;
     static u8 i=5,insign=0;

	 if(i==5 || insign!=ADC_Channel){Choose_ADC(3);i=0;}
 	 
	 if(insign==ADC_Channel){return ADC_GetConversionValue(ADC3);}
     else if(ADC_Channel==0) {TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_0, 1, ADC_SampleTime);fx(3);}	//  PA0
	 else if(ADC_Channel==1) {TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_1, 1, ADC_SampleTime);fx(3);}	//  PA1
	 else if(ADC_Channel==2) {TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_2, 1, ADC_SampleTime);fx(3);}	//  PA2
	 else if(ADC_Channel==3) {TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_3, 1, ADC_SampleTime);fx(3);}	//  PA3
	 //else if(ADC_Channel==4) {TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_4, 1, ADC_SampleTime);fx(3);}	//  PA4
	 //else if(ADC_Channel==5) {TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_5, 1, ADC_SampleTime);fx(3);}	//  PA5
	 //else if(ADC_Channel==6) {TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_6, 1, ADC_SampleTime);fx(3);}	//  PA6
	 //else if(ADC_Channel==7) {TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_7, 1, ADC_SampleTime);fx(3);}	//  PA7
	 //else if(ADC_Channel==8) {TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_8, 1, ADC_SampleTime);fx(3);}	//  PB0
	 //else if(ADC_Channel==9) {TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_9, 1, ADC_SampleTime);fx(3);}	//  PB1
	 else if(ADC_Channel==10){TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_10,1, ADC_SampleTime);fx(3);}	//  PC0
	 else if(ADC_Channel==11){TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_11,1, ADC_SampleTime);fx(3);}	//	PC1
	 else if(ADC_Channel==12){TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_12,1, ADC_SampleTime);fx(3);}	//	PC2
	 else if(ADC_Channel==13){TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_13,1, ADC_SampleTime);fx(3);}	//	PC3
	 //else if(ADC_Channel==14){TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_14,1, ADC_SampleTime);fx(3);}	//	PC4
	 //else if(ADC_Channel==15){TIME ADC_RegularChannelConfig(ADC3, ADC_Channel_15,1, ADC_SampleTime);fx(3);}	//	PC5
		
	 if(insign!=ADC_Channel){insign=ADC_Channel;delay_us(2);}
	 return ADC_GetConversionValue(ADC3);
}
void Choose_ADC(u8 ADC)
{
     ADC_InitTypeDef ADC_InitStructure;
     if(ADC==1)     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);		 //使能由APB2时钟控制的外设中的ADC1
     else if(ADC==2)RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
     else if(ADC==3)RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);	 
	
     ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
     ADC_InitStructure.ADC_ScanConvMode = ENABLE;
     ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
     ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
     ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
     ADC_InitStructure.ADC_NbrOfChannel = 1;
	 
     if(ADC==1)ADC_Init(ADC1, &ADC_InitStructure);
	 else if(ADC==2)ADC_Init(ADC2, &ADC_InitStructure);
	 else if(ADC==3)ADC_Init(ADC3, &ADC_InitStructure);
}
void fx(u8 ADC)
{
    if(ADC==1)
	{
        ADC_Cmd(ADC1, ENABLE);                                 //使能ADC1
        ADC_ResetCalibration(ADC1);							 //重置ADC1校准寄存器
        while(ADC_GetResetCalibrationStatus(ADC1));			 //得到重置校准寄存器状态
        ADC_StartCalibration(ADC1);							 //开始校准ADC1
        while(ADC_GetCalibrationStatus(ADC1));				 //得到校准寄存器状态
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);				 //使能ADC1由软件控制开始转换
	}
	else if(ADC==2)
	{
        ADC_Cmd(ADC2, ENABLE);                                 //使能ADC1
        ADC_ResetCalibration(ADC2);							 //重置ADC1校准寄存器
        while(ADC_GetResetCalibrationStatus(ADC2));			 //得到重置校准寄存器状态
        ADC_StartCalibration(ADC2);							 //开始校准ADC1
        while(ADC_GetCalibrationStatus(ADC2));				 //得到校准寄存器状态
        ADC_SoftwareStartConvCmd(ADC2, ENABLE);				 //使能ADC1由软件控制开始转换
	}
	else if(ADC==3)
	{
        ADC_Cmd(ADC3, ENABLE);                                 //使能ADC1
        ADC_ResetCalibration(ADC3);							 //重置ADC1校准寄存器
        while(ADC_GetResetCalibrationStatus(ADC3));			 //得到重置校准寄存器状态
        ADC_StartCalibration(ADC3);							 //开始校准ADC1
        while(ADC_GetCalibrationStatus(ADC3));				 //得到校准寄存器状态
        ADC_SoftwareStartConvCmd(ADC3, ENABLE);				 //使能ADC1由软件控制开始转换
	}
}
u8 ADC_Time(u8 ADC_SampleTime)
{
    if(ADC_SampleTime==1)       {return ADC_SampleTime_1Cycles5 ;}
	else if(ADC_SampleTime==7)	{return ADC_SampleTime_7Cycles5 ;}
	else if(ADC_SampleTime==13)	{return ADC_SampleTime_13Cycles5 ;}
	else if(ADC_SampleTime==28)	{return ADC_SampleTime_28Cycles5 ;}
	else if(ADC_SampleTime==41)	{return ADC_SampleTime_41Cycles5 ;}
	else if(ADC_SampleTime==55)	{return ADC_SampleTime_55Cycles5 ;}
	else if(ADC_SampleTime==71)	{return ADC_SampleTime_71Cycles5 ;}
	else if(ADC_SampleTime==239){return ADC_SampleTime_239Cycles5 ;}
	else {return 0 ;}				
}
