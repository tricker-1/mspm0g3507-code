#include "ti_msp_dl_config.h"
#include "bmp.h"
#include "oled.h"
#include "Key.h"
#include "dac_dds.h"

int main(void)
{
    SYSCFG_DL_init();
    OLED_Init();
    para_init();
    DL_TimerG_startCounter(TIMER_0_INST);
    DL_SYSCTL_enableSleepOnExit();

    while (1) {
        key_read();
        oled_show();
        dma_wave();
    }
}
