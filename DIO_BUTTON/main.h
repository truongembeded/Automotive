/*
* File: main.h
* Author: Nguyen Van Truong
* Date: 20/10/2001
* Description: this file create the functions to blink the led with the button press
*/
#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
void ConfigOut(void);
void ConfigIn(void);
void delay(uint32_t t);
void butTon1(void);
void butTon2(void);
void butTon3(void);
void Blink(uint8_t count);
void ChaseLed(uint8_t count);
void Stoped(void);

#endif