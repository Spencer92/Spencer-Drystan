#ifndef MODEL_H
#define MODEL_H

#include "types.h"
#include "Enemy.h"
#include "Missile.h"


typedef UINT8 BOOL;


typedef enum H_DIRECTION
{
	RIGHT = 1,
	LEFT = -1,
	VERTICAL = 0
	
}H_DIRECTION;

typedef enum V_DIRECTION
{
	UP = -1,
	DOWN = 1,
	HORIZONTAL = 0
	
}V_DIRECTION;


typedef struct Tank
{
	int x_coordinate;
	int y_coordinate;
	UINT32 hitpoints;
	UINT8  max_speed;
	BOOL is_moving;
	BOOL is_firing;
	UINT32 *sprite;
	UINT8 *bullets;
	H_DIRECTION h_facing;
	V_DIRECTION v_facing;
	BOOL is_visible;
	BEHAVIOUR current_behaviour;
	BOOL missile_available;
	
}Tank;

typedef struct Missile
{
	int x_coordinate;
	int y_coordinate;
	V_DIRECTION vertical_movement;
	H_DIRECTION horizontal_movement;
	UINT8 max_speed;
	UINT8 *sprite;
	BOOL is_visible;
	BOOL moving_vertical;
	MISSILE_BEHAVIOUR behaviour;
}Missile;

typedef struct Stationary_Object
{
	int x_coordinate;
	int y_coordinate;
	UINT32 *sprite;

}Stationary_Object;

void turn(Tank *tank);
void dodge_x(Tank *tank, Stationary_Object object, int direction);
void dodge_y(Tank *tank, Stationary_Object object, int direction);
BEHAVIOUR missile_fired(Tank *tank, Missile *missile);
BEHAVIOUR move_check_x(Tank *enemy, Tank *player, int *direction);
BEHAVIOUR move_check_y(Tank *enemy, Tank *player, int *direction);
BEHAVIOUR die_check(Tank *enemy, Missile *missile);
BEHAVIOUR shoot_check(Tank *enemy, Tank *player, Missile *missile);
BEHAVIOUR turn_check(Tank *enemy, Tank *player);
BEHAVIOUR respawn_check(Tank *enemy);
BEHAVIOUR dodge_x_check(Tank *enemy, Missile *missile);
BEHAVIOUR dodge_y_check(Tank *enemy, Missile *missile);
BOOL flip(int position);
void move_y(Tank *tank, Stationary_Object object, int offset);
void move_x(Tank *tank, Stationary_Object object, int offset);
void shoot(Tank *tank, Missile *missile);
void die(Tank *tank);
void respawn(Tank *tank);


MISSILE_BEHAVIOUR move_up_check(Missile *missile, Tank* tank);
MISSILE_BEHAVIOUR move_down_check(Missile *missile, Tank* tank);
MISSILE_BEHAVIOUR move_right_check(Missile *missile, Tank* tank);
MISSILE_BEHAVIOUR move_left_check(Missile *missile, Tank* tank);
MISSILE_BEHAVIOUR explode_check(Missile *missile, Tank *tank);
BOOL missile_exist_check(Tank *tank, Missile *missile, int offset);
void move_up(Missile *missile, int offset);
void move_down(Missile *missile, int offset);
void move_right(Missile *missile, int offset);
void move_left(Missile *missile, int offset);
void offscreen(Missile *missile);
void explode(Missile *missile, Tank *tank);






#endif












































