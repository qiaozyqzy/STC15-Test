#ifndef __nRF24L01_UI_H_
#define __nRF24L01_UI_H_

#include "SYS.h"
#include "nRF24L01_UI.h"
#include "nRF24L01.h"

#include "STC15_SPI.h"

// 错误返回代码
#define RF_R_NO_IRQ 0X10
#define RF_R_NO_DAT 0X11
#define RF_R_Wrong_DAT 0X12

#define RF_DATA_Check ENABLE // 是否开启数据检查功能，与预定接收长度作比较

#if (RF_DATA_Check == ENABLE)
#define Send_Len_MAX 5 // 发送数据的最大长度（单包最大32字节数据）
#endif
// 设置SPI通信所用模式及函数
#define LO1_SPI_NUM SPI_HW_Group_0
#define L01_SPI_RorW_Byte(Group_num, input) SPI_HW_RorW_Byte(Group_num, input)
// #define LO1_SPI_NUM SPI_SW_Group_0
// #define L01_SPI_RorW_Byte(Group_num, input) SPI_RorW_Byte(Group_num, input)
// 设置收发地址
#define L01_RX_Addr_SET_V 1, 2, 3, 4, 5
#define L01_TX_Addr_SET_V 1, 2, 3, 4, 5
extern uc8 L01_RX_Addr[5];
extern uc8 L01_TX_Addr[5];
// 初始化RF芯片
void RF_Init(void);
// 接收数据
E_Code RF_Recv(u8 *recv_dat, u8 *len);
// 发送数据
E_Code RF_Send(u8 *Send_dat, u8 *len);
// 设置模块为接收模式
void RF_Recv_Mode(void);
// 设置模块为发送模式
void RF_Send_Mode(void);

#endif
