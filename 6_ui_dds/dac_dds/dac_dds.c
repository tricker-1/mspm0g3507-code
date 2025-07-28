#include "dac_dds.h"
#include "ti_msp_dl_config.h"

/* Repetitive sine wave */
//sin:
const uint16_t gOutputSignalSine64[] = {2048, 2248, 2447, 2642, 2831, 3013,
    3185, 3347, 3496, 3631, 3750, 3854, 3940, 4007, 4056, 4086, 4095, 4086,
    4056, 4007, 3940, 3854, 3750, 3631, 3496, 3347, 3185, 3013, 2831, 2642,
    2447, 2248, 2048, 1847, 1648, 1453, 1264, 1082, 910, 748, 599, 464, 345,
    241, 155, 88, 39, 9, 0, 9, 39, 88, 155, 241, 345, 464, 599, 748, 910, 1082,
    1264, 1453, 1648, 1847};

float freq_sin ;//hz

//san:
const uint16_t gOutputSignalSan64[]={128, 256, 384, 512, 640, 768, 896, 1024, 1152, 1280, 1408, 1536, 1664, 1792, 1920, 2048, 2175, 2303, 2431, 2559, 2687, 2815, 2943, 3071, 3199, 3327, 3455, 3583, 3711, 3839, 3967, 4095, 3967, 3839, 3711, 3583, 3455, 3327, 3199, 3071, 2943, 2815, 2687, 2559, 2431, 2303, 2175, 2048, 1920, 1792, 1664, 1536, 1408, 1280, 1152, 1024, 896, 768, 640, 512, 384, 256, 128, 0};

float freq_san ;//hz

//square
const uint16_t gOutputSignalSquare64[]={4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

float freq_square;

//saw
const uint16_t gOutputSignalSaw64[]={64, 128, 192, 256, 320, 384, 448, 512, 576, 640, 704, 768, 832, 896, 960, 1024, 1088, 1152, 1216, 1280, 1344, 1408, 1472, 1536, 1600, 1664, 1728, 1792, 1856, 1920, 1984, 2048, 2111, 2175, 2239, 2303, 2367, 2431, 2495, 2559, 2623, 2687, 2751, 2815, 2879, 2943, 3007, 3071, 3135, 3199, 3263, 3327, 3391, 3455, 3519, 3583, 3647, 3711, 3775, 3839, 3903, 3967, 4031, 4095 };

float freq_saw;

uint8_t freq_change;

uint16_t load_value;

unsigned char wave_mode=0;//0:正弦波，1:三角波，2:方波，3:锯齿波

uint8_t wave_mode_old=0;

float freq_wave = 10000;

float freq_wave_old;

void dma_sine_init(void)
{
    /* Configure DMA source, destination and size */
    DL_DMA_setSrcAddr(
        DMA, DMA_CH0_CHAN_ID, (uint32_t) &gOutputSignalSine64[0]);
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) & (DAC0->DATA0));
    DL_DMA_setTransferSize(
        DMA, DMA_CH0_CHAN_ID, sizeof(gOutputSignalSine64) / sizeof(uint16_t));

    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
}

void dma_san_init(void)
{
    /* Configure DMA source, destination and size */
    DL_DMA_setSrcAddr(
        DMA, DMA_CH0_CHAN_ID, (uint32_t) &gOutputSignalSan64[0]);
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) & (DAC0->DATA0));
    DL_DMA_setTransferSize(
        DMA, DMA_CH0_CHAN_ID, sizeof(gOutputSignalSan64) / sizeof(uint16_t));

    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
}

void dma_square_init(void)
{
    /* Configure DMA source, destination and size */
    DL_DMA_setSrcAddr(
        DMA, DMA_CH0_CHAN_ID, (uint32_t) &gOutputSignalSquare64[0]);
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) & (DAC0->DATA0));
    DL_DMA_setTransferSize(
        DMA, DMA_CH0_CHAN_ID, sizeof(gOutputSignalSquare64) / sizeof(uint16_t));

    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
}

void dma_saw_init(void)
{
    /* Configure DMA source, destination and size */
    DL_DMA_setSrcAddr(
        DMA, DMA_CH0_CHAN_ID, (uint32_t) &gOutputSignalSaw64[0]);
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) & (DAC0->DATA0));
    DL_DMA_setTransferSize(
        DMA, DMA_CH0_CHAN_ID, sizeof(gOutputSignalSaw64) / sizeof(uint16_t));

    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
}

void dma_wave(void)
{
    if(wave_mode != wave_mode_old) freq_change =1;
    if(freq_wave != freq_wave_old) freq_change =1;
    if(freq_change == 1)
    {
        if(wave_mode>3)wave_mode = 0;
        else if(wave_mode<0)wave_mode =3;

        if(wave_mode == 0)//正弦波
        {
            freq_sin = freq_wave;
            DL_DMA_disableChannel(DMA, DMA_CH0_CHAN_ID);
            dma_sine_init();
            load_value=(uint16_t)((80000000.0/64.0/freq_sin)-1);
            DL_Timer_setLoadValue(TIMER_0_INST,load_value);
        }
        else if(wave_mode == 1)//三角波
        {
            freq_san = freq_wave;
            DL_DMA_disableChannel(DMA, DMA_CH0_CHAN_ID);
            dma_san_init();
            load_value=(uint16_t)((80000000.0/64.0/freq_san)-1);
            DL_Timer_setLoadValue(TIMER_0_INST,load_value);
        }
        else if(wave_mode == 2)//方波
        {
            freq_square = freq_wave;
            DL_DMA_disableChannel(DMA, DMA_CH0_CHAN_ID);
            dma_square_init();
            load_value=(uint16_t)((80000000.0/64.0/freq_square)-1);
            DL_Timer_setLoadValue(TIMER_0_INST,load_value);
        }
        else if(wave_mode == 3)//方波
        {
            freq_saw = freq_wave;
            DL_DMA_disableChannel(DMA, DMA_CH0_CHAN_ID);
            dma_saw_init();
            load_value=(uint16_t)((80000000.0/64.0/freq_saw)-1);
            DL_Timer_setLoadValue(TIMER_0_INST,load_value);
        }

        freq_change = 0;
        wave_mode_old = wave_mode;
        freq_wave_old = freq_wave;
    }
}
