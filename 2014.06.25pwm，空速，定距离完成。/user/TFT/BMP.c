/*

    BMP 的合成 和 显示

*/
#include "BMP.h"
#include "delay.h"


FIL f_bfile;
u8 bmpreadbuf[2048];
UINT bw;			//读写变量

//BMP编码函数
//将当前LCD屏幕的指定区域截图,存为16位格式的BMP文件 RGB565格式.
//保存为rgb565则需要掩码,需要利用原来的调色板位置增加掩码.这里我们已经增加了掩码.
//保存为rgb555格式则需要颜色转换,耗时间比较久,所以保存为565是最快速的办法.
//filename:存放路径
//x,y:在屏幕上的起始坐标  
//mode:模式.0,仅仅创建新文件的方式编码;1,如果之前存在文件,则覆盖之前的文件.如果没有,则创建新的文件.
//返回值:0,成功;其他,错误码.  
u8 bmp_encode(u8 *filename,u16 x,u16 y,u16 width,u16 height,u8 mode)
{				
	FATFS fs;
	FIL* f_bmp;
	u16 bmpheadsize;			//bmp头大小	   	
 	BITMAPINFO hbmp;			//bmp头	 
	u8 res=0;
	u16 tx,ty;				   	//图像尺寸
	u16 *databuf;				//数据缓存区地址	   	
	u16 pixcnt;				   	//像素计数器
	u16 bi4width;		       	//水平像素字节数	   
 	 
  f_mount(0, &fs);
	databuf=(u16*)bmpreadbuf;
	f_bmp=&f_bfile;
	      
	bmpheadsize=sizeof(hbmp);//得到bmp文件头的大小   
	//mymemset((u8*)&hbmp,0,sizeof(hbmp));//置零空申请到的内存.	    
	hbmp.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);//信息头大小
	hbmp.bmiHeader.biWidth=width;	 	//bmp的宽度
	hbmp.bmiHeader.biHeight=height; 	//bmp的高度
	hbmp.bmiHeader.biPlanes=1;	 		//恒为1
	hbmp.bmiHeader.biBitCount=16;	 	//bmp为16位色bmp
	hbmp.bmiHeader.biCompression=BI_BITFIELDS;//每个象素的比特由指定的掩码决定。
 	hbmp.bmiHeader.biSizeImage=hbmp.bmiHeader.biHeight*hbmp.bmiHeader.biWidth*hbmp.bmiHeader.biBitCount/8;//bmp数据区大小
 				   
	hbmp.bmfHeader.bfType=((u16)'M'<<8)+'B';//BM格式标志
	hbmp.bmfHeader.bfSize=bmpheadsize+hbmp.bmiHeader.biSizeImage;//整个bmp的大小
   	hbmp.bmfHeader.bfOffBits=bmpheadsize;//到数据区的偏移

	hbmp.RGB_MASK[0]=0X00F800;	 		//红色掩码
	hbmp.RGB_MASK[1]=0X0007E0;	 		//绿色掩码
	hbmp.RGB_MASK[2]=0X00001F;	 		//蓝色掩码

	if(mode==1)res=f_open(f_bmp,(const TCHAR*)filename,FA_READ|FA_WRITE);//尝试打开之前的文件
 	if(mode==0||res==0x04)res=f_open(f_bmp,(const TCHAR*)filename,FA_WRITE|FA_CREATE_NEW);//模式0,或者尝试打开失败,则创建新文件		   
 	if((hbmp.bmiHeader.biWidth*2)%4)//水平像素(字节)不为4的倍数
	{
		bi4width=((hbmp.bmiHeader.biWidth*2)/4+1)*4;//实际要写入的宽度像素,必须为4的倍数.	
	}else bi4width=hbmp.bmiHeader.biWidth*2;		//刚好为4的倍数	 
 	if(res==FR_OK)//创建成功
	{
		res=f_write(f_bmp,(u8*)&hbmp,bmpheadsize,&bw);//写入BMP首部  
		for(ty=y+height-1;hbmp.bmiHeader.biHeight;ty--)
		{
			pixcnt=0;
 			for(tx=x;pixcnt!=(bi4width/2);)
			{
				if(pixcnt<hbmp.bmiHeader.biWidth)databuf[pixcnt]=TFT_GetPoint(tx,ty);//读取坐标点的值 
				else databuf[pixcnt]=0Xffff;//补充白色的像素.  
				pixcnt++;
				tx++;
			}
			hbmp.bmiHeader.biHeight--;
			res=f_write(f_bmp,(u8*)databuf,bi4width,&bw);//写入数据
		}
		f_close(f_bmp);
	}	    	
	return res;
}

//24位。。变成16位图 
u32 RGB888ToRGB565(u8 r,u8 g,u8 b)
 {return (u32) (r & 0xF8) << 8 | (g & 0xFC) << 3 | (b & 0xF8) >> 3;}	//565
 /* 对24位色的BMP图像有效 */
 #define Maxt_Num 510  //每一次读取固定长度的数据，为了保证可靠性  更改这个数据可以改变速度
u8 TFT_Show_BMP(u16 x,u16 y,u8 *name)
{
		FATFS fs;
		FIL fsrc;
		FRESULT res;
		UINT br;
		BMP_HEAD bmp;
		u16 i,j;
		u32 k;
	
	  f_mount(0, &fs);
	 
	  res = f_open(&fsrc,(const TCHAR*)name, FA_OPEN_EXISTING | FA_READ);	//if(!res)printf(" Open_OK \r\n"); //打上图片文件名
		res = f_read(&fsrc, &bmp, sizeof(bmp), &br);
	
		if((bmp.pic_head[0]=='B')&&(bmp.pic_head[1]=='M'))
		{
			res = f_lseek(&fsrc, ((bmp.pic_data_address_h<<16)| bmp.pic_data_address_l));
			k=0; f_read(&fsrc, bmpreadbuf,Maxt_Num,&br);
			for(i=0;i<bmp.pic_h_l;i++)
			{		  
				  TFT_Window(x,bmp.pic_h_l+y-i ,bmp.pic_w_l,1);  // 开一个窗口
				  for(j=0;j<bmp.pic_w_l;j++)
				  {
						 LCD_WR_Data((bmpreadbuf[k+2]&0xF8)<<8|(bmpreadbuf[k+1]&0xFC)<<3|(bmpreadbuf[k+0]&0xF8)>>3); // 写颜色数据
						 if(k>=Maxt_Num-3)// 如果是小图片的话 这个方式显示的效率很高
						 {
							 k=0; f_read(&fsrc, bmpreadbuf,Maxt_Num,&br);
             } else k+=3;
          }
      }	
			f_close(&fsrc);	
		}
		return res;
}
u8 TFT_S_I_BMP(u16 x,u16 y,u8 *name)
{
		FATFS fs;
		FIL fsrc;
		FRESULT res;
		UINT br;
		BMP_HEAD bmp;
		u16 i,j;
		u32 k;
	  u16 R,G,B;
    u16 bright = 15,RGB;
	
	  f_mount(0, &fs);
	 
	  res = f_open(&fsrc,(const TCHAR*)name, FA_OPEN_EXISTING | FA_READ);	//if(!res)printf(" Open_OK \r\n"); //打上图片文件名
		res = f_read(&fsrc, &bmp, sizeof(bmp), &br);
	
		if((bmp.pic_head[0]=='B')&&(bmp.pic_head[1]=='M'))
		{
			res = f_lseek(&fsrc, ((bmp.pic_data_address_h<<16)| bmp.pic_data_address_l));
			k=0; f_read(&fsrc, bmpreadbuf,Maxt_Num,&br);
			for(i=0;i<bmp.pic_h_l;i++)
			{		  
				  TFT_Window(x,bmp.pic_h_l+y-i,bmp.pic_w_l,1);  // 开一个窗口
				  for(j=0;j<bmp.pic_w_l;j++)
				  {
						RGB=(bmpreadbuf[k+2]&0xF8)<<8|(bmpreadbuf[k+1]&0xFC)<<3|(bmpreadbuf[k+0]&0xF8)>>3;
						R = (RGB & 0xF800) >> 11;
						G = (RGB & 0x07E0) >> 5;
						B =  RGB & 0x001F;
						if (R > bright){R -= bright;}else{R = 0;}
						if (G > 2 * bright){G -= 2 * bright;}else{G = 0;}
						if (B > bright){B -= bright;}else{B = 0;}
						LCD_WR_Data((R<<11)+(G<<5)+B); // 写颜色数据
						
						 if(k>=Maxt_Num-3)// 如果是小图片的话 这个方式显示的效率很高
						 {
							 k=0; f_read(&fsrc, bmpreadbuf,Maxt_Num,&br);
             } else k+=3;
          }
      }	
			f_close(&fsrc);	
		}
		return res;
}



