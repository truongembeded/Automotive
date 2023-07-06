/*
* File: main.c 
* Author: Nguyen Van truong
* Date: 20/10
* Description:  This is file create to transmit and receiver data of 
*	the spi hardware 
*/
#include "stm32f10x.h"
#include "Delay.h"



#define BufferSize  10

SPI_InitTypeDef  SPI_InitStructure;
uint16_t SPI1_Buffer_Tx[BufferSize];

uint16_t SPI1_Buffer_Rx[BufferSize];
uint8_t TxIdx = 0, RxIdx = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void SPI1_IRQHandler(void);

int main(void)
{  
	DelayInit();

  RCC_Configuration();

  GPIO_Configuration();

  /* SPI1 configuration ------------------------------------------------------*/
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);

	
		/* Enable SPI1 interrupt */
		NVIC_EnableIRQ(SPI1_IRQn);
		/* Enable SPI1 TXE and RXNE interrupts */
    SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, ENABLE);
    SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);


  /* Enable SPI1 */
  SPI_Cmd(SPI1, ENABLE);


  

  while (1)
  {}
}


void RCC_Configuration(void)
{
  /* PCLK2 = HCLK/2 */
  RCC_PCLK2Config(RCC_HCLK_Div2);


  /* GPIOA, GPIOB and SPI1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

}


void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure SPI1 pins: SCK, MISO and MOSI ---------------------------------*/
  /* Confugure SCK and MOSI pins as Alternate Function Push Pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Confugure MISO pin as Input Floating  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
 
}
void SPI1_IRQHandler(void)
{
  if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_TXE) != RESET)
  {
    /* Handle SPI transmit interrupt */
    if (TxIdx < BufferSize)
    {
      /* Wait for SPI1 Tx buffer empty */
      while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

      /* Send SPI1 data */
      SPI_I2S_SendData(SPI1, SPI1_Buffer_Tx[TxIdx++]);
    }

    if (TxIdx >= BufferSize)
    {
      /* Disable TXE interrupt */
      SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);
    }

    /* Clear the interrupt flag */
    SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_TXE);

  }

  if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_RXNE) != RESET)
  {
    /* Handle SPI receive interrupt */
    if (RxIdx < BufferSize)
    {
      /* Wait for SPI1 data reception */
      while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

      /* Read SPI1 received data */
      SPI1_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI1);
    }

    if (RxIdx >= BufferSize)
    {
      /* Disable RXNE interrupt */
      SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, DISABLE);
    }

    /* Clear the interrupt flag */
    SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_RXNE);
  }
}