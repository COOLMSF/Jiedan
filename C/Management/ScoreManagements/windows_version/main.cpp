#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
#define _CRT_SECURE_NO_DEPRECATE
#endif
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Student{
public:
	friend void Input(Student stu[]);
	friend void Statistic(Student stu[]);
	friend void Lookup(Student stu[]);
	friend void Modify(Student stu[]);
	friend void Delete(Student stu[]);
	friend void Output(Student stu[]);
	friend void Insert(Student stu[]);
	friend void Sort(Student stu[]);
	friend void Write(Student stu[],int n);
	friend int Read(Student stu[]);
private:
	int num;
	char name[8];
	char class_0[20];
	float elec;
	float c_program;
	float english;
	float math;
	float media;
	float sport;
	float polity;
	float average;
	int order;
}stu[100];
 
void Write(Student stu[], int n) {
	fstream myFile;
	myFile.open("score.txt", ios::out | ios::binary);
	if (!myFile) {
		cout << "score.txt can't open!" << endl;
		abort();
	}
	int count = n;
	myFile << count << endl<<endl;
	for (int i = 0; i < count; i++) {
		myFile << stu[i].class_0  << "\t"
			   << stu[i].num      << "\t"
			   << stu[i].name     << "\t"
			   << stu[i].elec     << "\t"
			   << stu[i].c_program<< "\t"
			   << stu[i].media    << "\t"
			   << stu[i].english  << "\t"
			   << stu[i].math     << "\t"
			   << stu[i].sport    << "\t"
			   << stu[i].polity   << "\t"
			   << stu[i].average  << endl;
	}
	myFile.close();
}
 
int Read(Student stu[]) {
	fstream myFile;
	myFile.open("score.txt", ios::in | ios::binary);
	if (!myFile) {
		cout << "score.txt can't open!" << endl;
		abort();
	}
	int count;
	string temp;
	myFile.seekg(0);

	
	
	myFile >> count;
	for (int i = 0; i <= count; i++) {
		myFile >> stu[i].class_0 >> stu[i].num       >> stu[i].name 
			   >> stu[i].elec    >> stu[i].c_program >> stu[i].media 
			   >> stu[i].english >> stu[i].math      >> stu[i].sport 
			   >> stu[i].polity  >> stu[i].average;
	}
	myFile.close();
	return count;
}
 
void Input(Student stu[]) {
	system("cls");
	int i = 0;
	int flag;
	char sign = '0';
	cout << endl<<"======>>    请输入学生成绩    <<======"<<endl;
	while (sign != 'n' && sign != 'N') {
		cout << "班级：";
		cin >> stu[i].class_0;
	loop:
		cout << "学号：";
		cin >> stu[i].num;
		int c = 0;
		while (c < i) {
			c++;
			if (stu[i].num == stu[i - c].num) {
				cout << "您输入的学号已存在！请重新输入。" << endl;
				goto loop;
			}
		}
		cout << "姓名：";
		cin >> stu[i].name;
		do {
			flag = 0;
			cout << "电子技术成绩：";
			cin >> stu[i].elec;
			if (stu[i].elec > 100 || stu[i].elec < 1) {
				cout << " 对不起，请输入1-100之间的数字！！\n";
			}
			else {
				flag = 1;
			}
		} while (flag == 0);
		do {
			flag = 0;
			cout << "C++程序设计成绩：";
			cin >> stu[i].c_program;
			if (stu[i].c_program > 100 || stu[i].c_program < 1) {
				cout << " 对不起，请输入1-100之间的数字！！\n";
			}
			else {
				flag = 1;
			}
		} while (flag == 0);
		do {
			flag = 0;
			cout << "多媒体技术成绩：";
			cin >> stu[i].media;
			if (stu[i].media > 100 || stu[i].media < 1) {
				cout << " 对不起，请输入1-100之间的数字！！\n";
			}
			else {
				flag = 1;
			}
		} while (flag == 0);
		do {
			flag = 0;
			cout << "大学英语成绩：";
			cin >> stu[i].english;
			if (stu[i].english > 100 || stu[i].english < 1) {
				cout << " 对不起，请输入1-100之间的数字！！\n";
			}
			else {
				flag = 1;
			}
		} while (flag == 0);
		do {
			flag = 0;
			cout << "高等数学成绩：";
			cin >> stu[i].math;
			if (stu[i].math > 100 || stu[i].math < 1) {
				cout << " 对不起，请输入1-100之间的数字！！\n";
			}
			else {
				flag = 1;
			}
		} while (flag == 0);
		do {
			flag = 0;
			cout << "大学体育成绩：";
			cin >> stu[i].sport;
			if (stu[i].sport > 100 || stu[i].sport < 1) {
				cout << " 对不起，请输入1-100之间的数字！！\n";
			}
			else {
				flag = 1;
			}
		} while (flag == 0);
		do {
			flag = 0;
			cout << "马克思主义基本原理成绩：";
			cin >> stu[i].polity;
			if (stu[i].polity > 100 || stu[i].polity < 1) {
				cout << " 对不起，请输入1-100之间的数字！！\n";
			}
			else {
				flag = 1;
			}
		} while (flag == 0);
		stu[i].average = (stu[i].elec + stu[i].c_program + stu[i].media + stu[i].english + stu[i].math +
			stu[i].sport + stu[i].polity) / 7;
		cout << " 平均分为：" << stu[i].average<<endl;
		cout << "======>>    提示：是否继续写入学生成绩 ?(y/n)";
		cin >> sign;
		i++;
	}
	Write(stu, i);
}
 
void Statistic(Student stu[]) {
	system("cls");
	int n = Read(stu);
	cout << endl << "======>>    输出学生统计数据    <<======\n" << endl;
	cout << "---------------------------------------" << endl;
	cout << "班级" << "\t" << "学号" << "\t" << "姓名" << "\t" << "平均分" << endl;
	cout << "---------------------------------------" << endl;
	for (int i = 0; i < n; i++)
		cout << stu[i].class_0 << "\t" << stu[i].num << "\t" << stu[i].name << "\t" << stu[i].average << endl;
	cout << "---------------------------------------" << endl;
	system("pause");
}
 
void Lookup(Student stu[]) {
	system("cls");
	int n = Read(stu);
	int s;
	int i = 0;
	cout << endl << "======>>    查找学生成绩    <<======" << endl;
	cout << "请输入要查找学生的学号：";
	cin >> s;
	while ((stu[i].num - s) != 0 && i < n)i++;
	if (i == n) {
		cout << "======>>    对不起，无法找到该学生......    <<======" << endl;
	}
	else {
		cout << "----------------------------" << endl;
		cout << "班级：" << stu[i].class_0 << endl;
		cout << "学号：" << stu[i].num << endl;
		cout << "姓名：" << stu[i].name << endl;
		cout << "电子技术：" << stu[i].elec << endl;
		cout << "C++程序设计：" << stu[i].c_program << endl;
		cout << "多媒体技术：" << stu[i].media << endl;
		cout << "大学英语：" << stu[i].english << endl;
		cout << "高等数学：" << stu[i].math << endl;
		cout << "大学体育：" << stu[i].sport << endl;
		cout << "马克思主义基本原理：" << stu[i].polity << endl;
		cout << "平均分：" << stu[i].average << endl;
	}
}
 
void Modify(Student stu[]) {
	system("cls");
	int n = Read(stu);
	int s;
	int i = 0;
	cout << endl << "======>>    修改学生成绩    <<======" << endl;
	cout << "请输入要修改成绩学生的学号：";
	cin >> s;
	while ((stu[i].num - s) != 0 && i < n)i++;
	if (i == n) {
		cout << "======>>    对不起，无法找到该学生......    <<======" << endl;
	}
	else {
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "班级" << "\t" << "学号"  << "\t" << "姓名" << "\t"
			 << "电子" << "\t" << "C++"  << "\t" << "多媒体" << "\t"
			 << "英语" << "\t" << "数学"  << "\t" << "体育" << "\t"
			 << "政治" << "\t" << "平均分" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << stu[i].class_0 << "\t" << stu[i].num       << "\t" << stu[i].name  << "\t"
			 << stu[i].elec    << "\t" << stu[i].c_program << "\t" << stu[i].media << "\t"
			 << stu[i].english << "\t" << stu[i].math      << "\t" << stu[i].sport << "\t"
			 << stu[i].polity  << "\t" << stu[i].average   << endl;
		cout << endl << "请重新输入该学生成绩： " << endl;
		cout << "电子技术成绩：";
		cin >> stu[i].elec;
		cout << "C++成绩：";
		cin >> stu[i].c_program;
		cout << "多媒体技术成绩：";
		cin >> stu[i].media;
		cout << "大学英语成绩：";
		cin >> stu[i].english;
		cout << "高等数学成绩：";
		cin >> stu[i].math;
		cout << "大学体育成绩：";
		cin >> stu[i].sport;
		cout << "马克思主义基本原理成绩：";
		cin >> stu[i].polity;
		stu[i].average = (stu[i].elec + stu[i].c_program + stu[i].media +
			stu[i].english + stu[i].math + stu[i].sport + stu[i].polity) / 7;
		cout << "平均分：" << stu[i].average << endl;
 
		char c;
		cout << "======>>    是否保存数据 ？(y/n)";
		cin >> c;
		if (c != 'n' && c != 'N')
			Write(stu, n);
	}
}
 
void Delete(Student stu[]) {
	system("cls");
	int n = Read(stu);
	int s;
	int i = 0, j ;
	cout << endl << "======>>    删除学生成绩    <<======" << endl;
	cout << "请输入要删除的学生的学号：";
	cin >> s;
	while ((stu[i].num - s) != 0 && i < n)i++;
	if (i == n) {
		cout << "======>>    对不起，无法找到该学生......    <<======" << endl;
	}
	else {
		for (j = i; j < n - 1; j++) {
			strcpy(stu[j].class_0,stu[j + 1].class_0);
			stu[j].num = stu[j + 1].num;
			strcpy(stu[j].name, stu[j + 1].name);
			stu[j].elec = stu[j + 1].elec;
			stu[j].c_program = stu[j + 1].c_program;
			stu[j].media = stu[j + 1].media;
			stu[j].english = stu[j + 1].english;
			stu[j].math = stu[j + 1].math;
			stu[j].sport = stu[j + 1].sport;
			stu[j].polity = stu[j + 1].polity;
			stu[j].average = stu[j + 1].average;
		}
		cout << "======>>    提示：已成功删除！" << endl;
	}
	Write(stu, n - 1);
}
 
void Insert(Student stu[]) {
	system("cls");
	int n = Read(stu);
	char s='0';
	cout << endl << "=======>>    增加学生成绩    <<========" << endl;
	while (s != 'n' && s != 'N') {
		cout << "班级：";
		cin >> stu[n].class_0;
		cout << "学号：";
		cin >> stu[n].num;
		cout << "姓名：";
		cin >> stu[n].name;
		cout << "电子技术成绩：";
		cin >> stu[n].elec;
		cout << "C++成绩：";
		cin >> stu[n].c_program;
		cout << "多媒体技术成绩：";
		cin >> stu[n].media;
		cout << "大学英语成绩：";
		cin >> stu[n].english;
		cout << "高等数学成绩：";
		cin >> stu[n].math;
		cout << "大学体育成绩：";
		cin >> stu[n].sport;
		cout << "马克思主义基本原理成绩：";
		cin >> stu[n].polity;
		stu[n].average = (stu[n].elec + stu[n].c_program + stu[n].media +
			stu[n].english + stu[n].math + stu[n].sport + stu[n].polity) / 7;
		cout << "平均分：" << stu[n].average << endl;
		n++;
		cout << "======>>    是否继续插入(y/n)";
		cin >> s;
	}
	Write(stu, n);
}
 
void Sort(Student stu[]) {
	system("cls");
	int i, j, k;
	float s;
	char t[20];
	cout << endl << "======>>    降序排列    <<======" << endl;
	int n = Read(stu);
	for (i = 0; i < n-1; i++) {
		for (j = 0; j < n - 1; j++) {
			if (stu[j].average < stu[j + 1].average) {
				//交换课程
				strcpy(t, stu[j + 1].class_0);
				strcpy(stu[j + 1].class_0, stu[j].class_0);
				strcpy(stu[j].class_0, t);
				//num
				k = stu[j + 1].num;
				stu[j + 1].num = stu[j].num;
				stu[j].num = k;
 
				//name
				strcpy(t, stu[j + 1].name);
				strcpy(stu[j + 1].name, stu[j].name);
				strcpy(stu[j].name, t);
				//elec
				s = stu[j + 1].elec;
				stu[j + 1].elec = stu[j].elec;
				stu[j].elec = s;
				//c_program
				s = stu[j + 1].c_program;
				stu[j + 1].c_program = stu[j].c_program;
				stu[j].c_program = s;
				//media
				s = stu[j + 1].media;
				stu[j + 1].media = stu[j].media;
				stu[j].media = s;
				//english
				s = stu[j + 1].english;
				stu[j + 1].english = stu[j].english;
				stu[j].english = s;
				//math
				s = stu[j + 1].math;
				stu[j + 1].math = stu[j].math;
				stu[j].math = s;
				//sport
				s = stu[j + 1].sport;
				stu[j + 1].sport = stu[j].sport;
				stu[j].sport = s;
				//polity
				s = stu[j + 1].polity;
				stu[j + 1].polity = stu[j].polity;
				stu[j].polity = s;
				//average
				s = stu[j + 1].average;
				stu[j + 1].average = stu[j].average;
				stu[j].average = s;
			}
		}
	}
	cout << "------------------------------------------------------------------------------------" << endl;
	cout << "班级" << "\t" << "学号" << "\t" << "姓名" << "\t"
		 << "电子" << "\t" << "C++" << "\t" << "多媒体" << "\t"
		 << "英语" << "\t" << "数学" << "\t" << "体育" << "\t"
		 << "政治" << "\t" << "平均分" << endl;
	cout << "------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < n; i++) {
		stu[i].order = i + 1;
		cout << stu[i].class_0 << "\t" << stu[i].num       << "\t" << stu[i].name << "\t"
			 << stu[i].elec    << "\t" << stu[i].c_program << "\t" << stu[i].media << "\t"
			 << stu[i].english << "\t" << stu[i].math      << "\t" << stu[i].sport << "\t"
			 << stu[i].polity  << "\t" << stu[i].average   << endl;
	}
	Write(stu, n);
}
 
void Output(Student stu[]) {
	system("cls");
	int n = Read(stu);
	cout << endl << "======>>    显示全部学生成绩    <<======" << endl;
	if (!stu) {
		cout << "没有记录";
	}
	else {
		cout << "------------------------------------------------------------------------------------" << endl;
		cout << "班级" << "\t" << "学号"  << "\t" << "姓名"  << "\t" 
			 << "电子" << "\t" << "C++"  << "\t" << "多媒体" << "\t" 
			 << "英语" << "\t" << "数学"  << "\t" << "体育"  << "\t" 
			 << "政治" << "\t" << "平均分" << endl;
		cout << "------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < n; i++) {
			cout << stu[i].class_0 << "\t" << stu[i].num       << "\t" << stu[i].name  << "\t"
				 << stu[i].elec    << "\t" << stu[i].c_program << "\t" << stu[i].media << "\t"
				 << stu[i].english << "\t" << stu[i].math      << "\t" << stu[i].sport << "\t"
				 << stu[i].polity  << "\t" << stu[i].average   << endl;
		}
		cout << "------------------------------------------------------------------------------------" << endl;
	}
}
 
int menu() {
	char c;
	do {
		system("cls");
		cout << "******************************************************" << endl;
		cout << "----------------欢迎使用学生成绩管理系统---------------" << endl;
		cout << "    *          【1】输入学生成绩                  *    " << endl;
		cout << "    *          【2】显示统计数据                  *    " << endl;
		cout << "    *          【3】查找学生成绩                  *    " << endl;
		cout << "    *          【4】修改学生成绩                  *    " << endl;
		cout << "    *          【5】删除学生成绩                  *    " << endl;
		cout << "    *          【6】插入学生成绩                  *    " << endl;
		cout << "    *          【7】按平均分排列                  *    " << endl;
		cout << "    *          【8】显示学生成绩                  *    " << endl;
		cout << "    *          【0】退出管理系统                  *    " << endl;
		cout << "******************************************************" << endl;
		cout << "请选择您的操作 (0-8):" << endl;
		c = getchar();
	} while (c < '0' || c > '8');
	return (c - '0');
}
 
int main() {
	for (;;) {
		switch (menu()) {
			case 1:
				Input(stu);
				break;
			case 2:
				Statistic(stu);
				break;
			case 3:
				Lookup(stu);
				system("pause");
				break;
			case 4:
				Modify(stu);
				system("pause");
				break;
			case 5:
				Delete(stu);
				system("pause");
				break;
			case 6:
				Insert(stu);
				system("pause");
				break;
			case 7:
				Sort(stu);
				system("pause");
				break;
			case 8:
				Output(stu);
				system("pause");
				break;
			case 0:
				cout << endl << "================感谢您使用学生成绩管理系统==============\n" << endl;
				exit(0);
		}
	}
	return 0;
}


