/*----------------------------------------------------------------------------
 *      Name:    usbaudio.h
 *      Purpose: USB Audio Demo Definitions
 *      Version: V1.10
 *----------------------------------------------------------------------------
 *      This software is supplied "AS IS" without any warranties, express,
 *      implied or statutory, including but not limited to the implied
 *      warranties of fitness for purpose, satisfactory quality and
 *      noninfringement. Keil extends you a royalty-free right to reproduce
 *      and distribute executable files created using this software for use
 *      on NXP Semiconductors LPC family microcontroller devices only. Nothing 
 *      else gives you the right to use this software.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

/* Audio Definitions */
#define DATA_FREQ 32000                 /* Audio Data Frequency */
#define P_S       32                    /* Packet Size */
#define P_C       1                     /* Packet Count */
#define B_S       (8*P_C*P_S)           /* Buffer Size */
#define ADC       0                     /* Set as 1 if the device has DAC */

/* Audio Demo Variables */
extern uint8_t   Mute;                   /* Mute State */
extern uint32_t  Volume;                 /* Volume Level */
extern uint16_t  VolCur;                /* Volume Current Value */
extern short DataBuf[B_S];              /* Data Buffer */
extern uint16_t  DataOut;               /* Data Out Index */
extern uint16_t  DataIn;                /* Data In Index */
extern uint8_t   DataRun;               /* Data Stream Run State */

extern void TIMER16_0_IRQHandler( void );
