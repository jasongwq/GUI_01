
/* 就为了显示图形 */
#include "WindowP.h"

#define Max_WindowP_Num  3  // 串口最多数目
#define NB_C             0x3888
#define NZ_C             0x3333
#define N_Wide           16

My_WindowP PWin[Max_WindowP_Num];

                       
u8 Creat_PWindow(u16 x0,u16 y0,u16 lenth,u16 wide,u8 *name,u16 txcolour,u8 txnum,u8  tic,u16 colourback,u16 colour,u16  Max_y,u8 N)
{
	  u8 i;
	
	  PWin[N].x0=x0;
	  PWin[N].y0=y0;
	  PWin[N].lenth=lenth;
	  PWin[N].wide=wide;
	  for(i=0;i<20 && name[i]!='\0';i++)PWin[N].Name[i]=name[i];
	  PWin[N].tx=0;
	  PWin[N].txnum=txnum;
	  PWin[N].txcolour=txcolour;
	  PWin[N].tic=tic;
	  PWin[N].nowtic=0;
	  for(i=0;i<150;i++){PWin[N].p0[i]=0;PWin[N].p1[i]=0;}
	  PWin[N].colourback=colourback;
	  PWin[N].colour=colour;
	  PWin[N].Max_y=Max_y;
	  Drow_PWindow(N);
	
	  return 1;
}
void Drow_PWindow(u8 N)
{
	
	  TFT_Sq_Str(PWin[N].x0,PWin[N].y0,PWin[N].lenth/2,N_Wide,PWin[N].Name,NZ_C,NB_C);  // 标题
	  TFT_Sq_Float(PWin[N].x0+PWin[N].lenth/2,PWin[N].y0,PWin[N].lenth/2,N_Wide,0,PWin[N].txnum,5,PWin[N].txcolour,NB_C);
	  My_TFT_Sq(PWin[N].x0,PWin[N].y0+N_Wide,PWin[N].lenth,PWin[N].wide,PWin[N].colourback);
	    
}
void Updat_PWin(int x1,int x2,u8 mode,u8 N)
{
	  u16 t,tx0,tx1;
	  u16 y0,y01,y1,y2;
	  u16 shownum,shownum1;
	 
	  if(x1<0)shownum=(u16)((-1)*x1);
	  else shownum=(u16)x1;
	  
	  if(x2<0)shownum1=(u16)((-1)*x2);
	  else shownum1=(u16)x2;
	
	  tx0=PWin[N].x0;
	  tx1=PWin[N].x0+PWin[N].lenth;  // 最大的x
	  
	  y0=PWin[N].y0+N_Wide+PWin[N].wide/2+x1;
	  y01=PWin[N].y0+N_Wide+PWin[N].wide/2+x2;
	  y1=PWin[N].y0+N_Wide+PWin[N].wide;
	  y2=PWin[N].y0+N_Wide;
	
	  
	  //TFT_Show_Num(PWin[N].x0,PWin[N].y0+N_Wide,PWin[N].Max_y,4,PWin[N].colour,PWin[N].colourback); // 显示纵坐标上面的最大数字
	  TFT_Show_Num(PWin[N].x0,PWin[N].y0+N_Wide+PWin[N].wide/2,0,1,PWin[N].colour,PWin[N].colourback); // 显示纵坐标上面的0	   
			
	  if(mode==1)
		{
				for(t=tx0;t<tx1 && (t-tx0)<130 ;t++) TFT_DrawPoint(t,PWin[N].y0+N_Wide+PWin[N].wide/2+PWin[N].p0[t],PWin[N].colourback);		
				for(t=129;t>0;t--){PWin[N].p0[t]=PWin[N].p0[t-1];}								    
				if(y0<y1 && y0>y2)
				{
						PWin[N].p0[0]=x1;
						if(PWin[N].nowtic>=PWin[N].tic)
						{
								PWin[N].nowtic=0;
								//TFT_Show_Num(PWin[N].x0+PWin[N].lenth/2,PWin[N].y0,(u32)x1,3,PWin[N].txcolour,NB_C);
								//TFT_Show_Num(PWin[N].x0+PWin[N].lenth/2,PWin[N].y0,PWin[N].lenth/2,N_Wide,(u16)x1,3,PWin[N].txcolour,NB_C);
								TFT_Sq_Float(PWin[N].x0+PWin[N].lenth/2,PWin[N].y0,PWin[N].lenth/2,N_Wide,shownum,PWin[N].txnum,5,PWin[N].txcolour,NB_C);
						}
						else PWin[N].nowtic++;
				}		//
				for(t=tx0;t<tx1 && (t-tx0)<130 ;t++){TFT_DrawPoint(t,PWin[N].y0+N_Wide+PWin[N].wide/2+PWin[N].p0[t],PWin[N].colour);}
		}
		else if(mode==2)
		{
			
			  for(t=tx0;t<tx1 && (t-tx0)<130 ;t++) TFT_DrawPoint(t,PWin[N].y0+N_Wide+PWin[N].wide/2+PWin[N].p0[t],PWin[N].colourback);		
				for(t=129;t>0;t--){PWin[N].p0[t]=PWin[N].p0[t-1];}								    
				if(y0<y1 && y0>y2)
						PWin[N].p0[0]=x1;
				for(t=tx0;t<tx1 && (t-tx0)<130 ;t++){TFT_DrawPoint(t,PWin[N].y0+N_Wide+PWin[N].wide/2+PWin[N].p0[t],PWin[N].colour);}

					
			  for(t=tx0;t<tx1 && (t-tx0)<130 ;t++) TFT_DrawPoint(t,PWin[N].y0+N_Wide+PWin[N].wide/2+PWin[N].p1[t],PWin[N].colourback);		
				for(t=129;t>0;t--){PWin[N].p1[t]=PWin[N].p1[t-1];}								    
				if(y01<y1 && y01>y2)
				{
						PWin[N].p1[0]=x2;
						if(PWin[N].nowtic>=PWin[N].tic)
						{
								PWin[N].nowtic=0;
								//TFT_Show_Num(PWin[N].x0+PWin[N].lenth/2,PWin[N].y0,(u32)x1,3,PWin[N].txcolour,NB_C);
								//TFT_Show_Num(PWin[N].x0+PWin[N].lenth/2,PWin[N].y0,PWin[N].lenth/2,N_Wide,(u16)x1,3,PWin[N].txcolour,NB_C);
								TFT_Sq_Float(PWin[N].x0+PWin[N].lenth/2,PWin[N].y0,PWin[N].lenth/2,N_Wide,shownum1,PWin[N].txnum,5,0xf100,NB_C);
						}
						else PWin[N].nowtic++;
				}		//
				for(t=tx0;t<tx1 && (t-tx0)<130 ;t++){TFT_DrawPoint(t,PWin[N].y0+N_Wide+PWin[N].wide/2+PWin[N].p1[t],0xf100);}
    }else {}
}

