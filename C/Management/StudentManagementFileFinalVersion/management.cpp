#include <iostream>
#include <fstream>

#include "management.hpp"

Management::Management(string name)
{
    this->name = name;
}

Management::~Management()
{
    // delete this;
}

void Management::welcome() 
{
    cout << "1:) 添加学生" << endl;
    cout << "2:) 删除学生" << endl;
    cout << "3:) 修改学生" << endl;
    cout << "4:) 查询学生" << endl;
    cout << "5:) 排序" << endl;
    cout << "6:) 保存数据到文件" << endl;
    cout << "7:) 从文件读取数据" << endl;
    cout << "8:) 显示所有数据" << endl;
    // cout << "8:) "
    cout << "0:) 退出" << endl;
    cout << endl;
    cout << endl;
}

int Management::addStudent(Student stu) 
{
    this->students.push_back(stu);
}

int Management::delStudentByName(string name) 
{
    for (list<Student>::iterator it = this->students.begin(); 
    it != this->students.end();it++) {
        if ((*it).getName() == name) {
            this->students.erase(it);
        } else {
		it++;
	}
    }
}

int Management::showAll() 
{
    for (list<Student>::iterator it = this->students.begin(); 
    it != this->students.end();it++) {
        cout << it->getInfo() << endl;
	}
}

int Management::modifyStudentByName(string name) 
{
    string newName;
    string newGender;

    for (list<Student>::iterator it = this->students.begin(); 
    it != this->students.end();
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

int Management::queryStudentByName(string name) 
{
    for (list<Student>::iterator it = this->students.begin(); 
    it != this->students.end();
    it++) {
        if ((*it).getName() == name) {
            cout << "成员已找到" << endl;

            cout << it->getInfo() << endl;
        }
    }
}

int Management::queryStudentByYear(string year) 
{
    for (list<Student>::iterator it = this->students.begin(); 
    it != this->students.end();
    it++) {
        if ((*it).enter_year == year) {
            cout << "成员已找到" << endl;

            cout << it->getInfo() << endl;
        }
    }
}

int Management::sort() 
{

}

int Management::saveToFile() 
{
    ofstream fout("result.txt");

    if (fout.bad()) {
        return -1;
    }

    for (list<Student>::iterator it = this->students.begin(); 
    it != this->students.end();
    it++) {
        fout << it->getInfoRaw();
    }

    fout.close();
}

int Management::readFromFile() {
    ifstream fin("result.txt");

    string data;

    // 从文件读取要先把链表清空
    this->students.empty();

    while (!fin.eof())
    {
        Student stu;
        fin >> stu.name >> stu.gender >> stu.id 
        >> stu.enter_year >> stu.address >> stu.mail_code >> stu.email;

        this->addStudent(stu);
    }
}

