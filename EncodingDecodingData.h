#pragma once
#include <string>
#include "TextBlock.h"

int main(int argc, char* argv[]);

std::string ReadTextFromFile(char* path);
void WriteTextToFile(char* path, std::string text);

bool FileIsExist(std::string filePath);
TextBlock GenerateKey(int size);

const std::string decodeMode = "decode";
const std::string encodeMode = "encode";
