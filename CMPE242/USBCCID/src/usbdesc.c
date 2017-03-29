/*----------------------------------------------------------------------------
 *      U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    usbdesc.c
 * Purpose: USB Descriptors
 * Version: V1.20
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
 *----------------------------------------------------------------------------
 * History:
 *          V1.20 Changed string descriptor handling
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/
#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbdesc.h"
#include "usbccid.h"

/* USB Standard Device Descriptor */
const uint8_t USB_DeviceDescriptor[] = {
    USB_DEVICE_DESC_SIZE,              /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,        /* bDescriptorType */
#if LPM_SUPPORT
    WBVAL(0x0201), /* 2.01 */          /* bcdUSB */
#else
    WBVAL(0x0200), /* 2.00 */          /* bcdUSB */
#endif
    0x00,                              /* bDeviceClass */
    0x00,                              /* bDeviceSubClass */
    0x00,                              /* bDeviceProtocol */
    USB_MAX_PACKET0,                   /* bMaxPacketSize0 */
    WBVAL(0x1FC9),                     /* idVendor */


    WBVAL(0x7477),                     /* idProduct */
    WBVAL(0x0100), /* 1.00 */          /* bcdDevice */
    0x01,                              /* iManufacturer */
    0x02,                              /* iProduct */
    0x00,                              /* iSerialNumber */
    0x01                               /* bNumConfigurations: one possible configuration*/
};

/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor) */
const uint8_t USB_ConfigDescriptor[] = {
/* Configuration 1 */
    USB_CONFIGUARTION_DESC_SIZE,       /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType */
    WBVAL(                             /* wTotalLength */
    		USB_CONFIGUARTION_DESC_SIZE +
    		USB_INTERFACE_DESC_SIZE     +
    		USB_SMARTCARD_DESCRIPTOR_SIZE +
    		USB_ENDPOINT_DESC_SIZE      +
    		USB_ENDPOINT_DESC_SIZE      +
    		USB_ENDPOINT_DESC_SIZE
         ),
    0x01,                              /* bNumInterfaces */
    0x01,                              /* bConfigurationValue */
    0x00,                              /* iConfiguration */
#if REMOTE_WAKEUP_ENABLE			 /* bmAttributes */
    USB_CONFIG_BUS_POWERED|USB_CONFIG_REMOTE_WAKEUP, 
#else
    USB_CONFIG_BUS_POWERED,
#endif
    USB_CONFIG_POWER_MA(100),          /* bMaxPower */

    /* Interface 0, Alternate Setting 0, MSC Class */
    USB_INTERFACE_DESC_SIZE,            /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType */
    0x00,                               /* bInterfaceNumber */
    0x00,                               /* bAlternateSetting */
    0x03,                               /* bNumEndpoints */
    USB_DEVICE_CLASS_SMARTCARD,         /* bInterfaceClass */
    0,                                  /* bInterfaceSubClass */
    0,                                  /* bInterfaceProtocol */
    0x00,                               /* iInterface */

    /* Smart Card Device Descriptor (endpoints follow)*/
    USB_SMARTCARD_DESCRIPTOR_SIZE,
    USB_SMARTCARD_DESCRIPTOR_TYPE,
    WBVAL(0x0100), /* 1.0 */            /* bcdCCID*/
    0,                                  /* Max Slot Index (only one)*/
    0x7,                                /* Voltage Support*/
    DBVAL(3),                           /*Protocols */
    DBVAL(0xfa0),                       /* Default Clock*/
    DBVAL(0xfa0),                       /* Max Clock*/
    0,                                  /* Num Clock Supported*/
    DBVAL(0x2a0),                       /* Data Rate*/
    DBVAL(0x3d090),                     /* Max Data Rate*/
    0,                                  /* Number of Data Rates*/
    DBVAL(0xfe),                        /* Max IFSD*/
    DBVAL(0),                           /* Synch Protocols*/
    DBVAL(0),                           /* Synch Protocols*/
    DBVAL(0x20042),                     /* Features */
    DBVAL(0x10f),                       /* Max CCID Message Length */
    0x0,                                /* Class Get Response */
    0,                                  /* Class Envelope */
    WBVAL(0),                           /* LCD Layout */
    0,                                  /* Pin Support */
    1,                                  /* Max Busy Slots */


    /* Endpoint, EP1 Bulk IN */
    USB_ENDPOINT_DESC_SIZE,             /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType */
    USB_ENDPOINT_IN(1),                 /* bEndpointAddress */
    USB_ENDPOINT_TYPE_INTERRUPT,        /* bmAttributes */
    WBVAL(8),                           /* wMaxPacketSize */
    0x02,                               /* bInterval: ignore for Bulk transfer */

    /* Endpoint, EP2 Bulk OUT */
    USB_ENDPOINT_DESC_SIZE,            /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
    USB_ENDPOINT_OUT(2),                /* bEndpointAddress */
    USB_ENDPOINT_TYPE_BULK,            /* bmAttributes */
    WBVAL(USB_MAX_NON_ISO_SIZE),       /* wMaxPacketSize */
    0x00,                              /* bInterval: ignore for Bulk transfer */

    /* Endpoint, EP2 Bulk IN */
    USB_ENDPOINT_DESC_SIZE,            /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType */
    USB_ENDPOINT_IN(2),               /* bEndpointAddress */
    USB_ENDPOINT_TYPE_BULK,            /* bmAttributes */
    WBVAL(USB_MAX_NON_ISO_SIZE),       /* wMaxPacketSize */
    0x00,                              /* bInterval: ignore for Bulk transfer */
    /* Terminator */
    0                                  /* bLength */
};

/* USB String Descriptor (optional) */
const uint8_t USB_StringDescriptor[] = {
/* Index 0x00: LANGID Codes */
    0x04,                              /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    WBVAL(0x0409), /* US English */    /* wLANGID */
/* Index 0x01: Manufacturer */
    (3*2 + 2),                        /* bLength (13 Char + Type + lenght) */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'A',0,
    'C',0,
    'S',0,
/* Index 0x02: Product */
    (21*2 + 2),                        /* bLength ( 19 Char + Type + lenght) */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'A',0,
    'C',0,
    'R',0,
    '3',0,
    '8',0,
    ' ',0,
    'C',0,
    'C',0,
    'I',0,
    'D',0,
    ' ',0,
    'U',0,
    'S',0,
    'B',0,
    ' ',0,
    'R',0,
    'e',0,
    'a',0,
    'd',0,
    'e',0,
    'r',0,
/* Index 0x03: Serial Number */
    (12*2 + 2),                        /* bLength (12 Char + Type + lenght) */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    '0',0,                             /* allowed characters are       */
    '0',0,                             /*   0x0030 - 0x0039 ('0'..'9') */
    '0',0,                             /*   0x0041 - 0x0046 ('A'..'F') */
    '1',0,                             /*   length >= 26               */
    'A',0,
    '0',0,
    '0',0,
    '0',0,
    '0',0,
    '0',0,
    '0',0,
    '0',0,
/* Index 0x04: Interface 0, Alternate Setting 0 */
    ( 6*2 + 2),                        /* bLength (6 Char + Type + lenght) */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'S',0,
    'M',0,
    'A',0,
    'R',0,
    'R',0,
    'T',0,
};

#if LPM_SUPPORT
/* In order to test Link Power Management(LPM), bcdUSB needs to be 0x0201(USB 2.0
Extension) instead of 0x0200. Below BOS descriptor is for LPM test only. However, 
current USBC2.0 CV test requires both Super Speed Device Capability Descriptor
and Device Capability descriptor to be present and wSpeedSupport should be 0x000F 
instead of 0x0003 indicating it's a Super Speed Device or USBCV test will fail. 
For USB2.0 extention and LPM support, the device is not necessary a Super Speed 
Device. To be discussed with USB-IF. */

/* USB BOS Descriptor */
const uint8_t USB_BOSDescriptor[] = {
    USB_BOS_DESC_SIZE,                 /* bLength */
    USB_BOS_TYPE,                      /* bDescriptorType, BOS */
    WBVAL(                             /* wTotalLength */
                                       USB_BOS_DESC_SIZE +
                                       USB_SS_DEVICE_CAPABILITY_SIZE +
                                       USB_DEVICE_CAPABILITY_SIZE
         ),
    0x02,                               /* bNumDeviceCaps, One Device Capability desc. */
    /* Device Capabilities, USB 2.0 Extension Descriptor */
    USB_SS_DEVICE_CAPABILITY_SIZE,     /* bLength */
    USB_DEVICE_CAPABILITY_TYPE,        /* bDescriptorType, DEVICE CAPABILITY */
    0x03,                              /* bDeviceCapabilityType, USB Super Speed */
    0x00,                              /* bmAttributes */
    WBVAL(0x000F),                     /* wSpeedsSupported, All speeds are supported. */
    0x02,                              /* bFunctionalitySupport, Full Speed */
    0x00,                              /* bU1DevExitLat */
    WBVAL(0x0000),                     /* bU2DevExitLat */
    /* Device Capabilities, USB 2.0 Extension Descriptor */
    USB_DEVICE_CAPABILITY_SIZE,        /* bLength */
    USB_DEVICE_CAPABILITY_TYPE,        /* bDescriptorType, DEVICE CAPABILITY */
    0x02,                              /* bDeviceCapabilityType, USB2.0 EXTENSION */
    (0x1<<1),                          /* bmAttributes, bit1 to 1, LPM supported. */
    0x00,
    0x00,
    0x00
};
#endif

