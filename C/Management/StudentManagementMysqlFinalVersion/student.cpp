#include <iostream>
#include <list>

#include "student.h"

using namespace std;


Student::Student()
{
    Person();
}

Student::~Student()
{
}


string Student::getMajor() {
    return this->major;
}

void Student::setScore() {
    cout << "请依次输入学生成绩，(语文，数学，英语)" << endl;
    for (int i = 0; i < MAX_ELEMENT; i++) {
        cin >> score[i];
    }
    cout << "[+] 成绩录入成功" << endl;
}

void Student::printScore() {
    for (int i = 0; i < MAX_ELEMENT; i++) {
        cout << score[i] << endl;
    }
}