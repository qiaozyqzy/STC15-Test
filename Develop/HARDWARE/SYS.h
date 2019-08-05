#ifndef __SYS_H_
#define __SYS_H_

#include "STC15WFxx.h"
#include "SYS.h"
#include <intrins.h>

#ifndef IDE_VSCODE
#define BOOL bit
#else
#define BOOL u8
#define bit u8
#endif

#define s8 char
#define s16 int
#define s32 long
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

#ifndef IDE_VSCODE
#define sc8 s8 code
#define sc16 s16 code
#define sc32 s32 code

#define uc8 u8 code
#define uc16 u16 code
#define uc32 u32 code
#else
#define sc8 s8 const
#define sc16 s16 const
#define sc32 s32 const

#define uc8 u8 const
#define uc16 u16 const
#define uc32 u32 const
#endif

#ifndef IDE_VSCODE
#define sx8 s8 xdata
#define sx16 s16 xdata
#define sx32 s32 xdata
#define ux8 u8 xdata
#define ux16 u16 xdata
#define ux32 u32 xdata
#else
#define sx8 s8
#define sx16 s16
#define sx32 s32
#define ux8 u8
#define ux16 u16
#define ux32 u32
#endif

#ifndef IDE_VSCODE
#define si8 s8 idata
#define si16 s16 idata
#define si32 s32 idata

#define ui8 u8 idata
#define ui16 u16 idata
#define ui32 u32 idata
#else
#define si8 s8
#define si16 s16
#define si32 s32
#define ui8 u8
#define ui16 u16
#define ui32 u32
#endif

#ifndef IDE_VSCODE
#define sb8 s8 bdata
#define sb16 s16 bdata
#define sb32 s32 bdata
#define ub8 u8 bdata
#define ub16 u16 bdata
#define ub32 u32 bdata
#else
#define sb8 s8
#define sb16 s16
#define sb32 s32
#define ub8 u8
#define ub16 u16
#define ub32 u32
#endif

#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define NULL 0

#define ENABLE 1
#define DISABLE 0

// �ض����������������
#define E_Code s8

// ���õ�Ƭ���ͺ�
#define MCU_NAME STC15W4K
#define STC15W 0X00
#define STC15W4K 0X01
#define STC15F 0X80
#define STC15F2K 0X81
//ϵͳʱ��
#define FOSC 22118400L

//���ڲ�����Ĭ������ ��ͬʱ���Թ��ö�ʱ��T2,������
#define BAUD1 115200 //����1������
#define BAUD2 115200 //����2������
#define BAUD3 115200 //����3������
#define BAUD4 115200 //����4������

void SYS_RST(void);

// // ���ڿ��ٲ�����ݵ�Ұ·�Ӱ취
// ub8 DATA_BIT_ALL;
// sbit DATA_BIT_0 = DATA_BIT_ALL ^ 0;
// sbit DATA_BIT_1 = DATA_BIT_ALL ^ 1;
// sbit DATA_BIT_2 = DATA_BIT_ALL ^ 2;
// sbit DATA_BIT_3 = DATA_BIT_ALL ^ 3;
// sbit DATA_BIT_4 = DATA_BIT_ALL ^ 4;
// sbit DATA_BIT_5 = DATA_BIT_ALL ^ 5;
// sbit DATA_BIT_6 = DATA_BIT_ALL ^ 6;
// sbit DATA_BIT_7 = DATA_BIT_ALL ^ 7;

#endif
