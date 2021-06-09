#pragma warning (disable: 4996 4710 4820)

//includes:
#include "EncriptionDecription.h"

//Function Codes:
void encryptBytes(const void* bytesToCrypt, const int numberOfBytes, const int randomBit)
{
	/** Run all three encryption part on bytesToCrypt */
	PRINT("Started");
	swapBitsInByte(bytesToCrypt, numberOfBytes, randomBit);
	fullMaskXOR(bytesToCrypt, numberOfBytes);
	circularRight(bytesToCrypt, numberOfBytes, randomBit);
	PRINT("Ended");
}

void decryptBytes(const void* bytesToCrypt, const int numberOfBytes, const int randomBit)
{
	/** Run all three decryption part on bytesToCrypt */
	PRINT("Started");
	circularLeft(bytesToCrypt, numberOfBytes, randomBit);
	fullMaskXOR(bytesToCrypt, numberOfBytes);
	swapBitsInByte(bytesToCrypt, numberOfBytes, randomBit);
	PRINT("Ended");
}

void swapBitsInByte(const void* bytesToCrypt, const int numberOfBytes, const int bitLocation)
{
	/** Swaping the bit in bitLocation with the bit in bitLocation+1 */
	int i;
	unsigned char firstBitMask = (1 << (CHAR_BIT - bitLocation));
	unsigned char secondBitMask = (1 << (CHAR_BIT - ((bitLocation + 1) % CHAR_BIT)));
	unsigned char mask = firstBitMask | secondBitMask;
	unsigned char* firstByte = (unsigned char*)bytesToCrypt;
	unsigned char firstBit;
	unsigned char secondBit;

	PRINT("Started");
	for (i = 0; i < numberOfBytes; i++) {
		firstBit = (*(firstByte + i))&firstBitMask;
		secondBit = (*(firstByte + i))&secondBitMask;
		if (firstBit != secondBit >> 1)
		{
			*(firstByte + i) ^= mask;
			*(((unsigned char*)bytesToCrypt) + i) = *(firstByte + i);
		}
	}
	PRINT("Ended");
}

void fullMaskXOR(const void* bytesToCrypt, const int numberOfBytes)
{
	/** XORs all bits with 1 - Encryption and Decryption */
	PRINT("Started");
	unsigned char* firstByte = (unsigned char*)bytesToCrypt;
	int i;
	for (i = 0; i < numberOfBytes; i++)
		*(firstByte + i) ^= FULL_MASK;
	PRINT("Ended");
}

void circularRight(const void* bytesToCrypt, const int numberOfBytes, const int jumps)
{
	/** Circularly rotating bits in a byte - Encription */
	int i;
	unsigned char* firstByte = (unsigned char*)bytesToCrypt;
	unsigned char temp;
	PRINT("Started");
	for (i = 0; i < numberOfBytes; i++)
	{
		temp = *(firstByte + i) << (CHAR_BIT - jumps);  // Move Left The (CHAR_BIT - jumps) (== the jumps bits from the right) Bits And Saveing it To Temp Var.
		*(firstByte + i) >>= jumps; // Removing the Bits saved to temp from Char
		*(firstByte + i) |= temp;
	}
	PRINT("Ended");
}

void circularLeft(const void* bytesToCrypt, const int numberOfBytes, const int jumps)
{
	/** Circularly rotating bits in a byte - Decryption*/
	int i;
	unsigned char* firstByte = (unsigned char*)bytesToCrypt;
	unsigned char temp;
	PRINT("Started");
	for (i = 0; i < numberOfBytes; i++)
	{
		temp = *(firstByte + i) >> (CHAR_BIT - jumps);  // Move Right The (CHAR_BIT - jumps) (== the jumps bits from the Left) Bits And Saveing it To Temp Var.
		*(firstByte + i) <<= jumps; // Removing the Bits saved to temp from Char
		*(firstByte + i) |= temp;
	}
	PRINT("Ended");
}