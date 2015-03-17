#include "model.h"
#include "behavior.h"
#include "missile.h"
#include "stdlib.h"
#include "osbind.h"
#define BOOL UINT8
BOOL missiles_alive_y(Tank *enemy, Missile* missile, int *num_missiles);
BOOL missiles_alive_x(Tank *enemy, Missile* missile, int *num_missiles);
void assess_situation(Tank enemy[], Tank *player, Stationary_Object *object, Missile* missile, int num_enemies, int num_missiles);
void missile_check(Tank *tank, Missile *missile, UINT8 num_missiles, int num_tanks);
BOOL adjacent_tanks(Tank *tanks, int current_tank, int num_tanks);




int main()
{
	Tank player;
	Tank enemy[3];
	Missile missile[10];
	int initial_offset = 100;
	int index;
	int number_of_enemies = 3;
	
	player.x_coordinate = 250;
	player.y_coordinate = 250;
	player.hitpoints = 100;
	player.current_speed = 0;
	player.is_moving = 0;
	player.is_firing = 0;
	player.sprite = NULL;
	player.x_posMask = 0;
	player.y_posMask = 0;
	player.h_facing = VERTICAL;
	player.v_facing = DOWN;
	player.is_visible = 1;
	player.current_behaviour = DO_NOTHING;
	player.is_firing = 0;
	player.missile_available = 2;
	
	for(index = 0; index < number_of_enemies; index++)
	{
		enemy[index].x_coordinate = initial_offset;
		enemy[index].y_coordinate = 100;
		enemy[index].hitpoints = 100;
		enemy[index].current_speed = 0;
		enemy[index].is_moving = 0;
		enemy[index].is_firing = 0;
		enemy[index].sprite = NULL;
		enemy[index].x_posMask = 0;
		enemy[index].y_posMask = 0;
		enemy[index].h_facing = VERTICAL;
		enemy[index].v_facing = DOWN;
		enemy[index].is_visible = 1;
		enemy[index].current_behaviour = DO_NOTHING;
		enemy[index].is_firing = 0;
		initial_offset += 32;
	}
	
	return 0;
}




void missile_check(Tank *tank, Missile *missile, UINT8 num_missiles, int num_tanks)
{
	int index_missile;
	int index_tanks;
	BOOL finished_firing = 0;
	for(index_tanks = 0; index_tanks < num_tanks; index_tanks++)
	{
		finished_firing = 0;
		for(index_missile = 0; index_missile < num_missiles && !finished_firing; index_missile++)
		{
			if(tank[index_tanks].is_firing && !missile[index_missile].is_visible)
			{
				if(tank[index_tanks].v_facing == UP)
				{
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate-16;
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].behaviour = MOVE_UP;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing == LEFT)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate-16;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].behaviour = MOVE_LEFT;
					finished_firing = 1;
				}
				else if(tank[index_tanks].v_facing = DOWN)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate+16;
					missile[index_missile].behaviour = MOVE_DOWN;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing = RIGHT)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate+16;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].behaviour = MOVE_RIGHT;
					finished_firing = 1;

				}
			}
			else if(!tank[index_tanks].is_firing)
			{
				finished_firing = 1;
			}
		}
	}
	
}


void respond_to_situation(Tank *tanks, 
						Stationary_Object* objects, 
						Missile *missiles, 
						int num_tanks, 
						int num_objects)
{
	int index;
	int direction;
	for(index = 0; index < num_tanks; index++)
	{
		if(tanks[index].current_behaviour == SHOOT)
		{
			if(tanks[index].missile_available > 0)
			{
				missile_check(&tanks[index], missiles, tanks[index].missile_available, 1);
				tanks[index].missile_available--;
			}
		}
		else if(tanks[index].current_behaviour == DODGE_X && !adjacent_tanks(tanks, index, num_tanks))
		{
			dodge_x(&tanks[index], objects, &tanks[index].h_facing, num_objects);
		}
		else if(tanks[index].current_behaviour == DODGE_Y && !adjacent_tanks(tanks, index, num_tanks))
		{
			dodge_y(&tanks[index], objects, &tanks[index].v_facing, num_objects);
		}
		else if(tanks[index].current_behaviour == MOVE_X)
		{
			move_x(&tanks[index], objects, tanks[index].h_facing, num_objects);
		}
		else if(tanks[index].current_behaviour == MOVE_Y)
		{
			move_y(&tanks[index], 
			objects, 
			tanks[index].h_facing, 
			num_objects);
		}
		else if(tanks[index].current_behaviour == DIE)
		{
			tanks[index].is_visible = 0;
		}
		else if(tanks[index].current_behaviour == RESPAWN)
		{
			tanks[index].is_visible = 1;
		}
		else if(tanks[index].current_behaviour == TURN)
		{
			turn(&tanks[index]);
		}

	}
}


BOOL adjacent_tanks(Tank *tank, int current_tank, int num_tanks)
{
	int index;
	for(index = 0; index < num_tanks; index++)
	{
		if(index != current_tank-1 && ((tank[current_tank].h_facing)*16 < tank[index].x_coordinate - 16
										&& (tank[current_tank].h_facing)*16 < tank[index].x_coordinate + 16
										&& (tank[current_tank].v_facing)*16 < tank[index].y_coordinate + 16
										&& (tank[current_tank].v_facing)*16 < tank[index].y_coordinate - 16))
		{
			return 1;
		}
	}
	return 0;
}


void assess_situation(Tank enemy[], Tank *player, Stationary_Object *object, Missile* missile, int num_enemies, int num_missiles)
{
	int index;

	for(index = 0; index < num_enemies; index++)
	{
		if(player->is_firing)
		{
		
			enemy[index].current_behaviour = missile_fired(&enemy[index], 
			missile, 
			&num_missiles);
		}
		else if(missiles_alive_x(&enemy[index], 
									missile, 
									&num_missiles))
		{
			enemy[index].current_behaviour = DODGE_X;
		}
		else if(missiles_alive_y(&enemy[index], 
									missile, 
									&num_missiles))
		{
			enemy[index].current_behaviour = DODGE_Y;
		}
		else if((enemy[index].x_coordinate >= player->x_coordinate-8
		&&enemy[index].x_coordinate <= player->x_coordinate+8)
		|| 
		(enemy[index].y_coordinate >= player->y_coordinate-8
		&& enemy[index].y_coordinate <= player->y_coordinate+8))
		{
			enemy[index].current_behaviour = SHOOT;
		}
		else if(((enemy[index].x_coordinate >= player->x_coordinate-16
		&& enemy[index].x_coordinate <= player->x_coordinate+16) 
		&& enemy[index].v_facing == HORIZONTAL) || 
		((enemy[index].y_coordinate >= player->y_coordinate-16
		&&enemy[index].y_coordinate <= player->y_coordinate+16) && enemy[index].h_facing == VERTICAL))
		{
			enemy[index].current_behaviour = TURN;
		}
		else if(((enemy[index].y_coordinate - player->y_coordinate) < ((enemy[index].x_coordinate - player->x_coordinate) + 16)
		&& (enemy[index].y_coordinate - player->y_coordinate > 16))
		||
		((enemy[index].y_coordinate - player->y_coordinate) > ((enemy[index].x_coordinate - player->x_coordinate)+16)
		&& (enemy[index].y_coordinate - player->y_coordinate < -16)))
		{
			enemy[index].current_behaviour = MOVE_Y;
		}
		else if(((enemy[index].x_coordinate - player->x_coordinate) < ((enemy[index].y_coordinate - player->y_coordinate)-16) /*Check to see if the player should move in the x direction because it's y offset is greater than it's x offset */
		&& (enemy[index].x_coordinate - player->x_coordinate > 16))
		||
		((enemy[index].x_coordinate - player->x_coordinate) > ((enemy[index].y_coordinate - player->y_coordinate)+16)
		&& (enemy[index].x_coordinate - player->x_coordinate < -16)))
		{
			enemy[index].current_behaviour = MOVE_X;
		}
		else if(foo(&enemy[index], missile, num_missiles))
		{
			enemy[index].current_behaviour = DIE;
		}
	}
}


BOOL missiles_alive_x(Tank *enemy, 
						Missile* missile,  
						int* num_missiles)
{
	int index;
	for(index = 0; index < *num_missiles && enemy->current_behaviour != DODGE_X; index++)
	{
		enemy->current_behaviour = dodge_x_check(enemy, &missile[index]);
	}
	if(enemy->current_behaviour == DODGE_X)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

BOOL missiles_alive_y( Tank *enemy, Missile* missile, int* num_missiles)
{
	int index;
	for(index = 0; index < *num_missiles && enemy->current_behaviour 
	!= DODGE_Y; index++)
	{
		enemy->current_behaviour = dodge_y_check(enemy, &missile[index]);
	}
	if(enemy->current_behaviour == DODGE_Y)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


























