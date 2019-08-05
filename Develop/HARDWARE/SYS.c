#include "SYS.h"

void SYS_RST(void)
{
    IAP_CONTR = 0x20; //软件复位,系统重新从用户代码区开始运行程序
    // IAP_CONTR = 0x60; //软件复位,系统重新从ISP代码区开始运行程序
}