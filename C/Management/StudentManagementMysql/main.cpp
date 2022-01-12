#include <iostream>
#include <list>

#include "management.h"


int main(int argc, char *argv[])
{
    int input;
    string name, gender;
    Student stu;
    Management management("student management");

    management.welcome();
    cout << "输入你的选项:" << endl;
    cin >> input;

    while (1) {
        management.welcome();
        cout << "输入你的选项:" << endl;
        cin >> input;

        switch (input)
        {
        case 1:
            cout << "名字:" << endl;
            cin >> name;
            cout << "性别:" << endl;
            cin >> gender;
            stu.setName(name);
            stu.setGender(gender);
            stu.setScore();
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
        
    cout << "6:) 保存数据到mysql服务器" << endl;
    cout << "7:) 从mysql服务器读取数据" << endl;
        case 5:
            management.showStat();
            break;
        
        case 6:
            management
        
        default:
            management.saveToMysqlServer();
            break;
        }
    }
}