/*
 ============================================================================
 *Title       : Game Engine
 *Author      : Drystan Mazur & Spencer Maslen
 *Email       : dmazu602@mtroyal.ca & smasl811@mtroyal.ca
 Due on       :
 *Version     : 1
 *Assignment  : Stage 3
 *Course      : Comp 2659
 *Instructor  : Paul Pospisil
 *Copyright   : Released under GPL v3
 *Description : Raster library for Atarti St, ANSI-style C89
 *Source File : GameEngine.c
 =============================================================================
 Purpose      : To demonstrate a working game model
 =============================================================================
 Method       :

 ============================================================================ */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <osbind.h>
#include <tos.h>
/*===================================================*/
/*Header files authored by Others*/

#include "types.h"

/*===================================================*/
/*Header files authored by Spencer Maslen or Drystan Mazur*/

#include  "Behavior.h"
#include  "Model.h"
#include  "RenderE.h"
#include  "AssemblerR.h"
#include  "System.h"
#include  "Fonts.h"
#include  "GameF.h"
#include  "Grass.h"
#include  "GameF.h"
#include  "BackDrop.h"
#include  "Bitmaps.h"

/*===================================================*/
#define  BUFFER_SIZE  0x8400L



void memCopy(char* screenChunk1 ,char* screenChunk2);
void waitForinput();


int main() {

	Tank thePlayer;
	Tank gameArray[NUMBER_OF_TANKS];
	Missile missile[MAX_MISSILES];
	Stationary_Object landobjects[NUM_OBJECTS];
	
	
	BOOL playerInput = 0;
	char keypress = 0;

	UINT16 playerScore = 0;	
	
	UINT8 i = 0;
	UINT8  lives = 0;
	
	char *mainScreen;
	char *logMainscreen;
	
	char *gameScreen;
	char *backGamescreen;
	char *backdropScreen;
	char *currentScreen;
	

	UINT8 screen1[BUFFER_SIZE];
	UINT8 screen2[BUFFER_SIZE];
	UINT8 welcomeScreen[BUFFER_SIZE];



	/*=========Will Change in next system=========================*/
	mainScreen 		= (Physbase());
	logMainscreen 	= (Logbase());
	
	backdropScreen 	= welcomeScreen;
	backdropScreen 	= (char*) ((UINT32) (backdropScreen + 255) & 0xFFFFFF00L); /* The screens have to be 256 byte aligned */
	
	gameScreen = screen1;
	gameScreen = (char*) ((UINT32) (gameScreen + 255) & 0xFFFFFF00L); /* The screens have to be 256 byte aligned */
	
	backGamescreen = screen2;
	backGamescreen = (char*) ((UINT32) (backGamescreen + 255) & 0xFFFFFF00L); /* The screens have to be 256 byte aligned */

	
	Cursconf(0, 0); /* removes cursor*/
	
	if(findRez()) /*If we are in High rez mode*/
	{
	 	
	 memCopy(backdrop, backdropScreen);
	 memCopy(grass,gameScreen);
	 memCopy(gameScreen,backGamescreen);
	
		
	 Vsync();	 
	 Setscreen(-1L,backdropScreen,-1L);
	

	while (!DSconis()) {

		if (i == 0) {
			DSconws("\r\n\0");			
			DSconws("Press space to start or q to quit \r\n\0");
			DSconws("\r\n\0");
		}

		if (!(i >= 1)) {
			i++;
		}

	}

	keypress = DSnecin();

	if (keypress != 'q') {


		
		gameStart(gameArray, &thePlayer, missile,NUMBER_OF_TANKS, &playerScore);
		
		/*copyBackground(gameScreen, thePlayer.backMask, thePlayer.x_coordinate,thePlayer.y_coordinate, SPRITE_SIZE);*/
		
		plotLargeSprite(gameScreen, thePlayer.sprite, thePlayer.x_coordinate, thePlayer.y_coordinate, SPRITE_SIZE);
		
		currentScreen = gameScreen;
		
		for(i = 0; i < NUMBER_OF_TANKS; i++)
		{
			/*copyBackground(gameScreen, gameArray[i].backMask, gameArray[i].x_coordinate,gameArray[i].y_coordinate, SPRITE_SIZE);*/
			plotLargeSprite(gameScreen, gameArray[i].sprite ,gameArray[i].x_coordinate,gameArray[i].y_coordinate,SPRITE_SIZE);
		}
	

		Vsync();
		Setscreen(-1L, currentScreen, -1L);

			
	/*=====================here is main game loop==================*/	
		
		do {

			
			if(DSconis())
			{
				keypress = DSnecin();
				playerInput = 1;
				
				if (keypress == 'p') 
				{
		/*=====================here is the pause game loop==================*/
			
				
				Vsync();
				
				Setscreen(logMainscreen, mainScreen, -1L);
				
				Cconws("In pause game loop \r\n\0");
				Cconws("Please press any key to start \r\n\0");

				while (!DSconis()) {
				}
				keypress = DSnecin();
				}
		/*=====================here is the end of pause game loop==================*/	
			
				else
				{
				
					/*Spencer's model works on the players movement and we plot the player's movement */
									
					/*plotBackground(char *fbstart,UINT32 *background,int xpos, int ypos ,int size) wipe over the old backgnd*/
					
					/*copyBackground(gameScreen, thePlayer.backMask, thePlayer.x_coordinate,thePlayer.y_coordinate, SPRITE_SIZE);*/
					
					
					
					/*plotLargeSprite(gameScreen, thePlayer.sprite, thePlayer.x_coordinate, thePlayer.y_coordinate, SPRITE_SIZE); plot the player on the back  screen*/
					
					
				
				}
			
			}
			else
			{
				playerInput = 0;
			
			
			
			}
			
			
			
			
			/*model(&thePlayer,gameArray,missile, landobjects, 			
				NUMBER_OF_TANKS,MAX_MISSILES, NUM_OBJECTS
				  ,keypress,playerInput);
			
				

			for(i = 0; i < NUMBER_OF_TANKS; i++) 
			{
				copyBackground(gameScreen, gameArray[i].backMask, gameArray[i].x_coordinate,gameArray[i].y_coordinate, SPRITE_SIZE);
				plotLargeSprite(gameScreen, gameArray[i].sprite, gameArray[i].x_coordinate, gameArray[i].y_coordinate, SPRITE_SIZE);


			}*/
			
			if(lives > 0)
			{
			Vsync();
			Setscreen(-1L, currentScreen, -1L);
			}
			
			
			else
			{
			
				/*ask player if he/she would wish to play again*/
				if(keypress == 'y')
				{
				gameStart(gameArray, &thePlayer, missile,NUMBER_OF_TANKS, &playerScore);
				
				memCopy(grass,gameScreen);
	 			memCopy(gameScreen,backGamescreen);
					
				copyBackground(gameScreen, thePlayer.backMask, thePlayer.x_coordinate,thePlayer.y_coordinate, SPRITE_SIZE);
		
				plotLargeSprite(gameScreen, thePlayer.sprite, thePlayer.x_coordinate, thePlayer.y_coordinate, SPRITE_SIZE);
		
				currentScreen = gameScreen;
		
				for(i = 0; i < NUMBER_OF_TANKS; i++)
				{
			    copyBackground(gameScreen, gameArray[i].backMask, gameArray[i].x_coordinate,gameArray[i].y_coordinate, SPRITE_SIZE);
				plotLargeSprite(gameScreen, gameArray[i].sprite ,gameArray[i].x_coordinate,gameArray[i].y_coordinate,SPRITE_SIZE);
				}
				
				Vsync();
		        Setscreen(-1L, currentScreen, -1L);
				
				
				
				}
				
				
				else
				{
				keypress = 'q'; /*Clean up and we are done*/
				
				
				}

			
			}
			
		
		
		
		} while (keypress != 'q');

	}

	}
	
	else
	{
	
		Cconws("Error in screen rezulution");
	
	}

	
	Vsync();
	Setscreen(mainScreen ,mainScreen ,-1L);

	return 0;

}


	
void memCopy(char* screenChunk1 ,char* screenChunk2)
{
	register UINT32  copySize;
	register UINT32 *srcPtr =  (UINT32*) screenChunk1;
	register UINT32 *dstPtr =  (UINT32*) screenChunk2;
	register UINT32 i;
	
	copySize = SCREEN_SIZE >> 2;
		
	
	for(i = 0 ;i < copySize;i++)
	{
	
		*dstPtr = *srcPtr;
		 dstPtr++;
		 srcPtr++;
			
		
	}	
	
	
}

void waitForinput() {

	UINT32 i;

	for(i = 0;i < 100000;i++)
	{

	}
}