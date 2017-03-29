/*
===============================================================================
 Name        : timer.cpp
 Author      : $ D H R U V K A K A D I Y A
 Email		 : $ D H R U V . K A K A D I Y A @ G M A I L . C O M
 Version     : $ 1.1
 Copyright   : $ CMPE 240 / 2015
 Description : Important Timer Interrupt and NVIC Interrupt definition
===============================================================================
*/
#include<LPC17xx.h>
#include "LPC17xx_1.h"

#include "timer.h"

unsigned int storetime=0;
void (*isrT0CR0Handler)	();
void (*isrT0CR1Handler)	();

void (*isrGPIOHandler)	();

void ConfigTimer(int timerselect,int prescale,int cap,int edge)
{
	switch(timerselect)
	{
		case TIMER0:
			PCONP |= 1<<1;
			PCLKSEL0 |= 3<<2;
			PINSEL3 |= 3<<(20+cap*2);
			LPC_TIM0 -> CTCR = cap<<2 | edge<<0;
			LPC_TIM0 -> PR = prescale;
			LPC_TIM0 -> IR = 1 << (4+cap); // Enable interrupt
			LPC_TIM0 -> TCR = 2; // counter disabled
			break;

	}
}

void StartTimer(int timerselect)
{
	switch(timerselect)	{

		case TIMER0:
				T0TCR = 0x00000001;
			break;
		case TIMER1:
				T1TCR = 0x00000001;
			break;
		case TIMER2:
				T2TCR = 0x00000001;
			break;
		case TIMER3:
				T3TCR = 0x00000001;
			break;
		}
}

//--------------------------------------------------------------------
void StopTimer(int timerSelect)	{

	switch(timerSelect)	{

	case TIMER0:
			T0TCR &= ~0x00000001;
		break;
	case TIMER1:
			T1TCR &= ~0x00000001;
		break;
	case TIMER2:
			T2TCR &= ~0x00000001;
		break;
	case TIMER3:
			T3TCR &= ~0x00000001;
		break;
	}
}

void ISR_TIMER0(void)
{
	int interrupt;
	if( T0IR & _CR0)
	{
		interrupt = _CR0;
		if(isrT0CR0Handler != NULL)
			(*isrT0CR0Handler)();						//call Timer0-Capture0 handler function
	}
	else if( T0IR &  _CR1)
	{
		interrupt = _CR1;
		if(*isrT0CR1Handler != NULL)
			(isrT0CR1Handler)();						//call Timer0-Capture1 handler function
	}
	//--------------------------
	T0IR |= interrupt;
}

void ISR_TIMER1(void){

}

void ISR_TIMER2(void){

}

void ISR_TIMER3(void){

}

void ISR_EINT0(void){

}

void ISR_EINT1(void){

}

void ISR_EINT2(void){

}

void ISR_EINT3(void){

	//-----------------------------------Test cmpe 240-----------------------------------

	if( (IO2IntStatR&0x00001000) == 0x00001000)
	{
		StopTimer(TIMER0);
		storetime=T0TC;
		LPC_GPIO0->FIOCLR = 1<<22;	// turn off onboard led
	}
	else if( (IO2IntStatF&0x00001000)== 0x00001000)
	{
		T0PC=0; // clear prescale counter
		T0TC=0; // clear timer counter
		StartTimer(TIMER0);
		LPC_GPIO0->FIOSET = 1<<22;	// turn on onboard led
	}

//-----------------------------------

	if( (IO2IntStatR&0x00001000) == 0x00001000)
	{
		StartTimer(TIMER0);
		LPC_GPIO0->FIOCLR = 1<<22;	// turn off onboard led
	}
	else if( (IO2IntStatF&0x00001000)== 0x00001000)
	{
		storetime=T0TC;
		StopTimer(TIMER0);
		LPC_GPIO0->FIOSET = 1<<22;	// turn on onboard led
	}

	IO2IntClr = 0xFFFFFFFF;
	IO0IntClr = 0xFFFFFFFF;

	//-----------------------------------
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
void Enable(int interrupt,int inttype)	{

	static short vtoractive = 0;
	if(!vtoractive)	{

		vtoractive = 1;
		VTOR=0x10005000;
	}
	unsigned long *NVICAddr;
	ISER0 |= (1<<interrupt);
	switch(interrupt)	{

		case TIMER0:
				NVICAddr=(unsigned long*)(VTOR+0x00000044);
				*NVICAddr=(unsigned long)ISR_TIMER0;
			break;
		case TIMER1:
				NVICAddr=(unsigned long*)(VTOR+0x00000048);
				*NVICAddr=(unsigned long)ISR_TIMER1;
			break;
		case TIMER2:
				NVICAddr=(unsigned long*)(VTOR+0x0000004C);
				*NVICAddr=(unsigned long)ISR_TIMER2;
			break;
		case TIMER3:
				NVICAddr=(unsigned long*)(VTOR+0x00000050);
				*NVICAddr=(unsigned long)ISR_TIMER3;
			break;
		case EINT0:
				EXTMODE = EINT0_EDGE;
				EXTPOLAR = 1;
				NVICAddr=(unsigned long*)(VTOR+0x00000088);
				*NVICAddr=(unsigned long)ISR_EINT0;
				break;
		case EINT1:
				EXTMODE = EINT1_EDGE;
				EXTPOLAR = 2;
				NVICAddr=(unsigned long*)(VTOR+0x0000008C);
				*NVICAddr=(unsigned long)ISR_EINT1;
				break;
		case EINT2:
				EXTMODE = EINT2_EDGE;
				EXTPOLAR = 4;
				NVICAddr=(unsigned long*)(VTOR+0x00000090);
				*NVICAddr=(unsigned long)ISR_EINT2;
				break;
		case EINT3:
				//EXTMODE = EINT3_EDGE;
				//EXTPOLAR = 8;
				NVICAddr=(unsigned long*)(VTOR+0x00000094);
				*NVICAddr=(unsigned long)ISR_EINT3;
				break;
	}
}

void On(int interrupt,void (*ISR)(void)) {

	switch(interrupt)	{
		//--------------------------------------------------
		//---------------------Timer 0----------------------
		case _T0CR0:
				isrT0CR0Handler = *ISR;
			break;
		case _T0CR1:
				isrT0CR1Handler = *ISR;
			break;
	}
}
