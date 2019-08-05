#ifndef __EXINT_H__
#define __EXINT_H__

#include "SYS.h"
#include "EXINTConfig.h"

#define INT0 P32
#define INT1 P33
#define INT2 P36
#define INT3 P37
#define INT4 P30

//外部中断初始化
//exint_num:外部中断编号、exint_typ:中断类型(0:仅下降沿 1:上升沿和下降沿)
extern void EXINT_Init(char exint_num, BOOL exint_typ);
//关闭外部中断
//exint_num:外部中断编号
extern void EXINT_Stop(char exint_num);
/*-----------------外部中断0--------------------*/
#if (EXINT0_Open)
extern BOOL EXINT0_Flag;
extern BOOL EXINT0_State; //1:上升沿中断 0:下降沿中断
extern void EXINT0_Init(BOOL inttyp);
extern void EXINT0_Stop();
//中断服务程序-->void EXINT_0() interrupt 0       //INT0中断入口
#endif
/*-----------------外部中断1--------------------*/
#if (EXINT1_Open)
extern BOOL EXINT1_Flag;
extern BOOL EXINT1_State; //1:上升沿中断 0:下降沿中断
extern void EXINT1_Init(BOOL inttyp);
extern void EXINT1_Stop();
//中断服务程序-->void EXINT_1() interrupt 2       //INT1中断入口
#endif
/*-----------------外部中断2--------------------*/
#if (EXINT2_Open)
extern BOOL EXINT2_Flag;
extern void EXINT2_Init();
extern void EXINT2_Stop();
//中断服务程序-->void EXINT_2() interrupt 10          //INT2中断入口
#endif
/*-----------------外部中断3--------------------*/
#if (EXINT3_Open)
extern BOOL EXINT3_Flag;
extern void EXINT3_Init();
extern void EXINT3_Stop();
//中断服务程序-->void EXINT_3() interrupt 11          //INT3中断入口
#endif
/*-----------------外部中断4--------------------*/
#if (EXINT4_Open)
extern BOOL EXINT4_Flag;
extern void EXINT4_Init();
extern void EXINT4_Stop();
//中断服务程序-->void EXINT_4() interrupt 16          //INT4中断入口
#endif
/*----------------------------------------------------*/
#endif
