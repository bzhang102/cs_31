#include <iostream>
using namespace std;

void removeS(char* ptr) {
    char* safe = ptr;
    while(*ptr != 0) {
        if(*ptr != 's' && *ptr != 'S') {
            *safe = *ptr;
            safe++;
        }
        ptr++;
    }
    *safe = 0;
}

int main()
{
    char msg[50] = "She'll blossom like a massless princess.";
    removeS(msg);
    cout << msg << endl;  // prints   he'll bloom like a male prince.
}
