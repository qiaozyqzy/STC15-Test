#ifndef __OLED_H
#define __OLED_H
#include "SYS.h"
#include "MY_STUDIO.h"
// #if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_USE_I2C
#include "I2C.H"
// #endif
#include "OLED.h"
// 字库
#include "Font_EN.h"
#include "Font_CHS.h"

/*************************************************************/
/*************************OLED参数部分*************************/
/*************************************************************/
// OLED读写命令
#define OLED_CMD 0  //写命令
#define OLED_DATA 1 //写数据
#define OLED_MODE 0
// 字体高度选择
#define Font_0 EN_FH8
#define Font_1 EN_FH16
#define Font_2 EN_FH24
#define Font_3 EN_FH32
// 显示模式选择
#define DISP_normal 0  // 正常显示
#define DISP_special 1 // 反白显示
// 错误代码返回
#define OLED_NO_Font_NUM 0X10
#define OLED_Screen_Overflow 0X10
/*****************************************************************/
/*************************OLED用户设置部分*************************/
/*****************************************************************/
// OLED驱动模式设置
#define OLED_HW_Drive_Mode_SET OLED_HW_Drive_USE_I2C
#define OLED_HW_Drive_USE_I2C 0
#define OLED_HW_Drive_UUSE_SPI 1
#define OLED_HW_Drive_UUSE_8080 2
#define OLED_HW_Drive_UUSE_4040 3
// OLED硬件尺寸设置
#define OLED_Type OLED_096
#define OLED_091 0
#define OLED_096 1
// OLED端口定义
#if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_USE_I2C
#define OLED_I2C_NUM I2C_PIN_Group_0
#endif
#if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_UUSE_SPI

#endif
#if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_UUSE_4040

#endif
#if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_UUSE_8080

#endif
// 是否使用显存
#define OLED_DISBUF  DISABLE   /*ENABLE*/ /**/ // 是否使用显存（使用显存会占用一定内存，但功能也会更加灵活）

//OLED控制用函数

/*****************************************************************/
/*************************OLED自动设置部分*************************/
/*****************************************************************/
#if OLED_Type == OLED_091
#define OLED_H_SET 32  // OLED默认高度
#define OLED_W_SET 128 // OLED默认宽度
#elif OLED_Type == OLED_096
#define OLED_H_SET 64  // OLED默认高度
#define OLED_W_SET 128 // OLED默认宽度
#endif
#if OLED_DISBUF == ENABLE
extern ux8 OLED_H;
extern ux8 OLED_W;
extern ux8 OLED_DIS_BUF[OLED_H_SET][OLED_W_SET / 8]; // 软显存
#endif
/*****************************************************************/
/*************************OLED控制函数部分*************************/
/*****************************************************************/
#if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_USE_I2C
// 写入命令
void OLED_Send_cmd(u8 cmd);
// 写入数据
void OLED_Send_dat(u8 dat);
#endif
// 写入数据/命令到OLED屏
void OLED_WR_Byte(u8 dat, u8 cmd);
// 坐标设置
void OLED_Set_Pos(u8 x, u8 y);
// 开启OLED显示
void OLED_Display_On(void);
// 关闭OLED显示
void OLED_Display_Off(void);
// 清除屏幕内容，(全灭；0或全亮；1)替代显示的内容
void OLED_CLC(u8 clc_point);
//初始化SSD1306
void OLED_Init(void);
#if OLED_DISBUF == ENABLE // 开启显存
// 刷新显示
void OLED_Refresh();
// 写入显存
void Set_OLED_DIS_BUF_1BIT(u8 x, u8 y, u8 dat);
/************************************GUI操作函数************************************/
// 定义颜色
#define Bright 1
#define Dark 0
// 定义错误代码
#define OLED_GUI_Box_Width_Set_ERR 0X10
// 画点
void OLED_GUI_Point(u8 x, u8 y, u8 dat);
// 画方框（两点矩形）
// x0,y0：起始坐标；x1,y1：终点坐标；L_dat：线框颜色；L_Width：线框宽度；Box_dat：填充颜色
// 返回OK/OLED_GUI_Box_Width_Set_ERR
// 注1：当线框宽度为(-1)时，不会刷新显示内容，仅是修改了相应显存内容。
// 注2：当L_dat(线框颜色)与Box_dat(填充颜色)相同时，相当于画了个矩形，此时的L_Width(线框宽度)只起控制是否刷新显示的作用
E_Code OLED_GUI_Box(u8 x0, u8 y0, u8 x1, u8 y1, u8 L_dat, s8 L_Width, u8 Box_dat);
// 画直线
// x0,y0：起始坐标；x1,y1：终点坐标；L_dat：线条颜色；L_Width：线条颜色；
void OLED_GUI_Line(s16 x0, s16 y0, s16 x1, s16 y1, u8 L_dat, u8 L_Width);
// 显示字符
//x:横向位置（0~127）,y:纵向位置（0~64）,dat:字符内容,Char_H:字体,mode:显示模式
E_Code OLED_Show_Char(u8 x, u8 y, u8 dat, u8 Char_H, u8 mode);
// 显示字符串（可自动换行）
E_Code OLED_Show_STR(u8 x, u8 y, u8 *dat, u8 Char_H, u8 mode);
// 显示数字
E_Code OLED_Show_NUM(u8 x, u8 y, s32 num, u8 Char_H, u8 mode);
// 显示汉字
void OLED_Show_CHS(u8 x, u8 y, u8 *CHS_F_DAT, u8 Char_H, u8 mode);
// 显示图片
void OLED_Show_PIC(u8 x0, u8 y0, u8 x1, u8 y1, u8 *PIC_dat);
#else //不开启显存
//在指定位置显示一个字符
//x:横向位置（0~127）,y:纵向位置（0~7）,dat:字符内容,Char_H:字体,mode:显示模式
E_Code OLED_Show_Char(u8 x, u8 y, u8 dat, u8 Char_H, u8 mode);
//显示字符串（可自动换行）
E_Code OLED_Show_STR(u8 x, u8 y, u8 *dat, u8 Char_H, u8 mode);
// 显示数字
E_Code OLED_Show_NUM(u8 x, u8 y, s32 num, u8 Char_H, u8 mode);
//显示汉字
void OLED_Show_CHS(u8 x, u8 y, u8 *CHS_F_DAT, u8 Char_H, u8 mode);
// 显示图片
void OLED_Show_PIC(u8 x0, u8 y0, u8 x1, u8 y1, u8 *BMP);
#endif

#endif
