/***SYS***/
#include "sys.h"
#include "gpio.h"
#include <string.h>
#include "usr_usart.h"
#include "minos_delay.h"
#include "sys_os.h"
#include "gpio.h"
#include "stm32_config.h"
#include "G32_timer.h"
/***C***/
#include "string.h"
/***Other***/
#include "./TASK/tasks.h"

void SYS_INIT(void)
{
    /***延时初始化***/
    delay_init();
    /***中断初始化***/
    NVIC_Configuration();
    //uart_init (115200);
    //uart_init (115200);
    uart3_init(115200);
    Sys_Printf(Printf_USART, (char *)"\r\nPrintf_USART ok");

    delay_ms(500);
}

int main(void)
{
    SYS_INIT();
    /***总循环***/
    while (1)
    {
        RunTaskA(task_gps,0);
        RunTaskA(task_gsm,2);
        RunTaskA(task_led,3);
    }
}
