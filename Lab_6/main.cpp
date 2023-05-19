#include "blowfish.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

void Read_Encrypt(string str, string& txt)
{
    ifstream data_1; // Open file with text
    data_1.open(str);

    if(data_1.is_open()) {
        while (getline(data_1, txt)) {
            data_1 >> txt;
        }
    }

    data_1.close();
}

void Write_Encrypt(string str, string& txt)
{
    ofstream data(str);
    if (data.is_open()) {
        data << txt;
    }
    data.close();
}

int main(int argc, const char * argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned char key[] = "Love you.";

    Blowfish blowfish;
    blowfish.SetKey(key, sizeof(key));

    // Input/Output length must be a multiple of the block length (64bit)
    string text;
    unsigned char txt[264];

    //Read_Encrypt("Text.txt", reinterpret_cast<string &>(text));

    Read_Encrypt("Encrypt.txt", reinterpret_cast<string &>(text));

    strcpy((char *)txt, text.c_str());

//    blowfish.Encrypt(txt, txt, sizeof(txt));
//    text = (const char *)txt;
//    Write_Encrypt("Encrypt.txt", reinterpret_cast<string &>(text));
//    SetConsoleCP(866);
//    SetConsoleOutputCP(866);
//    std::cout << txt << std::endl;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    blowfish.Decrypt(txt, txt, sizeof(txt));
    text = (const char *)txt;
    Write_Encrypt("Decrypt.txt", reinterpret_cast<string &>(text));
    SetConsoleCP(866);
    SetConsoleOutputCP(866);
    std::cout << txt << std::endl;

    return 0;
}