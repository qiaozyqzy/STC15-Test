#ifndef __EXINTConfig_H__
#define __EXINTConfig_H__

#include "SYS.h"
#include "EXINT.h"

//设置外部中断编号
#define EXINT0 0
#define EXINT1 1
#define EXINT2 2
#define EXINT3 3
#define EXINT4 4
//开启1或关闭0某外部中断，预编译时使用，减少无用代码量
#define EXINT0_Open 0
#define EXINT1_Open 0
#define EXINT2_Open 0
#define EXINT3_Open 0
#define EXINT4_Open 0

//外部中断初始化
//exint_num:外部中断编号、exint_typ:中断类型(0:仅下降沿 1:上升沿和下降沿)
//void EXINT_Init(char exint_num,BOOL exint_typ);

//关闭外部中断
//exint_num:外部中断编号
//void EXINT_Stop(char exint_num);

//中断服务程序-->void EXINT_0() interrupt 0     //INT0中断入口
//中断服务程序-->void EXINT_1() interrupt 2     //INT1中断入口
//中断服务程序-->void EXINT_2() interrupt 10    //INT2中断入口
//中断服务程序-->void EXINT_3() interrupt 11    //INT3中断入口
//中断服务程序-->void EXINT_4() interrupt 16    //INT4中断入口

#endif
