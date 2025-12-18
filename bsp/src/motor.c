#include "motor.h"

const uint8_t pluse4[4] = {0x02,0x10,0x08,0x04};
const uint8_t pluse8[8] = {0x02,0x12,0x10,0x18,0x08,0x0C,0x04,0x06};

//8拍需要4096个脉冲一圈，4拍需要2048个脉冲一圈
#define RPM2PERIOD4PLUSE(x) (84000000 / 84 * 60 / 2048 / x -1)
#define RPM2PERIOD8PLUSE(x) (84000000 / 84 * 60 / 4096 / x -1)
#define PLUSE4

void Timer2_Init(){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    TIM_TimeBaseInitTypeDef TIM_BaseInitStruct;
    TIM_BaseInitStruct.TIM_Prescaler = 84 -1;
    TIM_BaseInitStruct.TIM_Period = RPM2PERIOD4PLUSE(10);
    TIM_BaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2,&TIM_BaseInitStruct);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_ARRPreloadConfig(TIM2,ENABLE);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    TIM_Cmd(TIM2,ENABLE);
}

void Motor_Init(){
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD,&GPIO_InitStruct);

    Timer2_Init();
}

uint32_t index = 0;
void Motor_Task(uint8_t stop,uint8_t dir,uint32_t rpm){
    if (stop == 0)
    {
        GPIOD->ODR = 0;
        GPIO_ResetBits(GPIOE,GPIO_Pin_0);
    }else{
        GPIO_SetBits(GPIOE,GPIO_Pin_0);
        #ifdef PLUSE4
        GPIOD->ODR = pluse4[index%4];
        TIM_SetAutoreload(TIM2,RPM2PERIOD4PLUSE(rpm));
        #endif
        #ifdef PLUSE8
        GPIO->ODR = pluse8[index%8];
        TIM_SetAutoreload(TIM2,RPM2PERIOD8PLUSE(rpm));
        #endif
    }
}

extern uint8_t dir;
extern uint8_t stop;
void TIM2_IRQHandler(){
    if (TIM_GetITStatus(TIM2,TIM_IT_Update))
    {
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
        
        if (stop == 0)
        {
            return;
        }
        

        if (dir == 0)
        {
            index++;
        }else{
            index--;
        }
    }
    
    
}
