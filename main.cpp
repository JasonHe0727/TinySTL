#include <iostream>
#include "yl/String.hpp"
#include <vector>

using std::cout;
using std::endl;

int main()
{
    String text = "hello, world!";
    cout << "string length: " << text.size() << endl;
    for (int i = 0; i < text.size(); i++)
    {
        uint8_t *str = Encoding::Utf16CharacterToUtf8(text[i]);
        for (int k = 0; k < 6; k++)
        {
            cout << (char) str[k] << endl;
        }
    }
    return 0;
}