

#include "Window.h"

#define Max_Window_Num  3  // 串口最多数目
#define NOti_Back_C    0x3888
#define Noti_Z_C       0x3333
#define Noti_Wide      16

My_Window WIN[Max_Window_Num];

u8 Adjust_Window(u16 x,u16 y,u8 N)
{   

//	  static u8 tic=0,sign=0;
//	  static u16 Last_x0,Last_y0;
//	
//	  sign=0;
//	  if(In_Sq(x,y,WIN[N].x0,WIN[N].y0,WIN[N].lenth,Noti_Wide))
//		{
//			    sign=1;
//			  if(tic==1)
//				{					  
//					  Last_x0=x;
//			      Last_y0=y;
//					  tic++;
//        }
//			  else if(tic>2)
//				{
//					  tic=0;
//					  if(x>Last_x0){WIN[N].x0+=x-Last_x0;}
//						else {WIN[N].x0-=Last_x0-x;}
//						if(y>Last_y0){WIN[N].y0+=y-Last_y0;}
//						else {WIN[N].y0-=Last_y0-y;}
//						
//						Last_x0=x;
//			      Last_y0=y;
//					  Drow_Window(N);
//				}else tic++;	
//    }
//		else if(In_Sq(x,y,WIN[N].x0,WIN[N].y0+Noti_Wide,WIN[N].lenth,WIN[N].wide))
//		{
//        	sign=2;		
//    }
//		
//		if(sign==1)
//		{
//			  while(!PEN)
//				{
//					  
//        }
//    }
	  return 1;
}
u8 Creat_Window(u16 x0,u16 y0,u16 lenth,u16 wide,u8 *name,u16 colourback,u16 colour,u8 N)
{
	  u16 i;
	
		WIN[N].x0=x0;
		WIN[N].y0=y0;
		WIN[N].lenth=lenth;
		WIN[N].wide=wide;
		for(i=0;i<20 && name[i]!='\0';i++)WIN[N].Name[i]=name[i];
		WIN[N].colourback=colourback;
		WIN[N].colour=colour;
	  
	  WIN[N].zx=0;
	  WIN[N].zy=0;
	  WIN[N].zl=0;   // 向上高出多少个像素点
	  for(i=0;i<300;i++)WIN[N].Str[i]=' ';	
		WIN[N].location=0;	 
	  
	  Drow_Window(N);
	  return 1;
}

void Drow_Window(u8 N)
{
	  TFT_Sq_Str(WIN[N].x0,WIN[N].y0,WIN[N].lenth,Noti_Wide,WIN[N].Name,Noti_Z_C,NOti_Back_C);  // 标题
	  My_TFT_Sq(WIN[N].x0,WIN[N].y0+Noti_Wide,WIN[N].lenth,WIN[N].wide,WIN[N].colourback);
	  Show_Win_Str(N);
}
void Show_Win_Str(u8 N)
{
	  u16 i,j,nx0,ny0,ny1;
	  u16 tx,ty,num;
	  nx0=WIN[N].lenth/6;   // 一行字符数	  
	  ny0=WIN[N].wide/12;
	  ny1=(WIN[N].wide-(12-WIN[N].zl%12))%12;
	  
	  num=WIN[N].zl/12;// 从第几列开始显示
	 // printf(" num= %d \r\n",num);
	  tx=WIN[N].x0;
	  ty=WIN[N].y0+Noti_Wide-WIN[N].zl%12-1;
	  for(i=0;i<ny0+1;i++)
		{
			  tx=WIN[N].x0;
			  for(j=0;j<nx0;j++)
			  {
					  if(ty==WIN[N].y0+Noti_Wide-WIN[N].zl%12-1)    // 第一行
							  TFT_SwCr_0(tx,WIN[N].y0+Noti_Wide-1,WIN[N].Str[(num+i)*nx0+j],WIN[N].colour,WIN[N].colourback,WIN[N].zl%12,12,0);
						else if(ty+12>WIN[N].y0+Noti_Wide+WIN[N].wide)// 最后一行
							  TFT_SwCr_0(tx,ty,WIN[N].Str[(num+i)*nx0+j],WIN[N].colour,WIN[N].colourback,0,ny1,0);
						else  TFT_SwCr_0(tx,ty,WIN[N].Str[(num+i)*nx0+j],WIN[N].colour,WIN[N].colourback,0,12,0);
						tx+=6;
        }
				ty+=12;
		}
	
	
	
//	  num=WIN[N].zl/12*nx0;   // 便宜字节
//	  //printf(" num= %d \r\n",num);
//	  tx=WIN[N].x0;

//	  ty=WIN[N].y0+Noti_Wide-WIN[N].zl%12-1;
//    for(j=0;j<WIN[N].location;j++)
//	  {        				       					  
//				if(WIN[N].Str[num]==13){tx=WIN[N].x0;if(ty+12<WIN[N].y0+Noti_Wide+WIN[N].wide)ty+=12;}     // 回车
//				else if(WIN[N].Str[num]==10){tx=WIN[N].x0;if(ty+12<WIN[N].y0+Noti_Wide+WIN[N].wide)ty+=12;}// 换行
//				else if(WIN[N].Str[num]==9){if(tx+6<WIN[N].x0+WIN[N].lenth)tx+=6;}// 跳格
//				else if(WIN[N].Str[num]==11){if(ty+12<WIN[N].y0+Noti_Wide+WIN[N].wide)ty+=12;}// 垂直跳格
//				else 
//				{
//						if(tx+6<WIN[N].x0+WIN[N].lenth)
//						{									
//							if(ty==WIN[N].y0+Noti_Wide-WIN[N].zl%12-1)    // 第一行
//						      TFT_SwCr_0(tx,WIN[N].y0+Noti_Wide-1,WIN[N].Str[num],WIN[N].colour,WIN[N].colourback,WIN[N].zl%12,12,0); 
//							else if(ty+12>WIN[N].y0+Noti_Wide+WIN[N].wide)// 最后一行
//							    TFT_SwCr_0(tx,ty,WIN[N].Str[num],WIN[N].colour,WIN[N].colourback,0,ny1,0);
//							else TFT_SwCr_0(tx,ty,WIN[N].Str[num],WIN[N].colour,WIN[N].colourback,0,12,0);
//							tx+=6; 
//              //printf(" xy= %d %d \r\n",tx,ty);							
//						}
//						else if(ty+12<WIN[N].y0+Noti_Wide+WIN[N].wide)
//						{
//								ty+=12;tx=WIN[N].x0;							  
//								if(ty+12>WIN[N].y0+Noti_Wide+WIN[N].wide)   // 最后一行 第一个
//								    TFT_SwCr_0(tx,ty,WIN[N].Str[num],WIN[N].colour,WIN[N].colourback,0,ny1,0);
//							  else 
//									  TFT_SwCr_0(tx,ty,WIN[N].Str[num],WIN[N].colour,WIN[N].colourback,0,12,0);
//								tx+=6;			
//                //printf(" xy= %d %d \r\n",tx,ty);							
//						}							
//				} num++;      	         
//	  }
}
void Win_Str(u8 N,u8 *p)
{
	  u16 i,k,k0,k1;
	  u16 nx0,ny0,ny1;
	  for(i=0;p[i]!='\0';i++){}
			
	  nx0=WIN[N].lenth/6; // 一行的最大字符个数
	  ny0=300/nx0; // 最多行数
		if(i%nx0!=0)ny1=ny0-(i/nx0+1);
		else ny1=ny0-i/nx0;
			
    for(k=0;k<i;k++)
		{
			  if(WIN[N].zy+1>ny0) // 要覆盖移动
				{
					for(k0=0;k0<ny1;k0++)
					     for(k1=0;k1<nx0;k1++)
					         WIN[N].Str[k0*nx0+k1]=WIN[N].Str[(k0+ny0-ny1)*nx0+k1];
        }
				
			  if(p[k]==13){if(WIN[N].zy+1<ny0)WIN[N].zy+=1;}                   //   \r
				else if(p[k]==10){if(WIN[N].zy+1<ny0){WIN[N].zy+=1;WIN[N].zx=0;}}//   \n
				else if(p[k]==9){if(WIN[N].zx+1<nx0)WIN[N].zx+=1;}               //   \t
		   	else if(WIN[N].zx<nx0)  // 一行之内
				{					  
					  WIN[N].Str[WIN[N].zy*nx0+WIN[N].zx]=p[k];
					  WIN[N].zx++;
        }
				else if(WIN[N].zy+1<ny0) // 没有超过所有列的个数
				{
					  WIN[N].zx=0;
					  WIN[N].zy++;
					  if(WIN[N].zy>WIN[N].wide/12)WIN[N].zl+=12;// 辅助显示用
					  WIN[N].Str[WIN[N].zy*nx0+WIN[N].zx]=p[k];
					  WIN[N].zx++;
					 // printf("In_2 \r\n");
        }
				else  
				{
//					  for(k0=0;k0<ny1;k0++)
//					     for(k1=0;k1<nx0;k1++)
//					         WIN[N].Str[k0*nx0+k1]=WIN[N].Str[(k0+ny0-ny1)*nx0+k1];
//					  for(k0=0;k0<i;k0++)
//					     WIN[N].Str[ny1*nx0+k0]=p[k0];
        }
		}	
   // Show_Win_Str(N);
    for(k=0;k<ny0;k++)
		{
        for(i=0;i<nx0;i++)
				{
					 printf("%c",WIN[N].Str[k*nx0+i]);
				}
				printf("\r\n");
    }
//		if(WIN[N].location>=299)
//		{
//			    WIN[N].location=0;
//			    for(k=0;k<300;k++)WIN[N].Str[WIN[N].location]=' ';
//				WIN[N].location=299-i;
//				printf(" locat= %d \r\n",WIN[N].location);
//				for(k=0;k<WIN[N].location;k++) WIN[N].Str[k]=WIN[N].Str[k+i];
//			  for(k=0;k<i;k++)WIN[N].Str[k+WIN[N].location]=p[k];
//				WIN[N].location=299;			
//		}
//		else
//		{
//				for(k=0;k<i;k++)
//				{
//						
//					  if(WIN[N].location<299)
//						{
//							WIN[N].Str[WIN[N].location]=p[k];
//							WIN[N].location++;
//						}
//					  else 
//					  {
//							WIN[N].location=0;
//			        for(k=0;k<300;k++)WIN[N].Str[WIN[N].location]=' ';
//            }
//				}
//		}						
//		printf(" %d %s\r\n",WIN[N].location,WIN[N].Str);
//		Show_Win_Str(N);
}
void Win_Str_0(u16 x0,u16 y0,u16 lenth,u16 wide,u8 *p,u8 N)
{
	  u16 i,j;
	  static u16 x=10,y=56;
	  for(i=0;p[i]!='\0';i++);
	
	  //x=x0;y=y0;
	  for(j=0;j<i;j++)
	  {
			  if(p[j]==13){if(y+12<y0+wide){y+=12;} }            //   \r
				else if(p[j]==10){if(y+12<y0+wide){y+=12;x=x0;} }  //   \n
				else if(p[j]==9){if(x+6<x0+lenth)x+=6;}            //   \t
				else 
        {
					if(x+6<x0+lenth )// x方向限制
					{						
						TFT_SwCr_0(x,y,p[j],0x0,0xffff,0,12,1);
						x+=6;
					}
					else if(y+12<y0+wide)// y方向限制
					{
            y+=12;x=10;
						TFT_SwCr_0(x,y,p[j],0x0,0xffff,0,12,1);
						x+=6;
          }else {}
				}
		    //printf(" 20 x=%d y=%d %c\r\n",x,y,p[j]);		  
    }
}


