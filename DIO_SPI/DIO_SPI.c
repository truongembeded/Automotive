/*
* File: DIO_SPI.c 
* Author: Nguyen Van truong
* Date: 20/10
* Description:  This is file create to write and read data of 
*the spi interface according to the autosar standard(Dio)
*/

#include "DIO_SPI.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
/*
* Function: Spi_Init
* Description: Service for SPI initialization.
* Input:
*   ConfigPtr: Pointer to configuration set
* Output:
*   None
*/
void Spi_Init( Spi_ConfigType* ConfigPtr){
	/* SPI1 configuration ------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	ConfigPtr->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  ConfigPtr->SPI_Mode = SPI_Mode_Master;
  ConfigPtr->SPI_DataSize = SPI_DataSize_16b;
  ConfigPtr->SPI_CPOL = SPI_CPOL_Low;
  ConfigPtr->SPI_CPHA = SPI_CPHA_2Edge;
  ConfigPtr->SPI_NSS = SPI_NSS_Soft;
  ConfigPtr->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  ConfigPtr->SPI_FirstBit = SPI_FirstBit_MSB;
  ConfigPtr->SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, ConfigPtr);
	SPI_Cmd(SPI1, ENABLE);
	/* SPI2 configuration ------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  ConfigPtr->SPI_Mode = SPI_Mode_Slave;
  SPI_Init(SPI2, ConfigPtr);
	SPI_Cmd(SPI2, ENABLE);
}

/*
* Function: Spi_DeInit
* Description: Service for SPI de-initialization.
* Input:
*   None
* Output:
*   E_OK: de-initialisation command has been accepted
*   E_NOT_OK: de-initialisation command has not been accepted
*/
Std_ReturnType Spi_DeInit(void) {
	
	if(SPI1){
		// Disable SPI1
    SPI1->CR1 &= ~SPI_CR1_SPE;
		SPI_Cmd(SPI1, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, DISABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, DISABLE);
		return E_OK;
	}else if(SPI2){
		// Disable SPI2
    SPI2->CR1 &= ~SPI_CR1_SPE;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, DISABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, DISABLE);
		SPI_Cmd(SPI2, DISABLE);
		return E_OK;
	}else
		return E_NOT_OK;
}
/*
* Function: Spi_WriteIB
* Description: Service for writing one or more data to an IB SPI Handler/Driver Channel specified
*by parameter.
* Input:
*   Channel: Channel ID.
*   DataBufferPtr: Pointer to source data buffer. If this pointer is null, it is assumed that
*                  the data to be transmitted is not relevant and the default transmit
*                  value of this channel will be used instead. 
* Output:
*   E_OK: write command has been accepted
*   E_NOT_OK: write command has not been accepted
*/
Std_ReturnType Spi_WriteIB(Spi_ChannelType Channel,
 const Spi_DataBufferType* DataBufferPtr){
	 switch(Channel)
	 {
		 case 1:
			
			RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
			GPIO_InitTypeDef GPIO_InitStruct;
			// GPIO pins for MOSI, MISO, and SCK
			GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
			// GPIO pin for SS
			GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		 
		 if(*DataBufferPtr == '\0'){
				return E_NOT_OK;
		 }
		 
		 while(*DataBufferPtr != '\0'){
			 
			 /* Wait for SPI1 Tx buffer empty */
				while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
				/* Send SPI1 data */
				SPI_I2S_SendData(SPI1, *DataBufferPtr++);
			 
				while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
		 }

		 break;
		 
		 case 2:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
				// GPIO pins for MOSI, MISO, and SCK
				GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13;
				GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOB, &GPIO_InitStruct);
				// GPIO pin for SS
				GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
				GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
				GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
		 
			 if(*DataBufferPtr == '\0')
			{
				return E_NOT_OK;
			}
		 while(*DataBufferPtr != '\0'){
				while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
				/* Send SPI1 data */
				SPI_I2S_SendData(SPI1, *DataBufferPtr++);
				while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET);
		 }
		 break;
			
	}
	  return E_OK;
}
 /*
* Function: Spi_ReadIB
* Description: Service for reading synchronously one or more data from an IB SPI 
*Handler/Driver Channel specified by parameter.
* Input:
*   Channel: Channel ID.
* Output:
*   DataBufferPointer: Pointer to destination data buffer in RAM
*   E_OK: write command has been accepted
*   E_NOT_OK: write command has not been accepted
*/
Std_ReturnType Spi_ReadIB(Spi_ChannelType Channel,
 Spi_DataBufferType* DataBufferPointer){
		switch(Channel)
	 {
		 case 1:
				RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
				GPIO_InitTypeDef GPIO_InitStruct;
				// GPIO pins for MOSI, MISO, and SCK
				GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
				GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
				// GPIO pin for SS
				GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
				GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
				GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		 
		 if(*DataBufferPointer == '\0'){
				return E_NOT_OK;
		 }
		 while(*DataBufferPointer != '\0'){
				/* Wait for SPI2 data reception */
				while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
				*DataBufferPointer++ = (uint8_t)SPI_I2S_ReceiveData(SPI1);
				while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
		 }

		 break;
		 
		 case 2:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
				// GPIO pins for MOSI, MISO, and SCK
				GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13;
				GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOB, &GPIO_InitStruct);
				// GPIO pin for SS
				GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
				GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
				GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOB, &GPIO_InitStruct);
		 
			 if(*DataBufferPointer == '\0'){
				return E_NOT_OK;
		 }
		 while(*DataBufferPointer != '\0'){
				/* Wait for SPI2 data reception */
				while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
				*DataBufferPointer++ =(uint8_t)SPI_I2S_ReceiveData(SPI2);
				while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET);
		 }

		 break;

	}

	 return E_OK;
 }

		 

int main(){

}

