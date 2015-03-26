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

#inculde "Behavior.h"

void gameStart(Tank &gameArray[], Missile &missile[], int gameSize );

void gameReset(int &score);


#endif