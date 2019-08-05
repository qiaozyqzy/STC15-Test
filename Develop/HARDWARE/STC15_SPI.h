#ifndef __STC15_SPI_H
#define __STC15_SPI_H

#include "SYS.h"
#include "STC15_SPI.h"

/********************用户设置********************/
#define USE_HW_SPI ENABLE // 设置是否使用硬件SPI：ENABLE，DISABLE
#define USE_SW_SPI ENABLE // 设置是否使用软件SPI：ENABLE，DISABLE

#if (USE_HW_SPI == ENABLE) // 硬件SPI设置
#define SPI_IRO DISABLE    // 设置是否使用SPI中断模式，ENABLE，DISABLE
#define SPR SPDLL          // 设置SPI速度
#define SPI_HW_Group_0 0   // (P1.2/SS, P1.3/MOSI, P1.4/MISO, P1.5/SCLK)
#define SPI_HW_Group_1 1   // (P2.4/SS_2, P2.3/MOSI_2, P2.2/MISO_2, P2.1/SCLK_2)
#define SPI_HW_Group_2 2   // (P5.4/SS_3, P4.0/MOSI_3, P4.1/MISO_3, P4.3/SCLK_3)
#endif
#if (USE_SW_SPI == ENABLE) // 软件SPI设置
// 引脚组号定义
#define SPI_SW_Group_0 3
#define SPI_SW_Group_1 4
// 第一组引脚：SPI_SW_Group_0
#define SPI_SW_MOSI_PIN_0 P00
#define SPI_SW_MISO_PIN_0 P00
#define SPI_SW_SCK_PIN_0 P00
// 第二组引脚：SPI_SW_Group_1
#define SPI_SW_MOSI_PIN_1 P00
#define SPI_SW_MISO_PIN_1 P00
#define SPI_SW_SCK_PIN_1 P00
#define SPI_SW_Fast ENABLE  // 设置是否使用快速模拟SPI通信
#endif

/********************函数部分********************/
#if (USE_HW_SPI == ENABLE)
// SPI初始化
void SPI_HW_Inti(u8 Group_num);
// 通过SPI进行数据交换
u8 SPI_HW_RorW_Byte(u8 Group_num, u8 input);
#endif

#if (USE_SW_SPI == ENABLE)
// 通过SPI进行数据交换
u8 SPI_RorW_Byte(u8 Group_num, u8 input);
#endif

#endif
