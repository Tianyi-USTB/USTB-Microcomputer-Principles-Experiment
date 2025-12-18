#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f4xx.h"
#include "stm32f4xx_adc.h"

void ADC1_Init();
uint16_t GetValueOnce();

#endif