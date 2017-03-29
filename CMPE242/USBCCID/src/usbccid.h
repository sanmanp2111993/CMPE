#ifndef _USBCCID_H_
#define _USBCCID_H_
/****************************************************************************
 *
 *   Description:
 *     This file contains a USB CCID Class interface that sits on top of the
 *     smartcard code
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
typedef PRE_PACK struct _USB_SMARTCARD_DESCRIPTOR {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t bcdCCID;
    uint8_t  bMaxSlotIndex;
    uint8_t  bVoltageSupport;
    uint32_t dwProtocols;
    uint32_t dwDefaultClock;
    uint32_t dwMaximumClock;
    uint8_t  bNumClockSupported;
    uint32_t dwDataRate;
    uint32_t dwMaxDataRate;
    uint8_t  bNumDataRatesSupported;
    uint32_t dwMaxIFSD;
    uint32_t dwSynchProtocols;
    uint32_t dwMechanical;
    uint32_t dwFeatures;
    uint32_t dwMaxCCIDMessageLength;
    uint8_t  bClassGetResponse;
    uint8_t  bClassEnvelope;
    uint16_t wLcdLayout;
    uint8_t  bPinSupport;
    uint8_t  bMaxCCIDBusySlots;
} POST_PACK USB_SMARTCARD_DESCRIPTOR;

typedef PRE_PACK struct _CCID_OUT_MSG
{
    uint8_t MessageType;
    uint32_t MsgLen;
    uint8_t SlotNum;
    uint8_t SeqNum;
    uint8_t BWI;
    uint16_t LevelParameter;
    uint8_t Data[54];
} POST_PACK CCID_OUT_MSG;

/* CCID Messages to Device*/
#define SetParameters   0x61
#define IccPowerOn      0x62
#define IccPowerOff     0x63
#define GetSlotStatus   0x65
#define GetParameters   0x6c
#define XfrBlock        0x6f



typedef PRE_PACK struct _CCID_IN_MSG
{
    uint8_t MessageType;    // 0    
    uint32_t MsgLen;        // 1
    uint8_t SlotNum;        // 5
    uint8_t SeqNum;         // 6
    uint8_t CmdStatus;      // 7
    uint8_t ErrCode;        // 8
    uint8_t ChainParam;     // 9
    uint8_t Data[54];       //  0xa
} POST_PACK CCID_IN_MSG;

/* CCID Messages from the Device*/
#define DataBlock       0x80
#define SlotStatus      0x81
#define ParameterResp   0x82

#define CMDSTATUS_OK    0x1
#define CMDNOTSUPT      0x40;

typedef PRE_PACK struct _CCID_INT
{
    uint8_t MessageType;
    uint8_t Status;
} POST_PACK CCID_INT;

/* CCID Interrupt Message Types*/
#define SlotChange      0x50

/* CCID Class Requests on EP0*/
#define CCID_REQUEST_ABORT              0x01
#define CCID_REQUEST_GET_CLOCK_FREQS    0x02
#define CCID_REQUEST_GET_DATA_RATES     0x03

/* Smart Card Endpoint Def's */
#define SC_EP_IN        0x82    /* Status and Data from the Smart Card */
#define SC_EP_OUT       0x02    /* Command and Data to the Smart Card */
#define SC_EP_INT       0x81    /* Interrupt IN endpoint for card change notifications*/

/* Prototypes*/

void USBCCIDConfigureEvent(void);
void USBCCIDResetEvent(void);
void ShowCardInserted(void);
void ShowCardRemoved(void);
void SC_IntIn(void);
void SC_BulkOut(void);
void ExecuteCardCmd(void);
void SC_BulkIn(void);
void TurnCardPowerOn(void);
void TurnCardPowerOff(void);
void ReturnSlotStatus(void);
void SetSlotParams(void);
void GetSlotParams(void);

extern uint8_t CCID_SlotAbort;
extern uint8_t CCID_SeqAbort;


#endif // _USBCCID_H_

