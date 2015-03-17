#include "model.h"
#include "behavior.h"
#include "missile.h"
#include "stdlib.h"
#include "osbind.h"
BOOL missiles_alive_y(Missile* missile, Tank *enemy, int num_missiles);
BOOL missiles_alive_x(Missile* missile, Tank *enemy, int num_missiles);
void player_action_check(Tank *player, Tank *enemy, int num_enemies, char input, Missile* missiles);
void player_action(Tank* player, Missile* missile, char input);
BOOL tanks_at(Tank* player, Tank* enemy, int num_tanks);



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
	player.is_visable = 1;
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
		enemy[index].is_visable = 1;
		enemy[index].current_behaviour = DO_NOTHING;
		enemy[index].is_firing = 0;
		initial_offset += 32;
	}
	
	return 0;
}

char DSnecin()
{
	return Cnecin();
}



void player_action_check(Tank *player, Tank *enemy, int num_enemies, char input, Missile* missile, int num_missiles)
{
	if((input == 'd' || input == 'a') && !tanks_at(player, enemy, num_enemies)
	{
		player->current_behaviour = MOVE_X;
	}
	else if((input == 'w' || input == 's') && !tanks_at(player,enemy, num_enemies))
	{
		player->current_behaviour = MOVE_Y;
	}
	else if(input == ' ')
	{
		player->current_behaviour = SHOOT;
	}
	else if(die_check(player, missile, num_missiles))
	{
		player->current_behaviour = DIE;
	}
	else
	{
		player->current_behaviour == DO_NOTHING;
	}
}

void player_action(Tank* player, Missile* missile, char input)
{
	if(player->current_behaviour == MOVE_X && input == 'd')
	{
		player->x_coordinate++;
	}
	else if(player->current_behaviour == MOVE_X && input == 'a')
	{
		player->x_coordinate--;
	}
	else if(player->current_behaviour == MOVE_Y && input == 'w')
	{
		player->y_coordinate--;
	}
	else if(player->current_behaviour == MOVE_Y && input == 'd')
	{
		player->y_coordinate++;
	}
	else if(player->current_behaviour == SHOOT)
	{
		missile_check(player, missile, player->missile_available, 1);
	}
}

BOOL tanks_at(Tank* player, Tank* enemy, int num_tanks)
{
	int index;
	BOOL something_there = 0;
	for(index = 0; index < num_tanks && !something_there; index++)
	{
		if(!((player->x_coordinate + 16 < enemy[index].x_coordinate - 16 ||
			player->x_coordinate - 16 > enemy[index].x_coordinate + 16) &&
			(player->y_coordinate - 16 < enemy[index].y_coordinate + 16 ||
			plyaer->y_coordinate + 16 > enemy[index].y_coordinate - 16)))
			{
				something_there = 1;
			}
	}
	return something_there;
}



void missile_check(Tank *tank, Missile *missile, int num_missiles, int num_tanks)
{
	int index_missile;
	int index_tanks;
	BOOL finished_firing = 0;
	for(index_tanks = 0; index_tanks < num_tanks; index_tanks++)
	{
		finished_firing = 0;
		for(index_missile = 0; index_missile < num_missiles && !finished_firing; index_missile++)
		{
			if(tank[index_tanks].is_firing && !missile[index_missile].is_visable)
			{
				if(tank[index_tanks].v_facing == UP)
				{
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate-16;
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].current_behaviour = MOVE_UP;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing == LEFT)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate-16;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].current_behaviour = MOVE_LEFT;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].v_facing = DOWN)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate+16;
					missile[index_missile].current_behaviour = MOVE_DOWN;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing = RIGHT)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate+16;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].current_behaviour = MOVE_RIGHT;
					missile[index_missile].is_visible = 1;
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





void assess_situation(Tank enemy[], Tank *player, Stationary_Object *object, Missile* missile, int num_enemies, int num_missiles)
{
	int index;
	BOOL missile_alive_x;
	BOOL missile_alive_y;
	BEHAVIOUR missile_fired;
	for(index = 0; index < num_enemies; index++)
	{
		if(player->is_firing)
		{
			enemy[index].current_behaviour = missile_fired(enemy[index], missile, num_missiles);
		}
		else if(missiles_alive_x(enemy[index],
									missile, 
									num_missiles))
		{
			enemy[index].current_behaviour = DODGE_X;
		}
		else if(missiles_alive_y(enemy[index], 
									missile, 
									num_missiles))
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
		else if(die_check(enemy[index], missile, num_missiles))
		{
			enemy[index].current_behaviour = DIE;
		}
		else
		{
			enemy[index].current_behaviour = DO_NOTHING;
		}
	}
}



BOOL missiles_alive_x(Missile* missile, Tank *enemy, int num_missiles)
{
	int index;
	for(index = 0; index < num_missiles && enemy->current_behaviour != DODGE_X; index++)
	{
		enemy->current_behaviour = dodge_x_check(enemy, missile[index]);
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

BOOL missiles_alive_y(Missile* missile, Tank *enemy, int num_missiles)
{
	int index;
	for(index = 0; index < num_missiles && enemy->current_behaviour != DODGE_Y; index++)
	{
		enemy->current_behaviour = dodge_y_check(enemy, missile[index]);
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

























