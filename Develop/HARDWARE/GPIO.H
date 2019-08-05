#ifndef __GPIO_H_
#define __GPIO_H_

#include "SYS.h"

//IO口编号
#define IO_P0 0
#define IO_P00 0X00
#define IO_P01 0X01
#define IO_P02 0X02
#define IO_P03 0X03
#define IO_P04 0X04
#define IO_P05 0X05
#define IO_P06 0X06
#define IO_P07 0X07
#define IO_P1 1
#define IO_P10 0X10
#define IO_P11 0X11
#define IO_P12 0X12
#define IO_P13 0X13
#define IO_P14 0X14
#define IO_P15 0X15
#define IO_P16 0X16
#define IO_P17 0X17
#define IO_P2 2
#define IO_P20 0X20
#define IO_P21 0X21
#define IO_P22 0X22
#define IO_P23 0X23
#define IO_P24 0X24
#define IO_P25 0X25
#define IO_P26 0X26
#define IO_P27 0X27
#define IO_P3 3
#define IO_P30 0X30
#define IO_P31 0X31
#define IO_P32 0X32
#define IO_P33 0X33
#define IO_P34 0X34
#define IO_P35 0X35
#define IO_P36 0X36
#define IO_P37 0X37
#define IO_P4 4
#define IO_P40 0X40
#define IO_P41 0X41
#define IO_P42 0X42
#define IO_P43 0X43
#define IO_P44 0X44
#define IO_P45 0X45
#define IO_P46 0X46
#define IO_P47 0X47
#define IO_P5 5
#define IO_P50 0X50
#define IO_P51 0X51
#define IO_P52 0X52
#define IO_P53 0X53
#define IO_P54 0X54
#define IO_P55 0X55
#define IO_P56 0X56
#define IO_P57 0X57
#define IO_P6 6
#define IO_P60 0X60
#define IO_P61 0X61
#define IO_P62 0X62
#define IO_P63 0X63
#define IO_P64 0X64
#define IO_P65 0X65
#define IO_P66 0X66
#define IO_P67 0X67
#define IO_P7 7
#define IO_P70 0X70
#define IO_P71 0X71
#define IO_P72 0X72
#define IO_P73 0X73
#define IO_P74 0X74
#define IO_P75 0X75
#define IO_P76 0X76
#define IO_P77 0X77
//模式
#define Standard_Mode 0X00   //准双向口
#define Push_pull_Mode 0X01  //推挽输出
#define Pure_Input_Mode 0X10 //高阻输入
#define Open_Drain_Mode 0X11 //开漏模式
//IO口状态
#define IO_H 1
#define IO_L 0
//初始化IO口，弱上拉、高电平
extern void GPIO_Init();
//设置IO口模式
extern void Set_Pin_Group_Mode(u8 Pin_Name, u8 Pin_Mode);  //设置一组IO口的模式
extern void Set_Single_Pin_Mode(u8 Pin_Name, u8 Pin_Mode); //设置单个IO口的模式
//设置IO口（包括模式和值）
extern void Set_Pin_Group(u8 Pin_Name, u8 Pin_Mode, u8 Pin_State);  //设置一组IO口
extern void Set_Single_Pin(u8 Pin_Name, u8 Pin_Mode, u8 Pin_State); //设置单个IO口

#endif
