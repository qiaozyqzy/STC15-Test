/********************************************************
ע���û����ò��ֲμ�UARTuseapi.h�ļ�
********************************************************/
#ifndef __UART_H__
#define __UART_H__

#include "SYS.h"
#include "UARTConfig.h"


//У�鷽ʽ
#define NONE_PARITY 0  //��У��
#define ODD_PARITY 1   //��У��
#define EVEN_PARITY 2  //żУ��
#define MARK_PARITY 3  //���У��
#define SPACE_PARITY 4 //�հ�У��

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
STC15�����ܷ������
----------------------------*/
//���ڳ�ʼ��
extern s8 UART_Init(s8 UART_num, s8 UART_Seat, u32 BAUD);
//���ʹ�������
extern void UART_SendData(s8 UART_num, u8 dat);
//�����ַ���
extern void SendString(s8 UART_num, s8 *s);
//��������
extern void SendNumU32(s8 UART_num, u32 dat); //�޷�������ת��Ϊ�ַ�����0~42 9496 7295��
extern void SendNumS32(s8 UART_num, s32 dat); //�з�������ת��Ϊ�ַ�����-21 4748 3648~21 4748 3647��
/*----------------------------
STC15����1�������
----------------------------*/
#if UART1_Open
extern BOOL UART1_Flag; //����1���ձ�־λ
extern BOOL UART1_bit9; //����1�ھ�λ����
#if (UART1_REC_buf_Open)
#define UART1_REC_buf_MAX 64
extern u8 xdata UART1_REC_buf[UART1_REC_buf_MAX]; //����1��������
extern u8 xdata UART1_REC_buf_Count;
#else
extern u8 UART1_Data; //����1��������
#endif
//����1��ʼ��
extern void UART1_Iint(s8 UART_Seat, u32 BAUD);
//����1��������
extern void UART1_SendDat(u8 dat);
#endif
/*----------------------------
STC15����2�������
----------------------------*/
#if (UART2_Open)
extern BOOL UART2_Flag; //����2���ձ�־λ
extern BOOL UART2_bit9; //����2�ھ�λ����

#if (UART2_REC_buf_Open)
#define UART2_REC_buf_MAX 64
extern u8 xdata UART2_REC_buf[UART2_REC_buf_MAX]; //����2��������
extern u8 xdata UART2_REC_buf_Count;
#else
extern u8 UART2_Data; //����2��������
#endif
//����2��ʼ��
extern void UART2_Iint(s8 UART_Seat, u32 BAUD);
//����2��������
extern void UART2_SendDat(u8 dat);
#endif
/*----------------------------
STC15����3�������
----------------------------*/
#if (UART3_Open)
extern BOOL UART3_Flag; //����3���ձ�־λ
extern BOOL UART3_bit9; //����3�ھ�λ����
#if (UART3_REC_buf_Open)
#define UART3_REC_buf_MAX 64
extern u8 xdata UART3_REC_buf[UART3_REC_buf_MAX]; //����3��������
extern u8 xdata UART3_REC_buf_Count;
#else
extern u8 UART3_Data; //����3��������
#endif
//����3��ʼ��
extern void UART3_Iint(s8 UART_Seat, u32 BAUD);
//����3��������
extern void UART3_SendDat(u8 dat);
#endif
/*----------------------------
STC15����4�������
----------------------------*/
#if (UART4_Open)
extern BOOL UART4_Flag; //����4���ձ�־λ
extern BOOL UART4_bit9; //����4�ھ�λ����
#if (UART4_REC_buf_Open)
#define UART4_REC_buf_MAX 64
extern u8 xdata UART4_REC_buf[UART4_REC_buf_MAX]; //����3��������
extern u8 xdata UART4_REC_buf_Count;
#else
extern u8 UART4_Data; //����3��������
#endif
//����4��ʼ��
extern void UART4_Iint(s8 UART_Seat, u32 BAUD);
//����4��������
extern void UART4_SendDat(u8 dat);
#endif
/*----------------------------
//UART �жϷ������
-----------------------------*/
//void Uart1() interrupt 4 using 1
//void Uart2() interrupt 8 using 1
//void Uart3() interrupt 17 using 1
//void Uart4() interrupt 18 using 1

#endif