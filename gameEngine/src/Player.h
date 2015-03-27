#ifndef PLAYER_H
#define PLAYER_H

typedef enum PLAYER_BEHAVIOUR
{
	MOVE_RIGHT_PLAYER,
	MOVE_LEFT_PLAYER,
	MOVE_UP_PLAYER,
	MOVE_DOWN_PLAYER,
	FIRE_MISSILE_PLAYER,
	EXPLODE_PLAYER,

}PLAYER_BEHAVIOUR;

void player_move_right(Tank *player);
void player_move_up(Tank *player);
void player_move_left(Tank *player);
void player_move_down(Tank *player);

#endif