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
/*#include <tos.h>*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "osbind.h"
/*===================================================*/
/*Header files authored by Others*/
/*#include "fonts.h"*/
#include "types.h"
#include "bitmaps.h"
/*===================================================*/
/*Header files authored by Spencer Maslen or Drystan Mazur*/

#include  "behavior.h"
#include  "model.h"
#include  "rE.h"
#include  "AsRou.h"
#include  "bitmaps.h"
#include  "system.h"

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
#define  MAX_MISSILES 10
#define  FILE_SIZE 0x8000L
#define  NUM_OBJECTS 6

void gameReset();
void pauseAndchill(int duration);
void makeScreen(void* screenChunk1);
void makeGameScreens(long* screenChunk1 ,long* screenChunk2);

int main() {

	BOOL playerInput = 0;
	char keypress = 0;

	UINT16 playerScore = 0;
	UINT8 i = 0;
	Stationary_Object landobjects[6];
	char *mainScreen;
	char *logMainscreen;
	char *gameScreen;
	char *backGamescreen;
	char *backdropScreen;
	
	long readfile;
	int  handle;
	Missile missile[MAX_MISSILES];
	
	
	Tank playerDemo;
	Tank demoArray[5];

	for(i = 0; i < MAX_MISSILES; i++)
	{
		missile[i].is_visible = 0;
		missile[i].x_coordinate = -1;
		missile[i].y_coordinate = -1;
		missile[i].sprite = NULL;
	}
	
	
/*	playerDemo = {20, 50, PLAYER_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL, NULL, 0,0,NULL,0, 1, TRUE, DO_NOTHING,2};*/
	playerDemo.x_coordinate = 20;
	playerDemo.y_coordinate = 50;
	playerDemo.hitpoints = PLAYER_HITPOINTS;
	playerDemo.current_speed = MAXSPEED;
	playerDemo.is_moving = TRUE;
	playerDemo.is_firing = FALSE;
	getBitmap32(playerTankNorth, playerDemo.sprite);
/*	playerDemo.sprite = &playerTankNorth;*/
	playerDemo.x_posMask = 0;
	playerDemo.y_posMask = 0;
	playerDemo.h_facing = VERTICAL;
	playerDemo.v_facing = UP;
	playerDemo.is_visible = TRUE;
	playerDemo.current_behaviour = DO_NOTHING;
	playerDemo.missile_available = 2;
	
	demoArray[0].x_coordinate = 600;
	demoArray[0].y_coordinate = 10;
	demoArray[0].hitpoints = ENEMY_HITPOINTS;
	demoArray[0].current_speed = MAXSPEED;
	demoArray[0].is_moving = TRUE;
	demoArray[0].is_firing = FALSE;
/*	demoArray[0].sprite = enemyTankNorth;*/
	demoArray[0].x_posMask = 0;
	demoArray[0].y_posMask = 0;
	demoArray[0].h_facing = LEFT;
	demoArray[0].v_facing = UP;
	demoArray[0].is_visible = TRUE;
	demoArray[0].current_behaviour = DO_NOTHING;
	demoArray[0].missile_available = 2;
	
	demoArray[1].x_coordinate = 250;
	demoArray[1].y_coordinate = 30;
	demoArray[1].hitpoints = ENEMY_HITPOINTS;
	demoArray[1].current_speed = MAXSPEED;
	demoArray[1].is_moving = TRUE;
	demoArray[1].is_firing = FALSE;
/*	demoArray[1].sprite = enemyTankEast;*/
	demoArray[1].x_posMask = 0;
	demoArray[1].y_posMask = 0;
	demoArray[1].h_facing = LEFT;
	demoArray[1].v_facing = UP;
	demoArray[1].is_visible = TRUE;
	demoArray[1].current_behaviour = DO_NOTHING;
	demoArray[1].missile_available = 2;
	
/*	demoArray[1] = {600, 10, ENEMY_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,NULL, -1, 0, TRUE, D0_NOTHING,2};*/
	demoArray[2].x_coordinate = 300;
	demoArray[2].y_coordinate = 50;
	demoArray[2].hitpoints = ENEMY_HITPOINTS;
	demoArray[2].current_speed = MAXSPEED;
	demoArray[2].is_moving = TRUE;
	demoArray[2].is_firing = FALSE;
/*	demoArray[2].sprite = enemyTankEast;*/
	demoArray[2].x_posMask = 0;
	demoArray[2].y_posMask = 0;
	demoArray[2].h_facing = LEFT;
	demoArray[2].v_facing = UP;
	demoArray[2].is_visible = TRUE;
	demoArray[2].current_behaviour = DO_NOTHING;
	demoArray[2].missile_available = 2;
	
/*	demoArray[1] = {250, 30, ENEMY_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,NULL, -1, 0, TRUE, DO_NOTHING,2};*/
	demoArray[4].x_coordinate = 400;
	demoArray[4].y_coordinate = 70;
	demoArray[4].hitpoints = ENEMY_HITPOINTS;
	demoArray[4].current_speed = MAXSPEED;
	demoArray[4].is_moving = TRUE;
	demoArray[4].is_firing = FALSE;
/*	demoArray[4].sprite = enemyTankEast;*/
	demoArray[4].x_posMask = 0;
	demoArray[4].y_posMask = 0;
	demoArray[4].h_facing = LEFT;
	demoArray[4].v_facing = UP;
	demoArray[4].is_visible = TRUE;
	demoArray[4].current_behaviour = DO_NOTHING;
	demoArray[4].missile_available = 2;

/*	demoArray[2] = {300, 50, ENEMY_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,NULL, -1, 0, TRUE, DO_NOTHING, 2};*/
	demoArray[3].x_coordinate = 200;
	demoArray[3].y_coordinate = 100;
	demoArray[3].hitpoints = ENEMY_HITPOINTS;
	demoArray[3].current_speed = MAXSPEED;
	demoArray[3].is_moving = TRUE;
	demoArray[3].is_firing = FALSE;
/*	demoArray[3].sprite = enemyTankEast;*/
	demoArray[3].x_posMask = 0;
	demoArray[3].y_posMask = 0;
	demoArray[3].h_facing = LEFT;
	demoArray[3].v_facing = UP;
	demoArray[3].is_visible = TRUE;
	demoArray[3].current_behaviour = DO_NOTHING;
	demoArray[3].missile_available = 2;

/*	demoArray[3] = {400, 70, ENEMY_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,NULL, -1, 0, TRUE, DO_NOTHING, 2};*/
/*	demoArray[5] = {200, 100, ENEMY_HITPOINTS, MAXSPEED, TRUE, FALSE, NULL,NULL, -1, 0, TRUE, DO_NOTHING, 2};*/
/*
	demoArray[1].sprite = enemyTankNorth;
	demoArray[1].sprite = enemyTankNorth;
	demoArray[2].sprite = enemyTankNorth;
	demoArray[3].sprite = enemyTankNorth;
	demoArray[5].sprite = enemyTankNorth;
*/	

	for(i = 1; i < NUMBER_OFENEMYTANKS; i++)
	{
		getBitmap32(enemyTankNorth, demoArray[i].sprite);
	}


	/*=========Will Change in next system=========================*/
	mainScreen 		= (Physbase());
	logMainscreen 	= (Logbase());
	
	backdropScreen 	= (char*) Malloc(BUFFER_SIZE);
	backdropScreen 	= (char*) ((UINT32) (gameScreen + 256) & 0x00FFFF00); /* The screens have to be 256 byte aligned */
	
	gameScreen = (char*) Malloc(BUFFER_SIZE);
	gameScreen = (char*) ((UINT32) (gameScreen + 256) & 0x00FFFF00); /* The screens have to be 256 byte aligned */
	
	backGamescreen = (char*) Malloc(BUFFER_SIZE);
	backGamescreen = (char*) ((UINT32) (gameScreen + 256) & 0x00FFFF00); /* The screens have to be 256 byte aligned */

	
	clear(gameScreen);
	clear(backGamescreen);
	

	/*===========================================================*/

	/* TODO Initiate game system */

	readfile = Fopen("tankscreen.pi1",0);
	
	handle = (readfile &= 0x0000FFFF); /*handle is in lower word */
	
	 Fseek(34,handle,0); /*align to data offset in degas file */
	 
	 Fread(handle,FILE_SIZE,backdropScreen); /*load data to mem */
	
	
	Cursconf(0, 0); /* removes cursor*/

	

	makeGameScreens(gameScreen,backGamescreen);	
	 
	
	 
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

/*=====================here is main game loop==================*/
		plotLargeSprite(gameScreen, playerDemo.sprite, demoArray[i].x_coordinate,demoArray[i].y_coordinate,32);
		for(i = 0; i < NUMBER_OFENEMYTANKS; i++)
		{
			plotLargeSprite(gameScreen, demoArray[i].sprite, demoArray[i].x_coordinate,demoArray[i].y_coordinate,32);
		}
	

		Vsync();
		Setscreen(gameScreen, gameScreen, -1L);

		
		
		do {

			

			
			
			
			
			if(DSconis())
			{
				playerInput = 1;
				if (keypress == 'p') {
				/*=====================here is pause game loop==================*/
				clear(mainScreen);
				Vsync();
				Setscreen(logMainscreen, mainScreen, -1L);
				
				Cconws("In pause game loop \r\n\0");
				Cconws("Please press any key to start \r\n\0");

				while (!DSconis()) {
				}
				keypress = DSnecin();
				}
			}
			else
			{
				playerInput = 0;
			}
			model(&playerDemo,demoArray,missile, landobjects, 
			NUMBER_OFENEMYTANKS,MAX_MISSILES, NUM_OBJECTS,keypress,playerInput);
			
			plotLargeSprite(gameScreen, playerDemo.sprite, demoArray[i].x_coordinate,demoArray[i].y_coordinate,32);

			for(i = 0; i < NUMBER_OFENEMYTANKS; i++)
			{
				plotLargeSprite(gameScreen, demoArray[i].sprite, demoArray[i].x_coordinate,demoArray[i].y_coordinate,32);

/*				plotLargeSprite(gameScreen, demoArray[i].sprite, demoArray[i].x_coordinate
				demoArray[i].y_coordinate, 32);*/
			}
			Vsync();
			Setscreen(gameScreen, gameScreen, -1L);
			clear(backGamescreen);


			Vsync();
			Setscreen(backGamescreen, backGamescreen, -1L);
		} while (keypress != 'q');

	}

	/*TODO clean up*/

	Mfree(gameScreen);
	Mfree(backGamescreen);

	return 0;

}

void pauseAndchill(int duration) {

	
	}



void gameReset(){
	
	
	
}
	

void makeGameScreens(long* screenChunk1 ,long* screenChunk2)
{
	long readfile;
	long *fastCopyptSrc = screenChunk1;
	long *fastCopyptDst = screenChunk2;
	int  handle;
	int i;
	
	readfile = Fopen("grass.pi1",0);
	
	handle = (readfile &= 0x0000FFFF); /*handle is in lower word */
	
	Fseek(34,handle,0); /*align to data offset in degas file */
	 
	Fread(handle,FILE_SIZE,screenChunk1); /*load data to mem */
	
	for(i = 0 ;i < SCREEN_SIZE;i++)
	{
	
		*(screenChunk2) = *(screenChunk1);
		
		screenChunk1++;
		screenChunk2++;
		
		
	}
	

	
}
