#ifndef __I2C_H_
#define __I2C_H_

#include "SYS.h"
#include "I2C.H"

// I2Cͨ�����
#define I2C_PIN_Group_0 0
#define I2C_0_SDA P00 //IIC_1�������Ŷ���
#define I2C_0_SCL P01 //IIC_1ʱ�����Ŷ���
#define I2C_PIN_Group_1 1
#define I2C_1_SDA P02 //IIC_2�������Ŷ���
#define I2C_1_SCL P03 //IIC_2ʱ�����Ŷ���
#define I2C_PIN_Group_2 2
// ����I2Cͨ������SDA
// u8 where��������ţ� s8 level����ƽֵ��0��1Ϊ�����ƽ��-1Ϊ��ȡ��ƽ��
// ����ֵ���������ڶ�ȡ��ƽģʽ��Ϊ��Ӧ��ŵĵ�ƽ��дģʽ�º�Ϊ��OK������0xff����������������
u8 I2C_SDA_Pin(u8 where, s8 level);
// ����I2Cͨ������SDA
// u8 where��������ţ� s8 level����ƽֵ��0��1Ϊ�����ƽ��
// ����ֵ��������OK������0xff����������������
u8 I2C_SCL_Pin(u8 where, s8 level);

//I2C��ʼ�ź�
void Start_I2C(u8 Pin_num);
//I2Cֹͣ�ź�
void Stop_I2C(u8 Pin_num);
//I2C����Ӧ���ź�
//��ڲ���:ack (0:ACK 1:NAK)
void I2C_SendACK(u8 Pin_num, BOOL ack);
//I2C����Ӧ���ź�
BOOL I2C_RecvACK(u8 Pin_num);
//��I2C���߷���һ���ֽ�����
BOOL I2C_SendByte(u8 Pin_num, u8 dat);
//��I2C���߽���һ���ֽ�����
u8 I2C_RecvByte(u8 Pin_num);
#endif