#include "SYS.h"
#include "MY_STUDIO.h"

//m^n����
u32 M_Pow_N(u8 m, u8 n)
{
    u32 result = 1;
    while (n--)
    {
        result *= m;
    }
    return result;
}
//����תΪ�ַ���
void Num32_to_STR(s32 dat, s8 *str) //�з�������ת��Ϊ�ַ�����-21 4748 3647~21 4748 3647��
{
    s8 temp[12];
    u8 i, j = 0;

    i = 0;
    if (dat < 0)
    {
        temp[i] = '-';
        i = 1;
        dat = (-1) * dat;
    }
    else
    {
        temp[i] = '+';
        i = 1;
    }

    while (dat)
    {
        temp[i] = dat % 10 + 0x30;
        i++;
        dat /= 10;
    }
    j = i;
    str[0] = temp[0];
    for (i = 0; i < j; i++)
    {
        str[i + 1] = temp[j - i - 1];
    }
    if (!i)
    {
        str[i++] = '0';
    }
    str[i] = 0;
}
void NumU32_to_STR(u32 dat, s8 *str) //�޷�������ת��Ϊ�ַ�����0~42 9496 7295��
{
    s8 temp[12];
    u8 i, j = 0;

    i = 0;
    while (dat)
    {
        temp[i] = dat % 10 + 0x30;
        i++;
        dat /= 10;
    }
    j = i;
    for (i = 0; i < j; i++)
    {
        str[i] = temp[j - i - 1];
    }
    if (!i)
    {
        str[i++] = '0';
    }
    str[i] = 0;
}