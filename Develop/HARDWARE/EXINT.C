#include "SYS.h"
#include "EXINT.h"
#include "EXINTConfig.h"

/*-----------------�ⲿ�ж�0--------------------*/
#if (EXINT0_Open)
BOOL EXINT0_Flag = 0;
BOOL EXINT0_State = 0; //1:�������ж� 0:�½����ж�
#endif
#if (EXINT0_Open)
void EXINT0_Init(BOOL inttyp)
{
    EA = 0;
    INT0 = 1;
    IT0 = inttyp; //����INT0���ж����� (1:���½��� 0:�����غ��½���)
    EX0 = 1;      //ʹ��INT0�ж�
    EA = 1;
}
#endif
#if (EXINT0_Open)
void EXINT0_Stop()
{
    EA = 0;
    EX0 = 0;
    EA = 1;
}
#endif
#if (EXINT0_Open)
//�жϷ������
void EXINT_0() interrupt 0 //INT0�ж����
{
    EXINT0_State = INT0; //����INT0�ڵ�״̬, INT0=0(�½���); INT0=1(������)
    EXINT0_Flag = 1;
    //ADD YOUR CODE HERE
}
#endif
/*-----------------�ⲿ�ж�1--------------------*/
#if (EXINT1_Open)
BOOL EXINT1_Flag = 0;
BOOL EXINT1_State = 0; //1:�������ж� 0:�½����ж�
#endif
#if (EXINT1_Open)
void EXINT1_Init(BOOL inttyp)
{
    EA = 0;
    INT1 = 1;
    IT1 = inttyp; //����INT1���ж����� (1:���½��� 0:�����غ��½���)
    EX1 = 1;      //ʹ��INT1�ж�
    EA = 1;
}
#endif
#if (EXINT1_Open)
void EXINT1_Stop()
{
    EA = 0;
    EX1 = 0;
    EA = 1;
}
#endif
#if (EXINT1_Open)
//�жϷ������
void EXINT_1() interrupt 2 //INT1�ж����
{
    EXINT1_State = INT0; //����INT1�ڵ�״̬, INT1=0(�½���); INT0=1(������)
    EXINT1_Flag = 1;
    //ADD YOUR CODE HERE
}
#endif
/*-----------------�ⲿ�ж�2--------------------*/
#if (EXINT2_Open)
BOOL EXINT2_Flag = 0;
#endif
#if (EXINT2_Open)
//�жϷ������
void EXINT_2() interrupt 10 //INT2�ж����
{
    EXINT2_Flag = 1;
    //INT_CLKO &= 0xEF;               //����Ҫ�ֶ�����жϱ�־,���ȹر��ж�,��ʱϵͳ���Զ�����ڲ����жϱ�־
    //INT_CLKO |= 0x10;               //Ȼ���ٿ��жϼ���
    //ADD YOUR CODE HERE
}
#endif
#if (EXINT2_Open)
void EXINT2_Init()
{
    EA = 0;
    INT2 = 1;
    INT_CLKO |= 0x10; //(EX2 = 1)ʹ��INT2�ж�
    EA = 1;
}
#endif
#if (EXINT2_Open)
void EXINT2_Stop()
{
    EA = 0;
    INT_CLKO &= 0xEF; //����Ҫ�ֶ�����жϱ�־,���ȹر��ж�,��ʱϵͳ���Զ�����ڲ����жϱ�־
    EA = 1;
}
#endif
/*-----------------�ⲿ�ж�3--------------------*/
#if (EXINT3_Open)
BOOL EXINT3_Flag = 0;
#endif
#if (EXINT3_Open)
void EXINT3_Init()
{
    EA = 0;
    INT3 = 1;
    INT_CLKO |= 0x20; //(EX3 = 1)ʹ��INT3�ж�
    EA = 1;
}
#endif
#if (EXINT3_Open)
void EXINT3_Stop()
{
    EA = 0;
    INT_CLKO &= 0xDF; //����Ҫ�ֶ�����жϱ�־,���ȹر��ж�,��ʱϵͳ���Զ�����ڲ����жϱ�־
    EA = 1;
}
#endif
#if (EXINT3_Open)
//�жϷ������
void EXINT_3() interrupt 11 //INT3�ж����
{
    EXINT3_Flag = 1;
    //INT_CLKO &= 0xDF;               //����Ҫ�ֶ�����жϱ�־,���ȹر��ж�,��ʱϵͳ���Զ�����ڲ����жϱ�־
    //INT_CLKO |= 0x20;               //Ȼ���ٿ��жϼ���
    //ADD YOUR CODE HERE
}
#endif
/*-----------------�ⲿ�ж�4--------------------*/
#if (EXINT4_Open)
BOOL EXINT4_Flag = 0;
#endif
#if (EXINT4_Open)
void EXINT4_Init()
{
    EA = 0;
    INT4 = 1;
    INT_CLKO |= 0x40; //(EX4 = 1)ʹ��INT4�ж�
    EA = 1;
}
#endif
#if (EXINT4_Open)
void EXINT4_Stop()
{
    EA = 0;
    INT_CLKO &= 0xBF; //����Ҫ�ֶ�����жϱ�־,���ȹر��ж�,��ʱϵͳ���Զ�����ڲ����жϱ�־
    EA = 1;
}
#endif
#if (EXINT4_Open)
//�жϷ������
void EXINT_4() interrupt 16 //INT4�ж����
{
    EXINT4_Flag = 1;
    //INT_CLKO &= 0xBF;               //����Ҫ�ֶ�����жϱ�־,���ȹر��ж�,��ʱϵͳ���Զ�����ڲ����жϱ�־
    //INT_CLKO |= 0x40;               //Ȼ���ٿ��жϼ���
    //ADD YOUR CODE HERE
}
#endif
/*----------------------------------------------------*/
//exint_typ:0:���½��� 1:�����غ��½���)
void EXINT_Init(char exint_num, BOOL exint_typ)
{
    exint_typ = exint_typ;
    switch (exint_num)
    {
#if (EXINT0_Open)
    case EXINT0:
        EXINT0_Init(exint_typ);
        break;
#endif
#if (EXINT1_Open)
    case EXINT1:
        EXINT1_Init(exint_typ);
        break;
#endif
#if (EXINT2_Open)
    case EXINT2:
        EXINT2_Init();
        break;
#endif
#if (EXINT3_Open)
    case EXINT3:
        EXINT3_Init();
        break;
#endif
#if (EXINT4_Open)
    case EXINT4:
        EXINT4_Init();
        break;
#endif
    }
}
void EXINT_Stop(char exint_num)
{
    switch (exint_num)
    {
#if (EXINT0_Open)
    case EXINT0:
        EXINT0_Stop();
        break;
#endif
#if (EXINT1_Open)
    case EXINT1:
        EXINT1_Stop();
        break;
#endif
#if (EXINT2_Open)
    case EXINT2:
        EXINT2_Stop();
        break;
#endif
#if (EXINT3_Open)
    case EXINT3:
        EXINT3_Stop();
        break;
#endif
#if (EXINT4_Open)
    case EXINT4:
        EXINT4_Stop();
        break;
#endif
    }
}