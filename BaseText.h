#pragma once
#include <string>
#include "TextBlock.h"
class BaseText
{
public:
	BaseText(std::string text);
	std::string Text;
protected:
	const char substitutionSymbol = '#';
	std::string* TextBlocks;
	int TextBlocksCount;

	std::string TrimSubstitutionBlock(std::string text);
private:
	void TransformToTextBlocks(std::string text);
};

