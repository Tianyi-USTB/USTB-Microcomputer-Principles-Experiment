#include "led.h"

void LED_Lib_Init(){
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = 0xFF;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void Led_Reg_Init(){
    RCC->APB1ENR |= 1 << 4; 
    GPIOE->MODER = 0x55555555;
    GPIOE->OTYPER = 0x00000000;
    GPIOE->OSPEEDR = 0xFFFFFFFF;
    GPIOE->PUPDR = 0x00000000;
}