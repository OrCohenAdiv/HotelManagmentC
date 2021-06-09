#pragma warning (disable: 4996 4710 4820)

//Includes:
#include "Room.h"

//Function Codes:
void initRoom(room_t* theRoom)
{
	/** initisalizing room manually */
	int i, inputOK;
	char ch;
	PRINT("Started");
	theRoom->facilitiesStatus = 0;
	do
	{
		printf("Please Enter How Many Beds In Room:\t");
		scanf("%d", &theRoom->numberOfBeds);
	} while (theRoom->numberOfBeds < MIN_BEDS || theRoom->numberOfBeds> MAX_BEDS);
	cleanBuffer();

	for (i = 0; i < facilitiesSize; i++)
	{
		do
		{
			inputOK = FALSE;
			if (i == facilitiesSize - 1)
				printf("Is The Room Occupied? ");
			else
				printf("Please Enter If The Room Has %s: <y/n>", facilities[i]);
			scanf("%c", &ch);
			cleanBuffer();
			if (ch == 'y' || ch == 'Y' || ch == 'n' || ch == 'N')
				inputOK = TRUE;
		} while (!inputOK);
		if (ch == 'y' || ch == 'Y')
			theRoom->facilitiesStatus |= (char)pow(BIN, i);
	}
	PRINT("Ended");
}

void initRoomRandomized(room_t* theRoom)
{
	/** Randomizing room data */
	PRINT("Started");
	theRoom->numberOfBeds = MIN_BEDS + rand() % (MAX_BEDS - MIN_BEDS + 1);
	theRoom->facilitiesStatus = (unsigned char)(MIN_FACILITIES + rand() % (MAX_FACILITIES - MIN_FACILITIES + 1));
	PRINT("Ended");
}

void printRoom(room_t* theRoom) 
{
/** Print Room Data */
	int i;
	PRINT("Started");
	printf("There %s %d Bed%s In The Room\n", theRoom->numberOfBeds == 1 ? "Is" : "Are", theRoom->numberOfBeds, theRoom->numberOfBeds == 1 ? "" : "s");
	printf("Room Facilities:\n");
	for (i = 0; i < facilitiesSize; i++)
		if (theRoom->facilitiesStatus & (char)pow(BIN, i))
			printf("> %s\n", facilities[i]);
	printf("\n");
	PRINT("Ended");
}


