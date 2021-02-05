#pragma once
#include <string>
#include "BinaryWord.h"

class TextBlock 
{
public:
	TextBlock(std::string text);

	std::string Word;
	static const int Size = 16;

	const TextBlock operator <<(int bitsCount);
	const TextBlock operator >>(int bitsCount);
	const TextBlock operator ^(TextBlock other);
};

