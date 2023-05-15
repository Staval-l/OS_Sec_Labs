#include <iostream>
#include "blowfish.h"

int main(int argc, const char * argv[])
{
    unsigned char key[] = "The quick brown fox jumps over the lazy dog.";

    Blowfish blowfish;
    blowfish.SetKey(key, sizeof(key));

    // Input/Output length must be a multiple of the block length (64bit)
    unsigned char text[16] = "There's nothing";

    blowfish.Encrypt(text, text, sizeof(text));
    std::cout << text << std::endl;

    blowfish.Decrypt(text, text, sizeof(text));
    std::cout << text << std::endl;

    return 0;
}