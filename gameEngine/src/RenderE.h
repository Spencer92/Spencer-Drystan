#ifndef RENDERE_H
#define RENDERE_H


#define RESULUTION_ADDRESS 0xff8260
#define SCREEN_MEM_HIGH 0xff8201
#define SCREEN_MEM_LOW  0xff8203
#define SCREEN_SIZE     0x7D00L
#define BLANK 0x0000

#define START_OF_RENDER_AREA 0
#define LIVES_AREA_START 80
#define LIVES_AREA_END 144
#define SCORE_LINE 374
#define SCORE_AREA_START 368
#define SCORE_AREA_FIN   464
#define BLANK_SIZE_LIVES 4
#define MAX_SCORE_SIZE 6
#define SCORE_HEIGHT 18

/*Define screen dimensions  */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 365
#define POSTIVE_X_LIMIT 664
#define NEGTIVE_X_LIMIT -24
#define POSTIVE_Y_LIMIT 424
#define NEGTIVE_Y_LIMIT -24
#define FONT_SIZE 15





#include "Fonts.h"
#include "types.h"
#include <osbind.h>

void blanKscore(char *fbstart);

void plotPixel(char *fbstart, int x, int y);

void plotHorzLine(char *fbstart, int xstart, int ystart, int xfin);

void plotVertLine(char *fbstart, int xstart, int ystart, int yfin);

void plotArbLine(char *fbstart, int xstart, int ystart, int xfin, int yfin);

void plotSprite(char *fbstart, UINT8 *spriteLocation, int xpostoPlot,
		int ypostoPlot, int size);

void printvertical(unsigned char* base, unsigned int x_loc, unsigned int y_loc,
					unsigned int length);

void printArbitrary(unsigned char* base, unsigned int x_loc_start,
					unsigned int y_loc_start, unsigned int x_loc_end,
					unsigned int y_loc_end);

void plotLargeSprite(char *fbstart, UINT32 *spriteLocation , int xpostoPlot,
					int ypostoPlot,int size);


void plotString(char *fbstart, char *theString,int length, int xpos,int ypos);

void plotBackground(char *fbstart, UINT32 *background,int xpos, int ypos ,int size);

extern char scoreString[6];


BOOL findRez();
	
void plotScore(char* fbstart,UINT16 score, int xpos,int ypos,int size);

#endif 

