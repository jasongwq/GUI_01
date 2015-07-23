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
	/***串口初始化***/
	uart_init (115200);
}
//串口数据发送
void SendData(void)
{
	extern int curswitchbotton1;//波段选择界面选中标志
	extern int curswitchbotton2;//电文加载选择界面选中标志
	extern int curswitchbotton3;//伪码选择界面选中标志
	extern int curswitchbotton5;//多普勒频移标志
	extern int curswitchbotton6;//输出功率标志

	u16 data = 0;
	data = data << 1;
	data |= curswitchbotton1 & 0x01;
	data = data << 1;
	data |= curswitchbotton2 & 0x01;
	data = data << 5;
	data |= curswitchbotton3 & 0x1F;
	data = data << 1;
	data |= curswitchbotton5 & 0x01;
	data = data << 2;
	data |= curswitchbotton6 & 0x03;
	u8 data_to_send[2];
	data_to_send[0]=BYTE1(data);//取data中高字节放入 data_to_send[0]
	data_to_send[1]=BYTE0(data);//取data中低字节放入 data_to_send[1]
	Sys_sPrintf(USART1, data_to_send, 2);//将将两字节通过串口1(A9)发出去  波特率115200
}
int main(void)
{
	SYS_INIT();
	/***总循环***/
	while (1)
	{
		RunTaskA(task_display, 2);//显示任务
	}
}
