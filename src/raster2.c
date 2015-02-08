#include "raster.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <osbind.h>

void printvertical(unsigned char* base, unsigned int x_loc, unsigned int y_loc,
		unsigned int length) {
	unsigned int counter;

	for (counter = 0; counter < length; counter++) {
		plotPixel(base, x_loc, y_loc);
		y_loc++;
	}

}

void printArbitrary(unsigned char* base, unsigned int x_loc_start,
					unsigned int y_loc_start, unsigned int x_loc_end,
					unsigned int y_loc_end) {

	register unsigned int x_length = x_loc_start;
	register unsigned int y_length = y_loc_start;
	register unsigned int ratio;

	if ((y_loc_end - y_loc_start) > (x_loc_end - x_loc_start) && (x_loc_end - x_loc_start > 0)) {
		ratio = (y_loc_end - y_loc_start) / (x_loc_end - x_loc_start);

		for (; y_length < y_loc_end && x_length < x_loc_end; y_length++) {
			plotPixel(base, x_length, y_length);

			if (y_length % ratio == 0) {
				x_length++;
			}

		}

	} 
	else if((x_loc_end - x_loc_start) > (y_loc_end-y_loc_start) &&(y_loc_end - y_loc_start) > 0)
	{
		ratio = (x_loc_end - x_loc_start) / (y_loc_end - y_loc_start);

		for (; x_length < x_loc_end && y_length < y_loc_end; x_length++) {
			plotPixel(base, x_length, y_length);
			if (x_length % ratio == 0) {
				y_length++;
			}

		}

	}
	else if((y_loc_end - y_loc_start <= 0))
	{
		plotHorzLine((char*)base, x_loc_start, y_loc_start, x_loc_end);
	}
	else if((x_loc_end - x_loc_start) <= 0)
	{
		printvertical(base, x_loc_start, y_loc_start, y_length);
	}
	/*printf("x is %u\n", x_length);
	 printf("ratio is %u\n", ratio);
	 printf("\n");*/
}

void plotSprite(char *fbstart, UINT8 *spriteLocation, int xpostoPlot,
		int ypostoPlot, int size) {
	char* destPtr = fbstart;
	UINT8 *srcPtr = spriteLocation;
	static FILE* output;
	static int opened = 0;
	unsigned int leftBuffershift = 0;
	unsigned int rightBuffershift = 0;
	unsigned int buffer1 = 0;
	unsigned int buffer2 = 0;
	static int pass = 0;
	char* testPtr = destPtr;
	char* testPtr2 = destPtr;
	int guy;
	int screenOffset = (xpostoPlot >> 3);
	int offset = size >> 1;
	int i = 0;
	int postionMod = (xpostoPlot &= 7);

	if(!opened)
	{
		output = fopen("output.txt", "w");
		opened = 1;
	}
	
	/*Sprites at 16 x 16 max */

	/*TODO shift is incorrect for other postions than 271 = x*/

	destPtr += ((ypostoPlot - offset) * 80);
	destPtr += ((xpostoPlot - offset) >> 3);

	
	
	fprintf(output, "pass %i\n", pass);
	fprintf(output, "destPtr before equation %i\n", testPtr);
	fprintf(output, "ypostoPlot - offset = %i\n", ypostoPlot - offset);
	fprintf(output, "(ypostoPlot - offset) * 80 = %i\n", (ypostoPlot - offset) * 80);
	testPtr += (ypostoPlot-offset);
	fprintf(output, "destPtr current 01: %i\n", testPtr);
	testPtr = (testPtr + (ypostoPlot - offset) * 80);
	fprintf(output, "destPtr current 02: %i\n", testPtr);
	fprintf(output, "xpostoPlot - offset = %i\n", xpostoPlot - offset);
	fprintf(output, "(xpostoplot - offset) >> 3 = %i\n", (xpostoPlot - offset) >> 3);
	testPtr += ((xpostoPlot - offset) >> 3);
	fprintf(output, "destPtr current: %i\n", testPtr);
	
	
	fprintf(output, "destPtr is %i\n\0", destPtr );
	fprintf(output, "ypostoPlot is %i\n\0", ypostoPlot);
	fprintf(output, "xpostoPlot is %i\n\0", xpostoPlot);
	fprintf(output, "offset is %i\n\n", offset);
	pass++;

/* 	if(postionMod == 7){

		leftBuffershift = rightBuffershift = 4;

	}

 */
	leftBuffershift = ((xpostoPlot - offset) % 8) + 1;
	/*8 - (7 - (xpostoPlot & 7));*/
	rightBuffershift = 8 - leftBuffershift;

	while (size--) {

		buffer2 = buffer1 = spriteLocation[i];
		
		buffer1 >>= leftBuffershift;
		buffer2 <<= rightBuffershift;

		*destPtr++ = buffer1;
		*destPtr   = buffer2;
		i++;

		destPtr--;
		destPtr += 80;

	}

}

void plotHorzLine(char *fbstart, int xstart, int ystart, int xfin) {
	int length = xfin - xstart;
	int bytelen = length >> 3;
	int startingByte = xstart >> 3;
	int remaining;
	int intialShift = 8 - (xstart & 7);
	int i;

	char *tmpPtr;

	tmpPtr = fbstart;

	if ((xstart >= 0 && xstart + length < SCREEN_WIDTH)
			&& (ystart >= 0 && ystart < SCREEN_HEIGHT)) {

		tmpPtr += (ystart * 80); /*line start offset */

		*(tmpPtr += ((startingByte) * 8)) |= ((2 << (intialShift)) - 1);

		if (length > 8) {

			tmpPtr++;

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

unsigned int GCD(unsigned int var_1, unsigned int var_2) {
	unsigned int gcd;
	unsigned int multiple;
	unsigned int remainder;

}

void swap(unsigned int* var_1, unsigned int* var_2) {
	*var_1 ^= *var_2;
	*var_2 ^= *var_1;
	*var_1 ^= *var_2;
}

