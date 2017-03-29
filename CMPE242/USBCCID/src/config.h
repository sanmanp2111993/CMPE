/*
===============================================================================
 Name        : config.h
 Author      :
 Version     :
 Copyright   : Copyright (C)
 Description : Common config settings
===============================================================================
*/
#ifndef __CONFIG_H
#define __CONFIG_H


#define BOARD_EA_REVB
//#define BOARD_NGX
#if !defined(BOARD_EA_REVB) && !defined(BOARD_NGX)
#error "ERROR: No board defined"
#endif
#define LED_PORT 0
#define LED_PIN 7

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

#endif
