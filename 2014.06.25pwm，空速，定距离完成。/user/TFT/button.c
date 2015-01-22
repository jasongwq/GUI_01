/*




*/
#include "button.h"


#define Max_Button_0  20

Button_0 But0[Max_Button_0];
u8 Creat_Buuton_0(u16 x0,u16 y0,u8 *name,u16 startdat,u16 enddat,u16 datnow,u8 step,u8 N)
{ 
	  u8 i;
	  But0[N].x0=x0;
	  But0[N].y0=y0;
	  for(i=0;i<4 && name[i]!='\0';i++)But0[N].name[i]=name[i];
	  But0[N].startdat=startdat;
	  But0[N].enddat=enddat;
	  if(datnow<But0[N].startdat)datnow=But0[N].startdat;
	  else if(datnow>But0[N].enddat)datnow=But0[N].enddat;
	  else {}
	  But0[N].datnow=datnow;
	  But0[N].step=step;
    Dorw_But0(N);
	  return 1;
}
void Dorw_But0(u8 N)
{
	  TFT_Sq_Str(But0[N].x0,But0[N].y0,24,31,But0[N].name,0x0,0XBC40);
		TFT_Sq_Num(But0[N].x0+24,But0[N].y0,35,31,But0[N].datnow,7,0x0,0XBC40);
		TFT_Sq_Str(But0[N].x0+24+35,But0[N].y0,40,15,"+",0x0,0x7D7C);
		TFT_Sq_Str(But0[N].x0+24+35,But0[N].y0+16,40,15,"-",0x0,0x7D7C);
}
void But0_Updat(u16 dat,u8 N)
{
	  if(dat>But0[N].enddat)dat=But0[N].enddat;
	  else if(dat<But0[N].startdat)dat=But0[N].startdat;
	  But0[N].datnow=dat;
    TFT_Sq_Num(But0[N].x0+24,But0[N].y0,35,31,But0[N].datnow,7,0x0,0XBC40);
}
u16 But0_Deal(u16 x,u16 y,u8 N)
{
	  static u16 tic=0;
	  if(In_Sq(x,y,But0[N].x0+24+35,But0[N].y0,40,15))
  	{
			  But0[N].datnow=But0[N].datnow+But0[N].step;
			  if(But0[N].datnow>But0[N].enddat)But0[N].datnow=But0[N].datnow-But0[N].enddat+But0[N].startdat;			
			  TFT_Sq_Str(But0[N].x0,But0[N].y0,24,31,But0[N].name,0x0,0XBC40);
			  TFT_Sq_Num(But0[N].x0+24,But0[N].y0,35,31,But0[N].datnow,7,0x0,0XBC40);
			  TFT_Sq_Str(But0[N].x0+24+35,But0[N].y0,40,15,"+",0x7D7C,0x1111);
			
			  tic=0;
				while(!PEN)
				{
						if(tic>=100)
						{
								But0[N].datnow=But0[N].datnow+But0[N].step;
								if(But0[N].datnow>But0[N].enddat)But0[N].datnow=But0[N].datnow-But0[N].enddat+But0[N].startdat;
								TFT_Sq_Str(But0[N].x0,But0[N].y0,24,31,But0[N].name,0x0,0XBC40);
								TFT_Sq_Num(But0[N].x0+24,But0[N].y0,35,31,But0[N].datnow,7,0x0,0XBC40);
								TFT_Sq_Str(But0[N].x0+24+35,But0[N].y0,40,15,"+",0x7D7C,0x1111);
								delay_ms(100);
						}
						else {delay_ms(10);tic++;}
				}
        Dorw_But0(N);				
	  }
		else if(In_Sq(x,y,But0[N].x0+24+35,But0[N].y0+16,40,15))
		{
			  if(But0[N].datnow-But0[N].step<But0[N].startdat)But0[N].datnow=But0[N].enddat+But0[N].datnow-But0[N].startdat-But0[N].step;
			  else But0[N].datnow=But0[N].datnow-But0[N].step;
			  TFT_Sq_Str(But0[N].x0,But0[N].y0,24,31,But0[N].name,0x0,0XBC40);
			  TFT_Sq_Num(But0[N].x0+24,But0[N].y0,35,31,But0[N].datnow,7,0x0,0XBC40);
			  TFT_Sq_Str(But0[N].x0+24+35,But0[N].y0+16,40,15,"-",0x7D7C,0x1111);
				tic=0;
			  while(!PEN)
				{
						if(tic>=100)
						{
								if(But0[N].datnow-But0[N].step<But0[N].startdat)But0[N].datnow=But0[N].enddat+But0[N].datnow-But0[N].startdat-But0[N].step;
								else But0[N].datnow=But0[N].datnow-But0[N].step;
								TFT_Sq_Str(But0[N].x0,But0[N].y0,24,31,But0[N].name,0x0,0XBC40);
								TFT_Sq_Num(But0[N].x0+24,But0[N].y0,35,31,But0[N].datnow,7,0x0,0XBC40);
								TFT_Sq_Str(But0[N].x0+24+35,But0[N].y0+16,40,15,"-",0x7D7C,0x1111);
								delay_ms(100);
						}
						else {delay_ms(10);tic++;}
				}
        Dorw_But0(N);				
    }else {}
		return But0[N].datnow;
}

/*        多值化按钮      */
#define Max_Button_1 10
#define Bt1L  60          // 长
#define Bt1W  20          // 宽
Button_1 But1[Max_Button_1];
u8 Creat_Buuton_1(u16 x0,u16 y0,u16 colour,u8 *name,u8 startdat,u8 enddat,u8 datnow,u8 N)
{   
	  u8 i;
	  But1[N].x0=x0;
	  But1[N].y0=y0;
	  But1[N].colour=colour;
	  for(i=0;i<4 && name[i]!='\0';i++)But1[N].Name[i]=name[i];
	  But1[N].startdat=startdat;
	  But1[N].enddat=enddat;
	  if(datnow<But1[N].startdat)datnow=But1[N].startdat;
	  else if(datnow>But1[N].enddat)datnow=But1[N].enddat;
	  else {}
	  But1[N].datnow=datnow;
	
	  Dorw_But1(N);
	  return 1;
}
void Dorw_But1(u8 N)
{
	  TFT_Sq_Str(But1[N].x0,But1[N].y0,Bt1L/2,Bt1W,But1[N].Name,0x0,But1[N].colour);
		TFT_Sq_Num(But1[N].x0+Bt1L/2,But1[N].y0,Bt1L/2,Bt1W,But1[N].datnow,3,0x0,But1[N].colour);
}
void But1_Updat(u16 dat,u8 N)
{
	  if(dat>But1[N].enddat)dat=But1[N].enddat;
	  else if(dat<But1[N].startdat)dat=But1[N].startdat;
	  But1[N].datnow=dat;
    TFT_Sq_Num(But1[N].x0+Bt1L/2,But1[N].y0,Bt1L/2,Bt1W,But1[N].datnow,3,0x0,But1[N].colour);
}
u8 But1_Deal(u16 x,u16 y,u8 N)
{
	  u16 R,G,B,bright=10;
	  
	  if(In_Sq(x,y,But1[N].x0,But1[N].y0,Bt1L,Bt1W))
		{
			  if(But1[N].datnow<But1[N].enddat)But1[N].datnow++;
			  else But1[N].datnow=But1[N].startdat;
			  R = (But1[N].colour & 0xF800) >> 11;
				G = (But1[N].colour & 0x07E0) >> 5;
				B =  But1[N].colour & 0x001F;
			  if (R > bright){R -= bright;}else{R = 0;}
				if (G > 2 * bright){G -= 2 * bright;}else{G = 0;}
				if (B > bright){B -= bright;}else{B = 0;}				
			  TFT_Sq_Str(But1[N].x0,But1[N].y0,Bt1L/2,Bt1W,But1[N].Name,0x7D7C,(R<<11)+(G<<5)+B);
		    TFT_Sq_Num(But1[N].x0+Bt1L/2,But1[N].y0,Bt1L/2,Bt1W,But1[N].datnow,3,0x7D7C,(R<<11)+(G<<5)+B);
			  while(!PEN);
			  Dorw_But1(N);
    }
		else {}
		return But1[N].datnow;
}
/*  二值化按钮  */
#define Max_Button_2 10
#define Bt2L  60          // 长
#define Bt2W  20          // 宽
Button_2 But2[Max_Button_2];
u8 Creat_Buuton_2(u16 x0,u16 y0,u16 colour0,u8 *name0,u16 colour1,u8 *name1,u8 datnow,u8 N)
{
	  u8 i;
	  But2[N].x0=x0;
	  But2[N].y0=y0;
	  But2[N].colour0=colour0;
	  for(i=0;i<6 && name0[i]!='\0';i++)But2[N].Name0[i]=name0[i];
	  But2[N].colour1=colour1;
	  for(i=0;i<6 && name1[i]!='\0';i++)But2[N].Name1[i]=name1[i];
	  if(datnow)datnow=1;
	  else {datnow=0;}
	  But2[N].datnow=datnow;
	
	  Dorw_But2(N);
	  return 1;
}
void Dorw_But2(u8 N)
{
	  if(But2[N].datnow==1)TFT_Sq_Str(But2[N].x0,But2[N].y0,Bt2L,Bt2W,But2[N].Name0,But2[N].colour1,But2[N].colour0);
	  else 
			if(But2[N].datnow==0)TFT_Sq_Str(But2[N].x0,But2[N].y0,Bt2L,Bt2W,But2[N].Name1,But2[N].colour0,But2[N].colour1);
}
void But2_Updat(u16 dat,u8 N)
{
	  if(dat)dat=1;
	  else dat=0;
	  But2[N].datnow=dat;
    Dorw_But2(N);
}
u8 But2_Deal(u16 x,u16 y,u8 N)
{
	  if(In_Sq(x,y,But2[N].x0,But2[N].y0,Bt2L,Bt2W))
		{
			  if(But2[N].datnow==1)
				{
					  But2[N].datnow=0;
					  TFT_Sq_Str(But2[N].x0,But2[N].y0,Bt2L,Bt2W,But2[N].Name1,But2[N].colour0,But2[N].colour1);
        }
				else if(But2[N].datnow==0)
				{
					  But2[N].datnow=1;
					  TFT_Sq_Str(But2[N].x0,But2[N].y0,Bt2L,Bt2W,But2[N].Name0,But2[N].colour1,But2[N].colour0);
        }
				while(!PEN);
    }
		return But2[N].datnow;
}
/*  二值化按钮  做返回按键用 */
#define Max_Button_3 15

Button_3 But3[Max_Button_3];
u8 Creat_Buuton_3(u16 x0,u16 y0,u16 lenth,u16 wide,u16 colour0,u8 *name0,u16 colour1,u8 *name1,u8 N)
{
	  u8 i;
	  But3[N].x0=x0;
	  But3[N].y0=y0;
	  But3[N].lenth=lenth;
	  But3[N].wide=wide;
	  But3[N].colour0=colour0;
	  for(i=0;i<7 && name0[i]!='\0';i++)But3[N].Name0[i]=name0[i];
	  But3[N].colour1=colour1;
	  for(i=0;i<7 && name1[i]!='\0';i++)But3[N].Name1[i]=name1[i];
	
	  Dorw_But3(N);
	  return 1;
}
void Dorw_But3(u8 N)
{
	  TFT_Sq_Str(But3[N].x0,But3[N].y0,But3[N].lenth,But3[N].wide,But3[N].Name0,But3[N].colour1,But3[N].colour0);
}
u8 But3_Deal(u16 x,u16 y,u8 N)
{
	  if(In_Sq(x,y,But3[N].x0,But3[N].y0,But3[N].lenth,But3[N].wide))
		{			  
				TFT_Sq_Str(But3[N].x0,But3[N].y0,But3[N].lenth,But3[N].wide,But3[N].Name1,But3[N].colour0,But3[N].colour1);       
				while(!PEN);
			  return 1;
    }
		return 0;
}
