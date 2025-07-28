#include "ti_msp_dl_config.h"
#include "oled.h"
#include "bmp.h"
#include "Key.h"

uint16_t output_value;

int main( void )
{
    SYSCFG_DL_init();
    OLED_Init();		//初始化OLED
    para_init();

    output_value = 1500;
    DL_COMP_setDACCode0(COMP_0_INST, output_value*255.0/3300);
    DL_COMP_enable(COMP_0_INST);
    DL_OPA_enable(OPA_0_INST);

    while(1) 
    {		
        key_read();
        oled_show();
    }
}

