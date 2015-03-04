/*Define screen dimensions  */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

#include "RenderEngine.h"
/*#include "mask.h"*/
#include <stdlib.h>
#include  <stdio.h>

/*
 =============================================================================
 *
 * Function Name    : plotPixel (Note this function was defined in a lecture,
 * 					  we are not the authors of this function)
 *
 * Purpose          :To plot a pixel on the screen
 *
 *
 * Method           :The values are checked against the bounds of the screen.
 * 					 Then a mask is set to the x position, this mask is logically
 * 					 OR'ed with the Frame Buffer.
 *
 *
 * Input Parameters :(x,y) start position .A pointer to the
 * 					 screen buffer memory.
 *
 *
 * Return Value     :A modified screen buffer
 *
 *
 *=============================================================================*/

void plotPixel(char *fbstart, int x, int y) {
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {

		*(fbstart + (y * 80) + (x >> 3)) |= 1 << 7 - (x & 7);

	}

}

/*
 =============================================================================
 *
 * Function Name    : plotHorzLine
 *
 * Purpose          :To plot a horizontal line between two points on the screen
 *
 *
 * Method           :The values are checked against the bounds of the screen.
 * 							  Then a mask is set to the x position, this mask is logically
 * 					          OR'ed with the Frame Buffer byte and moves though line by line
 *
 *
 * Input Parameters :(x,y) start position and x finish position. A pointer to the
 * 					 screen buffer memory.
 *
 *
 * Return Value     :A modified screen buffer
 *
 * Limations		:xfin is always greater than xstart
 *=============================================================================*/

void plotHorzLine(char *fbstart, int xstart, int ystart, int xfin) {

	UINT16 length = xfin - xstart;
	UINT16 bytelen = length >> 3;
	UINT8 startingByte = xstart >> 3;
	UINT16 remaining;
	UINT8 intialShift = 8 - (xstart & 7);
	UINT16 i;

	char *tmpPtr = fbstart;

	if ((xstart >= 0 && xstart + length < SCREEN_WIDTH)
			&& (ystart >= 0 && ystart < SCREEN_HEIGHT)) {

		tmpPtr += (ystart * 80); /*line start offset */

		*(tmpPtr += ((startingByte) * 8)) |= ((2 << (intialShift)) - 1);

		if (length > 8) {

			tmpPtr += ((xstart & 7) + 1);

			remaining = length - ((startingByte + 1) * 8);

			for (i = 0; i < bytelen; i++) {

				*(tmpPtr) |= 0xff;
				tmpPtr++;
				remaining -= 8;

			}

			if (remaining != 0) {
				*(tmpPtr) |= (2 << (8 - remaining));

			}

		}
	}
}
/*
 =============================================================================
 *
 * Function Name    : plotVertLine
 *
 * Purpose          : To plot a vertical line between two points on the screen
 *
 *
 * Method           : The values are checked against the bounds of the screen.
 * 					  Then a mask is set to the x position, this mask is logically
 * 					  OR'ed with the Frame Buffer byte.Then moved though  2 lines
 * 					  at a time
 *
 *
 *
 * Input Parameters :(x,y) start position and y finish position. A pointer to the
 * 					 screen buffer memory.
 *
 *
 * Return Value     : A modified screen buffer
 *
 * Limations		:yfin is always greater than ystart
 =============================================================================*/

void plotVertLine(char *fbstart, int xstart, int ystart, int yfin) {

	UINT16 length = yfin - ystart;
	UINT8 startByte = xstart >> 3;
	UINT8 maskBit = 2 << (7 - (xstart & 7));

	char* tmpPtr = fbstart;

	if ((xstart >= 0 && xstart <= SCREEN_WIDTH)
			&& (ystart >= 0 && ystart + length < SCREEN_HEIGHT)) {

		tmpPtr += (ystart * 80);
		tmpPtr += startByte;

		if (length & 1) {
			*(tmpPtr) |= maskBit;
			tmpPtr += 80;
		}

		length >>= 1;

		while (length--) {

			*(tmpPtr) |= maskBit;
			tmpPtr += 80;
			*(tmpPtr) |= maskBit;
			tmpPtr += 80;

		}

	}

}

/*
 =============================================================================
 *
 * Function Name    : plotArbLine
 *
 * Purpose          : To plot a line with arbitrary parameters
 *
 *
 * Method           : By checking how much the line moves horizontally and
 *					  vertically, a ratio can be determined which shows
 *					  how much the line should move horizontally to
 *					  it moving vertically. Depending on which direction
 * 					  was longer it will move that direction a certain amount
 * 					  of pixels before moving in the other direction one pixel.
 *               	  A pixel will then be plotted on that location.
 *					  If there is no difference in the end result of the horizontal
 *                    or vertical line (ie it starts and ends on the same axis),
 *                    then the appropriate functions will be called to handle those
 *                    cases
 *
 *
 * Input Parameters : char *fbstart - the screen.
 *                    int x_loc_start    - where the horizontal start of the line will be on the screen
 *                    int y_loc_start    - where the vertical start of the line will be on the screen
 *                    int x_loc_end      - where the horizontal end of the line will be on the screen
 *                    int y_loc_end      - where the vertical end of the line will be on the screen
 *
 *
 * Return Value     : An arbitrary line on the screen.
 *
 *
 =============================================================================*/

void plotArbLine(char *fbstart, int x_loc_start, int y_loc_start, int x_loc_end,
		int y_loc_end)

{

	register unsigned int x_length = x_loc_start;
	register unsigned int y_length = y_loc_start;
	register unsigned int ratio;

	if ((y_loc_end - y_loc_start) > (x_loc_end - x_loc_start)
			&& (x_loc_end - x_loc_start > 0)) {
		ratio = (y_loc_end - y_loc_start) / (x_loc_end - x_loc_start);

		for (; y_length < y_loc_end && x_length < x_loc_end; y_length++) {
			plotPixel(fbstart, x_length, y_length);

			if (y_length % ratio == 0) {
				x_length++;
			}
		}
	} else if ((x_loc_end - x_loc_start) > (y_loc_end - y_loc_start)
			&& (y_loc_end - y_loc_start) > 0) {
		ratio = (x_loc_end - x_loc_start) / (y_loc_end - y_loc_start);

		for (; x_length < x_loc_end && y_length < y_loc_end; x_length++) {
			plotPixel(fbstart, x_length, y_length);
			if (x_length % ratio == 0) {
				y_length++;
			}
		}
	}

	else if ((y_loc_end - y_loc_start <= 0)) {
		plotHorzLine((char*) fbstart, x_loc_start, y_loc_start, x_loc_end);
	}

	else if ((x_loc_end - x_loc_start) <= 0) {
		plotVertLine(fbstart, x_loc_start, y_loc_start, y_length);
	}

}

/*=============================================================================
 *
 * Function Name    : plotSprite
 *
 * Purpose          : To plot a bitmapped sprite (small image) to the screen
 *
 *
 * Method           :The screen pointer is shifted to the top of the sprite
 *					 The sprite is aligned by splitting the sprite and shifting,
 *					 left and right as required. Then the two half's are plotted
 *					 on the screen.
 *
 *
 * Input Parameters :(x,y) start position, a pointer to the
 * 					 screen buffer memory, sprite size and a
 * 					 a pointer to the sprite array.
 *
 *
 * Return Value     :A modified screen buffer
 *
 * Limitations      :The sprite must be in 8bit format ie if size is 32x32
 * 					then the array will look like {[part1] [part2] [part3] [part4]},
 * 					for the first line of the sprite. Limited to 8x8 sprites
 * 					and no clipping as of yet.
 *
 *
 =============================================================================*/

void plotSprite(char *fbstart, UINT8 *spriteLocation, int xpostoPlot,
		int ypostoPlot, int size) {

	char *destPtr = fbstart;

	UINT8 *srcPtr = spriteLocation;
	UINT8 leftBuffershift = 0;
	UINT8 rightBuffershift = 0;

	UINT8 buffer1 = 0;
	UINT8 buffer2 = 0;

	UINT8 screenOffset = (xpostoPlot >> 3);
	UINT8 offset = size >> 1;

	int i = 0;

	if ((xpostoPlot - offset >= 0 && xpostoPlot + offset <= SCREEN_WIDTH)
			&& ((ypostoPlot + offset <= SCREEN_HEIGHT)
					&& ypostoPlot - offset >= 0)) {

		destPtr += (ypostoPlot - offset) * 80;
		destPtr += ((xpostoPlot - offset) >> 3);

		leftBuffershift = ((xpostoPlot - offset) & 7) + 1;
		rightBuffershift = 8 - leftBuffershift;

		while (size--) {

			buffer2 = buffer1 = spriteLocation[i];

			buffer1 >>= leftBuffershift;
			buffer2 <<= rightBuffershift;

			*destPtr++ = buffer1;
			*destPtr = buffer2;
			i++;

			destPtr--;
			destPtr += 80;

		}
	}

	return;
}

void plotLargeSprite(char *fbstart, UINT32 *spriteLocation, int xpostoPlot,
		int ypostoPlot, int size) {

	UINT32 *writePtrLH = fbstart;
	UINT32 *writePtrRH = NULL;
	UINT32 bufferleft;
	UINT32 bufferright;

	UINT16 	*trackPtr;
	UINT16	*trackPtrL;
	UINT8 	*trackptrS;

	UINT8 offset = size >> 1;

	UINT16 yposoffset = ypostoPlot + offset;
	UINT16 xposoffset = xpostoPlot + offset;

	int xnegBound = xpostoPlot - offset;
	int startLine = ypostoPlot - offset;
	int flag = 1;

	UINT8 i = 0;
	UINT8 j = 0;

	UINT8 shiftright;
	UINT8 shiftleft;

	/* Y Clipping section====================================*/

	if (startLine < 0) {
		i = (size - (size + startLine)) - 1;

		size = (size + startLine);

		startLine = 0;

	}

	else if ((yposoffset) > SCREEN_HEIGHT) {

		size = size - (yposoffset - SCREEN_HEIGHT);

	}

	writePtrLH += (20 * (startLine));

	/* Y Clipping section done ====================================*/

	/* X Clipping section ====================================*/

	if (xposoffset > SCREEN_WIDTH) {

		flag = 0;
		writePtrLH += 19;

	}

	else if ((xnegBound) < 0) {

		shiftleft = 15 - xpostoPlot;

		if (!(shiftleft > 23) && (shiftleft > 14)) {
			flag = -1;
			shiftleft = shiftleft - 15;
			bufferleft = (UINT16) bufferleft;
			trackPtr = spriteLocation;
			j = 2;
			i = 1;
			trackPtrL = (UINT16*) writePtrLH;
			offset = 40;
		}

		else if (shiftleft >= 23) {
			flag = 0;
			/*shiftleft = (8 - (30 - shiftleft));*/
			shiftleft = 0;
			bufferleft = (UINT8) bufferleft;
			trackptrS =  spriteLocation;
			i = 3;
			j = 4;
			trackPtrL = (UINT8*) writePtrLH;
			offset = 40;

		}

	}

	/* X Clipping section done====================================*/

	if (flag > 0) {

		writePtrLH += ((xpostoPlot - offset) >> 5);
		trackPtr = writePtrLH;
		trackPtr++;
		writePtrRH = trackPtr;

		shiftleft = ((xpostoPlot - offset) & 7);
		shiftright = (8 - shiftleft);

		while (size--) {

			bufferleft = spriteLocation[i];
			bufferright = bufferleft;

			bufferleft >>= shiftleft;
			bufferright <<= shiftright;

			*(writePtrLH) |= bufferleft;

			(bufferright) &= 0x00FFFFFF;
			*(writePtrRH) |= bufferright;

			writePtrLH += 20;
			writePtrRH += 20;

			i++;

		}

	}

	else {

		while (size--) {



			if (flag < 0) {
				bufferleft = trackPtr[i];
				bufferleft <<= shiftleft;
				*(trackPtrL) |= bufferleft;

			}

			else {
				bufferleft = trackptrS[i];
				bufferleft <<= shiftleft;
				*(trackPtrL) |= bufferleft;
			}
			i += j;
			trackPtrL += offset;
		}

	}

	return;
}

void blankSprite(char *fbstart, UINT8 *spriteLocation, int xpostoPlot,
		int ypostoPlot, int size) {
}

