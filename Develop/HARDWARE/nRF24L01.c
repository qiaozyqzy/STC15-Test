/*===========================================================================
* ��ַ ��http://yhmcu.taobao.com/   http://www.cdebyte.com/                 *
* ���� ������  ԭ �ں͵��ӹ�����  �� �ڰ��ص��ӿƼ����޹�˾                 * 
* �ʼ� ��yihe_liyong@126.com                                                *
* �绰 ��18615799380                                                        *
============================================================================*/

#include "nRF24L01.h"
#include "SYS.h" 
#include "nRF24L01_UI.h"
// extern u8 L01_SPI_RorW_Byte(u8 input); 
/*===========================================================================
* ���� ��L01_ReadSingleReg() => ��ȡһ���Ĵ�����ֵ                          * 
* ���� ��Addr����ȡ�ļĴ�����ַ                                             * 
* ��� ��������ֵ                                                           * 
============================================================================*/
u8 L01_ReadSingleReg(u8 Addr)
{
    u8 btmp;

    L01_CSN_LOW();
    L01_SPI_RorW_Byte(LO1_SPI_NUM,R_REGISTER | Addr);
    btmp = L01_SPI_RorW_Byte(LO1_SPI_NUM,0xFF);
    L01_CSN_HIGH();

    return (btmp);
}

/*===========================================================================
* ���� ��L01_WriteSingleReg() => д���ݵ�һ���Ĵ���                         * 
* ���� ��Addr��д��Ĵ����ĵ�ַ��Value����д���ֵ                          * 
============================================================================*/
void L01_WriteSingleReg(u8 Addr, u8 Value)
{
    L01_CSN_LOW();
    L01_SPI_RorW_Byte(LO1_SPI_NUM,W_REGISTER | Addr);
    L01_SPI_RorW_Byte(LO1_SPI_NUM,Value);
    L01_CSN_HIGH();
}

/*===========================================================================
* ���� ��L01_WriteMultiReg() => д���ݵ�����Ĵ���                          * 
* ���� ��StartAddr,д��Ĵ������׵�ַ��pBuff,ָ���д���ֵ��Length,����    * 
============================================================================*/
void L01_WriteMultiReg(u8 StartAddr, u8 *pBuff, u8 Length)
{
    u8 i;

    L01_CSN_LOW();
    L01_SPI_RorW_Byte(LO1_SPI_NUM,W_REGISTER | StartAddr);
    for (i = 0; i < Length; i++)
    {
        L01_SPI_RorW_Byte(LO1_SPI_NUM,*(pBuff + i));
    }
    L01_CSN_HIGH();
}

/*===========================================================================
* ���� ��L01_FlushTX() => ��λTX FIFOָ��                                   * 
============================================================================*/
void L01_FlushTX(void)
{
    L01_CSN_LOW();
    L01_SPI_RorW_Byte(LO1_SPI_NUM,FLUSH_TX);
    L01_CSN_HIGH();
}

/*===========================================================================
* ���� ��L01_FlushRX() => ��λRX FIFOָ��                                   *
============================================================================*/
void L01_FlushRX(void)
{
    L01_CSN_LOW();
    L01_SPI_RorW_Byte(LO1_SPI_NUM,FLUSH_RX);
    L01_CSN_HIGH();
}

u8 L01_ReadStatusReg(void)
{
    u8 Status;
    L01_CSN_LOW();
    Status = L01_SPI_RorW_Byte(LO1_SPI_NUM,R_REGISTER + L01REG_STATUS);
    L01_CSN_HIGH();
    return (Status);
}

/*===========================================================================
* ���� ��L01_ClearIRQ() => ����ж�                                         * 
* ���� ��IRQ_Source����Ҫ������ж�Դ                                       * 
============================================================================*/
void L01_ClearIRQ(u8 IRQ_Source)
{
    u8 btmp = 0;

    IRQ_Source &= (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT);
    btmp = L01_ReadStatusReg();

    L01_CSN_LOW();
    L01_SPI_RorW_Byte(LO1_SPI_NUM,W_REGISTER + L01REG_STATUS);
    L01_SPI_RorW_Byte(LO1_SPI_NUM,IRQ_Source | btmp);
    L01_CSN_HIGH();

    L01_ReadStatusReg();
}

/*===========================================================================
* ���� ��L01_ReadIRQSource() => ��ȡ�ж�                                    *         
* ��� ���������ж�Դ                                                       * 
============================================================================*/
u8 L01_ReadIRQSource(void)
{
    return (L01_ReadStatusReg() & ((1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT)));
}

/*===========================================================================
* ���� ��L01_ReadTopFIFOWidth() => ��ȡFIFO���ݿ��                         * 
============================================================================*/
u8 L01_ReadTopFIFOWidth(void)
{
    u8 btmp;

    L01_CSN_LOW();
    L01_SPI_RorW_Byte(LO1_SPI_NUM,R_RX_PL_WID);
    btmp = L01_SPI_RorW_Byte(LO1_SPI_NUM,0xFF);
    L01_CSN_HIGH();

    return (btmp);
}

/*===========================================================================
* ���� ��L01_ReadRXPayload() => ��ȡ���յ�������                            * 
* ���� ��pBuff��ָ���յ�������                                              * 
* ��� �����ݳ���                                                           * 
============================================================================*/
u8 L01_ReadRXPayload(u8 *pBuff)
{
    u8 width, PipeNum;
    PipeNum = (L01_ReadSingleReg(L01REG_STATUS) >> 1) & 0x07;
    width = L01_ReadTopFIFOWidth();

    L01_CSN_LOW();
    L01_SPI_RorW_Byte(LO1_SPI_NUM,R_RX_PAYLOAD);
    for (PipeNum = 0; PipeNum < width; PipeNum++)
    {
        *(pBuff + PipeNum) = L01_SPI_RorW_Byte(LO1_SPI_NUM,0xFF);
    }
    L01_CSN_HIGH();
    L01_FlushRX();
    return (width);
}

/*===========================================================================
* ���� ��L01_WriteTXPayload_Ack() => д���ݵ�TXFIFO(��ACK����)              * 
* ���� ��pBuff��ָ���д������ݣ�nBytes��д�����ݵĳ���                    * 
============================================================================*/
void L01_WriteTXPayload_Ack(u8 *pBuff, u8 nBytes)
{
    u8 btmp;
    u8 length = (nBytes > 32) ? 32 : nBytes;

    L01_FlushTX();
    L01_CSN_LOW();
    L01_SPI_RorW_Byte(LO1_SPI_NUM,W_TX_PAYLOAD);
    for (btmp = 0; btmp < length; btmp++)
    {
        L01_SPI_RorW_Byte(LO1_SPI_NUM,*(pBuff + btmp));
    }
    L01_CSN_HIGH();
}

/*===========================================================================
* ���� ��L01_WriteTXPayload_Ack() => д���ݵ�TXFIFO(����ACK����)            * 
* ���� ��Data��ָ���д������ݣ�Data_Length��д�����ݵĳ���                * 
============================================================================*/
void L01_WriteTXPayload_NoAck(u8 *Data, u8 Data_Length)
{
    if ((Data_Length > 32) || (Data_Length == 0))
    {
        return;
    }

    L01_CSN_LOW();
    L01_SPI_RorW_Byte(LO1_SPI_NUM,W_TX_PAYLOAD_NOACK);
    while (Data_Length--)
    {
        L01_SPI_RorW_Byte(LO1_SPI_NUM,*Data++);
    }
    L01_CSN_HIGH();
}

/*===========================================================================
* ���� ��L01_SetTXAddr() => ���÷��������ַ                                * 
* ���� ��pAddrָ����Ҫ���õĵ�ַ���ݣ�Addr_Length����ַ����                 * 
============================================================================*/
void L01_SetTXAddr(u8 *pAddr, u8 Addr_Length)
{
    u8 Length = (Addr_Length > 5) ? 5 : Addr_Length;
    L01_WriteMultiReg(L01REG_TX_ADDR, pAddr, Length);
}

/*===========================================================================
* ���� ��L01_SetRXAddr() => ���ý��������ַ                                * 
* ���� ��PipeNum���ܵ��ţ�pAddrָ����Ҫ���õ�ַ���ݣ�Addr_Length����ַ����  * 
============================================================================*/
void L01_SetRXAddr(u8 PipeNum, u8 *pAddr, u8 Addr_Length)
{
    u8 Length = (Addr_Length > 5) ? 5 : Addr_Length;
    u8 pipe = (PipeNum > 5) ? 5 : PipeNum;

    L01_WriteMultiReg(L01REG_RX_ADDR_P0 + pipe, pAddr, Length);
}

/*===========================================================================
* ���� ��L01_SetSpeed() => ����L01����                                      * 
* ���� ��speed��=SPD_250K(250K), =SPD_1M(1M), =SPD_2M(2M)                   * 
============================================================================*/
void L01_SetSpeed(u8 speed)
{
    u8 btmp = L01_ReadSingleReg(L01REG_RF_SETUP);

    btmp &= ~((1 << 5) | (1 << 3));

    switch (speed)
    {
    case SPD_250K:
        btmp |= (1 << 5);
        break; // 250K
    case SPD_1M:
        btmp &= ~((1 << 5) | (1 << 3));
        break; // 1M
    case SPD_2M:
        btmp |= (1 << 3);
        break; // 2M
    default:
        break;
    }
    L01_WriteSingleReg(L01REG_RF_SETUP, btmp);
}

/*===========================================================================
* ���� ��L01_SetPower() => ����L01����                                      * 
* ���� ��power, =P_F18DBM(18DB),=P_F12DBM(12DB),=P_F6DBM(6DB),=P_0DBM(0DB)  *
============================================================================*/
void L01_SetPower(u8 power)
{
    u8 btmp = L01_ReadSingleReg(L01REG_RF_SETUP) & ~0x07;

    switch (power)
    {
    case P_F18DBM:
        btmp |= PWR_18DB;
        break; // 18DBM
    case P_F12DBM:
        btmp |= PWR_12DB;
        break; // 12DBM
    case P_F6DBM:
        btmp |= PWR_6DB;
        break; // 6DBM
    case P_0DBM:
        btmp |= PWR_0DB;
        break; // 0DBM
    default:
        break;
    }
    L01_WriteSingleReg(L01REG_RF_SETUP, btmp);
}

/*===========================================================================
* ���� ��L01_WriteHoppingPoint() => ����L01Ƶ��                             * 
* ���� ��FreqPoint�������õ�Ƶ��                                            * 
============================================================================*/
void L01_WriteHoppingPoint(u8 FreqPoint)
{
    L01_WriteSingleReg(L01REG_RF_CH, FreqPoint & 0x7F);
}

/*===========================================================================
* ���� ��L01_SetTRMode() => ����L01ģʽ                                     * 
* ���� ��mode��=TX_MODE, TX mode; =RX_MODE, RX mode                         * 
============================================================================*/
void L01_SetTRMode(u8 mode)
{
    u8 controlreg = L01_ReadSingleReg(L01REG_CONFIG);
    if (mode == TX_MODE)
    {
        controlreg &= ~(1 << PRIM_RX);
    }
    else if (mode == RX_MODE)
    {
        controlreg |= (1 << PRIM_RX);
    }

    L01_WriteSingleReg(L01REG_CONFIG, controlreg);
}

/*===========================================================================
* ���� ��L01_Init() => ��ʼ��L01                                             * 
============================================================================*/
void L01_Init(void)
{

    L01_CE_LOW();
    L01_ClearIRQ(IRQ_ALL);

    // ʹ�ܹܵ�0��̬������
    L01_WriteSingleReg(L01REG_DYNPD, (1 << 0));
    L01_WriteSingleReg(L01REG_FEATRUE, 0x06);
    L01_ReadSingleReg(L01REG_DYNPD);
    L01_ReadSingleReg(L01REG_FEATRUE);

    L01_WriteSingleReg(L01REG_CONFIG, (1 << EN_CRC) | (1 << PWR_UP));
    L01_WriteSingleReg(L01REG_EN_AA, (1 << ENAA_P0));    // �Զ�Ӧ�𣨹ܵ�0��
    L01_WriteSingleReg(L01REG_EN_RXADDR, (1 << ERX_P0)); // ʹ�ܽ��գ��ܵ�0��
    L01_WriteSingleReg(L01REG_SETUP_AW, AW_5BYTES);      // ��ַ��� 5byte
    L01_WriteSingleReg(L01REG_RETR, ARD_4000US | (REPEAT_CNT & 0x0F));

    L01_WriteSingleReg(L01REG_RF_CH, 60); // ��ʼ��Ƶ��
    L01_WriteSingleReg(L01REG_RF_SETUP, 0x26);
    L01_SetTXAddr(&L01_TX_Addr[0], 5);    // ���õ�ַ�����ͣ�
    L01_SetRXAddr(0, &L01_RX_Addr[0], 5); // ���õ�ַ�����գ�

    L01_WriteHoppingPoint(77); // ����Ƶ��
    L01_SetSpeed(SPD_250K);    // ���ÿ���Ϊ250K
}

/*===========================================================================
-----------------------------------�ļ�����----------------------------------
===========================================================================*/
