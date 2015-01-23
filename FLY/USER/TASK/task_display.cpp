#include "./TASK/task.h"
#include "../../GLIB/PERIPHERAL/LCD/LCD.h"
#include "../../GLIB/PERIPHERAL/LCD/touch.h"
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif
/*
    需要包含
    lcd.c
    ili93.c
    touch.c
    */
/*
界面1
window[10]
Button[10]
Button_Properties[10]
GUI_EVENT
{

}
//int func(int x); //声明一个函数
*/




#include "string.h"
enum  Event {press, click, release, null};
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
        LCD_ShowxString(x, y, width, height, textsize, (char *)ptext, 1);
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
    Button *pButton[5];
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
    Window *pwindow_list[5];
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
    //redraw
};
MINI_GUI ui;
void Window::event_detection(void)
{
    tp_dev.scan(0);
    if (tp_dev.sta & TP_PRES_DOWN)
    {
        if (tp_dev.x < lcddev.width && tp_dev.y < lcddev.height&&ui.current_window==name)
        {
            for (int i = 0; i < Button_count; ++i)
            {
                pButton[i]->event_detection();
            }
        }
    }
}
void Window::Refresh(void)
{
    Window::draw();
    for (int i = 0; i < Button_count; ++i)
    {
        pButton[i]->Refresh();
    }
    ui.current_window = name;
}
Window window1(1);
Button Button1;
Button Button2;
Button Button3;
Button Button4;
Window window2(2);
Window window3(3);
Window window4(4);
Window window5(5);
int Button1_Event(Event event)
{
    if (event == press)
    {
        window2.Refresh();
    }
    return 0;
}
int Button2_Event(Event event)
{
    if (event == press)
    {
        window3.Refresh();
    }
    return 0;
}
int Button3_Event(Event event)
{
    if (event == press)
    {
        window4.Refresh();
    }
    return 0;
}
//TP_TestAdjust();
//LCD_Test();
int task_display(void)
{
    _SS
    WaitX(20);
    LCD_Init();
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    TP_Init();

    ui.add_window(&window1);
    window1.Set_BackColor(10);
    window1.Set_Rect(10, 10, 220, 300);
    window1.add_button(&Button1);
    Button1.rect.Set_Rect(10, 40, 105, 130);
    Button1.text.Set_Text((char *)"Ce_Shi001");
    Button1.Set_Event(&Button1_Event);

    window2.Set_BackColor(BRED);
    window2.Set_Rect(5, 5, 230, 310);
    window1.Refresh();
    //    WaitX(1000);
    //    LCD_Clear(WHITE);
    //    window2.Refresh();
    //    WaitX(1000);
    //    LCD_Clear(WHITE);
    //    window1.Refresh();

    //Refresh_window()
    //
    //
    while (1)
    {
        WaitX(10);
        window1.event_detection();
        //tp_dev.scan(0);
        TP_Draw_Big_Point(tp_dev.x, tp_dev.y, RED);
    }
    _EE
}


