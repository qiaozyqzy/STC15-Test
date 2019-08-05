#include "SYS.h"
#include <INTRINS.H>
#include "I2C.H"
#include "delay.h"

// ����I2Cͨ������SDA
// u8 where��������ţ� s8 level����ƽֵ��0��1Ϊ�����ƽ��-1Ϊ��ȡ��ƽ��
// ����ֵ���������ڶ�ȡ��ƽģʽ��Ϊ��Ӧ��ŵĵ�ƽ��дģʽ�º�Ϊ��OK������0xff����������������
u8 I2C_SDA_Pin(u8 where, s8 level)
{
    u8 pin_level = 0;
    if (level < 0)
    {
        switch (where)
        {
        case I2C_PIN_Group_0 :
            pin_level = I2C_0_SDA;
            break;
        case I2C_PIN_Group_1:
            pin_level = I2C_1_SDA;
            break;

        default:
            return 0xff;
            break;
        }
    }
    else
    {
        switch (where)
        {
        case I2C_PIN_Group_0:
            I2C_0_SDA = level;
            break;
        case I2C_PIN_Group_1:
            I2C_1_SDA = level;
            break;

        default:
            return 0xff;
            break;
        }
    }
    return pin_level;
}
// ����I2Cͨ������SDA
// u8 where��������ţ� s8 level����ƽֵ��0��1Ϊ�����ƽ��
// ����ֵ��������OK������0xff����������������
u8 I2C_SCL_Pin(u8 where, s8 level)
{
    if (level < 0)
    {
        return 0xff;
    }
    else
    {
        switch (where)
        {
        case I2C_PIN_Group_0:
            I2C_0_SCL = level;
            break;
        case I2C_PIN_Group_1:
            I2C_1_SCL = level;
            break;

        default:
            return 0xff;
            break;
        }
    }
    return OK;
}

//I2C��ʼ�ź�
void Start_I2C(u8 Pin_num)
{
    I2C_SDA_Pin(Pin_num, 1); //����������
    _nop_();
    I2C_SCL_Pin(Pin_num, 1); //����ʱ����
    delay_us(5);             //��ʱ
    I2C_SDA_Pin(Pin_num, 0); //�����½���
    delay_us(5);             //��ʱ
    I2C_SCL_Pin(Pin_num, 0); //����ʱ����
    _nop_();
    _nop_();
}
//I2Cֹͣ�ź�
void Stop_I2C(u8 Pin_num)
{
    I2C_SDA_Pin(Pin_num, 0); //����������
    _nop_();
    I2C_SCL_Pin(Pin_num, 1); //����ʱ����
    delay_us(5);             //��ʱ
    I2C_SDA_Pin(Pin_num, 1); //����������
    delay_us(5);             //��ʱ
}
//I2C����Ӧ���ź�
//��ڲ���:ack (0:ACK 1:NAK)
void I2C_SendACK(u8 Pin_num, BOOL ack)
{
    I2C_SDA_Pin(Pin_num, ack); //дӦ���ź�
    I2C_SCL_Pin(Pin_num, 1);   //����ʱ����
    delay_us(5);               //��ʱ
    I2C_SCL_Pin(Pin_num, 0);   //����ʱ����
    delay_us(5);               //��ʱ
}
//I2C����Ӧ���ź�
BOOL I2C_RecvACK(u8 Pin_num)
{
    _nop_();
    _nop_();
    I2C_SCL_Pin(Pin_num, 1);       //����ʱ����
    delay_us(5);                   //��ʱ
    CY = I2C_SDA_Pin(Pin_num, -1); //��Ӧ���ź�
    I2C_SCL_Pin(Pin_num, 0);       //����ʱ����
    delay_us(5);                   //��ʱ
    return CY;
}
//��I2C���߷���һ���ֽ�����
BOOL I2C_SendByte(u8 Pin_num, u8 dat)
{
    u8 i;
    for (i = 0; i < 8; i++) //8λ������
    {
        dat <<= 1;                //�Ƴ����ݵ����λ
        I2C_SDA_Pin(Pin_num, CY); //�����ݿ�
        _nop_();
        I2C_SCL_Pin(Pin_num, 1); //����ʱ����
        delay_us(5);             //��ʱ
        I2C_SCL_Pin(Pin_num, 0); //����ʱ����
        delay_us(5);             //��ʱ
    }
    return I2C_RecvACK(0);
}
//��I2C���߽���һ���ֽ�����
u8 I2C_RecvByte(u8 Pin_num)
{
    u8 i;
    u8 dat = 0;
    I2C_SDA_Pin(Pin_num, 1); //ʹ���ڲ�����,׼����ȡ����,
    for (i = 0; i < 8; i++)  //8λ������
    {
        _nop_();
        dat <<= 1;
        I2C_SCL_Pin(Pin_num, 1);         //����ʱ����
        delay_us(5);                     //��ʱ
        dat |= I2C_SDA_Pin(Pin_num, -1); //������
        I2C_SCL_Pin(Pin_num, 0);         //����ʱ����
        delay_us(5);                     //��ʱ
    }
    return dat;
}