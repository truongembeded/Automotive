/*
* File: main.c 
* Author: Nguyen Van Truong
* Date: 20/10/2001
* Description: Perform data transmission and Receivetion with uart method
*/
#include "stm32f10x.h"
#include "Delay.h"
#include "Dio.h"

#define Tx DIO_CHANNLE_PA9
#define Rx DIO_CHANNLE_PA10
#define size 6
char data[size];
char Uart_received[size];
uint8_t TxIdx = 0;
uint8_t RxIdx = 0;

void config(void);
void Uart_init(void);
void Uart_transmit(uint8_t mData);
uint8_t Uart_recieve(void);
void Delay(void);

// Hàm tao do tre 1 bit cho baud rate 9600
void Delay() {
  uint32_t delay_count = SystemCoreClock / 9600;

  while (delay_count--) {
    __NOP();  // No-operation do toc do tre
  }
}

int main(){
	config();
	/* Initialize timer interrupt */
	TIM2_INT_Init();
	
	/* Initialize UART */
	Uart_init();
	
	while(1){
		// Transmition
		if(TxIdx < size)
		{
			Uart_transmit(data[TxIdx++]);
		}
	//Receivetion
		if(RxIdx < size)
		{
				Uart_received[RxIdx++] = Uart_recieve();
		}
	}
}
/*
* Function: config
* Description: Initialize the pins with the corresponding output functions
* Input:
*   None
* Output:
*   Configure pins
*/
void config() {
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	
	gpio.GPIO_Pin = Tx;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
	
	gpio.GPIO_Pin = Rx;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_13;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio);
}
/*
* Function: Uart_init
* Description: Initialize the pins Tx and Rx is STD_HIGH
* Input:
*   None
* Output:
*   None
*/
void Uart_init(){
	Dio_WriteChannel(Tx, STD_HIGH);
	Dio_WriteChannel(Rx, STD_HIGH);
}
/*
* Function: Uart_transmit
* Description: the function used to transmit by uart method
* Input:
*   uint8_t mData : data to be transmited
* Output:
*   None
*/
void Uart_transmit(uint8_t mData){
	Dio_WriteChannel(Tx, STD_LOW);
	DelayMs(1000);
	Dio_WriteChannel(Tx, STD_HIGH);// send bit start
	Delay();

	for(uint8_t i = 0; i < 8; i++){
		if( mData & (1 << i)) {
			Dio_WriteChannel(Tx, STD_HIGH);
		} else {
			Dio_WriteChannel(Tx, STD_LOW);
		}
			Delay();
	}
	Dio_WriteChannel(Tx, STD_LOW);// send bit stop
	
	Delay();
}
/*
* Function: Uart_recieve
* Description: the function used to recieved by uart method
* Input:
*   None
* Output:
*   received_byte : data to be received
*/
uint8_t Uart_recieve(){
	// wait to until when bit start
  while (!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10)) {}  // GPIOA Pin 10 (RX) là muc cao
  Delay();
		
	uint8_t received_byte = 0;
	for(uint8_t i = 0; i < 8; i++){
		
		if(Dio_ReadChannel(Rx) == STD_HIGH){
			uint8_t bit_value = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10);  // Read trang thái GPIOA Pin 10 (RX)
			received_byte |= (bit_value << i);
			Delay();
		}
	}
	return received_byte;
}
