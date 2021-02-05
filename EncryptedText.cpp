#include "EncryptedText.h"

EncryptedText::EncryptedText(std::string text) : BaseText(text)
{
}

std::string EncryptedText::Decrypt(TextBlock key)
{
	std::string decryptedText;
	for (int i = 0; i < this->TextBlocksCount; i++)
	{
		TextBlock newWord = TextBlock(TextBlocks[i]) >> 7;
		newWord = key ^ newWord;
		decryptedText += newWord.Word;
	}

	decryptedText = TrimSubstitutionBlock(decryptedText);

	return decryptedText;
}
