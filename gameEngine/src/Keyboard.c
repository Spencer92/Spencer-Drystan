#include "osbind.h"
#include "keyboard.h"
/*Routines to read the keyboard directly*/


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
