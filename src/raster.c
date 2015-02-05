/*
 ============================================================================
 Name        : raster.c
 Author      : Drystan Mazur & Spencer Manser
 Version     : 1
 Copyright   : Released under GPL v3
 Description : Raster library for Atarti St, ANSI-style C89
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <raster.h>



/*Define screen dimensions  */

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define BUFFER_SIZE   0x8100L /*Screen buffer needed 32KB plus space to align */
#define CON 2


void plotPixel(char *fbstart, int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {

		*(fbstart + (y * 80) + (x >> 3)) |= 1 << 7 - (x & 7);

	}


}



void plotHorzLine(char *fbstart, int xstart, int ystart, int xfin)
{
	int length = xfin - xstart;
	int bytelen = length >> 3;
	int startingByte = xstart >> 3;
	int remaining;
	int intialShift = 8 -(xstart & 7);
	int i;

	char *tmpPtr;

	tmpPtr = fbstart;

	if ((xstart >= 0 && xstart + length < SCREEN_WIDTH) && (ystart >= 0 && ystart < SCREEN_HEIGHT))
	{

		tmpPtr += (ystart*80); /*line start offset */

		*(tmpPtr += ((startingByte)* 8)) |= ( ( 2<< (intialShift) ) - 1);

		if(length > 8)
		{

			tmpPtr += ((xstart & 7) + 1);

			remaining = length -((startingByte + 1)* 8);


					for(i = 0; i < bytelen; i++)
					{

						*(tmpPtr )|= 0xff;
						 tmpPtr += (8);
						 remaining -= 8;


					}

					if(remaining != 0)
					{
						*(tmpPtr)|= (2 << (8 - remaining));

					}

		}
		}
}

		void plotVertLine(char *fbstart, int xstart, int ystart, int yfin){}
		void plotArbLine(char *fbstart, int xstart, int ystart, int xfin, int yfin){}
		void plotSprite( char *fbstart, int xpos, int ypos){}


