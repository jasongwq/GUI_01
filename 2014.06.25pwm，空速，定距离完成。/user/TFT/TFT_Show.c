/*

                   各种显示

*/
#include "TFT_Show.h"
#include "font.h"

/* 硬件接口 */
void My_TFT_WR_Data(u32 dat)
{
	 LCD_WR_Data(dat);
}
void My_Dorw_Point(u16 x,u16 y,u16 z)
{
	 TFT_DrawPoint(x,y,z);
}
void My_TFT_Sq(u16 x,u16 y,u16 len,u16 wid,u16 z)
{
	TFT_CLEAR(x,y,len,wid,z);
}
//取绝对值
u32 abs(s32 res)
{
	if(res<0)return -res;
	else return res;
} 
void TFT_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2 ,u16 z)
{
	u16 x, y, t;
	if((x1==x2)&&(y1==y2))TFT_DrawPoint(x1, y1,z);
	else if(abs(y2-y1)>abs(x2-x1))// 
	{
		if(y1>y2) 
		{
			t=y1; y1=y2; y2=t; 
			t=x1; x1=x2; x2=t; 
		}
		for(y=y1;y<y2;y++)
		{
			x=(u32)(y-y1)*(x2-x1)/(y2-y1)+x1;
			TFT_DrawPoint(x, y, z);  
		}
	} else    
	{
		if(x1>x2)
		{
			t=y1; y1=y2; y2=t;
			t=x1; x1=x2; x2=t;
		}   
		for(x=x1;x<x2;x++)//?x???? 
		{
			y =(u32)(x-x1)*(y2-y1)/(x2-x1)+y1;
			TFT_DrawPoint(x,y,z); 
		}
	} 
}
void TFT_SwCr(u16 x,u16 y,u8 num,u16 z,u16 l,u8 mode)
{       
		u8 temp,pos,t;
	  u16 a;
		
		a=x; num=num-' ';
		for(pos=0;pos<12;pos++)
		{
				x=a; temp=asc2_1206[num][pos]; y++;
				for(t=0;t<6;t++)
				{   
						x++;
						if(temp&0x01)My_Dorw_Point(x,y,z); 
					  else {if(mode==0)My_Dorw_Point(x,y,l); else {}}
						temp>>=1; 
				}
		}
} 
void TFT_SwCr_0(u16 x,u16 y,u8 num,u16 z,u16 l,u8 start,u8 end,u8 mode)
{       
		u8 temp,pos,t;
	  u16 a;
		
		a=x; num=num-' ';
		for(pos=start;pos<end;pos++)
		{
				x=a; temp=asc2_1206[num][pos]; y++;
				for(t=0;t<6;t++)
				{   
						x++;
						if(temp&0x01)My_Dorw_Point(x,y,z); 
					  else {if(mode==0)My_Dorw_Point(x,y,l); else {}}
						temp>>=1; 
				}
		}
} 
/* 有背景颜色   */
void TFT_ShowChar(u16 x,u16 y,u8 num,u16 z,u16 l)
{ TFT_SwCr(x,y,num,z,l,0); }
/* 不带背景颜色 */
void TFT_ShowChar1(u16 x,u16 y,u8 num,u16 z)
{ TFT_SwCr(x,y,num,z,0,1); }

#define MAX_CHAR_POSX 234
#define MAX_CHAR_POSY 308 
void TFT_ShStr(u16 x,u16 y,const u8 *p,u16 z,u16 l,u8 mode)
{         
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=12;}
        if(y>MAX_CHAR_POSY){y=0;}
        TFT_SwCr(x,y,*p,z,l,mode);
        x+=6;
        p++;
    }  
}
/* 选择性显示字符串 */
void TFT_ShStri(u16 x,u16 y,const u8 *p,u8 start,u8 end,u16 z)
{
	  while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=12;}
        if(y>MAX_CHAR_POSY){y=0;}
				TFT_SwCr_0(x,y,*p,z,0xffff,start,end,1);// 不带背景颜色
        x+=6;
        p++;
    }
}
/* 有背景颜色   */
void TFT_ShowString(u16 x,u16 y,const u8 *p,u16 z,u16 l)
{ TFT_ShStr(x,y,p,z,l,0); }
/* 不带背景颜色 */
void TFT_ShowString1(u16 x,u16 y,const u8 *p,u16 z)
{ TFT_ShStr(x,y,p,z,0,1); }


//X的N次
static unsigned int N_X(unsigned char x,unsigned char n)
{
	unsigned char i;
	unsigned int date=1;
	if(n)for(i=0;i<n;i++)date*=x;
	else date=1;
	return date;
}
/* 显示一个数字, date为显示的数字，num为开的窗口 */
void TFT_Show_Num(u16 x,u16 y,u32 date,u8 win,u16 z,u16 l)
{
	  u32 date0;
    u8 i,j,dat[15];
    
    for(i=0;i<win;i++)dat[i]=' ';dat[win]='\0';
    if(date==0) {dat[0]='0';TFT_ShowString(x,y,dat,z,l);}   
    else
    {
        j=1; date0=date;
        for(i=0;date0>0;i++)date0/=10;
        date0=date;
        
        for(j=0;j<i;j++)
        {
            date0%=N_X(10,i-j);
            date0/=N_X(10,i-j-1);
            dat[j]=date0+'0';
            date0=date;
        }
        TFT_ShowString(x,y,dat,z,l);
    }
}
/* 显示一个数字, date为显示的数字，num为开的窗口 */
void TFT_Show_Num1(u16 x,u16 y,u32 date,u8 win,u16 z)
{
	  u32 date0;
    u8 i,j,dat[15];
    
    for(i=0;i<win;i++)dat[i]=' ';dat[win]='\0';
    if(date==0) {dat[0]='0';TFT_ShowString1(x,y,dat,z);}   
    else
    {
        j=1; date0=date;
        for(i=0;date0>0;i++)date0/=10;
        date0=date;
       
        for(j=0;j<i;j++)
        {
            date0%=N_X(10,i-j);
            date0/=N_X(10,i-j-1);
            dat[j]=date0+'0';
            date0=date;
        }
        TFT_ShowString1(x,y,dat,z);
    }
}
/* 显示小数                         数据   小数位数  窗口  字体颜色 背景颜色*/
void TFT_Show_Float(u16 x,u16 y,   u32 date,u8 n,   u8 win, u16 z,    u16 l)
{
	u8 i;
  u32 date0;
  if(n)
  {
		TFT_Show_Num(x,y,date/N_X(10,n),win,z,l);
    date0=date/N_X(10,n);
    for(i=0;date0>0;i++)date0/=10;
		TFT_ShowChar(x+i*6,y,'.',z,l);
		TFT_Show_Num(x+(i+1)*6,y,date%N_X(10,n),win-n,z,l);
  }else {TFT_Show_Num(x+(i+1)*6,y,date,win,z,l);}
}
/* 显示小数                         数据   小数位数  窗口  字体颜色 */
void TFT_Show_Float1(u16 x,u16 y,   u32 date,u8 n,   u8 win, u16 z)
{
	u8 i;
  u32 date0;
  if(n)
  {
		TFT_Show_Num1(x,y,date/N_X(10,n),win,z);
    date0=date/N_X(10,n);
    for(i=0;date0>0;i++)date0/=10;
		TFT_ShowChar1(x+i*6,y,'.',z);
		TFT_Show_Num1(x+(i+1)*6,y,date%N_X(10,n),win-n,z);
  }else {TFT_Show_Num1(x+(i+1)*6,y,date,win,z);}
}
//  0.03  3  30 1000
//  12.3  3  12300
/* 显示小数                 数据   保留位数  窗口  字体颜色 */
void TFT_Show_Float2(u16 x,u16 y,float fdat,u8 n, u8 win, u16 z)
{
	u8 i,t;
  int dat;
	u32 date0;
  dat=(int)(fdat*N_X(10,n));
	if(dat>0)
	{
		  if(dat<N_X(10,n))
			{
				 if(n)
				 {
					 for(t=1;dat*N_X(10,t)<N_X(10,n);t++);// 获得前面有几个0		
					 TFT_ShowChar1(x,y,'0',z);
					 TFT_ShowChar1(x+6,y,'.',z);				
					 for(i=0;i<(t-1);i++)
							 TFT_ShowChar1(x+12+i*6,y,'0',z);				
					 TFT_Show_Num1(x+6+t*6,y,dat,win-t,z);
				 }else {TFT_Show_Num1(x,y,(u16)fdat,win,z);}
				//printf(" dat %d t %d  %d %d \r\n",dat,t,N_X(10,t),N_X(10,n));
      }
			else 
			{
				  if(n)
					{
						TFT_Show_Num1(x,y,dat/N_X(10,n),win,z);
						date0=dat/N_X(10,n);
						for(i=0;date0>0;i++)date0/=10;
						TFT_ShowChar1(x+i*6,y,'.',z);
						TFT_Show_Num1(x+(i+1)*6,y,dat%N_X(10,n),win-n,z);
					}else {TFT_Show_Num1(x,y,(u16)fdat,win,z);}
      }
  }
	else if(dat<0)
	{
		  dat*=-1;
		  if(dat<N_X(10,n))
			{
				 if(n)
				 {
					 for(t=1;dat*N_X(10,t)<N_X(10,n);t++);// 获得前面有几个0	
					 TFT_ShowChar1(x,y,'-',z);
					 TFT_ShowChar1(x+6,y,'0',z);
					 TFT_ShowChar1(x+12,y,'.',z);				
					 for(i=0;i<(t-1);i++)
							 TFT_ShowChar1(x+18+i*6,y,'0',z);				
					 TFT_Show_Num1(x+12+t*6,y,dat,win-t-1,z);
				 }else {TFT_Show_Num1(x,y,(u16)fdat,win,z);}
				
      }
			else 
			{
				  if(n)
					{
				    TFT_ShowChar1(x,y,'-',z);
				    TFT_Show_Num1(x+6,y,dat/N_X(10,n),win,z);
						date0=dat/N_X(10,n);
						for(i=0;date0>0;i++)date0/=10;
						TFT_ShowChar1(x+6+i*6,y,'.',z);
						TFT_Show_Num1(x+(i+2)*6,y,dat%N_X(10,n),win-n-1,z);
					}else {TFT_Show_Num1(x,y,(u16)fdat,win,z);}
      }
  }
	else if(dat==0)
	{
		TFT_ShowChar1(x,y,'0',z);
				 TFT_ShowChar1(x+6,y,'.',z);				
				for(i=0;i<n;i++)
		         TFT_ShowChar1(x+12+i*6,y,'0',z);
  }
}
/*** */
void TFT_Chinese_1612(u16 x,u16 y,const u8 (*p)[24] ,u8 num,u16 z,u16 l,u8 mode)
{       
	u32 temp;
	u8 pos,t;
	u16 a;	
	
	a=x;
	for(pos=0;pos<12;pos++)
	{
		x=a; temp=*(*(p+num)+pos*2+1)<<8 | *(*(p+num)+pos*2); y++;
		for(t=0;t<12;t++)
		{   
			x++;		       
			if(temp&0x0001)My_Dorw_Point(x,y,z);
			else {if(mode==0)My_Dorw_Point(x,y,l);else {}  }   
			temp>>=1; 
		}
	}
}
/* 显示中文 带背景颜色 */
void TFT_Chin_16120(u16 x,u16 y,const u8 (*p)[24] ,u8 n,u16 z,u16 l)
{
	u8 i;
	for(i=0;i<n;i++)
	  TFT_Chinese_1612(x+=12,y,p,i,z,l,0);
}
/* 显示中文 不带背景颜色 */
void TFT_Chin_16121(u16 x,u16 y,const u8 (*p)[24] ,u8 n,u16 z)
{
	u8 i;
	for(i=0;i<n;i++)
	  TFT_Chinese_1612(x+=12,y,p,i,z,0,1);
}
/* 矩形内居中显示中文字 */
void TFT_Sq_Chin_1612(u16 x,u16 y,u16 len,u16 wid,const u8 (*p)[24] ,u8 n,u16 z,u16 l)
{
	  u16 x0,y0,L=0;
	  
	  L=12*n;
	  if(L>len){x0=(L-len)/2+x; y0=(wid-12)/2+y;}
		else { x0=(len-L)/2+x-12; y0=(wid-12)/2+y; }
	  TFT_CLEAR(x,y,len,wid,l);
	  TFT_Chin_16121(x0,y0,p,n,z);
}
/* 矩形内居中显示字符串 */
void TFT_Sq_Str(u16 x,u16 y,u16 len,u16 wid,u8 *p ,u16 z,u16 l)
{
	  u8 n;
	  u16 x0,y0,L=0;
	  for(n=0;p[n]!='\0';n++);
	  L=6*n;
	  if(L>len){x0=(L-len)/2+x; y0=(wid-12)/2+y;}
		else { x0=(len-L)/2+x; y0=(wid-12)/2+y; }
	  TFT_CLEAR(x,y,len,wid,l);
	  TFT_ShowString1(x0,y0,p,z);
}
/* 矩形内居中显示数字 */
void TFT_Sq_Num(u16 x,u16 y,u16 len,u16 wid,u32 date,u8 win,u16 z,u16 l)
{
	  u8 n;
	  u32 date0;
	  u16 x0,y0,L=0;
	 
	  date0=date;
    for(n=0;date0>0;n++)date0/=10;
	  L=6*n;
	  if(L>len){x0=(L-len)/2+x; y0=(wid-12)/2+y;}
		else { x0=(len-L)/2+x; y0=(wid-12)/2+y; }
	  TFT_CLEAR(x,y,len,wid,l);
    TFT_Show_Num1(x0,y0,date,win,z);
}
/* 矩形内居中显示小数 */
void TFT_Sq_Float(u16 x,u16 y,u16 len,u16 wid,u32 date,u8 m,u8 win,u16 z,u16 l)
{
	  u8 n;
	  u32 date0;
	  u16 x0,y0,L=0;
	 
	  date0=date;
    for(n=0;date0>0;n++)date0/=10;
	  L=6*(n+1);
	  if(L>len){x0=(L-len)/2+x; y0=(wid-12)/2+y;}
		else { x0=(len-L)/2+x; y0=(wid-12)/2+y; }
	  TFT_CLEAR(x,y,len,wid,l);
    //TFT_Show_Num1(x0,y0,date,win,z);
    TFT_Show_Float1(x0,y0,date,m,win,z);
}
/* 矩形内居中显示小数 */
void TFT_Sq_Float1(u16 x,u16 y,u16 len,u16 wid,float fdat,u8 n,u8 win,u16 z,u16 l)
{
	
	  u8 t;
	  u32 date;
	  u16 x0,y0,L=0;
	
	   if(fdat<0)L=18+n*6;
	   else if(fdat<1 && fdat>0)L=12+n*6;
	   else if(fdat>0)
		 {
			   L=12+n*6;
			   date=(u32)fdat;
			   for(t=0;date>0;t++)date/=10;
			   L=t*6+n*6+6;
			 
		 }else L=6;
		 //printf(" l=%d \r\n",L);

	  if(L>len){x0=x-(L-len)/2; y0=(wid-12)/2+y;}
		else { x0=(len-L)/2+x; y0=(wid-12)/2+y; }
	  TFT_CLEAR(x,y,len,wid,l);
    TFT_Show_Float2(x0,y0,fdat,n,win,z);
}
/* 判断是否在矩形区域内 */
u8 In_Sq(u16 x,u16 y,u16 x0,u16 y0,u16 length ,u16 wide)
{
	  if(x>x0 && x<x0+length && y>y0 && y<y0+wide)return 1;
	  else return 0;
}
