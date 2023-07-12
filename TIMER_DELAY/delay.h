/*
* File: Delay.h 
* Author: Nguyen Van Truong
* Date: 20/10
* Description: This is the file used to delay the timer delay
*/
#ifndef __DELAY_H
#define __DELAY_H


#include "stm32f10x.h"
#include "stm32f10x_tim.h"

void DelayInit(void);
void DelayMs(uint32_t us);
void Delayms(void);


#endif