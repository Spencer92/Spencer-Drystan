#ifndef RENDERE_H
#define RENDERE_H

#define START_OF_RENDER_AREA 0
#define SCORE_AREA_OFFSET 0
#define RESULUTION_ADDRESS 0xff8260
#define SCREEN_MEM_HIGH 0xff8201
#define SCREEN_MEM_LOW  0xff8203
#define SCREEN_SIZE     0x7D00L

/*Define screen dimensions  */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define POSTIVE_X_LIMIT 664
#define NEGTIVE_X_LIMIT -24
#define POSTIVE_Y_LIMIT 424
#define NEGTIVE_Y_LIMIT -24
#define FONT_SIZE 15
#define COPY_MASK 0x00000000


#include "Fonts.h"
#include "types.h"
#include <tos.h>


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

void plotLargeSprite(char *fbstart, UINT32 *spriteLocation , int xpostoPlot,
					int ypostoPlot,int size);


void plotString(char *fbstart, char *theString,int length, int xpos,int ypos);

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


void setScreen(char *newScreen, char *oldScreen);

BOOL findRez();
	

#endif 

