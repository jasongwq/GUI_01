/*

    BMP �ĺϳ� �� ��ʾ

*/
#include "BMP.h"
#include "delay.h"


FIL f_bfile;
u8 bmpreadbuf[2048];
UINT bw;			//��д����

//BMP���뺯��
//����ǰLCD��Ļ��ָ�������ͼ,��Ϊ16λ��ʽ��BMP�ļ� RGB565��ʽ.
//����Ϊrgb565����Ҫ����,��Ҫ����ԭ���ĵ�ɫ��λ����������.���������Ѿ�����������.
//����Ϊrgb555��ʽ����Ҫ��ɫת��,��ʱ��ȽϾ�,���Ա���Ϊ565������ٵİ취.
//filename:���·��
//x,y:����Ļ�ϵ���ʼ����  
//mode:ģʽ.0,�����������ļ��ķ�ʽ����;1,���֮ǰ�����ļ�,�򸲸�֮ǰ���ļ�.���û��,�򴴽��µ��ļ�.
//����ֵ:0,�ɹ�;����,������.  
u8 bmp_encode(u8 *filename,u16 x,u16 y,u16 width,u16 height,u8 mode)
{				
	FATFS fs;
	FIL* f_bmp;
	u16 bmpheadsize;			//bmpͷ��С	   	
 	BITMAPINFO hbmp;			//bmpͷ	 
	u8 res=0;
	u16 tx,ty;				   	//ͼ��ߴ�
	u16 *databuf;				//���ݻ�������ַ	   	
	u16 pixcnt;				   	//���ؼ�����
	u16 bi4width;		       	//ˮƽ�����ֽ���	   
 	 
  f_mount(0, &fs);
	databuf=(u16*)bmpreadbuf;
	f_bmp=&f_bfile;
	      
	bmpheadsize=sizeof(hbmp);//�õ�bmp�ļ�ͷ�Ĵ�С   
	//mymemset((u8*)&hbmp,0,sizeof(hbmp));//��������뵽���ڴ�.	    
	hbmp.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);//��Ϣͷ��С
	hbmp.bmiHeader.biWidth=width;	 	//bmp�Ŀ��
	hbmp.bmiHeader.biHeight=height; 	//bmp�ĸ߶�
	hbmp.bmiHeader.biPlanes=1;	 		//��Ϊ1
	hbmp.bmiHeader.biBitCount=16;	 	//bmpΪ16λɫbmp
	hbmp.bmiHeader.biCompression=BI_BITFIELDS;//ÿ�����صı�����ָ�������������
 	hbmp.bmiHeader.biSizeImage=hbmp.bmiHeader.biHeight*hbmp.bmiHeader.biWidth*hbmp.bmiHeader.biBitCount/8;//bmp��������С
 				   
	hbmp.bmfHeader.bfType=((u16)'M'<<8)+'B';//BM��ʽ��־
	hbmp.bmfHeader.bfSize=bmpheadsize+hbmp.bmiHeader.biSizeImage;//����bmp�Ĵ�С
   	hbmp.bmfHeader.bfOffBits=bmpheadsize;//����������ƫ��

	hbmp.RGB_MASK[0]=0X00F800;	 		//��ɫ����
	hbmp.RGB_MASK[1]=0X0007E0;	 		//��ɫ����
	hbmp.RGB_MASK[2]=0X00001F;	 		//��ɫ����

	if(mode==1)res=f_open(f_bmp,(const TCHAR*)filename,FA_READ|FA_WRITE);//���Դ�֮ǰ���ļ�
 	if(mode==0||res==0x04)res=f_open(f_bmp,(const TCHAR*)filename,FA_WRITE|FA_CREATE_NEW);//ģʽ0,���߳��Դ�ʧ��,�򴴽����ļ�		   
 	if((hbmp.bmiHeader.biWidth*2)%4)//ˮƽ����(�ֽ�)��Ϊ4�ı���
	{
		bi4width=((hbmp.bmiHeader.biWidth*2)/4+1)*4;//ʵ��Ҫд��Ŀ������,����Ϊ4�ı���.	
	}else bi4width=hbmp.bmiHeader.biWidth*2;		//�պ�Ϊ4�ı���	 
 	if(res==FR_OK)//�����ɹ�
	{
		res=f_write(f_bmp,(u8*)&hbmp,bmpheadsize,&bw);//д��BMP�ײ�  
		for(ty=y+height-1;hbmp.bmiHeader.biHeight;ty--)
		{
			pixcnt=0;
 			for(tx=x;pixcnt!=(bi4width/2);)
			{
				if(pixcnt<hbmp.bmiHeader.biWidth)databuf[pixcnt]=TFT_GetPoint(tx,ty);//��ȡ������ֵ 
				else databuf[pixcnt]=0Xffff;//�����ɫ������.  
				pixcnt++;
				tx++;
			}
			hbmp.bmiHeader.biHeight--;
			res=f_write(f_bmp,(u8*)databuf,bi4width,&bw);//д������
		}
		f_close(f_bmp);
	}	    	
	return res;
}

//24λ�������16λͼ 
u32 RGB888ToRGB565(u8 r,u8 g,u8 b)
 {return (u32) (r & 0xF8) << 8 | (g & 0xFC) << 3 | (b & 0xF8) >> 3;}	//565
 /* ��24λɫ��BMPͼ����Ч */
 #define Maxt_Num 510  //ÿһ�ζ�ȡ�̶����ȵ����ݣ�Ϊ�˱�֤�ɿ���  ����������ݿ��Ըı��ٶ�
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
	 
	  res = f_open(&fsrc,(const TCHAR*)name, FA_OPEN_EXISTING | FA_READ);	//if(!res)printf(" Open_OK \r\n"); //����ͼƬ�ļ���
		res = f_read(&fsrc, &bmp, sizeof(bmp), &br);
	
		if((bmp.pic_head[0]=='B')&&(bmp.pic_head[1]=='M'))
		{
			res = f_lseek(&fsrc, ((bmp.pic_data_address_h<<16)| bmp.pic_data_address_l));
			k=0; f_read(&fsrc, bmpreadbuf,Maxt_Num,&br);
			for(i=0;i<bmp.pic_h_l;i++)
			{		  
				  TFT_Window(x,bmp.pic_h_l+y-i ,bmp.pic_w_l,1);  // ��һ������
				  for(j=0;j<bmp.pic_w_l;j++)
				  {
						 LCD_WR_Data((bmpreadbuf[k+2]&0xF8)<<8|(bmpreadbuf[k+1]&0xFC)<<3|(bmpreadbuf[k+0]&0xF8)>>3); // д��ɫ����
						 if(k>=Maxt_Num-3)// �����СͼƬ�Ļ� �����ʽ��ʾ��Ч�ʺܸ�
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
	 
	  res = f_open(&fsrc,(const TCHAR*)name, FA_OPEN_EXISTING | FA_READ);	//if(!res)printf(" Open_OK \r\n"); //����ͼƬ�ļ���
		res = f_read(&fsrc, &bmp, sizeof(bmp), &br);
	
		if((bmp.pic_head[0]=='B')&&(bmp.pic_head[1]=='M'))
		{
			res = f_lseek(&fsrc, ((bmp.pic_data_address_h<<16)| bmp.pic_data_address_l));
			k=0; f_read(&fsrc, bmpreadbuf,Maxt_Num,&br);
			for(i=0;i<bmp.pic_h_l;i++)
			{		  
				  TFT_Window(x,bmp.pic_h_l+y-i,bmp.pic_w_l,1);  // ��һ������
				  for(j=0;j<bmp.pic_w_l;j++)
				  {
						RGB=(bmpreadbuf[k+2]&0xF8)<<8|(bmpreadbuf[k+1]&0xFC)<<3|(bmpreadbuf[k+0]&0xF8)>>3;
						R = (RGB & 0xF800) >> 11;
						G = (RGB & 0x07E0) >> 5;
						B =  RGB & 0x001F;
						if (R > bright){R -= bright;}else{R = 0;}
						if (G > 2 * bright){G -= 2 * bright;}else{G = 0;}
						if (B > bright){B -= bright;}else{B = 0;}
						LCD_WR_Data((R<<11)+(G<<5)+B); // д��ɫ����
						
						 if(k>=Maxt_Num-3)// �����СͼƬ�Ļ� �����ʽ��ʾ��Ч�ʺܸ�
						 {
							 k=0; f_read(&fsrc, bmpreadbuf,Maxt_Num,&br);
             } else k+=3;
          }
      }	
			f_close(&fsrc);	
		}
		return res;
}



