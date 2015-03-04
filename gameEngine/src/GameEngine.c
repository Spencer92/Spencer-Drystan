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
#include <tos.h>
/*#include <osbind.h>*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
/*===================================================*/
/*Header files authored by Others*/
#include "font.h"
#include "types.h"
#include "bitmaps.h"
/*===================================================*/
/*Header files authored by Spencer Maslen or Drystan Mazur*/

#include  "model.h"
#include  "RenderEngine.h"
#include  "AssemblerRoutines.h"
#include  "tankimage.h"
#include  "bitmap.h"

/*===================================================*/
#define  NUMBER_OFLIVES 3
#define  PLAYER_HITPOINTS 50
#define  ENEMY_HITPOINTS 5
#define  NUMBER_OFENEMYTANKS 5
#define  NUMBER_TILES 1
#define  MAXSPEED  5
#define  BUFFER_SIZE   0x8100L
#define  SCREEN_WIDTH 640
#define  SCREEN_HEIGHT 400

void gameReset();
void pauseAndchill(int duration);

int main() {

	

	char keypress = 0;

	UINT16 playerScore = 0;
	UINT8 i = 0;

	char *mainScreen;
	char *logMainscreen;
	char *gameScreen;
	char *backGamescreen;
	
	
	long readfile;
	int  handle;

	Tank demoArray[6] = { };

	demoArray[0] = Tank
			playerTank = {20, 50, PLAYER_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL, NULL, 1, 0, TRUE};
	demoArray[0].sprite = playerSprite;

	demoArray[1] = Tank
			enemyTank = {600, 10, ENEMY_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,NULL, -1, 0, TRUE};
	demoArray[2] = Tank
			enemyTank2 = {250, 30, ENEMY_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,NULL, -1, 0, TRUE};
	demoArray[3] = Tank
			enemyTank3 = {300, 50, ENEMY_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,NULL, -1, 0, TRUE};
	demoArray[4] = Tank
			enemyTank4 = {400, 70, ENEMY_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,NULL, -1, 0, TRUE};
	demoArray[5] = Tank
			enemyTank5 = {200, 100, ENEMY_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,NULL, -1, 0, TRUE};

	demoArray[1].sprite = enemySprite;
	demoArray[2].sprite = enemySprite;
	demoArray[3].sprite = enemySprite;
	demoArray[4].sprite = enemySprite;
	demoArray[5].sprite = enemySprite;

	Stationary_Object landobjects[6] = { };

	/*=========Will Change in next system=========================*/
	mainScreen = (Physbase());
	logMainscreen = (Logbase());
	backdropScreen = (char*) Malloc(BUFFER_SIZE);
	gameScreen = (char*) Malloc(BUFFER_SIZE);
	gameScreen = (char*) ((UINT32) (gameScreen + 256) & 0x00FFFF00); /* The screens have to be 256 byte aligned */

	backGamescreen = (char*) Malloc(BUFFER_SIZE);
	backGamescreen = (char*) ((UINT32) (gameScreen + 256) & 0x00FFFF00); /* The screens have to be 256 byte aligned */
	backdropScreen = (char*) ((UINT32) (gameScreen + 256) & 0x00FFFF00); /* The screens have to be 256 byte aligned */
	
	clear(gameScreen);
	clear(backGamescreen);
	

	/*===========================================================*/

	/* TODO Initiate game system */

	Cursconf(0, 0); /* removes cursor*/

	/*Setscreen(gameScreen,GameScreen,-1L);*/

	
	readfile = Fopen("tankscreen.pi1",0);
	
	handle = (readfile &= 0x0000FFFF); /*handle is in lower word */
	
	 Fseek(34,handle,0); /*align to data offset in degas file */
	 
	 Fread(handle,FILE_SIZE,backdropScreen); /*load data to mem */
	
	
	readfile = Fopen("grass.pi1",0);
	
	handle = (readfile &= 0x0000FFFF)
	
	 Fseek(34,handle,0); /*align to data offset in degas file */
	 
	 Fread(handle,FILE_SIZE,backGamescreen); /*load data to mem */
	 Fread(handle,FILE_SIZE,gameScreen);
	 
	
	 
	 Vsync();
	 
	 Setscreen(-1L,backdropScreen,-1L);
	
	
	

	while (!Cconis()) {

		if (i == 0) {
			Cconws("\r\n\0");
			
			Cconws("Press space to start or q to quit \r\n\0");
			Cconws("\r\n\0");
		}

		if (!(i >= 1)) {
			i++;
		}

	}

	keypress = Cnecin();

	if (keypress != 'q') {
/*=====================here is main game loop==================*/

		Vsync();
		Setscreen(gameScreen, gameScreen, -1L);

		do {

			/* Reed player input then call Spencer's Behavior method first pass*/

			Vsync();
			Setscreen(backGamescreen, backGamescreen, -1L);

			

		

			Vsync();
			Setscreen(gameScreen, gameScreen, -1L);
			clear(backGamescreen);

	if (keypress == 'p') {
				/*=====================here is pause game loop==================*/
				clear(mainScreen);
				Vsync();
				Setscreen(logMainscreen, mainScreen, -1L);
				
				Cconws("In pause game loop \r\n\0");
				Cconws("Please press any key to start \r\n\0");

				while (!Cconis()) {
				}
				keypress = Cnecin();
			}

			if (Cconis()) {
				keypress = Cnecin();
			}

		} while (keypress != 'q');

	}

	/*TODO clean up*/

	Mfree(gameScreen);
	Mfree(backGamescreen);

	return 0;

}

void pauseAndchill(int duration) {

	
	}

}

void gameReset(){
	
	
	
}
	

