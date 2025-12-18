#include "timer.h"

void Timer2_Init(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    TIM_TimeBaseInitTypeDef TIM_BaseInitStruct;
    TIM_BaseInitStruct.TIM_Prescaler = 84 -1;
    TIM_BaseInitStruct.TIM_Period = 1000 -1;
    TIM_BaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2,&TIM_BaseInitStruct);

    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
}

void Timer2_NVIC_Init(){
    NVIC_InitTypeDef NVIC_InitStruct;

    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
}

void TIM2_IRQHandler(){
    if(TIM_GetFlagStatus(TIM2,TIM_FLAG_Update)){
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

        if (GPIOE->ODR == (1 << 7))
        {
            GPIOE->ODR = 0x1;
            return;
        }
        
        GPIOE->ODR = GPIOE->ODR << 1;
    }
}