#include "raster.h"
#include <stdio.h>
/*#include <stdint.h>*/
/*#include <tos.h>*/
#include <types.h>
#include <stdlib.h>
#include "osbind.h"

#define BUFFER_SIZE   0x8100L /*Screen buffer needed 32KB plus space to align */
#define CON 2
#define SCREEN_SIZE_CLEAR 0x8000
#define CLEAR 0x00000000

void printMenu();
void clearScreen(char *fbstart);
void waitForinput();

int main(int argc, char **argv) {
	char selection = '0';
	long block;
	char *fbstart;
	char *fbAltscreen;
	char *logscreen;
	char output[] = { "Please any key" };
	char crlf[] = { 13, 10, 0 };

	UINT8 testSprite[8] = { 0xff, 0x18, 0x18, 0xff, 0x18, 0xff, 0x18, 0xff };
	UINT8 *arrayPtr;

	int i;


	fbstart = Physbase();
	logscreen = Logbase();

	block = Malloc(BUFFER_SIZE);
	fbAltscreen = (block + 256) & 0x00FFFF00;
	arrayPtr = &testSprite[0];
	
	
	/*fbAltscreen = (void*) (((unsigned int*) fbAltscreen + 256)
			& (unsigned int*) 0x00FFFF00);*/

	clearScreen(fbAltscreen);

/*
	printf("%d",&fbAltscreen);
	printf("\n")
	printf("%d",&fbstart);
*/
	do {

		Bconout(CON,27);

		printMenu();

		selection = Cnecin();

		switch (selection) {

		case 'a':

			plotPixel(fbAltscreen, 200, 200);

			Vsync();

			Setscreen(fbAltscreen, fbAltscreen, -1L);

			waitForinput();

			Vsync();

			Setscreen(fbstart, fbstart, -1L);

			clearScreen(fbAltscreen);

			break;

		case 'b':

			plotHorzLine(fbAltscreen, 264, 200, 280);

			Vsync();

			Setscreen(fbAltscreen, fbAltscreen, -1L);

			waitForinput();

			Vsync();

			Setscreen(fbstart, fbstart, -1L);

			clearScreen(fbAltscreen);

			break;

		case 'c':
			break;

		case 'd':

			plotSprite(fbAltscreen, arrayPtr, 271, 200, 8);

			plotSprite(fbAltscreen, arrayPtr, 272, 240, 8);

			plotSprite(fbAltscreen, arrayPtr, 273, 220, 8);

			plotSprite(fbAltscreen, arrayPtr, 274, 260, 8);

			Vsync();

			Setscreen(fbAltscreen, fbAltscreen, -1L);

			waitForinput();

			/*clearScreen(fbstart);*/

			Vsync();

			Setscreen(fbstart, fbstart, -1L);

			clearScreen(fbAltscreen);

			break;

		case 'e':

			plotSprite(fbAltscreen, arrayPtr, 271, 200, 8);

			Setscreen(fbAltscreen, fbAltscreen, -1L);

			for (i = 0; i < 5; i++) {

				clearScreen(fbstart);

				plotSprite(fbstart, arrayPtr, 272 + i, 200 + i, 8);

				Vsync();

				Setscreen(fbstart, fbstart, -1L);

				clearScreen(fbAltscreen);

				plotSprite(fbAltscreen, arrayPtr, 273 + i, 201 + i, 8);

				Setscreen(fbAltscreen, fbAltscreen, -1L);

			}



			break;

		case 'q':

			break;

		default:
			printf("\n Wrong key press \n");
			break;
		}
	} while (selection != 'q');

	Mfree(fbAltscreen);

	return 0;
}

void printMenu() {

	printf("\n");
	printf("Please select a routine \n");
	printf("Select a for pixel plot \n");
	printf("Select b for horiztal line \n");
	printf("Select c for vertical line \n");
	printf("Select d for a sprite \n");
	printf("Select e for giggles \n");
	printf("Select f for font demo \n");
	printf("Select q for quit");
	printf("\n \n");

}

void clearScreen(char *fbstart) {

	char *tmpPtr = fbstart;

	int i;

	for (i = 0; i < SCREEN_SIZE_CLEAR; i++) {
		tmpPtr[i] = 0;
	}

}

void waitForinput() {

	while (!Cconis()) {

	}

	Cnecin();

}
