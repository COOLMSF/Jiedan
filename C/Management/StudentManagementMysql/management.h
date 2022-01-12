#include <iostream>
#include <list>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "student.h"
#include "mysql_connection.h"


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
    int showStat();
    int saveToMysqlServer();
    int readFromMysqlServer();
};
