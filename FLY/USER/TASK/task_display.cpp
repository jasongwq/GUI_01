#include "./TASK/task.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "../../GLIB/PERIPHERAL/LCD/LCD.h"
int task_display(void)
{
    _SS
		WaitX(20);
	LCD_Init();
    
    while (1)
    {
        WaitX(10);
    }
    _EE
}

#ifdef __cplusplus
}
#endif
