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

#include <osbind.h>
#include <stdio.h>
#include <stdlib.h>
/*===================================================*/
/*Header files authored by Others*/
#include "font.h"
#include  "types.h"
/*===================================================*/
/*Header files authored by Spencer Maslen or Drystan Mazur*/

#include  "model.h"
#include  "clrScrn.h"
#include  "Keyboard.h"
#include  "AIsystem.h"
#include  "CollsionDetect.h"
#include  "TileControl.h"
#include  "RenderEngine.h"
#include  "AssemblerRoutines.h"

/*===================================================*/
#define  NUMBER_OFLIVES 3
#define  PLAYER_HITPOINTS 50
#define  ENEMY_TANKHITPOINTS 5
#define  NUMBER_OFENEMYTANKS 5
#define  NUMBER_TILES 1
#define  MAXSPEED = 5

#define BUFFER_SIZE   0x8100L

void gameReset();

int main() {

	UINT8 playerSprite[8] = { 0xff, 0x18, 0x18, 0xff, 0x18, 0xff, 0x18, 0xff };
	UINT8 enemySprite[8] = { 0xf1, 0xfd, 0xfd, 0x00, 0xff, 0x18, 0xfd, 0xff };
	/* TODO Screen *screenAray[2] = {};*/

	Tank *playerTank = {200,200,PLAYER_HITPOINTS,MAXSPEED,TRUE,FALSE,}
	Tank *enemyTank = {}
	Missile *missiles[2] = {};

	char keypress;
	UNIT16 playerScore = 0;

	UNIT32 mainScreen;
	UNIT32 gameScreen;
/*=========Will Change in next system=========================*/
	mainScreen = (char*) (Physbase());

	gameScreen = Malloc(BUFFER_SIZE);

	gameScreen = (char*) ((gameScreen + 256) & 0x00FFFF00); /* The screens have to be 256 byte alligned */

	clear(gameScreen);
/*===========================================================*/

	/* TODO Intaiate game system */

	plotSprite(gameScreen, playerSprite, 200, 200, 8);
	plotSprite(gameScreen, enemySprite, 400, 300, 8);

	return 0;

}

void gameReset() {
	/*TODO Here we need to reset all varibles and game states*/
}
