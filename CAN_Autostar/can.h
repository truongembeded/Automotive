/*
* File: can.h 
* Author: Nguyen Van truong
* Date: 20/10
* Description:  This is file create to define the functions and macros of 
*the can interface according to the autosar standard(Dio)
*/
#ifndef __CAN_H
#define __CAN_H
#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

typedef struct{
	uint8_t SJW;
	uint8_t BS1;
	uint8_t BS2;
	uint8_t Prescaler;
	uint32_t FilterMaskId;
	uint32_t FilterId;
	uint8_t TxBufferId;
	uint8_t RxBufferId;
}Can_ConfigType;
/* 
* Defines two values for the return result E_OK and E_NOT_OK. 
*/
typedef uint8_t Std_ReturnType;
	
#define E_OK ((Std_ReturnType)0x00U)
#define E_NOT_OK ((Std_ReturnType)0x01U)
/*
* Represents the hardware object handles of a CAN hardware unit. For CAN 
	hardware units with more than 255 HW objects use extended range.
*/
typedef uint16_t Can_HwHandleType;

typedef uint16_t PduIdType;
/*
* Represents the Identifier of an L-PDU. The two most significant bits specify the
frame type:
* 00 CAN message with Standard CAN ID
* 01 CAN FD frame with Standard CAN ID
* 10 CAN message with Extended CAN ID
*/
typedef uint32_t Can_IdType;
/*
* This type unites PduId (swPduHandle), SduLength (length), SduData (sdu), and
CanId (id) for any CAN L-SDU.
*/
typedef struct{
	PduIdType swPduHandle;
	uint8_t length;
	Can_IdType id;
	uint8_t *sdu;
}Can_PduType;

typedef struct{
	uint16_t vendorID;
	uint16_t moduleID;
	uint8_t sw_major_verson;
	uint8_t sw_minor_verson;
	uint8_t sw_patch_verson;
}Std_VersionInfoType;

typedef enum{
	CAN_CS_UNINIT = 0x00,
	CAN_CS_STARTED,
	CAN_CS_STOPPED,
	CAN_CS_SLEEP
}Can_ControllerStateType;

void Can_Init(const Can_ConfigType* Config);

Std_ReturnType Can_Write (Can_HwHandleType Hth, const Can_PduType* PduInfo);

Std_ReturnType Can_Read (Can_HwHandleType Hrh, Can_PduType* PduInfo);

void Can_DeInit(void);

void Can_GetVersionInfo(Std_VersionInfoType * versioninfo);

Std_ReturnType Can_SetBaudrate(uint8_t Controller, uint16_t BaudRateConfigID);

Std_ReturnType Can_SetControllerMode(uint8_t Controller, Can_ControllerStateType Transition);

Std_ReturnType Can_GetControllerMode(uint8_t Controller, Can_ControllerStateType* ControllerModePtr);

#endif