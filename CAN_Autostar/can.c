/*
* File: can.c 
* Author: Nguyen Van truong
* Date: 20/10
* Description:  This is file create to write and read data of 
*the can interface according to the autosar standard(Dio)
*/
#include "can.h"

/*
* Function: Can_Init
* Description: This function initializes the module.
* Input:
*   Config : Pointer to driver configuration
* Output:
*   None
*/
void Can_Init(const Can_ConfigType* Config){
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
    CAN_InitStructure.CAN_SJW = Config->SJW;
    CAN_InitStructure.CAN_BS1 = Config->BS1;
    CAN_InitStructure.CAN_BS2 = Config->BS2;
    CAN_InitStructure.CAN_Prescaler = Config->Prescaler;
    CAN_Init(CAN1, &CAN_InitStructure);

    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;//0x123xxxxx
    CAN_FilterInitStructure.CAN_FilterIdHigh = Config->FilterId >> 16;
    CAN_FilterInitStructure.CAN_FilterIdLow = Config->FilterId & 0xFFFF;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = Config->FilterMaskId >> 16;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = Config->FilterMaskId & 0xFFFF;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

}
/*
* Function: Can_Write
* Description: This function is called by CanIf to pass a CAN message to CanDrv for
transmission.
* Input:
*   Hth: information which HW-transmit handle shall be used for transmit.
					Implicitly this is also the information about the controller to use
					because the Hth numbers are unique inside one hardware unit.
*   PduInfo: Pointer to SDU user memory, Data Length and Identifier 
* Output:
*   E_OK: write command has been accepted
*   E_NOT_OK: write command has not been accepted
*/
Std_ReturnType Can_Write (Can_HwHandleType Hth, const Can_PduType* PduInfo){
	CanTxMsg TxMessage;

    TxMessage.StdId = PduInfo->id;
    TxMessage.ExtId = 0x00;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.DLC = PduInfo->length;

    for (int i = 0; i < PduInfo->length; i++)
    {
        TxMessage.Data[i] = PduInfo->sdu[i];
    }

    if(CAN_Transmit(CAN1, &TxMessage) != CAN_TxStatus_Ok){
			return E_NOT_OK;
		}
    return E_OK;
}
/*
* Function: Can_Read
* Description: This function is called by CanIf to pass a CAN message to CanDrv for
recievetion.
* Input:
*   Hrh: information which HW-recieve handle shall be used for recieve.
					Implicitly this is also the information about the controller to use
					because the Hrh numbers are unique inside one hardware unit.
*   PduInfo: Pointer to SDU user memory, Data Length and Identifier 
* Output:
*   E_OK: write command has been accepted
*   E_NOT_OK: write command has not been accepted
*/
Std_ReturnType Can_Read (Can_HwHandleType Hrh, Can_PduType* PduInfo){
	CanRxMsg RxMessage;

    if(CAN_MessagePending(CAN1, CAN_FIFO0) != 0){
			
			CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
			PduInfo->swPduHandle = Hrh;
			PduInfo->length = RxMessage.DLC;
			PduInfo->id = RxMessage.StdId;
			
			for(uint8_t i = 0; i < RxMessage.DLC; i++){
				
				PduInfo->sdu[i] = RxMessage.Data[i];
				return E_OK;	
			}
		}
		return E_NOT_OK;   
}
/*
* Function: Can_DeInit
* Description: This function de-initializes the module.
* Input:
*   None
* Output:
*   None
*/
void Can_DeInit(void){
	CAN_DeInit(CAN1);
}
/*
* Function: Can_GetVersionInfo
* Description: This function returns the version information of this module
* Input:
*   versioninfo: Pointer to where to store the version information of this module.
* Output:
*   None
*/
void Can_GetVersionInfo(Std_VersionInfoType * versioninfo){
	versioninfo->vendorID;// set up value cho nó
	versioninfo->moduleID;
}
/*
* Function: Can_SetBaudrate
* Description: This service shall set the baud rate configuration of the CAN controller. Depending
								on necessary baud rate modifications the controller might have to reset.
* Input:
*   Controller: CAN controller, whose baud rate shall be set

*   BaudRateConfigID: references a baud rate configuration by ID (seeCanControllerBaudRateConfigID)
 
* Output:
*   E_OK: write command has been accepted
*   E_NOT_OK: write command has not been accepted
*/
Std_ReturnType Can_SetBaudrate(uint8_t Controller, uint16_t BaudRateConfigID){
	if(Controller != 0){
		
		return E_NOT_OK;
	}
	CAN_InitTypeDef             CAN_InitStructure;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  
    /* CAN Baudrate = 1MBps*/
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;  // 1/(8/4) = 0.5 micro giAY
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStructure.CAN_Prescaler = BaudRateConfigID;   // time quanta
	
    CAN_Init(CAN1, &CAN_InitStructure);
	
	return E_OK;
}
/*
* Function: Can_GetControllerMode
* Description: This service reports about the current status of the requested CAN controller.

* Input:
*   Controller: CAN controller for which the status shall be requested.

*   ControllerModePtr: Pointer to a memory location, where the current mode of the CAN controller will be stored.
 
* Output:
*   E_OK: write command has been accepted
*   E_NOT_OK: write command has not been accepted
*/
Std_ReturnType Can_GetControllerMode(uint8_t Controller, Can_ControllerStateType* ControllerModePtr){
	if(Controller != 0){
		return E_NOT_OK;
	}
	
	if((CAN1->MSR && CAN_MSR_INAK) == 0){
		
		* ControllerModePtr = CAN_CS_STARTED;
		
	}else if((CAN1->MSR & CAN_MSR_SLAK) == 0){
		
		* ControllerModePtr = CAN_CS_SLEEP;
	}
	return E_OK;
}

