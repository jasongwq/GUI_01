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
    ÐèÒª°üº¬
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
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE ); GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	  LCD_Init();
    TP_Init();
	  UI_Init();
		Show_Str(0,0,200,16,(u8 *)"test",&User_Font_simsun_16x16,1,0x0000);
    while (1)
    {
        WaitX(80);
        ui.EventDetection();
        TP_Draw_Big_Point(tp_dev.x, tp_dev.y, RED);
    }
    _EE
}

