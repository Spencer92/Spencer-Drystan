#ifndef MODEL_H
#define MODEL_H



#define BOOL UINT8
#define TRUE  1
#define FALSE 0

#include "Behavior.h"
void model(Tank* player, Tank* enemy, Missile *missile, Stationary_Object *object, 
			int num_enemies, int num_missiles, int num_objects, char input, BOOL input_valid);



#endif












































