/*
 ============================================================================
 *Title       : Test library
 *Author      : Drystan Mazur & Spencer Maslen
 *Email       : dmazu602@mtroyal.ca & smasl811@mtroyal.ca
 Due on       : Feb 8th 2015
 *Version     : 1
 *Assignment  : Stage 2
 *Course      : Comp 2659
 *Instructor  : Paul Pospisil
 *Copyright   : Released under GPL v3
 *Description : Raster library for Atarti St, ANSI-style C89
 *Source File : testLib.c
 =============================================================================
 Purpose      : To show a set of basic graphic routines
 =============================================================================
 Method       : By setting two pointers to the Physical base (the current screen)
				And the logical base (the screen that will be switched to) various
				things can be plotted on the screen

 ============================================================================ */

#include "RenderEngine.h"
#include "types.h"
#include "bitmap.h"
#include "AssemblerRoutines.h"
#include <osbind.h>
#include <stdio.h>

#include <stdlib.h>


#define BUFFER_SIZE   0x8100L /*Screen buffer needed 32KB plus space to align */
#define CON 2


void printMenu();
void waitForinput();
void pause();

int main() {


	char selection = '0';
	char *fbstart;	/*The first screen */
	char *fbAltscreen; /* The second screen */
	char *logscreen;


	UINT8 testSprite[8] = { 0xff, 0x18, 0x18, 0xff, 0x18, 0xff, 0x18, 0xff }; /* The sprite that will be used for printsprite */
	
	UINT32  *arrayPtr  = data_Weird_Tank_Player_Two_East_png;

	int i;

	fbstart         = Physbase(); /*The screen the menu will be displayed on*/
	logscreen 		= Logbase(); /*The screen the lines and sprites will be displayed on*/

	fbAltscreen = (char*)Malloc(BUFFER_SIZE); /* There needs to be enough space for the second screen to show up */



	fbAltscreen = (char*) (((UINT32) fbAltscreen + 256)
			               & (UINT32) 0x00FFFF00); /* The screens have to be 256 byte alligned */


	clear(fbAltscreen); /* If there was anything on the second screen, there isn't any more */

	Cursconf(0, 0);


	do {


		printMenu();

		selection = Cnecin(); /* Takes the users input */

		switch (selection) {

		case 'a': /* Plot a pixel to the screen */

			plotPixel(fbAltscreen, 200, 200); /* Put the pixel on the other screen */

			Vsync();

			Setscreen(fbAltscreen, fbAltscreen, -1L); /* Change to the other screen */

			waitForinput();

			Vsync();

			Setscreen(fbstart, fbstart, -1L); /* Go back to the first screen */

			clear(fbAltscreen); /* Clear the other screen */

			break;

		case 'b': /* Plot a horizontal line to the screen */

			plotHorzLine(fbAltscreen, 264, 200, 280); /* Put a horizontal line on the screen */

			Vsync();

			Setscreen(fbAltscreen, fbAltscreen, -1L); /* Change to the other screen */

			waitForinput();

			Vsync();

			Setscreen(fbstart, fbstart, -1L); /* Go back to the first screen */

			clear(fbAltscreen); /* Clear the alternate screen */

			break;

		case 'c': /* Plot a vertical line to the screen */

			plotVertLine(fbAltscreen,270,200,300); /* Put a vertical line on the screen */

			Vsync();

			Setscreen(fbAltscreen, fbAltscreen, -1L); /* Change to the other screen */

			waitForinput();

			Setscreen(fbstart, fbstart, -1L); /* Go back to the first screen */

			clear(fbAltscreen); /* Clear the althernate screen */


			break;

		case 'd': /* Plot multiple sprites a sprite to the screen */

			/* Put a multitude of sprites on the alternate screen */

/*
			plotLargeSprite(fbAltscreen, arrayPtr, 100, 100, 32);

			plotLargeSprite(fbAltscreen, arrayPtr, 130, 120, 32);

			plotLargeSprite(fbAltscreen, arrayPtr, 250, 150, 32);

			plotLargeSprite(fbAltscreen, arrayPtr, 250, 400, 32);

			plotLargeSprite(fbAltscreen, arrayPtr, 250, 0, 32);*/

			plotLargeSprite(fbAltscreen, arrayPtr, 0, 200, 32);


			Vsync();

			/*Go to that screen */
			Setscreen(fbAltscreen, fbAltscreen, -1L);

			pause();

			Vsync();

			/*Go back to the first screen */
			Setscreen(fbstart, fbstart, -1L);

			clear(fbAltscreen); /* Clear the alternate screen */

			break;

		case 'e': /* Animation demo */

			
	
			plotSprite(fbAltscreen, arrayPtr, 271, 200, 8);

			Setscreen(fbAltscreen, fbAltscreen, -1L);
			clear(fbstart);

			Vsync();
		
			for (i = 0; i < 5; i++) {

				clear(fbAltscreen);

				plotSprite(fbstart, arrayPtr, 272 + i, 200 + i, 8);

				Vsync();

				Setscreen(fbstart, fbstart, -1L);

				clear(fbAltscreen);
				
				
				plotSprite(fbAltscreen, arrayPtr, 273 + i, 201 + i, 8);
				Vsync();
				
				Setscreen(fbAltscreen, fbAltscreen, -1L);
				clear(fbstart);
				Vsync();

			}
				
			Setscreen(fbstart, fbstart, -1L);
			clear(fbAltscreen);
			
			break;

		case 'f': /* Plot arbitrary line */


			plotArbLine(fbAltscreen, 200, 200, 230, 300); /* Put the line on the alternate screen */


			Vsync();

			Setscreen(-1L, fbAltscreen, -1L); /* Go to the alternate screen */

			waitForinput();

			Vsync();

			Setscreen(fbstart, fbstart, -1L); /* Go back to the first screen */

			clear(fbAltscreen); /* Clear the alternate screen */


			break;



		case 'q':
			break;

		default:
			Cconws("\r\n\0");
			Cconws("Wrong key press \n");


			break;
		}
	} while (selection != 'q');

	Mfree(fbAltscreen);

	return 0;
}




/*
 =============================================================================
 * 
 * Function Name    : printMenu
 * 
 * Purpose          : To show the menu to the user
 * 
 *  
 =============================================================================*/

 

 

void printMenu() {

	 Cconws("\r\n\0");
	 Cconws("Please select a routine \r\n\0");
	 Cconws("Select a for pixel plot \r\n\0");
	 Cconws("Select b for horizontal line \r\n\0");
	 Cconws("Select c for vertical line \r\n\0");
	 Cconws("Select d for a sprite \r\n\0");
	 Cconws("Select e for a simple animation demo\r\n\0");
	 Cconws("Select f for random line\r\n\0");
	 Cconws("Select q for quit\r\n\0");

}



/*
 =============================================================================
 * 
 * Function Name    : waitForinput
 * 
 * Purpose          : To show what is happening on the screen without it changing back too fast
 *                    to see the changes
 * 
 * Method			: By waiting for input, the user can check to see whats on the screen
 * 
 *
 * 
 =============================================================================*/

void waitForinput() {

	int i;

	for(i = 0;i < 35000;i++)
	{

	}



}
