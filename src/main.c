
#include "cmsis_gcc.h"
#include "stm32f4xx.h"

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

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

    GPIO_ResetBits(GPIOE, GPIO_Pin_1);

    GPIO_InitStructure.GPIO_Pin   = 0xFF;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

   GPIO_Init(GPIOE, &GPIO_InitStructure);

    while (1) {
        GPIO_ToggleBits(GPIOA, 0xFF);
        Delay(500);
    }
}
