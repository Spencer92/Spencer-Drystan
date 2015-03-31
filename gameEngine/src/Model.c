#include "Behavior.h"
#include "Missile.h"
#include "stdlib.h"
#include <osbind.h>
#include "System.h"
#include "Keyboard.h"

BOOL playAlin(Tank* enemy, Tank* player);
BOOL needTurn(Tank* enemy, Tank* player);
BOOL yMove(Tank* enemy, Tank* player, int index);
BOOL xMove(Tank* enemy, Tank* player, int index);
BOOL wrong(Tank* enemy);
BOOL notBehaviour(Tank* enemy, BEHAVIOUR behaviour);
void yfacing(Tank* enemy, Tank* player);
void xfacing(Tank* enemy, Tank* player);


/***************************************************************************
   Function Name:   model
  
   Purpose:         To run the backend of the game.
  
   Input Arguments: Player 			- The Player
					Enemy 			- The enemies
					Missile			- The missiles
					object			- The objects scattered around the game
					num_enimies		- The amount of enemies
					num_missiles	- The amount of missiles
					num_objects		- The amount of objects
  
   Method Notes:    Checks to see if the player has done anything
					and if so responds to the input the player has done
					
					The enemies will go on regardless
***************************************************************************/





void model(Tank* player, Tank* enemy, Missile *missile, Stationary_Object *object, 
			int num_enemies, int num_missiles, int num_objects, char input, BOOL input_valid)
{
	int tank_one_action = enemy[0].current_behaviour;
	int tank_two_action = enemy[1].current_behaviour;
	int tank_three_action = enemy[2].current_behaviour;
	int tank_four_action = enemy[3].current_behaviour;
	int tank_five_action = enemy[4].current_behaviour;
	if(input_valid)
	{
		player_action(player,missile,input);
	}
	tank_respond(enemy, missile, num_missiles, num_enemies, object, num_objects);	
}





/*This is mainly for debugging purposes*/
int thing()
{
	register int whatever = 3;
	return whatever;
}

/***************************************************************************
   Function Name:   player_action_check
  
   Purpose:         Looks at what was pushed and reacts based on that
  
   Input Arguments: Player 			- The Player
					Enemy 			- The enemies
					Missile			- The missiles
					num_enimies		- The amount of enemies
					num_missiles	- The amount of missiles
					input			- What the player is pressing
  
   Method Notes:    If 'd' or 'a' is pressed then the player tank will attempt to move left
					or right based on whether there is anything in the way
					
					If 'w' or 's' is pressed then the player tank will attempt to move
					up or down based on where there is anything in the way
					
					If ' ' is pressed then the player tank will attempt to shoot
					
					If the player is at the same place as a missile then the player dies
   
   
***************************************************************************/



void player_action_check(Tank *player, Tank *enemy, int num_enemies, char input, Missile* missile, int num_missiles)
{
	if((input == 'd' || input == 'a') && !tanks_at(player, enemy, num_enemies))
	{
		player->current_behaviour = MOVE_X;
	}
	else if((input == 'w' || input == 's') && !tanks_at(player,enemy, num_enemies))
	{
		player->current_behaviour = MOVE_Y;
	}
	else if(input == ' ')
	{
		player->current_behaviour = SHOOT;
		player->is_firing = 1;
	}
	else if(die_check(player, missile, num_missiles))
	{
		player->current_behaviour = DIE;
	}
	else
	{
		player->current_behaviour = DO_NOTHING;
	}
}





/***************************************************************************
   Function Name:   player_action
  
   Purpose:         To carry out the behaviour specified
  
   Input Arguments: Player 			- The Player
					Missile			- The missiles
					input			- What the player pressed previously
					
   Method Notes:    If 'd' was pressed then the player moves right
					If 'a' was pressed then the player moves left
					If 'w' was pressed then the player moves up
					if 'd' was pressed then the player moves down
					If the player behaviour was shooting then the amount of available missiles is
					checked and fired based on if there was any availble
   
   
***************************************************************************/



void player_action(Tank* player, Missile* missile, char input)
{
	if(player->current_behaviour == MOVE_X && input == 'd')
	{
		player->x_coordinate++;
	}
	else if(player->current_behaviour == MOVE_X && input == 'a')
	{
		player->x_coordinate--;
	}
	else if(player->current_behaviour == MOVE_Y && input == 'w')
	{
		player->y_coordinate--;
	}
	else if(player->current_behaviour == MOVE_Y && input == 'd')
	{
		player->y_coordinate++;
	}
	else if(player->current_behaviour == SHOOT)
	{
		missile_check(player, missile, player->missile_available, 1);
		player->is_firing = 0;
	}
}


/***************************************************************************
   Function Name:   Tanks_at
  
   Purpose:         To see if there is any tanks around the player
  
   Input Arguments: Player 			- The Player
					Enemy			- The enemy tanks
					num_tanks		- The number of tanks in the game
					
   Method Notes:    Check if anything is around the player (center + 16 pixels)
					in order for the enemies to not collide with the player and do weird things
   
   
***************************************************************************/


BOOL tanks_at(Tank* player, Tank* enemy, int num_tanks)
{
	int index;
	BOOL something_there = 0;
	for(index = 0; index < num_tanks && !something_there; index++)
	{
		if(!((player->x_coordinate + 16 < enemy[index].x_coordinate - 16 ||
			player->x_coordinate - 16 > enemy[index].x_coordinate + 16) &&
			(player->y_coordinate - 16 < enemy[index].y_coordinate + 16 ||
			player->y_coordinate + 16 > enemy[index].y_coordinate - 16)))
			{
				something_there = 1;
			}
	}
	return something_there;
}



/***************************************************************************
   Function Name:   tank_respond
  
   Purpose:         Does an action based on the current behaviour it possesses
  
   Input Arguments: enemy 			- the enemies
					missile			- the missiles
					num_missiles	- The number of missiles
					num_tanks		- the number of tanks
					object			- the objects in the playing field 
					num_objects		- The number of objects in the playing field
   
  
   Method Notes:    Goes through all the tanks and checks on their behaviour, and
					responds based on those behaviours
   
					If the current behaviour is SHOOT, then the tank should shoot
					If the current behaviour is DODGE_X or DODGE_Y, it will attempt
					do dodge based on the information the tank has
					If the current behaviour is MOVE_X or MOVE_Y, then it will move
					depending on what direction it wanted to move
					If the current behaviour is DIE, then the tank will stop being
					visible and things will stop reacting to it.
					If the current behaviour is TURN, then the tank will turn.
   
   
   
   
***************************************************************************/


volatile void thing4(){}
void tank_respond(Tank *enemy, Missile *missile, int num_missiles, int num_tanks, Stationary_Object *object, int num_objects)
{
	int index;
	BOOL missile_avail;
	int dodge_loc;
	int move_loc;

	for(index = 0; index < num_tanks; index++)
	{
		if(!wrong(&enemy[index]))
		{
			if(!(notBehaviour(&enemy[index],SHOOT)))
			{
				missile_avail = enemy[index].missile_available;
				missile_check(&enemy[index], missile, missile_avail, 1);
				enemy[index].is_firing = 0;
			}
			else if(!(notBehaviour(&enemy[index],DODGE_X)))
			{
				dodge_loc = enemy[index].h_facing;
				dodge_x(&enemy[index], object, dodge_loc, num_objects);
			}
			else if(!(notBehaviour(&enemy[index], DODGE_Y)))
			{
				dodge_loc = enemy[index].v_facing;
				dodge_y(&enemy[index], object, 
										dodge_loc, num_objects);
			}
			else if(!(notBehaviour(&enemy[index],MOVE_X)))
			{
				move_loc = enemy[index].h_facing;
				move_x(&enemy[index], object,move_loc, 
					   num_objects);

			}
			else if(!(notBehaviour(&enemy[index],MOVE_Y)))
			{
				thing4();
				move_loc = enemy[index].v_facing;
				move_y(&enemy[index], object, move_loc, num_objects);
			}
			else if(!(notBehaviour(&enemy[index],DIE)))
			{
				enemy[index].is_visible = 0;
			}
			else if(!(notBehaviour(&enemy[index],TURN)))
			{
				turn(&enemy[index]);
			}
		}
		enemy[index].current_behaviour = DO_NOTHING;
	}

}

BOOL notBehaviour(Tank* enemy, BEHAVIOUR behaviour)
{
	return enemy->current_behaviour != behaviour;
}


BOOL wrong(Tank* enemy)
{
	int current_behaviour = enemy->current_behaviour;
	return !(enemy->is_visible && enemy->current_behaviour != DO_NOTHING);
}



/***************************************************************************
   Function Name:   tank_respond
  
   Purpose:         Does an action based on the current behaviour it possesses
  
   Input Arguments: enemy 			- the enemies
					missile			- the missiles
					num_missiles	- The number of missiles
					num_tanks		- the number of tanks
					object			- the objects in the playing field 
					num_objects		- The number of objects in the playing field
   
  
   Method Notes:    Goes through all the tanks and checks on their behaviour, and
					responds based on those behaviours
   
					If the current behaviour is SHOOT, then the tank should shoot
					If the current behaviour is DODGE_X or DODGE_Y, it will attempt
					do dodge based on the information the tank has
					If the current behaviour is MOVE_X or MOVE_Y, then it will move
					depending on what direction it wanted to move
					If the current behaviour is DIE, then the tank will stop being
					visible and things will stop reacting to it.
					If the current behaviour is TURN, then the tank will turn.

***************************************************************************/

void missile_check(Tank *tank, Missile *missile, int num_missiles, int num_tanks)
{
	int index_missile;
	int index_tanks;
	BOOL finished_firing = 0;
	for(index_tanks = 0; index_tanks < num_tanks; index_tanks++)
	{
		finished_firing = 0;
		for(index_missile = 0; index_missile < num_missiles && !finished_firing; index_missile++)
		{
			if(tank[index_tanks].is_firing && !missile[index_missile].is_visible)
			{
				if(tank[index_tanks].v_facing == UP)
				{
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate-16;
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].current_behaviour = MOVE_UP;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing == LEFT)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate-16;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].current_behaviour = MOVE_LEFT;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].v_facing = DOWN)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate+16;
					missile[index_missile].current_behaviour = MOVE_DOWN;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing = RIGHT)
				{
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate+16;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].current_behaviour = MOVE_RIGHT;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;

				}
			}
			else if(!tank[index_tanks].is_firing)
			{
				finished_firing = 1;
			}
		}
	}
	
}




/***************************************************************************
   Function Name:   assess_situation
  
   Purpose:         The tanks look at there surroundings, and 
					do a multitude of things based on what they are seeing
  
   Input Arguments: enemy 			- the enemies
					player			- the player
					missile			- the missiles
					num_missiles	- The number of missiles
					num_tanks		- the number of tanks
					object			- the objects in the playing field 
					num_objects		- The number of objects in the playing field
   
  
   Method Notes:    Case 1	  :	The player is firing and thus the tanks will have
								to figure out based on it's surroundings what to do
					
					Case 2 & 3: There's a missile somewhere already and the tanks have to 
								figure out if it is a threat to them, and react accordingly
							
					Case 4	  : If the tank is lined up with the player, then the tank
								will take a shot at the player if it has a chance to

					Case 5	  : If the tank isn't alligned with the player or needs to move toward the
								player but isn't facing the player then the tank will turn.
					
					Case 6 & 7: Depending on what is closer, the tank will move either in
								the x direction or y direction
								
					Case 8	  : If a missile and a tank is at the same location, then the 
								tank will be instructed to no longer be visible
								
					Case 9	   : Somehow the tank didn't meet any requirments at all and thus it will not
								 do anything
					
					

***************************************************************************/

volatile void thing5(){}
void assess_situation(Tank enemy[], Tank *player, Stationary_Object *object, Missile* missile, int num_enemies, int num_missiles)
{
	int index;
	int tank_one_value;
	int tank_two_value;
	int tank_three_value;
	int tank_four_value;
	int tank_five_value;
	for(index = 0; index < num_enemies; index++)
	{
		if(player->is_firing) /* Case One */
		{
			enemy[index].current_behaviour = 
			missile_fired(&enemy[index], 
			missile, 
			&num_missiles);
		}
		else if(missiles_alive_x(&enemy[index],
									missile, 
									num_missiles))/* Case Two */
		{
			enemy[index].current_behaviour = DODGE_X;
		}
		else if(missiles_alive_y(&enemy[index], 
									missile, 
									num_missiles))
		{
			enemy[index].current_behaviour = DODGE_Y; /* Case Three */
		}
		else if(playAlin(&enemy[index],player)/*(enemy[index].x_coordinate >= player->x_coordinate-8
		&&enemy[index].x_coordinate <= player->x_coordinate+8)
		|| 
		(enemy[index].y_coordinate >= player->y_coordinate-8
		&& enemy[index].y_coordinate <= player->y_coordinate+8)*/) /* Case 4*/
		{
			enemy[index].current_behaviour = SHOOT;
			DSconws("SHOOT goddammit!! Y\r\0");
		}
		else if(needTurn(&enemy[index], player)/* ((enemy[index].x_coordinate >= player->x_coordinate-16
		&& enemy[index].x_coordinate <= player->x_coordinate+16) 
		&& enemy[index].v_facing == HORIZONTAL) || 
		((enemy[index].y_coordinate >= player->y_coordinate-16
		&&enemy[index].y_coordinate <= player->y_coordinate+16) && enemy[index].h_facing == VERTICAL) */) /* Case 5*/
		{
			enemy[index].current_behaviour = TURN;
		}
		else if(yMove(&enemy[index], player, index)/* ((enemy[index].y_coordinate - player->y_coordinate) < ((enemy[index].x_coordinate - player->x_coordinate) + 16)
		&& (enemy[index].y_coordinate - player->y_coordinate > 16))
		||
		((enemy[index].y_coordinate - player->y_coordinate) > ((enemy[index].x_coordinate - player->x_coordinate)+16)
		&& (enemy[index].y_coordinate - player->y_coordinate < -16)) */)/* Case 6 */
		{
			enemy[index].current_behaviour = MOVE_Y;
			yfacing(&enemy[index], player);
			DSconws("MOVE Y\r\0");
		}
		else if(xMove(&enemy[index], player, index)/* ((enemy[index].x_coordinate - player->x_coordinate) < ((enemy[index].y_coordinate - player->y_coordinate)-16) 
		&& (enemy[index].x_coordinate - player->x_coordinate > 16))
		||
		((enemy[index].x_coordinate - player->x_coordinate) > ((enemy[index].y_coordinate - player->y_coordinate)+16)
		&& (enemy[index].x_coordinate - player->x_coordinate < -16)) */)/* Case 7*/
		{/*Check to see if the player should move in the x direction because it's y offset is greater than it's x offset */
			thing5();			
			enemy[index].current_behaviour = MOVE_X;
			xfacing(&enemy[index], player);
		}
		else if(die_check(&enemy[index], missile, num_missiles))/*Case 8 */
		{
			enemy[index].current_behaviour = DIE;
		}
		else/* Case 9 */
		{
			enemy[index].current_behaviour = DO_NOTHING;
		}
	}
	tank_one_value = enemy[0].current_behaviour;
	tank_two_value = enemy[1].current_behaviour;
	tank_three_value = enemy[2].current_behaviour;
	tank_four_value = enemy[3].current_behaviour;
	tank_five_value = enemy[4].current_behaviour;
	
}

void yfacing(Tank* enemy, Tank* player)
{
	register int enemy_coord = enemy->y_coordinate;
	register int player_coord = player->y_coordinate;
	
	if(enemy_coord - player_coord < 0)
	{
		enemy->v_facing = DOWN;
	}
	else
	{
		enemy->v_facing = UP;
	}
	enemy->h_facing = VERTICAL;
}

void xfacing(Tank* enemy, Tank* player)
{
	register int enemy_coord = enemy->x_coordinate;
	register int player_coord = player->x_coordinate;
	if(enemy_coord - player_coord < 0)
	{
		enemy->h_facing = RIGHT;
	}
	else
	{
		enemy->h_facing = LEFT;
	}
	enemy->v_facing = HORIZONTAL;
}

BOOL playAlin(Tank* enemy, Tank* player)
{
	int xdifference = enemy->x_coordinate - player->x_coordinate;
	int ydifference = enemy->y_coordinate - player->y_coordinate;

	BOOL check1 = enemy->x_coordinate >= player->x_coordinate-16;
	BOOL check2 = enemy->x_coordinate <= player->x_coordinate+16;
	BOOL check3 = enemy->y_coordinate >= player->y_coordinate-16;
	BOOL check4 = enemy->y_coordinate <= player->y_coordinate+16;
	if(xdifference < 0)
	{
		xdifference *= -1;
	}
	if(ydifference < 0)
	{
		ydifference *= -1;
	}
	
	return ((check1 && check2)
			|| 
			(check3 && check4));
}

BOOL needTurn(Tank* enemy, Tank* player)
{
	BOOL check1 = enemy->x_coordinate >= player->x_coordinate-32;
	BOOL check2 = enemy->x_coordinate <= player->x_coordinate+32;
	BOOL check3 = enemy->v_facing == HORIZONTAL;
	BOOL check4 = enemy->y_coordinate >= player->y_coordinate-32;
	BOOL check5 = enemy->y_coordinate <= player->y_coordinate+32;
	BOOL check6 = enemy->h_facing == VERTICAL;

	return ((check1 && check2 
		&& check3) || 
		((check4 && check5) && check6));
}

BOOL yMove(Tank* enemy, Tank* player, int index)
{
	int loc = index;
	BOOL check1 = (enemy->y_coordinate - player->y_coordinate) < ((enemy->x_coordinate - player->x_coordinate) + 32);
	BOOL check2 = (enemy->y_coordinate - player->y_coordinate > 32);
	BOOL check3 = (enemy->y_coordinate - player->y_coordinate) > ((enemy->x_coordinate - player->x_coordinate)+32);
	BOOL check4 = (enemy->y_coordinate - player->y_coordinate < -32);
	
	return ((check1 && check2)
		||
		(check3	&& check4));
}


BOOL xMove(Tank* enemy, Tank* player, int index)
{
	int loc = index;
	BOOL check1 = (enemy->x_coordinate - player->x_coordinate) < ((enemy->y_coordinate - player->y_coordinate)-32);
	BOOL check2 = 1;/*(enemy->x_coordinate - player->x_coordinate > 32);*/
	BOOL check3 = (enemy->x_coordinate - player->x_coordinate) > ((enemy->y_coordinate - player->y_coordinate)+32);
	BOOL check4 = 1;/*(enemy->x_coordinate - player->x_coordinate < -32);*/
	
	return ((check1 && check2)
		||
		(check3 && check4));
}

	


/***************************************************************************
   Function Name:   missile_alive_x
  
   Purpose:         To see if there is any missiles
					in line with a tank
  
   Input Arguments: enemy 			- the enemy
					missile			- the missiles
					num_missiles	- The number of missiles
   
  
   Method Notes:    If there is a missile in line
					with the tank, then the tank will attempt to
					dodge
					

***************************************************************************/




BOOL missiles_alive_x(Tank *enemy, Missile* missile, int num_missiles)
{
	int index;
	for(index = 0; index < num_missiles && enemy->current_behaviour != DODGE_X; index++)
	{
		enemy->current_behaviour = dodge_x_check(enemy, &missile[index]);
	}
	if(enemy->current_behaviour == DODGE_X)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



/***************************************************************************
   Function Name:   missile_alive_y
  
   Purpose:         To see if there is any missiles
					in line with a tank
  
   Input Arguments: enemy 			- the enemy
					missile			- the missiles
					num_missiles	- The number of missiles
   
  
   Method Notes:    If there is a missile in line
					with the tank, then the tank will attempt to
					dodge
					

***************************************************************************/


BOOL missiles_alive_y( Tank *enemy, Missile* missile,int num_missiles)
{
	int index;
	for(index = 0; index < num_missiles && enemy->current_behaviour != DODGE_Y; index++)
	{
		enemy->current_behaviour = dodge_y_check(enemy, &missile[index]);
	}
	if(enemy->current_behaviour == DODGE_Y)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


























