/*
* File: DIO_SPI.h 
* Author: Nguyen Van truong
* Date: 20/10
* Description:  This is file create to define the functions and macros of 
*the spi interface according to the autosar standard(Dio)
*/

#ifndef __DIO_SPI_H
#define __DIO_SPI_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"

/* 
*	Define the pins 4 5 6 and 7 of port A and SPI1
*	According to autosar.
*/
#define SPIx_RCC				RCC_APB2Periph_SPI1
#define SPIx						SPI1
#define SPI_GPIO_RCC		RCC_APB2Periph_GPIOA

#define SPI_GPIO				GPIOA
#define SPI_PIN_MOSI		GPIO_Pin_7
#define SPI_PIN_MISO		GPIO_Pin_6
#define SPI_PIN_SCK			GPIO_Pin_5
#define SPI_PIN_SS			GPIO_Pin_4

/* 
* Defines two values for the return result E_OK and E_NOT_OK. 
*/
typedef uint8_t Std_ReturnType;

#define E_OK 			(Std_ReturnType)0
#define E_NOT_OK 	(Std_ReturnType)1
/*
* This type of the external data structure shall contain the initialization data for the SPI .
*/
typedef SPI_InitTypeDef Spi_ConfigType ;

/*
* This type defines a range of specific status for SPI Handler/Driver
*/
typedef enum {
        SPI_UNINIT,
        SPI_IDLE,
        SPI_BUSY
} Spi_StatusType;


/*
* defines the type of application data buffer elements, Type is uint8_t
*/
typedef uint8_t Spi_DataBufferType;

/*
* Specifies the identification (ID) for a Channel.
*/
typedef uint8_t Spi_ChannelType;

/*
* Service for SPI initialization.
*/
void Spi_Init( Spi_ConfigType* ConfigPtr);

/*
* Service for SPI de-initialization.
*/
Std_ReturnType Spi_DeInit(void);

/*
* Service for writing one or more data to an IB SPI Handler/Driver Channel specified
*	by parameter.
*/
Std_ReturnType Spi_WriteIB(Spi_ChannelType Channel,
 const Spi_DataBufferType* DataBufferPtr);
 
/*
* Service for reading synchronously one or more data from an IB SPI Handler/Driver
Channel specified by parameter.
*/
Std_ReturnType Spi_ReadIB(Spi_ChannelType Channel,
 Spi_DataBufferType* DataBufferPointer);


#endif
