#include "iFlash.h"


/********************************************************************************************************** 
** Function name:      FLASH_ReadHalfWord
** Descriptions:       ��ȡָ����ַ�İ�������
** input parameters:   u32 addr��Ҫ���ĵ�ַ
** output parameters:  ��
** Returned value:     ��
**********************************************************************************************************/
u16 FLASH_ReadHalfWord(u32 addr)
{
	return *(vu16*)addr; 
}

/********************************************************************************************************** 
** Function name:      FLASH_Write
** Descriptions:       Flashд
** input parameters:   u32 Addr����ʼ��ַ
                       u16 *p �� Ҫд�����ݣ�����Ϊ��λ��
                       u16 Num�� Ҫд�İ�����Ŀ 
** output parameters:  ��
** Returned value:     ��
**********************************************************************************************************/
void FLASH_Write(u32 Addr,u16 *p,u16 Num)
{	
	u16 i;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(Addr);
	for(i = 0;i < Num;i++){
		FLASH_ProgramHalfWord(Addr,*(p + i));
	  Addr += 2;
	} 
	FLASH_Lock();
}
