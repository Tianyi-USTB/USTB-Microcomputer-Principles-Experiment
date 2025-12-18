
#include "printf.h"
#include "cmsis_gcc.h"
#include "stm32f4xx.h"
#include "pot.h"
#include "adc.h"
#include "usart.h"



void SystemClock_Config(void)
{
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    ErrorStatus HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if (HSEStartUpStatus == SUCCESS) {
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;
        PWR->CR |= PWR_CR_PMODE;
        RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);
        RCC_PLLCmd(ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        RCC_PCLK1Config(RCC_HCLK_Div4);
        RCC_PCLK2Config(RCC_HCLK_Div2);
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        while (RCC_GetSYSCLKSource() != 0x08);
    }
}

uint32_t tick = 0;

void SysTick_Handler(void)
{
    tick++;
}

void Delay(uint32_t delay)
{
    uint32_t startTick = tick;
    __NOP();
    while ((tick - startTick) < delay);
}

int main(void)
{
    SystemClock_Config();
    SysTick_Config(SystemCoreClock / 1000); // 1ms tick

    POT_Init();
    ADC1_Init();
    USART1_Init();

    while (1) {
        uint16_t value = GetValueOnce();
        printf("value = %f V \n",value*3.3f/4095.0f);
        Delay(100);
    }
}
