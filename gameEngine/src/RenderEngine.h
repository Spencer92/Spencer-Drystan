#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#define START_OF_RENDER_AREA 0
#define SCORE_AREA_OFFSET 0
#define SCREEN_SIZE 0x8000L

#include "types.h"


void plotPixel(char *fbstart, int x, int y);

void plotHorzLine(char *fbstart, int xstart, int ystart, int xfin);

void plotVertLine(char *fbstart, int xstart, int ystart, int yfin);

void plotArbLine(char *fbstart, int xstart, int ystart, int xfin, int yfin);

void plotSprite(char *fbstart, UINT8 *spriteLocation, int xpostoPlot,
		int ypostoPlot, int size);

void copyBackground(char *fbstart, UINT8 *spriteLocation, int xpostoPlot,
		int ypostoPlot, int size);

void printvertical(unsigned char* base, unsigned int x_loc, unsigned int y_loc,
		unsigned int length);

void printArbitrary(unsigned char* base, unsigned int x_loc_start,
		unsigned int y_loc_start, unsigned int x_loc_end,
		unsigned int y_loc_end);

void plotLargeSprite(char *fbstart, UINT32 *spriteLocationint, int xpostoPlot,
		int ypostoPlot,int size);


void plotString(char *fbstart, char *theString,int xpos,int ypos);

void copyBackground(char *fbstart, UINT32 *backgroundLocation, int xpostoPlot,int ypostoPlot, int size);

void plotBackground(char *fbstart,UINT32 *background,int xpos, int ypos ,int size);

typedef struct Screen {

	UINT32 *startOfSrcreen;

	UINT32 *displayArea;

} Screen;


typedef struct ScoreBox
{

  UINT16 const xpos;
  UINT16 const ypos;
  UINT16 const width;
  UINT16 const hight;
	
	
} ScoreBox;



#endif /* RENDERENGINE_H*/

