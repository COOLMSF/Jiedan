#include <list>
#include <iostream>

#include "person.hpp"

#define MAX_ELEMENT 3

using namespace std;


class Student: public Person
{
public:
    string id;
    // 入学年份
    string enter_year;
    string address;
    string phone_number;
    string mail_code;
    string email;

public:
    Student();
    ~Student();

    void setInfo();
    string getInfo();
    string getInfoRaw();
};
