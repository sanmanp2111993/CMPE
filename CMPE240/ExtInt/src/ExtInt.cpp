/*
===============================================================================
 Name        : main.c
 Author      : $ D H R U V K A K A D I Y A
 Email		 : $ D H R U V . K A K A D I Y A @ G M A I L . C O M
 Version     : $ 1.1
 Copyright   : $ CMPE 240 / 2015
 Description : Working with External GPIO Interrupts
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
//#include<iostream>
#include<stdio.h>
#include "timer.h"
#include "GPIO.h"
//using namespace std;

int main(void) {

	LPC_GPIO0->FIODIR |= (1 << 22);
	LPC_GPIO2->FIODIR &= ~(1 << 12);
	LPC_GPIO0->FIODIR &= ~(1 << 28);
	ConfigPortMode(Port0,PULLUP);
	ConfigPortMode(Port2,PULLUP);
	ConfigTimer(TIMER0,0XFFFF,CAP0,RISING);// PCLK = 4MHz (IRC nominal frequency) / 4  -> timer clock = PCLK/prescale = 15 Hz -> 0.06 sec per pulse
	Enable(TIMER0);
	Enable(EINT3);
	ConfigGPIOInt(Port2_12,BOTH);
	while(1)
	{
		printf("Time : %f\n",(float)storetime/15);
	}
    return 0 ;
}
