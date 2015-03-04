#include "Behavior.h"


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
	
	if(((x_coordinate_enemy - x_coordinate_player) < ((y_coordinate_enemy - y_coordinate_player)-16) /*Check to see if the player should move in the x direction because it's y offset is greater than it's x offset */
		&& (x_coordinate_enemy - x_coordinate_player > 16))
		||
		((x_coordinate_enemy - x_coordinate_player) > ((y_coordinate_enemy - y_coordinate_player)+16)
		&& (x_coordinate_enemy - x_coordinate_player < -16)))
	{
		if(player->x_coordinate - enemy->x_coordinate < -16) /*if the tank isn't lined up with the player to make a shot */
		{
			*direction = -1;
		}
		else if(player->x_coordinate - enemy->x_coordinate > 16) /*if the tank isn't lined up with the player to make a shot*/
		{
			*direction = 1;
		}
		else
		{
			return enemy->current_behaviour;
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
	
	if(((y_coordinate_enemy - y_coordinate_player) < ((x_coordinate_enemy - x_coordinate_player) + 16)
		&& (y_coordinate_enemy - y_coordinate_player > 16))
		||
		((y_coordinate_enemy - y_coordinate_player) > ((x_coordinate_enemy - x_coordinate_player)+16)
		&& (y_coordinate_enemy - y_coordinate_player < -16)))
	{
		if(enemy->y_coordinate - player->y_coordinate < -16)
		{
			*direction = 1;
		}
		else if(enemy->y_coordinate - player->y_coordinate > 16)
		{
			*direction = -1;
		}
		else
		{
			return enemy->current_behaviour;
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
	if((enemy->x_coordinate >= missile->x_coordinate-16
		&& enemy->x_coordinate <= missile->x_coordinate+16) 
		&& 
		(enemy->y_coordinate >= missile->y_coordinate-16
		&& enemy->y_coordinate <= missile->y_coordinate+16))
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
	if((enemy->x_coordinate >= player->x_coordinate-8
		&&enemy->x_coordinate <= player->x_coordinate+8)
		|| 
		(enemy->y_coordinate >= player->y_coordinate-8
		&& enemy->y_coordinate <= player->y_coordinate+8))
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
	if(((enemy->x_coordinate >= player->x_coordinate-16
		&& enemy->x_coordinate <= player->x_coordinate+16) 
		&& enemy->v_facing == HORIZONTAL) || 
		((enemy->y_coordinate >= player->y_coordinate-16
		&&enemy->y_coordinate <= player->y_coordinate+16) && enemy->h_facing == VERTICAL))
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
	if(enemy->y_coordinate >= missile->y_coordinate-16
		&& enemy->y_coordinate <= missile->y_coordinate+16
		&& missile->is_visible)
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
	if(enemy->x_coordinate <= missile->x_coordinate+16
		&& enemy->x_coordinate >= missile->x_coordinate-16
		&& missile->is_visible)
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
	if((tank->y_coordinate+offset >= object.y_coordinate-16
		&& tank->y_coordinate+offset <= object.y_coordinate+16)
		&& tank->x_coordinate <= object.x_coordinate+16
		&& tank->x_coordinate >= object.x_coordinate-16)
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
	if((tank->x_coordinate+offset >= object.x_coordinate-16
		&& tank->x_coordinate+offset <= object.x_coordinate+16)
		&& tank->y_coordinate <= object.y_coordinate+16
		&& tank->y_coordinate >= object.y_coordinate+16)
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






