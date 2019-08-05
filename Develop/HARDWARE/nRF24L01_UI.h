#ifndef __nRF24L01_UI_H_
#define __nRF24L01_UI_H_

#include "SYS.h"
#include "nRF24L01_UI.h"
#include "nRF24L01.h"

#include "STC15_SPI.h"

// ���󷵻ش���
#define RF_R_NO_IRQ 0X10
#define RF_R_NO_DAT 0X11
#define RF_R_Wrong_DAT 0X12

#define RF_DATA_Check ENABLE // �Ƿ������ݼ�鹦�ܣ���Ԥ�����ճ������Ƚ�

#if (RF_DATA_Check == ENABLE)
#define Send_Len_MAX 5 // �������ݵ���󳤶ȣ��������32�ֽ����ݣ�
#endif
// ����SPIͨ������ģʽ������
#define LO1_SPI_NUM SPI_HW_Group_0
#define L01_SPI_RorW_Byte(Group_num, input) SPI_HW_RorW_Byte(Group_num, input)
// #define LO1_SPI_NUM SPI_SW_Group_0
// #define L01_SPI_RorW_Byte(Group_num, input) SPI_RorW_Byte(Group_num, input)
// �����շ���ַ
#define L01_RX_Addr_SET_V 1, 2, 3, 4, 5
#define L01_TX_Addr_SET_V 1, 2, 3, 4, 5
extern uc8 L01_RX_Addr[5];
extern uc8 L01_TX_Addr[5];
// ��ʼ��RFоƬ
void RF_Init(void);
// ��������
E_Code RF_Recv(u8 *recv_dat, u8 *len);
// ��������
E_Code RF_Send(u8 *Send_dat, u8 *len);
// ����ģ��Ϊ����ģʽ
void RF_Recv_Mode(void);
// ����ģ��Ϊ����ģʽ
void RF_Send_Mode(void);

#endif
