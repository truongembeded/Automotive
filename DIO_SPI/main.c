#include "DIO_SPI.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
int *send = 0;

int main(){
	Std_ReturnType Spi_DeInit(void);
	void Spi_Init( Spi_ConfigType* ConfigPtr);
	Std_ReturnType Spi_WriteIB(SPI1, *send);
	
	
	
	while(1){}
}