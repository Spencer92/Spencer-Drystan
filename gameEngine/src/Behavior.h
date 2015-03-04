#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

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

}BEHAVIOUR;

void turn(Tank *tank);
void dodge_x(Tank *tank, Stationary_Object object, int direction);
void dodge_y(Tank *tank, Stationary_Object object, int direction);
void move_y(Tank *tank, Stationary_Object object, int offset);
void move_x(Tank *tank, Stationary_Object object, int offset);
void shoot(Tank *tank, Missile *missile);
void die(Tank *tank);
void respawn(Tank *tank);
BOOL flip(int position);

BEHAVIOUR missile_fired(Tank *tank, Missile *missile);
BEHAVIOUR move_check_x(Tank *enemy, Tank *player, int *direction);
BEHAVIOUR move_check_y(Tank *enemy, Tank *player, int *direction);
BEHAVIOUR die_check(Tank *enemy, Missile *missile);
BEHAVIOUR shoot_check(Tank *enemy, Tank *player, Missile *missile);
BEHAVIOUR turn_check(Tank *enemy, Tank *player);
BEHAVIOUR respawn_check(Tank *enemy);
BEHAVIOUR dodge_x_check(Tank *enemy, Missile *missile);
BEHAVIOUR dodge_y_check(Tank *enemy, Missile *missile);




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






#endif // BEHAVIOUR_H
