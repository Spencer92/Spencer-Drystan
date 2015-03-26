#include "Behavior.h"
#include "Player.h"



PLAYER_BEHAVIOUR player_right_check(Tank *player, Stationary_Object object)
{
  if(player->x_coordinate+17 != object.x_coordinate)
    {
      return MOVE_RIGHT_PLAYER;
    }
}

PLAYER_BEHAVIOUR player_up_check(Tank *player, Stationary_Object object)
{
  if(player->y_coordinate-17 != object.y_coordinate)
    {
      return MOVE_UP_PLAYER;
    }
}


PLAYER_BEHAVIOUR player_down_check(Tank *player, Stationary_Object object)
{
  if(player->y_coordinate+17 != object.y_coordinate)
    {
      return MOVE_DOWN_PLAYER;
    }
}


PLAYER_BEHAVIOUR player_left_check(Tank *player, Stationary_Object object)
{
  if(player->x_coordinate-17 != object.x_coordinate)
    {
      return MOVE_LEFT_PLAYER;
    }
}


PLAYER_BEHAVIOUR player_fire_check(Tank *player)
{
		player->is_firing = 1;
		return FIRE_MISSILE_PLAYER;
}


PLAYER_BEHAVIOUR player_explode_check(Tank *player, Missile *missile)
{
	if(player->x_coordinate == missile->x_coordinate || player->y_coordinate == missile->x_coordinate)
	{
		return EXPLODE_PLAYER;
	}
}



void player_move_right(Tank *player)
{
  player->x_coordinate++;
}


void player_move_up(Tank *player)
{
  player->y_coordinate--;
}


void player_move_left(Tank *player)
{
  player->x_coordinate--;
}


void player_move_down(Tank *player)
{
  player->y_coordinate++;
}



