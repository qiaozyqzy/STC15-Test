#ifndef __EXINTConfig_H__
#define __EXINTConfig_H__

#include "SYS.h"
#include "EXINT.h"

//�����ⲿ�жϱ��
#define EXINT0 0
#define EXINT1 1
#define EXINT2 2
#define EXINT3 3
#define EXINT4 4
//����1��ر�0ĳ�ⲿ�жϣ�Ԥ����ʱʹ�ã��������ô�����
#define EXINT0_Open 0
#define EXINT1_Open 0
#define EXINT2_Open 0
#define EXINT3_Open 0
#define EXINT4_Open 0

//�ⲿ�жϳ�ʼ��
//exint_num:�ⲿ�жϱ�š�exint_typ:�ж�����(0:���½��� 1:�����غ��½���)
//void EXINT_Init(char exint_num,BOOL exint_typ);

//�ر��ⲿ�ж�
//exint_num:�ⲿ�жϱ��
//void EXINT_Stop(char exint_num);

//�жϷ������-->void EXINT_0() interrupt 0     //INT0�ж����
//�жϷ������-->void EXINT_1() interrupt 2     //INT1�ж����
//�жϷ������-->void EXINT_2() interrupt 10    //INT2�ж����
//�жϷ������-->void EXINT_3() interrupt 11    //INT3�ж����
//�жϷ������-->void EXINT_4() interrupt 16    //INT4�ж����

#endif