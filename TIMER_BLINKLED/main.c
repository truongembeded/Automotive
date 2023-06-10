#include"delay.h"

int main(){
		DelayInit();
	
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
	
	while(1){
		GPIOC->BRR = GPIO_Pin_13;
		DelayMs(1000);
		GPIOC->BSRR = GPIO_Pin_13;
		DelayMs(1000);
	}
}
