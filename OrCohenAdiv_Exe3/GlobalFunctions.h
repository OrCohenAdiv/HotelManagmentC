#ifndef __GLOBAL_FUNCTIONS_H
#define __GLOBAL_FUNCTIONS_H

//Includes:
#include <stdio.h>
#include <stdlib.h>

//Constant Definitions:
//Menu:
#define SHOW_HOTEL_STATUS '1'
#define ROOM_SEARCH_BY_FACILITY '2'
#define EXIT '0'
//ERROR CODES:
#define ERROR_MEMORY_ALLOCATION_FAILED 1
#define ERROR_OPEN_FILE_FAILED         2
//Arguments:
#define ARG_FILENAME 1
//File Modes:
#define WRITE_BINARY "wb"
#define READ_BINARY "rb"
#define WRITE "w"
#define READ "r"
//FileNames:
#define ENCRYPTION_CODE_FILENAME "EncryptionCode.txt"
#define BINARY_FILENAME "HotelData.bin"
//Etc.
#define MINIMAL_NUM_FOR_VARIADIC 3
#define BIN 2
//Enums:
typedef enum { POOL_VIEW, BALCONY, KETTLE, FREE_WIFI, SOFA_BED, TV, OCCUPIED } facility;
typedef enum { FALSE, TRUE } boolean;
//Global Statics:
static const char* facilities[] = { "Pool Side View", "Balcony", "Kettle", "Free WiFi", "Sofa Bed", "TV", "Occupied" };
static const int facilitiesSize = sizeof(facilities) / sizeof(facilities[0]);

//Macros:
//#define DEBUG_WITH_DETAILS

#ifdef DEBUG_SIMPLE
	#define PRINT(str) printf("%s\n", str);
#else
	#ifdef DEBUG_WITH_DETAILS
		#define PRINT(str) printf("%s (%ld): %s\n", __FUNCTION__, __LINE__, str);
	#else
		#define PRINT(str) ;
	#endif
#endif
//__FILE__, __LINE__, __FUNCTION__

//Function Prototypes:
void cleanBuffer(void);
void validateAllocation(void* pointerToCheck);
void validateFile(FILE* fileToCheck);
unsigned int createMask(int left, int right);
void menu(void);

#endif // __GLOBAL_FUNCTIONS_H

