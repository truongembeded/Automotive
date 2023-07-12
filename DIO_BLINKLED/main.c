#include "stm32f10x.h"
#include "Dio.h"


void ConfigOut(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOC, &gpio);
}

void Delay(uint32_t t)
{
    for (volatile uint32_t i = 0; i < t; i++)
    {
        for (volatile uint32_t j = 0; j < 1000; j++) {}
    }
}


int main(void){

	ConfigOut();
	
	while(1){
		Dio_WriteChannel(DIO_CHANNLE_PC13, STD_LOW);
		Delay(1000);
		Dio_WriteChannel(DIO_CHANNLE_PC13, STD_HIGH);
		Delay(1000);
	}
	
}




