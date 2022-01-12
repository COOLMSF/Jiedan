#include <list>
#include <iostream>

#include "person.h"

#define MAX_ELEMENT 3

using namespace std;

class Student: public Person
{
private:
    int id;
    string major;

public:
    Student();
    ~Student();

    int score[MAX_ELEMENT];
    string getMajor();
    void setMajor();
    void setScore();
    void printScore();
};
