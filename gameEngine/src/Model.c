#include "model.h"
#include "Behavior.h"
#include "Missile.h"
#include "stdlib.h"
#include <osbind.h>
#include "System.h"
#include "Keyboard.h"



/* Not really needed, but I'll keep it in anyway
int main()
{
	Tank player;
	Tank enemy[3];
	Missile missile[10];
	Stationary_Object object[10];
	int num_objects = 10;
	int initial_offset = 100;
	int index;
	int number_of_enemies = 3;
	char input = '\0';
	BOOL done = 0;
	long time_now;
	
	time_now = getTime();
	
	player.x_coordinate = 250;
	player.y_coordinate = 250;
	player.hitpoints = 100;
	player.current_speed = 0;
	player.is_moving = 0;
	player.is_firing = 0;
	player.sprite = NULL;
	player.x_posMask = 0;
	player.y_posMask = 0;
	player.h_facing = VERTICAL;
	player.v_facing = DOWN;
	player.is_visible = 1;
	player.current_behaviour = DO_NOTHING;
	player.is_firing = 0;
	player.missile_available = 2;
	player.x_find = "X_find\r\n\0";
	player.y_find = "Y_find\r\n\0";
	player.end_coords = "end_coords\r\n\0";
	
	for(index = 0; index < number_of_enemies; index++)
	{
		enemy[index].x_coordinate = initial_offset;
		enemy[index].y_coordinate = 100;
		enemy[index].hitpoints = 100;
		enemy[index].current_speed = 0;
		enemy[index].is_moving = 0;
		enemy[index].is_firing = 0;
		enemy[index].sprite = NULL;
		enemy[index].x_posMask = 0;
		enemy[index].y_posMask = 0;
		enemy[index].h_facing = VERTICAL;
		enemy[index].v_facing = DOWN;
		enemy[index].is_visible = 1;
		enemy[index].current_behaviour = DO_NOTHING;
		enemy[index].is_firing = 0;
		enemy[index].x_find = "X_find\r\n\0";
		enemy[index].y_find = "Y_find\r\n\0";
		enemy[index].end_coords = "end_coords\r\n\0";
		initial_offset += 32;
	}
	
	thing();
	while(!done && input != 'q')
	{
		if(DSconis() && getTime() >= time_now+10)
		{
			time_now = getTime();
			DSconws("Got in \r\n\0");
			input = DSnecin();
			if(input == 'd')
			{
				DSconws("Player pressed \"d\"\r\n\n\0");
			}
			else if(input == 's')
			{
				DSconws("Player pressed \"s\"\r\n\n\0");
			}
			else if(input == 'a')
			{
				DSconws("Player pressed \"a\"\r\n\n\0");
			}
			else if(input == 'w')
			{
				DSconws("Player pressed \"d\"\r\n\n\0");
			}
			else if(input == 'q')
			{
				DSconws("Player pressed \"q\"\r\n\n\0");
				done = 1;
			}
		}
		else if(!DSconis() && getTime() >= time_now+10)
		{
			time_now = getTime();
			DSconws("No input\r\n\0");
			assess_situation(enemy, &player, object, missile, 10, 0);
			tank_respond(enemy, missile, 10, number_of_enemies, object, num_objects);
		}
	}
	
	DSconout(input);
	DSconws("\r\n\0");
	
	
	
	return 0;
}
*/


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
	static int time_now;
	time_now = getTime();
	if(input_valid)
	{
/*		input = DSnecin();*/
		player_action_check(player, 
		enemy, 
		num_enemies, 
		input, 
		missile, 
		num_missiles);
		if(getTime() >= time_now+10)
		{
			player_action(player,missile,input);
			time_now = getTime();
		}
	}
	assess_situation(enemy, player, object, missile, num_enemies, num_missiles);
	if(getTime() >= time_now+10)
	{
		tank_respond(enemy, missile, num_missiles, num_enemies, object, num_objects);
		time_now = getTime();
	}
	
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



void tank_respond(Tank *enemy, Missile *missile, int num_missiles, int num_tanks, Stationary_Object *object, int num_objects)
{
	int index;
	for(index = 0; index < num_tanks; index++)
	{
		if(enemy[index].is_visible && !enemy[index].current_behaviour == DO_NOTHING)
		{
			if(enemy[index].current_behaviour == SHOOT)
			{
				missile_check(&enemy[index], missile, enemy[index].missile_available, 1);
				enemy[index].is_firing = 0;
				DSconws("shooting\r\n\0");
			}
			else if(enemy[index].current_behaviour == DODGE_X)
			{
				dodge_x(&enemy[index], object, &(enemy[index].h_facing), num_objects);
				DSconws("Dodging x\r\n\0");
			}
			else if(enemy[index].current_behaviour == DODGE_Y)
			{
				dodge_y(&enemy[index], object, 
										&(enemy[index].v_facing), num_objects);
				DSconws("Dodging y\r\n\0");
			}
			else if(enemy[index].current_behaviour == MOVE_X)
			{
				move_x(&enemy[index], object,enemy[index].h_facing, 
					   
					   
					   num_objects);
				
				
				DSconws("Moving x\r\n\0");
			}
			else if(enemy[index].current_behaviour == MOVE_Y)
			{
				move_y(&enemy[index], object, enemy[index].v_facing, num_objects);
				DSconws("Moving y\r\n\0");
			}
			else if(enemy[index].current_behaviour == DIE)
			{
				enemy[index].is_visible == 0;
				DSconws("Dying\r\n\0");
			}
			else if(enemy[index].current_behaviour == TURN)
			{
				turn(&enemy[index]);
				DSconws("Turning\r\n\0");
			}
		}

	}
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


void assess_situation(Tank enemy[], Tank *player, Stationary_Object *object, Missile* missile, int num_enemies, int num_missiles)
{
	int index;
	DSconws("Im in assess_situation \r\n\0");
	for(index = 0; index < num_enemies; index++)
	{
		if(player->is_firing) /* Case One */
		{
			enemy[index].current_behaviour = 
			missile_fired(&enemy[index], 
			missile, 
			&num_missiles);
			DSconws("Player is fireing\r\n\0");
		}
		else if(missiles_alive_x(&enemy[index],
									missile, 
									num_missiles))/* Case Two */
		{
			enemy[index].current_behaviour = DODGE_X;
			DSconws("Dodge x\r\n\0");
		}
		else if(missiles_alive_y(&enemy[index], 
									missile, 
									num_missiles))
		{
			enemy[index].current_behaviour = DODGE_Y; /* Case Three */
			DSconws("Dodge y\r\n\0");
		}
		else if((enemy[index].x_coordinate >= player->x_coordinate-8
		&&enemy[index].x_coordinate <= player->x_coordinate+8)
		|| 
		(enemy[index].y_coordinate >= player->y_coordinate-8
		&& enemy[index].y_coordinate <= player->y_coordinate+8)) /* Case 4*/
		{
			enemy[index].current_behaviour = SHOOT;
			DSconws("Shoot \r\n\0");
		}
		else if(((enemy[index].x_coordinate >= player->x_coordinate-16
		&& enemy[index].x_coordinate <= player->x_coordinate+16) 
		&& enemy[index].v_facing == HORIZONTAL) || 
		((enemy[index].y_coordinate >= player->y_coordinate-16
		&&enemy[index].y_coordinate <= player->y_coordinate+16) && enemy[index].h_facing == VERTICAL)) /* Case 5*/
		{
			enemy[index].current_behaviour = TURN;
			DSconws("Turn \r\n\0");
		}
		else if(((enemy[index].y_coordinate - player->y_coordinate) < ((enemy[index].x_coordinate - player->x_coordinate) + 16)
		&& (enemy[index].y_coordinate - player->y_coordinate > 16))
		||
		((enemy[index].y_coordinate - player->y_coordinate) > ((enemy[index].x_coordinate - player->x_coordinate)+16)/* Case 6 */
		&& (enemy[index].y_coordinate - player->y_coordinate < -16)))
		{
			enemy[index].current_behaviour = MOVE_Y;
			DSconws("Move y\r\n\0");
		}
		else if(((enemy[index].x_coordinate - player->x_coordinate) < ((enemy[index].y_coordinate - player->y_coordinate)-16) /*Check to see if the player should move in the x direction because it's y offset is greater than it's x offset */
		&& (enemy[index].x_coordinate - player->x_coordinate > 16))
		||
		((enemy[index].x_coordinate - player->x_coordinate) > ((enemy[index].y_coordinate - player->y_coordinate)+16)/* Case 7*/
		&& (enemy[index].x_coordinate - player->x_coordinate < -16)))
		{
			enemy[index].current_behaviour = MOVE_X;
			DSconws("move x\r\n\0");
		}
		else if(die_check(&enemy[index], missile, num_missiles))/*Case 8 */
		{
			enemy[index].current_behaviour = DIE;
			DSconws("Die \r\n\0");
		}
		else/* Case 9 */
		{
			enemy[index].current_behaviour = DO_NOTHING;
			DSconws("Nuttun\r\n\0");
		}
	}
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


























