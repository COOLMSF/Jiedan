#include <iostream>

using namespace std;

class Person
{
private:
    string name;
    string gender;
public:
    Person();
    Person(string name, string gender);
    ~Person();

    string getName();
    string getGender();
    void setName(string name);
    void setGender(string gender);
};
