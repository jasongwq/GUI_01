界面1





window[10]
Button[10]
Button_Properties[10]
GUI_EVENT
{

}
int func(int x); /* 声明一个函数 */
int (*f) (int x); /* 声明一个函数指针 */

Button_Event()
{

}

Window window1;
window1.Set_BackColor(10);
Button Button1;
window1.add_button(Button1);
Button1.Set_Rect(10, 40, 105, 130);
Button1.Set_Text("Ce_Shi001");
Button1.Set_Event(Button1_Event);
creat_window(2);
window.Set_BackColor(20);
window.Button.Set_Rect(10, 40, 105, 130);
window.Button.Set_Text("Ce_Shi011");
window.Button.Set_Event("Ce_Shi012");



//刷新窗口
Refresh_window();
{
	window1.draw();
	Button1.draw();
}
set_current_window();
Refresh_Back(1);//刷新背景
{
    //填充颜色
}
//刷新控件
Refresh_Button();//刷新按钮如果有的话
{
    EV = event_detection(); //事件检测
    if (EV == click)
    {
        set_current_window(2);
    }
}
EV event_detection(void)
{
    return EV;
}
Set_Rect()
{

}
MINI_GUI
{
    current_window
    redraw
}
//矩形
class Rect //以class开头
{
    u16 Bounds[2];//左坐标上坐标
    u16 Size[];
    u16 BackColor;
    u8 *BackgroundImage;
    void draw() //这是成员函数
    {

    }
};
class text //以class开头
{
    u8 *ptext;
    u8 Color;
    void Set_Text(u8 *text) //这是成员函数
    {
    	ptext=text;
    }
};
//窗口属性
class Window: public Rect
{
    u8 Winreturn;
    u8 add_button()
    {

    }
};

class Button: public Rect
{
    u8 *text
    u8 Key;
};

