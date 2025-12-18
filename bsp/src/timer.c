#include "timer.h"

void Timer4_Init(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

    TIM_TimeBaseInitTypeDef TIM_BaseInitStruct;
    TIM_BaseInitStruct.TIM_Prescaler = 84 -1;
    TIM_BaseInitStruct.TIM_Period = 1000000 -1;
    TIM_BaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM4,&TIM_BaseInitStruct);

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
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)){
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

        // static uint8_t led1_on = 0;
        // if (led1_on == 1)
        // {
        //     GPIO_ResetBits(GPIOE,GPIO_Pin_1);
        //     GPIO_SetBits(GPIOE,GPIO_Pin_0);
        //     led1_on = 0;
        // }
        // else{
        //     GPIO_SetBits(GPIOE,GPIO_Pin_1);
        //     GPIO_ResetBits(GPIOE,GPIO_Pin_0);
        //     led1_on = 1;
        // }
        
        static uint8_t led_num = 0;
        if (led_num == 8)
        {
            led_num = 0;
            // return;
        }
        GPIO_SetBits(GPIOE,GPIO_Pin_All);
        GPIO_ResetBits(GPIOE,1<<led_num);
        
        led_num++;
    }
}