#ifndef __Font_EN_H
#define __Font_EN_H

#include "SYS.h"
#include "Font_EN.h"

//����ASCII��
//ƫ����32
#define USE_EN_F6X8 ENABLE
#define USE_EN_F8X16 ENABLE
#define USE_EN_F12X24 ENABLE
#define USE_EN_F16X32 ENABLE
#define USE_EN_Font_NUM 4

#define EN_FH8 0
#define EN_FH16 1
#define EN_FH24 2
#define EN_FH32 3

extern uc8 EN_Font_Index[USE_EN_Font_NUM][2];
#if USE_EN_F6X8 == ENABLE
/************************************6*8�ĵ���************************************/
extern uc8 EN_F6X8[95][6];
#endif
#if USE_EN_F8X16 == ENABLE
/************************************8*16�ĵ���************************************/
extern uc8 EN_F8X16[95][16];
#endif
#if USE_EN_F12X24 == ENABLE
/************************************12*24�ĵ���************************************/
extern uc8 EN_F12X24[95][36];
#endif
#if USE_EN_F16X32 == ENABLE
/************************************16*32�ĵ���************************************/
extern uc8 EN_F16X32[95][64];
#endif
#if USE_EN_F6X8 == ENABLE
#endif

#endif
