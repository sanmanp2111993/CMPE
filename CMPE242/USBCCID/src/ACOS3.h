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

typedef enum
{
	ACOS3_CARDINFO_SERIALNUM,
	ACOS3_CARDINFO_EEPROM_SIZE,
	ACOS3_CARDINFO_REVISION,
}ACOS3_CARDINFO;

typedef enum
{
	LIFECYCLE_STATE_USER_STATE,
	LIFECYCLE_STATE_MANUFACTURING_STATE,
	LIFECYCLE_STATE_PERSONALIZATION_STATE,
}LIFECYCLE_STATE;

typedef enum
{
	ACOS3_CARD_STATUS_SUCCESS,
	ACOS3_CARD_STATUS_ERROR,
	ACOS3_CARD_STATUS_INVALID,
}ACOS3_CARD_STATUS;

#define ACOS3_PERSONALIZATIONFILE_LEN (5)
#define ACOS3_SERIALNUMBER_LEN (8)
#define ACOS3_REVISION_LEN (8)

void ClearBuffers();
ACOS3_CARD_STATUS ACOS3_getCardSerialNumber(int bufsize, unsigned char *buf);
ACOS3_CARD_STATUS ACOS3_getCardEEPROMSize(unsigned char *eepromSize);
ACOS3_CARD_STATUS ACOS3_getCardRevision(int bufsize, unsigned char *buf);
ACOS3_CARD_STATUS ACOS3_ParseATR(
		int buflen,
		unsigned char *ATRBuf,
		unsigned char *revision,
		unsigned char *optionRegister,
		unsigned char *securityOptionRegister,
		unsigned char *N_OF_FILE,
		unsigned char personalizationFile[ACOS3_PERSONALIZATIONFILE_LEN],
		LIFECYCLE_STATE *lifecycleState);
ACOS3_CARD_STATUS ACOS3_DumpCardParameters(int ATRLen, unsigned char *ATRBuf);
ACOS3_CARD_STATUS ACOS3_ReadRecord(unsigned char record, unsigned char offset, unsigned char datalen, unsigned char *databuf);
ACOS3_CARD_STATUS ACOS3_SelectFile(unsigned short fileID);

