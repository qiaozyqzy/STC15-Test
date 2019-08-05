#include "SYS.h"
#include "STC15_SPI.h"

/********************函数部分********************/
#if (USE_HW_SPI == ENABLE)
/********************硬件SPI设置参数********************/
// SPSTAT:SPI状态寄存器
#define SPIF 0x80 // SPSTAT.7
#define WCOL 0x40 // SPSTAT.6
// SPCTL：SPI控制寄存器
#define SSIG 0x80 // SPCTL.7
#define SPEN 0x40 // SPCTL.6
#define DORD 0x20 // SPCTL.5
#define MSTR 0x10 // SPCTL.4
#define CPOL 0x08 // SPCTL.3
#define CPHA 0x04 // SPCTL.2
#if (MCU_NAME < STC15F)
#define SPDHH 0x00 // CPU_CLK/4
#define SPDH 0x01  // CPU_CLK/8
#define SPDL 0x02  // CPU_CLK/16
#define SPDLL 0x03 // CPU_CLK/32
#else
#define SPDHH 0x00 // CPU_CLK/4
#define SPDH 0x01  // CPU_CLK/16
#define SPDL 0x02  // CPU_CLK/64
#define SPDLL 0x03 // CPU_CLK/128
#endif
// SPDAT：SPI数据寄存器
//IE2:中断控制寄存器2
#define ESPI 0x02 // IE2.1

// 外设功能切换
#define SPI_S0 0x04
#define SPI_S1 0x08

#if (SPI_IRO == ENABLE)
BOOL SPI_Busy = FALSE; // SPI的工作状态
#endif
#if (SPI_IRO == ENABLE)
// SPI中断服务程序
void spi_IRO() interrupt 9 using 1
{
    SPSTAT = SPIF | WCOL; // 清除SPI状态位
    SPI_Busy = FALSE;
}
#endif
// SPI初始化
void SPI_HW_Inti(u8 Group_num)
{
    ACC = P_SW1;
    ACC &= ~(SPI_S0 | SPI_S1); // SPI_S0=0 SPI_S1=0
    switch (Group_num)
    {
    case SPI_HW_Group_0:
        break;
    case SPI_HW_Group_1:
        ACC |= SPI_S0; // SPI_S0=1 SPI_S1=0
        break;
    case SPI_HW_Group_2:
        ACC |= SPI_S1; // SPI_S0=0 SPI_S1=1
        break;
    default:
        break;
    }
    P_SW1 = ACC;
    SPSTAT = SPIF | WCOL;             //清除SPI状态
    SPCTL = SSIG | SPEN | MSTR | SPR; //设置SPI为主模式
#if (SPI_IRO == ENABLE)
    IE2 |= ESPI; //使能SPI传输中断
    EA = 1;
#endif
}
// 通过SPI进行数据交换
u8 SPI_HW_RorW_Byte(u8 Group_num, u8 input)
{
    Group_num = 0;
#if (SPI_IRO == ENABLE)
    SPI_Busy = TRUE;
    SPDAT = input;   //触发SPI发送
    while (SPI_Busy) //等待SPI数据传输完成
    {
    }
#else
    SPDAT = input;           //触发SPI发送
    while (!(SPSTAT & SPIF)) //等待SPI数据传输完成
    {
    }
    SPSTAT = SPIF | WCOL; //清除SPI状态
#endif
    return SPDAT;
}
#endif

#if (USE_SW_SPI == ENABLE)

#if (SPI_SW_Fast == ENABLE)
ub8 SPI_DATA_BIT_ALL;
sbit SPI_DATA_BIT_0 = SPI_DATA_BIT_ALL ^ 0;
sbit SPI_DATA_BIT_1 = SPI_DATA_BIT_ALL ^ 1;
sbit SPI_DATA_BIT_2 = SPI_DATA_BIT_ALL ^ 2;
sbit SPI_DATA_BIT_3 = SPI_DATA_BIT_ALL ^ 3;
sbit SPI_DATA_BIT_4 = SPI_DATA_BIT_ALL ^ 4;
sbit SPI_DATA_BIT_5 = SPI_DATA_BIT_ALL ^ 5;
sbit SPI_DATA_BIT_6 = SPI_DATA_BIT_ALL ^ 6;
sbit SPI_DATA_BIT_7 = SPI_DATA_BIT_ALL ^ 7;
#endif
// 通过SPI进行数据交换
u8 SPI_RorW_Byte(u8 Group_num, u8 input)
{
#if (SPI_SW_Fast != ENABLE)
    u8 i;
#endif
    switch (Group_num)
    {
    case SPI_SW_Group_0:
#if (SPI_SW_Fast == ENABLE)
        SPI_DATA_BIT_ALL = input;
        // bit7
        SPI_SW_MOSI_PIN_0 = SPI_DATA_BIT_7;
        SPI_SW_SCK_PIN_0 = 1;
        SPI_DATA_BIT_7 = SPI_SW_MISO_PIN_0;
        SPI_SW_SCK_PIN_0 = 0;
        // bit6
        SPI_SW_MOSI_PIN_0 = SPI_DATA_BIT_6;
        SPI_SW_SCK_PIN_0 = 1;
        SPI_DATA_BIT_6 = SPI_SW_MISO_PIN_0;
        SPI_SW_SCK_PIN_0 = 0;
        // bit5
        SPI_SW_MOSI_PIN_0 = SPI_DATA_BIT_5;
        SPI_SW_SCK_PIN_0 = 1;
        SPI_DATA_BIT_5 = SPI_SW_MISO_PIN_0;
        SPI_SW_SCK_PIN_0 = 0;
        // bit4
        SPI_SW_MOSI_PIN_0 = SPI_DATA_BIT_4;
        SPI_SW_SCK_PIN_0 = 1;
        SPI_DATA_BIT_4 = SPI_SW_MISO_PIN_0;
        SPI_SW_SCK_PIN_0 = 0;
        // bit3
        SPI_SW_MOSI_PIN_0 = SPI_DATA_BIT_3;
        SPI_SW_SCK_PIN_0 = 1;
        SPI_DATA_BIT_3 = SPI_SW_MISO_PIN_0;
        SPI_SW_SCK_PIN_0 = 0;
        // bit2
        SPI_SW_MOSI_PIN_0 = SPI_DATA_BIT_2;
        SPI_SW_SCK_PIN_0 = 1;
        SPI_DATA_BIT_2 = SPI_SW_MISO_PIN_0;
        SPI_SW_SCK_PIN_0 = 0;
        // bit1
        SPI_SW_MOSI_PIN_0 = SPI_DATA_BIT_1;
        SPI_SW_SCK_PIN_0 = 1;
        SPI_DATA_BIT_1 = SPI_SW_MISO_PIN_0;
        SPI_SW_SCK_PIN_0 = 0;
        // bit0
        SPI_SW_MOSI_PIN_0 = SPI_DATA_BIT_0;
        SPI_SW_SCK_PIN_0 = 1;
        SPI_DATA_BIT_0 = SPI_SW_MISO_PIN_0;
        SPI_SW_SCK_PIN_0 = 0;
        input = SPI_DATA_BIT_ALL;
#else
        for (i = 8; i > 0; i--)
        {
            SPI_SW_MOSI_PIN_0 = (input & 0x80);
            input = (input << 1);
            SPI_SW_SCK_PIN_0 = 1;
            input |= SPI_SW_MISO_PIN_0;
            SPI_SW_SCK_PIN_0 = 0;
        }
#endif
        break;
    case SPI_SW_Group_1:
#if (SPI_SW_Fast == ENABLE)
        SPI_DATA_BIT_ALL = input;
        // bit7
        SPI_SW_MOSI_PIN_1 = SPI_DATA_BIT_7;
        SPI_SW_SCK_PIN_1 = 1;
        SPI_DATA_BIT_7 = SPI_SW_MISO_PIN_1;
        SPI_SW_SCK_PIN_1 = 0;
        // bit6
        SPI_SW_MOSI_PIN_1 = SPI_DATA_BIT_6;
        SPI_SW_SCK_PIN_1 = 1;
        SPI_DATA_BIT_6 = SPI_SW_MISO_PIN_1;
        SPI_SW_SCK_PIN_1 = 0;
        // bit5
        SPI_SW_MOSI_PIN_1 = SPI_DATA_BIT_5;
        SPI_SW_SCK_PIN_1 = 1;
        SPI_DATA_BIT_5 = SPI_SW_MISO_PIN_1;
        SPI_SW_SCK_PIN_1 = 0;
        // bit4
        SPI_SW_MOSI_PIN_1 = SPI_DATA_BIT_4;
        SPI_SW_SCK_PIN_1 = 1;
        SPI_DATA_BIT_4 = SPI_SW_MISO_PIN_1;
        SPI_SW_SCK_PIN_1 = 0;
        // bit3
        SPI_SW_MOSI_PIN_1 = SPI_DATA_BIT_3;
        SPI_SW_SCK_PIN_1 = 1;
        SPI_DATA_BIT_3 = SPI_SW_MISO_PIN_1;
        SPI_SW_SCK_PIN_1 = 0;
        // bit2
        SPI_SW_MOSI_PIN_1 = SPI_DATA_BIT_2;
        SPI_SW_SCK_PIN_1 = 1;
        SPI_DATA_BIT_2 = SPI_SW_MISO_PIN_1;
        SPI_SW_SCK_PIN_1 = 0;
        // bit1
        SPI_SW_MOSI_PIN_1 = SPI_DATA_BIT_1;
        SPI_SW_SCK_PIN_1 = 1;
        SPI_DATA_BIT_1 = SPI_SW_MISO_PIN_1;
        SPI_SW_SCK_PIN_1 = 0;
        // bit0
        SPI_SW_MOSI_PIN_1 = SPI_DATA_BIT_0;
        SPI_SW_SCK_PIN_1 = 1;
        SPI_DATA_BIT_0 = SPI_SW_MISO_PIN_1;
        SPI_SW_SCK_PIN_1 = 0;
        input = SPI_DATA_BIT_ALL;
#else
        for (i = 8; i > 0; i--)
        {
            SPI_SW_MOSI_PIN_1 = (input & 0x80);
            input = (input << 1);
            SPI_SW_SCK_PIN_1 = 1;
            input |= SPI_SW_MISO_PIN_1;
            SPI_SW_SCK_PIN_1 = 0;
        }
#endif
        break;
        /* 在此添加其他引脚组 */
    default:
#if (USE_HW_SPI == ENABLE)
        SPI_HW_Inti(Group_num);
        SPI_HW_RorW_Byte(Group_num, input);
#endif
        break;
    }
    return input;
}
#endif
