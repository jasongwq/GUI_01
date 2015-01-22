/*


*/

#include "Motor.h"


u16 A=20;
u16 B=70;
u16 C=5;

/* ������ĸ� PWM ���� */
void Motor_PWM(u16 p1,u16 p2,u16 p3,u16 p4)
{
	  if(p1>MinPWM+MaxMM)p1=MinPWM+MaxMM;
	  else if(p1<MinPWM)p1=MinPWM;else {}
	
	  if(p2>MinPWM+MaxMM)p2=MinPWM+MaxMM;
	  else if(p2<MinPWM)p2=MinPWM;else {}
	
	  if(p3>MinPWM+MaxMM)p3=MinPWM+MaxMM;
	  else if(p3<MinPWM)p3=MinPWM;else {}
	
	  if(p4>MinPWM+MaxMM)p4=MinPWM+MaxMM;
	  else if(p4<MinPWM)p4=MinPWM;else {}
		speed1=p2;
		TIM8_Change_Period(p2);//Change_TIM8_OC1_Pulse(x/2)
	  //Motor1_PWM(p1);
		Motor2_PWM(p2);
		Motor3_PWM(p3);
		//Motor4_PWM(p4);
		
}

/* �����������Ƕ� */
/*
   (A0)1    .    3(C7)
           /|\
            |
   (A1)4         2(C6)
*/
void Adjust_Motor(float AngX,float AngY,float AngZ)
{
	  int Qx,Qy,Qz;          // �Ǽ��ٶ�
	  int cx,cy;          // Ŀ��ǶȺ�ʵ�ʽǶȵĲ�ֵ
	  int pwx,pwy,pwz;        // X �� Y����ĵ���ֵ
	  static int px,py;
	  
	  cx=(int)((comx-AngX)*10);  // <0 1 4 ����   2 3 ����
		if(cx>300)cx=300;else if(cx<-300)cx=-300;else {}
	  cy=(int)((comy-AngY)*10);  // <0 1 3 ����   2 4 ����
		if(cy>300)cy=300;else if(cy<-300)cy=-300;else {}

	  px+=cx; if(px>200000)px=200000; else if(px<-200000)px=-200000;
	  py+=cy; if(py>200000)py=200000; else if(py<-200000)py=-200000;
    
	  Qx=(int)qx;  // <0 1 4 ����   2 3 ����
		Qy=(int)qy;  // >0 1 3 ����   2 4 ����
		Qz=(int)qz;    // ˳ʱ�� +  ��ʱ�� -  >0  1 2 ����
		if(Qx>30)Qx=30;else if(Qx<-30)Qx=-30;else {}
		if(Qy>30)Qy=30;else if(Qy<-30)Qy=-30;else {}
		if(Qz>30)Qz=30;else if(Qz<-30)Qz=-30;else {}

    pwx=A*(int)Qx*PMM/2000+B*cx*PMM/100000+C*px/10000;
		pwy=A*(int)Qy*PMM/2000+B*cy*PMM/100000+C*py/10000; // ǰ�� �� PWM��
		pwz=A*(int)Qz*PMM/2000+B*AngZ;	  

		PM1=MinPWM+PMM+(-1)*pwx;
		PM2=MinPWM+PMM+pwx;
		PM3=MinPWM+PMM+pwx;
		PM4=MinPWM+PMM+(-1)*pwx;
		
//		PM1=MinPWM+PMM-pwx+pwy-pwz;
//		PM2=MinPWM+PMM+pwx-pwy-pwz;
//		PM3=MinPWM+PMM+pwx+pwy+pwz;
//		PM4=MinPWM+PMM-pwx-pwy+pwz;
 
}


