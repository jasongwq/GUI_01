#include"DAC.h"
#include "stm32f10x.h"

void DAC1_Init(u16 digital)
{
	static DAC_InitTypeDef  DAC_InitStructure1;

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	/*DAC通道IO配置*/
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;				                     //IO端口的第4位
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;				                 //端口模式为模拟输入方式
  	GPIO_Init(GPIOA, &GPIO_InitStructure);


	DAC_InitStructure1.DAC_Trigger = DAC_Trigger_Software;						 //DAC触发方式为软件控制
  	DAC_InitStructure1.DAC_WaveGeneration = DAC_WaveGeneration_None;			 //不从DAC端口产生波形
  	DAC_InitStructure1.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits8_0;//8位DA波形生成模式
  	DAC_InitStructure1.DAC_OutputBuffer = DAC_OutputBuffer_Enable;				 //使能DAC输出缓冲器

	DAC_Init(DAC_Channel_1, &DAC_InitStructure1);						         //用上面参数初始化DAC通道1
	DAC_Cmd(DAC_Channel_1, ENABLE);								                 //使能DAC通道1
	DAC_SetChannel1Data(DAC_Align_12b_R, digital);				                 //设置DAC通道1为12位且数据右对齐模式
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);			                     //使能DAC通道1的软件触发方式，转换一次

}
void DAC2_Init(u16 digital)
{
	static DAC_InitTypeDef DAC_InitStructure2;

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	/*DAC通道IO配置*/			             //IO端口的第4位
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;				                  //端口模式为模拟输入方式
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_InitStructure2.DAC_Trigger = DAC_Trigger_Software;						  //DAC触发方式为软件控制
  	DAC_InitStructure2.DAC_WaveGeneration = DAC_WaveGeneration_None;			  //不从DAC端口产生波形
  	DAC_InitStructure2.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits8_0; //8位DA波形生成模式
  	DAC_InitStructure2.DAC_OutputBuffer = DAC_OutputBuffer_Enable;				  //使能DAC输出缓冲器

	DAC_Init(DAC_Channel_2, &DAC_InitStructure2);
	DAC_Cmd(DAC_Channel_2, ENABLE);								                  //使能DAC通道2
	DAC_SetChannel1Data(DAC_Align_12b_R, digital);				                  //设置DAC通道2为12位且数据右对齐模式
	DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);			                      //使能DAC通道1的软件触发方式，转换一次
}
void Set_DAC1(u16 digital)
{
	DAC_SetChannel1Data(DAC_Align_12b_R, digital);				             
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);			                   
}
void Set_DAC2(u16 digital)
{
    DAC_SetChannel2Data(DAC_Align_12b_R, digital);
	DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);
}

