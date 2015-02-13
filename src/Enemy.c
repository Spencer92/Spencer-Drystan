#include "model.h"
#include "Enemy.h"






void dodge_x(Tank *tank, Stationary_Object object)
{
	if(tank->current_behaviour == DODGE_X)
	{
		if(flip(tank->x_coordinate))
		{
			move_up(tank, object);
		}
		else
		{
			move_down(tank, object);
		}
	}

}


void dodge_y(Tank *tank, Stationary_Object object)
{
	if(tank->current_behaviour == DODGE_Y)
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

BEHAVIOUR move_check(Tank *enemy, Tank *player)
{
	if((enemy->x_location-player->x_location) > (enemy->y_location-player->y_location))
	{
		return MOVE_X;
	}
	else
	{
		return MOVE_Y;
	}
} 


BEHAVIOUR die(Tank *enemy, Missile *missile)
{
	if(enemy->x_coordinate == missile->x_coordinate && enemy->y_coordinate == missile->y_coordinate)
	{
		return DIE;
	}
	else
	{
		return enemy->current_behaviour
	}
}


BEHAVIOUR shoot(Tank *enemy, Tank *player, Missile *missile)
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





























































