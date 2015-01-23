#include "./TASK/task.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "../../GLIB/PERIPHERAL/GPS/GPS_DRIVER.h"
nmea_msg gpsx;
int task_gps(void)
{
    _SS
    u16 i, rxlen;
    WaitX(20);
    while (1)
    {
        u8 USART2_RX_t[0xff];
        if (USART2_RX_STA & 0X8000)     //接收到一次数据了
        {
            rxlen = USART2_RX_STA & 0X7FFF; //得到数据长度
            for (i = 0; i < rxlen; i++)USART2_RX_t[i] = USART2_RX_BUF[i];
            USART2_RX_STA = 0;          //启动下一次接收
            USART2_RX_t[i] = 0;       //自动添加结束符
            GPS_Analysis(&gpsx, (u8 *)USART2_RX_t); //分析字符串
            //Gps_Msg_Show();             //显示信息
            //if (upload)printf("\r\n%s\r\n", USART1_TX_BUF); //发送接收到的数据到串口1
        }
        WaitX(10);
    }
    _EE
}

#ifdef __cplusplus
}
#endif
