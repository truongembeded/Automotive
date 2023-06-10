#include "Dio.h"

void Dio_WriteChannel(Dio_ChannelType Channel1Id, Dio_levelType Level){
		GPIO_TypeDef * gpioPort;
		uint16_t gpioPin;
	
		switch(Channel1Id){
			case DIO_CHANNLE_PA0:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_0;
				break;
			case DIO_CHANNLE_PA1:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_1;
				break;
			case DIO_CHANNLE_PA2:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_2;
				break;
			case DIO_CHANNLE_PB5:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_5;
				break;
			case DIO_CHANNLE_PB6:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_6;
				break;
			case DIO_CHANNLE_PB7:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_7;
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
/*****************Dio_ReadChannel*********************/
Dio_levelType Dio_ReadChannel(Dio_ChannelType Channel1Id){
		GPIO_TypeDef * gpioPort;
		uint16_t gpioPin;
		switch(Channel1Id){
			case DIO_CHANNLE_PA0:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_0;
				break;
			case DIO_CHANNLE_PA1:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_1;
				break;
			case DIO_CHANNLE_PA2:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_2;
				break;
			case DIO_CHANNLE_PB5:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_5;
				break;
			case DIO_CHANNLE_PB6:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_6;
				break;
			case DIO_CHANNLE_PB7:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_7;
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

