#include"delay.h"
/*
* File: main.c 
* Author: Nguyen Van Truong
* Date: 20/10/2001
* Description: this file create timer delay to blink led arcoding to asked
*/
int main(){
		DelayInit();
	
		GPIO_InitTypeDef GPIO_InitStruct;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init (GPIOC, &GPIO_InitStruct);
	
	while(1){
		GPIOC->BRR = GPIO_Pin_13;
		DelayMs(500);//0.5s
		GPIOC->BSRR = GPIO_Pin_13;
		DelayMs(500);
	}
}
