#include <iostream>
#include <list>

#include "management.hpp"

bool myCompare(Student stu1, Student stu2)
{
    return stu1.id > stu2.id;
}


int main(int argc, char *argv[])
{
    int input;
    string name, gender;
    Student stu;
    Management management("student management");


    while (1) {
        management.welcome();
        cout << "输入你的选项:" << endl;
        cin >> input;

        switch (input)
        {
        case 1:
            stu.setInfo();
            management.addStudent(stu);
            cout << "添加成功" << endl;
            break;
        
        case 2:
            cout << "输入要删除的名字:" << endl;
            cin >> name;
            management.delStudentByName(name);
            cout << "删除成功" << endl;
            break;

        case 3:
            cout << "输入要修改的名字:" << endl;
            cin >> name;
            management.modifyStudentByName(name);
            cout << "修改成功" << endl;
            break;
        
        case 4:
            cout << "请输入要查询的名字:" << endl;
            cin >> name;
            management.queryStudentByName(name);
            cout << "查询成功" << endl;
            break;
        
        case 5:
            // management.sort(myCompare);
            management.students.sort(myCompare);
            break;
        
        case 6:
            if (management.saveToFile() < 0) {
                cout << "Error save file" << endl;
            } else {
                cout << "Save file ok" << endl;
            }
	        break;
        
        case 7:
            if (management.readFromFile() < 0) {
                cout << "Error read file" << endl;
            } else {
                cout << "Read file ok" << endl;
            }
            break;

        case 8:
            management.showAll();
            break;
	case 0:
	    exit(1);
        }
    }
}
