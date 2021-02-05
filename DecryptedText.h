#pragma once
#include <string>
#include "EncryptedText.h"
#include "BaseText.h"
class DecryptedText : public BaseText
{
public:
	DecryptedText(std::string text);
	std::string Encrypt(TextBlock key);
};

