#ifndef __OLED_H
#define __OLED_H
#include "SYS.h"
#include "MY_STUDIO.h"
// #if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_USE_I2C
#include "I2C.H"
// #endif
#include "OLED.h"
// �ֿ�
#include "Font_EN.h"
#include "Font_CHS.h"

/*************************************************************/
/*************************OLED��������*************************/
/*************************************************************/
// OLED��д����
#define OLED_CMD 0  //д����
#define OLED_DATA 1 //д����
#define OLED_MODE 0
// ����߶�ѡ��
#define Font_0 EN_FH8
#define Font_1 EN_FH16
#define Font_2 EN_FH24
#define Font_3 EN_FH32
// ��ʾģʽѡ��
#define DISP_normal 0  // ������ʾ
#define DISP_special 1 // ������ʾ
// ������뷵��
#define OLED_NO_Font_NUM 0X10
#define OLED_Screen_Overflow 0X10
/*****************************************************************/
/*************************OLED�û����ò���*************************/
/*****************************************************************/
// OLED����ģʽ����
#define OLED_HW_Drive_Mode_SET OLED_HW_Drive_USE_I2C
#define OLED_HW_Drive_USE_I2C 0
#define OLED_HW_Drive_UUSE_SPI 1
#define OLED_HW_Drive_UUSE_8080 2
#define OLED_HW_Drive_UUSE_4040 3
// OLEDӲ���ߴ�����
#define OLED_Type OLED_096
#define OLED_091 0
#define OLED_096 1
// OLED�˿ڶ���
#if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_USE_I2C
#define OLED_I2C_NUM I2C_PIN_Group_0
#endif
#if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_UUSE_SPI

#endif
#if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_UUSE_4040

#endif
#if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_UUSE_8080

#endif
// �Ƿ�ʹ���Դ�
#define OLED_DISBUF  DISABLE   /*ENABLE*/ /**/ // �Ƿ�ʹ���Դ棨ʹ���Դ��ռ��һ���ڴ棬������Ҳ�������

//OLED�����ú���

/*****************************************************************/
/*************************OLED�Զ����ò���*************************/
/*****************************************************************/
#if OLED_Type == OLED_091
#define OLED_H_SET 32  // OLEDĬ�ϸ߶�
#define OLED_W_SET 128 // OLEDĬ�Ͽ��
#elif OLED_Type == OLED_096
#define OLED_H_SET 64  // OLEDĬ�ϸ߶�
#define OLED_W_SET 128 // OLEDĬ�Ͽ��
#endif
#if OLED_DISBUF == ENABLE
extern ux8 OLED_H;
extern ux8 OLED_W;
extern ux8 OLED_DIS_BUF[OLED_H_SET][OLED_W_SET / 8]; // ���Դ�
#endif
/*****************************************************************/
/*************************OLED���ƺ�������*************************/
/*****************************************************************/
#if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_USE_I2C
// д������
void OLED_Send_cmd(u8 cmd);
// д������
void OLED_Send_dat(u8 dat);
#endif
// д������/���OLED��
void OLED_WR_Byte(u8 dat, u8 cmd);
// ��������
void OLED_Set_Pos(u8 x, u8 y);
// ����OLED��ʾ
void OLED_Display_On(void);
// �ر�OLED��ʾ
void OLED_Display_Off(void);
// �����Ļ���ݣ�(ȫ��0��ȫ����1)�����ʾ������
void OLED_CLC(u8 clc_point);
//��ʼ��SSD1306
void OLED_Init(void);
#if OLED_DISBUF == ENABLE // �����Դ�
// ˢ����ʾ
void OLED_Refresh();
// д���Դ�
void Set_OLED_DIS_BUF_1BIT(u8 x, u8 y, u8 dat);
/************************************GUI��������************************************/
// ������ɫ
#define Bright 1
#define Dark 0
// ����������
#define OLED_GUI_Box_Width_Set_ERR 0X10
// ����
void OLED_GUI_Point(u8 x, u8 y, u8 dat);
// ������������Σ�
// x0,y0����ʼ���ꣻx1,y1���յ����ꣻL_dat���߿���ɫ��L_Width���߿��ȣ�Box_dat�������ɫ
// ����OK/OLED_GUI_Box_Width_Set_ERR
// ע1�����߿���Ϊ(-1)ʱ������ˢ����ʾ���ݣ������޸�����Ӧ�Դ����ݡ�
// ע2����L_dat(�߿���ɫ)��Box_dat(�����ɫ)��ͬʱ���൱�ڻ��˸����Σ���ʱ��L_Width(�߿���)ֻ������Ƿ�ˢ����ʾ������
E_Code OLED_GUI_Box(u8 x0, u8 y0, u8 x1, u8 y1, u8 L_dat, s8 L_Width, u8 Box_dat);
// ��ֱ��
// x0,y0����ʼ���ꣻx1,y1���յ����ꣻL_dat��������ɫ��L_Width��������ɫ��
void OLED_GUI_Line(s16 x0, s16 y0, s16 x1, s16 y1, u8 L_dat, u8 L_Width);
// ��ʾ�ַ�
//x:����λ�ã�0~127��,y:����λ�ã�0~64��,dat:�ַ�����,Char_H:����,mode:��ʾģʽ
E_Code OLED_Show_Char(u8 x, u8 y, u8 dat, u8 Char_H, u8 mode);
// ��ʾ�ַ��������Զ����У�
E_Code OLED_Show_STR(u8 x, u8 y, u8 *dat, u8 Char_H, u8 mode);
// ��ʾ����
E_Code OLED_Show_NUM(u8 x, u8 y, s32 num, u8 Char_H, u8 mode);
// ��ʾ����
void OLED_Show_CHS(u8 x, u8 y, u8 *CHS_F_DAT, u8 Char_H, u8 mode);
// ��ʾͼƬ
void OLED_Show_PIC(u8 x0, u8 y0, u8 x1, u8 y1, u8 *PIC_dat);
#else //�������Դ�
//��ָ��λ����ʾһ���ַ�
//x:����λ�ã�0~127��,y:����λ�ã�0~7��,dat:�ַ�����,Char_H:����,mode:��ʾģʽ
E_Code OLED_Show_Char(u8 x, u8 y, u8 dat, u8 Char_H, u8 mode);
//��ʾ�ַ��������Զ����У�
E_Code OLED_Show_STR(u8 x, u8 y, u8 *dat, u8 Char_H, u8 mode);
// ��ʾ����
E_Code OLED_Show_NUM(u8 x, u8 y, s32 num, u8 Char_H, u8 mode);
//��ʾ����
void OLED_Show_CHS(u8 x, u8 y, u8 *CHS_F_DAT, u8 Char_H, u8 mode);
// ��ʾͼƬ
void OLED_Show_PIC(u8 x0, u8 y0, u8 x1, u8 y1, u8 *BMP);
#endif

#endif
