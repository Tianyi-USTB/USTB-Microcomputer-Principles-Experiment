#include "adc.h"

void ADC1_Init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    ADC_DeInit();

    ADC_CommonInitTypeDef ADC_CommonStruct;
    ADC_CommonStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonStruct.ADC_Prescaler = ADC_Prescaler_Div4;
    ADC_CommonStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonStruct);

    ADC_InitTypeDef ADC_InitStruct;

    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = DISABLE;
    ADC_InitStruct.ADC_NbrOfConversion = 1;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_Init(ADC1,&ADC_InitStruct);
    ADC_Cmd(ADC1,ENABLE);
}

uint16_t GetValueOnce(){
    ADC_RegularChannelConfig(ADC1,ADC_Channel_9,1,ADC_SampleTime_480Cycles);
    ADC_SoftwareStartConv(ADC1);
    while (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == 0);
    return ADC_GetConversionValue(ADC1);
}