#include "../../GLIB/ALGORITHM/binary_chop.h"
#include "font_user.h"
#include "lcd.h"
#include "usr_usart.h"
#include "minos_delay.h"
#include "font_Mat.h"
int cmp(const void *p1, const void *p2)
{
  return *(u16*)p1-*(u16*)p2;
}
u8* Get_UserMat(unsigned char *code,Font *User_Font)
{
		u16 ucode=((u16)(*code)<<8);
	  void **p=(void *)(User_Font->mat);
	  ucode+=*(++code);
	  int offset=0;
	  offset=binary_chop(User_Font->GBK_code,User_Font->codesize/2,2,&ucode,&cmp);
	if(offset<0)offset=0;
	//		int x=(int)(sizeof((User_Font->GBK_code)));
	//	int y=(int)(sizeof(User_Font->GBK_code[0]));
	//	Sys_Printf(USART1, (char *)"\r\n %d %d %d",sizeof(GBK_code_simsun_16x16),ucode,offset);
		//delay_ms(100);
		return p[offset];
}
//显示一个指定大小的汉字
//x,y :汉字的坐标
//font:汉字GBK码
//size:字体大小
//mode:0,正常显示,1,叠加显示
void Show_Font(u16 x, u16 y, u8* font,Font *User_Font, u8 mode,u16 color)
{
    u8 temp, t, t1;
	  u16 x0 = x;
    u8 *dzk;
    //u16 tempcolor;
	  dzk =Get_UserMat(font,User_Font);
    if (mode == 0) //正常显示
    {
        for (t = 0; t < User_Font->fontsize * 2; t++)
        {
            temp = dzk[t]; //得到12数据
            for (t1 = 0; t1 < 8; t1++)
            {
                if (temp & 0x80)LCD_Fast_DrawPoint(x, y,color);
                else
                {
									LCD_Fast_DrawPoint(x, y,BACK_COLOR);
                }
                temp <<= 1;
							  x++;
                if ((x - x0) == User_Font->fontsize)
                {
                    x = x0;
                    y++;
                    break;
                }
            }
        }
    }
    else //叠加显示
    {
        for (t = 0; t < User_Font->fontsize * 2; t++)
        {
            temp = dzk[t]; //得到12数据
            for (t1 = 0; t1 < 8; t1++)
            {
                if (temp & 0x80)LCD_Fast_DrawPoint(x, y,color);
                temp <<= 1;
                x++;
                if ((x - x0) == User_Font->fontsize)
                {
                    x = x0;
                    y++;
                    break;
                }
            }
        }
    }
}
void Show_Str(u16 x, u16 y, u16 width, u16 height, u8 * str,Font *User_Font, u8 mode,u16 color)
{
    u16 x0 = x;
    u16 y0 = y;
    u8 bHz = 0;   //字符或者中文
    while (*str != 0) //数据未结束
    {
        if (!bHz)
        {
            if (*str > 0x80)bHz = 1; //中文
            else              //字符
            {
                if (x > (x0 + width - User_Font->fontsize / 2)) //换行
                {
                    y += User_Font->fontsize;
                    x = x0;
                }
                if (y > (y0 + height - User_Font->fontsize))break; //越界返回
                if (*str == 13) //换行符号
                {
                    y += User_Font->fontsize;
                    x = x0;
                    str++;
                }
                else LCD_ShowChar(x, y, *str, User_Font->fontsize, mode); //有效部分写入
                str++;
                x += User_Font->fontsize / 2; //字符,为全字的一半
            }
        }
        else //中文
        {
            bHz = 0; //有汉字库
            if (x > (x0 + width - User_Font->fontsize)) //换行
            {
                y += User_Font->fontsize;
                x = x0;
            }
            if (y > (y0 + height - User_Font->fontsize))break; //越界返回
            Show_Font(x, y, (u8*)str, User_Font, mode,color); //显示这个汉字,空心显示
            str += 2;
            x += User_Font->fontsize; //下一个汉字偏移
        }
    }
}
