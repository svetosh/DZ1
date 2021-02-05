#include "BinaryWord.h"
#include <string>
#include "BinaryChar.h"

using namespace std;

BinaryWord::BinaryWord(std::string word)
{
	this->Word = word;
}

int BinaryWord::BitsCount()
{
	int bitsInChar = BinaryChar::BitsInChar;
	return CharsCount() * bitsInChar;
}

int BinaryWord::CharsCount()
{
	return Word.length();
}

int* BinaryWord::GetBits()
{
	int bitsCount = this->BitsCount();
	int* bits = new int[bitsCount];

	int currentPosition = 0;
	for (int i = 0; i < Word.length(); i++)
	{
		unsigned char symbol = Word[i];
		BinaryChar binarySymbol(symbol);
		int* currentBits = binarySymbol.GetBits();

		int bitsInChar = BinaryChar::BitsInChar;
		for (int j = 0; j < bitsInChar; j++)
		{
			bits[currentPosition] = currentBits[j];
			currentPosition++;
		}
	}

	return bits;
}

std::string BinaryWord::GetWord(int* bits, int charsCount)
{
	string result = "";

	int currentBitPosition = 0;
	for (int i = 0; i < charsCount; i++)
	{
		int* currentCharBits = new int[BinaryChar::BitsInChar];
		for (int j = 0; j < BinaryChar::BitsInChar; j++)
		{
			currentCharBits[j] = bits[currentBitPosition];
			currentBitPosition++;
		}
		unsigned char c = BinaryChar::GetCharFromBits(currentCharBits);
		result += c;
	}
	return result;
}


