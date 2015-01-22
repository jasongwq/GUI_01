#include "MPU6050.h"


static int MPU_err_X,MPU_err_Y,MPU_err_Z;
static int MPU_err_QX=-62,MPU_err_QY=11,MPU_err_QZ=15;

void MPU6050_IIC_Init(void)
{	
    MPU6050_IIC_SCL_Init
	  MPU6050_IIC_SDA_Init	
}
void MPU6050_IIC_Start(void)
{
	MPU6050_SDA_OUT();    
	MPU6050_Set_IIC_SDA	  	  
	MPU6050_Set_IIC_SCL
	delay_us(4);
 	MPU6050_Clr_IIC_SDA
	delay_us(4);
	MPU6050_Clr_IIC_SCL
}	  
void MPU6050_IIC_Stop(void)
{
	MPU6050_SDA_OUT();
	MPU6050_Clr_IIC_SCL
	MPU6050_Clr_IIC_SDA
 	delay_us(4);
	MPU6050_Set_IIC_SCL 
	MPU6050_Set_IIC_SDA
	delay_us(4);		 	
}
u8 MPU6050_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	MPU6050_SDA_IN();      
	MPU6050_Set_IIC_SDA
	delay_us(1);	   
	MPU6050_Set_IIC_SCL
	delay_us(1);	 
	while(MPU6050_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			MPU6050_IIC_Stop();
			return 1;
		}
	}
	MPU6050_Clr_IIC_SCL	   
	return 0;  
} 
void MPU6050_IIC_Ack(void)
{
	MPU6050_Clr_IIC_SCL
	MPU6050_SDA_OUT();
	MPU6050_Clr_IIC_SDA
	delay_us(2);
	MPU6050_Set_IIC_SCL
	delay_us(2);
	MPU6050_Clr_IIC_SCL
}    
void MPU6050_IIC_NAck(void)
{
	MPU6050_Clr_IIC_SCL
	MPU6050_SDA_OUT();
	MPU6050_Set_IIC_SDA
	delay_us(2);
	MPU6050_Set_IIC_SCL
	delay_us(2);
	MPU6050_Clr_IIC_SCL
}					 				       
void MPU6050_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	MPU6050_SDA_OUT(); 	    
    MPU6050_Clr_IIC_SCL
    for(t=0;t<8;t++)
    {    
	    if((txd&0x80)>>7){MPU6050_Set_IIC_SDA}
		else {MPU6050_Clr_IIC_SDA}      
        //IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   
		MPU6050_Set_IIC_SCL
		delay_us(2); 
		MPU6050_Clr_IIC_SCL	
		delay_us(2);
    }	 
} 	    
u8 MPU6050_IIC_Read_Byte(u8 ack)
{
	u8 i,receive=0;
	MPU6050_SDA_IN();//
    for(i=0;i<8;i++ )
	{
        MPU6050_Clr_IIC_SCL 
        delay_us(2);
		MPU6050_Set_IIC_SCL
        receive<<=1;
        if(MPU6050_READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        MPU6050_IIC_NAck();//
    else
        MPU6050_IIC_Ack(); //  
    return receive;
}



void MPU6050_WriteReg(u8 REG_Address,u8 REG_data) 
{  
   MPU6050_IIC_Start();   
   MPU6050_IIC_Send_Byte(SlaveAddress);	//
   MPU6050_IIC_Wait_Ack();        
   MPU6050_IIC_Send_Byte(REG_Address);    // 
   MPU6050_IIC_Wait_Ack();            
   MPU6050_IIC_Send_Byte(REG_data);    //  
   MPU6050_IIC_Wait_Ack();
   MPU6050_IIC_Stop();                  //
}
u8 MPU6050_ReadReg(u8 Regs_Addr) 
{
   u8 ret;
   
   MPU6050_IIC_Start();  
   MPU6050_IIC_Send_Byte(SlaveAddress); //   
   MPU6050_IIC_Wait_Ack();//  
   MPU6050_IIC_Send_Byte(Regs_Addr);    //   
   MPU6050_IIC_Wait_Ack();
   MPU6050_IIC_Start();     
   MPU6050_IIC_Send_Byte(SlaveAddress+1);  // 
   MPU6050_IIC_Wait_Ack();       //         
   ret=(u8)MPU6050_IIC_Read_Byte(0);//      
   MPU6050_IIC_Stop();                  //  
   
   return ret;

} 
void MPU6050_Init(void)
{
	MPU6050_IIC_Init();
	MPU6050_WriteReg(PWR_MGMT_1, 0x00);	//
	MPU6050_WriteReg(SMPLRT_DIV, 0x07);
	MPU6050_WriteReg(CONFIG, 0x06);
	MPU6050_WriteReg(GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(ACCEL_CONFIG, 0x01);
}
void Get_6050_Dat(u16 *x,u16 *y,u16 *z,u16 *Qx,u16 *Qy,u16 *Qz)
{
	*x=(MPU6050_ReadReg(ACCEL_XOUT_H)<<8) | MPU6050_ReadReg(ACCEL_XOUT_H+1);
	*y=(MPU6050_ReadReg(ACCEL_YOUT_H)<<8) | MPU6050_ReadReg(ACCEL_YOUT_H+1);
	*z=(MPU6050_ReadReg(ACCEL_ZOUT_H)<<8) | MPU6050_ReadReg(ACCEL_ZOUT_H+1);
	*Qx=(MPU6050_ReadReg(GYRO_XOUT_H)<<8) | MPU6050_ReadReg(GYRO_XOUT_H+1);
	*Qy=(MPU6050_ReadReg(GYRO_YOUT_H)<<8) | MPU6050_ReadReg(GYRO_YOUT_H+1);
	*Qz=(MPU6050_ReadReg(GYRO_ZOUT_H)<<8) | MPU6050_ReadReg(GYRO_ZOUT_H+1);
}

// 获得角度数据
void Get_6050_Angle(float *X,float *Y,float *Z)
{
		u16 x,y,z;
	  int ang_x,ang_y,ang_z;
	
		x=(MPU6050_ReadReg(ACCEL_XOUT_H)<<8) | MPU6050_ReadReg(ACCEL_XOUT_H+1);
		y=(MPU6050_ReadReg(ACCEL_YOUT_H)<<8) | MPU6050_ReadReg(ACCEL_YOUT_H+1);
		z=(MPU6050_ReadReg(ACCEL_ZOUT_H)<<8) | MPU6050_ReadReg(ACCEL_ZOUT_H+1);
	
	  ang_x=(int)x-MPU_err_X;
	  ang_y=(int)y-MPU_err_Y;
	  ang_z=(int)z-MPU_err_Z;
	
		if(x>16384){ ang_x=ang_x-65535; }else { }
		if(y>16384){ ang_y=ang_y-65535; }else { }
		if(z>16384){ ang_z=ang_z-65535; }else { }
		
    *X=(float)ang_x*90/16384;
    *Y=(float)ang_y*90/16384;
    *Z=(float)ang_z*90/16384;
}
/*  矫正初始错误 */
#define MPU_Max_Tim 50
void Adjust_MPU6050_Location(void)
{
	 u8 i;
	 u16 x,y,z;
	 for(i=0;i<MPU_Max_Tim;i++)
	 {
		  delay_ms(50);
		  x=(MPU6050_ReadReg(GYRO_XOUT_H)<<8) | MPU6050_ReadReg(GYRO_XOUT_H+1);
	    y=(MPU6050_ReadReg(GYRO_YOUT_H)<<8) | MPU6050_ReadReg(GYRO_YOUT_H+1);
	    z=(MPU6050_ReadReg(GYRO_ZOUT_H)<<8) | MPU6050_ReadReg(GYRO_ZOUT_H+1);
		  if(x>30000){MPU_err_QX-=65535-x;}else {MPU_err_QX+=x;}
			if(y>30000){MPU_err_QY-=65535-y;}else {MPU_err_QY+=y;}
			if(z>30000){MPU_err_QZ-=65535-z;}else {MPU_err_QZ+=z;}
   }
	 MPU_err_QX/=MPU_Max_Tim;
	 MPU_err_QY/=MPU_Max_Tim;
	 MPU_err_QZ/=MPU_Max_Tim;
	 printf("L3G_err : %d %d %d \r\n",MPU_err_QX,MPU_err_QY,MPU_err_QZ);
}
#define Adj_d    0.06
#define dt       0.005 			// 基本不变
/* 获得陀螺仪积分后的角加速度 */
void Get_6050_q(float *qx,float *qy,float *qz)
{
	u16 Qx,Qy,Qz;
	
	Qx=(MPU6050_ReadReg(GYRO_XOUT_H)<<8) | MPU6050_ReadReg(GYRO_XOUT_H+1);
	Qy=(MPU6050_ReadReg(GYRO_YOUT_H)<<8) | MPU6050_ReadReg(GYRO_YOUT_H+1);
	Qz=(MPU6050_ReadReg(GYRO_ZOUT_H)<<8) | MPU6050_ReadReg(GYRO_ZOUT_H+1);
	Qx-=MPU_err_QX;Qy-=MPU_err_QY;Qz-=MPU_err_QZ;// 矫正静态误差
	if(Qx>30000){*qx=(Adj_d)*(float)(Qx-65535);}else *qx=(Adj_d)*(float)Qx;
  if(Qy>30000){*qy=(Adj_d)*(float)(Qy-65535);}else *qy=(Adj_d)*(float)Qy;
  if(Qz>30000){*qz=(Adj_d)*(float)(Qz-65535);}else *qz=(Adj_d)*(float)Qz;
}
/* 获得陀螺仪积分后的角度 */
void Get_6050_Q(float *qx,float *qy,float *qz)
{  
	float ang_qx,ang_qy,ang_qz;	
	Get_6050_q(&ang_qx,&ang_qy,&ang_qz); //printf(" %d %d %d \r\n",ang_qx,ang_qy,ang_qz);
	ang_qx*=-1;
	*qx+=ang_qx*dt;		   // 陀螺仪积分后的角度
	*qy+=ang_qy*dt;		   // 陀螺仪积分后的角度
  *qz+=ang_qz*dt;
}
#define Q_angle  0.005      // 角度数据置信度	   太小容易滞后，太大噪声多(滤波效果不好)
#define R_angle  0.1       // 方差噪声		   太小收敛不起来，太大容易滞后
#define Q_y      0.005     // 尽量和上面的数据一样
#define R_y      0.1
void Get_6050_Klm_ang(float *qx,float *qy,float *qz)
{
	  float x,y,z;
	  static float K;
	  /*  一次加速度滤波 X */
		static float Klm_angle_X;
		static float P_0 = 0.5,P_1 = 0.5;
		/*  一次加速度滤波 Y */
		static float Klm_angle_Y;
		static float P_2 = 0.5,P_3 = 0.5;
	/*  一次加速度滤波 Z */
		static float Klm_angle_Z;
		static float P_4 = 0.5,P_5 = 0.5;
	
	  Get_6050_Angle(&x,&y,&z);
	
	  // 加速度 X
		P_1=sqrt(P_0*P_0+Q_angle*Q_angle);
		K = P_1 / (P_1 + R_angle);
		Klm_angle_X += K * (x - Klm_angle_X);
		P_0=(1.0-K) * P_1;
		// 加速度 Y
		P_3=sqrt(P_2*P_2+Q_angle*Q_angle);
		K = P_3 / (P_3 + R_angle);
		Klm_angle_Y += K * (y - Klm_angle_Y);
		P_2=(1.0-K) * P_3;
		// 加速度 Z
		P_5=sqrt(P_4*P_4+Q_angle*Q_angle);
		K = P_5 / (P_5 + R_angle);
		Klm_angle_Z += K * (z - Klm_angle_Z);
		P_4=(1.0-K) * P_5;
		
		*qx=Klm_angle_X;
		*qy=Klm_angle_Y;
    *qz=Klm_angle_Z;		
}
void Get_6050_Klm_q(float *qx,float *qy,float *qz)
{  
	  float x,y,z;
	  static float K;
    /*  一次陀螺仪滤波 Y */
		static float Klm_Y;
		static float P_4 = 0.5,P_5 = 0.5;
		/*  一次陀螺仪滤波 X */
		static float Klm_X;
		static float P_6 = 0.5,P_7 = 0.5;
	/*  一次陀螺仪滤波 Z */
		static float Klm_Z;
		static float P_8 = 0.5,P_9 = 0.5; 
	
	  Get_6050_q(qx,qy,qz);
	  x=*qx;y=*qy;z=*qz;
	  // 陀螺仪 Y
		P_5=sqrt(P_4*P_4+Q_y*Q_y);
		K = P_5 / (P_5 + R_y);
		Klm_Y += K * (y - Klm_Y);
		P_4=(1.0-K) * P_5;
		// 陀螺仪 X
		P_7=sqrt(P_6*P_6+Q_y*Q_y);
		K = P_7 / (P_7 + R_y);
		Klm_X += K * (x - Klm_X);
		P_6=(1.0-K) * P_7;
		// 陀螺仪 Z
		P_9=sqrt(P_8*P_8+Q_y*Q_y);
		K = P_9 / (P_9 + R_y);
		Klm_Z += K * (z - Klm_Z);
		P_8=(1.0-K) * P_9;
		
		*qx=Klm_X;
		*qy=Klm_Y;
		*qz=Klm_Z; // */
}
/* 卡尔曼之后陀螺仪的角度 有积分误差 */
void Get_6050_Klm_Q(float *qx,float *qy,float *qz)
{
	float ang_qx,ang_qy,ang_qz;	
	Get_6050_Klm_q(&ang_qx,&ang_qy,&ang_qz); //printf(" %d %d %d \r\n",ang_qx,ang_qy,ang_qz);
	ang_qx*=-1;
	*qx+=ang_qx*dt;		   // 陀螺仪积分后的角度
	*qy+=ang_qy*dt;		   // 陀螺仪积分后的角度
  *qz+=ang_qz*dt;
}
void Get_6050_Com(float *cx,float *cy,float *cz)
{
	  float x,y,z;
	  float qx,qy,qz;
	  /*  二阶互补滤波  01 */
		static float K,x1,x2,y1,y2;
		static float Com2_angle_X;
		/*  二阶互补滤波  23 */
		static float Com2_angle_Y;
	
	  Get_6050_Klm_ang(&x,&y,&z);
	  Get_6050_Klm_q(&qx,&qy,&qz);
	  qx*=-1;
	  // 二阶互补算法	 X
    K = 0.8;
    x1 = (x - Com2_angle_X) * K * K;
    y1 = y1 + x1 * dt;
    x2 = y1 + 2 * K *(x - Com2_angle_X) + qy;
    Com2_angle_X = Com2_angle_X + x2 * dt;
		// 二阶互补算法 Y
		x1 = (y - Com2_angle_Y) * K * K;
    y2 = y2 + x1 * dt;
    x2 = y2 + 2 * K *(y - Com2_angle_Y) + qx;
    Com2_angle_Y = Com2_angle_Y + x2 * dt;
		
		*cx=Com2_angle_X;
		*cy=Com2_angle_Y;
}

/****************             单轴的滤波后数据                  ******************/

/* 水平的时候 加速度的 X 和陀螺仪的  Y  相结合  */
void Get_X(float *angx,float *cx,float *qy)
{
		u16 ax,Qy;
		int ax0;
		float ax1,Qy1;

		float K;
		/*  一次加速度滤波 X */
		static float Klm_angle_X;
		static float P_0 = 0.5,P_1 = 0.5;
		/*  一次陀螺仪滤波 Y */
		static float Klm_Y;
		static float P_4 = 0.5,P_5 = 0.5;
		/*  二阶互补滤波  01 */
		static float x1,x2,y1;
		static float Com2_angle_X;

		ax=(MPU6050_ReadReg(ACCEL_XOUT_H)<<8) | MPU6050_ReadReg(ACCEL_XOUT_H+1);
		Qy=(MPU6050_ReadReg(GYRO_YOUT_H)<<8) | MPU6050_ReadReg(GYRO_YOUT_H+1);

		ax0=(int)ax-MPU_err_X;
		if(ax0>16384){ ax0=ax0-65535; }else {}	
		ax1=(float)ax0*90/16384;

		Qy-=MPU_err_QY;// 矫正静态误差
		if(Qy>30000){Qy1=(Adj_d)*(float)(Qy-65535);}else Qy1=(Adj_d)*(float)Qy;

		// 加速度 X
		P_1=sqrt(P_0*P_0+Q_angle*Q_angle);
		K = P_1 / (P_1 + R_angle);
		Klm_angle_X += K * (ax1 - Klm_angle_X);
		P_0=(1.0-K) * P_1;
		*angx=Klm_angle_X;
		// 陀螺仪 Y
		P_5=sqrt(P_4*P_4+Q_y*Q_y);
		K = P_5 / (P_5 + R_y);
		Klm_Y += K * (Qy1 - Klm_Y);
		P_4=(1.0-K) * P_5;
		*qy=Klm_Y;
		//Klm_angleG_Y+=Klm_Y*dt;
		// 二阶互补滤波融合
		K = 0.8;
		x1 = (Klm_angle_X - Com2_angle_X) * K * K;
		y1 = y1 + x1 * dt;
		x2 = y1 + 2 * K *(Klm_angle_X - Com2_angle_X) + Klm_Y;
		Com2_angle_X = Com2_angle_X + x2 * dt;
		*cx=Com2_angle_X;
}
/* 水平的时候 加速度的 Y 和陀螺仪的  X  相结合  */
void Get_Y(float *angy,float *cy,float *qx)
{
		u16 ay,Qx;
		int ay0;
		float ay1,Qx1;

		float K;
		/*  一次加速度滤波 X */
		static float Klm_angle_Y;
		static float P_0 = 0.5,P_1 = 0.5;
		/*  一次陀螺仪滤波 Y */
		static float Klm_X;
		static float P_4 = 0.5,P_5 = 0.5;
		/*  二阶互补滤波  01 */
		static float x1,x2,y1;
		static float Com2_angle_Y;

		ay=(MPU6050_ReadReg(ACCEL_YOUT_H)<<8) | MPU6050_ReadReg(ACCEL_YOUT_H+1);
		Qx=(MPU6050_ReadReg(GYRO_XOUT_H)<<8) | MPU6050_ReadReg(GYRO_XOUT_H+1);

		ay0=(int)ay-MPU_err_Y;
		if(ay0>16384){ ay0=ay0-65535; }else {}	
		ay1=(float)ay0*90/16384;

		Qx-=MPU_err_QY;// 矫正静态误差
		if(Qx>30000){Qx1=(Adj_d)*(float)(Qx-65535);}else Qx1=(Adj_d)*(float)Qx;
		Qx1*=-1;
		// 加速度 X
		P_1=sqrt(P_0*P_0+Q_angle*Q_angle);
		K = P_1 / (P_1 + R_angle);
		Klm_angle_Y += K * (ay1 - Klm_angle_Y);
		P_0=(1.0-K) * P_1;
		*angy=Klm_angle_Y;
		// 陀螺仪 Y
		P_5=sqrt(P_4*P_4+Q_y*Q_y);
		K = P_5 / (P_5 + R_y);
		Klm_X += K * (Qx1 - Klm_X);
		P_4=(1.0-K) * P_5;
		*qx=Klm_X;
		//Klm_angleG_Y+=Klm_Y*dt;
		// 二阶互补滤波融合
		K = 0.8;
		x1 = (Klm_angle_Y - Com2_angle_Y) * K * K;
		y1 = y1 + x1 * dt;
		x2 = y1 + 2 * K *(Klm_angle_Y - Com2_angle_Y) + Klm_X;
		Com2_angle_Y = Com2_angle_Y + x2 * dt;
		*cy=Com2_angle_Y;
}
/* 竖直的时候 加速度的 Z 和陀螺仪的  X  相结合  */
void Get_Z_x(float *angz,float *cz,float *qx)
{
		u16 az,Qx;
		int az0;
		float az1,Qx1;

		float K;
	  //static u8 In_0=0;
		/*  一次加速度滤波 X */
		static float Klm_angle_Z;
		static float P_0 = 0.5,P_1 = 0.5;
		/*  一次陀螺仪滤波 Y */
		static float Klm_X;
		static float P_4 = 0.5,P_5 = 0.5;
		/*  二阶互补滤波  01 */
		static float x1,x2,y1;
		static float Com2_angle_Z;

		az=(MPU6050_ReadReg(ACCEL_ZOUT_H)<<8) | MPU6050_ReadReg(ACCEL_ZOUT_H+1);
		Qx=(MPU6050_ReadReg(GYRO_XOUT_H)<<8) | MPU6050_ReadReg(GYRO_XOUT_H+1);

		az0=(int)az-MPU_err_Z;
		if(az0>16384){ az0=az0-65535; }else {}	
		az1=(float)az0*90/16384;

		Qx-=MPU_err_QY;// 矫正静态误差
		if(Qx>30000){Qx1=(Adj_d)*(float)(Qx-65535);}else Qx1=(Adj_d)*(float)Qx;
		Qx1*=-1;
		
		//if(In_0==0){In_0=1;Klm_angle_Z=az1;Klm_X=Qx1;}
		
		// 加速度 X
		P_1=sqrt(P_0*P_0+Q_angle*Q_angle);
		K = P_1 / (P_1 + R_angle);
		Klm_angle_Z += K * (az1 - Klm_angle_Z);
		P_0=(1.0-K) * P_1;
		*angz=Klm_angle_Z;
		// 陀螺仪 Y
		P_5=sqrt(P_4*P_4+Q_y*Q_y);
		K = P_5 / (P_5 + R_y);
		Klm_X += K * (Qx1 - Klm_X);
		P_4=(1.0-K) * P_5;
		*qx=Klm_X;
		//Klm_angleG_Y+=Klm_Y*dt;
		// 二阶互补滤波融合
		K = 0.8;
		x1 = (Klm_angle_Z - Com2_angle_Z) * K * K;
		y1 = y1 + x1 * dt;
		x2 = y1 + 2 * K *(Klm_angle_Z - Com2_angle_Z) + Klm_X;
		Com2_angle_Z = Com2_angle_Z + x2 * dt;
		*cz=Com2_angle_Z;
}
/* 竖直的时候 加速度的 Z 和陀螺仪的  Y  相结合  */
void Get_Z_y(float *angz,float *cz,float *qy)
{
		u16 az,Qy;
		int az0;
		float az1,Qy1;

		float K;
		/*  一次加速度滤波 X */
		static float Klm_angle_Z;
		static float P_0 = 0.5,P_1 = 0.5;
		/*  一次陀螺仪滤波 Y */
		static float Klm_Y;
		static float P_4 = 0.5,P_5 = 0.5;
		/*  二阶互补滤波  01 */
		static float x1,x2,y1;
		static float Com2_angle_Z;

		az=(MPU6050_ReadReg(ACCEL_ZOUT_H)<<8) | MPU6050_ReadReg(ACCEL_ZOUT_H+1);
		Qy=(MPU6050_ReadReg(GYRO_YOUT_H)<<8) | MPU6050_ReadReg(GYRO_YOUT_H+1);

		az0=(int)az-MPU_err_Z;
		if(az0>16384){ az0=az0-65535; }else {}	
		az1=(float)az0*90/16384;

		Qy-=MPU_err_QY;// 矫正静态误差
		if(Qy>30000){Qy1=(Adj_d)*(float)(Qy-65535);}else Qy1=(Adj_d)*(float)Qy;
		Qy1*=-1;
		// 加速度 X
		P_1=sqrt(P_0*P_0+Q_angle*Q_angle);
		K = P_1 / (P_1 + R_angle);
		Klm_angle_Z += K * (az1 - Klm_angle_Z);
		P_0=(1.0-K) * P_1;
		*angz=Klm_angle_Z;
		// 陀螺仪 Y
		P_5=sqrt(P_4*P_4+Q_y*Q_y);
		K = P_5 / (P_5 + R_y);
		Klm_Y += K * (Qy1 - Klm_Y);
		P_4=(1.0-K) * P_5;
		*qy=Klm_Y;
		//Klm_angleG_Y+=Klm_Y*dt;
		// 二阶互补滤波融合
		K = 0.8;
		x1 = (Klm_angle_Z - Com2_angle_Z) * K * K;
		y1 = y1 + x1 * dt;
		x2 = y1 + 2 * K *(Klm_angle_Z - Com2_angle_Z) + Klm_Y;
		Com2_angle_Z = Com2_angle_Z + x2 * dt;
		*cz=Com2_angle_Z;
}
