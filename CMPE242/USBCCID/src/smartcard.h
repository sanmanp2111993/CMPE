/****************************************************************************
 *
 *   Description:
 *     This file contains a smartcard interface that sits on top of the USART
 *
 *   Copyright(C) 2011, NXP Semiconductor
 *   All rights reserved.
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
#define MAX_ATR_LEN (32)

typedef enum
{
	APDU_STATUS_SUCCESS,
	APDU_STATUS_INVALID_CMD,
	APDU_STATUS_INVALID_INS,
	APDU_STATUS_INVALID_P1P2,
	APDU_STATUS_INVALID_P3,
	APDU_STATUS_UNKNOWN_ERROR,
	APDU_STATUS_INVALID_PROCEDURE_BYTE,
	APDU_STATUS_TIMEOUT,
}APDU_STATUS;

void smartcardInit();
int smartcardReset(int buflen, unsigned char *ATRBuf);
void smartcardWaitForInsertion();
void smartcardWaitForRemoval();
void smartcardParseATR(int buflen, unsigned char *ATRBuf);
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
		unsigned char *SW2
		);

/* USB descriptors and messages for CCID class*/


