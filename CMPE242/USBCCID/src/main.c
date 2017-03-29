/****************************************************************************

 *   Description:
 *     This file contains a smartcard driver example
 *
 *   Copyright(C) 2011, NXP Semiconductor
 *   All rights reserved.
 *
 *****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 ****************************************************************************/
#include <string.h>
#include "LPC11Uxx.h"
#include "config.h"
#include "usart.h"
#include "timer32.h"
#include "misc_gpio.h"
#include "smartcard.h"
#include "type.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbccid.h"
#include "gpio.h"
#ifdef __USE_CMSIS
#include "LPC11Uxx.h"
#endif
#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

#include <stdio.h>
#include "ACOS3.h"
uint32_t led_status=0;
int led_count=0;

/*Timer 1 match interrupt service routine,executed every 32usec (32Khz), LED blinking @3.1Hz */

void TIMER16_1_IRQHandler(void){
	led_count++;
	if(led_count>10000)
	{
		led_count=0;
		if(isCardInserted())
		{
			GPIOSetBitValue(LED_PORT, LED_PIN,1) ; /*Switch On LED ,If card inserted*/
		}
		else 	/*If card is not inserted toggle LED*/
		{
			GPIOSetBitValue(LED_PORT, LED_PIN, led_status);

			if(led_status)		/*Toggle LED*/
			{
				led_status=0;
			}
			else
			{
				led_status=1;
			}
		}
	}
	LPC_CT16B1->IR = 1;                      /* Clear Interrupt Flag */
}

int main(void)
{
	printf("Smartcard demo\n");

	/* Setup SysTick Timer for 1 msec interrupts  */
	SysTick_Config(SystemCoreClock / 1000);

	SystemInit(); // Initialize the system
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6)|(1<<8);		/*Enable GPIO, Timer1*/
	GPIOSetDir(0,7,1);			/*Set GPIO Direction output*/
	LPC_CT16B1->MR0 = 1500;	/* TC1 Match Value 0, set to 32uSecs  */
	LPC_CT16B1->MCR = 3;					/* TC1 Interrupt and Reset on MR0 */
	LPC_CT16B1->TCR = 1;					/* TC1 Enable */
	NVIC_EnableIRQ(TIMER_16_1_IRQn);

	/* Ensure timer has power before using the delayMs() routines */
#if (TIME_SOURCE == 0)
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<9);
#else
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<10);
#endif

	// Initialize all GPIOs connected to the smart card socket.
	MiscGpioInit();

#if USB_CCID

	USB_Init();                               /* USB Initialization */
	USB_Connect(TRUE);                        /* USB Connect */

	NVIC_SetPriority(USB_IRQn, 2);			// USB interrupt priority must be lower than USART

	while(1)
	{
		printf("\nWaiting for smart card insertion ...\n");
		smartcardWaitForInsertion(); // hang here until a card is inserted
		printf("Card inserted\n");
		ShowCardInserted();
		smartcardWaitForRemoval(); // hang here until the card is removed
        ShowCardRemoved();
        printf("Card removed\n");

	}
#else

	// Initialize the smart card and underlying USART
	smartcardInit();

	while(1)
	{
		int i;
		unsigned char ATRBuf[32];

		printf("\nWaiting for ACOS3 card insertion ...\n");
		smartcardWaitForInsertion(); // hang here until a card is inserted
		printf("\nResetting smart card ...\n");
		i = smartcardReset(sizeof(ATRBuf), ATRBuf); // reset the smart card and retrieve the ATR string

		smartcardParseATR(i, ATRBuf);

		printf("\nDisplay ACOS3 card parameters ...\n");
		if (ACOS3_CARD_STATUS_SUCCESS == ACOS3_DumpCardParameters(i, ATRBuf))
		{
			int i;
			unsigned char record;
			unsigned char offset = 0;
			unsigned char datalen = 8;
			unsigned char databuf[16];

			printf("\nSelecting the MCU-ID file ...\n");
			if (ACOS3_CARD_STATUS_SUCCESS == ACOS3_SelectFile(0x00ff))
			{
				for(record = 0; record < 2; record++)
				{
					// read some data from the EEPROM in the card
					if (ACOS3_CARD_STATUS_SUCCESS == ACOS3_ReadRecord(record, offset, datalen, databuf))
					{
						printf("Record %d:  ", record, offset);
						for(i = 0; i < datalen; i++)
							printf("0x%x ", databuf[i]);
						printf("\n");
					}
					else
						printf("ERROR: reading file\n");
				}
			}
			else
				printf("ERROR: selecting a file\n");
		}

		smartcardWaitForRemoval(); /*Wait here until the card is removed*/
		printf("Card removed\n");
	}

#endif

	// Enter an infinite loop, just incrementing a counter
	volatile static int i = 0 ;
	while(1) {
		i++ ;
	}
	return 0 ;
}
