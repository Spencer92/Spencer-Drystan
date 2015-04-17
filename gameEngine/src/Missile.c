#include "Model.h"
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


volatile void thin14() {}
void exploding_check(Missile *missile, Tank *tank)
{
	thin14();
	if(missile->x_coordinate+8 >= tank->x_coordinate-32 && missile->y_coordinate+8 <= tank->y_coordinate-32
		|| missile->x_coordinate-8 <= tank->x_coordinate+32 && missile->y_coordinate-8 >= tank->y_coordinate+32)
	{
		missile->current_behaviour = EXPLODE;
		tank->current_behaviour = DIE;
		missile->is_visible = 0;
		missile->x_coordinate;
		missile->y_coordinate;
	}
}

volatile thin16() {}
void move_missile(Missile *missile)
{
	thin16();
	if(missile->current_behaviour == MOVE_RIGHT)
	{	
		missile->x_coordinate += 8;
	}
	else if(missile->current_behaviour == MOVE_LEFT)
	{
		missile->x_coordinate -= 8;
	}
	else if(missile->current_behaviour == MOVE_UP)
	{
		missile->y_coordinate -= 8;
	}
	else if(missile->current_behaviour == MOVE_DOWN)
	{
		missile->y_coordinate += 8;
	}
	if(missile->x_coordinate > 640 || missile->x_coordinate < 0 || missile->y_coordinate < 0 || missile->y_coordinate > 360)
	{
		missile->is_visible = 0;
		missile->sprite = 0;
		missile->y_coordinate = -1;
		missile->x_coordinate = -1;
		missile->current_behaviour = DO_NOTHING_MISSILE;
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

































































