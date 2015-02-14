#ifndef MODEL_H
#define MODEL_H

#include "types.h"
#include "Enemy.h"

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
	BOOL is_visable;
	BEHAVIOUR current_behaviour;
	
}Tank;

typedef struct Missile
{
	int x_coordinate;
	int y_coordinate;
	V_DIRECTION vertical_movement;
	H_DIRECTION horizontal_movement;
	UINT8 max_speed;
	UINT8 *sprite;
	BOOL is_visable;
	BOOL moving_vertical;
}Missile;

typedef struct Stationary_Object
{
	int x_coordinate;
	int y_coordinate;
	UINT32 *sprite;

}Stationary_Object;

#endif












































