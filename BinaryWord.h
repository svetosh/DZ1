#pragma once
#include <string>

class BinaryWord
{
public:
	BinaryWord(std::string word);

	std::string Word;

	int BitsCount();
	int CharsCount();
	int* GetBits();
	static std::string GetWord(int* bits, int charsCount);
};

