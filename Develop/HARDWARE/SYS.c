#include "SYS.h"

void SYS_RST(void)
{
    IAP_CONTR = 0x20; //�����λ,ϵͳ���´��û���������ʼ���г���
    // IAP_CONTR = 0x60; //�����λ,ϵͳ���´�ISP��������ʼ���г���
}