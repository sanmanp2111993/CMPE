/****************************************************************************
 *   
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
#include "longhorn_sunset.h"

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

#include "LPC17xx.h"                        /* LPC17xx definitions */
#include "ssp.h"
#include <stdlib.h>
#include <stdio.h>

/* Be careful with the port number and location number, because
some of the location may not exist in that port. */
#define PORT_NUM            1
#define LOCATION_NUM        0

#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

uint8_t src_addr[SSP_BUFSIZE];
uint8_t dest_addr[SSP_BUFSIZE];
int colstart = 0;
int rowstart = 0;

/*****************************************************************************
** Function name:        LoopbackTest
**
** Descriptions:        Loopback test
**
** parameters:            None
** Returned value:        None
**
*****************************************************************************/

//LCD
#define ST7735_TFTWIDTH  127
#define ST7735_TFTHEIGHT 159
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define swap(x, y) { x = x + y; y = x - y; x = x - y; }
//Colours
#define GREEN 0x00FF00
#define BLACK  0x000000
#define RED  0xFF0000
#define BLUE  0x0000FF
#define WHITE  0xFFFFFF
#define YELLOW 0xFFFF00
#define PINK 0xFFC0CB
#define ORANGE 0xFFA500
#define PURPLE 0xCC99FF
//Axes
int _height = ST7735_TFTHEIGHT;
int _width = ST7735_TFTWIDTH;
int cursor_x = 0, cursor_y = 0;
//uint16_t textcolor = RED, textbgcolor= GREEN;
//float textsize = 2;
//int wrap = 1;

/*********************************************************/
//Setting coordinates here
//defining colours
  uint32_t colours[12] = {ORANGE, BLUE, GREEN, YELLOW, PURPLE, RED, ORANGE, GREEN, BLUE, YELLOW, PINK};

  //defining coordinates for rectangle
  uint8_t c1 = 20, c2 = 30, c3 = 20, c4 = 120, c5 = 120, c6 = 120, c7 = 120, c8 = 30;

  //defining coordinates for triangle
  uint8_t d1 = 10, d2 = 10, d3 = 10, d4 = 120, d5 = 100, d6 = 60;

  //defining coordinates for pentagon
  uint8_t e1 = 10, e2 = 50, e3 = 10, e4 = 130, e5 = 70, e6 = 150, e7 = 120, e8 = 100, e9 = 70, e10 = 30;

  //updated coordinates
  uint8_t n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;

  //3-D coordinates
  /* Origin 0.0.0 = 60.60
   *
   */
  uint8_t q1 = 60, q2 = 60, q3 = 0, q4 = 30, q5 = 30, q6 = 0, q7 = 30, q8 = 70, q9 = 0, q10 = 60, q11 = 100, q12 = 0;
  uint8_t t1 = 30, t2 = 50, t3 = 0, t4 = 30, t5 = 50, t6 = 0;
  uint8_t level = 3;



/******************************************************/
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
//write colour
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

void fillrect(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint32_t color)
{
    //int16_t i;
    int16_t width, height;
    width = x1-x0+1;
    height = y1-y0+1;
    setAddrWindow(x0,y0,x1,y1);
    writecommand(ST7735_RAMWR);
    write888(color,width*height);
}

void lcddelay(int ms)
{
    int count = 24000;
    int i;
    for (i = count*ms; i>0; i--);
}


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
    /* Notice the hack, for portnum 0 p0.16 is used */
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

    lcddelay(500);                        /*delay 500 ms */
    LPC_GPIO0->FIOCLR |= (0x1<<22);
    lcddelay(500);                        /* delay 500 ms */
    LPC_GPIO0->FIOSET |= (0x1<<22);
    lcddelay(500);                        /* delay 500 ms */
     for ( i = 0; i < SSP_BUFSIZE; i++ )    /* Init RD and WR buffer */
        {
            src_addr[i] = 0;
            dest_addr[i] = 0;
        }

     /* do we need Sw reset (cmd 0x01) ? */

     /* Sleep out */
     SSP_SSELToggle( portnum, 0 );
     src_addr[0] = 0x11;    /* Sleep out */
     SSPSend( portnum, (uint8_t *)src_addr, 1 );
     SSP_SSELToggle( portnum, 1 );

     lcddelay(200);
    /* delay 200 ms */
    /* Disp on */
     SSP_SSELToggle( portnum, 0 );
     src_addr[0] = 0x29;    /* Disp On */
     SSPSend( portnum, (uint8_t *)src_addr, 1 );
     SSP_SSELToggle( portnum, 1 );
    /* delay 200 ms */
     lcddelay(200);
}


void drawline(int16_t x0, int16_t y0, int16_t x1, int16_t y1,uint32_t color) {
	int16_t slope = abs(y1 - y0) > abs(x1 - x0);
	if (slope) {
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

void drawrectangle(c1, c2, c3, c4, c5, c6, c7, c8, c9)
{
	drawline(c1,c2,c3,c4,c9);
	//lcddelay(200);
	drawline(c3,c4,c5,c6,c9);
	//lcddelay(200);
	drawline(c7,c8,c5,c6,c9);
	//lcddelay(200);
	drawline(c1,c2,c7,c8,c9);
	lcddelay(20);
}

/* 3D axes position in 2D plane
 * origin is at (60,60)
 * Y axis till 159
 * Z-axis till 127
 * X-axis from 0,0 to 60,60
 */
void draw_3d_axes(void)
{
	drawline(0,0,60,60,GREEN);	//X-axis
	drawline(60,60,127,60,BLUE); //Z-axis
	drawline(60,60,60,159,RED); //Y-axis
}

void draw_3d_cube(q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12)
{
		drawline(q4+q6, q5, q1+q3, q2, WHITE);
		drawline(q4+q6, q5, q7+q9, q8, WHITE);
		drawline(q7+q9, q8, q10+q12, q11, WHITE);
		drawline(q1+q3, q2, q10+q12, q11, WHITE);
		int i=0;
		for(i=0;i<40;i++)
		{
			drawline(q4+i, q5, q1+i, q2, WHITE);
			drawline(q4+i, q5, q7+i, q8, BLUE);
			drawline(q7+i, q8, q10+i, q11, ORANGE);
			drawline(q1+i, q2, q10+i, q11, WHITE);

		}
}




void trees(t1, t2, t3, t4, t5, t6, level)
{
	int i=0;
	for(i=0;i<10;i++)
		{
			drawline(t1+i, t2, t4+i, t5, WHITE);
		}
	//float X = ((t1+i)*0.71) - (t2*0.71);
	//float Y = ((t1+i)*-0.71)-(t2*0.71);
	//trees(X,t2,t3,Y,t5,t6,level--);
}

void cube(void)
{
	draw_3d_cube(q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12);
	trees(t1, t2, t3, t4, t5, t6, level);
}

/******************************************************************************
**   Main Function  main()
******************************************************************************/
int main (void)
{
  //EINTInit();
  uint32_t i, portnum = PORT_NUM;
  portnum = 1 ; /* For LCD use 1 */
  /* SystemClockUpdate() updates the SystemFrequency variable */
//  SystemClockUpdate();
  if ( portnum == 0 )
    SSP0Init();            /* initialize SSP port */
  else if ( portnum == 1 )
    SSP1Init();
  for ( i = 0; i < SSP_BUFSIZE; i++ )
  {
    src_addr[i] = (uint8_t)i;
    dest_addr[i] = 0;
  }

  //initialize LCD
  	lcd_init();
  	fillrect(0, 0, ST7735_TFTWIDTH, ST7735_TFTHEIGHT, BLACK);

  //creating axes and plotting the cube
  	draw_3d_axes();
  	cube();

  //drawing trees and triangles


  	return 0;
}


/******************************************************************************
**                            End Of File
******************************************************************************/
