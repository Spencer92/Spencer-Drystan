#ifndef RENDERENGINE_H
#define RENDERENGINE_H


#define START_OF_RENDER_AREA 0
#define SCORE_AREA_OFFSET 0
#define SCREEN_SIZE 0x8000


#include "types.h"

const UINT32 leftmask[] = {0x7FFFFFFF,0x3FFFFFFF,0x1FFFFFF,0x0FFFFFF,0x07FFFFFF,0x03FFFFFF,0x01ffffff,0x00ffffff,0x007FFFFF,0x003FFFFF,0x001FFFFF,
                          0x000FFFFF};
const UINT32 rightmask[] = {};


void plotPixel(char *fbstart, int x, int y);

void plotHorzLine(char *fbstart, int xstart, int ystart, int xfin);

void plotVertLine(char *fbstart, int xstart, int ystart, int yfin);

void plotArbLine(char *fbstart, int xstart, int ystart, int xfin, int yfin);

void plotSprite(char *fbstart, UINT8 *spriteLocation, int xpostoPlot, int ypostoPlot, int size );

void blankSprite(char *fbstart,UINT8 *spriteLocation, int xpostoPlot, int ypostoPlot, int size );

void printvertical(unsigned char* base, unsigned int x_loc, unsigned int y_loc,
                   unsigned int length);

void printArbitrary(unsigned char* base, unsigned int x_loc_start,
                    unsigned int y_loc_start, unsigned int x_loc_end,
                    unsigned int y_loc_end);


void plotLargeSprite(char *fbstart,UINT32 *spriteLocationint, int xpostoPlot,int ypostoPlot);


typedef struct Screen
{

	UINT32 *startOfSrcreen;

	UINT32 *displayArea;

} Screen;

#endif /* RENDERENGINE_H*/

