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

void plotPixel(char *fbstart, int x, int y);
void plotHorzLine( char *fbstart, int xstart, int ystart, int xfin);
void plotVertLine( char *fbstart, int xstart, int ystart, int yfin);
void plotArbLine(char *fbstart, int xstart, int ystart, int xfin, int yfin);
void plotSprite( char *fbstart, int xpos, int ypos);


#endif /* RASTER_H_ */
