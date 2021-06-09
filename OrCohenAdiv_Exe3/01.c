#pragma warning (disable: 4996 4710 4820)
/*	Disabled Warnings:
*	4996 = Scanf security issue (_CRT_SECURE_NO_WARNING replacement)
*	4710 = Function not inlined
*	4820 = X Bytes pading for structs
*	(nothing we can do to prevent these warnings, Keren approved to suppression of those)
*/

//Includes:
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GlobalFunctions.h"
#include "Room.h"
#include "Hotel.h"
#include "EncriptionDecription.h"

//main:
int main(int argc, const char** argv)
{
	//Program Variables:
	char iOption;
	hotel_t HotelCalifornia;
	facility facilityToCheck;

	//Random Seed:
	srand((unsigned long)time(NULL));

	if (argc == 1) {
		printf("There Was No Filename Inserted As Argument...\n");
		printf("Initializing Hotel From Scratch...\n");
		initHotel(&HotelCalifornia);
	}
	else
	{
		printf("Initializing Hotel From File:\n>> %s\n", argv[ARG_FILENAME]);
		initHotelFromFile(&HotelCalifornia, argv[ARG_FILENAME], ENCRYPTION_CODE_FILENAME);
	}
	system("pause");
	system("cls");

	if (HotelCalifornia.roomsPerFloor >= MINIMAL_NUM_FOR_VARIADIC)
	{
		//impossible to print room number, used as a test as requested in questions.
		printf("There Are More Than %d Rooms In Each Floor.\n", MINIMAL_NUM_FOR_VARIADIC);
		printf("Check The First %d Rooms On The First Floor For Having %s\n", MINIMAL_NUM_FOR_VARIADIC, facilities[BALCONY]);
		variadicRoomWithFacility(BALCONY, &HotelCalifornia.allRooms[0][0], &HotelCalifornia.allRooms[0][1], &HotelCalifornia.allRooms[0][2], NULL);
	}

	do //If Reached To That Point, Hotel Is Allocated and Rooms are Filled with Data. No Need To Check NullPtrs etc.
	{
		system("pause");
		system("cls");
		menu();
		scanf("%c", &iOption);
		cleanBuffer(); //empty buffer -> flushall or fflush(stdin) doesn't work.
		switch (iOption)
		{
		case SHOW_HOTEL_STATUS:
			printHotel(&HotelCalifornia);
			break;
		case ROOM_SEARCH_BY_FACILITY:
			facilityToCheck = chooseFacility();
			allRoomsWithFacilityInHotel(&HotelCalifornia, facilityToCheck);
			break;
		case EXIT:
			saveHotelToFile(&HotelCalifornia, BINARY_FILENAME, ENCRYPTION_CODE_FILENAME);
			printf("Good Bye!\n");
			freeHotel(&HotelCalifornia);
			break;
		default:
			printf("Wrong Input, Please Try Again!\n");
			break;
		}
	} while (iOption != EXIT);
	system("pause");
	return EXIT_SUCCESS;
}
