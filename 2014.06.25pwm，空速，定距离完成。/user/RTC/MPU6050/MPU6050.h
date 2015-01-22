/*
  用二阶互补滤波的时候k值越大越快和加速度的直线贴近，越小则越慢，一般k值大一点比较真实
	用二阶互补滤波之后必须要改变  #define Adj_d    0.17   的值，使之让陀螺仪积分后的角加速度值和二阶互补滤波
	中用的卡尔曼之后的倾角变化率相同，使之准确
	
	当外外界震动比较大的时候 应当先调节倾角的  Q_angle 和 R_angle  让他尽可能的有滤波效果并且滞后不厉害，
	然后再调节陀螺仪的 Q 和 R 值(一般不怎么需要改，陀螺仪的数据基本都默认准确),然后再调节  #define Adj_d    0.17
	使之相匹配
	
	    单取一个轴的数据一秒钟内有303次的速度
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


// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			  0x1A	//低通滤波频率，典型值:0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值:0x18(不自检,2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速度计自检、测量范围及高通滤波频率，典型值:0x01(不自检,2G,5Hz)
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
#define	PWR_MGMT_1		0x6B	//电源管理，典型值:0x00(正常启动)
#define	WHO_AM_I			0x75	//IIC地址寄存器(默认数值0x68,只读)
#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据,+1为读数据

void MPU6050_IIC_Init(void);
void MPU6050_Init(void);
void Get_6050_Dat(u16 *x,u16 *y,u16 *z,u16 *Qx,u16 *Qy,u16 *Qz);

void Get_6050_Angle(float *X,float *Y,float *Z);
void Adjust_MPU6050_Location(void);
void Get_6050_Q(float *qx,float *qy,float *qz);
void Get_6050_Klm_ang(float *qx,float *qy,float *qz);
void Get_6050_Klm_Q(float *qx,float *qy,float *qz);
void Get_6050_Com(float *cx,float *cy,float *cz);
void Get_X(float *angx,float *cx,float *qy);         // 水平的时候 加速度的 X 和陀螺仪的  Y  相结合  
void Get_Y(float *angy,float *cy,float *qx);         // 水平的时候 加速度的 Y 和陀螺仪的  X  相结合 
void Get_Z_x(float *angz,float *cz,float *qx);       // 竖直的时候 加速度的 Z 和陀螺仪的  X  相结合  
void Get_Z_y(float *angz,float *cz,float *qy);       // 竖直的时候 加速度的 Z 和陀螺仪的  Y  相结合 


#endif
