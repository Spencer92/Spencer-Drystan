#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H
#include "types.h"
#include "Missile.h"

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
	BOOL is_moving;
	BOOL is_firing;
	UINT32 *sprite;
	UINT32 backMask[32];
	UINT16 x_posMask;
	UINT16 y_posMask;
	UINT8  *Missile;
	H_DIRECTION h_facing;
	V_DIRECTION v_facing;
	BOOL is_visible;
	BEHAVIOUR current_behaviour;
	UINT8 missile_available;
}Tank;

typedef struct Missile
{
	UINT16 x_coordinate;
	UINT16 y_coordinate;
	UINT8 max_speed;
	UINT8 *sprite;
	BOOL is_visible;
	MISSILE_BEHAVIOUR current_behaviour;
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

BOOL flip(int position);
BOOL die_check(Tank *enemy, Missile *missile, int num_missiles);


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

BOOL missile_exist_check(Tank *tank, Missile *missile, int offset);
BOOL missiles_alive_y(Tank *enemy, Missile* missile, int num_missiles);
BOOL missiles_alive_x(Tank *enemy, Missile* missile, int num_missiles);
BOOL tanks_at(Tank* player, Tank* enemy, int num_tanks);
BOOL DSconis();

void move_up(Missile *missile, int offset);
void move_down(Missile *missile, int offset);
void move_right(Missile *missile, int offset);
void move_left(Missile *missile, int offset);
void offscreen(Missile *missile);
void explode(Missile *missile, Tank *tank);
void player_action_check(Tank *player, Tank *enemy, int num_enemies, char input, Missile* missile, int num_missiles);
void player_action(Tank* player, Missile* missile, char input);

char DSnecin();
void DSconws(String output);
void missile_check(Tank *tank, Missile *missile, int num_missiles, int num_tanks);
void DSconout(char output);
int thing();
void assess_situation(Tank enemy[], Tank *player, Stationary_Object *object, Missile* missile, int num_enemies, int num_missiles);
void tank_respond(Tank *enemy, Missile *missile, int num_missiles, int num_tanks, Stationary_Object *object, int num_objects);







#endif
