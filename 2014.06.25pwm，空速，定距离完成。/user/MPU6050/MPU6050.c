#include "MPU6050.h"


static int MPU_err_X=89,MPU_err_Y=256,MPU_err_Z=8123;
static int MPU_err_QX=-11,MPU_err_QY=6,MPU_err_QZ=-16;
u16 VirtAddVarTab[NumbOfVar] = {0x5555, 0x6666, 0x7777};
u16 rwdate[12];
u8 mpu6050_buffer[14];					//iic��ȡ��������

void Get_6050_Dat(u16 *x,u16 *y,u16 *z,u16 *Qx,u16 *Qy,u16 *Qz)
{ 
    i2cRead(devAddr,MPU6050_RA_ACCEL_XOUT_H,14,mpu6050_buffer);
		
		*x=(((u16)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1];
		*y=(((u16)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3];
		*z=(((u16)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5];
		
		*Qx=(((u16)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9];
		*Qy=(((u16)mpu6050_buffer[10]) << 8) | mpu6050_buffer[11];
		*Qz=(((u16)mpu6050_buffer[12]) << 8) | mpu6050_buffer[13];	
}
#define MPU_Max_Tim 50
void Adjust_MPU6050_Ang(void)
{
	 u8 i;
	 u16 x,y,z;
	 for(i=0;i<MPU_Max_Tim;i++)
	 {
		  delay_ms(50);	  
			i2cRead(devAddr,MPU6050_RA_ACCEL_XOUT_H,14,mpu6050_buffer);
			x=(((u16)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1];
			y=(((u16)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3];
			z=(((u16)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5];
		  if(x>30000){MPU_err_X-=65535-x;}else {MPU_err_X+=x;}
			if(y>30000){MPU_err_Y-=65535-y;}else {MPU_err_Y+=y;}
			if(z>30000){MPU_err_Z-=65535-z;}else {MPU_err_Z+=z;}
   }
	 MPU_err_X/=MPU_Max_Tim;
	 MPU_err_Y/=MPU_Max_Tim;
	 MPU_err_Z/=MPU_Max_Tim;
	 printf("Ang_err : %d %d %d \r\n",MPU_err_X,MPU_err_Y,MPU_err_Z);
}
/*  ������ʼ���� */
void Adjust_MPU6050_Location(void)
{
	 u8 i;
	 u16 x,y,z;
	 for(i=0;i<MPU_Max_Tim;i++)
	 {
		  delay_ms(50);
			i2cRead(devAddr,MPU6050_RA_ACCEL_XOUT_H,14,mpu6050_buffer);
		  x=(((u16)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9];
		  y=(((u16)mpu6050_buffer[10]) << 8) | mpu6050_buffer[11];
		  z=(((u16)mpu6050_buffer[12]) << 8) | mpu6050_buffer[13];
		  if(x>30000){MPU_err_QX-=65535-x;}else {MPU_err_QX+=x;}
			if(y>30000){MPU_err_QY-=65535-y;}else {MPU_err_QY+=y;}
			if(z>30000){MPU_err_QZ-=65535-z;}else {MPU_err_QZ+=z;}
   }
	 MPU_err_QX/=MPU_Max_Tim;
	 MPU_err_QY/=MPU_Max_Tim;
	 MPU_err_QZ/=MPU_Max_Tim;
	 printf("L3G_err : %d %d %d \r\n",MPU_err_QX,MPU_err_QY,MPU_err_QZ);
}
void Adjust_All(void)
{
	  u8 i;
	  Adjust_MPU6050_Ang(); 
		Adjust_MPU6050_Location();
		
		if(MPU_err_X>0)rwdate[0]=1;else rwdate[0]=0;rwdate[1]=fabs(MPU_err_X);   
		if(MPU_err_Y>0)rwdate[2]=1;else rwdate[2]=0;rwdate[3]=fabs(MPU_err_Y);
		if(MPU_err_Z>0)rwdate[4]=1;else rwdate[4]=0;rwdate[5]=fabs(MPU_err_Z);
		if(MPU_err_QX>0)rwdate[6]=1;else rwdate[6]=0;rwdate[7]=fabs(MPU_err_QX);
		if(MPU_err_QY>0)rwdate[8]=1;else rwdate[8]=0;rwdate[9]=fabs(MPU_err_QY);	
		if(MPU_err_QZ>0)rwdate[10]=1;else rwdate[10]=0;rwdate[11]=fabs(MPU_err_QZ);
		
    for(i=0;i<12;i++)
		EE_WriteVariable(VirtAddVarTab[0]+i, rwdate[i]);
}
void Read_All_Err(void)
{
	  u8 i;
		for(i=0;i<12;i++)
		  EE_ReadVariable(VirtAddVarTab[0]+i, &(rwdate[i]));
	  
		if(rwdate[0]==1)MPU_err_X=rwdate[1];else MPU_err_X=(-1)*rwdate[1];
		if(rwdate[2]==1)MPU_err_Y=rwdate[3];else MPU_err_Y=(-1)*rwdate[3];
		if(rwdate[4]==1)MPU_err_Z=rwdate[5];else MPU_err_Z=(-1)*rwdate[5];
		if(rwdate[6]==1)MPU_err_QX=rwdate[7];else MPU_err_QX=(-1)*rwdate[7];
		if(rwdate[8]==1)MPU_err_QY=rwdate[9];else MPU_err_QY=(-1)*rwdate[9];
		if(rwdate[10]==1)MPU_err_QZ=rwdate[11];else MPU_err_QZ=(-1)*rwdate[11];
		printf("Ang_err : %d %d %d \r\n",MPU_err_X,MPU_err_Y,MPU_err_Z);
		printf("L3G_err : %d %d %d \r\n",MPU_err_QX,MPU_err_QY,MPU_err_QZ);
}
#define KmD      0.05
#define Adj_d    0.035f
#define dt       0.005f 			// ��������
void Get_Signs(float *angx,float *angy,float *cx,float *cy,float *qx,float *qy,float *qz)
{
	  u16 x,y,Qx,Qy,Qz;
		int ax0,ay0;
		float ax1,ay1;
		float Qx1,Qy1,Qz1;	
		float K;	
		static float Klm_angle_X,Klm_angle_Y;//  һ�μ��ٶ��˲� X 
		static float Klm_X,Klm_Y,Klm_Z;      //  һ���������˲� Y 
		static float x1,x2,y1;               //  ���׻����˲�  01 
		static float Com2_angle_X,Com2_angle_Y;
		
    i2cRead(devAddr,MPU6050_RA_ACCEL_XOUT_H,14,mpu6050_buffer);
		
		x=(((u16)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1];
		y=(((u16)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3];
		//z=(((u16)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5];
		
		Qx=(((u16)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9];
		Qy=(((u16)mpu6050_buffer[10]) << 8) | mpu6050_buffer[11];
		Qz=(((u16)mpu6050_buffer[12]) << 8) | mpu6050_buffer[13];
		
		ax0=(int)x-MPU_err_X;
		if(ax0>16384){ ax0=ax0-65535; }else {}	
		ax1=(float)ax0*180/16384;
		
		ay0=(int)y-MPU_err_Y;
		if(ay0>16384){ ay0=ay0-65535; }else {}	
		ay1=(float)ay0*180/16384;
//----------------------------------------------------------------------------	
		Qy-=MPU_err_QY;// ������̬���
		if(Qy>30000){Qy1=(Adj_d)*(float)(65535-Qy);}else Qy1=(Adj_d)*(float)Qy*-1;
		Qx-=MPU_err_QX;// ������̬���
		if(Qx>30000){Qx1=(Adj_d)*(float)(Qx-65535);}else Qx1=(Adj_d)*(float)Qx;
		Qz-=MPU_err_QZ;// ������̬���
		if(Qz>30000){Qz1=(Adj_d)*(float)(Qz-65535);}else Qz1=(Adj_d)*(float)Qz;		
			
		Klm_Y += KmD * (Qy1 - Klm_Y);// ������ Y		
		Klm_X += KmD * (Qx1 - Klm_X);// ������ X				
		Klm_Z += KmD * (Qz1 - Klm_Z);// ������ Z
		 *qy=Qx1;*qx=Qy1;*qz=Qz1;
		//*qy=Klm_X;*qx=Klm_Y;*qz=Klm_Z;
//----------------// ���ٶ� X	--------------------------------------------------------------					
		Klm_angle_X += KmD * (ax1 - Klm_angle_X);
		*angx=Klm_angle_X;
		//Klm_angleG_Y+=Klm_Y*dt;
		// ���׻����˲��ں�
		K = 0.8;
		x1 = (Klm_angle_X - Com2_angle_X) * K * K;
		y1 = y1 + x1 * dt;
		x2 = y1 + 2 * K *(Klm_angle_X - Com2_angle_X) + Klm_Y;
		Com2_angle_X = Com2_angle_X + x2 * dt;
		*cx=Com2_angle_X;
//--------------------// ���ٶ� Y----------------------------------------						
		Klm_angle_Y += KmD * (ay1 - Klm_angle_Y);
		*angy=Klm_angle_Y;
		//Klm_angleG_Y+=Klm_Y*dt;
		// ���׻����˲��ں�
		K = 0.8;
		x1 = (Klm_angle_Y - Com2_angle_Y) * K * K;
		y1 = y1 + x1 * dt;
		x2 = y1 + 2 * K *(Klm_angle_Y - Com2_angle_Y) + Klm_X;
		Com2_angle_Y = Com2_angle_Y + x2 * dt;
		*cy=Com2_angle_Y;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBit(u8 dev, u8 reg, u8 bitNum, u8 data)
*��������:	    �� �޸� д ָ���豸 ָ���Ĵ���һ���ֽ� �е�1��λ
����	dev  Ŀ���豸��ַ
reg	   �Ĵ�����ַ
bitNum  Ҫ�޸�Ŀ���ֽڵ�bitNumλ
data  Ϊ0 ʱ��Ŀ��λ������0 ���򽫱���λ
����   �ɹ� Ϊ1 
ʧ��Ϊ0
*******************************************************************************/ 
void IICwriteBit(u8 dev, u8 reg, u8 bitNum, u8 data){
	u8 b;
	ANO_Tech_I2C1_Read_Buf(dev, reg, 1, &b);
	b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
	ANO_Tech_I2C1_Write_1Byte(dev, reg, b);
}
/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
*��������:	    �� �޸� д ָ���豸 ָ���Ĵ���һ���ֽ� �еĶ��λ
����	dev  Ŀ���豸��ַ
reg	   �Ĵ�����ַ
bitStart  Ŀ���ֽڵ���ʼλ
length   λ����
data    ��Ÿı�Ŀ���ֽ�λ��ֵ
����   �ɹ� Ϊ1 
ʧ��Ϊ0
*******************************************************************************/ 
void IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
{
	
	u8 b,mask;
	ANO_Tech_I2C1_Read_Buf(dev, reg, 1, &b);
	mask = (0xFF << (bitStart + 1)) | 0xFF >> ((8 - bitStart) + length - 1);
	data <<= (8 - length);
	data >>= (7 - bitStart);
	b &= mask;
	b |= data;
	ANO_Tech_I2C1_Write_1Byte(dev, reg, b);
}
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void MPU6050_setClockSource(uint8_t source)
*��������:	    ����  MPU6050 ��ʱ��Դ
* CLK_SEL | Clock Source
* --------+--------------------------------------
* 0       | Internal oscillator
* 1       | PLL with X Gyro reference
* 2       | PLL with Y Gyro reference
* 3       | PLL with Z Gyro reference
* 4       | PLL with external 32.768kHz reference
* 5       | PLL with external 19.2MHz reference
* 6       | Reserved
* 7       | Stops the clock and keeps the timing generator in reset
*******************************************************************************/
void MPU6050_setClockSource(uint8_t source){
	IICwriteBits(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
	
}
/** Set full-scale gyroscope range.
* @param range New full-scale gyroscope range value
* @see getFullScaleRange()
* @see MPU6050_GYRO_FS_250
* @see MPU6050_RA_GYRO_CONFIG
* @see MPU6050_GCONFIG_FS_SEL_BIT
* @see MPU6050_GCONFIG_FS_SEL_LENGTH
*/
void MPU6050_setFullScaleGyroRange(uint8_t range) {
	IICwriteBits(devAddr, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void MPU6050_setFullScaleAccelRange(uint8_t range)
*��������:	    ����  MPU6050 ���ٶȼƵ��������
*******************************************************************************/
void MPU6050_setFullScaleAccelRange(uint8_t range) {
	IICwriteBits(devAddr, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void MPU6050_setSleepEnabled(uint8_t enabled)
*��������:	    ����  MPU6050 �Ƿ����˯��ģʽ
enabled =1   ˯��
enabled =0   ����
*******************************************************************************/
void MPU6050_setSleepEnabled(uint8_t enabled) {
	IICwriteBit(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void MPU6050_setI2CMasterModeEnabled(uint8_t enabled)
*��������:	    ���� MPU6050 �Ƿ�ΪAUX I2C�ߵ�����
*******************************************************************************/
void MPU6050_setI2CMasterModeEnabled(uint8_t enabled) {
	IICwriteBit(devAddr, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_EN_BIT, enabled);
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void MPU6050_setI2CBypassEnabled(uint8_t enabled)
*��������:	    ���� MPU6050 �Ƿ�ΪAUX I2C�ߵ�����
*******************************************************************************/
void MPU6050_setI2CBypassEnabled(uint8_t enabled) {
	IICwriteBit(devAddr, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_I2C_BYPASS_EN_BIT, enabled);
}

void MPU6050_setDLPF(uint8_t mode)
{
	IICwriteBits(devAddr, MPU6050_RA_CONFIG, MPU6050_CFG_DLPF_CFG_BIT, MPU6050_CFG_DLPF_CFG_LENGTH, mode);
}
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void MPU6050_initialize(void)
*��������:	    ��ʼ�� 	MPU6050 �Խ������״̬��
*******************************************************************************/
void MPU6050_Init(void)
{
// 		ANO_Tech_I2C1_Write_1Byte(0xd2,0x19,0x07);//1khz
// 		ANO_Tech_I2C1_Write_1Byte(0xd2,0x1a,0x03);//44hz�˲�
// 		ANO_Tech_I2C1_Write_1Byte(0xd2,0x1b,0x00);//gyro 250du/s
// 		ANO_Tech_I2C1_Write_1Byte(0xd2,0x1c,0x08);//acc +-4g
// 		ANO_Tech_I2C1_Write_1Byte(0xd2,0x24,13);//400khz
// 		ANO_Tech_I2C1_Write_1Byte(0xd2,0x6a,0x00);//mst_en=0
// 		ANO_Tech_I2C1_Write_1Byte(0xd2,0x6b,0x00);//sleep=0

  i2cInit();
	MPU6050_setSleepEnabled(0); //���빤��״̬
	delay_ms(200);
	MPU6050_setClockSource(MPU6050_CLOCK_PLL_XGYRO); //����ʱ��  0x6b   0x01
	delay_ms(50);
	MPU6050_setFullScaleGyroRange(MPU6050_GYRO_FS_2000);//������������� +-2000��ÿ��
	delay_ms(50);
	MPU6050_setFullScaleAccelRange(MPU6050_ACCEL_FS_4);	//���ٶȶ�������� +-4G
	delay_ms(50);
	MPU6050_setDLPF(MPU6050_DLPF_BW_42);
	delay_ms(50);
	MPU6050_setI2CMasterModeEnabled(0);	 //����MPU6050 ����AUXI2C
	delay_ms(50);
	MPU6050_setI2CBypassEnabled(1);	 //����������I2C��	MPU6050��AUXI2C	ֱͨ������������ֱ�ӷ���HMC5883L
	delay_ms(50);

}
