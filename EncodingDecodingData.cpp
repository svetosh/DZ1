#include <iostream>
#include <fstream>
#include <string>
#include "TextBlock.h"
#include "DecryptedText.h"
#include "EncodingDecodingData.h"

using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	if (argc < 5)
	{
		cout << "Вы не указали режим работы программы, путь до расшифрованного и зашифрованного текстовых файлов или ключ криптосистемы в аргументах командной строки. Работа программы завершена.";
		return -1;
	}
	// Аргументы идут так:
	// 0 - сам файл, который вызываем (наша программа), он нам не нужен;
	// 1 (programMode) - режим работы программы (decode/encode);
	// 2 (decodedFilePath) - путь к расшифрованному файлу;
	// 3 (encodedFilePath) - путь к зашифрованному файлу;
	// 4 (key) - ключ криптосистемы
	char* programMode = argv[1];
	char* decodedFilePath = argv[2];
	char* encodedFilePath = argv[3];
	TextBlock key = TextBlock(argv[4]);

	if (!FileIsExist(decodedFilePath) || !FileIsExist(encodedFilePath))
	{
		cout << "Какой-то из файлов не существует, проверьте правильность указанных путей:\r\n";
		cout << "Путь до расшифрованного файла: " << decodedFilePath << "\r\n";
		cout << "Путь до зашифрованного файла: " << encodedFilePath << "\r\n";
		return -1;
	}
	else 
	{
		cout << "Файлы проверены:\r\n";
		cout << "Путь до расшифрованного файла: " << decodedFilePath << "\r\n";
		cout << "Путь до зашифрованного файла: " << encodedFilePath << "\r\n";
	}

	if (programMode != decodeMode && programMode != encodeMode)
	{
		cout << "Указан неверный режим работы программы (" << programMode << "), может быть лишь " << decodeMode << " или " << encodeMode;
		return -1;
	}
	else if (programMode == decodeMode)
	{
		EncryptedText encrypted = EncryptedText(ReadTextFromFile(encodedFilePath));

		DecryptedText decrypted = DecryptedText(encrypted.Decrypt(TextBlock(key)));

		WriteTextToFile(decodedFilePath, decrypted.Text);
		cout << "Текст успешно расширован и записан в " << decodedFilePath;
	}
	else if (programMode == encodeMode)
	{
		DecryptedText decrypted = DecryptedText(ReadTextFromFile(decodedFilePath));

		EncryptedText encrypted = EncryptedText(decrypted.Encrypt(key));

		WriteTextToFile(encodedFilePath, encrypted.Text);
		cout << "Текст успешно заширован и записан в " << encodedFilePath;
	}
	return 0;
}

/// <summary>
/// Проверяет наличие существования файла
/// </summary>
/// <param name="filePath">Путь к файлу</param>
/// <returns>true если файл существует</returns>
bool FileIsExist(string filePath)
{
	bool isExist = false;
	ifstream fin(filePath.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}

/// <summary>
/// Чтение из файла
/// </summary>
/// <param name="path">Путь к файлу</param>
/// <returns>Строка с текстом из файла</returns>
string ReadTextFromFile(char* path)
{
	// поток для чтения
	ifstream readStream(path);

	string line;
	string result;
	if (readStream.is_open())
	{
		while (getline(readStream, line))
		{
			result += line;
		}
	}

	readStream.close();
	return result;
}

/// <summary>
/// Запись в файл
/// </summary>
/// <param name="path">Путь к файлу, в который записывать</param>
/// <param name="text">Текст, который нужно записать в файл</param>
void WriteTextToFile(char* path, string text)
{
	// поток для записи
	ofstream writeStream(path);

	if (writeStream.is_open())
	{
		writeStream << text;
	}

	writeStream.close();
}

/// <summary>
/// Генератор псевдослучайных чисел
/// </summary>
/// <param name="size">Размер строки для генерации</param>
/// <returns>Строка из чисел</returns>
TextBlock GenerateKey(int size) 
{
	std::string key;
	for (int i = 0; i < size; i++)
	{
		key += to_string(rand() % 9);
	}
	return TextBlock(key);
}

