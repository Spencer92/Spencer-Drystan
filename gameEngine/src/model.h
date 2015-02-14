#ifndef MODEL_H
#define MODEL_H

#include "types.h"

#define BOOL UINT8
#define TRUE 1
#define FALSE 0


typedef enum H_DIRECTION
{
	RIGHT = 1,
	LEFT = -1
	
}H_DIRECTION;

typedef enum V_DIRECTION
{
	UP = -1,
	HORIZTIAL = 0;
	DOWN = 1
	
}V_DIRECTION;


typedef struct Tank
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT32 hitpoints;
	UINT8  max_speed;
	BOOL is_moving;
	BOOL is_firing;
	/*UINT32 *sprite;*/
	UINT 8 *sprite;
	UINT8 *Missile;
	H_DIRECTION h_facing;
	V_DIRECTION v_facing;
	BOOL is_visable;
}Tank;

typedef struct Missile
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT8 max_speed;
	UINT8 *sprite;
	BOOL is_visable;
}Missile;

typedef struct Stationary_Object
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT32 *sprite;

}Stationary_Object;

#endif












































