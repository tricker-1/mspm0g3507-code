#include "ti_msp_dl_config.h"
#include "oled.h"
#include "bmp.h"
#include "Key.h"
#include "iic.h"

int main( void )
{
    SYSCFG_DL_init();
    OLED_Init();		//初始化OLED
    para_init();
    DL_SYSCTL_enableSleepOnExit();

    while(1) 
    {		
        //key_read();
        //oled_show();
        //OLED_ShowNum(0,0,read_id(),4,8);
        read_id();
    }
}

