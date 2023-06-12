#include"stm32f10x.h"
#include"main.h"

void config(){
		GPIO_InitTypeDef GPIO_InitStruct;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; 
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init (GPIOB, &GPIO_InitStruct);
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13; 
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init (GPIOC, &GPIO_InitStruct);
	
}

uint32_t millis()
{
	
	
return Count;
}

void TIM2_IRQHandler(){
		if(TIM_GetITStatus(TIM2, TIM_IT_Update)){
	
				Count++;
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		}
}


void multitasks(Tasks *task){
		if(millis() - task->time >= task->delay){
			task->func();
			task->time = millis();

		}
}

void LED1(){
	GPIOB->ODR ^= GPIO_Pin_5;
}

void LED2(){
	GPIOB->ODR ^= GPIO_Pin_6;
}

void LED3(){
	GPIOB->ODR ^= GPIO_Pin_7;
}

void LED4(){
	GPIOC->ODR ^= GPIO_Pin_13;
}


int main(){

		Tasks task1 = {.func = &LED1, .time = millis(),.delay = 1000};
		Tasks task2 = {.func = &LED2, .time = millis(),.delay = 2000};
		Tasks task3 = {.func = &LED3, .time = millis(),.delay = 3000};
		Tasks task4 = {.func = &LED4, .time = millis(),.delay = 4000};
	
	
		TIM2_INT_Init();
		config();
		
	
	while(1){
		
		multitasks(&task1);
		multitasks(&task2);
		multitasks(&task3);
		multitasks(&task4);
				
	}
}


void TIM2_INT_Init(){
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	

		TIM_TimeBaseInitStruct.TIM_Prescaler = 3599;
		TIM_TimeBaseInitStruct.TIM_Period = 19;
		TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
		//enable TIM2 interup
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
		//start TIM2
		TIM_Cmd(TIM2, ENABLE);
	
		NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;// cau hinh ngat timer2
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00; // InterrupPriority
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;// turn on Timer2
		NVIC_Init(&NVIC_InitStruct);
}