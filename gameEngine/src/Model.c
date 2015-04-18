#include "Behavior.h"
#include "Missile.h"
#include "stdlib.h"
#include <osbind.h>
#include "System.h"
#include "Keyboard.h"
#include "assess.h"
#include "bitmaps.h"
#include "stdio.h"

#define TANK_OFFSET 4
#define COLLISION_OFFSET 45
#define MINIMUM_DISTANCE 32

BOOL yMoveP(Tank* enemy, Tank* player, char input);
BOOL xMoveP(Tank* enemy, Tank* player, char input);
BOOL playerCanMoveY(Tank* player, Tank* enemies, int num_enemies, char input);
BOOL playerCanMoveX(Tank* player,Tank* enemies, int num_enemies, char input);



/***************************************************************************
   Function Name:   playerCanMoveY
  
   Purpose:         looks at all the tanks around the player to check if the player can move in the y direction
  
   Input Arguments: Player 			- The Player
					Enemy 			- The enemies
					num_enimies		- The amount of enemies
					input			- What the player is pressing
  
   Method Notes:    It makes a run through of all the tanks on the field
					and makes sure that the player cannot run into any of them
   
   
***************************************************************************/

BOOL playerCanMoveY(Tank* player, Tank* enemies, int num_enemies, char input)
{
    UINT8 index;
	BOOL canMove = 1;
	for(index = 0; index < num_enemies && canMove; index++)
	{
		canMove = yMoveP(player,&enemies[index], input);
	}
    return canMove;
}


/***************************************************************************
   Function Name:   playerCanMoveX
  
   Purpose:         looks at all the tanks around the player to check if the player can move in the X direction
  
   Input Arguments: Player 			- The Player
					Enemy 			- The enemies
					num_enimies		- The amount of enemies
					input			- What the player is pressing
  
   Method Notes:    It makes a run through of all the tanks on the field
					and makes sure that the player cannot run into any of them
   
   
***************************************************************************/

BOOL playerCanMoveX(Tank* player,Tank* enemies, int num_enemies, char input)
{
	UINT8 index;
	BOOL canMove = 1;
	for(index = 0; index < num_enemies && canMove; index++)
	{
		canMove = xMoveP(player,&enemies[index], input);
	}
    return canMove;
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
	if((input == 'd' || input == 'a') && playerCanMoveX(player,enemy,num_enemies,input))
	{
		player->current_behaviour = MOVE_X;
		if(input == 'a')
		{
			player->h_facing = LEFT;
		}
		else
		{
			player->h_facing = RIGHT;
		}
		player->v_facing = HORIZONTAL;
	}
	else if((input == 'w' || input == 's') && playerCanMoveY(player,enemy,num_enemies,input))
	{
		player->current_behaviour = MOVE_Y;
		if(input == 'w')
		{
			player->v_facing = UP;
		}
		else
		{
			player->v_facing = DOWN;
		}
		player->h_facing = VERTICAL;
	}
	else if(input == ' ')
	{
		player->current_behaviour = SHOOT;
		player->is_firing = 1;
	}
	else if(die_check(player, missile, num_missiles))
	{
		player->hitpoints -= (getTime()%1000);
		if(player->hitpoints <= 0)
		{
			player->current_behaviour = DIE;
		}
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


void player_action(Tank* player, Missile* missile, int num_missiles)
{

	if(player->current_behaviour == MOVE_X && player->h_facing == RIGHT)
	{
		player->x_prev = player->x_coordinate;
		player->y_prev = player->y_coordinate;
		player->x_coordinate += TANK_OFFSET;
		player->sprite = playerTankEast;
	}
	else if(player->current_behaviour == MOVE_X && player->h_facing == LEFT)
	{
		player->x_prev = player->x_coordinate;
		player->y_prev = player->y_coordinate;
		player->x_coordinate -= TANK_OFFSET;
		player->sprite = playerTankWest;
	}
	else if(player->current_behaviour == MOVE_Y && player->v_facing == UP)
	{
		player->x_prev = player->x_coordinate;
		player->y_prev = player->y_coordinate;
		player->y_coordinate -= TANK_OFFSET;
		player->sprite = playerTankNorth;
	}
	else if(player->current_behaviour == MOVE_Y && player->v_facing == DOWN)
	{
		player->x_prev = player->x_coordinate;
		player->y_prev = player->y_coordinate;
		player->y_coordinate += TANK_OFFSET;
		player->sprite = playerTankSouth;
	}
	else if(player->current_behaviour == SHOOT)
	{
		missile_check(player, missile,num_missiles, 1);
		player->is_firing = 0;
	}
	player->current_behaviour = DO_NOTHING;
}



/***************************************************************************
   Function Name:   tank_respond
  
   Purpose:         Does an action based on the current behaviour it possesses
  
   Input Arguments: enemy 			- the enemies
					missile			- the missiles
					num_missiles	- The number of missiles
					num_tanks		- the number of tanks
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
					If the current behaviour is one of the TURN behaviours, the 
					tank will turn in that direction
   
   
   
   
***************************************************************************/




void tank_respond(Tank *enemy, Missile *missile, int num_missiles, int num_tanks)
{
	static long time;
	int index;
	BOOL missile_avail;
	int dodge_loc;
	int move_loc;
	int facing_x;
	int facing_y;
    
	for(index = 0; index < num_tanks; index++)
	{
		if(enemy[index].is_visible && enemy[index].current_behaviour != DO_NOTHING)
		{

			if(enemy[index].current_behaviour == SHOOT)
			{
				missile_avail = enemy[index].missile_available;
					
				
				if(getTime() >= time+700)
				{
					enemy[index].is_firing = 1;				
					missile_check(&enemy[index], missile, num_missiles,1);
					enemy[index].is_firing = 0;
					time = getTime();
				}
			}
			else if(enemy[index].current_behaviour == DODGE_X)
			{
				enemy[index].x_prev = enemy[index].x_coordinate;
				enemy[index].y_prev = enemy[index].y_coordinate;			
				dodge_loc = enemy[index].h_facing;
				dodge_x(&enemy[index], dodge_loc*TANK_OFFSET);
			}
			else if(enemy[index].current_behaviour == DODGE_Y)
			{
				dodge_loc = enemy[index].v_facing;
				dodge_y(&enemy[index],dodge_loc*TANK_OFFSET);
			}
			else if(enemy[index].current_behaviour == MOVE_X)
			{
				enemy[index].x_prev = enemy[index].x_coordinate;
				enemy[index].y_prev = enemy[index].y_coordinate;
				move_loc = enemy[index].h_facing;
				move_x(&enemy[index],move_loc*TANK_OFFSET);

			}
			else if(enemy[index].current_behaviour == MOVE_Y)
			{
				enemy[index].x_prev = enemy[index].x_coordinate;
				enemy[index].y_prev = enemy[index].y_coordinate;
				move_loc = enemy[index].v_facing;
				move_y(&enemy[index], move_loc*TANK_OFFSET);
			}
			else if(enemy[index].current_behaviour == DIE)
			{
				enemy[index].is_visible = 0;
				enemy[index].sprite = NULL;
				enemy[index].x_coordinate = -1;
				enemy[index].y_coordinate = -1;
			}
			else if(enemy[index].current_behaviour == TURN_UP)
			{
				enemy[index].h_facing = VERTICAL;
				enemy[index].v_facing = UP;
				enemy[index].sprite = playerTankNorth;
			}
			else if(enemy[index].current_behaviour == TURN_DOWN)
			{
				enemy[index].h_facing = VERTICAL;
				enemy[index].v_facing = DOWN;
				enemy[index].sprite = playerTankSouth;
			}
			else if(enemy[index].current_behaviour == TURN_LEFT)
			{
				enemy[index].h_facing = LEFT;
				enemy[index].v_facing = HORIZONTAL;
				enemy[index].sprite = playerTankWest;
			}
			else if(enemy[index].current_behaviour == TURN_RIGHT)
			{
				enemy[index].h_facing = RIGHT;
				enemy[index].v_facing = HORIZONTAL;
				enemy[index].sprite = playerTankEast;
			}
		}
		enemy[index].current_behaviour = DO_NOTHING;
	}

}


/***************************************************************************
   Function Name:   missile_check
  
   Purpose:         checks to see if there is an available missile for the tank to shoot,
					and if so fires out
  
   Input Arguments: tank			- The tank
					missile			- The missiles
					num_missiles	- The number of missiles
					num_tanks		- The number of tanks
  
   Method Notes:    Goes through each tank and checks if the
					tank is firing,
					
					If the tank is firing, then the missile will
					spawn in front of the tank, and move in the direction
					the tank was facing, it will ignore any tanks
					that were not firing.
   
   
   

***************************************************************************/



void missile_check(Tank *tank, Missile *missile, int num_missiles, int num_tanks)
{
	int index_missile;
	int index_tanks;
	BOOL finished_firing = 0;
	int right_check;
	for(index_tanks = 0; index_tanks < num_tanks; index_tanks++)
	{
		finished_firing = 0;
		for(index_missile = 0; index_missile < num_missiles && !finished_firing; index_missile++)
		{
			if(tank[index_tanks].is_firing && !missile[index_missile].is_visible)
			{
				if(tank[index_tanks].v_facing == UP)
				{
					missile[index_missile].sprite = player_missile;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate-COLLISION_OFFSET;
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].horizontal_movement = VERTICAL;
					missile[index_missile].vertical_movement = UP;
					missile[index_missile].current_behaviour = MOVE_UP;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing == LEFT)
				{
					missile[index_missile].sprite = player_missile;
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate-COLLISION_OFFSET;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].vertical_movement = HORIZONTAL;
					missile[index_missile].horizontal_movement = LEFT;
					missile[index_missile].current_behaviour = MOVE_LEFT;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].v_facing == DOWN)
				{
					missile[index_missile].sprite = player_missile;
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate + COLLISION_OFFSET;
					missile[index_missile].vertical_movement = DOWN;
					missile[index_missile].horizontal_movement = VERTICAL;
					missile[index_missile].current_behaviour = MOVE_DOWN;
					missile[index_missile].is_visible = 1;
					finished_firing = 1;
				}
				else if(tank[index_tanks].h_facing == RIGHT)
				{
					missile[index_missile].sprite = player_missile;
					missile[index_missile].x_coordinate = tank[index_tanks].x_coordinate+COLLISION_OFFSET;
					missile[index_missile].y_coordinate = tank[index_tanks].y_coordinate;
					missile[index_missile].vertical_movement = HORIZONTAL;
					missile[index_missile].horizontal_movement = RIGHT;
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
   
  
   Method Notes:	Checks the situation around the tanks in order for
					a proper responce to occur, and puts the correct sprite in
					for what it is now facing
					Case 1	  :	The player is firing and thus the tanks will have
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

	for(index = 0; index < num_enemies; index++)
	{
		tankBehav(&enemy[index],player, missile, num_missiles);
		if(enemy[index].v_facing == DOWN)
		{
			enemy[index].sprite = playerTankSouth;
		}
		else if(enemy[index].v_facing == UP)
		{
			enemy[index].sprite = playerTankNorth;
		}
		else if(enemy[index].h_facing == RIGHT)
		{
			enemy[index].sprite = playerTankEast;
		}
		else if(enemy[index].h_facing == LEFT)
		{
			enemy[index].sprite == playerTankWest;
		}

	}
	
}


/***************************************************************************
   Function Name:   yfacing
  
   Purpose:         check if the player tank is under the enemy tank
					if a move was successful
		
   Input Arguments: enemy 			- the enemy
					player			- the player

   
  
   Method Notes:    if the player tank is under the enemy tank,
					then the tank should face down
					
					otherwise, the tank should face up
					
					

***************************************************************************/
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


/***************************************************************************
   Function Name:   xfacing
  
   Purpose:         check if the player tank is under the enemy tank
					after a move was successful
  
   Input Arguments: enemy 			- the enemy
					player			- the player

   
  
   Method Notes:    if the player tank is right to the player tank,
					then the tank should face right
					
					otherwise, the tank should face left
					
					

***************************************************************************/
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



/***************************************************************************
   Function Name:   playAlinHorizontal
  
   Purpose:         check if the player tank is right or left to the enemy if
					a move was not successful
  
   Input Arguments: enemy 			- the enemy
					player			- the player

   
  
   Method Notes:    if the player tank is right to the player tank,
					then the tank should face right
					
					otherwise, the tank should face left
					
					

***************************************************************************/



BOOL playAlinHorizontal(Tank* enemy, Tank* player)
{
	BOOL correct;

	BOOL check1 = enemy->y_coordinate >= player->y_coordinate-16;
	BOOL check2 = enemy->y_coordinate <= player->y_coordinate+16;
	if(check1 && check2)
	{

		if(enemy->x_coordinate - player->x_coordinate > 0)
		{
			enemy->h_facing = RIGHT;
		}
		else
		{
			enemy->h_facing = LEFT;
		}
		enemy->v_facing = HORIZONTAL;
		correct = 1;
	}
	else
	{
		correct = 0;
	}
	
	
	return correct;
}


/***************************************************************************
   Function Name:   playAlinVertical
  
   Purpose:         check if the player tank is above or under to the enemy if
					a move was not successful
  
   Input Arguments: enemy 			- the enemy
					player			- the player

   
  
   Method Notes:    if the player tank is right to the player tank,
					then the tank should face right
					

					
					

***************************************************************************/

BOOL playAlinVertical(Tank* enemy, Tank* player)
{
	BOOL correct;

	BOOL check1 = enemy->x_coordinate >= player->x_coordinate-16;
	BOOL check2 = enemy->x_coordinate <= player->x_coordinate+16;
	if(check1 && check2)
	{
		if(enemy->y_coordinate - player->y_coordinate < 0)
		{
			enemy->v_facing = UP;
		}
		else
		{
			enemy->v_facing = DOWN;
		}
		enemy->h_facing = HORIZONTAL;
		correct = 1;
	}
	else
	{
		correct = 0;
	}
	
	
	return correct;
}

/***************************************************************************
   Function Name:   needTurnRight
  
   Purpose:         to see if the enemy needs to turn right in order
					for it to face the player
  
   Input Arguments: enemy 			- the enemy
					player			- the player

   
  
   Method Notes:    if the enemy isn't facing the player 
					then the enemy needs to move to face the player
					in order to fire
					

					

***************************************************************************/


BOOL needTurnRight(Tank* enemy, Tank* player)
{
	if(enemy->x_coordinate-player->x_coordinate < 0
		&& ((enemy->x_coordinate-player->x_coordinate <
		   enemy->y_coordinate-player->y_coordinate)
		||
		   (enemy->x_coordinate-player->x_coordinate <
		    player->y_coordinate-enemy->y_coordinate)
		   ))
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
	
}

/***************************************************************************
   Function Name:   needTurnLeft
  
   Purpose:         to see if the enemy needs to turn left in order
					for it to face the player
  
   Input Arguments: enemy 			- the enemy
					player			- the player

   
  
   Method Notes:    if the enemy isn't facing the player 
					then the enemy needs to move to face the player
					in order to fire
					
***************************************************************************/


BOOL needTurnLeft(Tank* enemy, Tank* player)
{
	if(enemy->x_coordinate-player->x_coordinate > 0 /* if the enemy is to the left of the player*/
	  && ((enemy->x_coordinate-player->x_coordinate < 
		  enemy->y_coordinate-player->y_coordinate) /* and the enemy is closer on x than on y */
	  ||  enemy->x_coordinate-player->x_coordinate <
		  player->y_coordinate-enemy->y_coordinate))
	 {
		return 1;
	 }
	 else
	 {
		return 0;
	 }
	 
}


/***************************************************************************
   Function Name:   needTurnUp
  
   Purpose:         to see if the enemy needs to face up so it
					can face the player in order to fire
  
   Input Arguments: enemy 			- the enemy
					player			- the player

   
  
   Method Notes:    if the enemy isn't facing the player 
					then the enemy needs to move to face the player
					in order to fire
					
***************************************************************************/

BOOL needTurnUp(Tank* enemy, Tank* player)
{
	if(enemy->y_coordinate-player->y_coordinate > 0	/*if the player is above the enemy*/
	 && ((enemy->y_coordinate-player->y_coordinate <
		  enemy->x_coordinate-player->x_coordinate)/* and the enemy is closer the player on the y axis*/
	 ||
		enemy->y_coordinate-player->y_coordinate <
		player->x_coordinate-enemy->y_coordinate))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/***************************************************************************
   Function Name:   needTurnDown
  
   Purpose:         to see if the enemy needs to face up so it
					can face the player in order to fire
  
   Input Arguments: enemy 			- the enemy
					player			- the player

   
  
   Method Notes:    if the enemy isn't facing the player 
					then the enemy needs to move to face the player
					in order to fire
					
***************************************************************************/


BOOL needTurnDown(Tank* enemy, Tank* player)
{
	if(enemy->y_coordinate-player->y_coordinate < 0 /*if the player is under the enemy*/
	&& ((enemy->y_coordinate-player->y_coordinate <
		enemy->x_coordinate-player->x_coordinate)/* and the player is closer to the enemy on the y axis*/
	||
		enemy->y_coordinate-player->y_coordinate <
		player->x_coordinate-enemy->x_coordinate))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/***************************************************************************
   Function Name:   xMove
  
   Purpose:        move the tank in the x_direction, while also figuring out where
					the player is and moving accordingly without colliding with the player
  
   Input Arguments: enemy 			- the enemy
					player			- the player

   
  
   Method Notes:    Once the enemy determines that it is in its own
					best interest to move in the x direction, the 
					enemy will figure out where it is in relation to
					the player tank.
					
					If it is already close enough to the player tank, 
					then the enemy tank will not move as the player tank
					is already within its sights
					
					once it determines what direction it needs to go,
					then it faces that direction and moves that direction.
					
***************************************************************************/


BOOL xMove(Tank* enemy, Tank* player)
{
	register int check1 = (enemy->y_coordinate - player->y_coordinate);
	register int check2 = (enemy->x_coordinate - player->x_coordinate);
	register BOOL check3;
	BOOL check4;
	BOOL check5;
	BOOL check6;
	BOOL check7;
	BOOL check8;
	check4 = check1 > MINIMUM_DISTANCE;/* The enemy is to the right of the player */
	check5 = check1 < -MINIMUM_DISTANCE;/* The enemy is to the left of the player */
	check6 = check1 < MINIMUM_DISTANCE;/* the enemy isn't too close to the player */
	check7 = check1 > -MINIMUM_DISTANCE;

	
    if(enemy->x_coordinate-player->x_coordinate > MINIMUM_DISTANCE) /* if the player is to the left of the enemy*/
    {
		check3 = ((check4 || check5)/* If the player is not alligned aligned with the enemy*/
        ||
            (check6 && check7/* or the player alligned with the enemy but the player is suffiently below or above the enemy*/
              && (enemy->x_coordinate-MINIMUM_DISTANCE > player->x_coordinate || player->x_coordinate-28 > enemy->x_coordinate)))
			  && (enemy->x_coordinate > MINIMUM_DISTANCE);/*and the tank isn't going to run off the screen*/		
        if(check3)
        {
			enemy->v_facing = HORIZONTAL;
			enemy->h_facing = LEFT;
			
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(enemy->x_coordinate-player->x_coordinate < -MINIMUM_DISTANCE) /* if the player is to the right of the enemy*/
    {
		check3 = ((check4 || check5)/* If the player is not alligned aligned with the enemy*/
        ||
            (check6 && check7/* or the player alligned with the enemy but the player is suffiently below or above the enemy*/
              && (enemy->x_coordinate+MINIMUM_DISTANCE < player->x_coordinate || player->x_coordinate+28 < enemy->x_coordinate)))
			  && (enemy->x_coordinate < 608);	/*and the tank isn't going to run off the screen*/			
        if(check3)
        {
			enemy->v_facing = HORIZONTAL;
			enemy->h_facing = RIGHT;
            return 1;
        }
        else
        {
            return 0;
        }
    }
	else
	{
		return 0;
	}
    

}


/***************************************************************************
   Function Name:   xMove
  
   Purpose:        move the tank in the y direction, while also figuring out where
					the player is and moving accordingly without colliding with the player
  
   Input Arguments: enemy 			- the enemy
					player			- the player

   
  
   Method Notes:    Once the enemy determines that it is in its own
					best interest to move in the y direction, the 
					enemy will figure out where it is in relation to
					the player tank.
					
					If it is already close enough to the player tank, 
					then the enemy tank will not move as the player tank
					is already within its sights
					
					once it determines what direction it needs to go,
					then it faces that direction and moves that direction.
					
***************************************************************************/


BOOL yMove(Tank* enemy, Tank* player)
{
	register long check1 = (long)(enemy->y_coordinate - player->y_coordinate);
	register long check2 = (long)(enemy->x_coordinate - player->x_coordinate);
	register long check3;
	BOOL check4;
	BOOL check5;
	BOOL check6;
	BOOL check7;
	BOOL check8;
	check4 = check2 > MINIMUM_DISTANCE;/* The enemy is below the player*/
	check5 = check2 < -MINIMUM_DISTANCE;/*The enemy is above the player*/
	check6 = check2 < MINIMUM_DISTANCE;/* The enemy is alligned with the player*/
	check7 = check2 > -MINIMUM_DISTANCE;

    
    if(enemy->y_coordinate-player->y_coordinate > MINIMUM_DISTANCE)
    {
		check3 = ((check4 || check5)/* If the player is not alligned aligned with the enemy*/
        ||
            (check6 && check7/* or the player alligned with the enemy but the player is suffiently below or above the enemy*/
              && (enemy->y_coordinate-MINIMUM_DISTANCE > player->y_coordinate || player->y_coordinate-28 > enemy->y_coordinate)))
			  && (enemy->y_coordinate > MINIMUM_DISTANCE) ;	/*and the tank isn't going to run off the screen*/	

        if(check3)
        {
			enemy->v_facing = UP;
			enemy->h_facing = VERTICAL;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if(enemy->y_coordinate-player->y_coordinate < -MINIMUM_DISTANCE)
    {
		check3 = ((check4 || check5)/* If the player is not alligned aligned with the enemy*/
        ||
            (check6 && check7/* or the player alligned with the enemy but the player is suffiently below or above the enemy*/
              && (enemy->y_coordinate+MINIMUM_DISTANCE < player->y_coordinate || player->y_coordinate+28 < enemy->y_coordinate)))
			  && (enemy->y_coordinate < 350);/*and the tank isn't going to run off the screen*/	
    
		
        if(check3)
        {
			enemy->v_facing = DOWN;
			enemy->h_facing = VERTICAL;
            return 1;
        }
        else
        {
            return 0;
        }
    }
	else
	{
		return 0;
	}


        
 }


 /***************************************************************************
   Function Name:   xMoveP
  
   Purpose:        What makes the player move based on the players input
  
   Input Arguments: enemy 			- the enemy
					player			- the player
					input			- what the player pressed

   
  
   Method Notes:    				The player tank responds to what
									behaviour it should take depending
									the players input, if it is an invalid
									input, then the tank will not respond to
									the player input
					
***************************************************************************/
 
 
 /***************************************************************************
   Function Name:   yMoveP
  
   Purpose:        What makes the player move based on the players input
  
   Input Arguments: enemy 			- the enemy
					player			- the player
					input			- what the player pressed

   
  
   Method Notes:    				The player tank responds to what
									behaviour it should take depending
									the players input, if it is an invalid
									input, then the tank will not respond to
									the player input
					
***************************************************************************/
 
 
BOOL yMoveP(Tank* player, Tank* enemy, char input)
{
	register long check1 = (long)(player->y_coordinate - enemy->y_coordinate);
	register long check2 = (long)(player->x_coordinate - enemy->x_coordinate);
	register long check3;
	BOOL check4;
	BOOL check5;
	BOOL check6;
	BOOL check7;
	BOOL check8;
	check4 = check2 > MINIMUM_DISTANCE;/* the player is to the right of the enemy */
	check5 = check2 < -MINIMUM_DISTANCE;/* the player is to the left of the enemy */
	check6 = check2 < MINIMUM_DISTANCE;/* the player is alligned with the enemy*/
	check7 = check2 > -MINIMUM_DISTANCE;
	
    if(input != 'w' && input != 's')
    {
        return 0;
    }
    
    
    if(input == 'w')
    {
		check3 = ((check4 || check5)/* if the player isn't alligned with the enemy */
        ||
            (check6 && check7/* or the player alligned with the enemy but the enemy is suffiently below or above the player*/
              && (player->y_coordinate-MINIMUM_DISTANCE > enemy->y_coordinate || enemy->y_coordinate-28 > player->y_coordinate)))
			  && (player->y_coordinate > MINIMUM_DISTANCE) ;

        if(check3)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
		check3 = ((check4 || check5)/*if the player isn't alligned with the enemy*/
        ||
            (check6 && check7/* or the player alligned with the enemy but the enemy is suffiently below or above the player*/
              && (player->y_coordinate+MINIMUM_DISTANCE < enemy->y_coordinate || enemy->y_coordinate+28 < player->y_coordinate)))
			  && (player->y_coordinate < 350);
    
		
        if(check3)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }


        
 }





 
BOOL xMoveP(Tank* enemy, Tank* player, char input)
{
	register int check1 = (enemy->y_coordinate - player->y_coordinate);
	register int check2 = (enemy->x_coordinate - player->x_coordinate);
	register BOOL check3;
	BOOL check4;
	BOOL check5;
	BOOL check6;
	BOOL check7;
	BOOL check8;
	check4 = check1 > MINIMUM_DISTANCE;/* the enemy is to the right of the player*/
	check5 = check1 < -MINIMUM_DISTANCE;/* the enemy is to the left of the player */
	check6 = check1 < MINIMUM_DISTANCE;/* the player is alligned with the enemy */
	check7 = check1 > -MINIMUM_DISTANCE;
	
    if(input != 'a' && input != 'd')
    {
        return 0;
    }
    if(input == 'a')
    {
		check3 = ((check4 || check5)/*if the player isn't alligned with the enemy*/
        ||
            (check6 && check7/* or the player alligned with the enemy but the enemy is suffiently below or above the player*/
              && (enemy->x_coordinate-MINIMUM_DISTANCE > player->x_coordinate || player->x_coordinate-28 > enemy->x_coordinate)))
			  && (enemy->x_coordinate > MINIMUM_DISTANCE);		
        if(check3) 
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
		check3 = ((check4 || check5)
        ||
            (check6 && check7/*if the player isn't alligned with the enemy*/
              && (enemy->x_coordinate+MINIMUM_DISTANCE < player->x_coordinate || player->x_coordinate+28 < enemy->x_coordinate)))
			  && (enemy->x_coordinate < 608);/* or the player alligned with the enemy but the enemy is suffiently below or above the player*/			
        if(check3)
        {
            return 1;
        }
        else
        {
            return 0;
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


























