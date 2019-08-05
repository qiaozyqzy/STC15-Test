#include "nRF24L01_UI.h"
#include "delay.h"

uc8 L01_RX_Addr[5] = {L01_RX_Addr_SET_V};
uc8 L01_TX_Addr[5] = {L01_TX_Addr_SET_V};
// 初始化RF芯片
void RF_Init(void)
{
    L01_Init(); // 初始化L01寄存器

    L01_SetTRMode(RX_MODE); // 接收模式
    L01_FlushRX();          // 复位接收FIFO指针
    L01_FlushTX();          // 复位发送FIFO指针
    L01_ClearIRQ(IRQ_ALL);  // 清除所有中断
    L01_CE_HIGH();          // CE = 1, 启动接收
}
// 接收数据
E_Code RF_Recv(u8 *recv_dat, u8 *len)
{
    E_Code ERR;
    if (0 == L01_IRQ_READ()) // 检测无线模块是否产生接收中断
    {
        if (L01_ReadIRQSource() & (1 << RX_DR)) // 检测无线模块是否接收到数据
        {

            len[0] = L01_ReadRXPayload(&recv_dat[0]); // 读取接收到的数据长度和数据内容
#if (RF_DATA_Check == ENABLE)
            if (len[0] <= Send_Len_MAX) // 判断接收数据是否正确
            {
                ERR = OK;
            }
            else
            {
                ERR = RF_R_Wrong_DAT;
            }
#else
            ERR = OK;
#endif
        }
        else
        {
            ERR = RF_R_NO_DAT;
        }
        L01_FlushRX();         // 复位接收FIFO指针
        L01_ClearIRQ(IRQ_ALL); // 清除中断
    }
    else
    {
        ERR = RF_R_NO_IRQ;
    }
    return ERR;
}
// 发送数据
E_Code RF_Send(u8 *Send_dat, u8 *len)
{
    E_Code ERR = OK;
    L01_CE_LOW();           // CE = 0, 关闭发送
    L01_SetTRMode(TX_MODE); // 设置为发送模式
    L01_WriteTXPayload_NoAck(&Send_dat[0], len[0]);
    L01_CE_HIGH(); // CE = 1, 启动发送
    delay_ms(250);
    // 等待发送中断产生
    while (0 != L01_IRQ_READ())
    {
    }
    while (0 == L01_ReadIRQSource())
    {
    }
    L01_CE_LOW(); // CE = 0, 关闭发送

    L01_FlushRX();          // 复位接收FIFO指针
    L01_FlushTX();          // 复位发送FIFO指针
    L01_ClearIRQ(IRQ_ALL);  // 清除中断
    L01_SetTRMode(RX_MODE); // 接收模式
    L01_CE_HIGH();          // 启动接收

    return ERR;
}
// 设置模块为接收模式
void RF_Recv_Mode(void)
{
    L01_CE_LOW();           // CE = 0, 关闭发送
    L01_FlushRX();          // 复位接收FIFO指针
    L01_ClearIRQ(IRQ_ALL);  // 清除中断
    L01_SetTRMode(RX_MODE); // 接收模式
    L01_CE_HIGH();          // 启动接收
}
// 设置模块为发送模式
void RF_Send_Mode(void)
{
    L01_CE_LOW();           // CE = 0, 关闭发送
    L01_FlushTX();          // 复位发送FIFO指针
    L01_ClearIRQ(IRQ_ALL);  // 清除中断
    L01_SetTRMode(TX_MODE); // 设置为发送模式
    // L01_CE_HIGH(); // CE = 1, 启动发送
}
