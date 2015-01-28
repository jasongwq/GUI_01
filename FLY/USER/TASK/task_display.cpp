#include "./TASK/task.h"
#include "../../GLIB/PERIPHERAL/LCD/LCD.h"
#include "../../GLIB/PERIPHERAL/LCD/touch.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif
#include "UI.h"
#include "UI_User.h"
#include "font_User.h"

/*
    需要包含
    lcd.c
    ili93.c
    touch.c
    */

//TP_TestAdjust();
//LCD_Test();
int task_display(void)
{
    _SS
    WaitX(20);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	  LCD_Init();
    TP_Init();
	  UI_Init();
    //    WaitX(1000);
    //    LCD_Clear(WHITE);
    //    window2.Refresh();
    //    WaitX(1000);
    //    LCD_Clear(WHITE);
    //    window1.Refresh();
    //    Refresh_window()
		Show_Str(0,0,200,16,(u8 *)"拉美撒吃的喝",&User_Font_simsun_16x16,1);
	  //Show_Font(10,10,(u8 *)"的",&User_Font_1,0);
    while (1)
    {
        WaitX(10);
        ui.event_detection();
        //tp_dev.scan(0);
        TP_Draw_Big_Point(tp_dev.x, tp_dev.y, RED);
    }
    _EE
}

