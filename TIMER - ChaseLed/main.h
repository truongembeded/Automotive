/*
* File: main.h 
* Author: Nguyen Van Truong
* Date: 20/10
* Description: file used to initialize functions
*/
#ifndef __MAIN_H
#define __MAIN_H

#include"stm32f10x.h"

typedef struct {
		void(*func)();
		uint32_t time;
		uint32_t delay;
}Tasks;

uint32_t Count = 0;
void config(void);
uint32_t millis(void);
void TIM2_IRQHandler(void);
void TIM2_INT_Init(void);
void multitasks(Tasks *task);
void LED1(void);
void LED2(void);
void LED3(void);
void LED4(void);

#endif