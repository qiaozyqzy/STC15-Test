#include "SYS.h"
#include "MAIN.h"
#include "DEBUG.h"
/**********************************************USER**********************************************/
// 系统初始化
E_CODE SYS_Init(void)
{
    E_CODE err = OK;
    GPIO_Init();
    UART_Init(UART1, UART1_on_P30_P31, BAUD1);
    SPI_HW_Inti(LO1_SPI_NUM);
    // 初始化RF芯片
    RF_Init();
    //初始化SSD1306
    OLED_Init();

    delay_ms(10);
    return err;
}
// 主函数
void main(void)
{
    E_CODE err;
    ux8 RF_dat[32];
    ux8 dat_len[2] = {10, 10};
    err = SYS_Init();
    DEBUG_PRINT_LOG(err, "SYS_Init");
    RF_dat[0] = 'a';
    RF_dat[1] = 'b';
    RF_dat[2] = 'c';
    RF_dat[3] = 'd';
    RF_dat[4] = 'q';
    RF_dat[5] = 'i';
    RF_dat[6] = 'a';
    RF_dat[7] = 'o';
    RF_dat[8] = 'z';
    RF_dat[9] = 'y';
    while (1)
    {
        OLED_Show_STR(12, 1, "send", Font_1, DISP_normal);
        RF_Send(&RF_dat[0], &dat_len[0]);
        while (1)
        {
            err = RF_Recv(&RF_dat[10], &dat_len[1]);
            if (err == OK)
            {
                OLED_Show_STR(12, 2, "RECV DATA", Font_1, DISP_special);
                delay_ms(1000);
                delay_ms(1000);
                delay_ms(1000);
                OLED_Show_STR(12, 2, "          ", Font_1, DISP_normal);
                OLED_Show_STR(12, 1, "RE-send", Font_1, DISP_normal);
                RF_Send(&RF_dat[0], &dat_len[0]);
            }
        }
    }
    SYS_RST();
}

//void delay_ms(uint nms);
//void delay_us(uint nus);
