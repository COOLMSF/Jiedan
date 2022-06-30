#include <iostream>
#include <list>

#include "student.hpp"

using namespace std;


Student::Student()
{
    Person();
}

Student::~Student()
{
}

void Student::setInfo()
{
    string name;
    string gender;

    cout << "Input name: ";
    cin >> name;
    this->setName(name);

    cout << "Input gender: ";
    cin >> gender;
    this->setGender(gender);

    cout << "Input ID: ";
    cin >> this->id;

    cout << "Input enter year: ";
    cin >> this->enter_year;

    cout << "Input addr: ";
    cin >> this->address;

    cout << "Input mail code: ";
    cin >> this->mail_code;

    cout << "Input e-mail: ";
    cin >> this->email;
}

string Student::getInfo()
{
    string data;
    data += "name: " + this->getName() + "\n";
    data += "gender: " + this->getGender() + "\n";
    data += "id: " + this->id + "\n";
    data += "enter year: " + this->enter_year + "\n";
    data += "addr: " + this->address + "\n";
    data += "mail code: " + this->mail_code + "\n";
    data += "e-mail: " + this->email + "\n";
    
    return data;
}

string Student::getInfoRaw()
{
    string data;

    data += this->getName() + " ";
    data += this->getGender() + " ";
    data += this->id + " ";
    data += this->enter_year + " ";
    data += this->address + " ";
    data += this->phone_number + " ";
    data += this->mail_code + " ";
    data += this->email + "\n";

    return data;
}