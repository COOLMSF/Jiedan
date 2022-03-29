#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
#define _CRT_SECURE_NO_DEPRECATE
#endif
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class Student {
public:
	friend void Input    (Student stu[]);
	friend void Statistic(Student stu[]);
	friend void Lookup   (Student stu[]);
	friend void Modify   (Student stu[]);
	friend void Delete   (Student stu[]);
	friend void Output   (Student stu[]);
	friend void save_stat_stat_info(Student stu[]);
	friend void show_stat(Student stu[]);
	friend void Insert   (Student stu[]);
	/*friend void Sort(Student stu[]);*/
	friend void Write    (Student stu[],int n);
	friend int  Read     (Student stu[]);
public:
	// int   num;
	// char  name[8];
	// char  sex[4];
	// char  class_0[20];
	// float work;
	// float experiment;
	// float report;
	// float exam;
	// int   order;
	// float final_score;

	int   num;
	string  name;
	string  sex;
	string  class_0;
	float work;
	float experiment;
	float report;
	float exam;
	int   order;
	float final_score;
}stu[100];

void Write(Student stu[], int n)
{
	fstream myFile;
	myFile.open("StudentScore_modify.dat", ios::out | ios::binary);
	if (!myFile) 
	{
		cout << "StudentScore_modify.dat can't open!" << endl;
		abort();
	}
	int count = n;
	myFile << count << endl << endl;
	for (int i = 0; i < count; i++)
	{
		myFile << stu[i].num << "\t"
			<< stu[i].name << "\t"
			<< stu[i].class_0 << "\t"
			<< stu[i].work << "\t"
			<< stu[i].experiment << "\t"
			<< stu[i].report << "\t"
			<< stu[i].exam << endl;
	}
	myFile.close();
}

int Read(Student stu[])
{
	fstream myFile;
	
	myFile.open("StudentScore.dat", ios::in | ios::binary);
	if(!myFile)
	{
		cout << "StudentScore_modify.dat can't open!" << endl;
		abort();
	}
	int count;
	string line;

	myFile.seekg(0);
	getline(myFile, line);
	getline(myFile, line);
	getline(myFile, line);
	getline(myFile, line);
	
	myFile >> line >> count;
	getline(myFile, line);
	getline(myFile, line);
	getline(myFile, line);
	getline(myFile, line);
	for (int i = 0; i <= count; i++)
	{
		myFile >> stu[i].num >> stu[i].name >> stu[i].sex
			>>  stu[i].class_0
			>> stu[i].work >> stu[i].experiment
			>> stu[i].report >> stu[i].exam;
	}
	myFile.close();
	return count;
}


void Input(Student stu[])
{
	system("cls");
	int i = 0;
	int flag;
	char sign = '0';
	cout << endl << "======>>    请输入学生成绩    <<====== " << endl;
	// cin >> sign;
	while (sign != 'n' && sign != 'N') {
        cout << "班级：";
		cin >> stu[i].class_0;
	loop:
		cout << "学号:";
		cin >> stu[i].num;
		int c = 0;
		// while (c < i)
		// {
		// 	if (stu[i].num == stu[i - c].num)
		// 	{
		// 		cout << "您输入的学号已存在！请重新输入。" << endl;
		// 		goto loop;
		// 	}
		// }
		cout << "姓名:";
		cin >> stu[i].name;
		do {
			flag = 0;
			cout << "平时作业（作业）：";
			cin >> stu[i].work;
			if (stu[i].work > 100 || stu[i].work < 1)
			{
				cout << "对不起，请输入1-100之间的数字！！\n";
			}
			else
			{
				flag = 1;
			}
		} while (flag == 0);
		do
		{
			flag = 0;
			cout << "平时作业（实验）：";
			cin >> stu[i].experiment;
			if (stu[i].experiment > 100 || stu[i].experiment < 1)
			{
				cout << "对不起，请输入1-100之间的数字！！\n";
			}
			else
			{
				flag = 1;
			}
		} while (flag == 0);
		do
		{
			flag = 0;
			cout << "平时作业（报告）：";
			cin >> stu[i].report;
			if (stu[i].report > 100 || stu[i].report < 1)
			{
				cout << "对不起，请输入1-100之间的数字！！\n";
			}
			else
			{
				flag = 1;
			}
		} while (flag == 0);
		do
		{
			flag = 0;
			cout << "考试成绩：";
			cin >> stu[i].exam;
			if (stu[i].exam > 100 || stu[i].exam < 1)
			{
				cout << "对不起，请输入1-100之间的数字！！\n";
			}
			else
			{
				flag = 1;
			}
		} while (flag == 0);

		// 计算最终成绩
		stu[i].final_score = stu[i].work * 0.2 + stu[i].experiment * 0.15 + stu[i].report * 0.05 + stu[i].exam * 0.6;
		i++;
		cout << "输入n或者N退出, y继续:", cin >> sign;
	}
	Write(stu, i);
}
		

void Statistic(Student syu[])
{
	system("cls");
	int n = Read(stu);
	cout << endl << "======>>    输出学生统计数据    <<======\n" << endl;
	cout << "------------------------------------------" << endl;
	cout << "学号" << "\t" << "姓名" << "\t" << "\t" << "成绩" << endl;
	cout << "------------------------------------------" << endl;
	for (int i = 0; i < n; i++) {
		// 计算最终成绩
		stu[i].final_score = stu[i].work * 0.2 + stu[i].experiment * 0.15 + stu[i].report * 0.05 + stu[i].exam * 0.6;
		cout << stu[i].num << "\t" << stu[i].name << "\t"<< "\t" << stu[i].final_score << endl;
	}
	cout << "------------------------------------------" << endl;
	system("pause");
}

void Lookup(Student stu[])
{
	system("cls");
	int n = Read(stu);
	int s;
	int i = 0;
	cout << endl << "======>>    查找学生成绩    <<======" << endl;
	cout << "请输入要查找的学生学号:";
	cin >> s;
	while ((stu[i].num - s) != 0 && i < n)
		i++;
	if (i == n)
	{
		cout << "======>>    对不起，无法找到该学生......    <<======" << endl;
	}
	else
	{
		cout << "------------------------------------------" << endl;
		cout << "学号：" << stu[i].num << endl;
		cout << "姓名：" << stu[i].name << endl;
		cout << "班级名称：" << stu[i].class_0 << endl;
		cout << "平时成绩（作业）：" << stu[i].work << endl;
		cout << "平时成绩（实验）：" << stu[i].experiment << endl;
		cout << "平时成绩（报告）" << stu[i].report << endl;
		cout << "考试成绩" << stu[i].exam << endl;
	}
}
void Modify(Student stu[])
{
	system("cls");
	int n = Read(stu);
	int s;
	int i = 0;
	cout << endl << "======>>    修改学生成绩    <<======" << endl;
	cout << "请输入要修改成绩的学生学号：";
	cin >> s;
	while ((stu[i].num - s) != 0 && i < n)
			i++;
	if (i == n)
	{
		cout << "======>>    对不起，无法找到该学生......    <<======" << endl;
	}
	else
	{
		cout << "------------------------------------------" << endl;
		cout << "学号" << "\t" << "姓名" << "\t" << "性别" << "\t"
			<< "班级名称" << "\t" << "平时成绩（作业）" << "\t"
			<< "平时成绩（实验）" << "\t" << "平时成绩（报告）" << "\t"
			<< "考试成绩" << endl;
		cout << "------------------------------------------" << endl;
		cout << stu[i].num << "\t" << stu[i].name << "\t"
			<< stu[i].class_0 << "\t" <<stu[i].work<< "\t"
			<< stu[i].experiment << "\t" << stu[i].report << "\t"
			<< stu[i].exam << endl;
		cout << endl << "请重新输入该学生成绩：" << endl;
		cout << "学号：";
		cin>> stu[i].num ;
		cout << "姓名：";
		cin>> stu[i].name ;
		cout << "性别：";
		cout << "班级名称："; 
		cin >> stu[i].class_0;
		cout << "平时成绩（作业）：";
		cin >> stu[i].work;
		cout << "平时成绩（实验）：";
		cin >> stu[i].experiment;
		cout << "平时成绩（报告）";
		cin >> stu[i].report ;
		cout << "考试成绩";
		cin >> stu[i].exam ;
		
		char c;
		cout << "======>>    是否保存数据？（y/n)";
		cin >> c;
		if (c != 'n' && c != 'N')
			Write(stu, n);
	}
}

void Delete(Student stu[])
{
	system("cls");
	int n = Read(stu);
	int s;
	int i = 0,j;
	cout << endl << "======>>    删除学生成绩    <<======" << endl;
	cout << "请输入要删除成绩的学生学号：";
	cin >> s;
	while ((stu[i].num - s) != 0 && i < n)
		i++;
	if (i == n)
	{
			cout << "======>>    对不起，无法找到该学生......    <<======" << endl;
		}
	else
	{
		for (j = i; j < n - 1; j++)
		{
			stu[j].num = stu[j + 1].num;
			// strcpy(stu[j].name, stu[j + 1].name);
			// strcpy(stu[j].class_0, stu[j + 1].class_0);
			stu[j].name = stu[j + 1].name;
			stu[j].class_0 = stu[j + 1].class_0;
			stu[j].work = stu[j + 1].work;
			stu[j].experiment = stu[j + 1].experiment;
			stu[j].report = stu[j + 1].report;
			stu[j].exam = stu[j + 1].exam;
		}
		cout << "======>>    提示：已成功删除!" << endl;
	}
	Write(stu, n - 1);
	}

void Insert(Student stu[])
{
	system("cls");
	int n = Read(stu);
	char s = '0';
	cout << endl << "======>>    增加学生成绩    <<======" << endl;
	while (s != 'n' && s != 'N')
	{
		cout << "学号：";
		cin >> stu[n].num;
		cout << "姓名：";
		cin >> stu[n].name;
		cout << "性别：";
		cout << "班级名称：";
		cin >> stu[n].class_0;
		cout << "平时成绩（作业）：";
		cin >> stu[n].work;
		cout << "平时成绩（实验）：";
		cin >> stu[n].experiment;
		cout << "平时成绩（报告）";
		cin >> stu[n].report;
		cout << "考试成绩";
		cin >> stu[n].exam;
		n++;
		cout << "======>>    是否继续插入（y/n)";
		cin >> s;
	}
	Write(stu, n);
}


/*void Sort(Student stu[])
{
	system("cls");
	int i, j, k;
	float s;
	char t[20];
	cout << endl << "======>>    降序排列    <<======" << endl;
	int n = Read(stu);
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - 1; j++)
		{}
	}*/
void save_stat_stat_info(Student stu[])
{

	ofstream ofile;

	ofile.open("StudentScore_statistics.dat");

	system("cls");
	int n = Read(stu);

	ofile << endl << "======>>    显示全部统计信息    <<======" << endl;
	if (!stu)
	{
		ofile << "没有记录";
	}
	else
	{
		// 冒泡排序
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (stu[i].final_score < stu[j].final_score) {
					Student temp;

					temp = stu[i];
					stu[i] = stu[j];
					stu[j] = temp;
				}
			}
		}
		ofile << "按最终成绩排序";
		ofile << "------------------------------------------" << endl;
		ofile << "学号" << "\t" << "姓名" << "\t" << "性别" << "\t"
			<< "班级名称" << "\t" << "平时成绩（作业）" << "\t"
			<< "平时成绩（实验）" << "\t" << "平时成绩（报告）" << "\t"
			<< "考试成绩" << endl << "最终成绩" << endl;
		ofile << "------------------------------------------" << endl;

		double total_score = 0.0;
		// 优秀率
		double good_count = 0;
		// 及格率
		double soso_count = 0;

		for (int i = 0; i < n; i++)
		{
			ofile << stu[i].num << "\t" << stu[i].name << "\t" 
				<< stu[i].class_0 << "\t" << stu[i].work << "\t"
				<< stu[i].experiment << "\t" << stu[i].report << "\t"
				<< stu[i].exam << "\t" << stu[i].final_score << endl;
				total_score += stu[i].final_score;

				if (stu[i].final_score >= 80) {
					good_count++;
				} else if (stu[i].final_score >= 60) {
					soso_count++;
				}
		}
		ofile << "------------------------------------------" << endl;
		ofile << "最高分 " << stu[n - 1].final_score << endl;
		ofile << "最低分 " << stu[0].final_score << endl;
		ofile << "平均分 " << total_score / n << endl;
		// cout << "优秀率 " << double(good_count) / n << endl;
		// cout << "及格率 " << double(good_count) / n << endl;

	cout << "保存成功";
	}

}

void show_stat(Student stu[])
{
	system("cls");
	int n = Read(stu);
	cout << endl << "======>>    显示全部统计信息    <<======" << endl;
	if (!stu)
	{
		cout << "没有记录";
	}
	else
	{
		// 冒泡排序
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (stu[i].final_score < stu[j].final_score) {
					Student temp;

					temp = stu[i];
					stu[i] = stu[j];
					stu[j] = temp;
				}
			}
		}
		cout << "按考试成绩排序";
		cout << "------------------------------------------" << endl;
		cout << "学号" << "\t" << "姓名" << "\t"  << "\t"
			<< "班级名称" << "\t" << "平时成绩（作业）" << "\t"
			<< "平时成绩（实验）" << "\t" << "平时成绩（报告）" << "\t"
			<< "考试成绩" << endl << "最终成绩" << endl;
		cout << "------------------------------------------" << endl;

		double total_score = 0.0;
		// 优秀率
		double good_count = 0;
		// 及格率
		double soso_count = 0;

		for (int i = 0; i < n; i++)
		{
			cout << stu[i].num << "\t" << stu[i].name << "\t" << "\t"
				<< stu[i].class_0 << "\t" << stu[i].work << "\t"
				<< stu[i].experiment << "\t" << stu[i].report << "\t"
				<< stu[i].exam << "\t" << stu[i].final_score << endl;
				total_score += stu[i].final_score;

				if (stu[i].final_score >= 80) {
					good_count++;
				} else if (stu[i].final_score >= 60) {
					soso_count++;
				}
		}
		cout << "------------------------------------------" << endl;
		cout << "最高分 " << stu[n - 1].final_score << endl;
		cout << "最低分 " << stu[0].final_score << endl;
		cout << "平均分 " << total_score / n << endl;
		// cout << "优秀率 " << double(good_count) / n << endl;
		// cout << "及格率 " << double(good_count) / n << endl;
	}
}



void Output(Student stu[])
{
	system("cls");
	int n = Read(stu);
	cout << endl << "======>>    显示全部学生成绩    <<======" << endl;
	if (!stu)
	{
		cout << "没有记录";
	}
	else
	{
		cout << "------------------------------------------" << endl;
		cout << "学号" << "\t" << "姓名" << "\t" << "\t"
			<< "班级名称" << "\t" << "平时成绩（作业）" << "\t"
			<< "平时成绩（实验）" << "\t" << "平时成绩（报告）" << "\t"
			<< "考试成绩" << endl;
		cout << "------------------------------------------" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << stu[i].num << "\t" << stu[i].name << "\t" << "\t"
				<< stu[i].class_0 << "\t" << stu[i].work << "\t"
				<< stu[i].experiment << "\t" << stu[i].report << "\t"
				<< stu[i].exam << endl;
		}
		cout << "------------------------------------------" << endl;
	}
}

int menu()
	{
	char c;
	do 
	{
		system("cls");
		cout << "**********************************************************" << endl;
		cout << "----------------欢迎使用学生成绩管理系统----------------" << endl;
		cout << "    *             (1) 输入学生成绩                  *    " << endl;
		cout << "    *             (2）显示统计数据                  *    " << endl;
		cout << "    *             (3) 查找学生成绩                  *    " << endl;
		cout << "    *             (4) 修改学生成绩                  *    " << endl;
		cout << "    *             (5) 删除学生成绩                  *    " << endl;
		cout << "    *             (6) 插入学生成绩                  *    " << endl;
		cout << "    *             (7) 显示学生成绩                  *    " << endl;
		cout << "    *             (8) 统计课程成绩                  *    " << endl;
		cout << "    *             (9) 保存统计信息                  *    " << endl;
		cout << "    *             (0) 退出管理系统                  *    " << endl;
		cout << "**********************************************************" << endl;
		cout << "请选择您的操作（0-7）：" << endl;
		c = getchar();
	} while (c < '0' || c>'9');
	return(c - '0');
	}


int main()
{
	for (;;)
	{
		switch (menu())
		{
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
			Output(stu);
			system("pause");
			break;
		case 8:
			show_stat(stu);
			system("pause");
			break;
		case 9:
			save_stat_stat_info(stu);
			system("pause");
			break;
		case 0:
			cout << endl << "================感谢您使用学生管理系统================\n" << endl;
			exit(0);
		}
	}
	return 0;
}


