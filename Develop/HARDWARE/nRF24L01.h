/*===========================================================================
* 网址 ：http://yhmcu.taobao.com/   http://www.cdebyte.com/                 *
* 作者 ：李勇  原 亿和电子工作室  现 亿佰特电子科技有限公司                 * 
* 邮件 ：yihe_liyong@126.com                                                *
* 电话 ：18615799380                                                        *
============================================================================*/

#ifndef _nRF24L01_H_
#define _nRF24L01_H_

#include "SYS.h"
#include "nRF24L01.h"
#include "nRF24L01_Reg.h"

#define REPEAT_CNT 15 // 0-15, repeat transmit count
// #define INIT_ADDR 1, 2, 3, 4, 5

// nRF24L01P相关控制引脚定义

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

// nRF24L01P相关函数接口
// 初始化L01
void L01_Init(void);

// 复位TX FIFO指针
void L01_FlushTX(void);

// 复位RX FIFO指针
void L01_FlushRX(void);

// 读取中断
u8 L01_ReadIRQSource(void);

// 清除中断
#define IRQ_ALL ((1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT))
void L01_ClearIRQ(u8 IRQ_Source);

// 读取FIFO数据宽度
u8 L01_ReadTopFIFOWidth(void);

// 读取接收到的数据
u8 L01_ReadRXPayload(u8 *pBuff);

// 设置L01模式
#define TX_MODE 0
#define RX_MODE 1
void L01_SetTRMode(u8 mode);

// 设置L01空速
#define SPD_250K 0
#define SPD_1M 1
#define SPD_2M 2
void L01_SetSpeed(u8 speed);

// 设置L01功率
#define P_F18DBM 0
#define P_F12DBM 1
#define P_F6DBM 2
#define P_0DBM 4
void L01_SetPower(u8 power);

// 设置L01频率
void L01_WriteHoppingPoint(u8 FreqPoint);

u8 L01_ReadStatusReg(void);

// 写数据到一个寄存器
void L01_WriteSingleReg(u8 Addr, u8 Value);

// 读取一个寄存器的值
u8 L01_ReadSingleReg(u8 Addr);

// 读取多个寄存器的值
void L01_ReadMultiReg(u8 StartAddr, u8 nBytes, u8 *pBuff);

// 写数据到多个寄存器
void L01_WriteMultiReg(u8 StartAddr, u8 *pBuff, u8 Length);

// 写数据到TXFIFO(带ACK返回)
void L01_WriteTXPayload_Ack(u8 *pBuff, u8 nBytes);

// 写数据到TXFIFO(不带ACK返回)
void L01_WriteTXPayload_NoAck(u8 *Data, u8 Data_Length);

// 设置发送物理地址
void L01_SetTXAddr(u8 *pAddr, u8 Addr_Length);

// 设置接收物理地址
void L01_SetRXAddr(u8 PipeNum, u8 *pAddr, u8 Addr_Length);

#endif //_nRF24L01_H_

/*===========================================================================
-----------------------------------文件结束----------------------------------
===========================================================================*/