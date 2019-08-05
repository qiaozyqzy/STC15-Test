#ifndef __STC15_SPI_H
#define __STC15_SPI_H

#include "SYS.h"
#include "STC15_SPI.h"

/********************�û�����********************/
#define USE_HW_SPI ENABLE // �����Ƿ�ʹ��Ӳ��SPI��ENABLE��DISABLE
#define USE_SW_SPI ENABLE // �����Ƿ�ʹ�����SPI��ENABLE��DISABLE

#if (USE_HW_SPI == ENABLE) // Ӳ��SPI����
#define SPI_IRO DISABLE    // �����Ƿ�ʹ��SPI�ж�ģʽ��ENABLE��DISABLE
#define SPR SPDLL          // ����SPI�ٶ�
#define SPI_HW_Group_0 0   // (P1.2/SS, P1.3/MOSI, P1.4/MISO, P1.5/SCLK)
#define SPI_HW_Group_1 1   // (P2.4/SS_2, P2.3/MOSI_2, P2.2/MISO_2, P2.1/SCLK_2)
#define SPI_HW_Group_2 2   // (P5.4/SS_3, P4.0/MOSI_3, P4.1/MISO_3, P4.3/SCLK_3)
#endif
#if (USE_SW_SPI == ENABLE) // ���SPI����
// ������Ŷ���
#define SPI_SW_Group_0 3
#define SPI_SW_Group_1 4
// ��һ�����ţ�SPI_SW_Group_0
#define SPI_SW_MOSI_PIN_0 P00
#define SPI_SW_MISO_PIN_0 P00
#define SPI_SW_SCK_PIN_0 P00
// �ڶ������ţ�SPI_SW_Group_1
#define SPI_SW_MOSI_PIN_1 P00
#define SPI_SW_MISO_PIN_1 P00
#define SPI_SW_SCK_PIN_1 P00
#define SPI_SW_Fast ENABLE  // �����Ƿ�ʹ�ÿ���ģ��SPIͨ��
#endif

/********************��������********************/
#if (USE_HW_SPI == ENABLE)
// SPI��ʼ��
void SPI_HW_Inti(u8 Group_num);
// ͨ��SPI�������ݽ���
u8 SPI_HW_RorW_Byte(u8 Group_num, u8 input);
#endif

#if (USE_SW_SPI == ENABLE)
// ͨ��SPI�������ݽ���
u8 SPI_RorW_Byte(u8 Group_num, u8 input);
#endif

#endif
