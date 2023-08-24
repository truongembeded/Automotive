/*
* File: main.c 
* Author: Nguyen Van Truong
* Date: 20/10
* Description: This file is created to receive array of data by communication can
*/
#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
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

//cấu hình bộ lọc 1
    CAN_FilterInitStructure.CAN_FilterNumber = 1;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = (0x456 << 5);//mục đích dịch sang trái là nó đưa các bit id lên đầu tiên còn 5 bit trống là 1RTR, 1IDE, 3r0
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFFF;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);
}
//khi muốn truyền cho 2 địa chỉ với 2 id khác nhau thì mỗi địa chỉ sử dụng 1 cái bộ lọc

/*
* Function: receive_Can_Message
* Description: Receive array of data from NODEx
* Input:
*   data: Data array received from NODEx
* Ouput: 
*   None
*/
void receive_Can_message(uint8_t *data){
    
    CanRxMsg RxMessage;
	
    while (CAN_MessagePending(CAN1, CAN_FIFO0) == 0 );
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
		
    for (int i = 0; i < RxMessage.DLC; i++)
    {
			 if(RxMessage.StdId == 0x123)
					{
						data[i] = RxMessage.Data[i];
					}
			 if(RxMessage.StdId == 0x456)
					{
						data[i] = RxMessage.Data[i];
					}
    }
   
}


int main(){
    init_can();
	
		uint8_t data1[3] = {0};
		uint8_t data2[3] = {0};
		
    while (1)
    {
        receive_Can_message(data1);
	    receive_Can_message(data2);
    }
    
}