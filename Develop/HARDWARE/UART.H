/********************************************************
注：用户设置部分参见UARTuseapi.h文件
********************************************************/
#ifndef __UART_H__
#define __UART_H__

#include "SYS.h"
#include "UARTConfig.h"


//校验方式
#define NONE_PARITY 0  //无校验
#define ODD_PARITY 1   //奇校验
#define EVEN_PARITY 2  //偶校验
#define MARK_PARITY 3  //标记校验
#define SPACE_PARITY 4 //空白校验

#define S2RI 0x01  //S2CON.0
#define S2TI 0x02  //S2CON.1
#define S2RB8 0x04 //S2CON.2
#define S2TB8 0x08 //S2CON.3
#define S3RI 0x01  //S3CON.0
#define S3TI 0x02  //S3CON.1
#define S3RB8 0x04 //S3CON.2
#define S3TB8 0x08 //S3CON.3
#define S4RI 0x01  //S4CON.0
#define S4TI 0x02  //S4CON.1
#define S4RB8 0x04 //S4CON.2
#define S4TB8 0x08 //S4CON.3

#define S1_S0 0x40 //P_SW1.6
#define S1_S1 0x80 //P_SW1.7
#define S2_S0 0x01 //P_SW2.0
#define S3_S0 0x02 //P_SW2.1
#define S4_S0 0x04 //P_SW2.2

extern BOOL UART_busy;
/*----------------------------
STC15串口总服务程序
----------------------------*/
//串口初始化
extern s8 UART_Init(s8 UART_num, s8 UART_Seat, u32 BAUD);
//发送串口数据
extern void UART_SendData(s8 UART_num, u8 dat);
//发送字符串
extern void SendString(s8 UART_num, s8 *s);
//发送数字
extern void SendNumU32(s8 UART_num, u32 dat); //无符号数字转换为字符串（0~42 9496 7295）
extern void SendNumS32(s8 UART_num, s32 dat); //有符号数字转换为字符串（-21 4748 3648~21 4748 3647）
/*----------------------------
STC15串口1服务程序
----------------------------*/
#if UART1_Open
extern BOOL UART1_Flag; //串口1接收标志位
extern BOOL UART1_bit9; //串口1第九位数据
#if (UART1_REC_buf_Open)
#define UART1_REC_buf_MAX 64
extern u8 xdata UART1_REC_buf[UART1_REC_buf_MAX]; //串口1接收数据
extern u8 xdata UART1_REC_buf_Count;
#else
extern u8 UART1_Data; //串口1接收数据
#endif
//串口1初始化
extern void UART1_Iint(s8 UART_Seat, u32 BAUD);
//串口1发送数据
extern void UART1_SendDat(u8 dat);
#endif
/*----------------------------
STC15串口2服务程序
----------------------------*/
#if (UART2_Open)
extern BOOL UART2_Flag; //串口2接收标志位
extern BOOL UART2_bit9; //串口2第九位数据

#if (UART2_REC_buf_Open)
#define UART2_REC_buf_MAX 64
extern u8 xdata UART2_REC_buf[UART2_REC_buf_MAX]; //串口2接收数据
extern u8 xdata UART2_REC_buf_Count;
#else
extern u8 UART2_Data; //串口2接收数据
#endif
//串口2初始化
extern void UART2_Iint(s8 UART_Seat, u32 BAUD);
//串口2发送数据
extern void UART2_SendDat(u8 dat);
#endif
/*----------------------------
STC15串口3服务程序
----------------------------*/
#if (UART3_Open)
extern BOOL UART3_Flag; //串口3接收标志位
extern BOOL UART3_bit9; //串口3第九位数据
#if (UART3_REC_buf_Open)
#define UART3_REC_buf_MAX 64
extern u8 xdata UART3_REC_buf[UART3_REC_buf_MAX]; //串口3接收数据
extern u8 xdata UART3_REC_buf_Count;
#else
extern u8 UART3_Data; //串口3接收数据
#endif
//串口3初始化
extern void UART3_Iint(s8 UART_Seat, u32 BAUD);
//串口3发送数据
extern void UART3_SendDat(u8 dat);
#endif
/*----------------------------
STC15串口4服务程序
----------------------------*/
#if (UART4_Open)
extern BOOL UART4_Flag; //串口4接收标志位
extern BOOL UART4_bit9; //串口4第九位数据
#if (UART4_REC_buf_Open)
#define UART4_REC_buf_MAX 64
extern u8 xdata UART4_REC_buf[UART4_REC_buf_MAX]; //串口3接收数据
extern u8 xdata UART4_REC_buf_Count;
#else
extern u8 UART4_Data; //串口3接收数据
#endif
//串口4初始化
extern void UART4_Iint(s8 UART_Seat, u32 BAUD);
//串口4发送数据
extern void UART4_SendDat(u8 dat);
#endif
/*----------------------------
//UART 中断服务程序
-----------------------------*/
//void Uart1() interrupt 4 using 1
//void Uart2() interrupt 8 using 1
//void Uart3() interrupt 17 using 1
//void Uart4() interrupt 18 using 1

#endif
