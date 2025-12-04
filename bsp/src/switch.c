#include "switch.h"
void Switch_Lib_Init(){
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = 0xFF;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
}

void Switch_Reg_Init(){
    RCC->AHB1ENR |= 1 << 5;
    GPIOF->MODER = 0x00000000;
    GPIOF->PUPDR = 0x55555555;
}