#include "dac.h"

void DAC1_Init(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
    
    DAC_InitTypeDef DAC_InitStruct;
    DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
    DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
    DAC_Init(DAC_Channel_1,&DAC_InitStruct);
    DAC_Cmd(DAC_Channel_1,ENABLE);
}