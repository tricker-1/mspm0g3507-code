#include "ti_msp_dl_config.h"
#include "oled.h"
#include "bmp.h"

int main( void )
{
    SYSCFG_DL_init();
    OLED_Init();		//初始化OLED
    while(1) 
    {		
        OLED_ShowNum(1,1,64,2,16);
    }
}
