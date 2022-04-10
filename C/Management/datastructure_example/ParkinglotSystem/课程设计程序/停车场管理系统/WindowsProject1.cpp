// 停车场练习.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
using namespace std;
#define MAXSIZE 300               //定义停车场容量
#define price 5                 //定义每小时收费价格
struct Time {
	int year;
	int month;
	int day;
	int hour;
};
struct car {                     //定义车辆结构体
	string state;               //车辆当前状态
	string number;              //车牌号
	Time atime;                 //到达时间
	Time ltime;                 //离开时间
};
typedef struct {                        //设定栈
	car data[MAXSIZE];
	int top;
}SeqStack;
SeqStack* Init_SeqStack() {             //置空栈
	SeqStack* s;
	s = new SeqStack;
	s->top = -1;
	return s;
}
typedef struct node {                   //链队结点的类型
	car data;
	struct node* next;
}QNode;
typedef struct {                        //将头尾指针封装在一起的链队
	QNode* front, * rear;
}LQueue;
LQueue* Init_LQueue() {                 //置空链队
	LQueue* q;
	QNode* p;
	q = new LQueue;
	p = new QNode;
	p->next = NULL;
	q->front = p;
	q->rear = p;
	return q;
}
class Park {                                 //定义一个停车场类
public:
	Park() {                                 //构造函数
		s1 = Init_SeqStack();               //置空栈（停车场栈）
		s2 = Init_SeqStack();               //置空栈（临时栈）
		L1 = Init_LQueue();                 //置空链队（便道）
		i = 0;
	}
	int compare(Time& d1, Time& d2) {             //计算车辆在停车场停留的时间
		return (24 - d1.hour + d2.hour);
	}
	int compare1(Time d1, Time d2) {            //计算车辆在停车场停留的天数
		int i = -1;                         //计算天数
		while (!((d1.month == d2.month) && (d1.day == d2.day) && (d1.hour == d2.hour))) {
			if (d2.day == 1) {
				--d2.month;
				if (d2.month == 4 || d2.month == 6 || d2.month == 9 || d2.month == 11) {
					d2.day = 30;
				}
				if (d2.month == 1 || d2.month == 3 || d2.month == 5 || d2.month == 7 || d2.month == 8 || d2.month == 10 || d2.month == 12) {
					d2.day = 31;
				}
				if (d2.month == 2) {
					if (((d2.year % 4 == 0) && (d2.year % 100 != 0)) || (d2.year % 400 == 0))
						d2.day = 29;
					else
						d2.day = 28;
				}
				goto exit8;
			}
			--d2.day;
			++i;
		}
	exit8:return i;                //返回车辆停留的天数减一
	}
	int arrive() {                      //车辆到达
		car s;
		QNode* L;
		s.state = "到达";                   //定义到达的车辆的状态
		/*s.ltime = { 0, 0, 0, 0 };           //将车辆离开的时间先设定为0*/
		i++;                                //用于记录进站的车位于第几号车位
		cout << "请输入车牌号：";           //输入车牌号
		cin >> s.number;
		cout << "请依次输入车辆到达时间（年、月、日、小时）" << endl;      //输入车辆到站的时间
		cin >> s.atime.year >> s.atime.month >> s.atime.day >> s.atime.hour;
		if (s1->top < MAXSIZE - 1) {                  //当停车场的容量未满时
			s1->top++;                               //入栈
			s1->data[s1->top] = s;
			cout << "车辆停在停车场的第" << i << "号车位" << endl;
			return 1;
		}
		else {                                           //当停车场容量已满时，停入便道
			cout << "停车场已满，请停放在便道" << endl;
			L = new QNode;                           //入链队
			L->data = s;
			L->next = NULL;
			L1->rear->next = L;
			L1->rear = L;
			cout << "车辆停在便道的第" << i - MAXSIZE << "号车位" << endl;
			return 1;
		}
	}
	void leave() {                      //车辆离开
		car s;
		QNode* L;
		string num;
		int flag = 0, sumpri = 0, ye, mo, da, ho;
		cout << "请输入需要离开的车辆的车牌号：";     //输入需要离开的车辆的车牌号用于查找
		cin >> num;
		while (s1->top != -1) {                        //当停车场内有车辆时
			s = s1->data[s1->top];                    //出栈
			s1->top--;
			if (s.number == num) {                     //当停车场内有需要离开的车辆的车牌号时
				flag = 1;
				cout << "该车停在停车场内的" << s1->top + 1 << "号车位上" << endl;
				s.state = "离开";
				cout << "请依次输入车辆离开时间（年、月、日、小时）" << endl; //输入离开的车辆的信息
				cin >> s.ltime.year >> s.ltime.month >> s.ltime.day >> s.ltime.hour;
				ye = s.ltime.year;
				mo = s.ltime.month;
				da = s.ltime.day;
				ho = s.ltime.hour;
				cout << "离开的车辆的信息：" << endl;
				sumpri = price * (24 * compare1(s.atime, s.ltime) + compare(s.atime, s.ltime));//计算停车费
				cout << "状态" << '\t' << "停车费" << '\t' << "车牌号" << '\t' << "车辆到达时间" << '\t' << "车辆离开时间" << endl;
				cout << s.state << '\t' << sumpri << '\t' << s.number << '\t';
				cout << s.atime.year << "年" << s.atime.month << "月";
				cout << s.atime.day << "日" << s.atime.hour << "时" << '\t';
				cout << s.ltime.year << "年" << s.ltime.month << "月";
				cout << s.ltime.day << "日" << s.ltime.hour << "时" << endl;
				break;
			}
			else {                           //将停车场栈里出栈的数据存入临时栈
				s2->top++;                  //入栈
				s2->data[s2->top] = s;
			}
		}
		while (s2->top != -1) {               //当临时栈里有车辆时
			s = s2->data[s2->top];           //出栈
			s2->top--;
			s1->top++;                       //将临时栈里出栈的数据存入停车场栈
			s1->data[s1->top] = s;           //如果有车辆离开，后面的车辆依次前移一个车位
		}
		if (flag == 1) {                      //如果停车场内有车辆离开
			if (L1->front != L1->rear) {      //就让便道里的第一辆车进入停车场，后面的车辆依次前移一个车位
				L = L1->front->next;
				L1->front->next = L->next;
				L->data.atime.year = ye;
				L->data.atime.month = mo;
				L->data.atime.day = da;
				L->data.atime.hour = ho;
				s = L->data;
				s1->top++;
				s1->data[s1->top] = s;
				delete L;
				if (L1->front->next == NULL)
					L1->rear = L1->front;
			}
		}
	}
	void sdisplay() {                             //查看停车场内的车辆信息
		cout << "状态" << '\t' << "车牌号" << '\t' << "车辆到达时间" << endl;
		for (int i = 0; i <= s1->top; ++i) {
			cout << s1->data[i].state << '\t' << s1->data[i].number << '\t';
			cout << s1->data[i].atime.year << "年";
			cout << s1->data[i].atime.month << "月";
			cout << s1->data[i].atime.day << "日";
			cout << s1->data[i].atime.hour << "时" << endl;
		}
	}
	void ldisplay() {                             //查看便道上的车辆信息
		QNode* L = L1->front->next;
		cout << "状态" << '\t' << "车牌号" << '\t' << "车辆到达时间" << endl;
		while (L != NULL) {
			cout << L->data.state << '\t' << L->data.number << '\t';
			cout << L->data.atime.year << "年";
			cout << L->data.atime.month << "月";
			cout << L->data.atime.day << "日";
			cout << L->data.atime.hour << "时" << endl;
			L = L->next;
		}
	}
protected:
	SeqStack* s1, * s2;                 //停车场栈，临时栈
	LQueue* L1;                         //便道
	int i;
};
int _tmain(int argc, _TCHAR* argv[])
{
	Park park;
	int num;
exit:
	{
		cout << "操作菜单:" << endl;                        //输出操作菜单
		cout << "1、" << "输入到达车辆信息：" << endl;
		cout << "2、" << "输入离开车辆信息：" << endl;
		cout << "3、" << "查看停车场内的车辆信息：" << endl;
		cout << "4、" << "查看便道上的车辆信息：" << endl;
		cout << "0、" << "退出" << endl;
		cout << "请按操作菜单选择：" << endl;
		cin >> num;                                        //输入选项
		if (num > 4 || num < 0) {                               //判断选项是否合法
			cout << "输入有误，返回操作菜单" << endl;
			goto exit;                                     //若选项不合法，则再次输出操作菜单
		}
	}
exit1:
	{
		switch (num) {
		case 1: {                                 //输入到达车辆信息
			park.arrive(); break;
		}
		case 2: {                                 //输入离开车辆信息
			park.leave(); break;
		}
		case 3: {                                 //查看停车场内的车辆信息
			park.sdisplay(); break;
		}
		case 4: {                                 //查看便道上的车辆信息
			park.ldisplay(); break;
		}
		case 0:break;                            //退出
		}
		while (num != 0) {                   //如果没有选择退出，则循环输出操作菜单
			goto exit;
			goto exit1;
		}
		if (num == 0) {                      //如果选择0，则退出
			return 0;
		}
	}
}