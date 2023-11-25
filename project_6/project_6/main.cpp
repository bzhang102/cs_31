#include <iostream>
using namespace std;

void removeS(char* ptr) {
    while(*ptr != 0) {
        if(*ptr == 's' || *ptr == 'S') {
            for(char* shift = ptr; *shift != 0; shift++) {
                *shift = *(shift + 1);
            }
        } else {
            ptr++;
        }
    }
}

int main()
{
    char msg[50] = "She'll blossom like a massless princess.";
    removeS(msg);
    cout << msg << endl;  // prints   he'll bloom like a male prince.
}
