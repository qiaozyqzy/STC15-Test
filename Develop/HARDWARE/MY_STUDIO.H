#ifndef __MY_STUDIO_H__
#define __MY_STUDIO_H__
#include "SYS.h"

//m^n函数
u32 M_Pow_N(u8 m, u8 n);
//数字转为字符串
void Num32_to_STR(s32 dat, s8 *str); //有符号数字转换为字符串（-21 4748 3647~21 4748 3647）  
void NumU32_to_STR(u32 dat, s8 *str); //无符号数字转换为字符串（0~42 9496 7295）

#endif
