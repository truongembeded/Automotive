#include "stm32f10x.h"

#ifndef __DIO_H
#define __DIO_H

typedef enum{
	DIO_CHANNLE_PA0,
	DIO_CHANNLE_PA1,
	DIO_CHANNLE_PA2,
	DIO_CHANNLE_PB5,
	DIO_CHANNLE_PB6,
	DIO_CHANNLE_PB7,
}Dio_ChannelType;

typedef enum{
	STD_LOW,
	STD_HIGH
}Dio_levelType;

void ConfigOut(void);
void ConfigIn(void);
void delay(uint32_t t);
void Blink(uint8_t count);
void ChaseLed(uint8_t count);
void Stop();
void butTon1();
void butTon2();
void butTon3();

void Dio_WriteChannel(Dio_ChannelType Channel1Id, Dio_levelType Level);

Dio_levelType Dio_ReadChannel(Dio_ChannelType Channel1Id);

#endif