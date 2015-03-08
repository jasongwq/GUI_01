#include "UI.h"
Window *pwindow_list[8];
MiniGui ui(pwindow_list);
Button *pButton0[7];
SwitchButton *pSwitchButton0[1];
Window window0(0,pButton0,pSwitchButton0);
Button Button0_0;
Button Button0_1;
Button Button0_2;
Button Button0_3;
Button Button0_4;
Button Button0_5;
Button Button0_6;
Button *pButton1[1];
SwitchButton *pSwitchButton1[2];
Window window1(1,pButton1,pSwitchButton1);
Button Button1_0;
SwitchButton SwitchButton1_1("L1 已选","L1 未选",0xf800,0xef7d);
SwitchButton SwitchButton1_2("E1 已选","E1 未选",0xf800,0xef7d);
Button *pButton2[1];
SwitchButton *pSwitchButton2[1];
Window window2(2,pButton2,pSwitchButton2);
Button Button2_0;
SwitchButton SwitchButton2_1("是","否",0xf800,0xef7d);
Button *pButton3[1];
SwitchButton *pSwitchButton3[20];
Window window3(3,pButton3,pSwitchButton3);
// Window window3(3);
Button Button3_0;
SwitchButton SwitchButton3_1("","",0xf800,0xef7d);
SwitchButton SwitchButton3_2("","",0xf800,0xef7d);
SwitchButton SwitchButton3_3("","",0xf800,0xef7d);
SwitchButton SwitchButton3_4("","",0xf800,0xef7d);
SwitchButton SwitchButton3_5("","",0xf800,0xef7d);
SwitchButton SwitchButton3_6("","",0xf800,0xef7d);
SwitchButton SwitchButton3_7("","",0xf800,0xef7d);
SwitchButton SwitchButton3_8("","",0xf800,0xef7d);
SwitchButton SwitchButton3_9("","",0xf800,0xef7d);
SwitchButton SwitchButton3_10("","",0xf800,0xef7d);
SwitchButton SwitchButton3_11("","",0xf800,0xef7d);
SwitchButton SwitchButton3_12("","",0xf800,0xef7d);
SwitchButton SwitchButton3_13("","",0xf800,0xef7d);
SwitchButton SwitchButton3_14("","",0xf800,0xef7d);
SwitchButton SwitchButton3_15("","",0xf800,0xef7d);
SwitchButton SwitchButton3_16("","",0xf800,0xef7d);
SwitchButton SwitchButton3_17("","",0xf800,0xef7d);
SwitchButton SwitchButton3_18("","",0xf800,0xef7d);
SwitchButton SwitchButton3_19("","",0xf800,0xef7d);
SwitchButton SwitchButton3_20("","",0xf800,0xef7d);
Button *pButton4[1];
SwitchButton *pSwitchButton4[2];
Window window4(4,pButton4,pSwitchButton4);
// Window window4(4);
Button Button4_0;
SwitchButton SwitchButton4_1("DAC5687工作正常","DAC5687工作不正常",0xf800,0xef7d);
SwitchButton SwitchButton4_2("ADF4360工作正常","ADF4360工作不正常",0xf800,0xef7d);
Button *pButton5[1];
SwitchButton *pSwitchButton5[1];
Window window5(5,pButton5,pSwitchButton5);
// Window window5(5);
Button Button5_0;
SwitchButton SwitchButton5_1("是","否",0xf800,0xef7d);
Button *pButton6[1];
SwitchButton *pSwitchButton6[3];
Window window6(6,pButton6,pSwitchButton6);
// Window window6(6);
Button Button6_0;
SwitchButton SwitchButton6_1("-6dBm","-6dBm",0xf800,0xef7d);
SwitchButton SwitchButton6_2("-3dBm","-3dBm",0xf800,0xef7d);
SwitchButton SwitchButton6_3("0dBm","0dBm",0xf800,0xef7d);
Button *pButton7[1];
SwitchButton *pSwitchButton7[1];
Window window7(7,pButton7,pSwitchButton7);
// Window window7(7);
Button Button7_0;
int Button0_0_Event(Event event){if (event == release){window1.Refresh();}return 0;}
int Button0_1_Event(Event event){if (event == release){window2.Refresh();}return 0;}
int Button0_2_Event(Event event){if (event == release){window3.Refresh();}return 0;}
int Button0_3_Event(Event event){if (event == release){window4.Refresh();}return 0;}
int Button0_4_Event(Event event){if (event == release){window5.Refresh();}return 0;}
int Button0_5_Event(Event event){if (event == release){window6.Refresh();}return 0;}
int Button0_6_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int Button1_0_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int curswitchbotton1=0;
int SwitchButton1_1_Event(Event event){if (event == release){u8 cur=0;if(pSwitchButton1[cur]->GetOnoff()!=1){pSwitchButton1[curswitchbotton1]->SetOff();pSwitchButton1[curswitchbotton1]->Refresh();curswitchbotton1=cur;pSwitchButton1[cur]->SetOn();pSwitchButton1[cur]->Refresh();}} return 0;}
int SwitchButton1_2_Event(Event event){if (event == release){u8 cur=1;if(pSwitchButton1[cur]->GetOnoff()!=1){pSwitchButton1[curswitchbotton1]->SetOff();pSwitchButton1[curswitchbotton1]->Refresh();curswitchbotton1=cur;pSwitchButton1[cur]->SetOn();pSwitchButton1[cur]->Refresh();}} return 0;}
// int SwitchButton1_1_Event(Event event){if (event == release){if(SwitchButton1_1.GetOnoff())SwitchButton1_1.SetOff();else SwitchButton1_1.SetOn();SwitchButton1_1.Refresh();}return 0;}
// int SwitchButton1_2_Event(Event event){if (event == release){if(SwitchButton1_2.GetOnoff())SwitchButton1_2.SetOff();else SwitchButton1_2.SetOn();SwitchButton1_2.Refresh();}return 0;}
int Button2_0_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int SwitchButton2_1_Event(Event event){if (event == release){if(SwitchButton2_1.GetOnoff())SwitchButton2_1.SetOff();else SwitchButton2_1.SetOn();SwitchButton2_1.Refresh();}return 0;}
int Button3_0_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int curswitchbotton3=0;
int SwitchButton3_1_Event(Event event){if (event == release){u8 cur=0;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_2_Event(Event event){if (event == release){u8 cur=1;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_3_Event(Event event){if (event == release){u8 cur=2;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_4_Event(Event event){if (event == release){u8 cur=3;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_5_Event(Event event){if (event == release){u8 cur=4;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_6_Event(Event event){if (event == release){u8 cur=5;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_7_Event(Event event){if (event == release){u8 cur=6;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_8_Event(Event event){if (event == release){u8 cur=7;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_9_Event(Event event){if (event == release){u8 cur=8;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_10_Event(Event event){if (event == release){u8 cur=9;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_11_Event(Event event){if (event == release){u8 cur=10;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_12_Event(Event event){if (event == release){u8 cur=11;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_13_Event(Event event){if (event == release){u8 cur=12;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_14_Event(Event event){if (event == release){u8 cur=13;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_15_Event(Event event){if (event == release){u8 cur=14;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_16_Event(Event event){if (event == release){u8 cur=15;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_17_Event(Event event){if (event == release){u8 cur=16;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_18_Event(Event event){if (event == release){u8 cur=17;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_19_Event(Event event){if (event == release){u8 cur=18;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int SwitchButton3_20_Event(Event event){if (event == release){u8 cur=19;if(pSwitchButton3[cur]->GetOnoff()!=1){pSwitchButton3[curswitchbotton3]->SetOff();pSwitchButton3[curswitchbotton3]->Refresh();curswitchbotton3=cur;pSwitchButton3[cur]->SetOn();pSwitchButton3[cur]->Refresh();}} return 0;}
int Button4_0_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int SwitchButton4_1_Event(Event event){if (event == release){/*if(SwitchButton4_1.GetOnoff())SwitchButton4_1.SetOff();else SwitchButton4_1.SetOn();SwitchButton4_1.Refresh();*/}return 0;}
int SwitchButton4_2_Event(Event event){if (event == release){/*if(SwitchButton4_2.GetOnoff())SwitchButton4_2.SetOff();else SwitchButton4_2.SetOn();SwitchButton4_2.Refresh();*/}return 0;}
int Button5_0_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int SwitchButton5_1_Event(Event event){if (event == release){if(SwitchButton5_1.GetOnoff())SwitchButton5_1.SetOff();else SwitchButton5_1.SetOn();SwitchButton5_1.Refresh();}return 0;}
int Button6_0_Event(Event event){if (event == release){window0.Refresh();}return 0;}
int curswitchbotton6=0;
int SwitchButton6_1_Event(Event event){if (event == release){u8 cur=0;if(pSwitchButton6[cur]->GetOnoff()!=1){pSwitchButton6[curswitchbotton6]->SetOff();pSwitchButton6[curswitchbotton6]->Refresh();curswitchbotton6=cur;pSwitchButton6[cur]->SetOn();pSwitchButton6[cur]->Refresh();}} return 0;}
int SwitchButton6_2_Event(Event event){if (event == release){u8 cur=1;if(pSwitchButton6[cur]->GetOnoff()!=1){pSwitchButton6[curswitchbotton6]->SetOff();pSwitchButton6[curswitchbotton6]->Refresh();curswitchbotton6=cur;pSwitchButton6[cur]->SetOn();pSwitchButton6[cur]->Refresh();}} return 0;}
int SwitchButton6_3_Event(Event event){if (event == release){u8 cur=2;if(pSwitchButton6[cur]->GetOnoff()!=1){pSwitchButton6[curswitchbotton6]->SetOff();pSwitchButton6[curswitchbotton6]->Refresh();curswitchbotton6=cur;pSwitchButton6[cur]->SetOn();pSwitchButton6[cur]->Refresh();}} return 0;}
// int SwitchButton6_1_Event(Event event){if (event == release){if(SwitchButton6_1.GetOnoff())SwitchButton6_1.SetOff();else SwitchButton6_1.SetOn();SwitchButton6_1.Refresh();}return 0;}
// int SwitchButton6_2_Event(Event event){if (event == release){if(SwitchButton6_2.GetOnoff())SwitchButton6_2.SetOff();else SwitchButton6_2.SetOn();SwitchButton6_2.Refresh();}return 0;}
// int SwitchButton6_3_Event(Event event){if (event == release){if(SwitchButton6_3.GetOnoff())SwitchButton6_3.SetOff();else SwitchButton6_3.SetOn();SwitchButton6_3.Refresh();}return 0;}
int Button7_0_Event(Event event){if (event == release){window0.Refresh();}return 0;}
void UI_Init(void){
ui.AddWindow(&window0);
window0.SetBackColor(0xef7d);
window0.SetRect(0,0,240,320);
window0.AddButton(&Button0_0);
Button0_0.SetRect(10,30,100,80);
Button0_0.SetBackColor(0x555f);
Button0_0.text.SetText((char *)"波段选择");
Button0_0.SetEvent(&Button0_0_Event);
window0.AddButton(&Button0_1);
Button0_1.SetRect(130,30,100,80);
Button0_1.SetBackColor(0x555f);
Button0_1.text.SetText((char *)"电文加载");
Button0_1.SetEvent(&Button0_1_Event);
window0.AddButton(&Button0_2);
Button0_2.SetRect(10,130,100,80);
Button0_2.SetBackColor(0x555f);
Button0_2.text.SetText((char *)"伪码选择");
Button0_2.SetEvent(&Button0_2_Event);
window0.AddButton(&Button0_3);
Button0_3.SetRect(130,130,100,80);
Button0_3.SetBackColor(0x555f);
Button0_3.text.SetText((char *)"状态查询");
Button0_3.SetEvent(&Button0_3_Event);
window0.AddButton(&Button0_4);
Button0_4.SetRect(10,230,100,80);
Button0_4.SetBackColor(0x555f);
Button0_4.text.SetText((char *)"多普勒频移");
Button0_4.SetEvent(&Button0_4_Event);
window0.AddButton(&Button0_5);
Button0_5.SetRect(130,230,100,80);
Button0_5.SetBackColor(0x555f);
Button0_5.text.SetText((char *)"输出功率");
Button0_5.SetEvent(&Button0_5_Event);
window0.AddButton(&Button0_6);
Button0_6.SetRect(0,0,240,25);
Button0_6.SetBackColor(0xafff);
Button0_6.text.SetText((char *)"主界面");
Button0_6.SetEvent(&Button0_6_Event);
ui.AddWindow(&window1);
window1.SetBackColor(0x52bf);
window1.SetRect(0,0,240,320);
window1.AddButton(&Button1_0);
Button1_0.SetRect(0,0,240,25);
Button1_0.SetBackColor(0x57ff);
Button1_0.text.SetText((char *)"波段选择   |   返回");
Button1_0.SetEvent(&Button1_0_Event);
window1.AddButton(&SwitchButton1_1);
SwitchButton1_1.SetRect(10,100,100,100);
SwitchButton1_1.SetBackColor(0xef7d);
SwitchButton1_1.SetEvent(&SwitchButton1_1_Event);
window1.AddButton(&SwitchButton1_2);
SwitchButton1_2.SetRect(130,100,100,100);
SwitchButton1_2.SetBackColor(0xef7d);
SwitchButton1_2.SetEvent(&SwitchButton1_2_Event);
ui.AddWindow(&window2);
window2.SetBackColor(0x52bf);
window2.SetRect(0,0,240,320);
window2.AddButton(&Button2_0);
Button2_0.SetRect(0,0,240,25);
Button2_0.SetBackColor(0xef7d);
Button2_0.text.SetText((char *)"电文加载   |   返回");
Button2_0.SetEvent(&Button2_0_Event);
window2.AddButton(&SwitchButton2_1);
SwitchButton2_1.SetRect(50,50,140,150);
SwitchButton2_1.SetBackColor(0xef7d);
SwitchButton2_1.SetEvent(&SwitchButton2_1_Event);
ui.AddWindow(&window3);
window3.SetBackColor(0x97f);
window3.SetRect(0,0,240,320);
window3.AddButton(&Button3_0);
Button3_0.SetRect(0,0,240,25);
Button3_0.SetBackColor(0xef7d);
Button3_0.text.SetText((char *)"伪码选择   |   返回");
Button3_0.SetEvent(&Button3_0_Event);
window3.AddButton(&SwitchButton3_1);
SwitchButton3_1.SetRect(8,30,50,53);
SwitchButton3_1.SetBackColor(0xef7d);
SwitchButton3_1.SetEvent(&SwitchButton3_1_Event);
window3.AddButton(&SwitchButton3_2);
SwitchButton3_2.SetRect(66,30,50,53);
SwitchButton3_2.SetBackColor(0xef7d);
SwitchButton3_2.SetEvent(&SwitchButton3_2_Event);
window3.AddButton(&SwitchButton3_3);
SwitchButton3_3.SetRect(124,30,50,53);
SwitchButton3_3.SetBackColor(0xef7d);
SwitchButton3_3.SetEvent(&SwitchButton3_3_Event);
window3.AddButton(&SwitchButton3_4);
SwitchButton3_4.SetRect(182,30,50,53);
SwitchButton3_4.SetBackColor(0xef7d);
SwitchButton3_4.SetEvent(&SwitchButton3_4_Event);
window3.AddButton(&SwitchButton3_5);
SwitchButton3_5.SetRect(8,88,50,53);
SwitchButton3_5.SetBackColor(0xef7d);
SwitchButton3_5.SetEvent(&SwitchButton3_5_Event);
window3.AddButton(&SwitchButton3_6);
SwitchButton3_6.SetRect(66,88,50,53);
SwitchButton3_6.SetBackColor(0xef7d);
SwitchButton3_6.SetEvent(&SwitchButton3_6_Event);
window3.AddButton(&SwitchButton3_7);
SwitchButton3_7.SetRect(124,88,50,53);
SwitchButton3_7.SetBackColor(0xef7d);
SwitchButton3_7.SetEvent(&SwitchButton3_7_Event);
window3.AddButton(&SwitchButton3_8);
SwitchButton3_8.SetRect(182,88,50,53);
SwitchButton3_8.SetBackColor(0xef7d);
SwitchButton3_8.SetEvent(&SwitchButton3_8_Event);
window3.AddButton(&SwitchButton3_9);
SwitchButton3_9.SetRect(8,146,50,53);
SwitchButton3_9.SetBackColor(0xef7d);
SwitchButton3_9.SetEvent(&SwitchButton3_9_Event);
window3.AddButton(&SwitchButton3_10);
SwitchButton3_10.SetRect(66,146,50,53);
SwitchButton3_10.SetBackColor(0xef7d);
SwitchButton3_10.SetEvent(&SwitchButton3_10_Event);
window3.AddButton(&SwitchButton3_11);
SwitchButton3_11.SetRect(124,146,50,53);
SwitchButton3_11.SetBackColor(0xef7d);
SwitchButton3_11.SetEvent(&SwitchButton3_11_Event);
window3.AddButton(&SwitchButton3_12);
SwitchButton3_12.SetRect(182,146,50,53);
SwitchButton3_12.SetBackColor(0xef7d);
SwitchButton3_12.SetEvent(&SwitchButton3_12_Event);
window3.AddButton(&SwitchButton3_13);
SwitchButton3_13.SetRect(8,204,50,53);
SwitchButton3_13.SetBackColor(0xef7d);
SwitchButton3_13.SetEvent(&SwitchButton3_13_Event);
window3.AddButton(&SwitchButton3_14);
SwitchButton3_14.SetRect(66,204,50,53);
SwitchButton3_14.SetBackColor(0xef7d);
SwitchButton3_14.SetEvent(&SwitchButton3_14_Event);
window3.AddButton(&SwitchButton3_15);
SwitchButton3_15.SetRect(124,204,50,53);
SwitchButton3_15.SetBackColor(0xef7d);
SwitchButton3_15.SetEvent(&SwitchButton3_15_Event);
window3.AddButton(&SwitchButton3_16);
SwitchButton3_16.SetRect(182,204,50,53);
SwitchButton3_16.SetBackColor(0xef7d);
SwitchButton3_16.SetEvent(&SwitchButton3_16_Event);
window3.AddButton(&SwitchButton3_17);
SwitchButton3_17.SetRect(8,262,50,53);
SwitchButton3_17.SetBackColor(0xef7d);
SwitchButton3_17.SetEvent(&SwitchButton3_17_Event);
window3.AddButton(&SwitchButton3_18);
SwitchButton3_18.SetRect(66,262,50,53);
SwitchButton3_18.SetBackColor(0xef7d);
SwitchButton3_18.SetEvent(&SwitchButton3_18_Event);
window3.AddButton(&SwitchButton3_19);
SwitchButton3_19.SetRect(124,262,50,53);
SwitchButton3_19.SetBackColor(0xef7d);
SwitchButton3_19.SetEvent(&SwitchButton3_19_Event);
window3.AddButton(&SwitchButton3_20);
SwitchButton3_20.SetRect(182,262,50,53);
SwitchButton3_20.SetBackColor(0xef7d);
SwitchButton3_20.SetEvent(&SwitchButton3_20_Event);
ui.AddWindow(&window4);
window4.SetBackColor(0x52bf);
window4.SetRect(0,0,240,320);
window4.AddButton(&Button4_0);
Button4_0.SetRect(0,0,240,25);
Button4_0.SetBackColor(0xef7d);
Button4_0.text.SetText((char *)"状态查询   |   返回");
Button4_0.SetEvent(&Button4_0_Event);
window4.AddButton(&SwitchButton4_1);
SwitchButton4_1.SetRect(20,100,200,50);
SwitchButton4_1.SetBackColor(0xef7d);
SwitchButton4_1.SetEvent(&SwitchButton4_1_Event);
window4.AddButton(&SwitchButton4_2);
SwitchButton4_2.SetRect(20,200,200,50);
SwitchButton4_2.SetBackColor(0xef7d);
SwitchButton4_2.SetEvent(&SwitchButton4_2_Event);
ui.AddWindow(&window5);
window5.SetBackColor(0x52bf);
window5.SetRect(0,0,240,320);
window5.AddButton(&Button5_0);
Button5_0.SetRect(0,0,240,25);
Button5_0.SetBackColor(0xef7d);
Button5_0.text.SetText((char *)"多普勒频移 |   返回");
Button5_0.SetEvent(&Button5_0_Event);
window5.AddButton(&SwitchButton5_1);
SwitchButton5_1.SetRect(20,80,200,50);
SwitchButton5_1.SetBackColor(0xef7d);
SwitchButton5_1.SetEvent(&SwitchButton5_1_Event);
ui.AddWindow(&window6);
window6.SetBackColor(0x52bf);
window6.SetRect(0,0,240,320);
window6.AddButton(&Button6_0);
Button6_0.SetRect(0,0,240,25);
Button6_0.SetBackColor(0xef7d);
Button6_0.text.SetText((char *)"输出功率   |   返回");
Button6_0.SetEvent(&Button6_0_Event);
window6.AddButton(&SwitchButton6_1);
SwitchButton6_1.SetRect(20,80,200,50);
SwitchButton6_1.SetBackColor(0xef7d);
SwitchButton6_1.SetEvent(&SwitchButton6_1_Event);
window6.AddButton(&SwitchButton6_2);
SwitchButton6_2.SetRect(20,150,200,50);
SwitchButton6_2.SetBackColor(0xef7d);
SwitchButton6_2.SetEvent(&SwitchButton6_2_Event);
window6.AddButton(&SwitchButton6_3);
SwitchButton6_3.SetRect(20,220,200,50);
SwitchButton6_3.SetBackColor(0xef7d);
SwitchButton6_3.SetEvent(&SwitchButton6_3_Event);
ui.AddWindow(&window7);
window7.SetBackColor(0xef7d);
window7.SetRect(0,0,240,320);
window7.AddButton(&Button7_0);
Button7_0.SetRect(0,0,240,25);
Button7_0.SetBackColor(0xef7d);
Button7_0.text.SetText((char *)"返回");
Button7_0.SetEvent(&Button7_0_Event);
window0.Refresh();
}
