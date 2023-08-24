/*
* File: main.c 
* Author: Nguyen Van Truong
* Date: 20/10
* Description: This file is created to receive speed data by error frame
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

void processSpeedData(uint16_t speedData){
	if(speedData >= 100){
		// bật led
	}else{
		// tắt led
	}
}

/*
* Function: recieveSpeedData
* Description: recieve Speed Data to the requested NODEx
* Input:
*   None
* Ouput: 
*   Transmit array of data
*/
void recieveSpeedData(){
    CanRxMsg RxMessage;
	int retryCount = 0;
	while(retryCount < 3)
		{
		//kiểm tra xem dữ liệu có nhận được hay không
			if(CAN_MessagePending(CAN1, CAN_FIFO0) != 0){
				
				CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
				if(RxMessage.StdId == 0x123 && RxMessage.IDE == CAN_ID_STD && RxMessage.DLC == 2){
					
					uint16_t speedData = (uint16_t)(RxMessage.Data[1] << 8) | RxMessage.Data[0];
					
					processSpeedData(speedData);
					break;
				}
				
			}else
			{
					//logError("error")
					retryCount++;
				delay(100);
			}
	}  

}

int main(){
	
    init_can();
		while(1){
			recieveSpeedData();
		}
   
}