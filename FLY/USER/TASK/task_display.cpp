#include "./TASK/task.h"
#include "../../GLIB/PERIPHERAL/LCD/LCD.h"
#include "../../GLIB/PERIPHERAL/LCD/touch.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif
//#include "UI.h"
#include "UI_User.h"
#include "font_User.h"

/*
    ��Ҫ����
    lcd.c
    ili93.c
    touch.c
    */

//TP_TestAdjust();
//LCD_Test();
int task_display(void)
{
    _SS
    WaitX(20);//��ʱ20ms
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	  LCD_Init();//��ʾ��ʼ��
    TP_Init();//���س�ʼ��
	  UI_Init();//UI��ʼ��
    while (1)
    {
        WaitX(80);//Sleep 80ms
        ui.EventDetection();//�����¼�
        //TP_Draw_Big_Point(tp_dev.x, tp_dev.y, RED);
    }
    _EE
}

