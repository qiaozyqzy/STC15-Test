#include "nRF24L01_UI.h"
#include "delay.h"

uc8 L01_RX_Addr[5] = {L01_RX_Addr_SET_V};
uc8 L01_TX_Addr[5] = {L01_TX_Addr_SET_V};
// ��ʼ��RFоƬ
void RF_Init(void)
{
    L01_Init(); // ��ʼ��L01�Ĵ���

    L01_SetTRMode(RX_MODE); // ����ģʽ
    L01_FlushRX();          // ��λ����FIFOָ��
    L01_FlushTX();          // ��λ����FIFOָ��
    L01_ClearIRQ(IRQ_ALL);  // ��������ж�
    L01_CE_HIGH();          // CE = 1, ��������
}
// ��������
E_Code RF_Recv(u8 *recv_dat, u8 *len)
{
    E_Code ERR;
    if (0 == L01_IRQ_READ()) // �������ģ���Ƿ���������ж�
    {
        if (L01_ReadIRQSource() & (1 << RX_DR)) // �������ģ���Ƿ���յ�����
        {

            len[0] = L01_ReadRXPayload(&recv_dat[0]); // ��ȡ���յ������ݳ��Ⱥ���������
#if (RF_DATA_Check == ENABLE)
            if (len[0] <= Send_Len_MAX) // �жϽ��������Ƿ���ȷ
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
        L01_FlushRX();         // ��λ����FIFOָ��
        L01_ClearIRQ(IRQ_ALL); // ����ж�
    }
    else
    {
        ERR = RF_R_NO_IRQ;
    }
    return ERR;
}
// ��������
E_Code RF_Send(u8 *Send_dat, u8 *len)
{
    E_Code ERR = OK;
    L01_CE_LOW();           // CE = 0, �رշ���
    L01_SetTRMode(TX_MODE); // ����Ϊ����ģʽ
    L01_WriteTXPayload_NoAck(&Send_dat[0], len[0]);
    L01_CE_HIGH(); // CE = 1, ��������
    delay_ms(250);
    // �ȴ������жϲ���
    while (0 != L01_IRQ_READ())
    {
    }
    while (0 == L01_ReadIRQSource())
    {
    }
    L01_CE_LOW(); // CE = 0, �رշ���

    L01_FlushRX();          // ��λ����FIFOָ��
    L01_FlushTX();          // ��λ����FIFOָ��
    L01_ClearIRQ(IRQ_ALL);  // ����ж�
    L01_SetTRMode(RX_MODE); // ����ģʽ
    L01_CE_HIGH();          // ��������

    return ERR;
}
// ����ģ��Ϊ����ģʽ
void RF_Recv_Mode(void)
{
    L01_CE_LOW();           // CE = 0, �رշ���
    L01_FlushRX();          // ��λ����FIFOָ��
    L01_ClearIRQ(IRQ_ALL);  // ����ж�
    L01_SetTRMode(RX_MODE); // ����ģʽ
    L01_CE_HIGH();          // ��������
}
// ����ģ��Ϊ����ģʽ
void RF_Send_Mode(void)
{
    L01_CE_LOW();           // CE = 0, �رշ���
    L01_FlushTX();          // ��λ����FIFOָ��
    L01_ClearIRQ(IRQ_ALL);  // ����ж�
    L01_SetTRMode(TX_MODE); // ����Ϊ����ģʽ
    // L01_CE_HIGH(); // CE = 1, ��������
}
