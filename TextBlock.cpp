#include "TextBlock.h"
#include "BinaryWord.h"
#include <string>

using namespace std;

TextBlock::TextBlock(std::string text)
{
	if (text.length() != Size)
	{
		throw;
	}
	this->Word = text;
}

const TextBlock TextBlock::operator<<(int bitsCount)
{
	BinaryWord binaryWord(Word);
	int* bits = binaryWord.GetBits();
	int wordBitsCount = binaryWord.BitsCount();

	int* newBits = new int[wordBitsCount];
	for (int i = 0; i < wordBitsCount; i++)
	{
		int movedLeftPartIndex = wordBitsCount + i - bitsCount;
		int movedRightPartIndex = i - bitsCount;
		if (i < bitsCount)
		{
			newBits[i] = bits[movedLeftPartIndex];
		}
		else
		{
			newBits[i] = bits[movedRightPartIndex];
		}
	}

	return TextBlock(BinaryWord::GetWord(newBits, binaryWord.CharsCount()));
}

const TextBlock TextBlock::operator>>(int bitsCount)
{
	BinaryWord binaryWord(Word);
	int* bits = binaryWord.GetBits();
	int wordBitsCount = binaryWord.BitsCount();

	int* newBits = new int[wordBitsCount];
	for (int i = 0; i < wordBitsCount; i++)
	{
		int movedLeftPartIndex = i + bitsCount;
		int movedRightPartIndex = i + bitsCount - wordBitsCount;
		if (i < wordBitsCount - bitsCount)
		{
			newBits[i] = bits[movedLeftPartIndex];
		}
		else
		{
			newBits[i] = bits[movedRightPartIndex];
		}
	}

	return TextBlock(BinaryWord::GetWord(newBits, binaryWord.CharsCount()));
}

const TextBlock TextBlock::operator^(TextBlock other)
{
	string newWord = "";
	for (int i = 0; i < this->Word.length(); i++)
	{
		newWord += this->Word[i] ^ other.Word[i];
	}
	return TextBlock(newWord);
}
