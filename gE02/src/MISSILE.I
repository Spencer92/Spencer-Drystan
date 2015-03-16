# 1 "missile.c" 1
# 1 "./model.h" 1
# 1 "./types.h" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
# 6 "./model.h" 2
# 1 "./behavior.h" 1
# 1 "./types.h" 1
# 3 "./behavior.h" 2
# 1 "./missile.h" 1




typedef enum MISSILE_BEHAVIOUR
{
	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT,
	EXPLODE

}MISSILE_BEHAVIOUR;
# 4 "./behavior.h" 2
# 1 "./model.h" 1
# 5 "./behavior.h" 2





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




typedef struct Tank
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT32 hitpoints;
	UINT8  current_speed;
	UINT8  is_moving;
	UINT8  is_firing;
	UINT32 *sprite;
	UINT32 backMask[32];
	UINT16 x_posMask;
	UINT16 y_posMask;
	UINT8  *Missile;
	H_DIRECTION h_facing;
	V_DIRECTION v_facing;
	UINT8  is_visible;
	BEHAVIOUR current_behaviour;
	UINT8 missile_available;
}Tank;

typedef struct Missile
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT8 max_speed;
	UINT8 *sprite;
	UINT8  is_visible;
	MISSILE_BEHAVIOUR behaviour;
	H_DIRECTION horizontal_movement;
	V_DIRECTION vertical_movement;
}Missile;

typedef struct Stationary_Object
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT32 *sprite;

}Stationary_Object;



void turn(Tank *tank);
void dodge_y(Tank *tank, Stationary_Object *object, int *direction, int num_objects);
void dodge_x(Tank *tank, Stationary_Object *object, int *direction, int num_objects);
void move_y(Tank *tank, Stationary_Object *object, int offset, int num_objects);
void move_x(Tank *tank, Stationary_Object *object, int offset, int num_objects);
void shoot(Tank *tank, Missile *missile);
void die(Tank *tank);
void respawn(Tank *tank);
UINT8  flip(int position);
UINT8  die_check(Tank *enemy, Missile *missile, int num_missiles);


BEHAVIOUR foo(Tank * enemy, Missile * missile, int num_missles);
BEHAVIOUR missile_fired(Tank *tank, Missile *missile, int* num_missiles);
BEHAVIOUR move_check_x(Tank *enemy, Tank *player, int *direction);
BEHAVIOUR move_check_y(Tank *enemy, Tank *player, int *direction);
BEHAVIOUR shoot_check(Tank *enemy, Tank *player, Missile *missile);
BEHAVIOUR turn_check(Tank *enemy, Tank *player);
BEHAVIOUR respawn_check(Tank *enemy);
BEHAVIOUR dodge_x_check(Tank *enemy, Missile *missile);
BEHAVIOUR dodge_y_check(Tank *enemy, Missile *missile);
BEHAVIOUR move_check_player(Tank *enemy, Tank *player, char input);




MISSILE_BEHAVIOUR move_up_check(Missile *missile);
MISSILE_BEHAVIOUR move_down_check(Missile *missile);
MISSILE_BEHAVIOUR move_right_check(Missile *missile);
MISSILE_BEHAVIOUR move_left_check(Missile *missile);
MISSILE_BEHAVIOUR explode_check(Missile *missile, Tank *tank);
UINT8  missile_exist_check(Tank *tank, Missile *missile, int offset);
void move_up(Missile *missile, int offset);
void move_down(Missile *missile, int offset);
void move_right(Missile *missile, int offset);
void move_left(Missile *missile, int offset);
void offscreen(Missile *missile);
void explode(Missile *missile, Tank *tank);
# 7 "./model.h" 2
# 1 "missile.c" 2
# 1 "./behavior.h" 1
# 2 "missile.c" 2



MISSILE_BEHAVIOUR move_up_check(Missile *missile)
{
	if(missile->is_visible && missile->vertical_movement == UP)
	{
		return MOVE_UP;
	}
	else
	{
		return missile->behaviour;
	}
}



MISSILE_BEHAVIOUR move_down_check(Missile *missile)
{
	if(missile->is_visible && missile->vertical_movement == DOWN)
	{
		return MOVE_DOWN;
	}
	else
	{
		return missile->behaviour;
	}
}


MISSILE_BEHAVIOUR move_right_check(Missile *missile)
{
	if(missile->is_visible && missile->horizontal_movement == RIGHT)
	{
		return MOVE_RIGHT;
	}
	else
	{
		return missile->behaviour;
	}

}

MISSILE_BEHAVIOUR move_left_check(Missile *missile)
{
	if(missile->is_visible && missile->horizontal_movement == LEFT)
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
# 77 "missile.c"
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
