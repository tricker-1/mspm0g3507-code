#include "arm_const_structs.h"
#include "arm_math.h"
#include "ti_msp_dl_config.h"
#include "oled.h"
#include "bmp.h"

#define NUM_SAMPLES 2048
#define average 0.987389

uint32_t count;
uint8_t data;

//uint32_t gDstBuffer[NUM_SAMPLES] ;

float32_t gDstBuffer_f32[NUM_SAMPLES*2] ;

uint16_t gADCSamplesPing[NUM_SAMPLES];

uint16_t Buffer_flag=0;

uint8_t FFT_finish=0;
/* Array with FFT results */
volatile float32_t gFFTOutput[NUM_SAMPLES];
/* Maximum amplitude of FFT */
volatile float32_t gFFTmaxValue;
/* Index of maximum frequency */
volatile uint32_t gFFTmaxFreqIndex;

float wave_freq;

void dma_init()
{
    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,(uint32_t) DL_ADC12_getMemResultAddress(ADC12_0_INST, DL_ADC12_MEM_IDX_0));
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t)&gADCSamplesPing[0]);
    DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, NUM_SAMPLES);
    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
}

int main( void )
{
    SYSCFG_DL_init();
    OLED_Init();		//初始化OLED
    OLED_Clear();

    dma_init();
    NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
    DL_TimerG_startCounter(TIMER_0_INST);

    OLED_ShowString(0,0,(uint8_t *)"WELCOME",8);

    while (1)
    {
        OLED_decimal(0,2,wave_freq,6,1,8);
        if(FFT_finish !=0)
        {
            for(uint16_t i=0;i<NUM_SAMPLES;i++)
            {
                gDstBuffer_f32[2*i]=(gADCSamplesPing[i]*3.3/4095);
                gDstBuffer_f32[2*i+1]=0;
            }
            arm_cfft_f32(&arm_cfft_sR_f32_len2048, (float32_t *) gDstBuffer_f32, 0, 1);
            arm_cmplx_mag_f32((float32_t *) gDstBuffer_f32, (float32_t *) gFFTOutput, NUM_SAMPLES);
            gFFTOutput[0] = 0;
            arm_max_f32((float32_t *) gFFTOutput, NUM_SAMPLES, (float32_t *) &gFFTmaxValue,(uint32_t *) &gFFTmaxFreqIndex);
            FFT_finish = 0;
            if(gFFTmaxFreqIndex>1024)gFFTmaxFreqIndex = 2048 - gFFTmaxFreqIndex;
            wave_freq = (float)gFFTmaxFreqIndex /2048.0*3333.3;  // 采样时间0.3us
            //if(gFFTmaxFreqIndex != 0)
            //OLED_ShowNum(1,1,gFFTmaxFreqIndex,8,12);
            wave_freq = wave_freq / average;
            dma_init();
            DL_TimerG_startCounter(TIMER_0_INST);
        }
    }
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
        case DL_ADC12_IIDX_DMA_DONE:
                    if(FFT_finish == 0)
                    {
                            FFT_finish = 1;
                            DL_TimerG_stopCounter(TIMER_0_INST);
                    }
            break;
        default:
            break;
    }
}
