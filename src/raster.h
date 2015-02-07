/*
 * raster.h
 *
 *  Created on: Feb 2, 2015
 *      Author: Drystan Mazur & Spencer Masen
 *      Project BattleTank stage 2
 *
 *      Overview : Basic graphic Library
 */

#ifndef RASTER_H_
#define RASTER_H_

#ifndef
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#endif


void plotPixel(unsigned char *fbstart, int x, int y);
void plotHorzLine(unsigned int *fbstart, int xstart, int ystart, int xfin);
void plotVertLine(char *fbstart, int xstart, int ystart, int yfin);
void plotArbLine(char *fbstart, int xstart, int ystart, int xfin, int yfin);

void plotSprite(char *fbstart, UINT8 *spriteLocation, int xpostoPlot, int ypostoPlot, int size );

void printvertical(unsigned char* base, unsigned int x_loc, unsigned int y_loc,
		unsigned int length);

void printArbitrary(unsigned char* base, unsigned int x_loc_start,
		unsigned int y_loc_start, unsigned int x_loc_end,
		unsigned int y_loc_end);

#endif /* RASTER_H_ */
