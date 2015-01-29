#include "string.h"
#include "sys.h"
#include "../../GLIB/PERIPHERAL/LCD/LCD.h"
#include "../../GLIB/PERIPHERAL/LCD/touch.h"
#include "font_User.h"
#include "usr_usart.h"
#ifndef __UI_H
#define __UI_H

enum Event {press, click, release, null};
class Point
{
public:
    u16 x;
    u16 y;
};
class Size
{
public:
    u16 w;
    u16 h;
};
//矩形
class Rect //以class开头
{
private:
public:
    u16 BackColor;
    u8 *BackgroundImage;
    Point Bounds;//左坐标上坐标
    Size size;
    Rect()
    {
        Bounds.x = 0;
        Bounds.y = 0;
        size.w = 240;
        size.h = 320;
        BackColor = BLUE;
    }
    void draw() //这是成员函数
    {
        LCD_Fill(Bounds.x, Bounds.y, Bounds.x + size.w, Bounds.y + size.h, BackColor);
    }
    void Set_BackColor(u16 color)
    {
        BackColor = color;
    }
    void Set_Rect(u16 x, u16 y, u16 w, u16 h)
    {
        Bounds.x = x;
        Bounds.y = y;
        size.w = w;
        size.h = h;
    }
};
class Text //以class开头
{
private:
    u8 Color;
    Font *User_Font;
public:
    char *ptext;
    Size textsize;//12/16
    Text()
    {
     textsize.w = 0;   
        Color = BLACK;
			  User_Font=&User_Font_simsun_16x16;
    }
    void Set_Text(char *text) //这是成员函数
    {
			  textsize.w = 0;
        ptext = text;
				while (*text != 0)
				{
					text++;
					textsize.w++;
				}
				Sys_Printf(Printf_USART, (char *)"textsize.w:%d",textsize.w);
				textsize.w=textsize.w/2;
				//textsize.w=4;
				textsize.w*=User_Font->fontsize;
				textsize.h=User_Font->fontsize;
    }
    Size Get_Size() //这是成员函数
    {
        return textsize;
    }
		void Set_Font(Font* font) //这是成员函数
    {
        User_Font = font;
    }
    void Refresh(u16 x, u16 y, u16 width, u16 height)
    {
			  Show_Str(x, y, width, height,(u8 *)ptext,User_Font,1);
    }
};

typedef int (*pFun_Event)(Event x); //声明一个函数指针
#define tp_button(x1,y1,x2,y2) (\
                                ((tp_dev.x >x1) && (tp_dev.x < x2))\
                                && \
                                ((tp_dev.y > y1) && (tp_dev.y < y2))\
                               )
class Button
{
private:
    u8 Key;
    pFun_Event pEvent;
		Event event;
public:
    Rect rect;
    Text text;
Button()
{
	event=null;
}

    void Refresh()
    {
        rect.draw();
			if(text.Get_Size().w<rect.size.w)
        text.Refresh((rect.size.w-text.Get_Size().w)/2+rect.Bounds.x,(rect.size.h-text.Get_Size().h)/2+rect.Bounds.y, 
							strlen((char *)text.ptext)*text.textsize.w,text.textsize.h);    
			else
				text.Refresh((rect.size.w-text.Get_Size().w)/2+rect.Bounds.x,(rect.size.h-text.Get_Size().h)/2+rect.Bounds.y, 
							strlen((char *)text.ptext)*text.textsize.w,text.textsize.h);    
		}
    void Set_Event(pFun_Event pf)
    {
        pEvent = pf;
    }
    void event_detection(void)
    {
			if (tp_dev.sta & TP_PRES_DOWN)
    {
        if (tp_button(rect.Bounds.x, rect.Bounds.y, rect.Bounds.x + rect.size.w, rect.Bounds.y + rect.size.h))
            event = press;
        else
				{
						event = null;
				}
        
			}
		else
			if(event == press)
						event =release;
					else
						event = null;
		(*pEvent)(event);
    }
		
};

//窗口属性
class Window: public Rect
{
private:
    u8 Winreturn;
    Button *pButton[10];
    u8 Button_count;
    u8 name;
public:
    Window(u8 n)
    {
        Button_count = 0;
        name = n;
    }
    void add_button(Button *pB)
    {
        pButton[Button_count++] = pB;
    }
    void Refresh(void);
    void event_detection(void);

};
class MINI_GUI
{
private:
    Window *pwindow_list[10];
    u8 Window_count;
public:
    u8 current_window;
    MINI_GUI()
    {
        Window_count = 0;
        current_window=0;
    }
    void add_window(Window *win)
    {
        pwindow_list[Window_count++] = win;
    }
		void event_detection(void)
    {
        pwindow_list[current_window]->event_detection();
    }
    //redraw
};

extern MINI_GUI ui;
#endif
