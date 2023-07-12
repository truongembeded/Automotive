/*
* File: Dio.c 
* Author: Nguyen Van Truong
* Date: 20/10
* Description: Declare functions written according to the autosar standard(dio)
*/
#include "Dio.h"
#include"stm32f10x.h"

/*
* Function: Dio_WriteChannel
* Description: Service to set a level of a channel
* Input:
*   ChannelId: ID of DIO channel
*   Level: Value return high or low
* Output:
*   None
*/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_levelType Level){
		GPIO_TypeDef * gpioPort;
		uint16_t gpioPin;
	
		switch(ChannelId){
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
			case DIO_CHANNLE_PA3:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_3;
				break;
			case DIO_CHANNLE_PA4:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_4;
				break;
			case DIO_CHANNLE_PA5:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_5;
				break;
			case DIO_CHANNLE_PA6:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_6;
				break;
			case DIO_CHANNLE_PA7:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_7;
				break;
			case DIO_CHANNLE_PA8:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_8;
				break;
			case DIO_CHANNLE_PA9:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_9;
				break;
			case DIO_CHANNLE_PA10:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_10;
				break;
			case DIO_CHANNLE_PA11:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_11;
				break;
			case DIO_CHANNLE_PA12:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_12;
				break;
			case DIO_CHANNLE_PA13:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_13;
				break;
			case DIO_CHANNLE_PA14:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_14;
				break;
			case DIO_CHANNLE_PA15:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_15;
				break;
			
			case DIO_CHANNLE_PB0:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_0;
				break;
			case DIO_CHANNLE_PB1:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_1;
				break;
			case DIO_CHANNLE_PB3:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_3;
				break;
			case DIO_CHANNLE_PB4:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_4;
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
			case DIO_CHANNLE_PB8:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_8;
				break;
			case DIO_CHANNLE_PB9:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_9;
				break;
			case DIO_CHANNLE_PB10:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_10;
				break;
			case DIO_CHANNLE_PB11:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_11;
				break;
			case DIO_CHANNLE_PB12:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_12;
				break;
			case DIO_CHANNLE_PB13:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_13;
				break;
			case DIO_CHANNLE_PB14:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_14;
				break;
			case DIO_CHANNLE_PB15:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_15;
				break;
			
			
			case DIO_CHANNLE_PC13:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_13;
				break;
			case DIO_CHANNLE_PC14:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_14;
				break;
			
			case DIO_CHANNLE_PC15:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_15;
				break;
			
			}
				
		if(Level == STD_LOW){
			GPIO_ResetBits(gpioPort, gpioPin);
		}else{
			GPIO_SetBits(gpioPort, gpioPin);
		}
}
/*
* Function: Dio_ReadChannel
* Description: Returns the value of the specified DIO channel.
* Input:
*   ChannelId: ID of DIO channel
* Output:
*   Dio_LevelType: 
*     STD_HIGH The physical level of Pin is STD_HIGH
*     STD_LOW The physical level of Pin is STD_LOW
*/
Dio_levelType Dio_ReadChannel(Dio_ChannelType Channe1Id){
		GPIO_TypeDef * gpioPort;
		uint16_t gpioPin;
		switch(Channe1Id){
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
			case DIO_CHANNLE_PA3:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_3;
				break;
			case DIO_CHANNLE_PA4:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_4;
				break;
			case DIO_CHANNLE_PA5:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_5;
				break;
			case DIO_CHANNLE_PA6:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_6;
				break;
			case DIO_CHANNLE_PA7:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_7;
				break;
			case DIO_CHANNLE_PA8:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_8;
				break;
			case DIO_CHANNLE_PA9:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_9;
				break;
			case DIO_CHANNLE_PA10:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_10;
				break;
			case DIO_CHANNLE_PA11:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_11;
				break;
			case DIO_CHANNLE_PA12:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_12;
				break;
			case DIO_CHANNLE_PA13:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_13;
				break;
			case DIO_CHANNLE_PA14:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_14;
				break;
			case DIO_CHANNLE_PA15:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_15;
				break;
			
			case DIO_CHANNLE_PB0:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_0;
				break;
			case DIO_CHANNLE_PB1:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_1;
				break;
			case DIO_CHANNLE_PB3:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_3;
				break;
			case DIO_CHANNLE_PB4:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_4;
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
			case DIO_CHANNLE_PB8:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_8;
				break;
			case DIO_CHANNLE_PB9:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_9;
				break;
			case DIO_CHANNLE_PB10:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_10;
				break;
			case DIO_CHANNLE_PB11:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_11;
				break;
			case DIO_CHANNLE_PB12:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_12;
				break;
			case DIO_CHANNLE_PB13:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_13;
				break;
			case DIO_CHANNLE_PB14:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_14;
				break;
			case DIO_CHANNLE_PB15:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_15;
				break;

			case DIO_CHANNLE_PC13:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_13;
				break;
			case DIO_CHANNLE_PC14:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_14;
				break;
			
			case DIO_CHANNLE_PC15:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_15;
				break;
			
		}
		
		if(GPIO_ReadInputDataBit(gpioPort, gpioPin) == STD_LOW){
			return STD_LOW;
		}else{
			return STD_HIGH;
		}

}
/*
* Function: Dio_ReadPort
* Description: Returns the level of all channels of that port
* Input:
		PortId : ID of DIO Port
* Output:
*   Dio_PortLevelType : Level of all channels of that port
*/
uint16_t Dio_ReadPort( Dio_PortType PortId ){
		uint16_t data;
	switch(PortId)
		{
				case DIO_A :
						data = GPIO_ReadInputData(GPIOA);
            break;
			
			case DIO_B :
						data = GPIO_ReadInputData(GPIOB);
            break;
						
			case DIO_C :
						data = GPIO_ReadInputData(GPIOC);
            break;
			
		}
		
		return data ;
}

/*
* Function: Dio_WritePort
* Description: Service to set a value of the port.
* Input:
*   PortId : ID of DIO Port
		Level  : Value to be written
* Output: none
*/
void Dio_WritePort(Dio_PortType PortId, uint8_t Level)
{
    switch (PortId)
    {
        case DIO_A:
            GPIO_Write(GPIOA, Level);
            break;

        case DIO_B:
            GPIO_Write(GPIOB, Level); 
            break;

        case DIO_C:
            GPIO_Write(GPIOC, Level);
            break;

    }
}
/*
* Function: Dio_FlipChannel
* Description: Service to flip (change from 1 to 0 or from 0 to 1) the level of a channel and return 
the level of the channel after flip.
* Input:
*   ChannelId: ID of DIO channel
* Output:
*   Dio_LevelType: 
*     STD_HIGH The physical level of the corresponding Pin is STD_HIGH
*     STD_LOW The physical level of the corresponding Pin is STD_LOW
*/
Dio_levelType Dio_FlipChannel (Dio_ChannelType Channe1Id){
		GPIO_TypeDef * gpioPort;
		uint16_t gpioPin;
		switch(Channe1Id){
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
			case DIO_CHANNLE_PA3:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_3;
				break;
			case DIO_CHANNLE_PA4:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_4;
				break;
			case DIO_CHANNLE_PA5:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_5;
				break;
			case DIO_CHANNLE_PA6:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_6;
				break;
			case DIO_CHANNLE_PA7:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_7;
				break;
			case DIO_CHANNLE_PA8:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_8;
				break;
			case DIO_CHANNLE_PA9:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_9;
				break;
			case DIO_CHANNLE_PA10:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_10;
				break;
			case DIO_CHANNLE_PA11:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_11;
				break;
			case DIO_CHANNLE_PA12:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_12;
				break;
			case DIO_CHANNLE_PA13:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_13;
				break;
			case DIO_CHANNLE_PA14:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_14;
				break;
			case DIO_CHANNLE_PA15:
				gpioPort = GPIOA;
				gpioPin = GPIO_Pin_15;
				break;
			
			case DIO_CHANNLE_PB0:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_0;
				break;
			case DIO_CHANNLE_PB1:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_1;
				break;
			case DIO_CHANNLE_PB3:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_3;
				break;
			case DIO_CHANNLE_PB4:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_4;
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
			case DIO_CHANNLE_PB8:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_8;
				break;
			case DIO_CHANNLE_PB9:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_9;
				break;
			case DIO_CHANNLE_PB10:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_10;
				break;
			case DIO_CHANNLE_PB11:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_11;
				break;
			case DIO_CHANNLE_PB12:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_12;
				break;
			case DIO_CHANNLE_PB13:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_13;
				break;
			case DIO_CHANNLE_PB14:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_14;
				break;
			case DIO_CHANNLE_PB15:
				gpioPort = GPIOB;
				gpioPin = GPIO_Pin_15;
				break;
			
			case DIO_CHANNLE_PC13:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_13;
				break;
			case DIO_CHANNLE_PC14:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_14;
				break;
			
			case DIO_CHANNLE_PC15:
				gpioPort = GPIOC;
				gpioPin = GPIO_Pin_15;
				break;
			
		}
		
		if(GPIO_ReadInputDataBit(gpioPort, gpioPin) == STD_LOW){
			return STD_HIGH;
		}else{
			return STD_LOW;
		}

}




