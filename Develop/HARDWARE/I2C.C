#include "SYS.h"
#include <INTRINS.H>
#include "I2C.H"
#include "delay.h"

// 设置I2C通信引脚SDA
// u8 where：引脚组号； s8 level：电平值（0，1为输入电平，-1为读取电平）
// 返回值：正常：在读取电平模式下为对应组号的电平，写模式下恒为：OK；错误：0xff（引脚组号溢出）；
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
// 设置I2C通信引脚SDA
// u8 where：引脚组号； s8 level：电平值（0，1为输入电平）
// 返回值：正常：OK；错误：0xff（引脚组号溢出）；
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

//I2C起始信号
void Start_I2C(u8 Pin_num)
{
    I2C_SDA_Pin(Pin_num, 1); //拉高数据线
    _nop_();
    I2C_SCL_Pin(Pin_num, 1); //拉高时钟线
    delay_us(5);             //延时
    I2C_SDA_Pin(Pin_num, 0); //产生下降沿
    delay_us(5);             //延时
    I2C_SCL_Pin(Pin_num, 0); //拉低时钟线
    _nop_();
    _nop_();
}
//I2C停止信号
void Stop_I2C(u8 Pin_num)
{
    I2C_SDA_Pin(Pin_num, 0); //拉低数据线
    _nop_();
    I2C_SCL_Pin(Pin_num, 1); //拉高时钟线
    delay_us(5);             //延时
    I2C_SDA_Pin(Pin_num, 1); //产生上升沿
    delay_us(5);             //延时
}
//I2C发送应答信号
//入口参数:ack (0:ACK 1:NAK)
void I2C_SendACK(u8 Pin_num, BOOL ack)
{
    I2C_SDA_Pin(Pin_num, ack); //写应答信号
    I2C_SCL_Pin(Pin_num, 1);   //拉高时钟线
    delay_us(5);               //延时
    I2C_SCL_Pin(Pin_num, 0);   //拉低时钟线
    delay_us(5);               //延时
}
//I2C接收应答信号
BOOL I2C_RecvACK(u8 Pin_num)
{
    _nop_();
    _nop_();
    I2C_SCL_Pin(Pin_num, 1);       //拉高时钟线
    delay_us(5);                   //延时
    CY = I2C_SDA_Pin(Pin_num, -1); //读应答信号
    I2C_SCL_Pin(Pin_num, 0);       //拉低时钟线
    delay_us(5);                   //延时
    return CY;
}
//向I2C总线发送一个字节数据
BOOL I2C_SendByte(u8 Pin_num, u8 dat)
{
    u8 i;
    for (i = 0; i < 8; i++) //8位计数器
    {
        dat <<= 1;                //移出数据的最高位
        I2C_SDA_Pin(Pin_num, CY); //送数据口
        _nop_();
        I2C_SCL_Pin(Pin_num, 1); //拉高时钟线
        delay_us(5);             //延时
        I2C_SCL_Pin(Pin_num, 0); //拉低时钟线
        delay_us(5);             //延时
    }
    return I2C_RecvACK(0);
}
//从I2C总线接收一个字节数据
u8 I2C_RecvByte(u8 Pin_num)
{
    u8 i;
    u8 dat = 0;
    I2C_SDA_Pin(Pin_num, 1); //使能内部上拉,准备读取数据,
    for (i = 0; i < 8; i++)  //8位计数器
    {
        _nop_();
        dat <<= 1;
        I2C_SCL_Pin(Pin_num, 1);         //拉高时钟线
        delay_us(5);                     //延时
        dat |= I2C_SDA_Pin(Pin_num, -1); //读数据
        I2C_SCL_Pin(Pin_num, 0);         //拉低时钟线
        delay_us(5);                     //延时
    }
    return dat;
}