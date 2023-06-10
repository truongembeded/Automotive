#include "stm32f10x.h"
#include "Dio.h"

void ConfigOut(void){
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_IPU;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio);
}

void ConfigIn(void){
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &gpio);
}


void delay(uint32_t t)
{
    for (volatile uint32_t i = 0; i < t; i++)
    {
        for (volatile uint32_t j = 0; j < 1000; j++) {}
    }
}

void butTon1() {
  if (Dio_ReadChannel(DIO_CHANNLE_PA0) == STD_HIGH) {
    while(1) {
      if (Dio_ReadChannel(DIO_CHANNLE_PA0) != STD_HIGH) Blink(5);
    }
  }
}

void butTon2() {
  if (Dio_ReadChannel(DIO_CHANNLE_PA1) == STD_HIGH) {
	  while(1) {
		  if (Dio_ReadChannel(DIO_CHANNLE_PA1) != STD_HIGH) ChaseLed(5);
		}
  }
}

void butTon3() {
  if (Dio_ReadChannel(DIO_CHANNLE_PA2) == STD_HIGH) Stop();
}


void Blink(uint8_t count)
{
    for (int i = 0; i < count; i++)
    {
				delay(10000);
				Dio_WriteChannel(DIO_CHANNLE_PB5, STD_HIGH);
				Dio_WriteChannel(DIO_CHANNLE_PB6, STD_HIGH);
				Dio_WriteChannel(DIO_CHANNLE_PB7, STD_HIGH);
				delay(10000);
				Dio_WriteChannel(DIO_CHANNLE_PB5, STD_LOW);
				Dio_WriteChannel(DIO_CHANNLE_PB6, STD_LOW);
				Dio_WriteChannel(DIO_CHANNLE_PB7, STD_LOW);
				delay(10000);
    }
				Stop();
}

void ChaseLed(uint8_t count)
{
	for(uint8_t i = 0; i < count; i++){
	 Dio_WriteChannel(DIO_CHANNLE_PB5, STD_HIGH);
		delay(10000);
		Dio_WriteChannel(DIO_CHANNLE_PB5, STD_LOW);
		Dio_WriteChannel(DIO_CHANNLE_PB6, STD_HIGH);
		delay(10000);
		Dio_WriteChannel(DIO_CHANNLE_PB6, STD_LOW);
		Dio_WriteChannel(DIO_CHANNLE_PB7, STD_HIGH);
	  delay(10000);
		Dio_WriteChannel(DIO_CHANNLE_PB7, STD_LOW);

    }
	  Stop();

	}




void Stop()
{
		Dio_WriteChannel(DIO_CHANNLE_PB5, STD_LOW);
		Dio_WriteChannel(DIO_CHANNLE_PB6, STD_LOW);
		Dio_WriteChannel(DIO_CHANNLE_PB7, STD_LOW);
		while(1){
		butTon1();
	  butTon2();
		}
}

int main(void){

	ConfigOut();
	ConfigIn();
	
	while (1)
    {
			butTon1();
			butTon2();
    }
}

