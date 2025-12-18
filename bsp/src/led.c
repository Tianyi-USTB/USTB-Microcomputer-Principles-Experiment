#include "led.h"

void LED_Init(){
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
    // GPIO_InitTypeDef GPIO_InitStruct;
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    // GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
    // GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    // GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    // GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;

    // GPIO_Init(GPIOE,&GPIO_InitStruct);
}