#include "timer.h"

void TIM2_Init(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BaseStruct.TIM_Prescaler = 84 -1;
    TIM_BaseStruct.TIM_Period = 2*1000000/4096 -1;//1000000Hz 1/1000000s 4s一循环 则2秒计数4096次 2/(1/1000000)/4096=2*1000000/4096
    TIM_TimeBaseInit(TIM2,&TIM_BaseStruct);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x0;
    NVIC_Init(&NVIC_InitStruct);

    TIM_Cmd(TIM2,ENABLE);
}

uint16_t cnt = 0;
uint8_t dir = 0;
void TIM2_IRQHandler(){
    if (TIM_GetITStatus(TIM2,TIM_IT_Update))
    {
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
        
        if (dir == 0)
        {
            cnt++;
        }else{
            cnt--;
        }

        if (cnt >= 4095)
        {
            dir = 1;
        }else if (cnt <=0){
            dir = 0;
        }

        DAC_SetChannel1Data(DAC_Align_12b_R,cnt);
    }
    
    
    
}