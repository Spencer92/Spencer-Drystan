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
/*===================================================*/
/*Header files authored by Spencer Maslen or Drystan Mazur*/

#include  "model.h"
#include  "Keyboard.h"
#include  "AIsystem.h"
#include  "CollsionDetect.h"
#include  "TileControl.h"
#include  "RenderEngine.h"
#include  "AssemblerRoutines.h"
#include  "tankimage.h"

/*===================================================*/
#define  NUMBER_OFLIVES 3
#define  PLAYER_HITPOINTS 50
#define  ENEMY_HITPOINTS 5
#define  NUMBER_OFENEMYTANKS 5
#define  NUMBER_TILES 1
#define  MAXSPEED  5
#define BUFFER_SIZE   0x8100L
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400

void gameReset();
void pauseAndchill(int duration);

int main() {

	UINT8 playerSprite[8] = { 0xff, 0x18, 0x18, 0xff, 0x18, 0xff, 0x18, 0xff };
	UINT8 enemySprite[8] = { 0xf1, 0xfd, 0xfd, 0x00, 0xff, 0x18, 0xfd, 0xff };

	/* TODO Screen *screenAray[2] = {};*/

	/*playerTank.x_coordinate = 200;*/

	/*Tank enemyTank = { 300,300,ENEMY_HITPOINTS,MAXSPEED,TRUE,FALSE,enemySprite,NULL,-1,0,TRUE};*/
	/*Missile *missiles[2] = { };*/

	char keypress = 0;

	UINT16 playerScore = 0;
	UINT8 i = 0;

	char *mainScreen;
	char *logMainscreen;
	char *gameScreen;
	char *backGamescreen;

	Tank playerTank = { 20, 50, PLAYER_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,
			NULL, 1, 0, TRUE };
	Tank enemyTank = { 600, 10, ENEMY_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,
			NULL, -1, 0, TRUE };

	playerTank.sprite = playerSprite;
	enemyTank.sprite = enemySprite;

	/*=========Will Change in next system=========================*/
	mainScreen = (Physbase());
	logMainscreen = (Logbase());
	gameScreen = (char*) Malloc(BUFFER_SIZE);
	gameScreen = (char*) ((UINT32) (gameScreen + 256) & 0x00FFFF00); /* The screens have to be 256 byte aligned */

	backGamescreen = (char*) Malloc(BUFFER_SIZE);
	backGamescreen = (char*) ((UINT32) (gameScreen + 256) & 0x00FFFF00); /* The screens have to be 256 byte aligned */
	clear(gameScreen);
	clear(backGamescreen);
	/*clear(mainScreen);*/
	/*===========================================================*/

	/* TODO Initiate game system */

	plotSprite(gameScreen, playerTank.sprite, playerTank.x_coordinate,
			playerTank.y_coordinate, 8);
	plotSprite(gameScreen, enemyTank.sprite, enemyTank.x_coordinate,
			enemyTank.y_coordinate, 8);

	/*Setscreen(gameScreen,GameScreen,-1L);*/

	Cconws("\r\n\0");
	Cconws("On first screen \r\n\0");
	Cconws("Please press any key to start \r\n\0");

	while (!Cconis()) {

		if (i == 0) {
			Cconws("\r\n\0");
			Cconws("Display start screen  here\r\n\0");
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
					Cursconf(0,0); /* removes cusors*/
		             Vsync();
		             Vsync();
					Setscreen(gameScreen, gameScreen, -1L);


					do {
						if(!(playerTank.x_coordinate  >= SCREEN_WIDTH ))
						{
							playerTank.x_coordinate += 5;

							enemyTank.x_coordinate -= 5;


						}
						else
						{
							playerTank.x_coordinate = 20;

							enemyTank.x_coordinate  = 600;
						}


						plotSprite(backGamescreen, playerTank.sprite,
								playerTank.x_coordinate, playerTank.y_coordinate, 8);
						plotSprite(backGamescreen, enemyTank.sprite, enemyTank.x_coordinate,
								enemyTank.y_coordinate, 8);

					/*	pauseAndchill(1);*/
						Vsync();
						Vsync();
						Setscreen(backGamescreen, backGamescreen, -1L);
						clear(gameScreen);


						if(!(playerTank.x_coordinate  >= SCREEN_WIDTH ))
						{
							playerTank.x_coordinate += 5;

							enemyTank.x_coordinate -= 5;


						}
						else
						{
							playerTank.x_coordinate = 20;

							enemyTank.x_coordinate  = 600;
						}

						plotSprite(gameScreen, playerTank.sprite, playerTank.x_coordinate,
								playerTank.y_coordinate, 8);
						plotSprite(gameScreen, enemyTank.sprite, enemyTank.x_coordinate,
								enemyTank.y_coordinate, 8);

						Vsync();
						Setscreen(gameScreen, gameScreen, -1L);
						clear(backGamescreen);
						/*pauseAndchill(1);*/



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

						if(Cconis()){
						keypress = Cnecin();}

					} while (keypress != 'q');

	}

	/*TODO clean up*/

	Mfree(gameScreen);
	Mfree(backGamescreen);

	return 0;

}

void pauseAndchill(int duration) {

	duration *= 35;

	while (duration--) {
		Vsync();
	}

}

void gameReset() {
	/*TODO Here we need to reset all variables and game states*/
}
