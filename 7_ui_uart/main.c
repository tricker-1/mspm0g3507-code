#include "ti_msp_dl_config.h"
#include "oled.h"
#include "bmp.h"
#include "Key.h"
#include "uart.h"

int main( void )
{
    SYSCFG_DL_init();
    OLED_Init();		//初始化OLED
    para_init();
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    while(1) 
    {		
        key_read();
        oled_show();
        uart_deal();
    }
}

