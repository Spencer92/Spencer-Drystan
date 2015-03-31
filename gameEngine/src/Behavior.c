#include "Behavior.h"
#include "Model.h"
#include "osbind.h"



/***************************************************************************
   Function Name:   die_check
  
   Purpose:         To check if the tank should die because a missile hit it
  
   Input Arguments: Tank - The tank that will be dying
					Missile - What will do the killing
  
   Return Value:    The Behaviour that the tank should take
  
   Method Notes:    If the tank is in the same place as the missile, 
					then it will be told to die
					
				If not then the current behaviour will just be used
***************************************************************************/

BOOL die_check(Tank *enemy, Missile *missile, int num_missiles)
{
	int index;
	for(index = 0; index < num_missiles; index++)
	{
		if((enemy->x_coordinate >= missile[index].x_coordinate-16
		&& enemy->x_coordinate <= missile[index].x_coordinate+16) 
		&& 
		(enemy->y_coordinate >= missile[index].y_coordinate-16
		&& enemy->y_coordinate <= missile[index].y_coordinate+16))
		{
			missile[index].is_visible = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}
}



/***************************************************************************
   Function Name:   respawn
  
   Purpose:         To respawn the tank after it dies
  
   Input Arguments: Tank - The tank that will be respawned
  
***************************************************************************/

void respawn(Tank *tank)
{
	tank->is_visible = 1;
}


/***************************************************************************
   Function Name:   die
  
   Purpose:         To kill off the tank
  
   Input Arguments: Tank - The tank that will be killed
   
   Method notes: by setting is_visible, is_firing, and is_moving to false,
				it will be ignored by any missile, tank, or other object.
  
***************************************************************************/


void die(Tank *tank)
{
	tank->is_visible = 0;
	tank->is_firing = 0;
	tank->is_moving = 0;
}

/***************************************************************************
   Function Name:   shoot
  
   Purpose:         To fire a missile to another tank
  
   Input Arguments: Tank - the tank that will be firing the missile
					Missile - The missile to be fired
  
   Method Notes:    The tank checks the amount of missiles it has, and
					if it has a missile to fire, the missile will become visible
					and the amount of missiles the tank has will be decreased
					the tank will also set its "firing" attribute to "true" (also known as "1")
					
					If the tank does not have a missile to fire, it will
					set its firing attribute to "false" (also known as "0")
					
***************************************************************************/


void shoot(Tank *tank, Missile *missile)
{
	if(tank->missile_available > 0)
	{
		tank->is_firing = 1;
		tank->missile_available--;
		missile->is_visible = 1;
	}
	else
	{
		tank->is_firing = 0;
		Cconws("I cannot fire!\r\n\0");
	}
}


/***************************************************************************
   Function Name:   turn
  
   Purpose:         To turn left
  
   Input Arguments: Tank - The tank that is going to turn left
***************************************************************************/


void turn(Tank *tank)
{
	/*TODO change sprite for tank */
	switch(tank->h_facing)
	{
		case VERTICAL:
			tank->h_facing = LEFT;
			tank->v_facing = HORIZONTAL;
			break;
		case LEFT:
			tank->h_facing = VERTICAL;
			tank->v_facing = UP;
		case RIGHT:
			tank->h_facing = VERTICAL;
			tank->v_facing = DOWN;
		default:
			break;
	}

}

/***************************************************************************
   Function Name:   dodge_x
  
   Purpose:         To dodge something 
  
   Input Arguments: Tank: The tank that is dodging
					Object: An object that can be dodged
					Direction: 
  
   Method Notes:    The tank takes a random number, and uses that random number
					to determine if the tank is going to dodge left or right
***************************************************************************/

void dodge_x(Tank *tank, Stationary_Object *object, int direction, int num_objects)
{

	if(flip(tank->x_coordinate))
	{
		move_x(tank, object, direction, num_objects);
	}
	else
	{
		move_x(tank, object, direction *-1, num_objects);
	}


}

/***************************************************************************
   Function Name:   dodge_y
  
   Purpose:         To dodge something 
  
   Input Arguments: Tank: The tank that is dodging
					Object: An object that can be dodged
					Direction: 
  
   Method Notes:    The tank takes a random number, and uses that random number
					to determine if the tank is going to dodge up or down
***************************************************************************/

void dodge_y(Tank *tank, Stationary_Object *object, int direction, int num_objects)
{
	if(flip(tank->y_coordinate))
	{
		move_y(tank, object, direction, num_objects);
	}
	else
	{
		move_y(tank, object, direction * -1, num_objects);
	}
	
}

/***************************************************************************
   Function Name:   missile_fired
  
   Purpose:         To tell a tank to dodge an incoming missile
  
   Input Arguments: Tank - The tank that will be dodging
					Missile - The missile that the tank will dodge
  
   Return Value:    The Behaviour that the tank should take
  
   Method Notes:    If the tank is either vertically or horizontally alligned
					with the missile being fired, a command to dodge will
					be sent to the tank.
					
					If not then the current behaviour will just be used
***************************************************************************/

BEHAVIOUR missile_fired(Tank *tank, Missile *missile, int* num_missiles)
{
	int index;
	for(index = 0; index < *num_missiles; index++)
	{
		if(tank->x_coordinate >= missile[index].x_coordinate + 8
			&& tank->x_coordinate <= missile[index].x_coordinate - 8) /*TODO figure out way to check if the missile is coming towards them without killing time*/
		{
			return DODGE_X;
		}
		else if(tank->y_coordinate >= missile[index].y_coordinate + 8
				&& tank->y_coordinate <= missile[index].y_coordinate - 8)
		{
			return DODGE_Y;
		}
	}

	return tank->current_behaviour;
	

}


/***************************************************************************
   Function Name:   move_check_x
  
   Purpose:         To tell the tank to move depending on whether the player is closer in the x direction
					than in the y direction
  
   Input Arguments: Tank - The tank that will be going toward the player
					Player - The player
					Direction - the direction that the tank will be moving (either left or right)
  
   Return Value:    The Behaviour that the tank should take
  
   Method Notes:    If the play is closer in the x direction than it
					is in the y direction, the tank will check to
					see if it should move left or right, and act accordingly
					
					If not then the current behaviour will just be used
***************************************************************************/

BEHAVIOUR move_check_x(Tank *enemy, Tank *player, int *direction)
{
	register int x_coordinate_enemy = enemy->x_coordinate;
	register int x_coordinate_player = player->x_coordinate;
	register int y_coordinate_enemy = enemy->y_coordinate;
	register int y_coordinate_player = player->y_coordinate;
	
	if(((x_coordinate_enemy - x_coordinate_player) < ((y_coordinate_enemy - y_coordinate_player)-16) /*Check to see if the player should move in the x direction because it's y offset is greater than it's x offset */
		&& (x_coordinate_enemy - x_coordinate_player > 16))
		||
		((x_coordinate_enemy - x_coordinate_player) > ((y_coordinate_enemy - y_coordinate_player)+16)
		&& (x_coordinate_enemy - x_coordinate_player < -16)))
	{
		if(player->x_coordinate - enemy->x_coordinate < -16) /*if the tank isn't lined up with the player to make a shot */
		{
			*direction = -1;
		}
		else if(player->x_coordinate - enemy->x_coordinate > 16) /*if the tank isn't lined up with the player to make a shot*/
		{
			*direction = 1;
		}
		else
		{
			return enemy->current_behaviour;
		}
		return MOVE_X;
	}
	else
	{
		return enemy->current_behaviour;
	}
} 


/***************************************************************************
   Function Name:   move_check_y
  
   Purpose:         To tell the tank to move depending on whether the player is closer in
					the y position than is in the x position
  
   Input Arguments: Tank - The tank that will be dodging
					Player - the player
					Direction - The direction the tank needs to move (up or down)
  
   Return Value:    The Behaviour that the tank should take
  
   Method Notes:    If the tank is closer in the y direction than in the x direction
					the tank will move in the y direction either up or down
					depending on where the player is located
					
					If not then the current behaviour will just be used
***************************************************************************/


BEHAVIOUR move_check_y(Tank *enemy, Tank *player, int *direction)
{
	register int x_coordinate_enemy = enemy->x_coordinate;
	register int x_coordinate_player = player->x_coordinate;
	register int y_coordinate_enemy = enemy->y_coordinate;
	register int y_coordinate_player = player->y_coordinate;
	
	if(((y_coordinate_enemy - y_coordinate_player) < ((x_coordinate_enemy - x_coordinate_player) + 16)
		&& (y_coordinate_enemy - y_coordinate_player > 16))
		||
		((y_coordinate_enemy - y_coordinate_player) > ((x_coordinate_enemy - x_coordinate_player)+16)
		&& (y_coordinate_enemy - y_coordinate_player < -16)))
	{
		if(enemy->y_coordinate - player->y_coordinate < -16)
		{
			*direction = 1;
		}
		else if(enemy->y_coordinate - player->y_coordinate > 16)
		{
			*direction = -1;
		}
		else
		{
			return enemy->current_behaviour;
		}
		return MOVE_Y;
	}
	else
	{
		return enemy->current_behaviour;
	}
}

BEHAVIOUR move_check_player(Tank *enemy, Tank *player, char input)
{
	if(input == 'a' && player->x_coordinate > enemy->x_coordinate + 16)
	{
		player->h_facing = LEFT;
		player->v_facing = HORIZONTAL;
		return MOVE_X;
	}
	else if(input == 'd' && player->x_coordinate < enemy->x_coordinate - 16)
	{
		player->h_facing = RIGHT;
		player->v_facing = HORIZONTAL;
		return MOVE_X;
	}
	else if(input == 'w' && player->y_coordinate < enemy->y_coordinate - 16)
	{
		player->h_facing = VERTICAL;
		player->v_facing = UP;
		return MOVE_Y;
	}
	else if(input == 's' && player->y_coordinate > enemy->y_coordinate + 16)
	{
		player->h_facing = VERTICAL;
		player->v_facing = DOWN;
		return MOVE_Y;
	}	
	else
	{
		return player->current_behaviour;
	}
}
/***************************************************************************
   Function Name:   die_check
  
   Purpose:         To check if the tank should die because a missile hit it
  
   Input Arguments: Tank - The tank that will be dying
					Missile - What will do the killing
  
   Return Value:    The Behaviour that the tank should take
  
   Method Notes:    If the tank is in the same place as the missile, 
					then it will be told to die
					
				If not then the current behaviour will just be used
***************************************************************************/
/*
BOOL die_check02(Tank *enemy, Missile *missile, int num_missiles)
{
	int index;
	if(index = 0; index < num_missiles; index++)
	{
		if((enemy->x_coordinate >= missile[index]->x_coordinate-16
			&& enemy->x_coordinate <= missile[index]->x_coordinate+16) 
			&& 
			(enemy->y_coordinate >= missile[index]->y_coordinate-16
			&& enemy->y_coordinate <= missile[index]->y_coordinate+16))
		{
			missile->is_visible = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}
}
*/

/***************************************************************************
   Function Name:   shoot_check
  
   Purpose:         To check to see if a tank can fire a missile
  
   Input Arguments: enemy - the tank that will be firing
					player - the tank that is being fired on
					missile - the missile to be fired
  
   Return Value:    The Behaviour that the tank should take
  
   Method Notes:    If the tank is either on the same x or y of the player
					then the tank will be told to fire the missile at the player
					
					If not then the current behaviour will just be used
***************************************************************************/


BEHAVIOUR shoot_check(Tank *enemy, Tank *player, Missile *missile)
{
	if((enemy->x_coordinate >= player->x_coordinate-8
		&&enemy->x_coordinate <= player->x_coordinate+8)
		|| 
		(enemy->y_coordinate >= player->y_coordinate-8
		&& enemy->y_coordinate <= player->y_coordinate+8))
	{
		return SHOOT;
	}
	else
	{
		return enemy->current_behaviour;
	}
}

/***************************************************************************
   Function Name:   shoot_check
  
   Purpose:         To check to see if a tank can fire a missile
  
   Input Arguments: enemy - the tank that will be firing
					player - the tank that is being fired on
					missile - the missile to be fired
  
   Return Value:    The Behaviour that the tank should take
  
   Method Notes:    If the tank is either on the same x or y of the player
					then the tank will be told to fire the missile at the player
					
					If not then the current behaviour will just be used
***************************************************************************/


BEHAVIOUR turn_check(Tank *enemy, Tank *player)
{
	if(((enemy->x_coordinate >= player->x_coordinate-16
		&& enemy->x_coordinate <= player->x_coordinate+16) 
		&& enemy->v_facing == HORIZONTAL) || 
		((enemy->y_coordinate >= player->y_coordinate-16
		&&enemy->y_coordinate <= player->y_coordinate+16) && enemy->h_facing == VERTICAL))
	{
		return TURN;
	}
	else
	{
		return enemy->current_behaviour;
	}
}

/***************************************************************************
   Function Name:  	respawn check
  
   Purpose:         To check to see if the tank is allowed to respawn
  
   Input Arguments: Enemy: the tank that will respawn
  
   Return Value:    The Behaviour that the tank should take
  
   Method Notes:    If the tank is either on the same x or y of the player
					then the tank will be told to fire the missile at the player
					
					If not then the current behaviour will just be used
***************************************************************************/




BEHAVIOUR respawn_check(Tank *enemy)
{
	if(event())
	{
		return RESPAWN;
	}
	else
	{
		return enemy->current_behaviour;
	}
}


/***************************************************************************
   Function Name:  	dodge_y_check
  
   Purpose:         To check if a missile is about to hit a tank
  
   Input Arguments: Enemy: the tank that will be dodging
					Missile: the missile that might hit the tank
					
  
   Return Value:    The Behaviour that the tank should take
  
   Method Notes:    If the tank is either at the same x or
					y of the tanks location, then the tank should dodge
***************************************************************************/


BEHAVIOUR dodge_y_check(Tank *enemy, Missile *missile)
{
	if(enemy->y_coordinate >= missile->y_coordinate-16
		&& enemy->y_coordinate <= missile->y_coordinate+16
		&& missile->is_visible)
	{
		return DODGE_Y;
	}
	else
	{
		return enemy->current_behaviour;
	}

}

/***************************************************************************
   Function Name:  	dodge_x_check
  
   Purpose:         To check if a missile is about to hit a tank
  
   Input Arguments: Enemy: the tank that will be dodging
					Missile: the missile that might hit the tank
					
  
   Return Value:    The Behaviour that the tank should take
  
   Method Notes:    If the tank is either at the same x or
					y of the tanks location, then the tank should dodge
***************************************************************************/


BEHAVIOUR dodge_x_check(Tank *enemy, Missile *missile)
{
	if(enemy->x_coordinate <= missile->x_coordinate+16
		&& enemy->x_coordinate >= missile->x_coordinate-16
		&& missile->is_visible)
	{
		return DODGE_X;
	}
	else
	{
		return enemy->current_behaviour;
	}
}




BOOL event() {return 0;}



BOOL flip(int position)
{
	return position%2;
}


/***************************************************************************
   Function Name:  	move_y
  
   Purpose:         To move a tank a number of pixels
					in an vertical direction
  
   Input Arguments: tank: The tank that will be moving
					object: an object that might get in the way
					offset: how much the tank is going to move
					
   Method Notes:    If the tank isn't near a stationary object
					then it will move vertically toward the player
					otherwise it will move horizontally
***************************************************************************/


void move_y(Tank *tank, Stationary_Object *object, int offset, int num_objects)
{
	int index;
	BOOL all_clear = 1;
/*	for(index = 0; index < num_objects && all_clear; index++)
	{
		if(!((tank->y_coordinate+offset >= object[index].y_coordinate-16
			&& tank->y_coordinate+offset <= object[index].y_coordinate+16)
			&& tank->x_coordinate <= object[index].x_coordinate+16
			&& tank->x_coordinate >= object[index].x_coordinate-16))
		{
			all_clear = 0;
		} 
	}*/
	if(all_clear)
	{
		tank->y_coordinate += offset;
	}
	else
	{
		if(flip(tank->y_coordinate))
		{
			move_x(tank, object, 1, num_objects);
		}
		else
		{
			move_x(tank, object, -1, num_objects);
		}
	}
	
}


/***************************************************************************
   Function Name:  	move_x
  
   Purpose:         To move a tank a number of pixels
					in a horizontal direction
  
   Input Arguments: tank: The tank that will be moving
					object: an object that might get in the way
					offset: how much the tank is going to move
					
   Method Notes:    If the tank isn't near a stationary object
					then it will move horizontally toward the player
					otherwise it will move vertically
***************************************************************************/



void move_x(Tank *tank, Stationary_Object *object, int offset, int num_objects)
{
	int index;
	BOOL all_clear = 1;
	for(index = 0; index < num_objects && all_clear; index++)
	{
		if(!((tank->x_coordinate+offset >= object[index].x_coordinate-16
			&& tank->x_coordinate+offset <= object[index].x_coordinate+16)
			&& tank->y_coordinate <= object[index].y_coordinate+16
			&& tank->y_coordinate >= object[index].y_coordinate+16))
		{
			all_clear = 0;
		}
		
	}
	if(all_clear)
	{
		tank->x_coordinate += offset;
	}
	else
	{
		if(flip(tank->x_coordinate))
		{
			move_y(tank, object, 1, num_objects);
		}
		else
		{
			move_y(tank, object, -1, num_objects);
		}
	}
}






