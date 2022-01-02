#include <iostream>
#include <string>

using namespace std;


int main(){
    string s1;
    getline(cin, s1); // get the whole line as input
    cout << "string: " << s1 << endl;
    cout << "hexval: ";
    for(int i = 0; i < s1.size(); i++) {
        int character = int(s1[i]); // converting each character to its ascii value 
        cout << hex << character; // basefield is now set to hex
    }
    cout << endl;
}
