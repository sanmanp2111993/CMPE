/*
===============================================================================
 Name        : GPIO.cpp
 Author      : $ D H R U V K A K A D I Y A
 Email		 : $ D H R U V . K A K A D I Y A @ G M A I L . C O M
 Version     : $ 1.1
 Copyright   : $ CMPE 240 / 2015
 Description : GPIO functions definition
===============================================================================
*/
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
#include<LPC17xx.h>
#include"LPC17xx_1.h"
#include"timer.h"

#include"GPIO.h"
//-----------------------------------------------------------------------------------------------
void set(unsigned short pin)
{
	if(pin < Port1_0)		{
		FIO0SET |= (1<<pin-Port0_0);
	}
	else if(pin < Port2_0)	{
		FIO1SET |= (1<<(pin-Port1_0));
	}
	else if(pin < Port3_0)	{
		FIO2SET |= (1<<(pin-Port2_0));
	}
}
//-----------------------------------------------------------------------------------------------
void reset(unsigned short pin)
{
	if(pin < Port1_0)		{
		FIO0CLR |= (1<<pin-Port0_0);
	}
	else if(pin < Port2_0)	{
		FIO1CLR |= (1<<(pin-Port1_0));
	}
	else if(pin < Port3_0)	{
		FIO2CLR |= (1<<(pin-Port2_0));
	}
}
//-----------------------------------------------------------------------------------------------
void ConfigPort(unsigned  short port,unsigned int stat)
{
	switch(port)	{

		case	Port0:
				FIO0DIR = stat;
			break;
		case	Port1:
				FIO1DIR = stat;
			break;
		case	Port2:
				FIO2DIR = stat;
			break;
		case	Port3:
				FIO3DIR = stat;
			break;
		case	Port4:
				FIO4DIR = stat;
			break;
	}
}
//-----------------------------------------------------------------------------------------------
void ConfigPin(unsigned  short port,unsigned int stat)
{
}
//-----------------------------------------------------------------------------------------------
void ConfigPortMode(unsigned  short port,unsigned int stat)
{
	switch(port)	{

		case Port0:
				PINMODE0 = 	stat;
				PINMODE1 = 	stat;
			break;
		case Port1:
				PINMODE2 = 	stat;
				PINMODE3 = 	stat;
			break;
		case Port2:
				PINMODE4 = 	stat;
			break;
		case Port3:
				PINMODE7 = 	stat;
			break;
		case Port4:
				PINMODE9 = 	stat;
			break;
	}
}
//-----------------------------------------------------------------------------------------------
void ConfigPinMode(unsigned  short,unsigned int)
{
}
//-----------------------------------------------------------------------------------------------
void ConfigGPIOInt(unsigned short pin,unsigned short stat)
{
	if(pin < Port1_0)	{

		if(stat == RISING)			{
			IO0IntEnR |= 1<<pin;
		}
		else if(stat == FALLING)	{
			IO0IntEnF |= 1<<pin;
		}
		else if(stat == BOTH)		{
			IO0IntEnR |= 1<<pin;
			IO0IntEnF |= 1<<pin;
		}
	}
	else if(pin >= Port2_0 && pin < Port3_0)	{

		if(stat == RISING)			{
			IO2IntEnR |= 1<<(pin-64);
		}
		else if(stat == FALLING)	{
			IO2IntEnF |= 1<<(pin-64);
		}
		else if(stat == BOTH)		{
			IO2IntEnR |= 1<<(pin-64);
			IO2IntEnF |= 1<<(pin-64);
		}
	}
}
//-----------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------
