#include "ti_msp_dl_config.h"
#include "uart.h"

//提供100个数据暂存
uint8_t uart_data[100];
uint8_t uart_num = 0;

uint8_t uart_received = 0;

//接受：DL_UART_Main_receiveData(UART_0_INST);
//发送：DL_UART_Main_transmitData(UART_0_INST, uart_data);

void uart_deal(void)
{
    if(uart_received==1)
    {
        for(int i=0;uart_num!=0;uart_num--)
        {
            DL_UART_Main_transmitData(UART_0_INST, uart_data[i++]);
        }
        uart_num = 0;
        uart_received = 0;
    }
}

void UART_0_INST_IRQHandler(void)
{
    switch (DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
        case DL_UART_MAIN_IIDX_RX:
            uart_data[uart_num] = DL_UART_Main_receiveData(UART_0_INST);
            if(++uart_num>99)uart_num=99;
            uart_received = 1;
            break;
        default:
            break;
    }
}

