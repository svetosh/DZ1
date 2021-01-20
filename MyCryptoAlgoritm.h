#include <string>
#include "TextBlock.h"

using namespace std;

// Алгоритм шифрования 
class MyCryptoAlgoritm
{
public:

	unsigned int textBlockSize;
	unsigned int bitShiftCount;

	MyCryptoAlgoritm(unsigned int textBlockSize, int unsigned bitShiftCount)
	{
		this->textBlockSize = textBlockSize;
		this->bitShiftCount = bitShiftCount;
	}

	/// Зашифровывает текст
	string EncryptText(string decryptedText)
	{
		string result = "";
		for (int i = 0; i < decryptedText.length(); i += this->textBlockSize)
		{
			string decodedBlock = decryptedText.substr(i, this->textBlockSize);
			TextBlock textBlock(this->textBlockSize, this->bitShiftCount);
			string key = textBlock.GetRandomGamma();
			if (decodedBlock.length() != this->textBlockSize)
			{
				key = key.substr(0, decodedBlock.length());
			}
			string encodedBlock = textBlock.EncodeTextByKey(decodedBlock, key);
			result += key + encodedBlock;
		}
		return result;
	}

	/// Расшифровывает текст
	string DecryptText(string encryptedText)
	{
		string result = "";
		for (int i = 0; i < encryptedText.length(); i += this->textBlockSize * 2)
		{
			string encodedBlock = encryptedText.substr(i, this->textBlockSize * 2);
			TextBlock textBlock(this->textBlockSize, this->bitShiftCount);
			string decodedText = "";

			if (encodedBlock.length() == this->textBlockSize * 2)
			{
				string key = encodedBlock.substr(0, this->textBlockSize);
				string encodedText = encodedBlock.substr(this->textBlockSize, this->textBlockSize);
				decodedText = textBlock.DecodeTextByKey(encodedText, key);
			}
			else 
			{
				int keySize = encodedBlock.length() / 2;
				string key = encodedBlock.substr(0, keySize);
				string encodedText = encodedBlock.substr(keySize, keySize);
				decodedText = textBlock.DecodeTextByKey(encodedText, key);
			}
			result += decodedText;
		}
		return result;
	}
};

