#include <iostream>
#include <fstream>
#include <list>

using namespace std;

#define MAX_ELEMENT 255

void welcome()
{
    for (int i = 0; i < 30; i++) {
        cout << "*";
    }
    cout << endl;
    cout << "欢迎使用课外兴趣小组管理系统"<< endl;
    for (int i = 0; i < 30; i++) {
        cout << "*";
    }
    cout << endl;
}

void menu()
{
    for (int i = 0; i < 30; i++) {
        cout << "-";
    }
    cout << endl;
    cout << "1:) 添加学生" << endl;
    cout << "2:) 修改学生" << endl;
    cout << "3:) 删除学生" << endl;
    cout << "4:) 查询学生" << endl;
    cout << endl;
    cout << "5:) 添加兴趣" << endl;
    cout << "6:) 修改兴趣" << endl;
    cout << "7:) 删除兴趣" << endl;
    cout << "8:) 查询兴趣" << endl;
    cout << "9:) 保存到文件" << endl;
    cout << "10:) 退出本系统" << endl;

    for (int i = 0; i < 30; i++) {
        cout << "-";
    }
    cout << endl;
}


class Interest {
    public:
        int id;
        string type;
        string data;
};

class Student {
    public:
        int id;
        string name;
        string gender;
        list <Interest>interests;

        void addInterest() {
            // 新建一个对象
            Interest interest = Interest();

            cout << "输入兴趣的id：" << endl;
            cin >> interest.id;
            cout << "输入兴趣的类型：" << endl;
            cin >> interest.type;
            cout << "输入兴趣内容：" << endl;
            cin >> interest.data;

            // 添加兴趣
            interests.push_back(interest);
            cout << "添加兴趣成功" << endl;
        }

        void delInterest() {
            int id;
            bool flag = false;

            cout << "请输入兴趣id:" << endl;
            cin >> id;
            // 使用迭代器，迭代list容器
            for (std::list<Interest>::iterator it = interests.begin(); it != interests.end(); ++it) {
                // 查找到指定id，删除
                if ((*it).id == id) {
                    // interests.remove(*it);
                    flag = true;
                }
            }

            if (flag) {
                cout << "删除兴趣成功" << endl;
            } else {
                cout << "兴趣id不存在" << endl;
            }
        }

        void modifyInterest() {
            int id;
            bool flag = false;

            cout << "请输入兴趣id:" << endl;
            cin >> id;
            // 使用迭代器，迭代list容器
            for (std::list<Interest>::iterator it = interests.begin(); it != interests.end(); ++it) {
                // 查找到指定id，修改
                if ((*it).id == id) {
                    cout << "输入新的兴趣的类型：" << endl;
                    cin >> (*it).type;
                    cout << "输入新的兴趣内容：" << endl;
                    cin >> (*it).data;
                }
            }

            if (flag) {
                cout << "修改兴趣成功" << endl;
            } else {
                cout << "兴趣id不存在" << endl;
            }
        }

        void showInterest() {
            int id;
            bool flag = false;

            // 使用迭代器，迭代list容器
            for (std::list<Interest>::iterator it = interests.begin(); it != interests.end(); ++it) {
                // 查找到指定id，修改
                cout << "兴趣的类型：\t";
                cout << (*it).type << endl;
                cout << "兴趣内容：\t" ;
                cout << (*it).data << endl;
                flag = true;
            }
        }
};

class Management {
    public:
        list <Student>students;

        void save_file() {
            string filename;

            cout << "请输入保存的文件名:";
            cin >> filename;

            ofstream fout(filename);

                if (!fout.is_open()) 
                { 
                    cout << "未成功打开文件" << endl; 
                } 
            // fout.open(filename);
            // if (fout.bad()) {
            //     cout << "无法打开文件" << endl;
            //     exit(EXIT_FAILURE);
            // }

            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                char stu_info[MAX_ELEMENT];
                char stu_interest[MAX_ELEMENT];

                fout << "id:" << (*it).id << endl;
                fout << "姓名:" << (*it).name << endl;
                fout << "性别:" << (*it).gender << endl;
                for (std::list<Interest>::iterator it1 = (*it).interests.begin(); it1 != (*it).interests.end(); ++it1) {
                    fout << "兴趣id:" << endl;
                    fout << (*it1).id << endl;;
                    fout << "兴趣类型:" << endl;
                    fout << (*it1).type << endl;
                    fout << "兴趣内容:" << endl;
                    fout << (*it1).data << endl;
                }
            }
            fout.close();
        }

        int addStudent() {
            Student stu =  Student();
            cout << "请输入id：" << endl;
            cin >> stu.id;
            cout << "请输入姓名：" << endl;
            cin >> stu.name;
            cout << "请输入性别：" << endl;
            cin >> stu.gender;
            students.push_back(stu);
            // stu.addInterest();
            cout << "添加学生成功" << endl;
        }

        int delStudent() {
            int id;
            bool flag = false;

            cout << "请输入id:" << endl;
            cin >> id;
            // 使用迭代器，迭代list容器
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // 查找到指定id，删除
                if ((*it).id == id) {
                    // students.remove(*it);
                    flag = true;
                }
            }

            if (flag) {
                cout << "删除学生成功" << endl;
            } else {
                cout << "学生不存在" << endl;
            }
        }

        int modifyStudent() {
            int id;
            bool flag = false;

            cout << "请输入id:" << endl;
            cin >> id;
            // 使用迭代器，迭代list容器
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // 查找到指定id，修改
                if ((*it).id == id) {
                    cout << "请重新输入姓名：" << endl;
                    cin >> (*it).name;
                    cout << "请重新输入性别：" << endl;
                    cin >> (*it).gender;
                    flag = true;
                }
            }

            if (flag) {
                cout << "修改除学生成功" << endl;
            } else {
                cout << "学生不存在" << endl;
            }
        }

        int showStudent() {
            bool flag = false;

            // 使用迭代器，迭代list容器
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // 查找到指定id，查询
                cout << "姓名：" << endl;
                cout << (*it).name << endl;
                cout << "性别：" << endl;
                cout << (*it).gender << endl;;
                (*it).showInterest();
                flag = true;
            }

            if (flag) {
                cout << "查询学生成功" << endl;
            } else {
                cout << "学生不存在" << endl;
            }
        }

        void addInterest() {
            bool flag = false;
            int id;

            cout << "请输入要添加兴趣的学生id:";
            cin >> id;

            // 使用迭代器，迭代list容器
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // 查找到指定id，查询
                if ((*it).id == id) {
                    (*it).addInterest();
                    flag = true;
                }
            }

            if (flag) {
                cout << "添加兴趣成功" << endl;
            } else {
                cout << "学生不存在" << endl;
            }
        }

        void modifyInterest() {
            bool flag = false;
            int id;

            cout << "请输入要修改兴趣的学生id:";
            cin >> id;

            // 使用迭代器，迭代list容器
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // 查找到指定id，修改兴趣
                if ((*it).id == id) {
                    (*it).modifyInterest();
                    flag = true;
                }
            }

            if (flag) {
                cout << "修改兴趣成功" << endl;
            } else {
                cout << "学生不存在" << endl;
            }
        }

        void delInterest() {
            bool flag = false;
            int id;

            cout << "请输入要删除兴趣的学生id:";
            cin >> id;

            // 使用迭代器，迭代list容器
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // 查找到指定id，删除兴趣
                if ((*it).id == id) {
                    (*it).delInterest();
                    flag = true;
                }
            }

            if (flag) {
                cout << "删除兴趣成功" << endl;
            } else {
                cout << "学生不存在" << endl;
            }
        }

        void showInterest() {
            bool flag = false;
            int id;

            cout << "请输入要查询兴趣的学生id:";
            cin >> id;

            // 使用迭代器，迭代list容器
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // 查找到指定id，查询兴趣
                if ((*it).id == id) {
                    (*it).showInterest();
                    flag = true;
                }
            }

            if (flag) {
                cout << "查询兴趣成功" << endl;
            } else {
                cout << "学生不存在" << endl;
            }
        }
};


int main()
{
    int input;

    welcome();

    Management management = Management();
    Student stu = Student();

    while (1) {
        menu();
        cout << "输出你的选项:";
        cin >> input;
        switch (input) {
            case 1:
                management.addStudent();
                break;
            case 2:
                management.modifyStudent();
                break;
            case 3:
                management.delStudent();
                break;
            case 4:
                management.showStudent();
                break;
            case 5:
                management.addInterest();
                break;
            case 6:
                management.modifyInterest();
                break;
            case 7:
                management.delInterest();
                break;
            case 8:
                management.showInterest();
                break;
            case 9:
                management.save_file();
                break;
            case 10:
                exit(EXIT_SUCCESS);
        }
    }
}
