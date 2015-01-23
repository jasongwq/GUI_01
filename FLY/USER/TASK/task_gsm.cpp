#include "./TASK/task.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "../../GLIB/PERIPHERAL/GSM/SIM900A/SIM900A.h"
int task_gsm(void)
{
    _SS

    WaitX(20);
    while (1)
    {
        WaitX(10);
    }
    _EE
}
//sim900a主测试程序
void sim900a_test(void)
{
    u8 key = 0;
    u8 timex = 0;
    u8 sim_ready = 0;
    Sys_Printf(Printf_USART, (char *)"\r\nATK-SIM900A 测试程序");
    while (sim900a_send_cmd((u8*)"AT", (u8*)"OK", 100)) //检测是否应答AT指令
    {
    Sys_Printf(Printf_USART, (char *)"\r\n未检测到模块!!!");
        delay_ms(800);
    Sys_Printf(Printf_USART, (char *)"\r\n尝试连接模块...");
        delay_ms(400);
    }
    key += sim900a_send_cmd((u8*)"ATE0", (u8*)"OK", 200); //不回显
    sim900a_mtest_ui(40, 30);
    while (1)
    {
        delay_ms(10);
        sim_at_response(1);//检查GSM模块发送过来的数据,及时上传给电脑
        if (sim_ready) //SIM卡就绪.
        {
//            key = KEY_Scan(0);
            if (key)
            {
                switch (key)
                {
                //case KEY_RIGHT:
                    sim900a_call_test();//拨号测试
//                    break;
//                case KEY_DOWN:
//                    sim900a_sms_test(); //短信测试
//                    break;
//                case KEY_UP:
//                    sim900a_gprs_test();//GPRS测试
//                    break;
                }
                sim900a_mtest_ui(40, 30);
                timex = 0;
            }
        }
        if (timex == 0)     //2.5秒左右更新一次
        {
            if (sim900a_gsminfo_show(40, 225) == 0)sim_ready = 1;
            else sim_ready = 0;
        }
//        if ((timex % 20) == 0)LED0 = !LED0; //200ms闪烁
        timex++;
    }
}

#ifdef __cplusplus
}
#endif
