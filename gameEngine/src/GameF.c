#include "GameF.h"
#include "bitmaps.h"


const int xPostions[] = {600,250,300,400,200};
const int yPostions[] = {10,30,50,70,100};

void gameStart(Tank gameArray[], Missile missile[], int gameSize, int *score )
{

    register int i;

	*score = 0;
	
	gameArray[0].x_coordinate = 20;
	gameArray[0].y_coordinate = 50;
	gameArray[0].hitpoints = PLAYER_HITPOINTS;
	gameArray[0].current_speed = MAXSPEED;
	gameArray[0].is_moving = TRUE;
	gameArray[0].is_firing = FALSE;	
    gameArray[0].sprite = playerTankNorth;
	gameArray[0].x_posMask = 0;
	gameArray[0].y_posMask = 0;
	gameArray[0].h_facing = VERTICAL;
	gameArray[0].v_facing = UP;
	gameArray[0].is_visible = TRUE;
	gameArray[0].current_behaviour = DO_NOTHING;
	gameArray[0].missile_available = START_PLAYER_MISSILES;

	
	
	for(i = 1; i < gameSize; i++)
	{
	gameArray[i].x_coordinate = xPostions[i -1];
	gameArray[i].y_coordinate = yPostions[i -1];
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
