/****************************************************************************

 *   Description:
 *     This file contains a USB CCID Class interface that sits on top of the
 *     smartcard routines.
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
#include "LPC11Uxx.h"
#include "config.h"
#include "type.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbuser.h"
#include "smartcard.h"
#include "usbccid.h"
#include "misc_gpio.h"


extern uint8_t CardInserted;
uint8_t CCID_SlotAbort;
uint8_t CCID_SeqAbort;


CCID_OUT_MSG  CmdBuf; /* Smart Card Command Buffer*/
uint8_t  CmdLen;      /* Command Length */

CCID_IN_MSG StatusBuf;
uint8_t  StatusLen;
uint8_t StatusValid;

CCID_INT IntMsg;
uint8_t IntMsgValid;

uint8_t CardInserted = 0;

void USBCCIDConfigureEvent(void)
{
    IntMsgValid = 1;
    SC_IntIn();
}

void USBCCIDResetEvent(void)
{
    //CardPowerOff();
}

void ShowCardRemoved(void)
{
    CardInserted = 0;
    IntMsg.MessageType = SlotChange;
    IntMsg.Status = 0x00;
    IntMsgValid = 1;
    SC_IntIn();
}

void ShowCardInserted(void)
{
    CardInserted = 1;
    IntMsg.MessageType = SlotChange;
    IntMsg.Status = 0x03;
    IntMsgValid = 1;
    SC_IntIn();
}

void SC_IntIn(void)
{
    if(IntMsgValid)
    {
        USB_WriteEP(SC_EP_INT, (uint8_t *)&IntMsg, sizeof(IntMsg));
        IntMsgValid = 0;
    }
}

void SC_BulkOut(void)
{
    CmdLen = USB_ReadEP(SC_EP_OUT, ( uint8_t *)&CmdBuf);

    switch(CmdBuf.MessageType)
    {
        case SetParameters:
//        	printf("HOST: SetParameters\n");
            SetSlotParams();
            break;

        case GetParameters:
//        	printf("HOST: GetParameters\n");
            GetSlotParams();
            break;

        case GetSlotStatus:
//        	printf("HOST: GetSlotStatus\n");
            ReturnSlotStatus();
            break;

        case XfrBlock:
//        	printf("HOST: XfrBlock\n");
            ExecuteCardCmd();
            break;

        case IccPowerOn:
//        	printf("HOST: IccPowerOn\n");
            TurnCardPowerOn();
            break;

        case IccPowerOff:
//        	printf("HOST: IccPowerOff\n");
            TurnCardPowerOff();
            break;

        default:
        	printf("HOST: UNHANDLED CMD 0x%x\n", CmdBuf.MessageType);
            break;
    }
    if(StatusValid)
    {
        SC_BulkIn();
    }
}

void ExecuteCardCmd(void)
{
	unsigned char CLA, INS, P1, P2, P3, SW1, SW2, writeFlag;
    int RDataCount;
    APDU_STATUS status;

    StatusBuf.MessageType = DataBlock;
    StatusBuf.SlotNum = CmdBuf.SlotNum;
    StatusBuf.SeqNum = CmdBuf.SeqNum;
    StatusBuf.CmdStatus = 0;
    StatusBuf.ErrCode = 0;
    StatusBuf.ChainParam = 0;

    CLA = CmdBuf.Data[0];
    INS = CmdBuf.Data[1];
    P1 = CmdBuf.Data[2];
    P2 = CmdBuf.Data[3];
    P3 = CmdBuf.Data[4];
    if(CmdBuf.MsgLen > 5)
    {
        // This is a write command
        writeFlag = 1;
        status = SendAPDU(CLA,INS,P1,P2,P3,1,&CmdBuf.Data[5], 
                          &RDataCount, &SW1, &SW2);
        StatusBuf.Data[0] = SW1;
        StatusBuf.Data[1] = SW2;
        StatusBuf.MsgLen = 2;
    }else
    {
        writeFlag = 0;
        status = SendAPDU(CLA,INS,P1,P2,P3,0,&StatusBuf.Data[0],  
                          &RDataCount, &SW1, &SW2);
        StatusBuf.Data[RDataCount] = SW1;
        StatusBuf.Data[RDataCount+1] = SW2;
        StatusBuf.MsgLen = RDataCount+2;
    }

    StatusLen = sizeof(StatusBuf) - sizeof(StatusBuf.Data) + StatusBuf.MsgLen;
    StatusValid = 1;

}

void SC_BulkIn(void)
{

    if(StatusValid)
    {
        USB_WriteEP(SC_EP_IN, (uint8_t *)&StatusBuf, StatusLen);
        StatusValid = 0;
    }
}

void SetSlotParams(void)
{
    StatusBuf.MessageType = ParameterResp;
    StatusBuf.SlotNum = CmdBuf.SlotNum;
    StatusBuf.SeqNum = CmdBuf.SeqNum;
    StatusBuf.CmdStatus = CMDNOTSUPT;
    StatusBuf.ErrCode = 0;
    StatusBuf.ChainParam = 0;
    StatusBuf.MsgLen = 0;
    StatusLen = 10;
    StatusValid = 1;
}

void GetSlotParams(void)
{
    StatusBuf.MessageType = ParameterResp;
    StatusBuf.SlotNum = CmdBuf.SlotNum;
    StatusBuf.SeqNum = CmdBuf.SeqNum;
    StatusBuf.CmdStatus = 0;
    StatusBuf.ErrCode = 0;
    StatusBuf.ChainParam = 0;
    StatusBuf.MsgLen = 5;
    StatusBuf.Data[0] = 0x11;
    StatusBuf.Data[1] = 0;
    StatusBuf.Data[2] = 0;
    StatusBuf.Data[3] = 0xa;
    StatusBuf.Data[4] = 0;
    StatusLen = 15;
    StatusValid = 1;
}

void TurnCardPowerOn(void)
{
	// Initialize the smart card and underlying USART
	smartcardInit();

    StatusBuf.MessageType = DataBlock;
    StatusBuf.SlotNum = CmdBuf.SlotNum;
    StatusBuf.SeqNum = CmdBuf.SeqNum;
    StatusBuf.CmdStatus = 0;
    StatusBuf.ErrCode = 0;
    StatusBuf.ChainParam = 0;
    StatusBuf.MsgLen = smartcardReset(sizeof(StatusBuf.Data), &(StatusBuf.Data[0]));
	//smartcardParseATR(StatusBuf.MsgLen, &(StatusBuf.Data[0]));

    StatusLen = sizeof(StatusBuf) - sizeof(StatusBuf.Data) + StatusBuf.MsgLen;
    StatusValid = 1;
}

void TurnCardPowerOff(void)
{
    CardPowerOff();
    StatusBuf.MessageType = SlotStatus;
    StatusBuf.MsgLen = 0;
    StatusBuf.SlotNum = CmdBuf.SlotNum;
    StatusBuf.SeqNum = CmdBuf.SeqNum;
    StatusBuf.CmdStatus = CMDSTATUS_OK;
    StatusBuf.ErrCode = 0;
    StatusBuf.ChainParam = 0;
    StatusLen = 10;
    StatusValid = 1;

}

void ReturnSlotStatus(void)
{
    StatusBuf.MessageType = SlotStatus;
    StatusBuf.MsgLen = 0;
    StatusBuf.SlotNum = CmdBuf.SlotNum;
    StatusBuf.SeqNum = CmdBuf.SeqNum;

    if(CardInserted)
    {
        StatusBuf.CmdStatus = 0;
        StatusBuf.ErrCode = 0;
        StatusBuf.ChainParam = 0;
        StatusLen = 10;
    }else
    {
        StatusBuf.CmdStatus = CMDSTATUS_OK;
        StatusBuf.ErrCode = 0;
        StatusBuf.ChainParam = 0;
        StatusLen = 10;
    }
    StatusValid = 1;
}


