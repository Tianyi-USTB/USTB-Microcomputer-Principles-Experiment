
#include "cmsis_gcc.h"
#include "stm32f4xx.h"
#include "led.h"
#include "switch.h"
#include "motor.h"

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

uint8_t dir;
uint8_t stop;
int main(void)
{
    SystemClock_Config();
    SysTick_Config(SystemCoreClock / 1000); // 1ms tick
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    LED_Reg_Init();
    Switch_Reg_Init();
    Motor_Init();

    GPIO_SetBits(GPIOE,GPIO_Pin_All);
    

    while (1) {
        uint8_t speed = GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_0);
        stop = GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_1);
        dir = GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_2);
        uint32_t rpm = 2;
        if (speed == 1) rpm = 5;
        
        Motor_Task(stop,dir,rpm);
    }
}
