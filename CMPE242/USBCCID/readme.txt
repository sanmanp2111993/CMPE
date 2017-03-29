USB CCID class example
======================
This project contains a USB CCID class (smart card) example device that runs on top of a USART interface. There are four major components in this example
1. the USART layer
2  the generic smartcard (ISO7816) layer
3. a card specific layer that drives a ACOS3 smart card from ACS.
4. USB CCID class layer


Hardware
========
The hardware that runs this project includes a LPCXpresso board with a LPC11u14 wired up to a smartcard socket. The smartcard socket can be found here: http://www.bgmicro.com/soc1021.aspx


This is how the smartcard socket is wired to the LPCXpresso board:

smartcard socket	LPCXpresso
----------------	----------
card detect		  	P1.14
goldpad reset		P1.16
goldpad IO		  	P0.19
goldpad clk		  	P0.17
goldpad power		3.3v
goldpad ground		gnd



The main routine initializes the system and then runs the example. There are two versions of this example that can be run, based on the value of USB_CCID defined in usbcfg.h.

If USB_CCID = 1 -> USB CCID test

The timer, USART, and GPIO systems are initialized
The USB driver is initialized
An endless loop is entered where:
	A card insertiion/removal is detected
	USB CCID class commands are acted upon


If USB_CCID = 0 -> Smartcard test

The timer, USART, and GPIO systems are initialized
An endless loop is entered where:
	A card insertiion/removal is detected
	A series of commands are sent to the card and the response is displayed

	LED Status- The status of the LED on the LPCXpresso board indicates any one of the following:
o	Continuously blinking: Indicates that a card has not been inserted yet
o	Continuously On: Indicates that a card has been inserted
o	Activity: When a card insertion is detected, the USART activity is indicated by toggling the LED


This project includes semi-hosting support. This is the expected output when USB_CCID = 0:
-----------------------------------------------------------------

Smartcard demo

Waiting for ACOS3 card insertion ...

Resetting smart card ...
ATR: 3b be 11 00 00 41 01 38 00 00 00 00 00 00 00 00 01 90 00 
TS = 0x3b
T0 = 0xbe
TA0 = 0x11
TB0 = 0x00
TD0 = 0x00
HistoricalBytes: 41 01 38 00 00 00 00 00 00 00 00 01 90 00 

Transmission protocol: T0

Display ACOS3 card parameters ...
Revision:               3.8
OptionRegister:         0x0
SecurityOptionRegister: 0x0
N_OF_FILE:              0x0
PersonalizationFile:    0x00 0x00 0x00 0x00 0x00 
Lifecycle State:        Manufacturing State
Card serial number:     35 33 d7 0f 3e e5 09 c4 
Card EEPROM size:       32k bytes
Card revision:          41 43 4f 53 03 01 16 20 

Selecting the MCU-ID file ...
Record 0:  0x35 0x33 0xd7 0xf 0x3e 0xe5 0x9 0xc4 
Record 1:  0x41 0x43 0x4f 0x53 0x3 0x1 0x16 0x20 
Card removed

Waiting for ACOS3 card insertion ...

-----------------------------------------------------------------


