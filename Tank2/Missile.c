#include "missile.h"
#include "model.h"
#include "osbind.h"

#define SCREEN_WIDTH 639
#define SCREEN_HEIGHT 399


MISSILE_BEHAVIOUR move_up_check(Missile *missile, Tank *tank)
{
	if(missile->is_visible && (tank->v_facing == UP || missile->behaviour == MOVE_UP))
	{
		return MOVE_UP;
	}
	else
	{
		return missile->behaviour;
	}
}



MISSILE_BEHAVIOUR move_down_check(Missile *missile, Tank *tank)
{
	if(missile->is_visible && (tank->v_facing == DOWN || missile->vertical_movement == DOWN))
	{
		return MOVE_DOWN;
	}
	else
	{
		return missile->behaviour;
	}
}


MISSILE_BEHAVIOUR move_right_check(Missile *missile, Tank *tank)
{
	if(missile->is_visible && (tank->h_facing == RIGHT || missile->horizontal_movement == RIGHT))
	{
		return MOVE_RIGHT;
	}
	else
	{
		return missile->behaviour;
	}

}

MISSILE_BEHAVIOUR move_left_check(Missile *missile, Tank *tank)
{
	if(missile->is_visible && (tank->h_facing == LEFT || missile->horizontal_movement == LEFT))
	{
		return MOVE_LEFT;
	}
	else
	{
		return missile->behaviour;
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
		return missile->behaviour;
	}
}


BOOL missile_exist_check(Tank *tank, Missile *missile, int offset)
{
	if(tank->is_firing == 1)
	{
		missile->horizontal_movement = tank->h_facing;
		missile->vertical_movement = tank->v_facing;
		Cconws("Setting initial missile location\r\n\0");
		if(missile->horizontal_movement == RIGHT)
		{
			missile->x_coordinate = tank->x_coordinate+offset;
			missile->y_coordinate = tank->y_coordinate;
		}
		else if(missile->horizontal_movement == LEFT)
		{
			missile->x_coordinate = tank->x_coordinate-offset;
			missile->y_coordinate = tank->y_coordinate;
		}
		else if(missile->vertical_movement == UP)
		{
			missile->y_coordinate = tank->y_coordinate-offset;
			missile->x_coordinate = tank->x_coordinate;
		}
		else if(missile->vertical_movement == DOWN)
		{
			missile->y_coordinate = tank->y_coordinate+offset;
			missile->x_coordinate = tank->x_coordinate;
		}
		tank->is_firing = 0;
		
		return 1;
	}
	else
	{
		return missile->is_visible;
	}
}



void explode(Missile *missile, Tank *tank)
{
		tank->is_visible = 0;
		missile->is_visible = 0;
}

void offscreen(Missile *missile)
{
	if(missile->x_coordinate > SCREEN_WIDTH || missile->x_coordinate < 0 
	|| missile->y_coordinate > SCREEN_HEIGHT || missile->y_coordinate < 0)
	{
		missile->is_visible = 0;
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

































































