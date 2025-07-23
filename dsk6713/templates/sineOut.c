#include<math.h>
#include<dsk6713.h>
#include<dsk6713_aic23.h>
#include<csl_irq.h>
#define BUFFER_NOF 2
#define BUFFER_SZ 512
#define M_PI 3.14

typedef struct{
    Int16 r;
    Int16 l;
}lr;

DSK6713_AIC23_CodecHandle codec;
DSK6713_AIC23_Config cfg = DSK6713_AIC23_DEFAULTCONFIG;
Uint32 buffer[BUFFER_NOF][BUFFER_SZ] = {0};
Int16 sin_array[BUFFER_SZ];
Int16 sin_array2[BUFFER_SZ];
void main(void)
{
    int prIdx, wrIdx, i;
    DSK6713_init();
    cfg.regs[4]=0x15;   //Mic Input; Comment this for Line-in input
    codec = DSK6713_AIC23_openCodec(0, &cfg);
    DSK6713_AIC23_setFreq(codec, DSK6713_AIC23_FREQ_16KHZ);
    for (i=0; i<BUFFER_SZ; i++){
        sin_array[i] = (Int16)((1<<15) * (sin(2*M_PI*10*(double)i/BUFFER_SZ)));   //fout = f*2*fs_in_khz; eg: for fs=16kHz and f=1; fout=2*16=32Hz
        sin_array2[i] = (Int16)((1<<15) * (sin(2*M_PI*20*(double)i/BUFFER_SZ)));
    }
    while(1)
    {
        for (prIdx = 0; prIdx<BUFFER_NOF; prIdx++)
        {
            wrIdx = BUFFER_NOF-1-prIdx;
            for (i=0; i<BUFFER_SZ; i++){
                while(!DSK6713_AIC23_write(codec, buffer[wrIdx][i]));
                while(!DSK6713_AIC23_read(codec, &buffer[wrIdx][i]));
            }
            /*Process buffer[prIdx]*/
            for(i=0; i<BUFFER_SZ; i++){
                ((lr*)(&(buffer[prIdx][i])))->r = sin_array[i];    //sin
                ((lr*)(&(buffer[prIdx][i])))->l = sin_array2[i];
            }
        }
    }
    DSK6713_AIC23_closeCodec(codec);
}
