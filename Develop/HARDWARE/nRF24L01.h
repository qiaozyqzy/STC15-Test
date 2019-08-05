/*===========================================================================
* ��ַ ��http://yhmcu.taobao.com/   http://www.cdebyte.com/                 *
* ���� ������  ԭ �ں͵��ӹ�����  �� �ڰ��ص��ӿƼ����޹�˾                 * 
* �ʼ� ��yihe_liyong@126.com                                                *
* �绰 ��18615799380                                                        *
============================================================================*/

#ifndef _nRF24L01_H_
#define _nRF24L01_H_

#include "SYS.h"
#include "nRF24L01.h"
#include "nRF24L01_Reg.h"

#define REPEAT_CNT 15 // 0-15, repeat transmit count
// #define INIT_ADDR 1, 2, 3, 4, 5

// nRF24L01P��ؿ������Ŷ���

// #define PORT_L01_CSN GPIOB
// #define PIN_L01_CSN GPIO_Pin_4

// #define PORT_L01_IRQ GPIOA
// #define PIN_L01_IRQ GPIO_Pin_3

// #define PORT_L01_CE GPIOA
// #define PIN_L01_CE GPIO_Pin_2

// #define L01_CSN_LOW() GPIO_ResetBits(PORT_L01_CSN, PIN_L01_CSN)
// #define L01_CSN_HIGH() GPIO_SetBits(PORT_L01_CSN, PIN_L01_CSN)

// #define L01_CE_LOW() GPIO_ResetBits(PORT_L01_CE, PIN_L01_CE)
// #define L01_CE_HIGH() GPIO_SetBits(PORT_L01_CE, PIN_L01_CE)

// #define L01_IRQ_READ() GPIO_ReadInputDataBit(PORT_L01_IRQ, PIN_L01_IRQ)
#define PIN_L01_CSN P01
#define PIN_L01_IRQ P02
#define PIN_L01_CE P03

#define L01_CSN_LOW() (PIN_L01_CSN = 0)
#define L01_CSN_HIGH() (PIN_L01_CSN = 1)

#define L01_CE_LOW() (PIN_L01_CE = 0)
#define L01_CE_HIGH() (PIN_L01_CE = 1)

#define L01_IRQ_READ() (PIN_L01_IRQ)

// nRF24L01P��غ����ӿ�
// ��ʼ��L01
void L01_Init(void);

// ��λTX FIFOָ��
void L01_FlushTX(void);

// ��λRX FIFOָ��
void L01_FlushRX(void);

// ��ȡ�ж�
u8 L01_ReadIRQSource(void);

// ����ж�
#define IRQ_ALL ((1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT))
void L01_ClearIRQ(u8 IRQ_Source);

// ��ȡFIFO���ݿ��
u8 L01_ReadTopFIFOWidth(void);

// ��ȡ���յ�������
u8 L01_ReadRXPayload(u8 *pBuff);

// ����L01ģʽ
#define TX_MODE 0
#define RX_MODE 1
void L01_SetTRMode(u8 mode);

// ����L01����
#define SPD_250K 0
#define SPD_1M 1
#define SPD_2M 2
void L01_SetSpeed(u8 speed);

// ����L01����
#define P_F18DBM 0
#define P_F12DBM 1
#define P_F6DBM 2
#define P_0DBM 4
void L01_SetPower(u8 power);

// ����L01Ƶ��
void L01_WriteHoppingPoint(u8 FreqPoint);

u8 L01_ReadStatusReg(void);

// д���ݵ�һ���Ĵ���
void L01_WriteSingleReg(u8 Addr, u8 Value);

// ��ȡһ���Ĵ�����ֵ
u8 L01_ReadSingleReg(u8 Addr);

// ��ȡ����Ĵ�����ֵ
void L01_ReadMultiReg(u8 StartAddr, u8 nBytes, u8 *pBuff);

// д���ݵ�����Ĵ���
void L01_WriteMultiReg(u8 StartAddr, u8 *pBuff, u8 Length);

// д���ݵ�TXFIFO(��ACK����)
void L01_WriteTXPayload_Ack(u8 *pBuff, u8 nBytes);

// д���ݵ�TXFIFO(����ACK����)
void L01_WriteTXPayload_NoAck(u8 *Data, u8 Data_Length);

// ���÷��������ַ
void L01_SetTXAddr(u8 *pAddr, u8 Addr_Length);

// ���ý��������ַ
void L01_SetRXAddr(u8 PipeNum, u8 *pAddr, u8 Addr_Length);

#endif //_nRF24L01_H_

/*===========================================================================
-----------------------------------�ļ�����----------------------------------
===========================================================================*/