#include "GameF.h"
#include "Bitmaps.h"
#include "Behavior.h"

const int xPostions[] = {250,250,300,400,200};
const int yPostions[] = {30,30,50,70,100};
volatile void thing3(){}

void gameStart(struct Tank gameArray[], Tank *player, Missile missile[], int numOfEnemy, int *score )
{

    register int i;

	*score = 0;
	
	player->x_coordinate = 320;
	player->y_coordinate = 200;
	player->hitpoints = PLAYER_HITPOINTS;
	player->current_speed = MAXSPEED;
	player->is_moving = TRUE;
	player->is_firing = FALSE;	
    player->sprite = playerTankNorth;
	player->x_posMask = 0;
	player->y_posMask = 0;
	player->h_facing = VERTICAL;
	player->v_facing = UP;
	player->is_visible = TRUE;
	player->current_behaviour = DO_NOTHING;
	player->missile_available = START_PLAYER_MISSILES;

	for(i = 0; i < numOfEnemy; i++)
	{
	gameArray[i].x_coordinate = xPostions[i];
	gameArray[i].y_coordinate = yPostions[i];
	gameArray[i].hitpoints = ENEMY_HITPOINTS;
	gameArray[i].current_speed = MAXSPEED;
	gameArray[i].is_moving = TRUE;
	gameArray[i].is_firing = FALSE;
	gameArray[i].sprite = playerTankNorth;
	gameArray[i].x_posMask = 0;
	gameArray[i].y_posMask = 0;
	gameArray[i].h_facing = LEFT;
	gameArray[i].v_facing = UP;
	gameArray[i].is_visible = TRUE;
	gameArray[i].current_behaviour = DO_NOTHING;
	gameArray[i].missile_available = START_PLAYER_MISSILES;	
	
	
	}

	
	for(i = 0; i < MAX_MISSILES; i++)
	{
		missile[i].is_visible = 0;
		missile[i].x_coordinate = -1;
		missile[i].y_coordinate = -1;
		missile[i].sprite = NULL;
	}

	
	
}
