#include "UI.h"
Window window0(0);
Button Button0_1;
Button Button0_2;
Button Button0_3;
Button Button0_4;
Button Button0_5;
Button Button0_6;
Window window1(1);
Button Button1_1;
Button Button1_2;
Button Button1_3;
Window window2(2);
Button Button2_1;
Button Button2_2;
Button Button2_3;
Button Button2_4;
Button Button2_5;
Window window3(3);
Button Button3_1;
SwitchButton SwitchButton3_1("on","off");
Window window4(4);
Button Button4_1;
Window window5(5);
Button Button5_1;
Window window6(6);
Button Button6_1;
Window window7(7);
Button Button7_1;
int Button0_1_Event(Event event){if (event == release){window1.Refresh();}return 0;}
int Button0_2_Event(Event event){if (event == release){window2.Refresh();}return 0;}
int Button0_3_Event(Event event){if (event == release){window4.Refresh();}return 0;}
int Button0_4_Event(Event event){if (event == release){window6.Refresh();}return 0;}
int Button0_5_Event(Event event){if (event == release){window5.Refresh();}return 0;}
int Button0_6_Event(Event event){if (event == release){window3.Refresh();}return 0;}
int Button1_1_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button1_2_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button1_3_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button2_1_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button2_2_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button2_3_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button2_4_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button2_5_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button3_1_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int SwitchButton3_1_Event(Event event){if (event == release){
if(SwitchButton3_1.GetOnoff())
	SwitchButton3_1.SetOff();
else
	SwitchButton3_1.SetOn();
SwitchButton3_1.Refresh();	
}return 0;}
int Button4_1_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button5_1_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button6_1_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button7_1_Event(Event event){if (event == release){window0.Refresh();}return 0;}
void UI_Init(void){
ui.AddWindow(&window0);
window0.SetBackColor(0xfe38);
window0.SetRect(0,0,240,320);
window0.AddButton(&Button0_1);
Button0_1.SetRect(20,20,80,80);
Button0_1.SetBackColor(0xffff);
Button0_1.text.SetText("波段选择");
Button0_1.SetEvent(&Button0_1_Event);
window0.AddButton(&Button0_2);
Button0_2.SetRect(140,20,80,80);
Button0_2.SetBackColor(0xffff);
Button0_2.text.SetText("电文加载");
Button0_2.SetEvent(&Button0_2_Event);
window0.AddButton(&Button0_3);
Button0_3.SetRect(140,120,80,80);
Button0_3.SetBackColor(0xffff);
Button0_3.text.SetText("状态查询");
Button0_3.SetEvent(&Button0_3_Event);
window0.AddButton(&Button0_4);
Button0_4.SetRect(140,220,80,80);
Button0_4.SetBackColor(0xffff);
Button0_4.text.SetText("输出功率");
Button0_4.SetEvent(&Button0_4_Event);
window0.AddButton(&Button0_5);
Button0_5.SetRect(20,220,80,80);
Button0_5.SetBackColor(0xffff);
Button0_5.text.SetText("多普勒频移");
Button0_5.SetEvent(&Button0_5_Event);
window0.AddButton(&Button0_6);
Button0_6.SetRect(20,120,80,80);
Button0_6.SetBackColor(0xffff);
Button0_6.text.SetText("伪码选择");
Button0_6.SetEvent(&Button0_6_Event);
ui.AddWindow(&window1);
window1.SetBackColor(0x7b7f);
window1.SetRect(0,0,240,320);
window1.AddButton(&Button1_1);
Button1_1.SetRect(0,0,240,20);
Button1_1.SetBackColor(0xffff);
Button1_1.text.SetText("返回 波段选择");
Button1_1.SetEvent(&Button1_1_Event);
window1.AddButton(&Button1_2);
Button1_2.SetRect(10,100,100,100);
Button1_2.SetBackColor(0xffff);
Button1_2.text.SetText("W1");
Button1_2.SetEvent(&Button1_2_Event);
window1.AddButton(&Button1_3);
Button1_3.SetRect(130,100,100,100);
Button1_3.SetBackColor(0xffff);
Button1_3.text.SetText("L1");
Button1_3.SetEvent(&Button1_3_Event);
ui.AddWindow(&window2);
window2.SetBackColor(0x0);
window2.SetRect(0,0,240,320);
window2.AddButton(&Button2_1);
Button2_1.SetRect(0,0,240,20);
Button2_1.SetBackColor(0xffff);
Button2_1.text.SetText("返回 电文加载");
Button2_1.SetEvent(&Button2_1_Event);
window2.AddButton(&Button2_2);
Button2_2.SetRect(67,30,47,40);
Button2_2.SetBackColor(0xffff);
Button2_2.text.SetText("");
Button2_2.SetEvent(&Button2_2_Event);
window2.AddButton(&Button2_3);
Button2_3.SetRect(124,30,47,40);
Button2_3.SetBackColor(0xffff);
Button2_3.text.SetText("");
Button2_3.SetEvent(&Button2_3_Event);
window2.AddButton(&Button2_4);
Button2_4.SetRect(181,30,47,40);
Button2_4.SetBackColor(0xffff);
Button2_4.text.SetText("");
Button2_4.SetEvent(&Button2_4_Event);
window2.AddButton(&Button2_5);
Button2_5.SetRect(181,30,47,40);
Button2_5.SetBackColor(0x0);
Button2_5.text.SetText("");
Button2_5.SetEvent(&Button2_5_Event);
ui.AddWindow(&window3);
window3.SetBackColor(0x4444);
window3.SetRect(0,0,240,320);
window3.AddButton(&Button3_1);
Button3_1.SetRect(0,0,240,20);
Button3_1.SetBackColor(0xffff);
Button3_1.text.SetText("返回 伪码选择");
Button3_1.SetEvent(&Button3_1_Event);
window3.AddButton(&SwitchButton3_1);
SwitchButton3_1.SetRect(0,100,240,40);
SwitchButton3_1.SetBackColor(0xffff);
SwitchButton3_1.SetEvent(&SwitchButton3_1_Event);
ui.AddWindow(&window4);
window4.SetBackColor(0x0);
window4.SetRect(0,0,240,320);
window4.AddButton(&Button4_1);
Button4_1.SetRect(0,0,240,20);
Button4_1.SetBackColor(0xffff);
Button4_1.text.SetText("返回 状态查询");
Button4_1.SetEvent(&Button4_1_Event);
ui.AddWindow(&window5);
window5.SetBackColor(0x0);
window5.SetRect(0,0,240,320);
window5.AddButton(&Button5_1);
Button5_1.SetRect(0,0,240,20);
Button5_1.SetBackColor(0xffff);
Button5_1.text.SetText("返回 多普勒频移");
Button5_1.SetEvent(&Button5_1_Event);
ui.AddWindow(&window6);
window6.SetBackColor(0x0);
window6.SetRect(0,0,240,320);
window6.AddButton(&Button6_1);
Button6_1.SetRect(0,0,240,20);
Button6_1.SetBackColor(0xffff);
Button6_1.text.SetText("返回 输出功率");
Button6_1.SetEvent(&Button6_1_Event);
ui.AddWindow(&window7);
window7.SetBackColor(0x0);
window7.SetRect(0,0,240,320);
window7.AddButton(&Button7_1);
Button7_1.SetRect(0,0,240,20);
Button7_1.SetBackColor(0xffff);
Button7_1.text.SetText("返回");
Button7_1.SetEvent(&Button7_1_Event);
window0.Refresh();
}
