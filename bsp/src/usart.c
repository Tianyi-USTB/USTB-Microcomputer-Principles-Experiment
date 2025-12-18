#include "usart.h"

void USART1_Init(){
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOA,&GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource9 ,GPIO_AF_USART1);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);    
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1,&USART_InitStruct);

    USART_Cmd(USART1,ENABLE);
}

int fputc(int ch,FILE *f){
    while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0);
    USART_SendData(USART1,(uint8_t)ch);
    return ch;
}

