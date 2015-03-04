/*#include "raster.h"*/
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
void enemy_first_pass(Tank *player, Tank *enemy, Missile *missile, int *direction);
void enemy_second_pass(Tank *player, Tank *enemy, Missile *missile, int direction, Stationary_Object object);
void missile_first_pass(Tank *tank, Missile *missile, int offset);
void missile_second_pass(Tank *tank, Missile *missile, int offset);
void missile_explode_pass(Tank *tank, Missile *missile);




int main()
{
	int direction = 0;
	int offset = 1;
	Tank players;
	Tank enemy;
	Stationary_Object tree;
	Missile missile_one;
	Missile missile_two;
	UINT8 thing;
	players.h_facing = RIGHT;
	players.v_facing = HORIZONTAL;
	players.hitpoints = 98765L;
	players.max_speed = 4;
	players.is_moving = 0;
	players.is_firing = 0;
	players.x_coordinate = 200;
	players.y_coordinate = 300;
	
	enemy.h_facing = RIGHT;
	enemy.v_facing = HORIZONTAL;
	enemy.hitpoints = 98765L;
	enemy.max_speed = 4;
	enemy.is_moving = 0;
	enemy.is_firing = 0;
	enemy.x_coordinate = 190;
	enemy.y_coordinate = 180;
	enemy.missile_available = 1;

	missile_one.is_visible = 0;
	missile_two.is_visible = 0;
	
	do
	{

 		printf("%i, %i: missile\n", missile_one.x_coordinate, missile_one.y_coordinate);
		printf("%i, %i: enemy\n", enemy.x_coordinate, enemy.y_coordinate);
		enemy_first_pass(&players, &enemy, &missile_one, &direction);
		enemy_second_pass(&players, &enemy, &missile_one, direction, tree);
		missile_first_pass(&enemy, &missile_one, offset);
		missile_explode_pass(&players, &missile_one);
		missile_second_pass(&enemy, &missile_one, offset);
		Cconws("done pass\r\n\0");
	}while(missile_one.behaviour != EXPLODE);
	
	
	
	
	return 0;

}	

void enemy_first_pass(Tank *player, Tank *enemy, Missile *missile, int *direction)
{
	enemy->current_behaviour = missile_fired(enemy, missile);
	enemy->current_behaviour = move_check_x(enemy, player, direction);
	enemy->current_behaviour = move_check_y(enemy, player, direction);
	enemy->current_behaviour = die_check(enemy, missile);
	enemy->current_behaviour = shoot_check(enemy,player,missile);
	enemy->current_behaviour = turn_check(enemy,player);
	enemy->current_behaviour = respawn_check(enemy);
	enemy->current_behaviour = dodge_x_check(enemy, missile);
	enemy->current_behaviour = dodge_y_check(enemy, missile);
}


void enemy_second_pass(Tank *player, Tank *enemy, Missile *missile, int direction, Stationary_Object object)
{
	switch(enemy->current_behaviour)
	{
		case SHOOT:
			Cconws("Enemy: Ok, Shooting target\r\n\0");
			shoot(enemy, missile);
			
			if(!enemy->missile_available)
			{
				Cconws("Enemy: I want to fire a missile, but I can't!\r\n\0");
			}
			if(missile->is_visible)
			{
				Cconws("Missile firing\r\n\0");
			}
			break;
		case DODGE_X:
			Cconws("Enemy: Ok, dodging x\r\n\0");
			dodge_x(enemy, object, direction);
			break;
		case DODGE_Y:
			Cconws("Enemy: Ok, dodging y\r\n\0");
			dodge_y(enemy, object, direction);
			break;
		case MOVE_X:
			Cconws("Enemy: Ok, moving x\r\n\0");
			move_x(enemy, object, direction);
			break;
		case MOVE_Y:
			Cconws("Enemy: Ok, moving y\r\n\0");
			move_y(enemy, object, direction);
			break;
		case DIE:
			Cconws("Enemy: Ok, dying\r\n\0");
			die(enemy);
			break;
		case RESPAWN:
			Cconws("Enemy: Ok, respawning\r\n\0");
			respawn(enemy);
			break;
		case TURN:
			Cconws("Enemy: Ok, turning\r\n\0");
			turn(enemy);
			break;
		default:
			break;
			
	}
}


void missile_first_pass(Tank *tank, Missile *missile, int offset)
{
	missile->is_visible = missile_exist_check(tank, missile, offset);
	if(missile->is_visible)
	{
		missile->behaviour = move_up_check(missile, tank);
		missile->behaviour = move_down_check(missile, tank);
		missile->behaviour = move_right_check(missile, tank);
		missile->behaviour = move_left_check(missile, tank);
		offscreen(missile);
	}
	else
	{
		Cconws("Missile: I do not exist");
	}
}


void missile_explode_pass(Tank *tank, Missile *missile)
{
	missile->behaviour = explode_check(missile,tank);
}

void missile_second_pass(Tank *tank, Missile *missile, int offset)
{
	if(missile->is_visible)
	{
		switch(missile->behaviour)
		{
			case MOVE_UP:
				Cconws("Missile: Ok, moving up\r\n\0");
				move_up(missile, offset);
				break;
			case MOVE_RIGHT:
				Cconws("Missile: Ok, moving right\r\n\0:");
				move_right(missile, offset);
				break;
			case MOVE_LEFT:
				Cconws("Missile: Ok, moving left\r\n\0");
				move_left(missile, offset);
				break;
			case MOVE_DOWN:
				Cconws("Missile: Ok, moving down\r\n\0");
				move_down(missile, offset);
				break;
			case EXPLODE:
				Cconws("Missile: Ok, exploding");
				explode(missile, tank);
				break;
			default:
				break;
		}
	}

}



/*	
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

*/





























