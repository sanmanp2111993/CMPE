/****************************************************************************
 *   $Id:: misc_gpio.c 5143 2010-10-07 23:06:18Z usb00423                       $
 *   Project: NXP LPC software example
 *
 *   Description:
 *     This file contains routines to control and monitor
 *     Smart Card interface signals.
 *
 ****************************************************************************
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
#include "LPC11Uxx.h"
#include "type.h"
#include "misc_gpio.h"

void MiscGpioInit(void)
{
  uint32_t prescale;

  /* Smart Card GPIO interface */
  /*
   P0_17; L=off, H=on; Pin used for the activity LED, it will toggle whenever bytes are recevied or
   transmitted and remain off when there is no activity

   P0_18; L=extracted, H=inserted; Pin is used to detect whether a Smart Card is inserted into its socket

   P0_19; L=off, H=on; Pin is used to enable power to the Smart Card

   P0_20; L=assert reset, H=out of reset; Pin is used to assert the reset condition to the Smart Card
  */
  LPC_IOCON->CARD_ACTIVITY_IOCON &= ~0x7;
  LPC_IOCON->CARD_ACTIVITY_IOCON |= 0x0;
  LPC_IOCON->CARD_RESET_IOCON &= ~0x7;
  LPC_IOCON->CARD_RESET_IOCON |= 0x0 | _BV(10);
  LPC_IOCON->POWER_ENABLE_IOCON &= ~0x7;
  LPC_IOCON->POWER_ENABLE_IOCON |= 0;
  LPC_IOCON->CARD_DETECT_IOCON &= ~0x7;
  LPC_IOCON->CARD_DETECT_IOCON |= 0; /* DETECT @ P1.10 */
  SC_GPIO->CLR[1] = CARD_RESET | POWER_ENABLE | CARD_ACTIVITY; /* RST active, power off, activity inactive */
  SC_GPIO->DIR[1] |= CARD_RESET | POWER_ENABLE | CARD_ACTIVITY; /* Only RST, POWER_EN, activity LED are outputs */

  /* Configure card asynchronous clock source on PWM match output*/
  prescale = ((SystemCoreClock * 2 / CLOCK_FREQUENCY) + 1) >> 1;
  LPC_SYSCON->SYSAHBCLKCTRL |= _BV(10);
	LPC_IOCON->SC_CLK_IOCON &= ~0x07;
  LPC_IOCON->SC_CLK_IOCON |= 0x03;
	SC_PWM->IR = 0x0F; /* Clear match interrupts */
	SC_PWM->PR  = 0;
  SC_PWM->MR1 = prescale / 2; /* pulse width */
	SC_PWM->MR3 = prescale - 1; /* period of waveform */
  SC_PWM->PWMC = _BV(1);
	SC_PWM->MCR = _BV(10);	/* reset on MR3 */
  SC_PWM->TCR = _BV(1); /* reset timer, leave stopped */
}


/*****************************************************************************
**                            End Of File
******************************************************************************/
