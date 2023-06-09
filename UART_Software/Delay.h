/*
* File: delay.h 
* Author: Nguyen Van Truong
* Date: 20/10
* Description: This is the file used to delay the timer interups
*/
#ifndef __DELAY__H
#define __DELAY__H


#include "stm32f10x.h"
#include "stm32f10x_tim.h"
static __IO uint32_t CountUs;
void TIM2_IRQHandler(void);
void TIM2_INT_Init(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);


#endif
