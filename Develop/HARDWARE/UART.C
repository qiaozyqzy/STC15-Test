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
   SCON = 0x50; //8λ�ɱ䲨����
#elif (UART1_PARITYBIT == ODD_PARITY) || (UART1_PARITYBIT == EVEN_PARITY) || (UART1_PARITYBIT == MARK_PARITY)
   SCON = 0xda;           //9λ�ɱ䲨����,У��λ��ʼΪ1
#elif (UART1_PARITYBIT == SPACE_PARITY)
   SCON = 0xd2;  //9λ�ɱ䲨����,У��λ��ʼΪ0
#endif
   EA = 0;
   if ((BAUD == BAUD1) && (BAUD1 == BAUD2)) //ʹ�ö�ʱ��2
   {
      AUXR |= 0x01;                      //����1ѡ��ʱ��2Ϊ�����ʷ�����
      AUXR |= 0x04;                      //��ʱ��2ʱ��ΪFosc,��1T
      T2L = (65536 - (FOSC / 4 / BAUD)); //���ò�������װֵ
      T2H = (65536 - (FOSC / 4 / BAUD)) >> 8;
      AUXR |= 0x10; //������ʱ��2
   }
   else //ʹ�ö�ʱ��1
   {
      AUXR |= 0x40;                      //��ʱ��1ʱ��ΪFosc,��1T
      AUXR &= 0xFE;                      //����1ѡ��ʱ��1Ϊ�����ʷ�����
      TMOD &= 0x0F;                      //�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
      TL1 = (65536 - (FOSC / 4 / BAUD)); //���ò�������װֵ
      TH1 = (65536 - (FOSC / 4 / BAUD)) >> 8;
      ET1 = 0; //��ֹ��ʱ��1�ж�
      TR1 = 1; //������ʱ��1
   }

   ES = 1; //ʹ�ܴ���1�ж�
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
   S2CON = 0x50; //8λ�ɱ䲨����
#elif (UART2_PARITYBIT == ODD_PARITY) || (UART2_PARITYBIT == EVEN_PARITY) || (UART2_PARITYBIT == MARK_PARITY)
   S2CON = 0xda;          //9λ�ɱ䲨����,У��λ��ʼΪ1
#elif (UART2_PARITYBIT == SPACE_PARITY)
   S2CON = 0xd2; //9λ�ɱ䲨����,У��λ��ʼΪ0
#endif
   EA = 0;
   if (BAUD == 0)
   {
      BAUD = BAUD2;
   }
   AUXR |= 0x04;                      //��ʱ��2ʱ��ΪFosc,��1T
   T2L = (65536 - (FOSC / 4 / BAUD)); //���ò�������װֵ
   T2H = (65536 - (FOSC / 4 / BAUD)) >> 8;
   AUXR |= 0x10; //������ʱ��2

   IE2 |= 0x01; //ʹ�ܴ���2�ж�
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
   S3CON = 0x50; //8λ�ɱ䲨����
#elif (UART3_PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
   S3CON = 0xda;          //9λ�ɱ䲨����,У��λ��ʼΪ1
#elif (UART3_PARITYBIT == SPACE_PARITY)
   S3CON = 0xd2; //9λ�ɱ䲨����,У��λ��ʼΪ0
#endif

   EA = 0;
   if ((BAUD == BAUD3) && (BAUD3 == BAUD2)) //ʹ�ö�ʱ��2
   {
      AUXR |= 0x01;                      //����3ѡ��ʱ��2Ϊ�����ʷ�����
      AUXR |= 0x04;                      //��ʱ��2ʱ��ΪFosc,��1T
      T2L = (65536 - (FOSC / 4 / BAUD)); //���ò�������װֵ
      T2H = (65536 - (FOSC / 4 / BAUD)) >> 8;
      AUXR |= 0x10; //������ʱ��2
   }
   else //ʹ�ö�ʱ��3
   {

      S3CON |= 0x40;                     //����3ѡ��ʱ��3Ϊ�����ʷ�����
      T4T3M |= 0x02;                     //��ʱ��3ʱ��ΪFosc,��1T
      T3L = (65536 - (FOSC / 4 / BAUD)); //���ò�������װֵ
      T3H = (65536 - (FOSC / 4 / BAUD)) >> 8;
      T4T3M |= 0x08; //������ʱ��3
   }
   IE2 |= 0x08; //ʹ�ܴ���3�ж�
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
   S4CON = 0x50; //8λ�ɱ䲨����
#elif (UART4_PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
   S4CON = 0xda;          //9λ�ɱ䲨����,У��λ��ʼΪ1
#elif (UART4_PARITYBIT == SPACE_PARITY)
   S4CON = 0xd2; //9λ�ɱ䲨����,У��λ��ʼΪ0
#endif

   EA = 0;
   if ((BAUD == BAUD4) && (BAUD4 == BAUD2)) //ʹ�ö�ʱ��2
   {
      AUXR |= 0x01;                      //����4ѡ��ʱ��2Ϊ�����ʷ�����
      AUXR |= 0x04;                      //��ʱ��2ʱ��ΪFosc,��1T
      T2L = (65536 - (FOSC / 4 / BAUD)); //���ò�������װֵ
      T2H = (65536 - (FOSC / 4 / BAUD)) >> 8;
      AUXR |= 0x10; //������ʱ��2
   }
   else //ʹ�ö�ʱ��4
   {
      S4CON |= 0x40;                     //����4ѡ��ʱ��4Ϊ�����ʷ�����
      T4T3M |= 0x20;                     //��ʱ��4ʱ��ΪFosc,��1T
      T4L = (65536 - (FOSC / 4 / BAUD)); //���ò�������װֵ
      T4H = (65536 - (FOSC / 4 / BAUD)) >> 8;
      T4T3M |= 0x80; //������ʱ��4
   }
   IE2 |= 0x10; //ʹ�ܴ���4�ж�
   EA = 1;
   SendString(UART4, "STC15_UART4_OK!!!\r\n");
}
#endif

/*----------------------------
//UART �жϷ������
-----------------------------*/
#if (UART1_Open) //UART1�жϷ������
void Uart1() interrupt 4 using 1
{
   if (RI)
   {
      RI = 0; //���RIλ
#if (UART1_REC_buf_Open)
      UART1_REC_buf[UART1_REC_buf_Count] = SBUF;
      UART1_REC_buf_Count++;
#else
      UART1_Data = SBUF;  //P0��ʾ��������
#endif
      UART1_bit9 = RB8; //У��λ
      UART1_Flag = 1;
   }
   if (TI)
   {
      TI = 0;        //���TIλ
      UART_busy = 0; //��æ��־
   }
}
#endif
#if (UART2_Open) //UART2�жϷ������
void Uart2() interrupt 8 using 1
{
   if (S2CON & S2RI)
   {
      S2CON &= ~S2RI; //���S2RIλ
#if (UART2_REC_buf_Open)
      UART2_REC_buf[UART2_REC_buf_Count] = S2BUF;
      UART2_REC_buf_Count++;
#else
      UART2_Data = S2BUF; //P0��ʾ��������
#endif
      UART2_bit9 = (((S2CON & S2RB8) >> 2) & 0x01); //P2.2��ʾУ��λ
      UART2_Flag = 1;
   }
   if (S2CON & S2TI)
   {
      S2CON &= ~S2TI; //���S2TIλ
      UART_busy = 0;  //��æ��־
   }
}
#endif
#if (UART3_Open) //UART3�жϷ������
void Uart3() interrupt 17 using 1
{
   if (S3CON & S3RI)
   {
      S3CON &= ~S3RI; //���S3RIλ
#if (UART3_REC_buf_Open)
      UART3_REC_buf[UART3_REC_buf_Count] = S3BUF;
      UART3_REC_buf_Count++;
#else
      UART3_Data = S3BUF; //P0��ʾ��������
#endif
      UART3_bit9 = (((S3CON & S3RB8) >> 2) & 0x01); //P2.2��ʾУ��λ
      UART3_Flag = 1;
   }
   if (S3CON & S3TI)
   {
      S3CON &= ~S3TI; //���S3TIλ
      UART_busy = 0;  //��æ��־
   }
}
#endif
#if (UART4_Open) //UART4�жϷ������
void Uart4() interrupt 18 using 1
{
   if (S4CON & S4RI)
   {
      S4CON &= ~S4RI; //���S4RIλ
#if (UART4_REC_buf_Open)
      UART4_REC_buf[UART4_REC_buf_Count] = S4BUF;
      UART4_REC_buf_Count++;
#else
      UART4_Data = S4BUF; //P0��ʾ��������
#endif
      UART4_bit9 = (((S4CON & S4RB8) >> 2) & 0x01); //P2.2��ʾУ��λ
      UART4_Flag = 1;
   }
   if (S4CON & S4TI)
   {
      S4CON &= ~S4TI; //���S4TIλ
      UART_busy = 0;  //��æ��־
   }
}
#endif
/*----------------------------
���ʹ�������
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
���ʹ��������ӳ���
----------------------------*/
#if (UART1_Open)
void UART1_SendDat(u8 dat)
{
   while (UART_busy)
      ;       //�ȴ�ǰ������ݷ������
   ACC = dat; //��ȡУ��λP (PSW.0)
   if (P)     //����P������У��λ
   {
#if (UART1_PARITYBIT == ODD_PARITY)
      TB8 = 0; //����У��λΪ0
#elif (UART1_PARITYBIT == EVEN_PARITY)
      TB8 = 1;            //����У��λΪ1
#endif
   }
   else
   {
#if (UART1_PARITYBIT == ODD_PARITY)
      TB8 = 1; //����У��λΪ1
#elif (UART1_PARITYBIT == EVEN_PARITY)
      TB8 = 0;            //����У��λΪ0
#endif
   }
   UART_busy = 1;
   SBUF = ACC; //д���ݵ�UART���ݼĴ���
}
#endif
#if (UART2_Open)
void UART2_SendDat(u8 dat)
{
   while (UART_busy)
      ;       //�ȴ�ǰ������ݷ������
   ACC = dat; //��ȡУ��λP (PSW.0)
   if (P)     //����P������У��λ
   {
#if (UART2_PARITYBIT == ODD_PARITY)
      S2CON &= ~S2TB8; //����У��λΪ0
#elif (UART2_PARITYBIT == EVEN_PARITY)
      S2CON |= S2TB8;     //����У��λΪ1
#endif
   }
   else
   {
#if (UART2_PARITYBIT == ODD_PARITY)
      S2CON |= S2TB8; //����У��λΪ1
#elif (UART2_PARITYBIT == EVEN_PARITY)
      S2CON &= ~S2TB8;    //����У��λΪ0
#endif
   }
   UART_busy = 1;
   S2BUF = ACC; //д���ݵ�UART2���ݼĴ���
}
#endif
#if (UART3_Open)
void UART3_SendDat(u8 dat)
{
   while (UART_busy)
      ;       //�ȴ�ǰ������ݷ������
   ACC = dat; //��ȡУ��λP (PSW.0)
   if (P)     //����P������У��λ
   {
#if (UART3_PARITYBIT == ODD_PARITY)
      S3CON &= ~S3TB8; //����У��λΪ0
#elif (UART3_PARITYBIT == EVEN_PARITY)
      S3CON |= S3TB8;     //����У��λΪ1
#endif
   }
   else
   {
#if (UART3_PARITYBIT == ODD_PARITY)
      S3CON |= S3TB8; //����У��λΪ1
#elif (UART3_PARITYBIT == EVEN_PARITY)
      S3CON &= ~S3TB8;    //����У��λΪ0
#endif
   }
   UART_busy = 1;
   S3BUF = ACC; //д���ݵ�UART3���ݼĴ���
}
#endif
#if (UART4_Open)
void UART4_SendDat(u8 dat)
{
   while (UART_busy)
      ;       //�ȴ�ǰ������ݷ������
   ACC = dat; //��ȡУ��λP (PSW.0)
   if (P)     //����P������У��λ
   {
#if (UART4_PARITYBIT == ODD_PARITY)
      S4CON &= ~S4TB8; //����У��λΪ0
#elif (UART4_PARITYBIT == EVEN_PARITY)
      S4CON |= S4TB8;     //����У��λΪ1
#endif
   }
   else
   {
#if (UART4_PARITYBIT == ODD_PARITY)
      S4CON |= S4TB8; //����У��λΪ1
#elif (UART4_PARITYBIT == EVEN_PARITY)
      S4CON &= ~S4TB8;    //����У��λΪ0
#endif
   }
   UART_busy = 1;
   S4BUF = ACC; //д���ݵ�UART4���ݼĴ���
}
#endif
/*----------------------------
�����ַ���
----------------------------*/
void SendString(s8 UART_num, s8 *s)
{
   while (*s) //����ַ���������־
   {
      UART_SendData(UART_num, *s++); //���͵�ǰ�ַ�
   }
}
/*----------------------------
��������
----------------------------*/
void SendNumU32(s8 UART_num, u32 dat) //�޷�������ת��Ϊ�ַ�����0~42 9496 7295��
{
   u8 xdata datbuf[12];
   NumU32_to_STR(dat, &datbuf);
   SendString(UART_num, datbuf);
}
void SendNumS32(s8 UART_num, s32 dat) //�з�������ת��Ϊ�ַ�����-21 4748 3648~21 4748 3647��
{
   u8 xdata datbuf[12];
   Num32_to_STR(dat, &datbuf);
   SendString(UART_num, datbuf);
}