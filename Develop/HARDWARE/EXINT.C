#include "SYS.h"
#include "EXINT.h"
#include "EXINTConfig.h"

/*-----------------外部中断0--------------------*/
#if (EXINT0_Open)
BOOL EXINT0_Flag = 0;
BOOL EXINT0_State = 0; //1:上升沿中断 0:下降沿中断
#endif
#if (EXINT0_Open)
void EXINT0_Init(BOOL inttyp)
{
    EA = 0;
    INT0 = 1;
    IT0 = inttyp; //设置INT0的中断类型 (1:仅下降沿 0:上升沿和下降沿)
    EX0 = 1;      //使能INT0中断
    EA = 1;
}
#endif
#if (EXINT0_Open)
void EXINT0_Stop()
{
    EA = 0;
    EX0 = 0;
    EA = 1;
}
#endif
#if (EXINT0_Open)
//中断服务程序
void EXINT_0() interrupt 0 //INT0中断入口
{
    EXINT0_State = INT0; //保存INT0口的状态, INT0=0(下降沿); INT0=1(上升沿)
    EXINT0_Flag = 1;
    //ADD YOUR CODE HERE
}
#endif
/*-----------------外部中断1--------------------*/
#if (EXINT1_Open)
BOOL EXINT1_Flag = 0;
BOOL EXINT1_State = 0; //1:上升沿中断 0:下降沿中断
#endif
#if (EXINT1_Open)
void EXINT1_Init(BOOL inttyp)
{
    EA = 0;
    INT1 = 1;
    IT1 = inttyp; //设置INT1的中断类型 (1:仅下降沿 0:上升沿和下降沿)
    EX1 = 1;      //使能INT1中断
    EA = 1;
}
#endif
#if (EXINT1_Open)
void EXINT1_Stop()
{
    EA = 0;
    EX1 = 0;
    EA = 1;
}
#endif
#if (EXINT1_Open)
//中断服务程序
void EXINT_1() interrupt 2 //INT1中断入口
{
    EXINT1_State = INT0; //保存INT1口的状态, INT1=0(下降沿); INT0=1(上升沿)
    EXINT1_Flag = 1;
    //ADD YOUR CODE HERE
}
#endif
/*-----------------外部中断2--------------------*/
#if (EXINT2_Open)
BOOL EXINT2_Flag = 0;
#endif
#if (EXINT2_Open)
//中断服务程序
void EXINT_2() interrupt 10 //INT2中断入口
{
    EXINT2_Flag = 1;
    //INT_CLKO &= 0xEF;               //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
    //INT_CLKO |= 0x10;               //然后再开中断即可
    //ADD YOUR CODE HERE
}
#endif
#if (EXINT2_Open)
void EXINT2_Init()
{
    EA = 0;
    INT2 = 1;
    INT_CLKO |= 0x10; //(EX2 = 1)使能INT2中断
    EA = 1;
}
#endif
#if (EXINT2_Open)
void EXINT2_Stop()
{
    EA = 0;
    INT_CLKO &= 0xEF; //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
    EA = 1;
}
#endif
/*-----------------外部中断3--------------------*/
#if (EXINT3_Open)
BOOL EXINT3_Flag = 0;
#endif
#if (EXINT3_Open)
void EXINT3_Init()
{
    EA = 0;
    INT3 = 1;
    INT_CLKO |= 0x20; //(EX3 = 1)使能INT3中断
    EA = 1;
}
#endif
#if (EXINT3_Open)
void EXINT3_Stop()
{
    EA = 0;
    INT_CLKO &= 0xDF; //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
    EA = 1;
}
#endif
#if (EXINT3_Open)
//中断服务程序
void EXINT_3() interrupt 11 //INT3中断入口
{
    EXINT3_Flag = 1;
    //INT_CLKO &= 0xDF;               //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
    //INT_CLKO |= 0x20;               //然后再开中断即可
    //ADD YOUR CODE HERE
}
#endif
/*-----------------外部中断4--------------------*/
#if (EXINT4_Open)
BOOL EXINT4_Flag = 0;
#endif
#if (EXINT4_Open)
void EXINT4_Init()
{
    EA = 0;
    INT4 = 1;
    INT_CLKO |= 0x40; //(EX4 = 1)使能INT4中断
    EA = 1;
}
#endif
#if (EXINT4_Open)
void EXINT4_Stop()
{
    EA = 0;
    INT_CLKO &= 0xBF; //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
    EA = 1;
}
#endif
#if (EXINT4_Open)
//中断服务程序
void EXINT_4() interrupt 16 //INT4中断入口
{
    EXINT4_Flag = 1;
    //INT_CLKO &= 0xBF;               //若需要手动清除中断标志,可先关闭中断,此时系统会自动清除内部的中断标志
    //INT_CLKO |= 0x40;               //然后再开中断即可
    //ADD YOUR CODE HERE
}
#endif
/*----------------------------------------------------*/
//exint_typ:0:仅下降沿 1:上升沿和下降沿)
void EXINT_Init(char exint_num, BOOL exint_typ)
{
    exint_typ = exint_typ;
    switch (exint_num)
    {
#if (EXINT0_Open)
    case EXINT0:
        EXINT0_Init(exint_typ);
        break;
#endif
#if (EXINT1_Open)
    case EXINT1:
        EXINT1_Init(exint_typ);
        break;
#endif
#if (EXINT2_Open)
    case EXINT2:
        EXINT2_Init();
        break;
#endif
#if (EXINT3_Open)
    case EXINT3:
        EXINT3_Init();
        break;
#endif
#if (EXINT4_Open)
    case EXINT4:
        EXINT4_Init();
        break;
#endif
    }
}
void EXINT_Stop(char exint_num)
{
    switch (exint_num)
    {
#if (EXINT0_Open)
    case EXINT0:
        EXINT0_Stop();
        break;
#endif
#if (EXINT1_Open)
    case EXINT1:
        EXINT1_Stop();
        break;
#endif
#if (EXINT2_Open)
    case EXINT2:
        EXINT2_Stop();
        break;
#endif
#if (EXINT3_Open)
    case EXINT3:
        EXINT3_Stop();
        break;
#endif
#if (EXINT4_Open)
    case EXINT4:
        EXINT4_Stop();
        break;
#endif
    }
}