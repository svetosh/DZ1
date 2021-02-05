#include "BaseText.h"

BaseText::BaseText(std::string text)
{
	this->Text = text;
	this->TransformToTextBlocks(text);
}

std::string BaseText::TrimSubstitutionBlock(std::string text)
{
	int j = text.length() - 1;
	char c = substitutionSymbol;
	do
	{
		c = text[j];
		if (c != substitutionSymbol || j <= 0)
		{
			break;
		}
		text.erase(j);
		j--;
	} while (c == substitutionSymbol);
	return text;
}

void BaseText::TransformToTextBlocks(std::string text)
{
	int textBlocksCount = text.length() / TextBlock::Size;
	if (text.length() % TextBlock::Size != 0)
	{
		textBlocksCount++;
	}
	std::string* textBlocks = new std::string[textBlocksCount];

	for (int i = 0; i < textBlocksCount; i++)
	{
		int currentStartPosition = TextBlock::Size * i;
		std::string textPart = text.substr(currentStartPosition, TextBlock::Size);

		if (textPart.length() < TextBlock::Size)
		{
			for (int j = textPart.length(); j < TextBlock::Size; j++)
			{
				textPart += substitutionSymbol;
			}
		}
		textBlocks[i] = textPart;
	}
	this->TextBlocks = textBlocks;
	this->TextBlocksCount = textBlocksCount;
}
