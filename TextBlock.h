#include <string>

using namespace std;

class TextBlock
{
public:

	TextBlock(unsigned int textBlockSize, unsigned int bitShiftCount)
	{
		this->textSize = textBlockSize;
		this->shiftSize = bitShiftCount;
	}
	unsigned int textSize;
	unsigned int shiftSize;
	string GetRandomGamma() 
	{
		string entropy = "";
		for (int i = 0; i < this->textSize; i++)
		{
			entropy += to_string(rand() % 10);
		}
		return entropy;
	}
	/// Шифрование расшифрованного текста
	string EncodeTextByKey(string decodedText, string key)
	{
		string encodedText = "";
		for (int i = 0; i < decodedText.length(); i++)
		{
			char symbol = decodedText[i];
			char keySymbol = key[i];
			char newSymbol = LeftShift(symbol);
			newSymbol = newSymbol ^ keySymbol;
			encodedText += newSymbol;
		}
		return encodedText;
	}
	/// Расшифровка зашифрованного текста
	string DecodeTextByKey(string encodedText, string key)
	{
		string decodedText = "";
		for (int i = 0; i < encodedText.length(); i++)
		{
			char symbol = encodedText[i];
			char keySymbol = key[i];
			char newSymbol = symbol ^ keySymbol;
			newSymbol = RightShift(newSymbol);
			decodedText += newSymbol;
		}
		return decodedText;
	}

	/// Сдвиг влево
	unsigned char LeftShift(unsigned char sourceChar)
	{
		int bitsInChar = sizeof(sourceChar) * 8;
		return (sourceChar << shiftSize) | (sourceChar >> (bitsInChar - this->shiftSize));
	}

	/// Сдвиг вправо
	unsigned char RightShift(unsigned char sourceChar)
	{
		int bitsInChar = sizeof(sourceChar) * 8;
		return (sourceChar >> shiftSize) | (sourceChar << (bitsInChar - this->shiftSize));
	}
};

