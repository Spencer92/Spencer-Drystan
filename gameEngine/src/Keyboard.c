/*Routines to read the keyboard directly*/
#include <tos.h>
#include "types.h"

void DSconout(char output)
{
	Cconout(output);
}


char DSnecin()
{
	return Cnecin();
}

BOOL DSconis()
{
	return Cconis();
}

void DSconws(String output)
{
	Cconws(output);
}
