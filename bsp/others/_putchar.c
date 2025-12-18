#include "usart.h"
void _putchar(uint8_t character){
    //事实上，这里才是真的串口输出，因为我用的armgcc
    while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == 0);
    USART_SendData(USART1,(uint8_t)character);
}