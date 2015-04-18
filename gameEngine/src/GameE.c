/*
 ============================================================================
 *Title       : Game Engine
 *Author      : Drystan Mazur & Spencer Maslen
 *Email       : dmazu602@mtroyal.ca & smasl811@mtroyal.ca
 Due on       :
 *Version     : 1
 *Assignment  : Stage 3
 *Course      : Comp 2659
 *Instructor  : Paul Pospisil
 *Copyright   : Released under GPL v3
 *Description : Raster library for Atarti St, ANSI-style C89
 *Source File : GameEngine.c
 =============================================================================
 Purpose      : To demonstrate a working game model
 =============================================================================
 Method       :

 ============================================================================ */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <osbind.h>
/*===================================================*/
/*Header files authored by Others*/

#include "types.h"

/*===================================================*/
/*Header files authored by Spencer Maslen or Drystan Mazur*/

#include  "Behavior.h"
#include  "Model.h"
#include  "RenderE.h"
#include  "AsRou.h"
#include  "System.h"
#include  "Fonts.h"
#include  "GameF.h"
#include  "Grass.h"
#include  "GameF.h"
#include  "BackDrop.h"
#include  "Bitmaps.h"
#include "soundgen.h"

/*===================================================*/
#define  BUFFER_SIZE  0x8400L


volatile void thing2(){}
void memCopy(char* screenChunk1 ,char* screenChunk2);
void waitForinput();
	UINT8 screen1[BUFFER_SIZE];
	UINT8 screen2[BUFFER_SIZE];
	UINT8 welcomeScreen[BUFFER_SIZE];

	

int main() {

	Tank thePlayer;
	Tank gameArray[NUMBER_OF_TANKS];
	Missile missile[MAX_MISSILES];
	Stationary_Object landobjects[NUM_OBJECTS];
	long missile_time;
	BOOL stuff_happened = 0;
    UINT32* background = (UINT32*) grass;
	
	
	BOOL playerInput = 0;
	char keypress = 0;

	UINT16 playerScore = 0;	
	
	UINT8 i = 0;
	UINT8  lives = 3;
	UINT8 j = 0;
	UINT8 k = 0;
	UINT8 l = 0;
    UINT8 tanksLeft = NUMBER_OF_TANKS;
	long tank_reset_timer[NUMBER_OF_TANKS];
	long player_reset_timer;
	int score = 0;

	
	char *mainScreen;
	char *logMainscreen;
	char *gameScreen;
	char *backGamescreen;
	char *backdropScreen;
	char *plottingScreen;
	char *plottingTankScreen;
	char *tmp;
	
	long music_time;
	long time_now;
	int tank_one_action;
	int tank_two_action;
	int tank_three_action;
	int tank_four_action;
	int tank_five_action;





	/*=========Will Change in next system=========================*/


  	mainScreen		= phys_Base(); 
/*	set_Screen(mainScreen);*/

/*	logMainscreen 	= (Logbase());*/
	
	backdropScreen 	= (char*) welcomeScreen;
	backdropScreen 	= (char*) ((UINT32) (backdropScreen + 255) & 0xFFFFFF00L); /* The screens have to be 256 byte aligned */
	
	gameScreen = (char*) screen1;
	gameScreen = (char*) ((UINT32) (gameScreen + 255) & 0xFFFFFF00L); /* The screens have to be 256 byte aligned */
	
	backGamescreen = (char*) screen2;
	backGamescreen = (char*) ((UINT32) (backGamescreen + 255) & 0xFFFFFF00L); /* The screens have to be 256 byte aligned */

	
	Cursconf(0, 0); /* removes cursor*/
	
	if(findRez() ) /*If we are in High rez mode*/
	{
	 	
	 memCopy((char*)backdrop, backdropScreen);
	 memCopy((char*)grass,gameScreen);
	 memCopy(gameScreen,backGamescreen);
	 memCopy(backdropScreen,mainScreen);
	

	 
	 set_Screen(backdropScreen);	
	 Vsync();

	while (!DSconis()) {

		if (i == 0) {
			DSconws("\r\n\0");			
			DSconws("Press space to start or q to quit \r\n\0");
			DSconws("\r\n\0");
		}

		if (!(i >= 1)) {
			i++;
		}

	}

	keypress = DSnecin();

	if (keypress != 'q') {


		
		gameStart(gameArray, &thePlayer, missile,NUMBER_OF_TANKS, (int*)&playerScore);
		
		plotLargeSprite(gameScreen, thePlayer.sprite, thePlayer.x_coordinate, thePlayer.y_coordinate, SPRITE_SIZE);
		

 		set_Screen(plottingScreen); 
		Vsync();

	
	/*=====================here is main game loop==================*/	
		music_time = time_now = missile_time = player_reset_timer = getTime();
		for(i = 0; i < NUMBER_OF_TANKS; i++)
		{
			tank_reset_timer[i] = time_now;
		}
		i = 0;
		start_music();
		do {
		
			tanksLeft = NUMBER_OF_TANKS;
			if(getTime() >= music_time+16)
			{
				music();
				music_time = getTime();
			}
		
			if(DSconis())
			{
				keypress = DSnecin();
				playerInput = 1;
				
				if (keypress == 'p') 
				{
		/*=====================here is the pause game loop==================*/
			
				
				Vsync();
 				set_Screen(mainScreen); 
			
				Cconws("In pause game loop \r\n\0");
				Cconws("Please press any key to start \r\n\0");

				while (!DSconis()) {
				}
				keypress = DSnecin();
				}
		/*=====================here is the end of pause game loop==================*/	
				else
				{
				
					player_action_check(&thePlayer, gameArray, NUMBER_OF_TANKS, keypress, missile, MAX_MISSILES);
					if(getTime() >= time_now)
					{
						player_action(&thePlayer, missile, MAX_MISSILES);
					}

					
				
				}
			
			}
			else
			{
				playerInput = 0;
			
			
			
			}
			
			assess_situation(&gameArray[j], &thePlayer, landobjects, missile, 1/*NUMBER_OF_TANKS*/, MAX_MISSILES);
		
    
        
            
            
           

			if(missile[k].current_behaviour != EXPLODE && missile[k].is_visible)
			{
				move_missile(&missile[k]);
			}
			else if(missile[k].current_behaviour == EXPLODE)
			{
				missile[k].is_visible = 0;
				missile[k].current_behaviour = DO_NOTHING_MISSILE;
			}
			
			
			if(die_check(&gameArray[j],missile,MAX_MISSILES))
			{

				gameArray[j].is_visible = 0;
			}
			if(die_check(&thePlayer,missile,MAX_MISSILES))
			{
				thePlayer.is_visible = 0;
			}

          
            
			if(getTime() >= time_now+10)
			{
				tank_respond(&gameArray[j], missile, MAX_MISSILES, NUMBER_OF_TANKS);	
				 time_now = getTime();
			}

			
			
	
			
			if(lives <= 0)
			{
			
				/*ask player if he/she would wish to play again*/
				if(keypress == 'y')
				{
				gameStart(gameArray, &thePlayer, missile,NUMBER_OF_TANKS, (int*)&playerScore);
				
				
				
				}
			

			
			}

				for(i = 0; i < MAX_MISSILES; i++)
				{
					plotBackground(plottingScreen,background,missile[i].x_coordinate, missile[i].y_coordinate ,SPRITE_SIZE);
				}	
				plotBackground(plottingScreen,background,thePlayer.x_prev, thePlayer.y_prev ,SPRITE_SIZE);				
				for(i = 0; i < NUMBER_OF_TANKS; i++)
				{
					plotBackground(plottingScreen,background,gameArray[i].x_prev, gameArray[i].y_prev ,SPRITE_SIZE);					
				}
				for(i = 0; i < NUMBER_OF_TANKS; i++)
				{
                    if(gameArray[i].is_visible)
                    {
                        plotLargeSprite(plottingScreen, gameArray[i].sprite ,gameArray[i].x_coordinate,gameArray[i].y_coordinate,SPRITE_SIZE);
                    }
					else if(!gameArray[i].is_visible)
					{
						thing2();
						gameArray[i].x_coordinate = -1;
						gameArray[i].y_coordinate = -1;
						tanksLeft--;
						if(gameArray[i].current_behaviour == DIE)
						{
							score += (int) (getTime()%100);
							gameArray[i].current_behaviour = DO_NOTHING;
						}
					}
				}
				
				plotLargeSprite(plottingScreen, thePlayer.sprite, thePlayer.x_coordinate, thePlayer.y_coordinate, SPRITE_SIZE);	

				plotScore(plottingScreen,score,368,376,5);
				plotScore(plottingScreen,thePlayer.hitpoints,80,376,4);

				for(l = 0; l < MAX_MISSILES; l++)
				{
					if(missile[l].is_visible)
					{
						plotLargeSprite(plottingScreen, missile[l].sprite, missile[l].x_coordinate ,
						missile[l].y_coordinate, SPRITE_SIZE);
					}
				
				}
				if(plottingScreen != gameScreen)
				{
 					plottingScreen = gameScreen;
					plottingTankScreen = backGamescreen;
 				}
				else
				{
					plottingScreen = backGamescreen;
					plottingTankScreen = gameScreen;
 				}
				
				
/*				plotLargeSprite(plottingScreen, thePlayer.sprite, thePlayer.x_coordinate, thePlayer.y_coordinate, SPRITE_SIZE);*/

/*				for(i = 0; i < NUMBER_OF_TANKS; i++)
				{

                    if(gameArray[i].is_visible)
                    {
                        plotLargeSprite(plottingScreen, gameArray[i].sprite ,gameArray[i].x_coordinate,gameArray[i].y_coordinate,SPRITE_SIZE);
                    }
                    else
                    {
                        tanksLeft--;
                    }
                    
				}*/


                i = 0;
/*				for(l = 0; l < MAX_MISSILES; l++)
				{
					if(missile[l].is_visible)
					{
						plotSprite(plottingScreen, missile[l].sprite, missile[l].x_coordinate ,
						missile[l].y_coordinate, SMALL_SPRITE_SIZE);
					}
				
				}*/
                l = 0;
				Vsync();
/*  		        Setscreen(-1L, plottingScreen, -1L);*/	 
				set_Screen(plottingScreen); 
/* 				memCopy((char*)grass,plottingTankScreen);
*/				

				if(getTime() <= tank_reset_timer[j]+210)
				{
					gameArray[j].missile_available = START_PLAYER_MISSILES;
				}
				if(getTime() <= player_reset_timer+210)
				{
					thePlayer.missile_available = START_PLAYER_MISSILES;
				}

				if(j < NUMBER_OF_TANKS-1)
				{
					j++;
				}
				else
				{
					j = 0;
				}
				if(k  < MAX_MISSILES-1)
				{
					k++;
				}
				else
				{
					k = 0;
				}
      
	            if(tanksLeft <= 0)
                {
                    break;
                }
		} while (keypress != 'q');

	}

	}
	
	else
	{
	
		Cconws("Error in screen resolution");
	
	}

	
	Vsync();
	set_Screen(mainScreen); 
/* 	Setscreen(mainScreen ,mainScreen ,-1L);*/

	stop_sound();
	if(thePlayer.is_visible)
	{
		printf("\n Player wins\n");
	}
	if(gameArray[0].is_visible)
	{
		printf("\n Enemy wins\n");
	}
	printf("%i\n", gameArray[0].v_facing);

	return 0;

}






	
void memCopy(char* screenChunk1 ,char* screenChunk2)
{
	register UINT32  copySize;
	register UINT32 *srcPtr =  (UINT32*) screenChunk1;
	register UINT32 *dstPtr =  (UINT32*) screenChunk2;
	register UINT32 i;
	copySize = SCREEN_SIZE >> 2;
	i = copySize>>3;
	
	do
	{
	
		*dstPtr++ = *srcPtr++;
		*dstPtr++ = *srcPtr++;
		*dstPtr++ = *srcPtr++;
		*dstPtr++ = *srcPtr++;
		*dstPtr++ = *srcPtr++;
		*dstPtr++ = *srcPtr++;
		*dstPtr++ = *srcPtr++;
		*dstPtr++ = *srcPtr++;
		
		
	}while(i--);
	
	
}

void waitForinput() {

	UINT32 i;

	for(i = 0;i < 100000;i++)
	{

	}
}