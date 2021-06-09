#pragma warning (disable: 4996 4710 4820)

//Includes:
#include "Hotel.h"

//Constant Definitions:
static boolean preventDoubleEncryption = FALSE;
static boolean preventDoubleDecryption = FALSE;

//Function Codes:
void initHotel(hotel_t* theHotel)
/** Initializing Hotel by user input, including memory allocation - DO NOT FORGET TO FREE */
{
	int i, j;
	int inputOK;
	char userInput;
	PRINT("Started");
	do
	{
		printf("How Many Floors Do The Hotel Has? [%d-%d]\t", MIN_FLOORS, MAX_FLOORS);
		scanf("%d", &theHotel->numberOfFloors);
	} while (theHotel->numberOfFloors > MAX_FLOORS || theHotel->numberOfFloors < MIN_FLOORS);
	do
	{
		printf("How Many Roomes Each Level Has? [%d-%d]\t", MIN_ROOMS, MAX_ROOMS);
		scanf("%d", &theHotel->roomsPerFloor);
	} while (theHotel->roomsPerFloor > MAX_ROOMS || theHotel->roomsPerFloor < MIN_ROOMS);
	cleanBuffer();
	do {
		inputOK = FALSE;
		printf("For Testing, Should I Randomize Rooms' Data? <y/n>\t");
		scanf("%c", &userInput);
		cleanBuffer();
		if (userInput == 'y' || userInput == 'Y' || userInput == 'n' || userInput == 'N')
			inputOK = TRUE;
	} while (!inputOK);

	theHotel->allRooms = (room_t**)calloc(theHotel->numberOfFloors, sizeof(room_t*));
	validateAllocation(theHotel->allRooms);
	for (i = 0; i < theHotel->numberOfFloors; i++) {
		theHotel->allRooms[i] = (room_t*)calloc(theHotel->roomsPerFloor, sizeof(room_t));
		validateAllocation(theHotel->allRooms[i]);
		for (j = 0; j < theHotel->roomsPerFloor; j++)
			if (userInput == 'y' || userInput == 'Y')
				initRoomRandomized(&theHotel->allRooms[i][j]);
			else
				initRoom(&theHotel->allRooms[i][j]);
	}
	PRINT("Ended");
}

void initHotelFromFile(hotel_t* theHotel, const char* binFileName, const char* encryptionFileName)
{
	/** Initializing Hotel from argumented filename, including memory allocation - DO NOT FORGET TO FREE */
	FILE* binFile = fopen(binFileName, READ_BINARY);
	int i, j;
	validateFile(binFile);

	fread(&theHotel->numberOfFloors, sizeof(int), 1, binFile);
	fread(&theHotel->roomsPerFloor, sizeof(int), 1, binFile);
	theHotel->allRooms = (room_t**)calloc(theHotel->numberOfFloors, sizeof(room_t*));
	validateAllocation(theHotel->allRooms);
	for (i = 0; i < theHotel->numberOfFloors; i++) {
		theHotel->allRooms[i] = (room_t*)calloc(theHotel->roomsPerFloor, sizeof(room_t));
		validateAllocation(theHotel->allRooms[i]);
		for (j = 0; j < theHotel->roomsPerFloor; j++)
			fread(&theHotel->allRooms[i][j], sizeof(room_t), 1, binFile);
	}
	decryptHotel(theHotel, encryptionFileName);
	fclose(binFile);
	printf("File Loading Completed!\n");
}

void printHotel(const hotel_t* theHotel)
{
	/** Printing Hotel Data */
	int i, j;
	PRINT("Started");
	printf("The Hotel Has %d Floor%s, and %d Room%s in Each Floor\n", theHotel->numberOfFloors, theHotel->numberOfFloors == 1 ? "" : "s", theHotel->roomsPerFloor, theHotel->roomsPerFloor == 1 ? "" : "s");
	for (i = 0; i < theHotel->numberOfFloors; i++)
		for (j = 0; j < theHotel->roomsPerFloor; j++)
		{
			printf("Details For Room #%d-%02d:\n", i, j);
			printRoom(&theHotel->allRooms[i][j]);
		}
	printf("\n");
	PRINT("Ended");
}

void freeHotel(hotel_t* theHotel)
{
	/** Freeing The Previously Allocated Room Matrix */
	int i;
	PRINT("Started");
	for (i = 0; i < theHotel->numberOfFloors; i++) {
		free(theHotel->allRooms[i]);
	}
	free(theHotel->allRooms);
	PRINT("Ended");
}

boolean facilityInRoom(room_t* theRoom, facility facilityToCheck)
{
	/** Checking if theRoom Has The facilityToCheck, Returns True (1) / False (0) */
	PRINT("Started");
	PRINT("Ended");
	return (theRoom->facilitiesStatus & (unsigned char)pow(BIN, facilityToCheck)) ? TRUE : FALSE;
}

void allRoomsWithFacilityInHotel(hotel_t* theHotel, facility facilityToCheck)
{
	/** Printing all Vacant Rooms in theHotel, having facilityToCheck bit ON */
	int i, j;
	PRINT("Started");
	printf("Printing All Rooms With %s...\n", facilities[facilityToCheck]);
	for (i = 0; i < theHotel->numberOfFloors; i++)
		for (j = 0; j < theHotel->roomsPerFloor; j++)
		{
			if (facilityInRoom(&theHotel->allRooms[i][j], facilityToCheck) && !facilityInRoom(&theHotel->allRooms[i][j], OCCUPIED))
			{
				printf("Details For Room #%d-%02d:\n", i, j);
				printRoom(&theHotel->allRooms[i][j]);
			}
		}
	printf("\n");
	PRINT("Ended");
}

facility chooseFacility(void)
{
	/** ask the user to choose Facility and return the facility chosen */
	int i;
	facility facilityToCheck;
	PRINT("Started");
	printf("Facilities Available To Search:\n");
	for (i = 0; i < facilitiesSize; i++)
	{
		printf("%d. %s\n", i + 1, facilities[i]);
	}
	do {
		printf("Please Choose Facility To Check For:\t");
		scanf("%d", &facilityToCheck);
		cleanBuffer();
	} while (facilityToCheck < 1 || facilityToCheck >facilitiesSize);
	PRINT("Ended");
	return facilityToCheck - 1;
}

void variadicRoomWithFacility(facility facilityToCheck, ...)
{
	/** Variadic, get room_t pointers as argument, NULL as last argument, checks if room has the facilityToCheck */
	va_list rooms;
	room_t *currentRoom;

	va_start(rooms, facilityToCheck);
	currentRoom = va_arg(rooms, room_t*);
	while (currentRoom != NULL)
	{
		if (facilityInRoom(currentRoom, facilityToCheck))
			printRoom(currentRoom);
		currentRoom = va_arg(rooms, room_t*);
	}
}

void encryptHotel(const hotel_t* theHotel, const char* filename)
{
	/** Encrypts hotel data */
	FILE* encriptionCodeFile = fopen(filename, WRITE);
	int randomBit;
	int i, j;
	PRINT("Started");

	validateFile(encriptionCodeFile);
	randomBit = rand() % CHAR_BIT;
	fprintf(encriptionCodeFile, "%d", randomBit);
	fclose(encriptionCodeFile);
	if (!preventDoubleEncryption) {
		for (i = 0; i < theHotel->numberOfFloors; i++)
			for (j = 0; j < theHotel->roomsPerFloor; j++)
				encryptBytes(&theHotel->allRooms[i][j], sizeof(theHotel->allRooms[0][0]), randomBit);
		printf("Data Encrypted!\n");
		preventDoubleEncryption = TRUE;
		preventDoubleDecryption = FALSE;
	}
	else
		printf("Data Already Encrypted\n");
	PRINT("Ended");
}

void decryptHotel(const hotel_t* theHotel, const char* filename)
{
	/** Decrypts hotel data */
	FILE* encriptionCodeFile = fopen(filename, READ);
	int randomBit;
	int i, j;
	PRINT("Started");

	validateFile(encriptionCodeFile);
	fscanf(encriptionCodeFile, "%d", &randomBit);
	fclose(encriptionCodeFile);
	if (!preventDoubleDecryption) {
		for (i = 0; i < theHotel->numberOfFloors; i++)
			for (j = 0; j < theHotel->roomsPerFloor; j++)
				decryptBytes(&theHotel->allRooms[i][j], sizeof(theHotel->allRooms[0][0]), randomBit);
		printf("Data Decrypted!\n");
		preventDoubleDecryption = TRUE;
		preventDoubleEncryption = FALSE;
	}
	else
		printf("Data Already Decrypted\n");
	PRINT("Ended");
}

void saveHotelToFile(const hotel_t* theHotel, const char* binFileName, const char* encryptionFileName)
{
	/** Saves Hotel Data to Binary file */
	FILE* binFile = fopen(binFileName, WRITE_BINARY);
	int i, j;
	validateFile(binFile);
	encryptHotel(theHotel, encryptionFileName);
	fwrite(&theHotel->numberOfFloors, sizeof(int), 1, binFile);
	fwrite(&theHotel->roomsPerFloor, sizeof(int), 1, binFile);
	for (i = 0; i < theHotel->roomsPerFloor; i++)
		for (j = 0; j < theHotel->numberOfFloors; j++)
			fwrite(&theHotel->allRooms[i][j], sizeof(room_t), 1, binFile);
	fclose(binFile);
	printf("Data Saved To File > %s\n", binFileName);
}
