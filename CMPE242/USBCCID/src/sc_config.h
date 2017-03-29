/****************************************************************************
 *   $Id:: config.h 5143 2010-10-07 23:06:18Z usb00423                       $
 *   Project: NXP LPC software example
 *
 *   Description:
 *     This file contains definitions to configure the Smart Card example.
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
#ifndef __CONFIG_H__ 
#define __CONFIG_H__

#ifndef _BV
#define _BV(_x_) (1UL << (_x_))
#endif

/***************************************************************************/
/* Test type */
#define LOOPBACK_TEST                       (0)   /* 0 for ACOS3 demo, 1 for loopback */

/***************************************************************************/
/* Some limits for this particular device */
#define N_TIMERS                            (4)   /* Number of timers on device */
#define N_MATCHES                           (4)   /* Number of match registers on device */
#define N_CAPTURES                          (2)   /* Number of capture registers on device */

#define N_PWM                               (2)   /* Number of PWMs on device */

/***************************************************************************/
/* Configuration for miscellaneous GPIO for Smart Card, assuming all GPIO on same port */
#define SC_GPIO                             LPC_GPIO
#define POWER_ENABLE                        (_BV(13)) /* P1.11 */
#define POWER_ENABLE_IOCON                  PIO1_13
#define CARD_DETECT                         (_BV(14)) /* P1.10 */
#define CARD_DETECT_IOCON                   PIO1_14
#define CARD_ACTIVITY                       (_BV(15)) /* P1.9 */
#define CARD_ACTIVITY_IOCON                 PIO1_15
#define CARD_RESET                          (_BV(16)) /* P1.12 */
#define CARD_RESET_IOCON                    PIO1_16

#define SC_PWM                              LPC_CT32B1
#define SC_CLK_IOCON                        TRST_PIO0_14

/***************************************************************************/
/* Configuration for default Smart Card interface clocks and rates */
#define CARD_BAUD_RATE                      (9600) /* baud rate */
#define CARD_EXTRA_GUARD_BITS               (2) /* extra guard bits */
#define CLOCK_FREQUENCY                     (CARD_BAUD_RATE * 372) /* ACOS3 external clock should be 372 x baud*/
//#define CLOCK_FREQUENCY                     (3571200) /* ACOS3 external clock */

/***************************************************************************/
/* Configuration for Smart Card interface on hardware UART */
#define SC_OVERSAMPLE                       (372)   /* Number of times to oversample a bit */

/***************************************************************************/
/* Configuration for software implementation of Smart Card UART */
#define SC_TIMER                            (3)   /* Timer number on device */
#define SC_MAT_OUTPUT                       (0)   /* Timer match register number for TX */
#define SC_MAT_PIN                          TDO_PIO0_13 /* Match output for TX */
#define SC_MAT_RXSTATE                      (1)   /* Timer match register number for RX */
#define SC_CAP_INPUT                        (0)   /* Timer capture register number for RX */
#define SC_CAP_PIN                          TMS_PIO0_12 /* Capture input for TX */

#define SC_BUFSIZE                          (64)  /* Size in bytes for RX and TX buffers */

/***************************************************************************/
/* Configuration for miscellaneous Smart Card clock and timing */
#define CLOCK_SOURCE                        (0)   /* PWM number on device */
#define TIME_SOURCE                         (0)   /* Timer number on device for short delays */
#define T_INSERTION_DEBOUNCE                (100) /* 100 ms */
#define T_Ta                                (5)   /* 5 ms */
#define T_Ta_Tb                             (400 * 1000 / CLOCK_FREQUENCY + 1) /* ~400 clock cycles */
#define T_Tb_Tc                             (40000 * 1000 / CLOCK_FREQUENCY + 1) /* ~40,000 clock cycles */
#define T_BYTE_TIME                         ((10 + CARD_EXTRA_GUARD_BITS) * 2 * 1000 / 9600)
#define T_CMD_DONE                          (500)  /* Time to wait in ms for command to complete */
#define T_IDLE_POWER_DOWN                   (1000) /* Time to wait in ms idle before powering off */

#endif /* end __CONFIG_H__ */
/*****************************************************************************
**                            End Of File
******************************************************************************/
