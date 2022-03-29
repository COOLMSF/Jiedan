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
	cout << endl << "======>>    ������ѧ���ɼ�    <<====== " << endl;
	// cin >> sign;
	while (sign != 'n' && sign != 'N') {
        cout << "�༶��";
		cin >> stu[i].class_0;
	loop:
		cout << "ѧ��:";
		cin >> stu[i].num;
		int c = 0;
		// while (c < i)
		// {
		// 	if (stu[i].num == stu[i - c].num)
		// 	{
		// 		cout << "�������ѧ���Ѵ��ڣ����������롣" << endl;
		// 		goto loop;
		// 	}
		// }
		cout << "����:";
		cin >> stu[i].name;
		do {
			flag = 0;
			cout << "ƽʱ��ҵ����ҵ����";
			cin >> stu[i].work;
			if (stu[i].work > 100 || stu[i].work < 1)
			{
				cout << "�Բ���������1-100֮������֣���\n";
			}
			else
			{
				flag = 1;
			}
		} while (flag == 0);
		do
		{
			flag = 0;
			cout << "ƽʱ��ҵ��ʵ�飩��";
			cin >> stu[i].experiment;
			if (stu[i].experiment > 100 || stu[i].experiment < 1)
			{
				cout << "�Բ���������1-100֮������֣���\n";
			}
			else
			{
				flag = 1;
			}
		} while (flag == 0);
		do
		{
			flag = 0;
			cout << "ƽʱ��ҵ�����棩��";
			cin >> stu[i].report;
			if (stu[i].report > 100 || stu[i].report < 1)
			{
				cout << "�Բ���������1-100֮������֣���\n";
			}
			else
			{
				flag = 1;
			}
		} while (flag == 0);
		do
		{
			flag = 0;
			cout << "���Գɼ���";
			cin >> stu[i].exam;
			if (stu[i].exam > 100 || stu[i].exam < 1)
			{
				cout << "�Բ���������1-100֮������֣���\n";
			}
			else
			{
				flag = 1;
			}
		} while (flag == 0);

		// �������ճɼ�
		stu[i].final_score = stu[i].work * 0.2 + stu[i].experiment * 0.15 + stu[i].report * 0.05 + stu[i].exam * 0.6;
		i++;
		cout << "����n����N�˳�, y����:", cin >> sign;
	}
	Write(stu, i);
}
		

void Statistic(Student syu[])
{
	system("cls");
	int n = Read(stu);
	cout << endl << "======>>    ���ѧ��ͳ������    <<======\n" << endl;
	cout << "------------------------------------------" << endl;
	cout << "ѧ��" << "\t" << "����" << "\t" << "\t" << "�ɼ�" << endl;
	cout << "------------------------------------------" << endl;
	for (int i = 0; i < n; i++) {
		// �������ճɼ�
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
	cout << endl << "======>>    ����ѧ���ɼ�    <<======" << endl;
	cout << "������Ҫ���ҵ�ѧ��ѧ��:";
	cin >> s;
	while ((stu[i].num - s) != 0 && i < n)
		i++;
	if (i == n)
	{
		cout << "======>>    �Բ����޷��ҵ���ѧ��......    <<======" << endl;
	}
	else
	{
		cout << "------------------------------------------" << endl;
		cout << "ѧ�ţ�" << stu[i].num << endl;
		cout << "������" << stu[i].name << endl;
		cout << "�༶���ƣ�" << stu[i].class_0 << endl;
		cout << "ƽʱ�ɼ�����ҵ����" << stu[i].work << endl;
		cout << "ƽʱ�ɼ���ʵ�飩��" << stu[i].experiment << endl;
		cout << "ƽʱ�ɼ������棩" << stu[i].report << endl;
		cout << "���Գɼ�" << stu[i].exam << endl;
	}
}
void Modify(Student stu[])
{
	system("cls");
	int n = Read(stu);
	int s;
	int i = 0;
	cout << endl << "======>>    �޸�ѧ���ɼ�    <<======" << endl;
	cout << "������Ҫ�޸ĳɼ���ѧ��ѧ�ţ�";
	cin >> s;
	while ((stu[i].num - s) != 0 && i < n)
			i++;
	if (i == n)
	{
		cout << "======>>    �Բ����޷��ҵ���ѧ��......    <<======" << endl;
	}
	else
	{
		cout << "------------------------------------------" << endl;
		cout << "ѧ��" << "\t" << "����" << "\t" << "�Ա�" << "\t"
			<< "�༶����" << "\t" << "ƽʱ�ɼ�����ҵ��" << "\t"
			<< "ƽʱ�ɼ���ʵ�飩" << "\t" << "ƽʱ�ɼ������棩" << "\t"
			<< "���Գɼ�" << endl;
		cout << "------------------------------------------" << endl;
		cout << stu[i].num << "\t" << stu[i].name << "\t"
			<< stu[i].class_0 << "\t" <<stu[i].work<< "\t"
			<< stu[i].experiment << "\t" << stu[i].report << "\t"
			<< stu[i].exam << endl;
		cout << endl << "�����������ѧ���ɼ���" << endl;
		cout << "ѧ�ţ�";
		cin>> stu[i].num ;
		cout << "������";
		cin>> stu[i].name ;
		cout << "�Ա�";
		cout << "�༶���ƣ�"; 
		cin >> stu[i].class_0;
		cout << "ƽʱ�ɼ�����ҵ����";
		cin >> stu[i].work;
		cout << "ƽʱ�ɼ���ʵ�飩��";
		cin >> stu[i].experiment;
		cout << "ƽʱ�ɼ������棩";
		cin >> stu[i].report ;
		cout << "���Գɼ�";
		cin >> stu[i].exam ;
		
		char c;
		cout << "======>>    �Ƿ񱣴����ݣ���y/n)";
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
	cout << endl << "======>>    ɾ��ѧ���ɼ�    <<======" << endl;
	cout << "������Ҫɾ���ɼ���ѧ��ѧ�ţ�";
	cin >> s;
	while ((stu[i].num - s) != 0 && i < n)
		i++;
	if (i == n)
	{
			cout << "======>>    �Բ����޷��ҵ���ѧ��......    <<======" << endl;
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
		cout << "======>>    ��ʾ���ѳɹ�ɾ��!" << endl;
	}
	Write(stu, n - 1);
	}

void Insert(Student stu[])
{
	system("cls");
	int n = Read(stu);
	char s = '0';
	cout << endl << "======>>    ����ѧ���ɼ�    <<======" << endl;
	while (s != 'n' && s != 'N')
	{
		cout << "ѧ�ţ�";
		cin >> stu[n].num;
		cout << "������";
		cin >> stu[n].name;
		cout << "�Ա�";
		cout << "�༶���ƣ�";
		cin >> stu[n].class_0;
		cout << "ƽʱ�ɼ�����ҵ����";
		cin >> stu[n].work;
		cout << "ƽʱ�ɼ���ʵ�飩��";
		cin >> stu[n].experiment;
		cout << "ƽʱ�ɼ������棩";
		cin >> stu[n].report;
		cout << "���Գɼ�";
		cin >> stu[n].exam;
		n++;
		cout << "======>>    �Ƿ�������루y/n)";
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
	cout << endl << "======>>    ��������    <<======" << endl;
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

	ofile << endl << "======>>    ��ʾȫ��ͳ����Ϣ    <<======" << endl;
	if (!stu)
	{
		ofile << "û�м�¼";
	}
	else
	{
		// ð������
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
		ofile << "�����ճɼ�����";
		ofile << "------------------------------------------" << endl;
		ofile << "ѧ��" << "\t" << "����" << "\t" << "�Ա�" << "\t"
			<< "�༶����" << "\t" << "ƽʱ�ɼ�����ҵ��" << "\t"
			<< "ƽʱ�ɼ���ʵ�飩" << "\t" << "ƽʱ�ɼ������棩" << "\t"
			<< "���Գɼ�" << endl << "���ճɼ�" << endl;
		ofile << "------------------------------------------" << endl;

		double total_score = 0.0;
		// ������
		double good_count = 0;
		// ������
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
		ofile << "��߷� " << stu[n - 1].final_score << endl;
		ofile << "��ͷ� " << stu[0].final_score << endl;
		ofile << "ƽ���� " << total_score / n << endl;
		// cout << "������ " << double(good_count) / n << endl;
		// cout << "������ " << double(good_count) / n << endl;

	cout << "����ɹ�";
	}

}

void show_stat(Student stu[])
{
	system("cls");
	int n = Read(stu);
	cout << endl << "======>>    ��ʾȫ��ͳ����Ϣ    <<======" << endl;
	if (!stu)
	{
		cout << "û�м�¼";
	}
	else
	{
		// ð������
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
		cout << "�����Գɼ�����";
		cout << "------------------------------------------" << endl;
		cout << "ѧ��" << "\t" << "����" << "\t"  << "\t"
			<< "�༶����" << "\t" << "ƽʱ�ɼ�����ҵ��" << "\t"
			<< "ƽʱ�ɼ���ʵ�飩" << "\t" << "ƽʱ�ɼ������棩" << "\t"
			<< "���Գɼ�" << endl << "���ճɼ�" << endl;
		cout << "------------------------------------------" << endl;

		double total_score = 0.0;
		// ������
		double good_count = 0;
		// ������
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
		cout << "��߷� " << stu[n - 1].final_score << endl;
		cout << "��ͷ� " << stu[0].final_score << endl;
		cout << "ƽ���� " << total_score / n << endl;
		// cout << "������ " << double(good_count) / n << endl;
		// cout << "������ " << double(good_count) / n << endl;
	}
}



void Output(Student stu[])
{
	system("cls");
	int n = Read(stu);
	cout << endl << "======>>    ��ʾȫ��ѧ���ɼ�    <<======" << endl;
	if (!stu)
	{
		cout << "û�м�¼";
	}
	else
	{
		cout << "------------------------------------------" << endl;
		cout << "ѧ��" << "\t" << "����" << "\t" << "\t"
			<< "�༶����" << "\t" << "ƽʱ�ɼ�����ҵ��" << "\t"
			<< "ƽʱ�ɼ���ʵ�飩" << "\t" << "ƽʱ�ɼ������棩" << "\t"
			<< "���Գɼ�" << endl;
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
		cout << "----------------��ӭʹ��ѧ���ɼ�����ϵͳ----------------" << endl;
		cout << "    *             (1) ����ѧ���ɼ�                  *    " << endl;
		cout << "    *             (2����ʾͳ������                  *    " << endl;
		cout << "    *             (3) ����ѧ���ɼ�                  *    " << endl;
		cout << "    *             (4) �޸�ѧ���ɼ�                  *    " << endl;
		cout << "    *             (5) ɾ��ѧ���ɼ�                  *    " << endl;
		cout << "    *             (6) ����ѧ���ɼ�                  *    " << endl;
		cout << "    *             (7) ��ʾѧ���ɼ�                  *    " << endl;
		cout << "    *             (8) ͳ�ƿγ̳ɼ�                  *    " << endl;
		cout << "    *             (9) ����ͳ����Ϣ                  *    " << endl;
		cout << "    *             (0) �˳�����ϵͳ                  *    " << endl;
		cout << "**********************************************************" << endl;
		cout << "��ѡ�����Ĳ�����0-7����" << endl;
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
			cout << endl << "================��л��ʹ��ѧ������ϵͳ================\n" << endl;
			exit(0);
		}
	}
	return 0;
}


