#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

void fill_blocks(vector<string>& vec, const string& text, unsigned int BlockSizeData) // заполнение для ровного делания и разхделдение на блоки по 16
{
    unsigned int a = 0;
    unsigned int howManyBlocks = BlockSizeData - text.length() % BlockSizeData;
    char randCh = rand() % 101;
    string textChunk = text;
    for (int i = 0; i < howManyBlocks; ++i)
    {
        textChunk += randCh;
    }
    for (int i = 0; i < textChunk.length() / BlockSizeData; ++i)
    {
        vec.push_back(textChunk.substr(a, BlockSizeData));
        a += BlockSizeData;
    }
}
void cryptedkey(unsigned int BlockSizeData, int& key, string& stringKey)
{
    key = 0;
    int a;
    for (int i = 0; i < BlockSizeData / 2; ++i)
    {
        a = rand() % 100;
        key += key * 100 + a;
        stringKey += static_cast<char>(a);
    }
}

string creatBinary(int i)
{
    string result;
    while (i > 0)
    {
        result += to_string(i % 2);
        i /= 2;
    }
    reverse(result.begin(), result.end());
    while (result.length() % 8 != 0)
    {
        result = "0" + result;
    }
    return result;
}
string createByte(const string& str)
{
    string res;
    for (const char& sym : str)
    {
        int num_sym = static_cast<unsigned char>(sym);
        string bin = creatBinary(num_sym);
        res += bin;
    }
    return res;
}

int createDec(string& str)
{
    long long res = 0;
    int count = 0;
    while (str[0] == '0')
    {
        str.erase(0, 1);
    }
    while (!str.empty())
    {
        res += static_cast<long long>((str[str.length() - 1] - '0') * pow(2, count));
        str.erase(str.length() - 1);
        ++count;
    }
    return res;
}

void shifting(string& str, unsigned int ShiftSize, const string& leftOrRight)  //  сразу для кодирования и раскодирования
{
    string result;
    if (leftOrRight == ">>")
    {
        rotate(str.begin(), str.begin() + ShiftSize, str.end());
    } else 
    {
        rotate(str.rbegin(), str.rbegin() + ShiftSize, str.rend());
    }
    while (!str.empty())
    {
        string add = str.substr(0, 8);
        result += static_cast<char>(createDec(add));
        str.erase(0, 8);
    }
    str = result;
}

int main() {
    setlocale(LC_ALL, "rus");
    ofstream inputText("inputText.txt");
    if (!inputText)
    {
        cout << "Ошибка открытия файла" << endl;
        return -1;
    }
    else
    {
        cout << "Файл открыт и вы можете ввести текст," << endl
             << "с которым хотите работать." << endl;
    }
    string text;
    getline(cin, text);  //  получение начального текста
    inputText << text;
    cout << endl;
    inputText.close();

    ofstream encrypt("Encrypted.txt");  //  Encrypted
    vector<string> vec;
    const unsigned int BlockSizeData = 16;
    fill_blocks(vec, text, BlockSizeData);  
    int key[2];
    string stringKey[2];
    for (string& i : vec)
    {
        cryptedkey(BlockSizeData, key[0], stringKey[0]);  //  создаем две части гаммы
        cryptedkey(BlockSizeData, key[1], stringKey[1]);
        string mainKey = stringKey[0] + stringKey[1];  //  полная гамма
        cout << "Используемый ключ: " << key << endl;
        for (int j = 0; j < i.length(); ++j)
        {
            i[j] ^= mainKey[j];  //  каждый байт гаммы побитово XOR 
        }
    }
    const unsigned int ShiftSize = 7;
    for (string& i : vec)
    {
        string byte = createByte(i);  //  представляем в байтовом виде
        shifting(byte, ShiftSize, ">>");  //  выполняем сдвиг
        i = byte;
    }
    for (const string& i : vec)
    {
        encrypt << i;  //  выводим в файл
    }
    encrypt.close();

    ofstream decrypt("Decrypted.txt"); //  Decrypting
    for (string& i : vec)
    {
        string byte = createByte(i);  //  представляем в байтовом виде
        shifting(byte, ShiftSize, "<<");  //  сдвигаем в обратную строну на shift
        i = byte;
    }
    for (string& i : vec)
    {
        cryptedkey(BlockSizeData, key[0], stringKey[0]);  //  создаем туже гамму 
        cryptedkey(BlockSizeData, key[1], stringKey[1]);
        string mainKey = stringKey[0] + stringKey[1];
        for (int j = 0; j < i.length(); ++j)
        {
            i[j] ^= mainKey[j];  //  каждый байт гаммы побитово XOR
        }
    }
    for (const string& i : vec)
    {
        decrypt << i;  //  выводим в файл
    }
    return 0;
}