#include "delay.h"

void Delayms(void)
{
	TIM_SetCounter(TIM2, 0);
	while(TIM_GetCounter(TIM2) < 1000){}
}

void DelayMs(uint32_t t)
{
	// Wait until ms reach zero
	while(t){
		Delayms();
		t--;
	}
}

void DelayInit()
{
	// Init struct
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// TIM2 initialization for overflow every 1ms
	// Update Event (Hz) = timer_clock / ((TIM_Prescaler + 1) * (TIM_Period + 1))
	// Update Event (Hz) = 72MHz / ((71 + 1) * (0 + 1)) = 1000000Hz (0.001s)
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72;
	TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	// Enable TIM2 interrupt
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	// Start TIM2
	TIM_Cmd(TIM2, ENABLE);
}
