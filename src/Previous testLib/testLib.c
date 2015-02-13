#include "raster.h"
#include "types.h"
/*#include <tos.h> */
#include <osbind.h>
#include <stdio.h>
/*#include <stdint.h>*/
#include <stdlib.h>
#include "model.h"
void fire();

int main()
{
	Tank players;
	Tank enemy;
	Stationary_Object tree;
	fire();
	
	return 0;
}

void fire()
{
	static int other = 1;
	register char *face = "Output\n";
	/*printf(face);*/
	other++;
	if(other != 10)
	{
		fire();
	}
}


void 



































