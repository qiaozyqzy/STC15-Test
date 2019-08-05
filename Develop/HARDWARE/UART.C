#include "SYS.h"
#include "UART.h"
#include "MY_STUDIO.h"
#include <intrins.h>

BOOL UART_busy;

#if (UART1_Open)
BOOL UART1_Flag = 0;
BOOL UART1_bit9;
#if (UART1_REC_buf_Open)
u8 xdata UART1_REC_buf[UART1_REC_buf_MAX];
u8 xdata UART1_REC_buf_Count;
#else
u8 UART1_Data;
#endif
#endif

#if (UART2_Open)
BOOL UART2_Flag = 0;
BOOL UART2_bit9;
#if (UART2_REC_buf_Open)
u8 xdata UART2_REC_buf[UART2_REC_buf_MAX];
u8 xdata UART2_REC_buf_Count;
#else
u8 UART2_Data;
#endif
#endif

#if (UART3_Open)
BOOL UART3_Flag = 0;
BOOL UART3_bit9;
#if (UART3_REC_buf_Open)
u8 xdata UART3_REC_buf[UART3_REC_buf_MAX];
u8 xdata UART3_REC_buf_Count;
#else
u8 UART3_Data;
#endif
#endif

#if (UART4_Open)
BOOL UART4_Flag = 0;
BOOL UART4_bit9;
#if (UART4_REC_buf_Open)
u8 xdata UART4_REC_buf[UART4_REC_buf_MAX];
u8 xdata UART4_REC_buf_Count;
#else
u8 UART4_Data;
#endif
#endif

s8 UART_Init(s8 UART_num, s8 UART_Seat, u32 BAUD)
{
   s8 a = TRUE;
   switch (UART_num)
   {
#if (UART1_Open)
   case UART1:
      UART1_Iint(UART_Seat, BAUD);
      break;
#endif
#if (UART2_Open)
   case UART2:
      UART2_Iint(UART_Seat, BAUD);
      break;
#endif
#if (UART3_Open)
   case UART3:
      UART3_Iint(UART_Seat, BAUD);
      break;
#endif
#if (UART4_Open)
   case UART4:
      UART4_Iint(UART_Seat, BAUD);
      break;
#endif
   default:
      a = ~a;
   }
   return a;
}
#if (UART1_Open)
void UART1_Iint(s8 UART_Seat, u32 BAUD)
{
   ACC = P_SW1;
   ACC &= ~(S1_S0 | S1_S1);
   switch (UART_Seat)
   {
   case UART1_on_P30_P31:
      break;
   case UART1_on_P36_P37:
      ACC |= S1_S0;
      break;
   case UART1_on_P16_P17:
      ACC |= S1_S1;
      break;
   }
   P_SW1 = ACC;
#if (UART1_PARITYBIT == NONE_PARITY)
   SCON = 0x50; //8位可变波特率
#elif (UART1_PARITYBIT == ODD_PARITY) || (UART1_PARITYBIT == EVEN_PARITY) || (UART1_PARITYBIT == MARK_PARITY)
   SCON = 0xda;           //9位可变波特率,校验位初始为1
#elif (UART1_PARITYBIT == SPACE_PARITY)
   SCON = 0xd2;  //9位可变波特率,校验位初始为0
#endif
   EA = 0;
   if ((BAUD == BAUD1) && (BAUD1 == BAUD2)) //使用定时器2
   {
      AUXR |= 0x01;                      //串口1选择定时器2为波特率发生器
      AUXR |= 0x04;                      //定时器2时钟为Fosc,即1T
      T2L = (65536 - (FOSC / 4 / BAUD)); //设置波特率重装值
      T2H = (65536 - (FOSC / 4 / BAUD)) >> 8;
      AUXR |= 0x10; //启动定时器2
   }
   else //使用定时器1
   {
      AUXR |= 0x40;                      //定时器1时钟为Fosc,即1T
      AUXR &= 0xFE;                      //串口1选择定时器1为波特率发生器
      TMOD &= 0x0F;                      //设定定时器1为16位自动重装方式
      TL1 = (65536 - (FOSC / 4 / BAUD)); //设置波特率重装值
      TH1 = (65536 - (FOSC / 4 / BAUD)) >> 8;
      ET1 = 0; //禁止定时器1中断
      TR1 = 1; //启动定时器1
   }

   ES = 1; //使能串口1中断
   EA = 1;

   SendString(UART1, "STC15_UART1_OK!!!\r\n");
}
#endif
#if (UART2_Open)
void UART2_Iint(s8 UART_Seat, u32 BAUD)
{
   switch (UART_Seat)
   {
   case UART2_on_P10_P11:
      P_SW2 &= ~S2_S0; //S2_S0=0 (P1.0/RxD2, P1.1/TxD2)
      break;
   case UART2_on_P46_P47:
      P_SW2 |= S2_S0; //S2_S0=1 (P4.6/RxD2_2, P4.7/TxD2_2)
      break;
   }
#if (UART2_PARITYBIT == NONE_PARITY)
   S2CON = 0x50; //8位可变波特率
#elif (UART2_PARITYBIT == ODD_PARITY) || (UART2_PARITYBIT == EVEN_PARITY) || (UART2_PARITYBIT == MARK_PARITY)
   S2CON = 0xda;          //9位可变波特率,校验位初始为1
#elif (UART2_PARITYBIT == SPACE_PARITY)
   S2CON = 0xd2; //9位可变波特率,校验位初始为0
#endif
   EA = 0;
   if (BAUD == 0)
   {
      BAUD = BAUD2;
   }
   AUXR |= 0x04;                      //定时器2时钟为Fosc,即1T
   T2L = (65536 - (FOSC / 4 / BAUD)); //设置波特率重装值
   T2H = (65536 - (FOSC / 4 / BAUD)) >> 8;
   AUXR |= 0x10; //启动定时器2

   IE2 |= 0x01; //使能串口2中断
   EA = 1;
   //SendString(UART2,"STC15_UART2_OK!!!\r\n");
}
#endif
#if (UART3_Open)
void UART3_Iint(s8 UART_Seat, u32 BAUD)
{
   switch (UART_Seat)
   {
   case UART3_on_P00_P01:
      P_SW2 &= ~S3_S0; //S3_S0=0 (P0.0/RxD3, P0.1/TxD3)
      break;
   case UART3_on_P50_P51:
      P_SW2 |= S3_S0; //S3_S0=1 (P5.0/RxD3_2, P5.1/TxD3_2)
      break;
   }
#if (UART3_PARITYBIT == NONE_PARITY)
   S3CON = 0x50; //8位可变波特率
#elif (UART3_PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
   S3CON = 0xda;          //9位可变波特率,校验位初始为1
#elif (UART3_PARITYBIT == SPACE_PARITY)
   S3CON = 0xd2; //9位可变波特率,校验位初始为0
#endif

   EA = 0;
   if ((BAUD == BAUD3) && (BAUD3 == BAUD2)) //使用定时器2
   {
      AUXR |= 0x01;                      //串口3选择定时器2为波特率发生器
      AUXR |= 0x04;                      //定时器2时钟为Fosc,即1T
      T2L = (65536 - (FOSC / 4 / BAUD)); //设置波特率重装值
      T2H = (65536 - (FOSC / 4 / BAUD)) >> 8;
      AUXR |= 0x10; //启动定时器2
   }
   else //使用定时器3
   {

      S3CON |= 0x40;                     //串口3选择定时器3为波特率发生器
      T4T3M |= 0x02;                     //定时器3时钟为Fosc,即1T
      T3L = (65536 - (FOSC / 4 / BAUD)); //设置波特率重装值
      T3H = (65536 - (FOSC / 4 / BAUD)) >> 8;
      T4T3M |= 0x08; //启动定时器3
   }
   IE2 |= 0x08; //使能串口3中断
   EA = 1;
   SendString(UART3, "STC15_UART3_OK!!!\r\n");
}
#endif
#if (UART4_Open)
void UART4_Iint(s8 UART_Seat, u32 BAUD)
{
   switch (UART_Seat)
   {
   case UART4_on_P02_P03:
      P_SW2 &= ~S4_S0; //S4_S0=0 (P0.2/RxD4, P0.3/TxD4)
      break;
   case UART4_on_P52_P53:
      P_SW2 |= S4_S0; //S4_S0=1 (P5.2/RxD4_2, P5.3/TxD4_2)
      break;
   }
#if (UART4_PARITYBIT == NONE_PARITY)
   S4CON = 0x50; //8位可变波特率
#elif (UART4_PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
   S4CON = 0xda;          //9位可变波特率,校验位初始为1
#elif (UART4_PARITYBIT == SPACE_PARITY)
   S4CON = 0xd2; //9位可变波特率,校验位初始为0
#endif

   EA = 0;
   if ((BAUD == BAUD4) && (BAUD4 == BAUD2)) //使用定时器2
   {
      AUXR |= 0x01;                      //串口4选择定时器2为波特率发生器
      AUXR |= 0x04;                      //定时器2时钟为Fosc,即1T
      T2L = (65536 - (FOSC / 4 / BAUD)); //设置波特率重装值
      T2H = (65536 - (FOSC / 4 / BAUD)) >> 8;
      AUXR |= 0x10; //启动定时器2
   }
   else //使用定时器4
   {
      S4CON |= 0x40;                     //串口4选择定时器4为波特率发生器
      T4T3M |= 0x20;                     //定时器4时钟为Fosc,即1T
      T4L = (65536 - (FOSC / 4 / BAUD)); //设置波特率重装值
      T4H = (65536 - (FOSC / 4 / BAUD)) >> 8;
      T4T3M |= 0x80; //启动定时器4
   }
   IE2 |= 0x10; //使能串口4中断
   EA = 1;
   SendString(UART4, "STC15_UART4_OK!!!\r\n");
}
#endif

/*----------------------------
//UART 中断服务程序
-----------------------------*/
#if (UART1_Open) //UART1中断服务程序
void Uart1() interrupt 4 using 1
{
   if (RI)
   {
      RI = 0; //清除RI位
#if (UART1_REC_buf_Open)
      UART1_REC_buf[UART1_REC_buf_Count] = SBUF;
      UART1_REC_buf_Count++;
#else
      UART1_Data = SBUF;  //P0显示串口数据
#endif
      UART1_bit9 = RB8; //校验位
      UART1_Flag = 1;
   }
   if (TI)
   {
      TI = 0;        //清除TI位
      UART_busy = 0; //清忙标志
   }
}
#endif
#if (UART2_Open) //UART2中断服务程序
void Uart2() interrupt 8 using 1
{
   if (S2CON & S2RI)
   {
      S2CON &= ~S2RI; //清除S2RI位
#if (UART2_REC_buf_Open)
      UART2_REC_buf[UART2_REC_buf_Count] = S2BUF;
      UART2_REC_buf_Count++;
#else
      UART2_Data = S2BUF; //P0显示串口数据
#endif
      UART2_bit9 = (((S2CON & S2RB8) >> 2) & 0x01); //P2.2显示校验位
      UART2_Flag = 1;
   }
   if (S2CON & S2TI)
   {
      S2CON &= ~S2TI; //清除S2TI位
      UART_busy = 0;  //清忙标志
   }
}
#endif
#if (UART3_Open) //UART3中断服务程序
void Uart3() interrupt 17 using 1
{
   if (S3CON & S3RI)
   {
      S3CON &= ~S3RI; //清除S3RI位
#if (UART3_REC_buf_Open)
      UART3_REC_buf[UART3_REC_buf_Count] = S3BUF;
      UART3_REC_buf_Count++;
#else
      UART3_Data = S3BUF; //P0显示串口数据
#endif
      UART3_bit9 = (((S3CON & S3RB8) >> 2) & 0x01); //P2.2显示校验位
      UART3_Flag = 1;
   }
   if (S3CON & S3TI)
   {
      S3CON &= ~S3TI; //清除S3TI位
      UART_busy = 0;  //清忙标志
   }
}
#endif
#if (UART4_Open) //UART4中断服务程序
void Uart4() interrupt 18 using 1
{
   if (S4CON & S4RI)
   {
      S4CON &= ~S4RI; //清除S4RI位
#if (UART4_REC_buf_Open)
      UART4_REC_buf[UART4_REC_buf_Count] = S4BUF;
      UART4_REC_buf_Count++;
#else
      UART4_Data = S4BUF; //P0显示串口数据
#endif
      UART4_bit9 = (((S4CON & S4RB8) >> 2) & 0x01); //P2.2显示校验位
      UART4_Flag = 1;
   }
   if (S4CON & S4TI)
   {
      S4CON &= ~S4TI; //清除S4TI位
      UART_busy = 0;  //清忙标志
   }
}
#endif
/*----------------------------
发送串口数据
----------------------------*/
void UART_SendData(s8 UART_num, u8 dat)
{
   switch (UART_num)
   {
#if (UART1_Open)
   case UART1:
      UART1_SendDat(dat);
      break;
#endif
#if (UART2_Open)
   case UART2:
      UART2_SendDat(dat);
      break;
#endif
#if (UART3_Open)
   case UART3:
      UART3_SendDat(dat);
      break;
#endif
#if (UART4_Open)
   case UART4:
      UART4_SendDat(dat);
      break;
#endif
      //default:break;
   }
}
/*----------------------------
发送串口数据子程序
----------------------------*/
#if (UART1_Open)
void UART1_SendDat(u8 dat)
{
   while (UART_busy)
      ;       //等待前面的数据发送完成
   ACC = dat; //获取校验位P (PSW.0)
   if (P)     //根据P来设置校验位
   {
#if (UART1_PARITYBIT == ODD_PARITY)
      TB8 = 0; //设置校验位为0
#elif (UART1_PARITYBIT == EVEN_PARITY)
      TB8 = 1;            //设置校验位为1
#endif
   }
   else
   {
#if (UART1_PARITYBIT == ODD_PARITY)
      TB8 = 1; //设置校验位为1
#elif (UART1_PARITYBIT == EVEN_PARITY)
      TB8 = 0;            //设置校验位为0
#endif
   }
   UART_busy = 1;
   SBUF = ACC; //写数据到UART数据寄存器
}
#endif
#if (UART2_Open)
void UART2_SendDat(u8 dat)
{
   while (UART_busy)
      ;       //等待前面的数据发送完成
   ACC = dat; //获取校验位P (PSW.0)
   if (P)     //根据P来设置校验位
   {
#if (UART2_PARITYBIT == ODD_PARITY)
      S2CON &= ~S2TB8; //设置校验位为0
#elif (UART2_PARITYBIT == EVEN_PARITY)
      S2CON |= S2TB8;     //设置校验位为1
#endif
   }
   else
   {
#if (UART2_PARITYBIT == ODD_PARITY)
      S2CON |= S2TB8; //设置校验位为1
#elif (UART2_PARITYBIT == EVEN_PARITY)
      S2CON &= ~S2TB8;    //设置校验位为0
#endif
   }
   UART_busy = 1;
   S2BUF = ACC; //写数据到UART2数据寄存器
}
#endif
#if (UART3_Open)
void UART3_SendDat(u8 dat)
{
   while (UART_busy)
      ;       //等待前面的数据发送完成
   ACC = dat; //获取校验位P (PSW.0)
   if (P)     //根据P来设置校验位
   {
#if (UART3_PARITYBIT == ODD_PARITY)
      S3CON &= ~S3TB8; //设置校验位为0
#elif (UART3_PARITYBIT == EVEN_PARITY)
      S3CON |= S3TB8;     //设置校验位为1
#endif
   }
   else
   {
#if (UART3_PARITYBIT == ODD_PARITY)
      S3CON |= S3TB8; //设置校验位为1
#elif (UART3_PARITYBIT == EVEN_PARITY)
      S3CON &= ~S3TB8;    //设置校验位为0
#endif
   }
   UART_busy = 1;
   S3BUF = ACC; //写数据到UART3数据寄存器
}
#endif
#if (UART4_Open)
void UART4_SendDat(u8 dat)
{
   while (UART_busy)
      ;       //等待前面的数据发送完成
   ACC = dat; //获取校验位P (PSW.0)
   if (P)     //根据P来设置校验位
   {
#if (UART4_PARITYBIT == ODD_PARITY)
      S4CON &= ~S4TB8; //设置校验位为0
#elif (UART4_PARITYBIT == EVEN_PARITY)
      S4CON |= S4TB8;     //设置校验位为1
#endif
   }
   else
   {
#if (UART4_PARITYBIT == ODD_PARITY)
      S4CON |= S4TB8; //设置校验位为1
#elif (UART4_PARITYBIT == EVEN_PARITY)
      S4CON &= ~S4TB8;    //设置校验位为0
#endif
   }
   UART_busy = 1;
   S4BUF = ACC; //写数据到UART4数据寄存器
}
#endif
/*----------------------------
发送字符串
----------------------------*/
void SendString(s8 UART_num, s8 *s)
{
   while (*s) //检测字符串结束标志
   {
      UART_SendData(UART_num, *s++); //发送当前字符
   }
}
/*----------------------------
发送数字
----------------------------*/
void SendNumU32(s8 UART_num, u32 dat) //无符号数字转换为字符串（0~42 9496 7295）
{
   u8 xdata datbuf[12];
   NumU32_to_STR(dat, &datbuf);
   SendString(UART_num, datbuf);
}
void SendNumS32(s8 UART_num, s32 dat) //有符号数字转换为字符串（-21 4748 3648~21 4748 3647）
{
   u8 xdata datbuf[12];
   Num32_to_STR(dat, &datbuf);
   SendString(UART_num, datbuf);
}
