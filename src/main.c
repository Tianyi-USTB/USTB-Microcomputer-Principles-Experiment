
#include "cmsis_gcc.h"
#include "stm32f4xx.h"
#include "led.h"
#include "timer.h"

void SystemClock_Config(void)
{
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    ErrorStatus HSEStartUpStatus = RCC_WaitForHSEStartUp();
    
    if (HSEStartUpStatus == SUCCESS) {
        // 配置FLASH等待周期（168MHz必须）
        FLASH_SetLatency(FLASH_Latency_5);
        FLASH_PrefetchBufferCmd(ENABLE);
        FLASH_InstructionCacheCmd(ENABLE);
        FLASH_DataCacheCmd(ENABLE);
        
        // 使能电源时钟并设置性能模式
        RCC->APB1ENR |= RCC_APB1Periph_PWR;
        PWR->CR |= PWR_CR_VOS;
        
        // 配置PLL
        RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 7);
        RCC_PLLCmd(ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        
        // 配置分频
        RCC_HCLKConfig(RCC_SYSCLK_Div1);     // HCLK = 168MHz
        RCC_PCLK1Config(RCC_HCLK_Div4);     // APB1 = 42MHz
        RCC_PCLK2Config(RCC_HCLK_Div2);     // APB2 = 84MHz
        
        // 切换到PLL
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        while (RCC_GetSYSCLKSource() != 0x08);
        
        // 更新SystemCoreClock变量
        SystemCoreClockUpdate();
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

    LED_Init();
    GPIOE->ODR = ~(0x1);

    Timer4_Init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Timer4_NVIC_Init();
    TIM_Cmd(TIM4,ENABLE);

    while (1) {
        // Delay(500);
    // GPIO_ResetBits(GPIOE,GPIO_Pin_All);
    }
}
