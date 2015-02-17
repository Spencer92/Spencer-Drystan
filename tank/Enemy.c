#include "model.h"
#include "Enemy.h"
#include "stdio.h"
#include "missile.h"
#include "math.h"
#include "osbind.h"
/*void dodge_x(Tank *tank,  Stationary_Object object, int direction);
void dodge_y(Tank *tank, Stationary_Object object, int direction);
BEHAVIOUR missile_fired( Tank *tank, Missile *missile);
BEHAVIOUR move_check( Tank *enemy, Tank *player);
BEHAVIOUR die_check( Tank *enemy,  Missile *missile);
BEHAVIOUR shoot_check( Tank *enemy, Tank *player, Missile *missile);
BEHAVIOUR turn_check( Tank *enemy, Tank *player);
BEHAVIOUR respawn_check( Tank *enemy);
BOOL event();
BOOL flip(int position);
void move_y(Tank *tank, Stationary_Object object, int offset);
void move_x(Tank *tank, Stationary_Object object, int offset);
*/

BOOL event();
BOOL flip(int position);

void respawn(Tank *tank)
{
	tank->is_visible = 1;
}


void die(Tank *tank)
{
	tank->is_visible = 0;
	tank->is_firing = 0;
	tank->is_moving = 0;
}


void shoot(Tank *tank, Missile *missile)
{
	if(tank->missile_available > 0)
	{
		tank->is_firing = 1;
		tank->missile_available--;
		missile->is_visible = 1;
	}
	else
	{
		tank->is_firing = 0;
		Cconws("I cannot fire!\r\n\0");
	}
}

void turn(Tank *tank)
{
	/*TODO change sprite for tank */
	switch(tank->h_facing)
	{
		case VERTICAL:
			tank->h_facing = LEFT;
			tank->v_facing = HORIZONTAL;
			break;
		case LEFT:
			tank->h_facing = VERTICAL;
			tank->v_facing = UP;
		case RIGHT:
			tank->h_facing = VERTICAL;
			tank->v_facing = DOWN;
		default:
			break;
	}

}


void dodge_x(Tank *tank, Stationary_Object object, int direction)
{

	if(flip(tank->x_coordinate))
	{
		move_x(tank, object, direction);
	}
	else
	{
		move_x(tank, object, direction *-1);
	}


}


void dodge_y(Tank *tank, Stationary_Object object, int direction)
{
	if(flip(tank->y_coordinate))
	{
		move_y(tank, object, direction);
	}
	else
	{
		move_y(tank, object, direction * -1);
	}
	
}


BEHAVIOUR missile_fired(Tank *tank, Missile *missile)
{
	if(tank->x_coordinate == missile->x_coordinate) /*TODO figure out way to check if the missile is coming towards them without killing time*/
	{
		return DODGE_X;
	}
	else if(tank->y_coordinate == missile->y_coordinate)
	{
		return DODGE_Y;
	}
	else
	{
		return tank->current_behaviour;
	}
	

}

BEHAVIOUR move_check_x(Tank *enemy, Tank *player, int *direction)
{
	register int x_coordinate_enemy = enemy->x_coordinate;
	register int x_coordinate_player = player->x_coordinate;
	register int y_coordinate_enemy = enemy->y_coordinate;
	register int y_coordinate_player = player->y_coordinate;
	
	if(((x_coordinate_enemy - x_coordinate_player) < (y_coordinate_enemy - y_coordinate_player)
		&& (x_coordinate_enemy - x_coordinate_player > 0))
		||
		((x_coordinate_enemy - x_coordinate_player) > (y_coordinate_enemy - y_coordinate_player)
		&& (x_coordinate_enemy - x_coordinate_player < 0)))
	{
		if(player->x_coordinate - enemy->x_coordinate < 0)
		{
			*direction = -1;
		}
		else
		{
			*direction = 1;
		}
		return MOVE_X;
	}
	else
	{
		return enemy->current_behaviour;
	}
} 


BEHAVIOUR move_check_y(Tank *enemy, Tank *player, int *direction)
{
	register int x_coordinate_enemy = enemy->x_coordinate;
	register int x_coordinate_player = player->x_coordinate;
	register int y_coordinate_enemy = enemy->y_coordinate;
	register int y_coordinate_player = player->y_coordinate;
	
	if(((y_coordinate_enemy - y_coordinate_player) < (x_coordinate_enemy - x_coordinate_player)
		&& (y_coordinate_enemy - y_coordinate_player > 0))
		||
		((y_coordinate_enemy - y_coordinate_player) > (x_coordinate_enemy - x_coordinate_player)
		&& (y_coordinate_enemy - y_coordinate_player < 0)))
	{
		if(enemy->y_coordinate - player->y_coordinate < 0)
		{
			*direction = 1;
		}
		else
		{
			*direction = -1;
		}
		return MOVE_Y;
	}
	else
	{
		return enemy->current_behaviour;
	}
} 


BEHAVIOUR die_check(Tank *enemy, Missile *missile)
{
	if(enemy->x_coordinate == missile->x_coordinate && enemy->y_coordinate == missile->y_coordinate)
	{
		return DIE;
	}
	else
	{
		return enemy->current_behaviour;
	}
}


BEHAVIOUR shoot_check(Tank *enemy, Tank *player, Missile *missile)
{
	if(enemy->x_coordinate == player->x_coordinate || enemy->y_coordinate == player->y_coordinate)
	{
		return SHOOT;
	}
	else
	{
		return enemy->current_behaviour;
	}
}

BEHAVIOUR turn_check(Tank *enemy, Tank *player)
{
	if(((enemy->x_coordinate == player->x_coordinate) && enemy->v_facing == HORIZONTAL) || ((enemy->y_coordinate == player->y_coordinate) && enemy->h_facing == VERTICAL))
	{
		return TURN;
	}
	else
	{
		return enemy->current_behaviour;
	}
}

BEHAVIOUR respawn_check(Tank *enemy)
{
	if(event())
	{
		return RESPAWN;
	}
	else
	{
		return enemy->current_behaviour;
	}
}

BEHAVIOUR dodge_y_check(Tank *enemy, Missile *missile)
{
	if(enemy->y_coordinate == missile->x_coordinate && missile->is_visible)
	{
		return DODGE_Y;
	}
	else
	{
		return enemy->current_behaviour;
	}

}

BEHAVIOUR dodge_x_check(Tank *enemy, Missile *missile)
{
	if(enemy->x_coordinate == missile->x_coordinate && missile->is_visible)
	{
		return DODGE_X;
	}
	else
	{
		return enemy->current_behaviour;
	}
}




BOOL event() {return 0;}



BOOL flip(int position)
{
	return position%2;
}


void move_y(Tank *tank, Stationary_Object object, int offset)
{
	if(tank->y_coordinate+offset != object.y_coordinate && tank->x_coordinate != object.x_coordinate)
	{
		tank->y_coordinate += offset;
	}
	else
	{
		if(flip(tank->y_coordinate))
		{
			move_x(tank, object, 1);
		}
		else
		{
			move_x(tank, object, -1);
		}
	}
}

void move_x(Tank *tank, Stationary_Object object, int offset)
{
	if(tank->x_coordinate+offset != object.x_coordinate && tank->y_coordinate != object.y_coordinate)
	{
		tank->x_coordinate += offset;
	}
	else
	{
		if(flip(tank->x_coordinate))
		{
			move_y(tank, object, 1);
		}
		else
		{
			move_y(tank, object, -1);
		}
	}
}


























































