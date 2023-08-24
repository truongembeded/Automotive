/*
* File: main.h 
* Author: Nguyen Van Truong
* Date: 20/10
* Description: This file is created function to transmit speed data by error frame
*/
#ifndef _MAIN_H
#define _MAIN_H

#include "stm32f10x.h"
#include "stm32f10x_can.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

void init_can(uint16_t can_id);
void sendSpeedData(uint16_t SpeedData);
void delay(uint32_t t);




#endif