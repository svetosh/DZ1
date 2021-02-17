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
            data.push_back(buffer);
                for (char i = 0; i < 16; i++) 
                    buffer.data[i] = '\0';
    }
    iread.close();
}

void writeFile(vector<Block>& data, string& outputFile, int& fix)
{
    ofstream owrite(outputFile, ios::binary);

    for (int i = 0; i < data.size() - 2 * fix; i++)
    {
        owrite.write(reinterpret_cast<char*>(&data[i]), sizeof(data[i]));
    }

    if (fix == 1) 
    {
        uint64_t last_index = data.size() - 2;
        for (uint32_t i = 0; i < 16; ++i) 
        {
            if (data[last_index].data[i] != '\0')
            {
                owrite.write(reinterpret_cast<char*>
                    (&data[last_index].data[i]),
                    sizeof(data[last_index].data[i]));
            }
            else
            {
                break;
            }
        }
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
        b.data[i] = (d[i] << shift) | (d[(i + 1) % 16] >> (8 - shift));
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
        b.data[i] = (d[i] >> shift) | (d[(i + 15) % 16] << (8 - shift));
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
    int fix = 0;
    readFile(b, inputName);
    srand(key);
    gamming(b, key);
    shifting(b, shift);
    writeFile(b, outputName, fix);
}

void decoding(string& inputName, string& outputName, int& key, int shift)
{
    vector<Block> b;
    int fix = 1;
    readFile(b, inputName);
    shifting(b, shift);
    srand(key);
    gamming(b, key);
    writeFile(b, outputName, fix);
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
    else if (command == "decode")
    {
        decoding(inputFile, outputFile, key, 7);
    }
    return 0;
}
