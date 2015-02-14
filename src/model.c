#include "raster.h"
#include "types.h"
/*#include <tos.h> */
#include <osbind.h>
#include <stdio.h>
/*#include <stdint.h>*/
#include <stdlib.h>
#include "model.h"

BOOL flip();
void move_to_player(Tank *player, Tank *enemy, Stationary_Object object);
void right_move(Tank *enemy, Stationary_Object object);
void left_move(Tank *enemy, Stationary_Object object);
void up_move(Tank *enemy, Stationary_Object object);
void down_move(Tank *enemy, Stationary_Object object);
void fire(Tank *tank);

int main()
{

	Tank players;
	Tank enemy;
	Stationary_Object tree;
	UINT8 thing;
	players.h_facing = RIGHT;
	players.v_facing = DOWN;
	players.hitpoints = 98765L;
	players.max_speed = 4;
	players.is_moving = 0;
	players.is_firing = 0;
	players.x_coordinate = 200;
	players.y_coordinate = 300;
	
	enemy.h_facing = RIGHT;
	enemy.v_facing = DOWN;
	enemy.hitpoints = 98765L;
	enemy.max_speed = 4;
	enemy.is_moving = 0;
	enemy.is_firing = 0;
	enemy.x_coordinate = 190;
	enemy.y_coordinate = 180;

	
	
	while(enemy.x_coordinate != players.x_coordinate && enemy.y_coordinate != players.y_coordinate)
	{
		printf("Moving from [%i][%i] to [%i][%i]\n", enemy.y_coordinate, enemy.x_coordinate, players.y_coordinate, players.x_coordinate);
		move_to_player(&players, &enemy, tree);
	}

	Cconout("HEY\r\n\0");
	return 0;
}


void move_to_player(Tank *player, Tank *enemy, Stationary_Object object)
{

	if((enemy->x_coordinate != player->x_coordinate) && (enemy->y_coordinate != player->y_coordinate))
	{
		if((player->x_coordinate - enemy->x_coordinate) <= (player->y_coordinate - enemy->y_coordinate))
		{
			if(player->x_coordinate > enemy->x_coordinate)
			{
				right_move(enemy, object);
			}
			else
			{
				left_move(enemy, object);
			}
		}
		else
		{
			if(player->y_coordinate > enemy->y_coordinate)
			{
				down_move(enemy, object);
			}	
			else
			{
				up_move(enemy, object);
			}
		}
	}
	else
	{
		fire(enemy);
	}
}

BOOL flip()
{
	return 0;
}

void right_move(Tank *enemy, Stationary_Object object)
{
	if((enemy->x_coordinate)+1 != object.x_coordinate)
	{
		enemy->x_coordinate++;
		enemy->h_facing = RIGHT;
	}
	else
	{
		if(flip())
		{
			enemy->y_coordinate++;
		}
		else
		{
			enemy->x_coordinate++;
		}
	}
}

void left_move(Tank *enemy, Stationary_Object object)
{
	enemy->x_coordinate--;
	enemy->h_facing = LEFT;
}

void up_move(Tank *enemy, Stationary_Object object)
{
	enemy->y_coordinate--;
	enemy->v_facing = UP;
}

void down_move(Tank *enemy, Stationary_Object object)
{
	enemy->y_coordinate++;
	enemy->v_facing = DOWN;
}

void fire(Tank *tank)
{
	tank->is_firing = 1;
}































