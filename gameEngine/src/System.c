/* #include <osbind.h> */
#include "asrou.h"

/***************************************************************************
   Function Name:   getTime
  
   Purpose:         To get the current time on the clock
  
   Return Value: 	The current time;
***************************************************************************/



long getTime()
{
	long *timer = (long *)0x462L;
	long new_time;
	enterSuper();
	new_time = *timer;
	exitSuper();
	return new_time;
}