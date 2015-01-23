界面1





window[10]
Button[10]
Button_Properties[10]
GUI_EVENT
{

}

creat_window(1);
Creat_Button(10, 40, 105, 130, 0x1111, "Ce_Shi", 0x4774, "In 1", window[0]);

//刷新窗口
Refresh_window(1);
set_current_window();
Refresh_Back(1);//刷新背景
{
	//填充颜色
}
//刷新控件
Refresh_Button();//刷新按钮如果有的话
{
    EV = event_detection() //事件检测
    if (EV == click)
    {
        set_current_window(2);
    }
}
EV event_detection(void)
{

	return EV;
}




MINI_GUI
{
    current_window
    redraw
}
窗口属性
window_Properties
WINDOW_PROPERTIES
{
    BackColor
    BackgroundImage
    Size
    Winreturn
}
控件属性
按钮属性
Button_Properties
BUTTON_PROPERTIES
{
    BackColor
    ForeColor
    BackgroundImage
    Size
    Key
    Bounds
}

