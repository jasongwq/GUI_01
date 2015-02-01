#ifndef __FONT_USER_H
#define __FONT_USER_H
#ifdef __cplusplus
extern "C" {
#endif
#include "sys.h"
typedef struct{
	u16* GBK_code;
	void *mat;
	u8 fontsize;
	u8 codesize;
}Font;
extern Font User_Font_1;
extern Font User_Font_simsun_16x16;
extern void Show_Str(u16 x, u16 y, u16 width, u16 height, u8 * str,Font *User_Font, u8 mode,u16 color);
//extern void Show_Font(u16 x, u16 y, u8* font,Font *User_Font, u8 mode);
#ifdef __cplusplus
}
#endif
#endif

