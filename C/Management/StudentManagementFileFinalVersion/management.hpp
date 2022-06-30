#include <iostream>
#include <list>

#include "student.hpp"

using namespace std;

class Management
{
private:
    string name;

public:
    list<Student> students;
    Management(string name);
    ~Management();
    
    void welcome();
    int addStudent(Student stu);
    int delStudentByName(string name);
    int modifyStudentByName(string name);
    int queryStudentByName(string name);
    int queryStudentByYear(string year);
    int sort();
    int saveToFile();
    int readFromFile();
    int showAll();
};
