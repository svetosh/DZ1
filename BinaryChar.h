#pragma once
class BinaryChar
{
public:
	BinaryChar(unsigned char);

	static const int BitsInChar = 8;
	unsigned char Symbol;

	int* GetBits();
	static unsigned char GetCharFromBits(int*);
private:
	int charToBit(unsigned char, int);
	static unsigned char AddBitToChar(unsigned char, int, int);
};

