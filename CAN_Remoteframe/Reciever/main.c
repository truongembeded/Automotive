/*
* File: main.c 
* Author: Nguyen Van Truong
* Date: 20/10
* Description: This file is created to receive request and feedback pressure data to the specified node
*/
#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void init_can(void);
void respond_To_Data_Request(uint8_t *data, uint8_t len);

/*
* Function: init_can
* Description: Configuration communication CAN
* Input:
*   can_id: ID of NODE
* Ouput: 
*   None
*/
void init_can(){
    GPIO_InitTypeDef            GPIO_InitStructure;
    CAN_InitTypeDef             CAN_InitStructure;
    CAN_FilterInitTypeDef       CAN_FilterInitStructure;

    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  
    /* CAN Baudrate = 1MBps*/
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStructure.CAN_Prescaler = 4;
    CAN_Init(CAN1, &CAN_InitStructure);

//cấu hình bộ lọc 0
    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = (0x123 << 5);//mục đích dịch sang trái là nó đưa các bit id lên đầu tiên còn 5 bit trống là 1RTR, 1IDE, 3r0
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFFF;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

}


/*
* Function: respond_To_Data_Request
* Description: Feedback pressure data to the requested NODEx
* Input:
*   data: Array of pressure data to send to NODEx
*   len: length of array
*   id: ID of NODEx
* Ouput: 
*   Transmit array of data
*/
void respond_To_Data_Request(uint8_t *data, uint8_t len){
    CanRxMsg RxMessage;
    CanTxMsg TxMessage;
    
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);

	if(RxMessage.StdId == 0x123 && RxMessage.IDE == CAN_ID_STD && RxMessage.RTR == CAN_RTR_REMOTE){
      TxMessage.StdId = 0x321;//id này là cái node của transmit dùng để truyền ngược lại
    	TxMessage.ExtId = 0x00;
    	TxMessage.RTR = CAN_RTR_DATA;
    	TxMessage.IDE = CAN_ID_STD;// ID theo tiêu chuẩn
    	TxMessage.DLC = len;
		
			CAN_Transmit(CAN1, &TxMessage);
		/* Wait until the current message frame is successfully transmitted */
		while (CAN_TransmitStatus(CAN1, CAN_FIFO0) != CAN_TxStatus_Ok);
        }
	
}

int main(){
	
    init_can();
		uint8_t data[3] = {11, 22, 33};
		respond_To_Data_Request(data, 3);
   
}