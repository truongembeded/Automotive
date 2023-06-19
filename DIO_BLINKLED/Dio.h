#include "stm32f10x.h"

#ifndef __DIO_H
#define __DIO_H
typedef enum{
	DIO_CHANNLE_PA0,
	DIO_CHANNLE_PA1,
	DIO_CHANNLE_PA4,
	DIO_CHANNLE_PA5,
	DIO_CHANNLE_PA6,
	DIO_CHANNLE_PA7,
	DIO_CHANNLE_PB1,
	DIO_CHANNLE_PC1,
	DIO_CHANNLE_PC13
}Dio_ChannleType;

typedef enum{
	STD_LOW,
	STD_HIGH
}Dio_levelType;

void Dio_WriteChannle(Dio_ChannleType Channle1Id, Dio_levelType Level);

Dio_levelType Dio_ReadChannle(Dio_ChannleType Channle1Id);

#endif