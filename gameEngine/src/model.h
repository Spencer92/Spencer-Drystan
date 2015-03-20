#ifndef MODEL_H
#define MODEL_H

/*All the models in the game*/

/*#include "types.h"*/

typedef unsigned int UINT16;
typedef unsigned char UINT8;
typedef unsigned long UINT32;
#define BOOL UINT8
#define TRUE  1
#define FALSE 0
/*
typedef enum BEHAVIOUR
{
	SHOOT,
	DODGE_X,
	DODGE_Y,
	MOVE_X,
	MOVE_Y,
	DIE,
	RESPAWN,
	TURN,
	DO_NOTHING

}BEHAVIOUR;

typedef enum H_DIRECTION
{
	RIGHT = 1,
	LEFT  = -1
	
}H_DIRECTION;

typedef enum V_DIRECTION
{
	UP = -1,
	HORIZTIAL = 0,
	DOWN = 1
	
}V_DIRECTION;


typedef struct Tank
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT32 hitpoints;
	UINT8  current_speed;
	BOOL is_moving;
	BOOL is_firing;
	UINT32 *sprite;
	UINT32 backMask[32];
	UINT16 x_posMask;
	UINT16 y_posMask;
	UINT8  *Missile;
	enum H_DIRECTION h_facing;
	enum V_DIRECTION v_facing;
	BOOL is_visable;
	BEHAVIOUR current_behaviour;
	BOOL 
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
*/




#endif












































