#include <iostream>

#include "management.h"

Management::Management(string name)
{
    this->name = name;
}

Management::~Management()
{
    // delete this;
}

void Management::welcome() {
    cout << "1:) 添加学生" << endl;
    cout << "2:) 删除学生" << endl;
    cout << "3:) 修改学生" << endl;
    cout << "4:) 查询学生" << endl;
    cout << "5:) 统计" << endl;
    cout << "6:) 保存数据到mysql服务器" << endl;
    cout << "7:) 从mysql服务器读取数据" << endl;
    cout << "8:) 退出" << endl;
}

int Management::addStudent(Student stu) {
    this->students.push_back(stu);
}

int Management::delStudentByName(string name) {
    for (list<Student>::iterator it = this->students.begin(); it != this->students.end()) {
        if ((*it).getName() == name) {
            this->students.erase(it);
        } else {
		it++;
	}
    }
}

int Management::modifyStudentByName(string name) {
    string newName;
    string newGender;

    for (list<Student>::iterator it = this->students.begin(); it != this->students.end();
    it++) {
        if ((*it).getName() == name) {
            cout << "成员已找到" << endl;

            cout << "请输入新的名字:" << endl;
            cin >> newName;
            (*it).setName(newName);
 
            cout << "请输入新的性别:" << endl;
            cin >> newGender;
            (*it).setGender(newGender);

            cout << "修改成功";
        }
    }
}

int Management::queryStudentByName(string name) {
    for (list<Student>::iterator it = this->students.begin(); it != this->students.end();
    it++) {
        if ((*it).getName() == name) {
            cout << "成员已找到" << endl;

            cout << "姓名:" << (*it).getName() << endl;
            cout << "性别:" << (*it).getGender() << endl;
            cout << "成绩(语文，数学，英语):" << endl;
            (*it).printScore();
        }
    }
}

int Management::showStat() {

}

int Management::saveToMysqlServer() {
    // Management management;
    try {
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://localhost:3306", "test", "testtest");
    /* Connect to the MySQL test database */
    con->setSchema("test_database");

    stmt = con->createStatement();

    for (std::list<Student>::iterator it = this->students.begin(); 
		    it != this->students.end(); ++it) {
        string name;
        string gender;
        int yuwenScore, shuxueScore, yingyuScore;

        name = it->getName();
        gender = it->getGender();
        yuwenScore = it->score[0];
        shuxueScore = it->score[1];
        yingyuScore = it->score[2];

	char buf[1024];
	char buff[100];
        sprintf(buff, "insert into test_table values( \"%s\", \"%s\", %d, %d, %d);", name.c_str(), gender.c_str(), yuwenScore, shuxueScore, yingyuScore);
  	std::string sqlString = buff;

	cout << "sqlstring:" << sqlString << endl;
        stmt->execute(sqlString);
    }

    cout << "保存成功" << endl;
    delete stmt;
    delete con;

} catch (sql::SQLException &e) {
  cout << "# ERR: SQLException in " << __FILE__;
  cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
  cout << "# ERR: " << e.what();
  cout << " (MySQL error code: " << e.getErrorCode();
  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}

cout << endl;
}

int Management::readFromMysqlServer() {
    // Management management;
    try {
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://localhost:3306", "test", "testtest");
    /* Connect to the MySQL test database */
    con->setSchema("test_database");

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * from test_table");

    for (std::list<Student>::iterator it = this->students.begin(); it != this->students.end();it++) {
    }

    while (res->next()) {
        string name;
        string gender;
        int yuwenScore, shuxueScore, yingyuScore;
	Student stu;

	name = res->getString(1);
	gender = res->getString(2);
        stu.setName(name);
        stu.setGender(gender);
        stu.score[0] = res->getInt(3);
        stu.score[1] = res->getInt(4);
        stu.score[2] = res->getInt(5);

    	this->students.push_back(stu);
    }
    cout << "远程获取数据成功" << endl;
    delete res;
    delete stmt;
    delete con;

} catch (sql::SQLException &e) {
  cout << "# ERR: SQLException in " << __FILE__;
  cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
  cout << "# ERR: " << e.what();
  cout << " (MySQL error code: " << e.getErrorCode();
  cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}

cout << endl;
}
