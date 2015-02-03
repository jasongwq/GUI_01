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
    void SetBackColor(u16 color)
    {
        BackColor = color;
    }
    void SetRect(u16 x, u16 y, u16 w, u16 h)
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
    u8 color;
    Font *User_Font;
public:
    const char *ptext;
    Size textsize;//12/16
    Text()
    {
        textsize.w = 0;
        color = BLACK;
        User_Font = &User_Font_simsun_16x16;
    }
    void SetText(const char *text) //这是成员函数
    {
        textsize.w = 0;
        ptext = text;
        while (*text != 0)
        {
            text++;
            textsize.w++;
        }
        //Sys_Printf(Printf_USART, (char *)"textsize.w:%d", textsize.w);
        textsize.w = textsize.w / 2;
        textsize.w *= User_Font->fontsize;
        textsize.h = User_Font->fontsize;
    }
    Size GetSize() //这是成员函数
    {
        return textsize;
    }
    void SetFont(Font *font) //这是成员函数
    {
        User_Font = font;
    }
    void SetColor(u16 col) //这是成员函数
    {
        color = col;
    }
    u16 GetColor() //这是成员函数
    {
        return color;
    }
    void Refresh(u16 x, u16 y, u16 width, u16 height)
    {
        Show_Str(x, y, width, height, (u8 *)ptext, User_Font, 1, color);
    }
};

typedef int (*pFunEvent)(Event x); //声明一个函数指针
#define tp_button(x1,y1,x2,y2) (\
                                ((tp_dev.x >x1) && (tp_dev.x < x2))\
                                && \
                                ((tp_dev.y > y1) && (tp_dev.y < y2))\
                               )
class Button: public Rect
{
private:
    u8 Key;
    pFunEvent pEvent;
    Event event;
public:
    Text text;
    Button()
    {
        event = null;
    }
    void Refresh(void)
    {
        Button::draw();
        if (text.GetSize().w < size.w)
            text.Refresh((size.w - text.GetSize().w) / 2 + Bounds.x, (size.h - text.GetSize().h) / 2 + Bounds.y,
                         strlen((char *)text.ptext)*text.textsize.w, text.textsize.h);
        else
            text.Refresh((size.w - text.GetSize().w) / 2 + Bounds.x, (size.h - text.GetSize().h) / 2 + Bounds.y,
                         strlen((char *)text.ptext)*text.textsize.w, text.textsize.h);
    }
    void SetEvent(pFunEvent pf)
    {
        pEvent = pf;
    }
    void EventDetection(void)
    {
        if (tp_dev.sta & TP_PRES_DOWN)
        {
            if (tp_button(Bounds.x, Bounds.y, Bounds.x + size.w, Bounds.y + size.h))
                event = press;
            else
            {
                event = null;
            }
        }
        else if (event == press)
            event = release;
        else
            event = null;
        (*pEvent)(event);
    }
};
class SwitchButton: public Button
{
private:
    u8 OnOff;
    const char *str1;
    const char *str2;
    u16 color1;
    u16 color2;
public:
    SwitchButton(const char *s1, const char *s2, u16 c1 , u16 c2)
    {
        OnOff = 0;
        str1 = s1;
        str2 = s2;
        color1 = c1;
        color2 = c2;
    }
    void SetOn(void)
    {
        OnOff = 1;
    }
    void SetOff(void)
    {
        OnOff = 0;
    }
    u8 GetOnoff(void)
    {
        return OnOff;
    }
    void Refresh(void)
    {
        if (OnOff)
        {
            text.SetText(str1);
            SwitchButton::SetBackColor(color1);
        }
        else
        {
            text.SetText(str2);
            SwitchButton::SetBackColor(color2);
        }

        Button::Refresh();
    }
};


//窗口属性
class Window: public Rect
{
private:
    u8 Winreturn;
    Button **pButton;
    SwitchButton **pSwitchButton;
    u8 Obj_count[2];
    u8 name;
public:
    Window(u8 n,Button *pB[],SwitchButton *pS[])
    {
        Obj_count[0] = 0;
        Obj_count[1] = 0;
        pButton=pB;
        pSwitchButton=pS;
        name = n;
    }
    void AddButton(Button *pB)
    {
        pButton[Obj_count[0]++] = pB;
    }
    void AddButton(SwitchButton *pB)
    {
        pSwitchButton[Obj_count[1]++] = pB;
    }
    void Refresh(void);
    void EventDetection(void);
};
class MiniGui
{
private:
    Window *pwindow_list[10];
    u8 window_count;
public:
    u8 current_window;
    MiniGui()
    {
        window_count = 0;
        current_window = 0;
    }
    void AddWindow(Window *win)
    {
        pwindow_list[window_count++] = win;
    }
    void EventDetection(void)
    {
        pwindow_list[current_window]->EventDetection();
    }
};

extern MiniGui ui;
#endif
