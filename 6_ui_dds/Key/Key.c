#include "ti_msp_dl_config.h"
#include "oled.h"
#include "dac_dds.h"

#define max_parameter 2

#ifndef GPIO_Key_PORT
#define GPIO_Key_PORT (GPIOB)
#endif

uint16_t para1 = 0;
uint16_t para2 = 0;
unsigned int count = 0;
unsigned char key_flag1=0;
unsigned char key_flag2=0;
unsigned char key_flag3=0;
unsigned char key_flag4=0;
unsigned int ui_flag=1;
char change_flag=0;

unsigned int ui_flag_pre;
unsigned int i;
unsigned int ui_temp;

void key_read(void)
{
    change_flag = 0;
    
    if((key_flag1!=1) && (key_flag2!=1) && (key_flag3!=1) && (key_flag4!=1))
    {
        if(!DL_GPIO_readPins(GPIO_Key_GPIO_K1_PORT, GPIO_Key_GPIO_K1_PIN)) key_flag1 = 1;
        if(!DL_GPIO_readPins(GPIO_Key_GPIO_K2_PORT, GPIO_Key_GPIO_K2_PIN)) key_flag2 = 1;
        if(!DL_GPIO_readPins(GPIO_Key_GPIO_K3_PORT, GPIO_Key_GPIO_K3_PIN)) key_flag3 = 1;
        if(!DL_GPIO_readPins(GPIO_Key_GPIO_K4_PORT, GPIO_Key_GPIO_K4_PIN)) key_flag4 = 1;

    }

    else if(key_flag1==1)
    {
        count++;
        if(count>10&&(DL_GPIO_readPins(GPIO_Key_GPIO_K1_PORT, GPIO_Key_GPIO_K1_PIN)))
        {
            count = 0;
            key_flag1 = 2;
        }
    }

    else if(key_flag2==1)
    {
        count++;
        if(count>10&&(DL_GPIO_readPins(GPIO_Key_GPIO_K2_PORT, GPIO_Key_GPIO_K2_PIN)))
        {
            count = 0;
            key_flag2 = 2;
        }
    }

    else if(key_flag3==1)
    {
        count++;
        if(count>10&&(DL_GPIO_readPins(GPIO_Key_GPIO_K3_PORT, GPIO_Key_GPIO_K3_PIN)))
        {
            count = 0;
            key_flag3 = 2;
        }
    }

    else if(key_flag4==1) 
    {
        count++;
        if(count>10&&DL_GPIO_readPins(GPIO_Key_GPIO_K4_PORT, GPIO_Key_GPIO_K4_PIN))
        {
            count = 0;
            key_flag4 = 2;
        }
    }

    if(key_flag1 == 2)
    {
        ui_flag++;
        if(ui_flag > max_parameter) ui_flag = 1;
        key_flag1 = 0;
    }

    if(key_flag2 == 2)
    {
        ui_flag--;
        if(ui_flag == 0) ui_flag = max_parameter;
        key_flag2 = 0;
    }

    if(key_flag3 == 2)
    {
        change_flag = 1;
        key_flag3 = 0;
    }

    if(key_flag4 == 2)
    {
        change_flag = 2;
        key_flag4 = 0;
    }

    if(change_flag == 1)
    {
        switch (ui_flag) {
            case 1: wave_mode += 1; break;
            case 2: freq_wave += 100; break;
        }
    }

    else if(change_flag == 2)
    {
        switch (ui_flag) {
            case 1: wave_mode -= 1; break;
            case 2: freq_wave -= 100; break;
        }
    }

    if(wave_mode>3) wave_mode =0; if(wave_mode<0) wave_mode=3;
    if(freq_wave>70000) freq_wave =0; if(freq_wave<=0) freq_wave=70000;
}

void oled_show(void)
{
    if(ui_flag_pre!=ui_flag) OLED_Clear();
    for(i=1;i<=2;i++)
    {
        ui_temp = (ui_flag+i-1) % max_parameter;
        switch (ui_temp) {
            case 1: OLED_ShowString(0, i, "mode:", 8);OLED_ShowNum(45, i, wave_mode, 2, 8); break;
            case 0: OLED_ShowString(0, i, "freq:", 8);OLED_decimal(45, i, freq_wave, 5,1, 8); break;
        
        }
    }
    OLED_ShowString(110, 1, "**", 8);
    ui_flag_pre = ui_flag;

}

void para_init(void)
{
    para1 = 0;
    para2 = 0;
}
