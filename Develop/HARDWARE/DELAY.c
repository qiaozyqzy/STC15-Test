#include "SYS.h" 
#include "delay.h"
#include <intrins.h>

//STC_ISP延时函数生成

#if (FOSC == 5529600L)
void Delay10us() //@5.5296MHz
{
	unsigned char i;

	_nop_();
	i = 11;
	while (--i)
		;
}
void Delay1ms() //@5.5296MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j)
			;
	} while (--i);
}
#elif (FOSC == 6000000L)
void Delay10us() //@6.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 12;
	while (--i)
		;
}
void Delay1ms() //@6.000MHz
{
	unsigned char i, j;

	i = 6;
	j = 211;
	do
	{
		while (--j)
			;
	} while (--i);
}
#elif (FOSC == 11059200L)
void Delay1us() //@11.0592MHz
{
	_nop_();
	_nop_();
	_nop_();
}
void Delay1ms() //@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j)
			;
	} while (--i);
}
#elif (FOSC == 12000000L)
void Delay1us() //@12.000MHz
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
void Delay1ms() //@12.000MHz
{
	unsigned char i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j)
			;
	} while (--i);
}
#elif (FOSC == 18432000L)
void Delay1us() //@18.432MHz
{
	unsigned char i;

	i = 2;
	while (--i)
		;
}
void Delay1ms() //@18.432MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j)
			;
	} while (--i);
}
#elif (FOSC == 20000000L)
void Delay1us() //@20.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 2;
	while (--i)
		;
}
void Delay1ms() //@20.000MHz
{
	unsigned char i, j;

	i = 20;
	j = 113;
	do
	{
		while (--j)
			;
	} while (--i);
}
#elif (FOSC == 22118400L)
void Delay1ms() //@22.1184MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 22;
	j = 128;
	do
	{
		while (--j)
			;
	} while (--i);
}
void Delay1us() //@22.1184MHz
{
	unsigned char i;

	i = 3;
	while (--i)
		;
}

#elif (FOSC == 24000000L)
void Delay1us() //@24.000MHz
{
	unsigned char i;

	_nop_();
	_nop_();
	i = 3;
	while (--i)
		;
}
void Delay1ms() //@24.000MHz
{
	unsigned char i, j;

	i = 24;
	j = 85;
	do
	{
		while (--j)
			;
	} while (--i);
}
#elif (FOSC == 27000000L)
void Delay1us() //@27.000MHz
{
	unsigned char i;

	_nop_();
	i = 4;
	while (--i)
		;
}
void Delay1ms() //@27.000MHz
{
	unsigned char i, j;

	i = 27;
	j = 64;
	do
	{
		while (--j)
			;
	} while (--i);
}
#elif (FOSC == 30000000L)
void Delay1us() //@30.000MHz
{
	unsigned char i;

	i = 5;
	while (--i)
		;
}
void Delay1ms() //@30.000MHz
{
	unsigned char i, j;

	i = 30;
	j = 43;
	do
	{
		while (--j)
			;
	} while (--i);
}
#endif

#if (FOSC > 7000000L) //主频大于7MHz提供us级延时
//延时nus
//nus为要延时的us数.
void delay_us(u16 nus)
{
	while (nus)
	{
		nus--;
		Delay1us();
	}
}
#else //主频小于7MHz提供10us级延时
//延时n*10us
//nus为要延时的10us数.
void delay_us(u16 nus)
{
	while (nus)
	{
		nus--;
		Delay10us();
	}
}
#endif

//延时nms
//nms为要延时的ms数.
void delay_ms(u16 nms)
{
	while (nms)
	{
		nms--;
		Delay1ms();
	}
}
