#ifndef __HOTEL_H
#define __HOTEL_H

//includes:
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "GlobalFunctions.h"
#include "Room.h"
#include "EncriptionDecription.h"

//Constant Definitions:
#define MAX_FLOORS 10 
#define MIN_FLOORS 1
//In order to keep room in 3 digits i've set MAX_FLOORS to be 9
#define MAX_ROOMS 100
#define MIN_ROOMS 1

//Structs typedefs:
typedef struct hotel
{
	int numberOfFloors;
	int roomsPerFloor;
	room_t** allRooms;
} hotel_t;

//Function Prototypes:
void initHotel(hotel_t* theHotel);
void initHotelFromFile(hotel_t* theHotel, const char* binFileName, const char* encryptionFileName);
void printHotel(const hotel_t* theHotel);
void freeHotel(hotel_t* theHotel);
boolean facilityInRoom(room_t* theRoom, facility facilityToCheck);
void allRoomsWithFacilityInHotel(hotel_t* theHotel, facility facilityToCheck);
facility chooseFacility(void);
void variadicRoomWithFacility(facility facilityToCheck, ...);
void encryptHotel(const hotel_t* theHotel, const char* filename);
void decryptHotel(const hotel_t* theHotel, const char* filename);
void saveHotelToFile(const hotel_t* theHotel, const char* binFileName, const char* encryptionFileName);

#endif // __HOTEL_H

