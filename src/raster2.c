#include "raster.h"
#include <stdio.h>
#include <stdlib.h>
#include <osbind.h>



void printvertical(unsigned char* base, unsigned int x_loc, unsigned int y_loc,
					unsigned int length)
{
	unsigned int counter;
		FILE* file;
	
	file = fopen("output.txt", "w+");
	
	for(counter = 0; counter < length; counter++)
	{
		fprintf(file, "Printing at %u\n", y_loc);
		plotPixel(base, x_loc, y_loc);
		y_loc++;
	}
	
	fclose(file);
	
}



void printArbitrary(unsigned char* base, unsigned int x_loc_start,
					unsigned int y_loc_start, unsigned int x_loc_end,
					unsigned int y_loc_end)
{
	unsigned int x_length = x_loc_start;
	unsigned int y_length = y_loc_start;
	unsigned int ratio;
	register unsigned int x_traverse;
	register unsigned int y_traverse;
	
	if((y_loc_end-y_loc_start) > (x_loc_end-x_loc_start))
	{
		ratio = (y_loc_end-y_loc_start) / (x_loc_end-x_loc_start);

		for(; y_length < y_loc_end && x_length < x_loc_end; y_length++)
		{
			plotPixel(base, x_length, y_length);
			if(y_length % ratio == 0)
			{
				x_length++;
			}

		}
		
	}
	else
	{
		ratio = (x_loc_end-x_loc_start) / (y_loc_end-y_loc_start);
	
		for(; x_length < x_loc_end && y_length < y_loc_end; x_length++)
		{
			plotPixel(base, x_length, y_length);
			if(x_length % ratio == 0)
			{
				y_length++;
			}

		}
		
	}
	/*printf("x is %u\n", x_length);
	printf("ratio is %u\n", ratio);
	printf("\n");*/
}

unsigned int GCD(unsigned int var_1, unsigned int var_2)
{
	unsigned int gcd;
	unsigned int multiple;
	unsigned int remainder;
	
	
	
}


void swap(unsigned int* var_1, unsigned int* var_2)
{
	*var_1 ^= *var_2;
	*var_2 ^= *var_1;
	*var_1 ^= *var_2;
}










