#ifndef __MY_DEBUG_H__
#define __MY_DEBUG_H__

#include "SYS.h"
#include "UART.h"
#include "UARTConfig.h"
#include "DEBUG.h"
#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#define E_CODE s16 
#define LOG_UART UART1
extern u16 LOG_count;
extern void DEBUG_PRINT_LOG(E_CODE ERR, s8 *str);
#endif

#endif
