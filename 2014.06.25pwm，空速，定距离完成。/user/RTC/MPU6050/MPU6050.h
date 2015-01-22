/*
  �ö��׻����˲���ʱ��kֵԽ��Խ��ͼ��ٶȵ�ֱ��������ԽС��Խ����һ��kֵ��һ��Ƚ���ʵ
	�ö��׻����˲�֮�����Ҫ�ı�  #define Adj_d    0.17   ��ֵ��ʹ֮�������ǻ��ֺ�ĽǼ��ٶ�ֵ�Ͷ��׻����˲�
	���õĿ�����֮�����Ǳ仯����ͬ��ʹ֮׼ȷ
	
	��������𶯱Ƚϴ��ʱ�� Ӧ���ȵ�����ǵ�  Q_angle �� R_angle  ���������ܵ����˲�Ч�������ͺ�������
	Ȼ���ٵ��������ǵ� Q �� R ֵ(һ�㲻��ô��Ҫ�ģ������ǵ����ݻ�����Ĭ��׼ȷ),Ȼ���ٵ���  #define Adj_d    0.17
	ʹ֮��ƥ��
	
	    ��ȡһ���������һ��������303�ε��ٶ�
*/
#ifndef __MPU6050_H
#define __MPU6050_H 

#include "stm32f10x.h"
#include "delay.h"
#include "GPIO.h"
#include <stdio.h>
#include <math.h>


#define MPU6050_IIC_SCL_Init      PB2_OUT  									 //I2C  SCL
#define MPU6050_IIC_SDA_Init      PB1_OUT  									 //I2C  SDA
#define MPU6050_SDA_OUT();        PB1_OUT
#define MPU6050_SDA_IN();         PB1_In

#define MPU6050_Clr_IIC_SCL       Clr_B2
#define MPU6050_Set_IIC_SCL       Set_B2
#define MPU6050_Clr_IIC_SDA       Clr_B1
#define MPU6050_Set_IIC_SDA       Set_B1
#define MPU6050_READ_SDA          B1


// ����MPU6050�ڲ���ַ
//****************************************
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			  0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ:0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ:0x18(���Լ�,2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ٶȼ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ:0x01(���Լ�,2G,5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ:0x00(��������)
#define	WHO_AM_I			0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68,ֻ��)
#define	SlaveAddress	0xD0	//IICд��ʱ�ĵ�ַ�ֽ�����,+1Ϊ������

void MPU6050_IIC_Init(void);
void MPU6050_Init(void);
void Get_6050_Dat(u16 *x,u16 *y,u16 *z,u16 *Qx,u16 *Qy,u16 *Qz);

void Get_6050_Angle(float *X,float *Y,float *Z);
void Adjust_MPU6050_Location(void);
void Get_6050_Q(float *qx,float *qy,float *qz);
void Get_6050_Klm_ang(float *qx,float *qy,float *qz);
void Get_6050_Klm_Q(float *qx,float *qy,float *qz);
void Get_6050_Com(float *cx,float *cy,float *cz);
void Get_X(float *angx,float *cx,float *qy);         // ˮƽ��ʱ�� ���ٶȵ� X �������ǵ�  Y  ����  
void Get_Y(float *angy,float *cy,float *qx);         // ˮƽ��ʱ�� ���ٶȵ� Y �������ǵ�  X  ���� 
void Get_Z_x(float *angz,float *cz,float *qx);       // ��ֱ��ʱ�� ���ٶȵ� Z �������ǵ�  X  ����  
void Get_Z_y(float *angz,float *cz,float *qy);       // ��ֱ��ʱ�� ���ٶȵ� Z �������ǵ�  Y  ���� 


#endif
