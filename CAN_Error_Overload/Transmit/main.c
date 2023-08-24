/*
* File: main.c 
* Author: Nguyen Van Truong
* Date: 20/10
* Description: This file is created to transmit speed data by error frame
*/

#include "main.h"
/*
* Function: init_can
* Description: Configuration communication CAN
* Input:
*   can_id: ID of NODE
* Ouput: 
*   None
*/
void init_can(uint16_t can_id){
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

    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;//0x123xxxxx
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFFF;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);
}

void delay(uint32_t t)
{
    for (volatile uint32_t i = 0; i < t; i++)
    {
        for (volatile uint32_t j = 0; j < 1000; j++) {}
    }
}

/*
* Function: sendSpeedData
* Description: Transmit message to NODEx (request data);
* Input:
*   id: ID of NODE to transmit message
* Ouput: 
*   Transmit message to NODE
*/
void sendSpeedData(uint16_t SpeedData){
  CanTxMsg TxMessage;

    TxMessage.StdId = 0x123;
    TxMessage.ExtId = 0x00;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_ID_STD;// ID theo tiêu chuẩn
    TxMessage.DLC = 2;
		TxMessage.Data[0] =(uint8_t)(SpeedData & 0xFF);
		TxMessage.Data[1] =(uint8_t)((SpeedData >> 8) & 0xFF);
    
    if(CAN_Transmit(CAN1, &TxMessage) != CAN_TxStatus_Ok){
				//logError("Error while transmit speed data") ARM có thanh ghi chứa log này 
		}
		
		for(uint8_t i = 0; i < 3; i++){
			if(CAN_Transmit(CAN1, &TxMessage) != CAN_TxStatus_Ok){
				break;
			}
			delay(100);	
		}

}


int main(){
    init_can(0x0000);
	
		uint16_t speedData= 500;
	
    while (1)
    {
        sendSpeedData(speedData);
			
				delay(1000);
    }
    
}