#include "timer.h"

void Timer4_Init(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

    TIM_TimeBaseInitTypeDef TIM_BaseInitStruct;
    TIM_BaseInitStruct.TIM_Prescaler = 84 -1;
    TIM_BaseInitStruct.TIM_Period = 1500 -1;
    TIM_BaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM4,&TIM_BaseInitStruct);

    TIM_OCInitTypeDef TIM_OCStruct;
    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCStruct.TIM_Pulse = 0;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;

    TIM_OC4Init(TIM4,&TIM_OCStruct);
    TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);

    TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
}

void Timer4_NVIC_Init(){
    NVIC_InitTypeDef NVIC_InitStruct;

    NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStruct);
}

void TIM4_IRQHandler(){
    if(TIM_GetITStatus(TIM4,TIM_IT_Update)){
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);

        static uint16_t cnt = 0;
        static uint8_t status = 0;//0==UP 1==DOWN
        
        if (status == 0){
            cnt++;
        }else{
            cnt--;
        }

        if (cnt >= 1000)
        {
            status = 1;
        }if (cnt == 0)
        {
            status = 0;
        }
        

        TIM_SetCompare4(TIM4,cnt);
        
    }
}