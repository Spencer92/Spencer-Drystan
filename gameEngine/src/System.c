#include <osbind.h>


/***************************************************************************
   Function Name:   getTime
  
   Purpose:         To get the current time on the clock
  
   Return Value: 	The current time;
***************************************************************************/



long getTime()
{
	long *timer = (long *)0x462L;
	long oldssp;
	long new_time;
	oldssp = Super(0);
	new_time = *timer;
	Super(oldssp);
	return new_time;
}