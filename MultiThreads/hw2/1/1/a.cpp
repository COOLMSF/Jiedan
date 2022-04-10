#include <string>
#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char const* argv[])
{
    string str = "106.85.76.114:";

    for (int i = 0; i < 1000; i++) {
        cout << str + to_string(abs((rand() * 1000) % 5000 + 600)) << endl;
    }
    return 0;
}
