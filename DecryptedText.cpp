#include "DecryptedText.h"

DecryptedText::DecryptedText(std::string text) : BaseText(text)
{
}

std::string DecryptedText::Encrypt(TextBlock key)
{
	std::string encryptedText;
	for (int i = 0; i < this->TextBlocksCount; i++)
	{
		TextBlock newWord = TextBlock(TextBlocks[i]) ^ key;
		newWord = newWord << 7;
		encryptedText += newWord.Word;
	}

	return encryptedText;
}
