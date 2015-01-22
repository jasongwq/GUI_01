#include"DAC.h"
#include "stm32f10x.h"

void DAC1_Init(u16 digital)
{
	static DAC_InitTypeDef  DAC_InitStructure1;

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	/*DACͨ��IO����*/
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;				                     //IO�˿ڵĵ�4λ
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;				                 //�˿�ģʽΪģ�����뷽ʽ
  	GPIO_Init(GPIOA, &GPIO_InitStructure);


	DAC_InitStructure1.DAC_Trigger = DAC_Trigger_Software;						 //DAC������ʽΪ�������
  	DAC_InitStructure1.DAC_WaveGeneration = DAC_WaveGeneration_None;			 //����DAC�˿ڲ�������
  	DAC_InitStructure1.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits8_0;//8λDA��������ģʽ
  	DAC_InitStructure1.DAC_OutputBuffer = DAC_OutputBuffer_Enable;				 //ʹ��DAC���������

	DAC_Init(DAC_Channel_1, &DAC_InitStructure1);						         //�����������ʼ��DACͨ��1
	DAC_Cmd(DAC_Channel_1, ENABLE);								                 //ʹ��DACͨ��1
	DAC_SetChannel1Data(DAC_Align_12b_R, digital);				                 //����DACͨ��1Ϊ12λ�������Ҷ���ģʽ
	DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);			                     //ʹ��DACͨ��1�����������ʽ��ת��һ��

}
void DAC2_Init(u16 digital)
{
	static DAC_InitTypeDef DAC_InitStructure2;

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	/*DACͨ��IO����*/			             //IO�˿ڵĵ�4λ
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;				                  //�˿�ģʽΪģ�����뷽ʽ
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	DAC_InitStructure2.DAC_Trigger = DAC_Trigger_Software;						  //DAC������ʽΪ�������
  	DAC_InitStructure2.DAC_WaveGeneration = DAC_WaveGeneration_None;			  //����DAC�˿ڲ�������
  	DAC_InitStructure2.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits8_0; //8λDA��������ģʽ
  	DAC_InitStructure2.DAC_OutputBuffer = DAC_OutputBuffer_Enable;				  //ʹ��DAC���������

	DAC_Init(DAC_Channel_2, &DAC_InitStructure2);
	DAC_Cmd(DAC_Channel_2, ENABLE);								                  //ʹ��DACͨ��2
	DAC_SetChannel1Data(DAC_Align_12b_R, digital);				                  //����DACͨ��2Ϊ12λ�������Ҷ���ģʽ
	DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);			                      //ʹ��DACͨ��1�����������ʽ��ת��һ��
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

