#include <dac_dds.h>
#include "ti_msp_dl_config.h"
#include "bmp.h"

int main(void)
{
    SYSCFG_DL_init();
    DL_TimerG_startCounter(TIMER_0_INST);
    DL_SYSCTL_enableSleepOnExit();

    while (1) {
        dma_wave();
    }
}
