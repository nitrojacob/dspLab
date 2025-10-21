/*
 loopback.c
 Read left and right channel samples from the ADC and loop
 them back out to the DAC. Do this repeatedly
 */
#include <dsk6713.h>
#include <dsk6713_aic23.h>

typedef struct{
    Int16 r;
    Int16 l;
}lr;

typedef union{
    lr c;    /* c - Component */
    Uint32 u;/* u - Uint */
}lru;

void main(void)
{
    DSK6713_AIC23_Config config = DSK6713_AIC23_DEFAULTCONFIG;
    DSK6713_AIC23_CodecHandle hCodec;
    lru sample;
    DSK6713_init(); /* In the BSL library */
    /* Start the codec */
    config.regs[4]=0x15;   /* Mic Input; Comment this for Line-in input */
    hCodec = DSK6713_AIC23_openCodec(0, &config);

    /* Change the sampling rate to 16 kHz */
    DSK6713_AIC23_setFreq(hCodec, DSK6713_AIC23_FREQ_16KHZ);

    for (;;){
        /* Read one sample from codec */
        while (!DSK6713_AIC23_read(hCodec, &(sample.u)));
        
        /* Process the sample */
        sample.c.l *= 10;   /* Gain of 10 for left channel */
        sample.c.r *= 10;   /* Gain of 10 for right channel */
    
        /* Write the sample to codec */
        while (!DSK6713_AIC23_write(hCodec, sample.u));
    }
}
