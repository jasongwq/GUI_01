/**
  *                           ���ģ��
  *                   ������USB  TFT  TOUCH����
	*                           TFT �ؼ�
  *
  *							               �����
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "delay.h"
#include "USART.h"
#include "EXTI.h"
#include "GPIO.h"
#include "sdio_sdcard.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "hw_config.h"
#include "ff.h"
#include "XPT2046.h"
#include "lcd_dis24.h"
#include "TFT_M.h"
#include "Chinese.h"
#include "CC1101.h"
#include "PWM.h"
#include "MPU6050.h"
#include "TIMER.h"
#include "Motor.h"
#include "eeprom.h"
//#include "STM32F10x_TIM_H"


typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;		 

void My_Init(void);
void RCC_Configuration(void);								
void GPIO_Configuration(void);
void ff_check(void);
extern u16 VirtAddVarTab[NumbOfVar];
u8 Init_All=0;
/* ���������� */
u16 Xs=0,Ys=0,X1,Y1;
/* ��ʾͼ�β��� */
u8 ShowMode=0;
u8 stic=0;
int picda_0[120];
int picda_1[120];
/* �Ƕ����� */
float angx,comx,qx;
float angy,comy,qy,qz;
/*  �����Ƕ� */
float  AngX,AngY,AngZ;
/* �Ƕȵ��� */
u8  AdAng=1;  // �Ƕ��Զ�У׼  
/* �����PWM */
u16 PM1,PM2,PM3,PM4;
u16 PMM;      // ����
u16 MaxMM=1500;// �������
u16 MinPWM=0;
u16 MaxPWM=1500;
u8  MON=0;    // ������ƿ���

u16 PWM4=0,Last_PWM4;
u16 timetic=0;
u32 leng;
u16 speed1;

int main(void)												 
{   
	  //u16 x,y,z,qx,qy,qz;
    My_Init();
	
	  Init_All=1;
    while(1)
    { 			 
				 TFT_Show_Num(200,50 ,leng,4,0x0,0xffff);// ��ʼ�����������꣬���֣����ȣ���ɫ1����ɫ2			
				if(PEN==0)
				{												 
					XPT2046_Read_Dat(&X1,&Y1);
					Xs=((Y1)*11)/80-1477/80; Ys=((X1)*150)/841-11090/841;  //
					TFT_Touch_Deal(Xs,Ys);								 
				}	// */
			       				
				if(Menu_Step==1 && Menu_Sign==2) 
				{
					  if(AdAng==0)
						{ 
							Init_All=0;AdAng=1;
							Adjust_MPU6050_Ang(); 
							Adjust_MPU6050_Location();
							//Adjust_All();
							Creat_Buuton_2(20,90,0xf45f,"Ad_0",0x2345,"Wait",1,4);	
              Init_All=1;							
						}
				 M1_S2_m0();
				}		
				//delay_ms(20);
				timetic++;
		}
  
}
void My_Init(void)
{
		RCC_Configuration();
		delay_init(72);
//  FLASH_Unlock();   
//	EE_Init();
    Init_All=0;
		delay_ms(50);
	  PM1=PM2=PM3=PM4=MinPWM;
		GPIO_Configuration();
	  MPU6050_Init();
	  XPT2046_Init();
	  LCD_Init();
		USART_NVIC_Configuration(1,1,0,0);
		USART1_Configuration(115200);
	
	
	  TIM_Init(TIM6,1000,120);  // һ����600 �� ��ȡ�Ƕ�ֵ
	  
	  TIMER_NVIC_Configuration(6,5,0,1);
	
	
	  TIM_Init(TIM5,801,0); 
	  TIM_TIxExternalClockConfig(TIM5, TIM_TIxExternalCLK1Source_TI1ED,TIM_ICPolarity_Rising, 0x0);
		TIMER_NVIC_Configuration(5,1,0,1);
//    TIM5_PWM_init(72,5000,1,1,0,0); // PA0 PA1 PA2 PA3
//    Change_TIM5_OC1_Pulse(MinPWM); // PA0
//		Change_TIM5_OC2_Pulse(MinPWM); // PA1
	  TIM8_PWM_init(72,3000,1,1,0,0); // PC6 PC7 PC8 PC9
    Change_TIM8_OC1_Pulse(MinPWM); // PC6
		Change_TIM8_OC2_Pulse(MinPWM); // PC7		
		//Read_All_Err();
		Creat_All();	

	  printf("\r\n OK");
		
}
/*******************************************************************************/
void GPIO_Configuration(void)
{
    PA2_OUT PA0_In
  	//Set_A2
}

void RCC_Configuration(void)
{
	ErrorStatus HSEStartUpStatus;								//ԭ���Ƕ�����ȫ�ֱ�����

    RCC_DeInit();									    		//ʱ�ӿ��ƼĴ���ȫ���ָ�Ĭ��ֵ
    RCC_HSEConfig(RCC_HSE_ON);						        	//�ⲿ����ʱ��Դ������8M����
    HSEStartUpStatus = RCC_WaitForHSEStartUp();					//�ȴ��ⲿʱ�Ӿ���
    if(HSEStartUpStatus == SUCCESS)								//���ʱ�������ɹ�
    {

      RCC_HCLKConfig(RCC_SYSCLK_Div1);						//����AHB�豸ʱ��Ϊϵͳʱ��1��Ƶ
    	RCC_PCLK2Config(RCC_HCLK_Div1);							//����AHB2�豸ʱ��ΪHCLKʱ��1��Ƶ
    	RCC_PCLK1Config(RCC_HCLK_Div2);							//����AHB1�豸ʱ��ΪHCLKʱ��2��Ƶ
    	FLASH_SetLatency(FLASH_Latency_2);					  	//�趨�ڲ�FLASH�ĵ���ʱ����Ϊ2����
    	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	//ʹ��FLASHԤ��ȡ������
    	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);	//����PLLʱ��Ϊ�ⲿ����ʱ�ӵ�9��Ƶ��8MHz * 9 = 72 MHz
    	RCC_PLLCmd(ENABLE);										//ʹ��PLLʱ��
    	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}    //�ȴ�PLLʱ���������׼������
    	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);				//ʹ��PLLʱ����Ϊϵͳʱ��Դ
    	while(RCC_GetSYSCLKSource() != 0x08){}					//����ϵͳ����ʱ��Դȷ��Ϊ�ⲿ���پ���8M����
  	}  
}
void ff_check(void)
{
	u8 buf[200]="This is a new file, the data is just written in! ����һ�����ļ�������Ҳ���µģ�";//SD�����ݻ�����

	FATFS fs;
	FIL fsrc;
	FRESULT res;
	UINT br;// */
	
	f_mount(0, &fs);
// �½��ļ���
    res=f_mkdir("My_dirab");if(!res)printf("Mkdir_0_OK \r\n");   // �½��ļ��е����ֲ��ܳ����˸��ַ������Ҷ��Ǵ�д��
	res=f_mkdir("My_dirab/My_1");if(!res)printf("Mkdir_1_OK \r\n");
	res=f_mkdir("My_dirab/My_2");if(!res)printf("Mkdir_2_OK \r\n");
// �½��ļ�
	res=f_open(&fsrc, "My_dirab/My_1/wu.txt", FA_WRITE | FA_CREATE_ALWAYS);
	if(!res)
	{
// д�ļ�
		printf("\r\n Creak_OK");
		res=f_write(&fsrc, buf,200,&br);
		if(br<200){printf("write_not_ok \r\n");}  // У��
	}
	else printf("\r\n Creak_fild");
// ������ �� �ļ����ƶ�
	res = f_rename("My_dirab/My_1/wu.txt","My_dirab/My_1/wutian.txt"); //�������ļ���  ����������֮���ļ����ݾͻ�ʧȥ
	res = f_rename("My_dirab/My_1/wutian.txt","My_dirab/My_2/wutian.txt"); //�ƶ��ļ���

	f_close(&fsrc);
}




