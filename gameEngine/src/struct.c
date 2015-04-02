#include "osbind.h"
#include "stdlib.h"


typedef enum H_DIRECTION
{
	RIGHT = 1,
	LEFT  = -1,
	VERTICAL = 0
	
}H_DIRECTION;

typedef enum V_DIRECTION
{
	UP = -1,
	HORIZONTAL = 0,
	DOWN = 1
	
}V_DIRECTION;

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

typedef unsigned int UINT16;
typedef unsigned long UINT32;
typedef unsigned char UINT8;
#define BOOL UINT8

typedef struct Tank
{

	UINT16 x_coordinate;	
	UINT16 y_coordinate;
	UINT32 hitpoints;
	UINT8  current_speed;
	BOOL is_moving;
	BOOL is_firing;
	UINT16 x_posMask;
	UINT16 y_posMask;
	H_DIRECTION h_facing;
	V_DIRECTION v_facing;
	BOOL is_visible;
	BEHAVIOUR current_behaviour;
	UINT8 missile_available;
	UINT32 *sprite;
	UINT8  *Missile;	
	UINT32 backMask[64];
}Tank;

Tank tank;

int main()
{
	UINT16 check1 = tank.x_coordinate;
	UINT16 check2 = tank.y_coordinate;
	UINT32 check3 = tank.hitpoints;
	UINT8 check4 = tank.current_speed;
	BOOL check5 = tank.is_moving;
	BOOL check6 = tank.is_firing;
	UINT16 check9 = tank.x_posMask;
	UINT16 check10 = tank.y_posMask;
	H_DIRECTION check12 = tank.h_facing;
	V_DIRECTION check13 = tank.v_facing;
	BOOL check14 = tank.is_visible;
	BEHAVIOUR check15 = tank.current_behaviour;
	UINT8 check16 = tank.missile_available;
	UINT32 *check7 = tank.sprite;	
	UINT8 *check11 = tank.Missile;
	UINT32 check500 = tank.backMask[0];
	UINT32 check8 = tank.backMask[63];


	Cconws("HERE I AM\r\n\0");
	
	
	return 0;
	
	
}






