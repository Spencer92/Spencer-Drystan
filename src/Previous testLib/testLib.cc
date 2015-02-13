#include "raster.h"
#include <stdio.h>
/*#include "stdint.h"*/
#include <stdlib.h>
#include <osbind.h>



#define BUFFER_SIZE   0x8100L /*Screen buffer needed 32KB plus space to align */
#define CON 2
#define SCREEN_SIZE_CLEAR 0x8000
#define CLEAR 0x00000000


void printMenu();
void clearScreen(unsigned int *fbstart);
void waitForinput();


/*
int main()
{
	unsigned char* firstScreen;
	unsigned char* secondScreen;

	
	firstScreen = Physbase();
	secondScreen = Logbase();
	
	Setscreen(secondScreen, secondScreen, -1L);
	clearScreen(secondScreen);
	
	
	printvertical(secondScreen, 60, 40,
					10);
	
	
	
	
}
*/





int main(int argc, char **argv) {
	char selection = '0';

	char *fbstart;
	long fbAltscreen;
	long logscreen;
	long screen;
	long realBase;
	unsigned char* realBaseAddr;
	unsigned char* logBaseAddr;
	char output[] = { "Please press space bar" };
	char crlf[] = { 13, 10, 0 };
	unsigned long integral = 0x00FFFF00;
	unsigned long block;
	int guy;
	UINT8 testSprite[8] = { 0xff, 0x18, 0x18, 0xff, 0x18, 0xff, 0x18, 0xff };

	
	block = Malloc(BUFFER_SIZE);
	
	fbAltscreen = (block + 256)&0x00FFFF00;
	

	guy = test();
	realBase = Physbase();
	logscreen = Logbase();
	guy = test();

	(long*) realBaseAddr = realBase;
	(long*) logBaseAddr = logscreen;
	
	Cconws("before anything \r\n\0");
	/*Setscreen(fbAltscreen, -1L, -1L);*/
	
/* 	char keypress, junkChar;
	int i;
	Cconws("before anything \r\n\0");
	fbstart = Physbase();
	logscreen = Logbase();
	Cconws("after screenthing \r\n\0");
 	fbAltscreen = (unsigned char*)malloc(BUFFER_SIZE* sizeof(unsigned int*));
	Cconws("after allowocation \r\n\0");
	
 */	
/* 	*integral &= (
		(unsigned long) ((*fbAltscreen / 256)*256));
	Cconws("checking before making \n\0");
	(unsigned long*) fbAltscreen = integral;
	clearScreen((unsigned int*)fbAltscreen);
	Cconws("before do \n\0");
 */	do {

		/*Bconout(CON,27);*/
		printMenu();
		guy = test();
		Vsync();
		


		selection = Cnecin();

		switch (selection) {



		case 'a':

			
			clearScreen((unsigned int*)logBaseAddr);
			Vsync();
			
			
			
			plotPixel((unsigned char*)logBaseAddr,200, 200);

			Vsync();

			Setscreen(logBaseAddr, logBaseAddr, -1L);
			waitForinput();
			clearScreen((unsigned int*)realBaseAddr);

			Vsync();
			
			Setscreen(realBaseAddr, realBaseAddr, -1L);


			
			Vsync();

			break;

		case 'b':

			clearScreen((unsigned int*)logBaseAddr);
			plotHorzLine((char*)logBaseAddr, 100, 200, 200);

			Vsync();

			Setscreen(logBaseAddr, logBaseAddr, -1L);


			waitForinput();

			Vsync();
			clearScreen((unsigned int*)realBaseAddr);
			Vsync();
			Setscreen(realBaseAddr, realBaseAddr, -1L);



			break;

		case 'c':
			clearScreen((unsigned int*)logBaseAddr);
			printvertical(logBaseAddr, 200, 150, 50);

			Vsync();

			Setscreen(logBaseAddr, logBaseAddr, -1L);


			waitForinput();

			Vsync();
			clearScreen((unsigned int*)realBaseAddr);
			Vsync();
			Setscreen(realBaseAddr, realBaseAddr, -1L);


			break;
			
			case 'd':
		
			clearScreen((unsigned int*)logBaseAddr);
			plotSprite((char*) logBaseAddr, testSprite, 271, 150, 8);
			waitForinput();
			plotSprite((char*) logBaseAddr, testSprite, 272, 200, 8);
			waitForinput();
			plotSprite((char*) logBaseAddr, testSprite, 273, 250, 8);
			waitForinput();
			plotSprite((char*) logBaseAddr, testSprite, 274, 300, 8);
			
			Vsync();

			Setscreen(logBaseAddr, logBaseAddr, -1L);


			waitForinput();

			Vsync();
			clearScreen((unsigned int*)realBaseAddr);
			Vsync();
			Setscreen(realBaseAddr, realBaseAddr, -1L);
			break;
			
		case 'e':
		
			clearScreen((unsigned int*)logBaseAddr);
			
			printArbitrary(logBaseAddr, 10, 50, 100, 200);
			Vsync();


			waitForinput();

			Vsync();
			clearScreen((unsigned int*)realBaseAddr);
			Vsync();
			Setscreen(realBaseAddr, realBaseAddr, -1L);

			break;
/*
		case 'q':

			break;*/
		default:

			break;
		}
	} while (selection != 'q');

	Mfree(fbAltscreen);

	return 0;
}

void printMenu()
{
	Cconws("Please select a routine \r\n\0");
	Cconws("Select a for pixel plot \r\n\0");
	Cconws("Select b for horiztal line \r\n\0");
	Cconws("Select c for vertical line \r\n\0");
	Cconws("Select d for a sprite \r\n\0");
	Cconws("Select e for a arbitrary line\r\n\0");
	Cconws("Select q for quit\r\n\0");
	
	
/*	printf("Please select a routine \n");
	printf("Select a for pixel plot \n");
	printf("Select b for horiztal line \n");
	printf("Select c for vertical line \n");
	printf("Select d for a sprite \n");
	printf("Select e for a arbitrary line\n");
	printf("Select q for quit");
	printf("\n \n");
*/


}



void clearScreen(unsigned int *fbstart)
{

int i;

char *tmpPtr;
	Cconws("In clear screen\r\n\0");
	(unsigned int*)tmpPtr = fbstart;

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

int test() 
{
register int guy = 0;

return guy;

}