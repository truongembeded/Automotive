/*
* File: Delay.c 
* Author: Nguyen Van Truong
* Date: 20/10/2001
* Description: this file create timer interrups to write i2c
*/
#include "Delay.h"
uint32_t Count = 0;

uint32_t mircos()
{
	
	
return Count;
}

void TIM2_IRQHandler(){
		if(TIM_GetITStatus(TIM2, TIM_IT_Update)){
	if (CountUs != 0)
	{
		CountUs--;
	}
				Count++;
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		}
}

void TIM2_INT_Init()
{
	// Init struct
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36;
	TIM_TimeBaseInitStruct.TIM_Period = 1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	// Enable TIM2 interrupt
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	// Start TIM2
	TIM_Cmd(TIM2, ENABLE);
	
	// Nested vectored interrupt settings
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}
void DelayUs(uint32_t us)
{
	// Reload us value
	CountUs = us;
	// Wait until usTick reach zero
	while (CountUs);
}

void DelayMs(uint32_t ms)
{
	// Wait until ms reach zero
	while (ms--)
	{
		// Delay 1ms
		DelayUs(1000);
	}
}

