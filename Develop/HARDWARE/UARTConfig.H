#ifndef __UARTConfig_H__
#define __UARTConfig_H__

#include "SYS.h"
#include "UARTConfig.h"


//设置串口编号
#define UART1 1
#define UART2 2
#define UART3 3
#define UART4 4
//开启1或关闭0某串口，预编译时使用，减少无用代码量
#define UART1_Open 1
#define UART2_Open 1
#define UART3_Open 0
#define UART4_Open 0
//开启11或关闭0某串口连续接收数据，预编译时使用，减少无用代码量
#define UART1_REC_buf_Open 0
#define UART2_REC_buf_Open 0
#define UART3_REC_buf_Open 0
#define UART4_REC_buf_Open 0

//设置某串口校验方式
//NONE_PARITY:无校验;ODD_PARITY:奇校验;EVEN_PARITY:偶校验;MARK_PARITY:标记校验;SPACE_PARIT:空白校验.
#define UART1_PARITYBIT NONE_PARITY //定义校验位
#define UART2_PARITYBIT NONE_PARITY //定义校验位
#define UART3_PARITYBIT NONE_PARITY //定义校验位
#define UART4_PARITYBIT NONE_PARITY //定义校验位

//设置串口1位置
#define UART1_on_P30_P31 0
#define UART1_on_P36_P37 1
#define UART1_on_P16_P17 2
//设置串口2位置
#define UART2_on_P10_P11 0
#define UART2_on_P46_P47 1
//设置串口3位置
#define UART3_on_P00_P01 0
#define UART3_on_P50_P51 1
//设置串口4位置
#define UART4_on_P02_P03 0
#define UART4_on_P52_P53 1

/*----------------------------
STC15串口总服务程序
//-------------------------------------------------------------------------------------
//串口初始化
//s8 UART_num：串口号,s8 UART_Seat：所在位置，u32 BAUD：波特率（0为默认值）
s8 UART_Init(s8 UART_num, s8 UART_Seat, u32 BAUD);
//-------------------------------------------------------------------------------------
//发送串口数据
//s8 UART_num：串口号,u8 dat：数据
void UART_SendData(s8 UART_num, u8 dat);
//-------------------------------------------------------------------------------------
//发送字符串
//s8 UART_num：串口号,s8 *s：数据
void SendString(s8 UART_num, s8 *s);
//----------------------------
BOOL UART1_Flag; //串口1接收标志位
BOOL UART1_bit9; //串口1第九位数据
#if (UART1_REC_buf_Open)
#define UART1_REC_buf_MAX 64
extern u8 xdata UART1_REC_buf[UART1_REC_buf_MAX]; //串口1接收数据
extern u8 xdata UART1_REC_buf_Count;
#else
extern u8 UART1_Data; //串口1接收数据
#endif
//----------------------------
BOOL UART2_Flag; //串口2接收标志位
BOOL UART2_bit9; //串口2第九位数据
#if (UART2_REC_buf_Open)
#define UART2_REC_buf_MAX 64
extern u8 xdata UART2_REC_buf[UART2_REC_buf_MAX]; //串口2接收数据
extern u8 xdata UART2_REC_buf_Count;
#else
extern u8 UART2_Data; //串口2接收数据
#endif
//----------------------------
BOOL UART3_Flag; //串口3接收标志位
BOOL UART3_bit9; //串口3第九位数据
#if (UART3_REC_buf_Open)
#define UART3_REC_buf_MAX 64
extern u8 xdata UART3_REC_buf[UART3_REC_buf_MAX]; //串口3接收数据
extern u8 xdata UART3_REC_buf_Count;
#else
extern u8 UART3_Data; //串口3接收数据
#endif
//-------------------
BOOL UART4_Flag; //串口4接收标志位
BOOL UART4_bit9; //串口4第九位数据
#if (UART4_REC_buf_Open)
#define UART4_REC_buf_MAX 64
extern u8 xdata UART4_REC_buf[UART4_REC_buf_MAX]; //串口4接收数据
extern u8 xdata UART4_REC_buf_Count;
#else
extern u8 UART4_Data; //串口4接收数据
#endif
-----------------------------------------------------*/

#endif
