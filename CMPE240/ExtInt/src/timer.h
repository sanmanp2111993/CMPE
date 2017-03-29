/*
===============================================================================
 Name        : timer.h
 Author      : $ D H R U V K A K A D I Y A
 Email		 : $ D H R U V . K A K A D I Y A @ G M A I L . C O M
 Version     : $ 1.1
 Copyright   : $ CMPE 240 / 2015
 Description : Interrupt vector table declaration and function declaration
===============================================================================
*/
#ifndef _TIMER_H
#define _TIMER_H

#include<LPC17xx.h>
#include "LPC17xx_1.h"

#define NULL 		0

#define RISING 		1
#define FALLING 	2
#define BOTH 		3

#define CAP0 		0
#define CAP1 		1

#define TIMER0 		1
#define TIMER1 		2
#define TIMER2 		3
#define TIMER3 		4
#define EINT0 		18
#define EINT1 		19
#define EINT2 		20
#define EINT3 		21
#define GPIO		21	  						//EINT3 channel is shared with GPIO interrupts
#define ADC			22

#define _T0CR0 		5
#define _T0CR1 		6

#define _CR0 		0x00000010
#define _CR1 		0x00000020

#define EINT0_EDGE	1
#define EINT1_EDGE	2
#define EINT2_EDGE	4
#define EINT3_EDGE	8

extern unsigned int storetime;
void ConfigTimer(int,int,int,int);
void StartTimer(int);
void StopTimer(int);
//-----------------------------
void On(int interrupt,void (*ISR)());
void Enable(int interrupt,int inttype=NULL);
//-----------------------------

#endif
