#ifndef __EXINT_H__
#define __EXINT_H__

#include "SYS.h"
#include "EXINTConfig.h"

#define INT0 P32
#define INT1 P33
#define INT2 P36
#define INT3 P37
#define INT4 P30

//�ⲿ�жϳ�ʼ��
//exint_num:�ⲿ�жϱ�š�exint_typ:�ж�����(0:���½��� 1:�����غ��½���)
extern void EXINT_Init(char exint_num, BOOL exint_typ);
//�ر��ⲿ�ж�
//exint_num:�ⲿ�жϱ��
extern void EXINT_Stop(char exint_num);
/*-----------------�ⲿ�ж�0--------------------*/
#if (EXINT0_Open)
extern BOOL EXINT0_Flag;
extern BOOL EXINT0_State; //1:�������ж� 0:�½����ж�
extern void EXINT0_Init(BOOL inttyp);
extern void EXINT0_Stop();
//�жϷ������-->void EXINT_0() interrupt 0       //INT0�ж����
#endif
/*-----------------�ⲿ�ж�1--------------------*/
#if (EXINT1_Open)
extern BOOL EXINT1_Flag;
extern BOOL EXINT1_State; //1:�������ж� 0:�½����ж�
extern void EXINT1_Init(BOOL inttyp);
extern void EXINT1_Stop();
//�жϷ������-->void EXINT_1() interrupt 2       //INT1�ж����
#endif
/*-----------------�ⲿ�ж�2--------------------*/
#if (EXINT2_Open)
extern BOOL EXINT2_Flag;
extern void EXINT2_Init();
extern void EXINT2_Stop();
//�жϷ������-->void EXINT_2() interrupt 10          //INT2�ж����
#endif
/*-----------------�ⲿ�ж�3--------------------*/
#if (EXINT3_Open)
extern BOOL EXINT3_Flag;
extern void EXINT3_Init();
extern void EXINT3_Stop();
//�жϷ������-->void EXINT_3() interrupt 11          //INT3�ж����
#endif
/*-----------------�ⲿ�ж�4--------------------*/
#if (EXINT4_Open)
extern BOOL EXINT4_Flag;
extern void EXINT4_Init();
extern void EXINT4_Stop();
//�жϷ������-->void EXINT_4() interrupt 16          //INT4�ж����
#endif
/*----------------------------------------------------*/
#endif