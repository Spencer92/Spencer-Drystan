#ifndef BITMAPS_H
#define BITMAPS_H
#include "types.h"
extern 	UINT32 playerTankEast[];
extern 	UINT32 playerTankNorth[];
extern 	UINT32 playerTankSouth[];
extern 	UINT32 playerTankWest[];
extern 	UINT32 enemyTankEast[];
extern 	UINT32 enemyTankNorth[];
extern 	UINT32 enemyTankSouth[];
extern 	UINT32 enemyTankWest[];
extern 	UINT32 Rock401[];
extern 	UINT32 explosion[];
extern 	UINT32 lake[];
extern 	UINT32 tree2[];
extern 	UINT8 player_missile[];
extern 	UINT8 enemy_missile[];

void getBitmap32(const UINT32* bitmap, UINT32* new_bitmap);

#endif