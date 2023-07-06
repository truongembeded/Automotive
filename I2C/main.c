#include"stm32f10x.h"
#include "stm32f10x_i2c.h"
#include"Dio.h"
#include"Delay.h"

#define buffsize 16
char dataSend[buffsize];
char dataGet[buffsize] ;
uint8_t Send = 0;
uint8_t Get = 0;

#define I2C_PIN_SDA			DIO_CHANNLE_PB9
#define I2C_PIN_SCL			DIO_CHANNLE_PB8

/*
 * Function: MACRO SCL_HIGH, MACRO SCL_LOW
 * Description: Set up for SCL to be HIGH or LOW
 */
#define SCL_HIGH 	Dio_WriteChannel(I2C_PIN_SCL, STD_HIGH)
#define SCL_LOW 	Dio_WriteChannel(I2C_PIN_SCL, STD_LOW)

/*
 * Function: MACRO SDA_HIGH, MACRO SDA_LOW
 * Description: Set up for SDA to be HIGH or LOW
 */
#define SDA_HIGH 	Dio_WriteChannel(I2C_PIN_SDA, STD_HIGH)
#define SDA_LOW 	Dio_WriteChannel(I2C_PIN_SDA, STD_LOW)

#define SDA_IN()  do { \
                    GPIO_InitTypeDef GPIO_InitStruct; \
                    GPIO_InitStruct.GPIO_Pin = I2C_PIN_SDA; \
                    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; \
                    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; \
                    GPIO_Init(GPIOB, &GPIO_InitStruct); \
                  } while(0)

#define SDA_OUT() do { \
                    GPIO_InitTypeDef GPIO_InitStruct; \
                    GPIO_InitStruct.GPIO_Pin =I2C_PIN_SDA; \
                    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; \
                    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; \
                    GPIO_Init(GPIOB, &GPIO_InitStruct); \
                  } while(0)
#define SCL_IN()  do { \
                    GPIO_InitTypeDef GPIO_InitStruct; \
                    GPIO_InitStruct.GPIO_Pin = I2C_PIN_SCL; \
                    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; \
                    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; \
                    GPIO_Init(GPIOB, &GPIO_InitStruct); \
                  } while(0)

#define SCL_OUT() do { \
                    GPIO_InitTypeDef GPIO_InitStruct; \
                    GPIO_InitStruct.GPIO_Pin =I2C_PIN_SCL; \
                    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; \
                    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; \
                    GPIO_Init(GPIOB, &GPIO_InitStruct); \
                  } while(0)
#define SLAVE_ADDRESS		0x08	


void i2c_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
uint8_t I2C_Get_Nack_Ack(void);
uint8_t SendData(uint8_t mData);
uint8_t ReadData(void);
void Clock(void);
uint8_t frameAddress(uint8_t addressSlave, uint8_t mode);
									
/*
  Function: i2cInit
  Description: i2c protocol start function, pin SDA & SCL pulled to a high level
  Input:
    No input
  Output:
    No return
*/
void i2c_Init(){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	SCL_OUT();		
	SDA_OUT();
	SCL_HIGH;
	SDA_HIGH;
	
}
int main(){
	
	i2c_Init();
	TIM2_INT_Init();
	Clock();
	while(1){
		if(Send < buffsize){
				frameAddress(SLAVE_ADDRESS, 0);
        SendData(dataSend[Send++]);
				DelayMs(100);
        I2C_Stop();
		}
		if(Get < buffsize){
				SDA_OUT();
        frameAddress(SLAVE_ADDRESS, 1);
        dataGet[Get++] = ReadData();
				DelayMs(100);
        I2C_Stop();
		}
	}
}
/*
  Function: frameAddress
  Description: (7 bits) + 1 bit Write/Read
  Input:
    addressSlave - uint8_t
    mode - uint8_t
  Output:
    returns frameAddress
*/
uint8_t frameAddress(uint8_t addressSlave, uint8_t level)
{
	I2C_Start();
	if(level == 0){
		return SendData(addressSlave);
	}else if(level == 1){
		return ReadData();
	}
	
  return ((addressSlave << 1) | level);
}
/*
  Function: clockSignal
  Description: clock generator function, used to synchronize the transmission signal
  Input:
    No input
  Output:
    No return
*/
void Clock(){
	SCL_HIGH;
	DelayMs(10);
	SCL_LOW;
	DelayMs(10);
}
/*
  Function: startI2C
  Description: the signal Start protocol I2C, SDA pulled to be LOW then SCL pulled to be LOW
  Input:
    No input
  Output:
    No return
*/
void I2C_Start(){
	SDA_OUT();
	SCL_OUT();
	SCL_HIGH;
	SDA_HIGH;
	DelayMs(5);
	SDA_LOW;
	DelayMs(5);
	SCL_LOW;
	
}
/*
  Function: stopI2C
  Description: the signal Stop protocol I2C, SCL pulled up HIGH and then SDA pulled up HIGH
  Input:
    No input
  Output:
    No return
*/
void I2C_Stop(){
	SDA_OUT();
	SCL_OUT();
	SCL_LOW;
	SDA_LOW;
	DelayMs(5);
	SCL_HIGH;
	DelayMs(5);
	SDA_HIGH;
}
/*
  Function: I2C_Get_Nack_Ack
  Description: get bits Ack/Nack after 1 byte transfer
  Input:
    No input
  Output:
     return Ack/Nack
*/
uint8_t I2C_Get_Nack_Ack(){
	SDA_IN();
	DelayMs(2);
	Clock();
	unsigned long timeOut = mircos();
	while(1){
		if(Dio_ReadChannel(I2C_PIN_SDA) == STD_LOW){
			SDA_OUT();
			DelayMs(2);
			return 1;
		}
		if( mircos() - timeOut > 50){
			SDA_OUT();
			DelayMs(2);
			return 0;
		}
	}
		
}
/*
  Function: SendData
  Description: function send 1 byte data 
  Input:
    mData - uint8_t
  Output:
    Return ACK/NACK
*/
uint8_t SendData(uint8_t mData){
	for(uint8_t i = 0; i < 8; i++){
		if( mData & (1 << i)) {
			SDA_HIGH;
		}else{
			SDA_LOW;
		}
		Clock();
	}
	return I2C_Get_Nack_Ack();
}
/*
  Function: ReadData
  Description: Read function data to be recieved
  Input:
    No input
  Output:
    Return ACK/NACK
*/
uint8_t ReadData(){
	uint8_t received_byte = 0x00;
	SDA_IN();
	for(uint8_t i = 0; i < 8; i++){
		Clock();
		uint8_t bit_value = GPIO_ReadInputDataBit(GPIOB,I2C_PIN_SDA );
		received_byte |= (bit_value << i);
		
	}
	return I2C_Get_Nack_Ack();
}
