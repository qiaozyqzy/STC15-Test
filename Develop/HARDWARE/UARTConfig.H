#ifndef __UARTConfig_H__
#define __UARTConfig_H__

#include "SYS.h"
#include "UARTConfig.h"


//���ô��ڱ��
#define UART1 1
#define UART2 2
#define UART3 3
#define UART4 4
//����1��ر�0ĳ���ڣ�Ԥ����ʱʹ�ã��������ô�����
#define UART1_Open 1
#define UART2_Open 1
#define UART3_Open 0
#define UART4_Open 0
//����11��ر�0ĳ���������������ݣ�Ԥ����ʱʹ�ã��������ô�����
#define UART1_REC_buf_Open 0
#define UART2_REC_buf_Open 0
#define UART3_REC_buf_Open 0
#define UART4_REC_buf_Open 0

//����ĳ����У�鷽ʽ
//NONE_PARITY:��У��;ODD_PARITY:��У��;EVEN_PARITY:żУ��;MARK_PARITY:���У��;SPACE_PARIT:�հ�У��.
#define UART1_PARITYBIT NONE_PARITY //����У��λ
#define UART2_PARITYBIT NONE_PARITY //����У��λ
#define UART3_PARITYBIT NONE_PARITY //����У��λ
#define UART4_PARITYBIT NONE_PARITY //����У��λ

//���ô���1λ��
#define UART1_on_P30_P31 0
#define UART1_on_P36_P37 1
#define UART1_on_P16_P17 2
//���ô���2λ��
#define UART2_on_P10_P11 0
#define UART2_on_P46_P47 1
//���ô���3λ��
#define UART3_on_P00_P01 0
#define UART3_on_P50_P51 1
//���ô���4λ��
#define UART4_on_P02_P03 0
#define UART4_on_P52_P53 1

/*----------------------------
STC15�����ܷ������
//-------------------------------------------------------------------------------------
//���ڳ�ʼ��
//s8 UART_num�����ں�,s8 UART_Seat������λ�ã�u32 BAUD�������ʣ�0ΪĬ��ֵ��
s8 UART_Init(s8 UART_num, s8 UART_Seat, u32 BAUD);
//-------------------------------------------------------------------------------------
//���ʹ�������
//s8 UART_num�����ں�,u8 dat������
void UART_SendData(s8 UART_num, u8 dat);
//-------------------------------------------------------------------------------------
//�����ַ���
//s8 UART_num�����ں�,s8 *s������
void SendString(s8 UART_num, s8 *s);
//----------------------------
BOOL UART1_Flag; //����1���ձ�־λ
BOOL UART1_bit9; //����1�ھ�λ����
#if (UART1_REC_buf_Open)
#define UART1_REC_buf_MAX 64
extern u8 xdata UART1_REC_buf[UART1_REC_buf_MAX]; //����1��������
extern u8 xdata UART1_REC_buf_Count;
#else
extern u8 UART1_Data; //����1��������
#endif
//----------------------------
BOOL UART2_Flag; //����2���ձ�־λ
BOOL UART2_bit9; //����2�ھ�λ����
#if (UART2_REC_buf_Open)
#define UART2_REC_buf_MAX 64
extern u8 xdata UART2_REC_buf[UART2_REC_buf_MAX]; //����2��������
extern u8 xdata UART2_REC_buf_Count;
#else
extern u8 UART2_Data; //����2��������
#endif
//----------------------------
BOOL UART3_Flag; //����3���ձ�־λ
BOOL UART3_bit9; //����3�ھ�λ����
#if (UART3_REC_buf_Open)
#define UART3_REC_buf_MAX 64
extern u8 xdata UART3_REC_buf[UART3_REC_buf_MAX]; //����3��������
extern u8 xdata UART3_REC_buf_Count;
#else
extern u8 UART3_Data; //����3��������
#endif
//-------------------
BOOL UART4_Flag; //����4���ձ�־λ
BOOL UART4_bit9; //����4�ھ�λ����
#if (UART4_REC_buf_Open)
#define UART4_REC_buf_MAX 64
extern u8 xdata UART4_REC_buf[UART4_REC_buf_MAX]; //����4��������
extern u8 xdata UART4_REC_buf_Count;
#else
extern u8 UART4_Data; //����4��������
#endif
-----------------------------------------------------*/

#endif