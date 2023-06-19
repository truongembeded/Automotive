#include "stm32f10x.h"

#ifndef __DIO_H
#define __DIO_H
typedef enum{
	DIO_CHANNLE_PA0,
	DIO_CHANNLE_PA1,
	DIO_CHANNLE_PA2,
	DIO_CHANNLE_PA3,
	DIO_CHANNLE_PA4,
	DIO_CHANNLE_PA5,
	DIO_CHANNLE_PA6,
	DIO_CHANNLE_PA7,
	DIO_CHANNLE_PA8,
	DIO_CHANNLE_PA9,
	DIO_CHANNLE_PA10,
	DIO_CHANNLE_PA11,
	DIO_CHANNLE_PA12,
	DIO_CHANNLE_PA13,
	DIO_CHANNLE_PA14,
	DIO_CHANNLE_PA15,
	
	DIO_CHANNLE_PB0,
	DIO_CHANNLE_PB1,
	DIO_CHANNLE_PB3,
	DIO_CHANNLE_PB4,
	DIO_CHANNLE_PB5,
	DIO_CHANNLE_PB6,
	DIO_CHANNLE_PB7,
	DIO_CHANNLE_PB8,
	DIO_CHANNLE_PB9,
	DIO_CHANNLE_PB10,
	DIO_CHANNLE_PB11,
	DIO_CHANNLE_PB12,
	DIO_CHANNLE_PB13,
	DIO_CHANNLE_PB14,
	DIO_CHANNLE_PB15,
	
	DIO_CHANNLE_PC13,
	DIO_CHANNLE_PC14,
	DIO_CHANNLE_PC15
	
}Dio_ChannelType;

typedef enum 
{
	DIO_A,
	DIO_B,
	DIO_C
	
}Dio_PortType;

typedef enum{
	STD_LOW,
	STD_HIGH
}Dio_levelType;

typedef struct
{
  uint8_t mask;
  uint8_t offset;
  Dio_PortType Port;
} Dio_ChannelGroupType;

typedef uint8_t Dio_PortLevelType;

/*
	Service Name	: Dio_ReadChannel
	Description		: Returns the value of the specified DIO channel.	
	Parameters		: ID of DIO channel
	Return value	: Dio_Level-Type (HIGH or LOW)
*/
Dio_levelType Dio_ReadChannel			( Dio_ChannelType ChannelId );

/*
	Service Name	: Dio_WriteChannel
	Description		: Service to set a level of a channel.	
	Parameters		: ID of DIO channel - Value to be written
	Return value	: None
*/
void Dio_WriteChannel					( Dio_ChannelType ChannelId, Dio_levelType Level );

/*
	Service Name	: Dio_ReadPort
	Description		: Returns the level of all channels of that port.	
	Parameters		: ID of DIO Port
	Return value	: Dio_PortLevelType
*/
uint16_t Dio_ReadPort						( Dio_PortType PortId );

/*
	Service Name	: Dio_WritePort
	Description		: Service to set a value of the port.	
	Parameters		: ID of DIO Port - Value to be written
	Return value	: None
*/
void Dio_WritePort						( Dio_PortType PortId, uint8_t Level );

/*
	Service Name	: Dio_FlipChannel
	Description		: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel.	
	Parameters		: ID of DIO channel
	Return value	: None
*/
Dio_levelType Dio_FlipChannel (Dio_ChannelType ChannelId);

#endif