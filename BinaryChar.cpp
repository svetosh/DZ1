#include "BinaryChar.h"

BinaryChar::BinaryChar(unsigned char c)
{
	Symbol = c;
}

int* BinaryChar::GetBits()
{
	int bits[BitsInChar];
	for (int i = 0; i < BitsInChar; i++)
	{
		bits[i] = charToBit(Symbol, i);
	}
	return bits;
}

unsigned char BinaryChar::GetCharFromBits(int* bits)
{
	char c = (char)0;
	for (int i = 0; i < BitsInChar; i++)
	{
		int currentBit = bits[i];
		c = AddBitToChar(c, i, currentBit);
	}
	return c;
}

int BinaryChar::charToBit(unsigned char c, int bitNumber)
{
	return (int)c >> (7 - bitNumber) & 1;
}

unsigned char BinaryChar::AddBitToChar(unsigned char c, int bitNumber, int bit)
{
	return (char)((int)c | (int)(bit << (7 - bitNumber)));
}

