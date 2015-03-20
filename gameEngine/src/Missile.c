#include "model.h"
#include "behavior.h"


MISSILE_BEHAVIOUR move_up_check(Missile *missile)
{
	if(missile->is_visible && missile->vertical_movement == UP)
	{
		return MOVE_UP;
	}
	else
	{
		return missile->current_behaviour;
	}
}



MISSILE_BEHAVIOUR move_down_check(Missile *missile)
{
	if(missile->is_visible && missile->vertical_movement == DOWN)
	{
		return MOVE_DOWN;
	}
	else
	{
		return missile->current_behaviour;
	}
}


MISSILE_BEHAVIOUR move_right_check(Missile *missile)
{
	if(missile->is_visible && missile->horizontal_movement == RIGHT)
	{
		return MOVE_RIGHT;
	}
	else
	{
		return missile->current_behaviour;
	}

}

MISSILE_BEHAVIOUR move_left_check(Missile *missile)
{
	if(missile->is_visible && missile->horizontal_movement == LEFT)
	{
		return MOVE_LEFT;
	}
	else
	{
		return missile->current_behaviour;
	}
	
}



MISSILE_BEHAVIOUR explode_check(Missile *missile, Tank *tank)
{
	if(missile->x_coordinate == tank->x_coordinate && missile->y_coordinate == tank->y_coordinate)
	{
		return EXPLODE;
	}
	else
	{
		return missile->current_behaviour;
	}
}






void move_up(Missile *missile, int offset)
{
	missile->vertical_movement = UP;
	missile->horizontal_movement = VERTICAL;
	missile->y_coordinate -= offset;
}


void move_down(Missile *missile, int offset)
{
	missile->vertical_movement = DOWN;
	missile->horizontal_movement = VERTICAL;
	missile->y_coordinate += offset;
}

void move_right(Missile *missile, int offset)
{
	missile->vertical_movement = HORIZONTAL;
	missile->horizontal_movement = RIGHT;
	missile->x_coordinate += offset;
}

void move_left(Missile *missile, int offset)
{
	missile->vertical_movement = HORIZONTAL;
	missile->horizontal_movement = LEFT;
	missile->x_coordinate -= offset;
}

































































