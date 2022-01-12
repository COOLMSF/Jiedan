#include "person.h"

string Person::getName() {
    return this->name;
}

string Person::getGender() {
    return this->gender;
}

void Person::setName(string name) {
    this->name = name;
}

void Person::setGender(string gender) {
    this->gender = gender;
}

Person::Person()
{

}

Person::Person(string name, string gender)
{
    this->name = name;
    this->gender = gender;
}

Person::~Person()
{
}