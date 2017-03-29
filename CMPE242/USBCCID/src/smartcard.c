/****************************************************************************

 *   Description:
 *     This file contains a smartcard interface that sits on top of the USART
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
#include <stdio.h>
#include "driver_config.h"
#include "LPC11Uxx.h"
#include "config.h"
#include "type.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbuser.h"
#include "usart.h"
#include "timer32.h"
#include "misc_gpio.h"
#include "smartcard.h"


uint8_t CardInserted;

static volatile uint8_t SendBuffer[USART_BUFSIZE];
static volatile uint8_t RNDc[8];
/*static uint32_t BaudTable[] =
{
    9600,
    13950,
    27900,
    55800,
    111600,
    115200,
    192000,
    223200
};*/

#if 0
static uint8_t TABaudTable[] =
{
    0x11, /* 9600 */
    0x92, /* 13,950 */
    0x93, /* 27,900 */
    0x94, /* 55,800 */
    0x95, /* 111,600 */
    0x18, /* 115,200 */
    0x19, /* 192,000 */
    0x96  /* 223,200 */
};

/*****************************************************************************
 ** Function name:		TAToBaud
 **
 ** Descriptions:		Converts TA byte to corresponding baudrate.
 **
 ** parameters:			ta - byte value TA
 ** Returned value:	baudrate
 **                  *index - pointer to index in baud tables (if not null)
 **
 *****************************************************************************/
static uint32_t TAToBaud(uint8_t ta, int * index)
{
    int i;

    for(i = 0;i < sizeof(TABaudTable) / sizeof(uint8_t);i++)
        if(TABaudTable[i] == ta)
        {
            if(index) *index = i;
            return BaudTable[i];
        }

    return BaudTable[0];
} 

/*****************************************************************************
 ** Function name:		BaudToTA
 **
 ** Descriptions:		Converts baudrate to corresponding TA byte.
 **
 ** parameters:			baudrate - baud rate to convert
 ** Returned value:	0 if no matches, otherwise TA byte value
 **                  *index - pointer to index in baud tables (if not null)
 **
 *****************************************************************************/
static uint8_t BaudToTA(uint32_t baudrate, int * index)
{
    int i;

    for(i = 0;i < sizeof(TABaudTable) / sizeof(uint8_t);i++)
        if(BaudTable[i] == baudrate)
        {
            if(index) *index = i;
            return TABaudTable[i];
        }

    return 0;
}
#endif // unused code

void smartcardInit()
{
    /* Turn off clock to device, wait in reset, make sure RX cannot receive garbage */
    USARTIgnore(); /* We don't want random noise from insertion */
	USARTInit(CARD_BAUD_RATE);	/* baud rate setting for communication with Smart Card */
}

int smartcardReset(int buflen, unsigned char *ATRBuf)
{
    /* Indicate that the card has been inserted */
    USARTClear();                       /* Clear USART buffer */
    ShowActivity();
    CardPowerOn();                      /* Power on */
    delay32Ms(TIME_SOURCE, T_Ta);       /* Wait for power to settle */
    ShowActivity();
    CardClockOn();                      /* Start clock at Ta */
    delay32Ms(TIME_SOURCE, T_Ta_Tb);    /* Wait until Tb */
    ShowActivity();

    USARTAccept();                      /* Come out of reset, get ready for ATR */
    memset((void *)USARTBuffer, 0, sizeof(USARTBuffer));

    CardDeassertReset();                /* Release reset to start the ATR */

    delay32Ms(TIME_SOURCE, T_Tb_Tc + (32 * T_BYTE_TIME)); /* Wait for 32 bytes to be sent */
    ShowActivity();

    if(buflen > USARTCount)            /* only copy what is in the USART buffer */
        buflen = USARTCount;

    memcpy(ATRBuf, (const char *)USARTBuffer, buflen);

    return buflen;
}

void smartcardWaitForInsertion()
{
    while(1)
    {
        while(!isCardInserted()) ; /* Wait for card to be inserted */
        delay32Ms(TIME_SOURCE, T_INSERTION_DEBOUNCE); /* Verify the card is still there */
        if(isCardInserted())
        {
            CardInserted = 1;
            return;
        }
    }
}

void smartcardWaitForRemoval()
{
    while(isCardInserted()) ; /* Wait for card to be extracted */
    /* Turn off clock to device, wait in reset */
    CardClockOff(); /* reset and stop clock */
    USARTIgnore(); /* Make sure RX interrupt does not respond to garbage on data line */
    CardPowerOff();
}

void smartcardCommandDelay(int bytecnt)
{
    delay32Ms(TIME_SOURCE, T_CMD_DONE + ((bytecnt + 11) * T_BYTE_TIME)); /* Wait for command to complete */

}

//Transmits APDU to Card and returns the response
APDU_STATUS SendAPDU(
                    unsigned char CLA,
                    unsigned char INS,
                    unsigned char P1,
                    unsigned char P2,
                    unsigned char P3,
                    unsigned char writeFlag,
                    unsigned char *DataBuff,
                    int *RDataCount,
                    unsigned char *SW1,
                    unsigned char *SW2)
{
    unsigned char procedureByte;
    int index = 0;
    int dataLen = P3?P3:256;
    *RDataCount = 0;

    if(CLA == 0xff)
        return APDU_STATUS_INVALID_CMD;

    if((INS >> 4) == 6 || (INS >> 4) == 9)
        return APDU_STATUS_INVALID_INS;

    USARTClear();                       /* Clear USART buffer */
    ShowActivity();
    USARTSend(&CLA, 1);
    USARTSend(&INS, 1);
    USARTSend(&P1, 1);
    USARTSend(&P2, 1);
    USARTSend(&P3, 1);

	// ISO/IEC 7816-3:2006(E)
	//
	// 10.3.3  Procedure Bytes
	//
	// After transmitting the header as a string of five characters,
	// the interface device shall wait for a character conveying a procedure byte.
	//
	//                                    Table 11 - Procedure bytes
	//
	// Byte          Value                   Action on data transfer                 Then reception of
	// ====  ===================    ==============================================   =================
	// NULL          '60'                           No action                         A procedure byte
	// SW1   '6X' (!='60'), '9X'                    No action                            A SW2 byte
	// ACK           INS            All remaining data bytes (if any bytes remain)    A procedure byte
	// ACK         INS ^ 'FF'            The next data byte (if it exists)            A procedure byte

	// The first two editions of ISO/IEC 7816-3 specified the use of two values of ACK
	// (namely, the exclusive-or of the value of INS with '01' and 'FE') to control
	// the deprecated use of contact C6 (see 5.1.1). These two values are deprecated.

    // Grab procedure bytes from the smart card in response to the command
    while(1)
    {
        ShowActivity();
        smartcardCommandDelay(1);
        procedureByte = USARTBuffer[index++];

		// If the value is '60', it is a NULL byte. It requests no action on data transfer.
		// The interface device shall wait for a character conveying a procedure byte.
        if(procedureByte == 0x60)
            continue;

		// If the value is '6X' or '9X', except for '60', it is a SW1 byte. It requests no action on data transfer.
		// The interface device shall wait for a character conveying a SW2 byte. There is no restriction on SW2 value.
        if((procedureByte >> 4) == 6 || (procedureByte >> 4) == 9)
        {
            *SW1 = procedureByte;
            ShowActivity();
            smartcardCommandDelay(1);
            *SW2 = USARTBuffer[index++];
            switch(*SW1)
            {
                case 0x90:
                    return APDU_STATUS_SUCCESS;
                case 0x6e:
                    return APDU_STATUS_INVALID_CMD;
                case 0x6d:
                    return APDU_STATUS_INVALID_INS;
                case 0x6b:
                    return APDU_STATUS_INVALID_P1P2;
                case 0x67:
                    return APDU_STATUS_INVALID_P3;
                case 0x6f:
                    return APDU_STATUS_UNKNOWN_ERROR;
            }
        }

		// If the value is the value of INS, apart from the values '6X' and '9X', it is an ACK byte.
		// All remaining data bytes if any bytes remain, denoted Di to Dn, shall be transferred subsequently.
		// Then the interface device shall wait for a character conveying a procedure byte.
        if(procedureByte == INS)
        {
            ShowActivity();
            if(writeFlag)
                USARTSend(DataBuff, dataLen);
            else
            {
                smartcardCommandDelay(dataLen);
                memcpy(DataBuff, (const char *)&USARTBuffer[index], dataLen);
                *RDataCount += dataLen;
                index += dataLen;
            }
            DataBuff += dataLen;
            dataLen = 0;
            continue;
        }


		// If the value is the exclusive-or of 'FF' with the value of INS, apart from the values '6X' and '9X',
		// it is an ACK byte. Only the next data byte if it exists, denoted Di, shall be transferred.
		// Then the interface device shall wait for a character conveying a procedure byte.
        if(procedureByte == (INS ^ 0xff))
        {
            if(!dataLen)
                return APDU_STATUS_INVALID_PROCEDURE_BYTE;
            ShowActivity();
            if(writeFlag)
            {
                USARTSend(DataBuff, 1);
                DataBuff++;
            }
            else
            {
                smartcardCommandDelay(1);
                *DataBuff++ = USARTBuffer[index++];
                //*RDataCount++;
            }
            dataLen--;
            continue;
        }

		// Any other value is invalid.
        return APDU_STATUS_INVALID_PROCEDURE_BYTE;
    }
}

void smartcardParseATR(int buflen, unsigned char *ATRBuf)
{
    int i;
    uint8_t *buffer_ptr;
    uint8_t TS, T0, TA[15], TB[15], TC[15], TD[15];
    uint8_t InterfaceBytesBitmap, InterfaceBytesSet;
    int transmissionProtocol = -1;
    printf("ATR: ");
    for(i = 0; i < buflen; i++){

    	printf("%02x ", ATRBuf[i]);

    }
    printf("\n");
    buffer_ptr = ATRBuf;
    TS = *buffer_ptr++;
    printf("TS = 0x%02x\n", TS);
    T0 = InterfaceBytesBitmap = *buffer_ptr++;
    printf("T0 = 0x%02x\n", T0);
    InterfaceBytesSet = 0;
    while((InterfaceBytesBitmap & 0xf0) && (InterfaceBytesSet < sizeof(TA)))
    {
        if(InterfaceBytesBitmap & 0x10)
        {
            TA[InterfaceBytesSet] = *buffer_ptr++;
            printf("TA%d = 0x%02x\n", InterfaceBytesSet, TA[InterfaceBytesSet]);
        }

        if(InterfaceBytesBitmap & 0x20)
        {
            TB[InterfaceBytesSet] = *buffer_ptr++;
            printf("TB%d = 0x%02x\n", InterfaceBytesSet, TB[InterfaceBytesSet]);
        }

        if(InterfaceBytesBitmap & 0x40)
        {
            TC[InterfaceBytesSet] = *buffer_ptr++;
            printf("TC%d = 0x%02x\n", InterfaceBytesSet, TC[InterfaceBytesSet]);
        }

        if(InterfaceBytesBitmap & 0x80)
        {
            TD[InterfaceBytesSet] = InterfaceBytesBitmap = *buffer_ptr++;\
            if(InterfaceBytesSet == 0)
                transmissionProtocol = TD[InterfaceBytesSet] & 0x0f;
            printf("TD%d = 0x%02x\n", InterfaceBytesSet, TD[InterfaceBytesSet]);
            InterfaceBytesSet++;
        }
        else
            InterfaceBytesBitmap = 0;
    }
    printf("HistoricalBytes: ");
    for(i = 0; i < buflen - (buffer_ptr - ATRBuf); i++){

    	printf("%02x ", *(buffer_ptr + i));

    }
    	printf("\n");

    if(transmissionProtocol != -1)
        printf("\nTransmission protocol: T%d\n", transmissionProtocol);

}

