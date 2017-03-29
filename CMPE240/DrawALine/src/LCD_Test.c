/****************************************************************************
 *   $Id:: ssptest.c 6098 2011-01-08 02:26:20Z nxp12832                     $
 *   Project: NXP LPC17xx SSP example
 *
 *   Description:
 *     This file contains SSP test modules, main entry, to test SSP APIs.
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
#include <cr_section_macros.h>
#include <NXP/crp.h>
//#include "longhorn_sunset.h"

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

#include "LPC17xx.h"                        /* LPC17xx definitions */
#include "ssp.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define PORT_NUM            1
#define LOCATION_NUM        0

#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

uint8_t src_addr[SSP_BUFSIZE];
uint8_t dest_addr[SSP_BUFSIZE];
int colstart = 0;
int rowstart = 0;


//LCD
#define ST7735_TFTWIDTH  240
#define ST7735_TFTHEIGHT 320
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define swap(x, y) { x = x + y; y = x - y; x = x - y; }
// delay

void delay(int ms)
{
	int count = 24000;
	int i;

	for ( i = count*ms; i--; i > 0);
}

//Colors
#define GREEN 0x00FF00
#define BLACK 0x000000
#define RED 0xFF0000
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define PINK 0xFFC0CB
#define PURPLE 0x800080
#define YELLOW 0xFFFF00
#define LIME 0x00FF00
#define MAGENTA 0xFF00FF
#define CYAN 0x00FFFF
#define SILVER 0xC0C0C0
#define GREY 0x808080
#define ORANGE 0xFFA500
#define BROWN 0xA52A2A
#define MAROON 0x800000

int _height = ST7735_TFTHEIGHT;
int _width = ST7735_TFTWIDTH;
int cursor_x = 0, cursor_y = 0;
uint32_t width;

//for writing data into the SPI
void spiwrite(uint8_t c)
{
    int portnum = 1;
    src_addr[0] = c;
    SSP_SSELToggle( portnum, 0 );
    SSPSend( portnum, (uint8_t *)src_addr, 1 );
    SSP_SSELToggle( portnum, 1 );
}
//writing commands into SPI
void writecommand(uint8_t c) {
    LPC_GPIO0->FIOCLR |= (0x1<<21);
    spiwrite(c);
}
//making LCD ready to write data
void writedata(uint8_t c) {

    LPC_GPIO0->FIOSET |= (0x1<<21);
    spiwrite(c);
}
//writing data to the LCD
void writeword(uint16_t c) {

    uint8_t d;
    d = c >> 8;
    writedata(d);
    d = c & 0xFF;
    writedata(d);
}

void write888(uint32_t color, uint32_t repeat) {
    uint8_t red, green, blue;
    int i;
    red = (color >> 16);
    green = (color >> 8) & 0xFF;
    blue = color & 0xFF;
    for (i = 0; i< repeat; i++) {
    	writedata(red);
        writedata(green);
        writedata(blue);
    }
}

void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1,
                    uint16_t y1) {

      writecommand(ST7735_CASET);
      writeword(x0);

      writeword(x1);
      writecommand(ST7735_RASET);
      writeword(y0);

      writeword(y1);

}
void drawPixel(int16_t x, int16_t y, uint32_t color) {
    if((x < 0) ||(x >= _width) || (y < 0) || (y >= _height)) return;

    setAddrWindow(x,y,x+1,y+1);
    writecommand(ST7735_RAMWR);
    write888(color, 1);
}

void HLine(int16_t x0,int16_t x1,int16_t y,uint16_t color){
    width = x1-x0+1;
    setAddrWindow(x0,y,x1,y);
    writecommand(ST7735_RAMWR);
    write888(color,width);
}
void VLine(int16_t x,int16_t y0,int16_t y1,uint16_t color){
    width = y1-y0+1;
    setAddrWindow(x,y0,x,y1);
    writecommand(ST7735_RAMWR);
    write888(color,width);
}

//Initialize LCD
void lcd_init()
{
/*
 * portnum     = 0 ;
 * cs         = p0.16 / p0.6 ?
 * rs        = p0.21
 * rst        = p0.22
 */
    uint32_t portnum = 1;
    int i;
    printf("LCD initialized\n");

    if ( portnum == 0 )
      {
        LPC_GPIO0->FIODIR |= (0x1<<16);        /* SSP1, P0.16 defined as Outputs */
      }
      else
      {
        LPC_GPIO0->FIODIR |= (0x1<<6);        /* SSP0 P0.6 defined as Outputs */
      }
    /* Set rs(dc) and rst as outputs */
    LPC_GPIO0->FIODIR |= (0x1<<21);        /* rs/dc P0.22 defined as Outputs */
    LPC_GPIO0->FIODIR |= (0x1<<22);        /* rst P0.21 defined as Outputs */


    /* Reset sequence */
    LPC_GPIO0->FIOSET |= (0x1<<22);
 delay(500);                        /*delay 500 ms */
    LPC_GPIO0->FIOCLR |= (0x1<<22);
 delay(500);                        /* delay 500 ms */
    LPC_GPIO0->FIOSET |= (0x1<<22);
 delay(500);                        /* delay 500 ms */
     for ( i = 0; i < SSP_BUFSIZE; i++ )    /* Init RD and WR buffer */
        {
            src_addr[i] = 0;
            dest_addr[i] = 0;
        }



     /* Sleep out */
     SSP_SSELToggle( portnum, 0 );
     src_addr[0] = 0x11;    /* Sleep out */
     SSPSend( portnum, (uint8_t *)src_addr, 1 );
     SSP_SSELToggle( portnum, 1 );

delay(200);

     SSP_SSELToggle( portnum, 0 );
     src_addr[0] = 0x29;    /* Disp On */
     SSPSend( portnum, (uint8_t *)src_addr, 1 );
     SSP_SSELToggle( portnum, 1 );

delay(200);
}



void fillrect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)
{
	int16_t i;
	int16_t width, height;

	width = x1-x0+1;
	height = y1-y0+1;
	setAddrWindow(x0,y0,x1,y1);
	writecommand(ST7735_RAMWR);
	write888(color,width*height);
}


void drawline(int16_t x0, int16_t y0, int16_t x1, int16_t y1,uint32_t color)
{
	int16_t slope = abs(y1 - y0) > abs(x1 - x0);
	if (slope)
	{
	swap(x0, y0);
	swap(x1, y1);
	}

	if (x0 > x1) {
	swap(x0, x1);
	swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
	ystep = 1;
	} else {
	ystep = -1;
	}

	for (; x0<=x1; x0++) {
	if (slope) {
	drawPixel(y0, x0, color);
	} else {
	drawPixel(x0, y0, color);
	}
	err -= dy;
	if (err < 0) {
	y0 += ystep;
	err += dx;
	}
	}
}


void drawsquare(int16_t x, int16_t y, uint32_t color)
{
	int16_t a0,a1,a2,a3;
	int16_t b0,b1,b2,b3;

	uint32_t j;

	int16_t x0,x1,x2,x3;
	int16_t y0,y1,y2,y3;

	x0=x;
	y0=y;
	x1=x+40;
	y1=y;
	x2=x+40;
	y2=y+40;
	x3=x;
	y3=y+40;


	  	 drawline(x0,y0,x1,y1,color);
	  	 delay(10);
	  	 drawline(x1,y1,x2,y2,color);
	  	 delay(10);
	  	 drawline(x2,y2,x3,y3,color);
	  	 delay(10);
	  	 drawline(x3,y3,x0,y0,color);

	for(j=0;j<10;j++)
	{
	  	 a0=(0.8*(x1-x0))+x0;
	  	 b0=(0.8*(y1-y0))+y0;

	  	 a1=(0.8*(x2-x1))+x1;
	  	 b1=(0.8*(y2-y1))+y1;

	  	 a2=(0.8*(x3-x2))+x2;
	  	 b2=(0.8*(y3-y2))+y2;

	  	 a3=(0.8*(x0-x3))+x3;
	  	 b3=(0.8*(y0-y3))+y3;


	  	 drawline(a0,b0,a1,b1,color);
	  	 delay(10);
	  	 drawline(a1,b1,a2,b2,color);
	  	 delay(10);
	  	 drawline(a2,b2,a3,b3,color);
	  	 delay(10);
	  	 drawline(a3,b3,a0,b0,color);


	  	 x0=a0;
	  	 x1=a1;
	  	 x2=a2;
	  	 x3=a3;
	  	 y0=b0;
	  	 y1=b1;
	  	 y2=b2;
	  	 y3=b3;
	}


}

int random_between(int min, int max) {
    return rand() % (max - min + 1) + min;
}


int main (void)
{


	uint32_t i, portnum = PORT_NUM;
  portnum = 1 ; /* For LCD use 1 */
  /* SystemClockUpdate() updates the SystemFrequency variable */

   if ( portnum == 0 )
    SSP0Init();            /* initialize SSP port */
  else if ( portnum == 1 )
    SSP1Init();
  for ( i = 0; i < SSP_BUFSIZE; i++ )
  {
    src_addr[i] = (uint8_t)i;
    dest_addr[i] = 0;
  }

  	lcd_init();


  	int16_t x;
  	int16_t y;




	drawline(30,50,40,50,BLACK);




  return 0;
}


