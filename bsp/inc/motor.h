#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "stm32f4xx.h"

extern const uint8_t pluse4[4];

void Motor_Init();
void Motor_Task(uint8_t stop,uint8_t dir,uint32_t delay);
#endif