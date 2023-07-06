/*
* File: main.c 
* Author: Nguyen Van Truong
* Date: 20/10/2001
* Description: Write functions that perform data to transmited
*/

#include"stm32f10x.h"
#include"Dio.h"
#include"Delay.h"

char spiMasterTX = 'A';


#define SCK 	DIO_CHANNLE_PA5 // chân SCK
#define MOSI 	DIO_CHANNLE_PA7 // chân MOSI
#define SS 		DIO_CHANNLE_PA4 // chân SS
#define MISO 	DIO_CHANNLE_PA6 // chân MISO

void ConfigOut(void);
void SPI_Soft_Init(void);// chuong trình khoi tao SPI
void Clock(void);// chuong trình tao 1 xung clock
void SPI_Soft_Transmit(uint8_t mData);// chuong trình gui 1 byte
uint8_t SPI_Soft_Receive(void);// chuong trình nhan ve 1 byte

/*
* Function: configOut
* Description: Initialize the pins with the corresponding output functions
* Input:
*   None
* Output:
*   Configure pins
*/
void ConfigOut(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio);
	
}
/*
* Function: SPI_Soft_Init
* Description: Set the initial state for the pins
* Input:
*   None
* Output:
*   None
*/

void SPI_Soft_Init(){
	Dio_WriteChannel(SCK, STD_LOW);
	Dio_WriteChannel(MOSI, STD_LOW);
	Dio_WriteChannel(SS, STD_HIGH);
}

/*
* Function: clock
* Description: Set the transmitted clock signal
* Input:
*   None
* Output:
*   None
*/
void Clock(){
	Dio_WriteChannel(SCK, STD_HIGH);
	DelayMs(50);
	Dio_WriteChannel(SCK, STD_LOW);
	DelayMs(50);
}

/*
* Function: SPI_Soft_Transmit
* Description: Transmit data by setting the corresponding output levels
* Input:
*   data: Data to transmitted
* Output:
*   None
*/
void SPI_Soft_Transmit(uint8_t mData){
	
	uint8_t i = 0;
	Dio_WriteChannel(SS, STD_LOW);
	for(i = 0; i < 8; i++){
		if( (mData&0x80) != 0x00) {
			Dio_WriteChannel(MOSI, STD_HIGH);
		}
		else Dio_WriteChannel(MOSI, STD_LOW);
			
		Clock();// goi xung clock de gui tin hieu di
		mData = mData << 1;
	}
		Dio_WriteChannel(SS, STD_HIGH);// gui xong thi tra SS ve 1 lai
}

uint8_t SPI_Soft_Receive(){  
  uint8_t _data=0x00, i=0;  
  while(i<8){     
    _data = _data << 1;       // dich du lieu lên 1 bit     
    _data = _data | MISO;    //doc chân MISO     
    Clock();                // phát mot xung clock de doc bit tiep theo  
  }   
  return _data;         
}

int main(){
	
	ConfigOut();
	/* Initialize timer interrupt */
	TIM2_INT_Init();
	/* Initialize timer delay */
	//TIM1_INT_Init();
	
	/* Initialize SPI */
	SPI_Soft_Init();
	
	/* Initialize clock signal */
	Clock();
	while(1){
		Dio_WriteChannel(SS, STD_LOW);
		SPI_Soft_Transmit(spiMasterTX);
		Dio_WriteChannel(SS, STD_HIGH);
		DelayMs(1000);
		
		if(spiMasterTX== 'Z'){ 
			spiMasterTX = 'A';
		}
		else spiMasterTX++;

	}
}
