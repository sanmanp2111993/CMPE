/*----------------------------------------------------------------------------
 * Name:    usbmain.c
 * Purpose: USB Audio Class Demo
 * Version: V1.20
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC microcontroller devices only. Nothing else 
 *      gives you the right to use this software.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbaudio.h"
#include "gpio.h"
#include "cdc.h"
#include "cdcuser.h"
#include "serial.h"
#define LED_PORT 0
#define LED_PIN 7
#ifdef __USE_CMSIS
#include "LPC11Uxx.h"
#endif

#include <NXP/crp.h>
#include <cr_section_macros.h>

__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

extern void FCT_fixed(int * x, int *y);
extern int count;
unsigned int warn_bit=0; 						/*Warning bit used when USB is not initialized*/
signed int FFTBuf[66];
unsigned char FFTData[66];
uint32_t led_status=0;
int led_count=0;
uint8_t  Mute;                                  /* Mute State */
uint32_t Volume;                                /* Volume Level */

short DataBuf[B_S];                             /* Data Buffer */
uint16_t  DataOut;                              /* Data Out Index */
uint16_t  DataIn;                               /* Data In Index */

uint8_t   DataRun;                              /* Data Stream Run State */
uint16_t  PotVal;                               /* Potenciometer Value */
uint32_t  VUM;                                  /* VU Meter */
uint32_t  Tick;                                 /* Time Tick */

/*
 * Get Potenciometer Value
 */

void get_potval (void) {
#if USE_VOLUME
  uint32_t val;

  LPC_ADC->CR |= 0x01000000;              /* Start A/D Conversion */
  do {
    val = LPC_ADC->GDR;                   /* Read A/D Data Register */
  } while ((val & 0x80000000) == 0);      /* Wait for end of A/D Conversion */
  LPC_ADC->CR &= ~0x01000000;             /* Stop A/D Conversion */
  PotVal = ((val >> 8) & 0xF8) +          /* Extract Potenciometer Value */
           ((val >> 7) & 0x08);
#endif
}


/*
 * Timer Counter 0 Interrupt Service Routine
 *   executed each 31.25us (32kHz frequency)
 */

void TIMER16_0_IRQHandler(void) 
{
	long  val;
	uint32_t cnt;
	if (DataRun) {                            /* Data Stream is running */
    val = DataBuf[DataOut];                 /* Get Audio Sample */
    cnt = (DataIn - DataOut) & (B_S - 1);   /* Buffer Data Count */
    if (cnt == (B_S - P_C*P_S)) {           /* Too much Data in Buffer */
      DataOut++;                            /* Skip one Sample */
    }
    if (cnt > (P_C*P_S)) {                  /* Still enough Data in Buffer */
      DataOut++;                            /* Update Data Out Index */
    }
    DataOut &= B_S - 1;                     /* Adjust Buffer Out Index */
    if (val < 0) VUM -= val;                /* Accumulate Neg Value */
    else         VUM += val;                /* Accumulate Pos Value */
    val  *= Volume;                         /* Apply Volume Level */
    val >>= 16;                             /* Adjust Value */
    val  += 0x8000;                         /* Add Bias */
    val  &= 0xFFFF;                         /* Mask Value */
  } else {
    val = 0x8000;                           /* DAC Middle Point */
  }

  if (Mute) {
    val = 0x8000;                           /* DAC Middle Point */
  }

#if USE_SPEAKER
  //This part was commented out as LPC11 does not have DAC
  LPC_DAC->DACR = val & 0xFFC0;             /* Set Speaker Output */

  if ((Tick++ & 0x03FF) == 0) {             /* On every 1024th Tick */
    get_potval();                           /* Get Potenciometer Value */
    if (VolCur == 0x8000) {                 /* Check for Minimum Level */
      Volume = 0;                           /* No Sound */
    } else {
      Volume = VolCur * PotVal;             /* Chained Volume Level */
    }
    val = VUM >> 20;                        /* Scale Accumulated Value */
    VUM = 0;                                /* Clear VUM */
    if (val > 7) val = 7;                   /* Limit Value */
  }
#endif

  LPC_CT16B0->IR = 1;                      /* Clear Interrupt Flag */
}
/*Timer 1 match interrupt service routine,executed every 32usec (32Khz), LED blinking @3.1Hz */
void TIMER16_1_IRQHandler(void){
	led_count++;
	if(!warn_bit){
		if(led_count>10000){
			GPIOSetBitValue(LED_PORT, LED_PIN, led_status);
			led_count=0;
			if(led_status)//toggle LED
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
/*****************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
  int i, j;
  int fft = 0;
  SystemCoreClockUpdate();

  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6)|(1<<7)|(1<<8)|(0x1<<13);  /* Enable clock to GPIO, 16-bit timer 0,timer1 and ADC. */

  GPIOSetDir(0,7,1);

  GPIOSetBitValue(LED_PORT, LED_PIN, 0);

#if USE_VOLUME
  /* Disable Power down bit to the ADC block. */  
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<4);
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7)|(0x1<<13);  /* Enable clock to 16-bit timer 0 and ADC. */

  /* ADC was supposed to be connected to the potenciometer as the volume control. 
  DAC is connected to the speaker. Depending on the board. It may or may be used. */
  LPC_IOCON->TDI_PIO0_11 &= ~0x9F; /*  ADC I/O config */
  LPC_IOCON->TDI_PIO0_11 |= 0x02;  /* ADC IN0 */

  LPC_ADC->CR = 0x00200E01;		/* ADC: 10-bit AIN0 @ 4MHz */
    
#endif

  LPC_CT16B0->MR0 = SystemCoreClock/DATA_FREQ-1;	/* TC0 Match Value 0 */
  LPC_CT16B0->MCR = 3;					/* TCO Interrupt and Reset on MR0 */
  LPC_CT16B0->TCR = 1;					/* TC0 Enable */
  NVIC_EnableIRQ(TIMER_16_0_IRQn);

  LPC_CT16B1->MR0 = SystemCoreClock/DATA_FREQ-1;	/* TC1 Match Value 0, set to 32uSecs  */
  LPC_CT16B1->MCR = 3;					/* TC1 Interrupt and Reset on MR0 */
  LPC_CT16B1->TCR = 1;					/* TC1 Enable */
  NVIC_EnableIRQ(TIMER_16_1_IRQn);

  CDC_Init();               /* CDC Init */
  USB_Init();				/* USB Initialization */
  USB_Connect(TRUE);		/* USB Connect */

  while (!USB_Configuration){// wait until USB is configured
	  GPIOSetBitValue(LED_PORT, LED_PIN, 1);//switch on LED to indicate Error
	  warn_bit=1;			/*Set warning bit, wont be cleared until USB is plugged in*/
  }
  warn_bit=0;				/*Clear warning bit*/
  FFTBuf[0] = 0xFFFF;
  FFTBuf[1] = 0xFFFF;

  /********* The main Function is an endless loop ***********/ 
  while( 1 ) {
		  if ((count==0) & (fft == 0)) {
		  j = DataIn;
		  for (i=0;i<64;i++, j++) {
			  if (j == B_S) j = 0;
			  FFTBuf[2+i] = DataBuf[j];
		  }
		  FCT_fixed(FFTBuf+2, FFTBuf+2);
		  fft = 1;
		  for (i=0;i<66;i++, j++) {
			  FFTData[i] = (FFTBuf[i] >> 8) & 0xff;
		  }
		  if (CDC_DepInEmpty) {
			  CDC_DepInEmpty = 0;
			  USB_WriteEP (CDC_DEP_IN, (unsigned char *)&FFTData[0], 66);
		  }

	  }
	  if (count==1) fft = 0;
  } 
}

/******************************************************************************
**                            End Of File
******************************************************************************/
