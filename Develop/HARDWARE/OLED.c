#include "SYS.h"
#include "MY_STUDIO.h"
#include "OLED.h"

#include "I2C.H"
#include "Font_EN.h"
#include "Font_CHS.h"

#if OLED_DISBUF == ENABLE
ux8 OLED_H = OLED_H_SET;
ux8 OLED_W = OLED_W_SET;
ux8 OLED_DIS_BUF[OLED_H_SET / 8][OLED_W_SET]; // 软显存
#endif

#if OLED_HW_Drive_Mode_SET == OLED_HW_Drive_USE_I2C
// 写入命令
void OLED_Send_cmd(u8 cmd)
{
	Start_I2C(OLED_I2C_NUM);
	I2C_SendByte(OLED_I2C_NUM, 0x78); //Slave address,SA0=0
	I2C_RecvACK(OLED_I2C_NUM);
	I2C_SendByte(OLED_I2C_NUM, 0x00); //write command
	I2C_RecvACK(OLED_I2C_NUM);
	I2C_SendByte(OLED_I2C_NUM, cmd);
	I2C_RecvACK(OLED_I2C_NUM);
	Stop_I2C(OLED_I2C_NUM);
}
// 写入数据
void OLED_Send_dat(u8 dat)
{
	Start_I2C(OLED_I2C_NUM);
	I2C_SendByte(OLED_I2C_NUM, 0x78); //D/C#=0; R/W#=0
	I2C_RecvACK(OLED_I2C_NUM);
	I2C_SendByte(OLED_I2C_NUM, 0x40); //write data
	I2C_RecvACK(OLED_I2C_NUM);
	I2C_SendByte(OLED_I2C_NUM, dat);
	I2C_RecvACK(OLED_I2C_NUM);
	Stop_I2C(OLED_I2C_NUM);
}
#endif

// 写入数据/命令到OLED屏
void OLED_WR_Byte(u8 dat, u8 cmd)
{
	if (cmd == OLED_DATA)
	{
		OLED_Send_dat(dat);
	}
	else
	{
		OLED_Send_cmd(dat);
	}
}
// 坐标设置
void OLED_Set_Pos(u8 x, u8 y)
{
	OLED_WR_Byte(0xb0 + y, OLED_CMD);
	OLED_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
	OLED_WR_Byte((x & 0x0f), OLED_CMD);
}
// 开启OLED显示
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD); //SET DCDC命令
	OLED_WR_Byte(0X14, OLED_CMD); //DCDC ON
	OLED_WR_Byte(0XAF, OLED_CMD); //DISPLAY ON
}
// 关闭OLED显示
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD); //SET DCDC命令
	OLED_WR_Byte(0X10, OLED_CMD); //DCDC OFF
	OLED_WR_Byte(0XAE, OLED_CMD); //DISPLAY OFF
}
// 清除屏幕内容，(全灭；0或全亮；FF)替代显示的内容
void OLED_CLC(u8 clc_point)
{
	u8 i, j;
	if (clc_point)
	{
		clc_point = 0XFF;
	}
	for (i = 0; i < (OLED_H_SET / 8); i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD); //设置页地址（0~7）
		OLED_WR_Byte(0x00, OLED_CMD);	 //设置显示位置—列低地址
		OLED_WR_Byte(0x10, OLED_CMD);	 //设置显示位置—列高地址
		for (j = 0; j < (OLED_W_SET); j++)
		{
#if OLED_DISBUF == ENABLE
			OLED_DIS_BUF[i][j] = clc_point;
#endif
			OLED_WR_Byte(clc_point, OLED_DATA);
		}
	}
}
//初始化SSD1306
void OLED_Init(void)
{

	OLED_WR_Byte(0xAE, OLED_CMD); //--display off
	OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
	OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
	OLED_WR_Byte(0x40, OLED_CMD); //--set start line address
	OLED_WR_Byte(0xB0, OLED_CMD); //--set page address
	OLED_WR_Byte(0x81, OLED_CMD); // contract control
	OLED_WR_Byte(0xFF, OLED_CMD); //--128
	OLED_WR_Byte(0xA1, OLED_CMD); //set segment remap
	OLED_WR_Byte(0xA6, OLED_CMD); //--normal / reverse
	OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F, OLED_CMD); //--1/32 duty
	OLED_WR_Byte(0xC8, OLED_CMD); //Com scan direction
	OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset
	OLED_WR_Byte(0x00, OLED_CMD); //

	OLED_WR_Byte(0xD5, OLED_CMD); //set osc division
	OLED_WR_Byte(0x80, OLED_CMD); //

	OLED_WR_Byte(0xD8, OLED_CMD); //set area color mode off
	OLED_WR_Byte(0x05, OLED_CMD); //

	OLED_WR_Byte(0xD9, OLED_CMD); //Set Pre-Charge Period
	OLED_WR_Byte(0xF1, OLED_CMD); //

	OLED_WR_Byte(0xDA, OLED_CMD); //set com pin configuartion
	OLED_WR_Byte(0x12, OLED_CMD); //

	OLED_WR_Byte(0xDB, OLED_CMD); //set Vcomh
	OLED_WR_Byte(0x30, OLED_CMD); //

	OLED_WR_Byte(0x8D, OLED_CMD); //set charge pump enable
	OLED_WR_Byte(0x14, OLED_CMD); //

	OLED_WR_Byte(0xAF, OLED_CMD); //--turn on oled panel
} 
#if OLED_DISBUF == ENABLE // 开启显存
// 刷新显示
void OLED_Refresh()
{
	u8 i, j, k;
	u8 temp;
	// ux8 OLED_DIS_BUF[OLED_H_SET / 8][OLED_W_SET]; // 软显存
	for (i = 0; i < OLED_H_SET / 8; i++)
	{
		OLED_WR_Byte(0xb0 + i, OLED_CMD); //设置页地址（0~7）
		OLED_WR_Byte(0x00, OLED_CMD);	 //设置显示位置—列低地址
		OLED_WR_Byte(0x10, OLED_CMD);	 //设置显示位置—列高地址
		for (j = 0; j < OLED_W_SET; j++)
		{
			temp = (OLED_DIS_BUF[i][j]);
			OLED_WR_Byte(temp, OLED_DATA);
		}
	}
}
// 写入显存
void Set_OLED_DIS_BUF_1BIT(u8 x, u8 y, u8 dat)
{
	u8 y_b_num;
	if (x > OLED_W_SET || y > OLED_H_SET)
	{
		return;
	}
	y_b_num = y % 8;
	y = y / 8;
	// OLED_DIS_BUF[y][x] = OLED_DIS_BUF[y][x] & (~(0X80 >> y_b_num));
	OLED_DIS_BUF[y][x] = OLED_DIS_BUF[y][x] & (~(0X01 << y_b_num));
	if (dat)
	{
		OLED_DIS_BUF[y][x] = OLED_DIS_BUF[y][x] | (0X01 << y_b_num);
		// OLED_DIS_BUF[y][temp[0]] = OLED_DIS_BUF[y][temp[0]] | (0X80 >> temp[1]);
	}
}
/************************************GUI操作函数************************************/
// 定义颜色
#define Bright 1
#define Dark 0
// 定义错误代码
#define OLED_GUI_Box_Width_Set_ERR 0X10
// 画点
void OLED_GUI_Point(u8 x, u8 y, u8 dat)
{
	Set_OLED_DIS_BUF_1BIT(x, y, dat);
	OLED_Refresh();
}
// 画方框（两点矩形）
// x0,y0：起始坐标；x1,y1：终点坐标；L_dat：线框颜色；L_Width：线框宽度；Box_dat：填充颜色
// 返回OK/OLED_GUI_Box_Width_Set_ERR
// 注1：当线框宽度为(-1)时，不会刷新显示内容，仅是修改了相应显存内容。
// 注2：当L_dat(线框颜色)与Box_dat(填充颜色)相同时，相当于画了个矩形，此时的L_Width(线框宽度)只起控制是否刷新显示的作用
E_Code OLED_GUI_Box(u8 x0, u8 y0, u8 x1, u8 y1, u8 L_dat, s8 L_Width, u8 Box_dat)
{
	u8 i, j;
	if (L_dat != Box_dat)
	{
		if (L_Width < 0)
		{
			return OLED_GUI_Box_Width_Set_ERR;
		}
		// 画横线（上、下）
		for (i = 0; i < (x1 - x0 + 1); i++)
		{
			for (j = 0; j < L_Width; j++)
			{
				Set_OLED_DIS_BUF_1BIT((x0 + i), (y0 + j), L_dat);
				Set_OLED_DIS_BUF_1BIT((x0 + i), (y1 - j), L_dat);
			}
		}
		// 画竖线（上、下）
		for (i = 0; i < (y1 - y0 + 1); i++)
		{
			for (j = 0; j < L_Width; j++)
			{
				Set_OLED_DIS_BUF_1BIT((x0 + j), (y0 + i), L_dat);
				Set_OLED_DIS_BUF_1BIT((x1 - j), (y1 + i), L_dat);
			}
		}
		// 填充内部
		for (i = 0; i < ((x1 - x0 + 1) - (2 * L_Width)); i++)
		{
			for (j = 0; j < ((y1 - y0 + 1) - (2 * L_Width)); j++)
			{
				Set_OLED_DIS_BUF_1BIT((x0 + i + L_Width), (y0 + j + L_Width), Box_dat);
			}
		}
	}
	else
	{
		// 直接填充内部
		for (i = 0; i < (x1 - x0 + 1); i++)
		{
			for (j = 0; j < (y1 - y0 + 1); j++)
			{
				Set_OLED_DIS_BUF_1BIT((x0 + i), (y0 + j), Box_dat);
			}
		}
	}
	if (L_Width < 0)
	{
		OLED_Refresh();
	}
	return OK;
}
// 画直线
// x0,y0：起始坐标；x1,y1：终点坐标；L_dat：线条颜色；L_Width：线条颜色；
void OLED_GUI_Line(s16 x0, s16 y0, s16 x1, s16 y1, u8 L_dat, u8 L_Width)
{
	s16 xf = 1, yf = 1;
	s16 x, y;
	u16 L = 0, F = 0;

	x1 = x1 - x0;
	y1 = y1 - y0;
	if (x1 < 0)
	{
		xf = (-1);
	}
	if (y1 < 0)
	{
		yf = (-1);
	}
	x1 = xf * x1;
	y1 = yf * y1;
	L = x1 + y1;
	while (L > 0)
	{
		if (F >= 0)
		{
			F = F - y1;
			x = x + xf;
		}
		else
		{
			F = F + x1;
			y = y + yf;
		}
		if (L_Width < 0)
		{
			Set_OLED_DIS_BUF_1BIT((x0 + x), (y0 + y), L_dat);
		}
		else
		{
			OLED_GUI_Box(x0 + x - L_Width, y0 + y - L_Width, x0 + x + L_Width, y0 + y + L_Width, L_dat, (-1), L_dat);
		}
		L = L - 1;
	}
	OLED_Refresh();
}
// 显示字符
//x:横向位置（0~127）,y:纵向位置（0~64）,dat:字符内容,Char_H:字体,mode:显示模式
E_Code OLED_Show_Char(u8 x, u8 y, u8 dat, u8 Char_H, u8 mode)
{
	u8 line_num = 0, column_num = 0;
	u16 Font_Move = 0;
	u8 *Font_buf;
	u8 Font_b_num;
	if (x + EN_Font_Index[Char_H][0] > (OLED_W_SET - 1) || y + EN_Font_Index[Char_H][1] > (OLED_H_SET - 1)) // 检测是否为有效显示位置
	{
		return OLED_Screen_Overflow;
	}
	dat = dat - ' '; //得到偏移后的值
	switch (Char_H)
	{
	case Font_0:
		Font_buf = &EN_F6X8[dat][0];
		break;
	case Font_1:
		Font_buf = &EN_F8X16[dat][0];
		break;
	case Font_2:
		Font_buf = &EN_F12X24[dat][0];
		break;
	case Font_3:
		Font_buf = &EN_F16X32[dat][0];
		break;
	default:
		return OLED_NO_Font_NUM;
		break;
	}
	Font_Move = 0;
	if (mode == DISP_normal)
	{
		for (line_num = 0; line_num < (EN_Font_Index[Char_H][1] / 8); line_num++)
		{
			Font_Move = line_num * EN_Font_Index[Char_H][0];
			for (column_num = 0; column_num < EN_Font_Index[Char_H][0]; column_num++)
			{
				for (Font_b_num = 0; Font_b_num < 8; Font_b_num++)
				{
					Set_OLED_DIS_BUF_1BIT(x, y, (Font_buf[column_num + Font_Move] & (0X01 << Font_b_num)));
					y++;
				}
				x++;
			}
		}
	}
	else
	{
		for (line_num = 0; line_num < (EN_Font_Index[Char_H][1] / 8); line_num++)
		{
			Font_Move = line_num * EN_Font_Index[Char_H][0];
			for (column_num = 0; column_num < EN_Font_Index[Char_H][0]; column_num++)
			{
				for (Font_b_num = 0; Font_b_num < 8; Font_b_num++)
				{
					Set_OLED_DIS_BUF_1BIT(x, y, (~(Font_buf[column_num + Font_Move] & (0X01 << Font_b_num))));
					y++;
				}
				x++;
			}
		}
	}
	return OK;
}
// 显示字符串（可自动换行）
E_Code OLED_Show_STR(u8 x, u8 y, u8 *dat, u8 Char_H, u8 mode)
{
	u16 i = 0;
	while (dat[i] != '\0')
	{
		OLED_Show_Char(x, y, dat[i], Char_H, mode);
		x = x + EN_Font_Index[Char_H][0];
		if (x + EN_Font_Index[Char_H][0] > (OLED_W_SET - 1)) // 检测是否为有效显示位置
		{
			x = 0;
			y = (y + (EN_Font_Index[Char_H][1] / 8));
			if (y + EN_Font_Index[Char_H][1] > (OLED_H_SET - 1))
			{
				OLED_Refresh();
				return OLED_Screen_Overflow;
			}
		}
		i++;
	}
	OLED_Refresh();
	return OK;
}
// 显示数字
E_Code OLED_Show_NUM(u8 x, u8 y, s32 num, u8 Char_H, u8 mode)
{
	E_Code err = OK;
	u8 temp[12];
	Num32_to_STR(num, temp);
	err = OLED_Show_STR(x, y, temp, Char_H, mode);
	return err;
}
// 显示汉字
void OLED_Show_CHS(u8 x, u8 y, u8 *CHS_F_DAT, u8 Char_H, u8 mode)
{
	u8 line_num = 0, column_num = 0;
	u16 Font_Move = 0;
	u8 Font_b_num;
	Font_Move = 0;
	if (mode == DISP_normal)
	{
		for (line_num = 0; line_num < (EN_Font_Index[Char_H][1] / 8); line_num++)
		{
			Font_Move = line_num * EN_Font_Index[Char_H][0];
			for (column_num = 0; column_num < EN_Font_Index[Char_H][0]; column_num++)
			{
				for (Font_b_num = 0; Font_b_num < 8; Font_b_num++)
				{
					Set_OLED_DIS_BUF_1BIT(x, y, ((CHS_F_DAT[column_num + Font_Move] & (0X01 << Font_b_num))));
					y++;
				}
				x++;
			}
		}
	}
	else
	{
		for (line_num = 0; line_num < (EN_Font_Index[Char_H][1] / 8); line_num++)
		{
			Font_Move = line_num * EN_Font_Index[Char_H][0];
			for (column_num = 0; column_num < EN_Font_Index[Char_H][0]; column_num++)
			{
				for (Font_b_num = 0; Font_b_num < 8; Font_b_num++)
				{
					Set_OLED_DIS_BUF_1BIT(x, y, (~(CHS_F_DAT[column_num + Font_Move] & (0X01 << Font_b_num))));
					y++;
				}
				x++;
			}
		}
	}
	OLED_Refresh();
}
// 显示图片
void OLED_Show_PIC(u8 x0, u8 y0, u8 x1, u8 y1, u8 *PIC_dat)
{
	u16 i = 0;
	u8 x, y;
	u8 Font_b_num;
	if (y1 % 8 == 0)
	{
		y = y1 / 8;
	}
	else
	{
		y = y1 / 8 + 1;
	}
	for (y = y0; y < y1; y++)
	{
		OLED_Set_Pos(x0, y);
		for (x = x0; x < x1; x++)
		{
			OLED_WR_Byte(PIC_dat[i], OLED_DATA);
			i++;
		}
	}
	y = y0;
	while (y < y1)
	{
		for (x = x0; x < x1; x++)
		{
			for (Font_b_num = 0; Font_b_num < 8; Font_b_num++)
			{
				Set_OLED_DIS_BUF_1BIT(x, y, (PIC_dat[i] & (0X01 << Font_b_num)));
				y++;
			}
			i++;
		}
	}

	OLED_Refresh();
}
#else //不开启显存
//在指定位置显示一个字符
//x:横向位置（0~127）,y:纵向位置（0~7）,dat:字符内容,Char_H:字体,mode:显示模式
E_Code OLED_Show_Char(u8 x, u8 y, u8 dat, u8 Char_H, u8 mode)
{
	u8 line_num = 0, column_num = 0;
	u16 Font_Move = 0;
	u8 *Font_buf;
	if (x > (OLED_W_SET - 1)) // 检测是否为有效显示位置
	{
		x = 0;
		y = y + 1;
		if (y >= (OLED_H_SET / 8))
		{
			return OLED_Screen_Overflow;
		}
	}
	if (x + EN_Font_Index[Char_H][0] > (OLED_W_SET - 1) || y + EN_Font_Index[Char_H][1] > (OLED_H_SET - 1)) // 检测是否为有效显示位置
	{
		return OLED_Screen_Overflow;
	}
	dat = dat - ' '; //得到偏移后的值
	switch (Char_H)
	{
	case Font_0:
		Font_buf = &EN_F6X8[dat][0];
		break;
	case Font_1:
		Font_buf = &EN_F8X16[dat][0];
		break;
	case Font_2:
		Font_buf = &EN_F12X24[dat][0];
		break;
	case Font_3:
		Font_buf = &EN_F16X32[dat][0];
		break;
	default:
		return OLED_NO_Font_NUM;
		break;
	}
	Font_Move = 0;
	if (mode == DISP_normal)
	{
		for (line_num = 0; line_num < (EN_Font_Index[Char_H][1] / 8); line_num++)
		{
			OLED_Set_Pos(x, (y + line_num));
			Font_Move = line_num * EN_Font_Index[Char_H][0];
			for (column_num = 0; column_num < EN_Font_Index[Char_H][0]; column_num++)
			{
				OLED_WR_Byte(Font_buf[column_num + Font_Move], OLED_DATA);
			}
		}
	}
	else
	{
		for (line_num = 0; line_num < (EN_Font_Index[Char_H][1] / 8); line_num++)
		{
			OLED_Set_Pos(x, (y + line_num));
			Font_Move = line_num * EN_Font_Index[Char_H][0];
			for (column_num = 0; column_num < EN_Font_Index[Char_H][0]; column_num++)
			{
				OLED_WR_Byte((~Font_buf[column_num + Font_Move]), OLED_DATA);
			}
		}
	}
	return OK;
}
//显示字符串（可自动换行）
E_Code OLED_Show_STR(u8 x, u8 y, u8 *dat, u8 Char_H, u8 mode)
{
	u16 i = 0;
	while (dat[i] != '\0')
	{
		OLED_Show_Char(x, y, dat[i], Char_H, mode);
		x = x + EN_Font_Index[Char_H][0];
		if (x + EN_Font_Index[Char_H][0] > (OLED_W_SET - 1)) // 检测是否为有效显示位置
		{
			x = 0;
			y = (y + (EN_Font_Index[Char_H][1] / 8));
			if (y + (EN_Font_Index[Char_H][1] / 8) > ((OLED_H_SET / 8) - 1))
			{
				return OLED_Screen_Overflow;
			}
		}
		i++;
	}
	return OK;
}
// 显示数字
E_Code OLED_Show_NUM(u8 x, u8 y, s32 num, u8 Char_H, u8 mode)
{
	E_Code err = OK;
	u8 temp[12];
	Num32_to_STR(num, temp);
	err = OLED_Show_STR(x, y, temp, Char_H, mode);
	return err;
}
//显示汉字
void OLED_Show_CHS(u8 x, u8 y, u8 *CHS_F_DAT, u8 Char_H, u8 mode)
{
	u8 line_num = 0, column_num = 0;
	u16 Font_Move = 0;
	Font_Move = 0;
	if (mode == DISP_normal)
	{
		for (line_num = 0; line_num < (Char_H / 8); line_num++)
		{
			OLED_Set_Pos(x, (y + line_num));
			Font_Move = line_num * Char_H;
			for (column_num = 0; column_num < Char_H; column_num++)
			{
				OLED_WR_Byte(CHS_F_DAT[column_num + Font_Move], OLED_DATA);
			}
		}
	}
	else
	{
		for (line_num = 0; line_num < (Char_H / 8); line_num++)
		{
			OLED_Set_Pos(x, (y + line_num));
			Font_Move = line_num * Char_H;
			for (column_num = 0; column_num < Char_H; column_num++)
			{
				OLED_WR_Byte((~CHS_F_DAT[column_num + Font_Move]), OLED_DATA);
			}
		}
	}
}
// 显示图片
void OLED_Show_PIC(u8 x0, u8 y0, u8 x1, u8 y1, u8 *BMP)
{
	u16 i = 0;
	u8 x, y;
	if (y1 % 8 == 0)
	{
		y = y1 / 8;
	}
	else
	{
		y = y1 / 8 + 1;
	}
	for (y = y0; y < y1; y++)
	{
		OLED_Set_Pos(x0, y);
		for (x = x0; x < x1; x++)
		{
			OLED_WR_Byte(BMP[i], OLED_DATA);
			i++;
		}
	}
}

#endif
