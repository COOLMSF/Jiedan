#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) 
{
    double a;
     ifstream fin(argv[1]);

     while (fin >> a) {
         printf("%lf", a);
     }
}