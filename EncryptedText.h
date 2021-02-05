#pragma once
#include <string>
#include "TextBlock.h"
#include "BaseText.h"
#include "DecryptedText.h"

class EncryptedText : public BaseText
{
public:
	EncryptedText(std::string text);
	std::string Decrypt(TextBlock key);
};

