#ifndef __ROOM_H
#define __ROOM_H

//Constant Definitions:
#define MAX_BEDS 4 
#define MIN_BEDS 1
#define MAX_FACILITIES 0x7F
#define MIN_FACILITIES 0x0

//includes:
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GlobalFunctions.h"

//Structs typedefs:
typedef struct room
{
	int numberOfBeds;
	unsigned char facilitiesStatus;
	// bits order R to L: POOL_VIEW, BALCONY, KETTLE, FREE_WIFI, SOFA_BED, TV, OCCUPIED.
} room_t;

//Function Prototypes:
void initRoom(room_t* theRoom);
void initRoomRandomized(room_t* theRoom);
void printRoom(room_t* theRoom);

#endif // __ROOM_H

