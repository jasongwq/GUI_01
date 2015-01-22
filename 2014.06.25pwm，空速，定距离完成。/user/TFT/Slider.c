/* 
        ����������
*/
#include "Slider.h"

#define  Blenth     15	         //����ĳ���
#define  Slider_Num       10	   // ��� 10 ��������	 
Slider Sldat[Slider_Num];

/*  �ж�  x ��Χ����������*/
u32 Adjust_Slider(u16 x,u16 y,u8 N)
{
	  u8 sign=0;
	  u16 j;
	  u32 dat;
	  if(In_Sq(x,y,Sldat[N].x0,Sldat[N].y0,Blenth+6,Sldat[N].wide)){j=Sldat[N].x0+Blenth+7;sign=1;}
    else if(In_Sq(x,y,Sldat[N].x0+Blenth+Sldat[N].lenth-6,Sldat[N].y0,Blenth+6,Sldat[N].wide)){j=Sldat[N].x0+Blenth+Sldat[N].lenth-7;sign=1;}
		else if(In_Sq(x,y,Sldat[N].x0+Blenth+7,Sldat[N].y0,Sldat[N].lenth-14,Sldat[N].wide)){j=x;sign=1;}
		else {sign=0; return Sldat[N].datnow;}
	  
	  if(sign)Dorw_S(N,j,&dat);
	  return dat;
}
/*  ����һ�������� */
u8 Creat_Sq(u16 x0,u16 y0,u16 lenth,u16 wide,u16 startdat,u16 enddat,u16 datnow,u8 N)
{
	Sldat[N].x0=x0;
	Sldat[N].y0=y0;
	Sldat[N].lenth=lenth;
	Sldat[N].wide=wide;
	Sldat[N].startdat=startdat;
	Sldat[N].enddat=enddat;
	Sldat[N].datnow=datnow;
  Sldat[N].Lastx0=(Sldat[N].datnow-Sldat[N].startdat) * (Sldat[N].lenth-14)/(Sldat[N].enddat-Sldat[N].startdat)+Sldat[N].x0+Blenth+7;        // ��¼��һ�ε�ֵ
	Dorw_Slider(N);
	return 1;
}
/* ��һ�������� */
void Dorw_Slider(u8 N)
{	
	 My_TFT_Sq(Sldat[N].x0,Sldat[N].y0,Blenth,Sldat[N].wide,0xf800);                      // ��
	 My_TFT_Sq(Sldat[N].x0+Blenth+Sldat[N].lenth,Sldat[N].y0,Blenth,Sldat[N].wide,0xf800);// ��
	 My_TFT_Sq(Sldat[N].x0+Blenth,Sldat[N].y0,Sldat[N].lenth,Sldat[N].wide,0x56f3);       // ������������ɫ
   My_TFT_Sq(Sldat[N].x0+Blenth,Sldat[N].y0+Sldat[N].wide/2-1,Sldat[N].lenth,2,0x0);    // �������м��������
	 My_TFT_Sq(Sldat[N].Lastx0-7,Sldat[N].y0,15,Sldat[N].wide,0XBC40);                    // ����
	 TFT_Sq_Num(Sldat[N].x0+Blenth+(Sldat[N].lenth-40)/2,Sldat[N].y0+(Sldat[N].wide-14)/2,40,14,Sldat[N].datnow,7,0X0,0XFFE0);
}
/* ���»��������� */
void Slider_Updat(u16 dat,u8 N)
{  
	  if(dat!=Sldat[N].datnow)
		{
			if(dat>Sldat[N].enddat)Sldat[N].datnow=Sldat[N].enddat;
			else if(dat<Sldat[N].startdat)Sldat[N].datnow=Sldat[N].startdat;
			Sldat[N].datnow=dat;
			Sldat[N].Lastx0=(Sldat[N].datnow-Sldat[N].startdat) * (Sldat[N].lenth-14)/(Sldat[N].enddat-Sldat[N].startdat)+Sldat[N].x0+Blenth+7;        // ��¼��һ�ε�ֵ
			Dorw_Slider(N);
		}else {}
}
/* ������������λ�� */
void Dorw_S(u8 N,u16 j,u32 *dat)
{
	 u16 i;
  
	 *dat=Sldat[N].datnow=(j-Sldat[N].x0-Blenth-7) * (Sldat[N].enddat-Sldat[N].startdat)/ (Sldat[N].lenth-14) +Sldat[N].startdat;
	 
	 if(j>Sldat[N].Lastx0)  // ����
	 {
		    for(i=Sldat[N].Lastx0;i<=j;i++)
				{      	
					  TFT_DrawLine(i-8,Sldat[N].y0,i-8,Sldat[N].y0+Sldat[N].wide/2-1,0x56f3); // ��ߵ�����
					  TFT_DrawLine(i-8,Sldat[N].y0+Sldat[N].wide/2+1,i-8,Sldat[N].y0+Sldat[N].wide,0x56f3); // ��ߵ�����
					  TFT_DrawLine(i-8,Sldat[N].y0+Sldat[N].wide/2-1,i-8,Sldat[N].y0+Sldat[N].wide/2+1,0x0);	
					  TFT_CLEAR(i-6,Sldat[N].y0,15,Sldat[N].wide,0XBC40);
				}
   }
	 else if(j<Sldat[N].Lastx0)  // ����
	 {
		    for(i=Sldat[N].Lastx0;i>=j;i--)
				{
            TFT_DrawLine(i+8,Sldat[N].y0,i+8,Sldat[N].y0+Sldat[N].wide/2-1,0x56f3); // ��ߵ�����
					  TFT_DrawLine(i+8,Sldat[N].y0+Sldat[N].wide/2+1,i+8,Sldat[N].y0+Sldat[N].wide,0x56f3); // ��ߵ�����
					  TFT_DrawLine(i+8,Sldat[N].y0+Sldat[N].wide/2-1,i+8,Sldat[N].y0+Sldat[N].wide/2+1,0x0);	
					  TFT_CLEAR(i-8,Sldat[N].y0,15,Sldat[N].wide,0XBC40);
				}
   }
	 TFT_Sq_Num(Sldat[N].x0+Blenth+(Sldat[N].lenth-40)/2,Sldat[N].y0+(Sldat[N].wide-14)/2,40,14,Sldat[N].datnow,7,0X0,0XFFE0);
	 Sldat[N].Lastx0=j;        // ��¼��һ�ε�ֵ
	 
}
