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

















