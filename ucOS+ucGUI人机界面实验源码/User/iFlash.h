#ifndef _iFlash_h
#define _iFlash_h
#include "stm32f10x.h"

u16 FLASH_ReadHalfWord(u32 addr);             //��ȡָ����ַ�İ�������
void FLASH_Write(u32 Addr,u16 *p,u16 Num);

#endif
