#include <iostream>
#include <fstream>
#include <string>
#include "MyCryptoAlgoritm.h"

using namespace std;

string ReadTextFromFile(char* path);

void WriteTextToFile(char* path, string text);

bool FileIsExist(string filePath);

const string decodeMode = "decode";
const string encodeMode = "encode";

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	if (argc != 4)
	{
		cout << "Вы не указали режим работы программы, путь до расшифрованного и зашифрованного текстовых файлов в аргументах командной строки. Работа программы завершена.";
		return -1;
	}
	// Аргументы идут так:
	// 0 - сам файл, который вызываем (наша программа), он нам не нужен;
	// 1 (programMode) - режим работы программы (decode/encode);
	// 2 (decodedFilePath) - путь к расшифрованному файлу;
	// 3 (encodedFilePath) - путь к зашифрованному файлу;
	char* programMode = argv[1];
	char* decodedFilePath = argv[2];
	char* encodedFilePath = argv[3];

	// если какой-то из файлов не существует, то останавливаем работу программы
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
		// получаем зашифрованный текст из файла
		string encodedText = ReadTextFromFile(encodedFilePath);

		// объявляем алгоритм шифрования
		MyCryptoAlgoritm algoritm(16, 7);

		// получаем расшифрованный текст благодаря алгоритму
		string decodedText = algoritm.DecryptText(encodedText);

		// записываем полученный расшифрованный текст в файл
		WriteTextToFile(decodedFilePath, decodedText);
		cout << "Текст успешно расширован и записан в " << decodedFilePath;
	}
	else if (programMode == encodeMode)
	{
		// получаем расшифрованный текст из файла
		string decodedText = ReadTextFromFile(decodedFilePath);

		// объявляем алгоритм шифрования
		MyCryptoAlgoritm algoritm(16, 7);

		// получаем зашифрованный текст благодаря алгоритму
		string encodedText = algoritm.EncryptText(decodedText);

		// записываем полученный зашифрованный текст в файл
		WriteTextToFile(encodedFilePath, encodedText);
		cout << "Текст успешно заширован и записан в " << encodedFilePath;
	}
	return 0;
}

bool FileIsExist(string filePath)
{
	bool isExist = false;
	ifstream fin(filePath.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}

string ReadTextFromFile(char* path)
{
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

void WriteTextToFile(char* path, string text)
{
	ofstream writeStream(path);
	if (writeStream.is_open())
	{
		writeStream << text;
	}
	writeStream.close();
}
