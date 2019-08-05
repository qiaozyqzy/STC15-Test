#ifndef __I2C_H_
#define __I2C_H_

#include "SYS.h"
#include "I2C.H"

// I2C通信组号
#define I2C_PIN_Group_0 0
#define I2C_0_SDA P00 //IIC_1数据引脚定义
#define I2C_0_SCL P01 //IIC_1时钟引脚定义
#define I2C_PIN_Group_1 1
#define I2C_1_SDA P02 //IIC_2数据引脚定义
#define I2C_1_SCL P03 //IIC_2时钟引脚定义
#define I2C_PIN_Group_2 2
// 设置I2C通信引脚SDA
// u8 where：引脚组号； s8 level：电平值（0，1为输入电平，-1为读取电平）
// 返回值：正常：在读取电平模式下为对应组号的电平，写模式下恒为：OK；错误：0xff（引脚组号溢出）；
u8 I2C_SDA_Pin(u8 where, s8 level);
// 设置I2C通信引脚SDA
// u8 where：引脚组号； s8 level：电平值（0，1为输入电平）
// 返回值：正常：OK；错误：0xff（引脚组号溢出）；
u8 I2C_SCL_Pin(u8 where, s8 level);

//I2C起始信号
void Start_I2C(u8 Pin_num);
//I2C停止信号
void Stop_I2C(u8 Pin_num);
//I2C发送应答信号
//入口参数:ack (0:ACK 1:NAK)
void I2C_SendACK(u8 Pin_num, BOOL ack);
//I2C接收应答信号
BOOL I2C_RecvACK(u8 Pin_num);
//向I2C总线发送一个字节数据
BOOL I2C_SendByte(u8 Pin_num, u8 dat);
//从I2C总线接收一个字节数据
u8 I2C_RecvByte(u8 Pin_num);
#endif