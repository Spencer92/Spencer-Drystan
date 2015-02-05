#include <raster.h>
#include <stdio.h>
#include <stdint.h>
#include <tos.h>



#define BUFFER_SIZE   0x8100L /*Screen buffer needed 32KB plus space to align */
#define CON 2
#define SCREEN_SIZE_CLEAR 0x8000
#define CLEAR 0x00000000

void printMenu();
void clearScreen(char *fbstart);
void waitForinput();


int main(int argc, char **argv) {
	char selection = '0';

	char *fbstart;
	char *fbAltscreen;
	char *logscreen;
	char output[] = { "Please press space bar" };
	char crlf[] = { 13, 10, 0 };

	char keypress, junkChar;
	int i;

	fbstart = Physbase();
	logscreen = Logbase();

	fbAltscreen = Malloc(BUFFER_SIZE);



	fbAltscreen = (void*) (((uintptr_t) fbAltscreen + 256)
			& (uintptr_t) 0x00FFFF00);

	clearScreen(fbAltscreen);

	do {

		Bconout(CON,27);

		printMenu();

		scanf("%c", &selection);

		Cnecin();

		switch (selection) {



		case 'a':



			plotPixel(fbAltscreen,200, 200);

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

			break;

		case 'q':

			break;

		default:

			break;
		}
	} while (selection != 'q');

	Mfree(fbAltscreen);

	return 0;
}

void printMenu()
{

	printf("Please select a routine \n");
	printf("Select a for pixel plot \n");
	printf("Select b for horiztal line \n");
	printf("Select c for vertical line \n");
	printf("Select d for a sprite \n");
	printf("Select q for quit");
	printf("\n \n");



}



void clearScreen(char *fbstart)
{

int i;

char *tmpPtr;

	tmpPtr = fbstart;

for (i = 0; i <SCREEN_SIZE_CLEAR ; ++i) {
		tmpPtr[i] = 0;



}



}

void waitForinput()
{

	while (!Cconis())
				{



				}

	Cnecin();

}



