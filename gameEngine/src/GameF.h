#ifndef GAMEF_H
#define GAMEF_H

#define  MAX_MISSILES 10
#define  GAME_SIZE 6
#define  NUMBER_OFLIVES 3
#define  PLAYER_HITPOINTS 50
#define  ENEMY_HITPOINTS 5
#define  START_PLAYER_MISSILES 2
#define  NUM_OBJECTS 6
#define  NUMBER_OFTANKS 6
#define  NUMBER_TILES 1
#define  MAXSPEED  5
#define  TRUE 1
#define  FALSE 0

#include <stddef.h>

#include "Behavior.h"

void gameStart(struct Tank gameArray[],struct Missile missile[], int gameSize );

void gameReset(int *score);

#endif