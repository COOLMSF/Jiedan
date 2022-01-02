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
    cout << "��ӭʹ�ÿ�����ȤС�����ϵͳ"<< endl;
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
    cout << "1:) ���ѧ��" << endl;
    cout << "2:) �޸�ѧ��" << endl;
    cout << "3:) ɾ��ѧ��" << endl;
    cout << "4:) ��ѯѧ��" << endl;
    cout << endl;
    cout << "5:) �����Ȥ" << endl;
    cout << "6:) �޸���Ȥ" << endl;
    cout << "7:) ɾ����Ȥ" << endl;
    cout << "8:) ��ѯ��Ȥ" << endl;
    cout << "9:) ���浽�ļ�" << endl;
    cout << "10:) �˳���ϵͳ" << endl;

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
            // �½�һ������
            Interest interest = Interest();

            cout << "������Ȥ��id��" << endl;
            cin >> interest.id;
            cout << "������Ȥ�����ͣ�" << endl;
            cin >> interest.type;
            cout << "������Ȥ���ݣ�" << endl;
            cin >> interest.data;

            // �����Ȥ
            interests.push_back(interest);
            cout << "�����Ȥ�ɹ�" << endl;
        }

        void delInterest() {
            int id;
            bool flag = false;

            cout << "��������Ȥid:" << endl;
            cin >> id;
            // ʹ�õ�����������list����
            for (std::list<Interest>::iterator it = interests.begin(); it != interests.end(); ++it) {
                // ���ҵ�ָ��id��ɾ��
                if ((*it).id == id) {
                    // interests.remove(*it);
                    flag = true;
                }
            }

            if (flag) {
                cout << "ɾ����Ȥ�ɹ�" << endl;
            } else {
                cout << "��Ȥid������" << endl;
            }
        }

        void modifyInterest() {
            int id;
            bool flag = false;

            cout << "��������Ȥid:" << endl;
            cin >> id;
            // ʹ�õ�����������list����
            for (std::list<Interest>::iterator it = interests.begin(); it != interests.end(); ++it) {
                // ���ҵ�ָ��id���޸�
                if ((*it).id == id) {
                    cout << "�����µ���Ȥ�����ͣ�" << endl;
                    cin >> (*it).type;
                    cout << "�����µ���Ȥ���ݣ�" << endl;
                    cin >> (*it).data;
                }
            }

            if (flag) {
                cout << "�޸���Ȥ�ɹ�" << endl;
            } else {
                cout << "��Ȥid������" << endl;
            }
        }

        void showInterest() {
            int id;
            bool flag = false;

            // ʹ�õ�����������list����
            for (std::list<Interest>::iterator it = interests.begin(); it != interests.end(); ++it) {
                // ���ҵ�ָ��id���޸�
                cout << "��Ȥ�����ͣ�\t";
                cout << (*it).type << endl;
                cout << "��Ȥ���ݣ�\t" ;
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

            cout << "�����뱣����ļ���:";
            cin >> filename;

            ofstream fout(filename);

                if (!fout.is_open()) 
                { 
                    cout << "δ�ɹ����ļ�" << endl; 
                } 
            // fout.open(filename);
            // if (fout.bad()) {
            //     cout << "�޷����ļ�" << endl;
            //     exit(EXIT_FAILURE);
            // }

            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                char stu_info[MAX_ELEMENT];
                char stu_interest[MAX_ELEMENT];

                fout << "id:" << (*it).id << endl;
                fout << "����:" << (*it).name << endl;
                fout << "�Ա�:" << (*it).gender << endl;
                for (std::list<Interest>::iterator it1 = (*it).interests.begin(); it1 != (*it).interests.end(); ++it1) {
                    fout << "��Ȥid:" << endl;
                    fout << (*it1).id << endl;;
                    fout << "��Ȥ����:" << endl;
                    fout << (*it1).type << endl;
                    fout << "��Ȥ����:" << endl;
                    fout << (*it1).data << endl;
                }
            }
            fout.close();
        }

        int addStudent() {
            Student stu =  Student();
            cout << "������id��" << endl;
            cin >> stu.id;
            cout << "������������" << endl;
            cin >> stu.name;
            cout << "�������Ա�" << endl;
            cin >> stu.gender;
            students.push_back(stu);
            // stu.addInterest();
            cout << "���ѧ���ɹ�" << endl;
        }

        int delStudent() {
            int id;
            bool flag = false;

            cout << "������id:" << endl;
            cin >> id;
            // ʹ�õ�����������list����
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // ���ҵ�ָ��id��ɾ��
                if ((*it).id == id) {
                    // students.remove(*it);
                    flag = true;
                }
            }

            if (flag) {
                cout << "ɾ��ѧ���ɹ�" << endl;
            } else {
                cout << "ѧ��������" << endl;
            }
        }

        int modifyStudent() {
            int id;
            bool flag = false;

            cout << "������id:" << endl;
            cin >> id;
            // ʹ�õ�����������list����
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // ���ҵ�ָ��id���޸�
                if ((*it).id == id) {
                    cout << "����������������" << endl;
                    cin >> (*it).name;
                    cout << "�����������Ա�" << endl;
                    cin >> (*it).gender;
                    flag = true;
                }
            }

            if (flag) {
                cout << "�޸ĳ�ѧ���ɹ�" << endl;
            } else {
                cout << "ѧ��������" << endl;
            }
        }

        int showStudent() {
            bool flag = false;

            // ʹ�õ�����������list����
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // ���ҵ�ָ��id����ѯ
                cout << "������" << endl;
                cout << (*it).name << endl;
                cout << "�Ա�" << endl;
                cout << (*it).gender << endl;;
                (*it).showInterest();
                flag = true;
            }

            if (flag) {
                cout << "��ѯѧ���ɹ�" << endl;
            } else {
                cout << "ѧ��������" << endl;
            }
        }

        void addInterest() {
            bool flag = false;
            int id;

            cout << "������Ҫ�����Ȥ��ѧ��id:";
            cin >> id;

            // ʹ�õ�����������list����
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // ���ҵ�ָ��id����ѯ
                if ((*it).id == id) {
                    (*it).addInterest();
                    flag = true;
                }
            }

            if (flag) {
                cout << "�����Ȥ�ɹ�" << endl;
            } else {
                cout << "ѧ��������" << endl;
            }
        }

        void modifyInterest() {
            bool flag = false;
            int id;

            cout << "������Ҫ�޸���Ȥ��ѧ��id:";
            cin >> id;

            // ʹ�õ�����������list����
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // ���ҵ�ָ��id���޸���Ȥ
                if ((*it).id == id) {
                    (*it).modifyInterest();
                    flag = true;
                }
            }

            if (flag) {
                cout << "�޸���Ȥ�ɹ�" << endl;
            } else {
                cout << "ѧ��������" << endl;
            }
        }

        void delInterest() {
            bool flag = false;
            int id;

            cout << "������Ҫɾ����Ȥ��ѧ��id:";
            cin >> id;

            // ʹ�õ�����������list����
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // ���ҵ�ָ��id��ɾ����Ȥ
                if ((*it).id == id) {
                    (*it).delInterest();
                    flag = true;
                }
            }

            if (flag) {
                cout << "ɾ����Ȥ�ɹ�" << endl;
            } else {
                cout << "ѧ��������" << endl;
            }
        }

        void showInterest() {
            bool flag = false;
            int id;

            cout << "������Ҫ��ѯ��Ȥ��ѧ��id:";
            cin >> id;

            // ʹ�õ�����������list����
            for (std::list<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                // ���ҵ�ָ��id����ѯ��Ȥ
                if ((*it).id == id) {
                    (*it).showInterest();
                    flag = true;
                }
            }

            if (flag) {
                cout << "��ѯ��Ȥ�ɹ�" << endl;
            } else {
                cout << "ѧ��������" << endl;
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
        cout << "������ѡ��:";
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
