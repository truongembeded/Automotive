#include "Dio.h"

void Dio_WriteChannle(Dio_ChannleType Channle1Id, Dio_levelType Level){
		GPIO_TypeDef * gpioPort;
		uint16_t gpioPin;
	
		switch(Channle1Id){
			case DIO_CHANNLE_PA0:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_0;
				break;
			case DIO_CHANNLE_PA1:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_1;
				break;
			case DIO_CHANNLE_PB1:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_1;
				break;
			case DIO_CHANNLE_PC1:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_1;
				break;
			case DIO_CHANNLE_PC13:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_13;
				break;
			default:
				break;
			}
				
		if(Level == STD_LOW){
			GPIO_ResetBits(gpioPort, gpioPin);
		}else{
			GPIO_SetBits(gpioPort, gpioPin);
		}
}

Dio_levelType Dio_ReadChannle(Dio_ChannleType Channle1Id){
		GPIO_TypeDef * gpioPort;
		uint16_t gpioPin;
		switch(Channle1Id){
			case DIO_CHANNLE_PA0:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_0;
				break;
			case DIO_CHANNLE_PA1:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_1;
				break;
			case DIO_CHANNLE_PB1:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_1;
				break;
			case DIO_CHANNLE_PC1:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_1;
				break;
			case DIO_CHANNLE_PC13:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_13;
				break;
			default:
				break;
		}
		
		if(GPIO_ReadInputDataBit(gpioPort, gpioPin) == STD_LOW){
			return STD_LOW;
		}else{
			return STD_HIGH;
		}

}

