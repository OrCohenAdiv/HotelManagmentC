#pragma warning (disable: 4996 4710 4820)

//Includes:
#include "GlobalFunctions.h"

//Function Codes:
void cleanBuffer(void)
{
	/** repeatedly getting chars until reaching the 'newline' (Enter) char. */
	PRINT("Started");
	while (getchar() != '\n');
	PRINT("Ended");

}

void validateAllocation(void* pointerToCheck)
{
	/** Terminates program immediately, used only when memory allocation fails. */
	PRINT("Started");
	if (!pointerToCheck)
	{
		printf("ALLOCATION ERROR!\n");
		PRINT("Ended Unsuccessfully");
		exit(ERROR_MEMORY_ALLOCATION_FAILED);
	}
	PRINT("Ended Successfully");
}

void validateFile(FILE* fileToCheck)
{
	/** Terminates program immediately, used only when memory allocation fails. */
	PRINT("Started");
	if (!fileToCheck)
	{
		printf("FILE OPENING ERROR!\n");
		PRINT("Ended Unsuccessfully");
		exit(ERROR_OPEN_FILE_FAILED);
	}
	PRINT("Ended Successfully");
}

unsigned int createMask(int high, int low)
{
	/** Puts 1s in all bits from left to right (includes). */
	PRINT("Started");
	PRINT("Ended");
	return (1 << (high + 1)) - (1 << low);

}

void menu(void)
{
	/** printing the menu*/
	PRINT("Started");
	printf("----------------------------------MENU----------------------------------\n");
	printf("Press %c To Show The Full Hotel Status\n", SHOW_HOTEL_STATUS);
	printf("Press %c To Search Room By Facility\n", ROOM_SEARCH_BY_FACILITY);
	printf("Press %c To Quit!\n", EXIT);
	printf("Please Enter Your Choice:\t");
	PRINT("Ended");
}
