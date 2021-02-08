#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Block
{
    unsigned char data[16] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
};



void readFile(vector<Block>& data, string& inputName)
{
    ifstream iread(inputName, ios::binary);
    Block buffer;
    while (!iread.eof())
    {
        iread.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
        if(!iread.eof())
        data.push_back(buffer);
        [&buffer]() { for (int i = 0; i < 16; i++) buffer.data[i] = '\0'; };
    }
    iread.close();
}

void writeFile(vector<Block>& data, string& outputFile)
{
    ofstream owrite(outputFile, ios::binary);
    for (int i = 0; i < data.size(); i++)
    {
        owrite.write(reinterpret_cast<char*>(&data[i]), sizeof(data[i]));
    }
    owrite.close();
}

void gamming(vector<Block>& b, int& key)
{
    srand(key);
    key = rand();
    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < 16; j++)
        {
            b[i].data[j] = b[i].data[j] ^ rand();
        }
    }
}

void operator<<(Block& b, int& shift)
{
    unsigned char* d = new unsigned char[16];
    for (int i = 0; i < 16; i++)
        d[i] = b.data[i];
    for (int i = 0; i < 16; i++)
    {
        b.data[i] = (d[i] << shift) | (d[(i + 1) % 16] >> (16 - shift));
    }
    delete[] d;
}

void operator>>(Block& b, int& shift)
{
    unsigned char* d = new unsigned char[16];
    for (int i = 0; i < 16; i++)
        d[i] = b.data[i];
    for (int i = 0; i < 16; i++)
    {
        b.data[i] = (d[i] >> shift) | (d[(i + 15) % 16] << (16 - shift));
    }
    delete[] d;
}

void shifting(vector<Block>& b, int& shift) 
{
    char where = 1;
    if (shift < 0)
    {
        shift = -shift;
        where = -1;
    }

    for (int i = 0; i < b.size(); i++) {
        if (where > 0) {
            b[i] >> shift;
        }
        else {
            b[i] << shift;
        }
    }
}

void coding(string& inputName, string& outputName, int& key, int shift)
{
    vector<Block> b;
    readFile(b, inputName);
    cout << "1";
    srand(key);
    cout << "2";
    gamming(b, key);
    cout << "3";
    shifting(b, shift);
    cout << "4";
    writeFile(b, outputName);
    cout << "5";
}

void decoding(string& inputName, string& outputName, int& key, int shift)
{
    vector<Block> b;
    readFile(b, inputName);
    cout << "1";
    shifting(b, shift);
    cout << "2";
    srand(key);
    cout << "3";
    gamming(b, key);
    cout << "4";
    writeFile(b, outputName);
    cout << "5";
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    for (int i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }
    if (argc != 5)
    {
        cout << "-----------404-------------" << endl;
        return -1;
    }
    string command = argv[1];
    string inputFile = argv[2];
    string outputFile = argv[3];
    int key = atoi(argv[4]);

    if (command == "encode")
    {
        coding(inputFile, outputFile, key, -7);
    }
    else if(command == "decode")
    {
        decoding(inputFile, outputFile, key, 7);
    }
    return 0;
}
