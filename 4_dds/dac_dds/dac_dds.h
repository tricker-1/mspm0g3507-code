#ifndef __dac_dds__h__
#define __dac_dds__h__

extern unsigned char wave_mode;//0:正弦波，1:三角波，2:方波，3:锯齿波
extern float freq_wave;

void dma_wave(void);

#endif
