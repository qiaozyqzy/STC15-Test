#include "SYS.h"
#include "GPIO.h"
#include <intrins.h>

void GPIO_Init()
{
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    P6M0 = 0x00;
    P6M1 = 0x00;
    P7M0 = 0x00;
    P7M1 = 0x00;
    P1 = 0xff;
    P2 = 0xff;
    P3 = 0xff;
    P4 = 0xff;
    P5 = 0xff;
    P6 = 0xff;
    P7 = 0xff;
}
void Set_Pin_Group_Mode(u8 Pin_Name, u8 Pin_Mode)
{
    switch (Pin_Name)
    {
    case 0:
        P0M0 = 0XFF * (Pin_Mode % 16);
        P0M1 = 0XFF * (Pin_Mode / 16);
        break;
    case 1:
        P1M0 = 0XFF * (Pin_Mode % 16);
        P1M1 = 0XFF * (Pin_Mode / 16);
        break;
    case 2:
        P1M0 = 0XFF * (Pin_Mode % 16);
        P2M1 = 0XFF * (Pin_Mode / 16);
        break;
    case 3:
        P3M0 = 0XFF * (Pin_Mode % 16);
        P3M1 = 0XFF * (Pin_Mode / 16);
        break;
    case 4:
        P4M0 = 0XFF * (Pin_Mode % 16);
        P4M1 = 0XFF * (Pin_Mode / 16);
        break;
    case 5:
        P5M0 = 0XFF * (Pin_Mode % 16);
        P5M1 = 0XFF * (Pin_Mode / 16);
        break;
    case 6:
        P6M0 = 0XFF * (Pin_Mode % 16);
        P6M1 = 0XFF * (Pin_Mode / 16);
        break;
    case 7:
        P7M0 = 0XFF * (Pin_Mode % 16);
        P7M1 = 0XFF * (Pin_Mode / 16);
        break;
    }
}

void Set_Single_Pin_Mode(u8 Pin_Name, u8 Pin_Mode)
{
    u8 Pin_Name_H, Pin_Name_L;
    Pin_Name_H = (Pin_Name / 16);
    Pin_Name_L = (Pin_Name % 16);
    switch (Pin_Name_H)
    {
    case 0:
        P0M0 = P0M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P0M1 = P0M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        break;
    case 1:
        P1M0 = P1M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P1M1 = P1M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        break;
    case 2:
        P2M0 = P2M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P2M1 = P2M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        break;
    case 3:
        P3M0 = P3M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P3M1 = P3M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        break;
    case 4:
        P4M0 = P4M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P4M1 = P4M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        break;
    case 5:
        P5M0 = P5M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P5M1 = P5M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        break;
    case 6:
        P6M0 = P6M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P6M1 = P6M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        break;
    case 7:
        P7M0 = P7M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P7M1 = P7M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        break;
    }
}

void Set_Pin_Group(u8 Pin_Name, u8 Pin_Mode, u8 Pin_State)
{
    switch (Pin_Name)
    {
    case 0:
        P0M0 = 0XFF * (Pin_Mode % 16);
        P0M1 = 0XFF * (Pin_Mode / 16);
        P0 = Pin_State;
        _nop_();
        _nop_();
        break;
    case 1:
        P1M0 = 0XFF * (Pin_Mode % 16);
        P1M1 = 0XFF * (Pin_Mode / 16);
        P1 = Pin_State;
        _nop_();
        _nop_();
        break;
    case 2:
        P1M0 = 0XFF * (Pin_Mode % 16);
        P2M1 = 0XFF * (Pin_Mode / 16);
        P2 = Pin_State;
        _nop_();
        _nop_();
        break;
    case 3:
        P3M0 = 0XFF * (Pin_Mode % 16);
        P3M1 = 0XFF * (Pin_Mode / 16);
        P3 = Pin_State;
        _nop_();
        _nop_();
        break;
    case 4:
        P4M0 = 0XFF * (Pin_Mode % 16);
        P4M1 = 0XFF * (Pin_Mode / 16);
        P4 = Pin_State;
        _nop_();
        _nop_();
        break;
    case 5:
        P5M0 = 0XFF * (Pin_Mode % 16);
        P5M1 = 0XFF * (Pin_Mode / 16);
        P5 = Pin_State;
        _nop_();
        _nop_();
        break;
    case 6:
        P6M0 = 0XFF * (Pin_Mode % 16);
        P6M1 = 0XFF * (Pin_Mode / 16);
        P6 = Pin_State;
        _nop_();
        _nop_();
        break;
    case 7:
        P7M0 = 0XFF * (Pin_Mode % 16);
        P7M1 = 0XFF * (Pin_Mode / 16);
        P7 = Pin_State;
        _nop_();
        _nop_();
        break;
    }
}

void Set_Single_Pin(u8 Pin_Name, u8 Pin_Mode, u8 Pin_State)
{
    u8 Pin_Name_H, Pin_Name_L;
    Pin_Name_H = (Pin_Name / 16);
    Pin_Name_L = (Pin_Name % 16);
    switch (Pin_Name_H)
    {
    case 0:
        P0M0 = P0M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P0M1 = P0M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        P0 = P0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * Pin_State;
        _nop_();
        _nop_();
        break;
    case 1:
        P1M0 = P1M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P1M1 = P1M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        P1 = P1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * Pin_State;
        _nop_();
        _nop_();
        break;
    case 2:
        P2M0 = P2M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P2M1 = P2M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        P2 = P2 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * Pin_State;
        _nop_();
        _nop_();
        break;
    case 3:
        P3M0 = P3M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P3M1 = P3M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        P3 = P3 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * Pin_State;
        _nop_();
        _nop_();
        break;
    case 4:
        P4M0 = P4M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P4M1 = P4M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        P4 = P4 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * Pin_State;
        _nop_();
        _nop_();
        break;
    case 5:
        P5M0 = P5M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P5M1 = P5M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        P5 = P5 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * Pin_State;
        _nop_();
        _nop_();
        break;
    case 6:
        P6M0 = P6M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P6M1 = P6M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        P6 = P6 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * Pin_State;
        _nop_();
        _nop_();
        break;
    case 7:
        P7M0 = P7M0 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode % 16);
        P7M1 = P7M1 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * (Pin_Mode / 16);
        P7 = P7 & (~(0X01 << Pin_Name_L)) + (0X01 << Pin_Name_L) * Pin_State;
        _nop_();
        _nop_();
        break;
    }
}
