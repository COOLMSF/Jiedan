#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char const *argv[])
{
    string total_string = "";
    string field1 = "06/04/2022-";

    string field2[] = {
        "ET POLICY Python-urllib/ Suspicious User Agent",
        "SURICATA Applayer Detect protocol only one direction"
        " ET SCAN Potential SSH Scan"
    };

    string field3[] = {
        "[Classification: Attempted Information Leak]",
        "[Classification: Generic Protocol Command Decode]",
        "[Classification: Misc Attack]"
    };

    string field4 = "10.0.16.2:";

    string field5 = "169.254.0.4:80";

    fstream fout;

    fout.open("result.txt");

    int n = 500;

    for (int i = 0; i < n; i++) {
        string rand24, rand60, rand601, rand96;

        int rand_num = rand() % 24;
        if (rand_num < 10)
            rand24 = "0" + to_string(rand_num);
        else
        rand24 = to_string(rand_num);

        rand_num = rand() % 60;
        if (rand_num < 10)
            rand60 = "0" + to_string(rand_num);
        else
        rand60 = to_string(rand_num);

        rand_num = rand() % 60;
        if (rand_num < 10)
            string rand601 = "0" + to_string(rand_num);
        else
        rand601 = to_string(rand_num);

        rand_num = rand() % 999999;
        if (rand_num < 100000)
            rand96 = "0" + to_string(rand_num);
        else
        rand96 = to_string(rand_num);

        fout << field1 + rand24 + ":" + rand60 + ":" + rand601 + "." + rand96<< endl;
    }

    fout.close();

    return 0;
}

