/*
* File: Delay.h 
* Author: Nguyen Van Truong
* Date: 20/10
* Description: This is the file used to delay the timer interups
*/
#ifndef __DELAY_H
#define __DELAY_H


#include "stm32f10x.h"
#include "stm32f10x_tim.h"
static __IO uint32_t CountUs;
void TIM2_IRQHandler(void);
void DelayInit(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);


#endif