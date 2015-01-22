
#include "ultrasonic.h"


void Ult_Init(void)
{
	TRIG_Init
  ECHO_Init
	
	Clr_ECHO

#ifdef	USE_TIM_TIM5
	TIM_Init(TIM5,65530-1,72-1);
#endif		
#ifdef	USE_TIM_TIM6
	TIM_Init(TIM6,65530-1,72-1);
#endif
#ifdef	USE_TIM_TIM7
	TIM_Init(TIM7,65530-1,72-1);
#endif

}
void Get_Distance(u16 *date)
{
	Set_TRIG
	delay_us(20);
	Clr_TRIG

	while(Read_ECHO==0);
	TIM_SetCounter(USE_TIM, 0);
	TIM_Cmd(USE_TIM, ENABLE);
	while(Read_ECHO==1);

	*date=TIM_GetCounter(USE_TIM);				// ��λ mm

	TIM_Cmd(USE_TIM, DISABLE);					//�رն�ʱ��
	TIM_SetCounter(USE_TIM, 0);				    //���������������ֵ

	Clr_ECHO
}
