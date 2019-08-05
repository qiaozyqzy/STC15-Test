#include "SYS.h"
#include "UART.h"
#include "UARTConfig.h"
#include "DEBUG.h"
#ifdef ENABLE_DEBUG

u16 LOG_count = 0;

void DEBUG_PRINT_LOG(E_CODE ERR, s8 *str)
{
    if (ERR == ERROR)
    {
        SendString(LOG_UART, "LOG(");
        SendNumU32(LOG_UART, LOG_count);
        SendString(LOG_UART, ")-->");
        SendString(LOG_UART, "ERR(");
        SendNumS32(LOG_UART, ERR);
        SendString(LOG_UART, "):");

        SendString(LOG_UART, str);
        SendString(LOG_UART, "\r\n");

        LOG_count++;
    }
}

#endif