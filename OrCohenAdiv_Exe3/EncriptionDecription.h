#ifndef __ENCRIPTION_DECRIPTION_H
#define __ENCRIPTION_DECRIPTION_H

//includes:
#include <stdio.h>
#include <stdlib.h>
#include "GlobalFunctions.h"

//Constant Definitions:
#define FULL_MASK 0xFF

//Function Prototypes:
void encryptBytes(const void* bytesToCrypt, const int numberOfBytes, const int randomBit);
void decryptBytes(const void* bytesToCrypt, const int numberOfBytes, const int randomBit);
void swapBitsInByte(const void* bytesToCrypt, const int numberOfBytes, const int bitLocation);
void fullMaskXOR(const void* bytesToCrypt, const int numberOfBytes);
void circularRight(const void* bytesToCrypt, const int numberOfBytes, const int jumps);
void circularLeft(const void* bytesToCrypt, const int numberOfBytes, const int jumps);

#endif // __ENCRIPTION_DECRIPTION_H

