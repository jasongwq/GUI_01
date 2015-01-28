#include "string.h"
#include "sys.h"
#include "../../GLIB/PERIPHERAL/LCD/LCD.h"
#include "../../GLIB/PERIPHERAL/LCD/touch.h"
#include "font_User.h"
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
public:
    char *ptext;
    u8 textsize;//12/16
    Text()
    {
        textsize = 16;
        Color = BLACK;
    }
    void Set_Text(char *text) //这是成员函数
    {
        ptext = text;
    }
    void Set_Size(u8 s) //这是成员函数
    {
        textsize = s;
    }
    void Refresh(u16 x, u16 y, u16 width, u16 height)
    {
       // LCD_ShowxString(x, y, width, height, textsize, (char *)ptext, 1);
			  Show_Str(x, y, width, height,(u8 *)ptext,&User_Font_simsun_16x16,1);
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
public:
    Rect rect;
    Text text;
    void Refresh()
    {
        rect.draw();
        text.Refresh(rect.Bounds.x, rect.Bounds.y, strlen((char *)text.ptext)*text.textsize, text.textsize);
    }
    void Set_Event(pFun_Event pf)
    {
        pEvent = pf;
    }
    void event_detection(void)
    {
        Event event;
        if (tp_button(rect.Bounds.x, rect.Bounds.y, rect.Bounds.x + rect.size.w, rect.Bounds.y + rect.size.h))
            event = press;
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
