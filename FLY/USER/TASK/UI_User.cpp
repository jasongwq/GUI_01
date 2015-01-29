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
int Button4_1_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button5_1_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button6_1_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button7_1_Event(Event event){if (event == release){window0.Refresh();}return 0;}
void UI_Init(void){
ui.add_window(&window0);
window0.Set_BackColor(0xfe38);
window0.Set_Rect(0,0,240,320);
window0.add_button(&Button0_1);
Button0_1.rect.Set_Rect(20,20,80,80);
Button0_1.rect.Set_BackColor(0xffff);
Button0_1.text.Set_Text((char *)"波段选择");
Button0_1.Set_Event(&Button0_1_Event);
window0.add_button(&Button0_2);
Button0_2.rect.Set_Rect(140,20,80,80);
Button0_2.rect.Set_BackColor(0xffff);
Button0_2.text.Set_Text((char *)"电文加载");
Button0_2.Set_Event(&Button0_2_Event);
window0.add_button(&Button0_3);
Button0_3.rect.Set_Rect(140,120,80,80);
Button0_3.rect.Set_BackColor(0xffff);
Button0_3.text.Set_Text((char *)"状态查询");
Button0_3.Set_Event(&Button0_3_Event);
window0.add_button(&Button0_4);
Button0_4.rect.Set_Rect(140,220,80,80);
Button0_4.rect.Set_BackColor(0xffff);
Button0_4.text.Set_Text((char *)"输出功率");
Button0_4.Set_Event(&Button0_4_Event);
window0.add_button(&Button0_5);
Button0_5.rect.Set_Rect(20,220,80,80);
Button0_5.rect.Set_BackColor(0xffff);
Button0_5.text.Set_Text((char *)"多普勒频移");
Button0_5.Set_Event(&Button0_5_Event);
window0.add_button(&Button0_6);
Button0_6.rect.Set_Rect(20,120,80,80);
Button0_6.rect.Set_BackColor(0xffff);
Button0_6.text.Set_Text((char *)"伪码选择");
Button0_6.Set_Event(&Button0_6_Event);
ui.add_window(&window1);
window1.Set_BackColor(0x7b7f);
window1.Set_Rect(0,0,240,320);
window1.add_button(&Button1_1);
Button1_1.rect.Set_Rect(0,0,240,20);
Button1_1.rect.Set_BackColor(0xffff);
Button1_1.text.Set_Text((char *)"返回 波段选择");
Button1_1.Set_Event(&Button1_1_Event);
window1.add_button(&Button1_2);
Button1_2.rect.Set_Rect(10,100,100,100);
Button1_2.rect.Set_BackColor(0xffff);
Button1_2.text.Set_Text((char *)"W1");
Button1_2.Set_Event(&Button1_2_Event);
window1.add_button(&Button1_3);
Button1_3.rect.Set_Rect(130,100,100,100);
Button1_3.rect.Set_BackColor(0xffff);
Button1_3.text.Set_Text((char *)"L1");
Button1_3.Set_Event(&Button1_3_Event);
ui.add_window(&window2);
window2.Set_BackColor(0x0);
window2.Set_Rect(0,0,240,320);
window2.add_button(&Button2_1);
Button2_1.rect.Set_Rect(0,0,240,20);
Button2_1.rect.Set_BackColor(0xffff);
Button2_1.text.Set_Text((char *)"返回 电文加载");
Button2_1.Set_Event(&Button2_1_Event);
window2.add_button(&Button2_2);
Button2_2.rect.Set_Rect(67,30,47,40);
Button2_2.rect.Set_BackColor(0xffff);
Button2_2.text.Set_Text((char *)"");
Button2_2.Set_Event(&Button2_2_Event);
window2.add_button(&Button2_3);
Button2_3.rect.Set_Rect(124,30,47,40);
Button2_3.rect.Set_BackColor(0xffff);
Button2_3.text.Set_Text((char *)"");
Button2_3.Set_Event(&Button2_3_Event);
window2.add_button(&Button2_4);
Button2_4.rect.Set_Rect(181,30,47,40);
Button2_4.rect.Set_BackColor(0xffff);
Button2_4.text.Set_Text((char *)"");
Button2_4.Set_Event(&Button2_4_Event);
window2.add_button(&Button2_5);
Button2_5.rect.Set_Rect(181,30,47,40);
Button2_5.rect.Set_BackColor(0x0);
Button2_5.text.Set_Text((char *)"");
Button2_5.Set_Event(&Button2_5_Event);
ui.add_window(&window3);
window3.Set_BackColor(0x0);
window3.Set_Rect(0,0,240,320);
window3.add_button(&Button3_1);
Button3_1.rect.Set_Rect(0,0,240,20);
Button3_1.rect.Set_BackColor(0xffff);
Button3_1.text.Set_Text((char *)"返回 伪码选择");
Button3_1.Set_Event(&Button3_1_Event);
ui.add_window(&window4);
window4.Set_BackColor(0x0);
window4.Set_Rect(0,0,240,320);
window4.add_button(&Button4_1);
Button4_1.rect.Set_Rect(0,0,240,20);
Button4_1.rect.Set_BackColor(0xffff);
Button4_1.text.Set_Text((char *)"返回 状态查询");
Button4_1.Set_Event(&Button4_1_Event);
ui.add_window(&window5);
window5.Set_BackColor(0x0);
window5.Set_Rect(0,0,240,320);
window5.add_button(&Button5_1);
Button5_1.rect.Set_Rect(0,0,240,20);
Button5_1.rect.Set_BackColor(0xffff);
Button5_1.text.Set_Text((char *)"返回 多普勒频移");
Button5_1.Set_Event(&Button5_1_Event);
ui.add_window(&window6);
window6.Set_BackColor(0x0);
window6.Set_Rect(0,0,240,320);
window6.add_button(&Button6_1);
Button6_1.rect.Set_Rect(0,0,240,20);
Button6_1.rect.Set_BackColor(0xffff);
Button6_1.text.Set_Text((char *)"返回 输出功率");
Button6_1.Set_Event(&Button6_1_Event);
ui.add_window(&window7);
window7.Set_BackColor(0x0);
window7.Set_Rect(0,0,240,320);
window7.add_button(&Button7_1);
Button7_1.rect.Set_Rect(0,0,240,20);
Button7_1.rect.Set_BackColor(0xffff);
Button7_1.text.Set_Text((char *)"返回");
Button7_1.Set_Event(&Button7_1_Event);
window0.Refresh();
}
