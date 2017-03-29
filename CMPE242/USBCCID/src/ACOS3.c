/****************************************************************************
 *
 *   Description:
 *     This file contains a support interface library for the ACOS3 smartcard
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
#include <string.h>
#include <stdio.h>
#include "smartcard.h"
#include "ACOS3.h"

////////////////////////////////////////////////////////////////////

#define MAX (256)

unsigned char SendBuff[262], RecvBuff[262];
int SendLen, RecvLen;

//Clears the buffers of any data
void ClearBuffers()
{

	int index;

	for( index = 0; index <= 262; index++ )
	{
		SendBuff[index] = 0x00;
		RecvBuff[index] = 0x00;
	}

}

ACOS3_CARD_STATUS ACOS3_getCardSerialNumber(int bufsize, unsigned char *buf)
{
	APDU_STATUS APDUStatus;
	unsigned char CLA, INS, P1, P2, P3, SW1, SW2, writeFlag, sbuf[8];
    int RDataCount;

	ClearBuffers();
	CLA = 0x80;
	INS = 0x14;
	P1  = 0x00;
	P2  = 0x00;
	P3  = 0x08;
	writeFlag = 0;

	APDUStatus = SendAPDU(CLA, INS, P1, P2, P3, writeFlag, sbuf, &RDataCount, 
                          &SW1, &SW2);

	if (APDUStatus == APDU_STATUS_SUCCESS)
	{
		memcpy(buf, sbuf, bufsize < 8?bufsize:8);
		return ACOS3_CARD_STATUS_SUCCESS;
	}
	else
		return ACOS3_CARD_STATUS_ERROR;

}

ACOS3_CARD_STATUS ACOS3_getCardEEPROMSize(unsigned char *eepromSize)
{
	APDU_STATUS APDUStatus;
	unsigned char CLA, INS, P1, P2, P3, SW1, SW2, writeFlag;
    int RDataCount;

	ClearBuffers();
	CLA = 0x80;
	INS = 0x14;
	P1  = 0x05;
	P2  = 0x00;
	P3  = 0x00;
	writeFlag = 0;

	APDUStatus = SendAPDU(CLA, INS, P1, P2, P3, writeFlag, NULL, &RDataCount, 
                          &SW1, &SW2);

	if (APDUStatus == APDU_STATUS_SUCCESS)
	{
		*eepromSize = SW2;
		return ACOS3_CARD_STATUS_SUCCESS;
	}
	else
		return ACOS3_CARD_STATUS_ERROR;
}

ACOS3_CARD_STATUS ACOS3_getCardRevision(int bufsize, unsigned char *buf)
{
	APDU_STATUS APDUStatus;
	unsigned char CLA, INS, P1, P2, P3, SW1, SW2, writeFlag, sbuf[8];
    int RDataCount;

	ClearBuffers();
	CLA = 0x80;
	INS = 0x14;
	P1  = 0x06;
	P2  = 0x00;
	P3  = 0x08;
	writeFlag = 0;

	APDUStatus = SendAPDU(CLA, INS, P1, P2, P3, writeFlag, sbuf, &RDataCount, 
                          &SW1, &SW2);

	if (APDUStatus == APDU_STATUS_SUCCESS)
	{
		memcpy(buf, sbuf, bufsize < 8?bufsize:8);
		return ACOS3_CARD_STATUS_SUCCESS;
	}
	else
		return ACOS3_CARD_STATUS_ERROR;
}

ACOS3_CARD_STATUS ACOS3_ReadRecord(unsigned char record, unsigned char offset, unsigned char datalen, unsigned char *databuf)
{
	APDU_STATUS APDUStatus;
	unsigned char CLA, INS, P1, P2, P3, SW1, SW2, writeFlag;
    int RDataCount;

	ClearBuffers();
	CLA = 0x80;
	INS = 0xb2;
	P1  = record;
	P2  = offset;
	P3  = datalen;
	writeFlag = 0;

	APDUStatus = SendAPDU(CLA, INS, P1, P2, P3, writeFlag, databuf, &RDataCount,
                          &SW1, &SW2);

	if (APDUStatus == APDU_STATUS_SUCCESS)
		return ACOS3_CARD_STATUS_SUCCESS;
	else
		return ACOS3_CARD_STATUS_ERROR;

}

ACOS3_CARD_STATUS ACOS3_SelectFile(unsigned short fileID)
{
	APDU_STATUS APDUStatus;
	unsigned char CLA, INS, P1, P2, P3, SW1, SW2, writeFlag;
    int RDataCount;

	ClearBuffers();
	CLA = 0x80;
	INS = 0xa4;
	P1  = 0x00;
	P2  = 0x00;
	P3  = 0x02;
	writeFlag = 1;

	APDUStatus = SendAPDU(CLA, INS, P1, P2, P3, writeFlag, (unsigned char *)&fileID, &RDataCount,
                          &SW1, &SW2);

	if (APDUStatus == APDU_STATUS_SUCCESS)
		return ACOS3_CARD_STATUS_SUCCESS;
	else
		return ACOS3_CARD_STATUS_ERROR;

}


ACOS3_CARD_STATUS ACOS3_DumpCardParameters(int ATRLen, unsigned char *ATRBuf)
{
	int i;
	unsigned char revision;
	unsigned char optionRegister;
	unsigned char securityOptionRegister;
	unsigned char N_OF_FILE;
	unsigned char personalizationFile[ACOS3_PERSONALIZATIONFILE_LEN];
	LIFECYCLE_STATE lifecycleState;
	unsigned char eepromSize;

	if (ACOS3_CARD_STATUS_SUCCESS != ACOS3_ParseATR(
			ATRLen,
			ATRBuf,
			&revision,
			&optionRegister,
			&securityOptionRegister,
			&N_OF_FILE,
			personalizationFile,
			&lifecycleState))
	{
		printf("Not a ACOS3 card\n");
		return ACOS3_CARD_STATUS_INVALID;
	}

	printf("Revision:               %d.%d\n", revision >> 4 & 0x0f, revision & 0x0f);
	printf("OptionRegister:         0x%x\n", optionRegister);
	printf("SecurityOptionRegister: 0x%x\n", securityOptionRegister);
	printf("N_OF_FILE:              0x%x\n", N_OF_FILE);
	printf("PersonalizationFile:    ");
	for(i = 0; i < ACOS3_PERSONALIZATIONFILE_LEN; i++){

		printf("0x%02x ", personalizationFile[i]);

	}
		printf("\n");
	printf("Lifecycle State:        ");
	switch(lifecycleState)
	{
	case LIFECYCLE_STATE_USER_STATE:
		printf("User");
		break;

	case LIFECYCLE_STATE_MANUFACTURING_STATE:
		printf("Manufacturing");
		break;

	case LIFECYCLE_STATE_PERSONALIZATION_STATE:
		printf("Personalization");
		break;
	}
	printf(" State\n");

	if (ACOS3_CARD_STATUS_SUCCESS == ACOS3_getCardSerialNumber(ACOS3_SERIALNUMBER_LEN, ATRBuf))
	{
		printf("Card serial number:     ");
		for(i = 0; i < ACOS3_SERIALNUMBER_LEN; i++){

			printf("%02x ", *(ATRBuf + i));

		}
		printf("\n");
	}
	else
		printf("ERROR: unable to get card info\n");

	if (ACOS3_CARD_STATUS_SUCCESS == ACOS3_getCardEEPROMSize(&eepromSize))
		printf("Card EEPROM size:       %dk bytes\n", eepromSize);
	else
		printf("ERROR: unable to get card info\n");

	if (ACOS3_CARD_STATUS_SUCCESS == ACOS3_getCardRevision(ACOS3_REVISION_LEN, ATRBuf))
	{
		printf("Card revision:          ");
		for(i = 0; i < ACOS3_REVISION_LEN; i++){
			printf("%02x ", *(ATRBuf + i));
		}
		printf("\n");
	}
	else
		printf("ERROR: unable to get card info\n");

	return ACOS3_CARD_STATUS_SUCCESS;

}

ACOS3_CARD_STATUS ACOS3_ParseATR(
		int buflen,
		unsigned char *ATRBuf,
		unsigned char *revision,
		unsigned char *optionRegister,
		unsigned char *securityOptionRegister,
		unsigned char *N_OF_FILE,
		unsigned char personalizationFile[ACOS3_PERSONALIZATIONFILE_LEN],
		LIFECYCLE_STATE *lifecycleState)
{
	unsigned char *cptr = ATRBuf + 5;

	if ((*cptr++ != 0x41) || (*cptr++ != 1) || (*(ATRBuf + 17) != 0x90) || (*(ATRBuf + 18) != 0))
		return(ACOS3_CARD_STATUS_INVALID);

	*revision = *cptr++;
	*optionRegister = *cptr++;
	*securityOptionRegister = *cptr++;
	*N_OF_FILE = *cptr++;
	memcpy(personalizationFile, cptr, ACOS3_PERSONALIZATIONFILE_LEN);
	cptr += ACOS3_PERSONALIZATIONFILE_LEN;
	*(unsigned char *)lifecycleState = *cptr++;

	return ACOS3_CARD_STATUS_SUCCESS;
}

