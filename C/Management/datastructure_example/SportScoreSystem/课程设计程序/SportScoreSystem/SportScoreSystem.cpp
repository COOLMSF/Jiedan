#include<iostream>
#include<iomanip>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<conio.h>
using namespace std;

typedef struct College    //学院的结构
{
    char name[20];        //学院的名称
    int number;            //学院的编号
    int boy;            //男子团体总分
    int girl;            //女子团体总分
    College* next;
}College;
typedef struct Sport    //运动项目结构
{
    char name[20];        //运动项目名称
    int isboy;            //0为女项目,1为男项目
    int is3;            //0为取前五名,1为取前五名
    int number;            //项目编号
    int first;            //第一名学院的编号
    int second;            //第二名学院的编号
    int third;            //第三名学院的编号
    int fourth;            //第四名学院的编号
    int fifth;            //第五名学院的编号
    Sport* next;
}Sport;
int getint(int a)        //字符转换成数字
{
    return (int)(a - '0');
}
College* head1;
//-------启动画面函数----------
void Cover()
{
    system("color 10");
    char line[] = { "程序读取中　请耐心等待..." };
    char bar[] = { "...." };
    int i, j, k = 0, x = 0, y = 0;
    for (i = 0; i <= strlen(line) / 2;)
    {
        system("cls");
        for (j = 0; j < 9; j++)   //改变行坐标
            cout << endl;
        for (j = 0; j < (75 - strlen(line)) / 2; j++) //改变列坐标
            cout << " ";
        for (j = 1; j <= i; j++)         //进度显示器
            cout << "●";
        for (x = strlen(line) / 2; x > i; x--)
            cout << "○";
        if (k == 4)
            i++;
        cout << endl;
        for (j = 0; j < (75 - strlen(line)) / 2; j++)   //行坐标定位
            cout << " ";
        cout << line;         //输出线条
        cout << endl;
        for (j = 0; j < (65 - strlen(bar)) / 2; j++)
            cout << " ";
        cout << (i + 7) * 5 << "% Loading";
        cout.write(bar, k);
        cout << endl;
        for (j = 0; j < 10; j++)
            cout << endl;
        for (j = 0; j < 24; j++)
            cout << " ";
        cout << "第八组 Sport Score System" << endl;
        for (j = 0; j < 24; j++)
            cout << " ";
        for (j = 0; j <= 24; j++)
            cout << "─";
        cout << endl;
        for (j = 0; j < 10000000; j++);//延时效果
        k++;
        if (k > 4)
            k = 0;
    }
}

void college_add()        //添加学院
{
    College* p;
    int mark = 0;
    p = new College;
    cout << "请输入学院的名称:";
    cin >> p->name;
    char c;
    while (mark != 1)
    {
        cout << "请输入学院的编号:";
        cin >> c;
        if (!isdigit(c))//是否为数字
        {
            cout << "数据非法" << endl;
        }
        else
        {
            mark = 1;
            p->number = c;
        }
    }
    p->boy = 0;
    p->girl = 0;
    p->next = head1->next;
    head1->next = p;
    cout << "成功添加了一个学院" << endl;
}
int college_getlong(College* first)//得到链表长度
{
    int i = 0;
    while (first->next != NULL)
    {
        i++;
        first = first->next;
    }
    return i;
}
void college_write()//将学院数据写入文本
{
    College* p;
    p = head1;
    p = p->next;
    ofstream outfile("College.txt", ios::out);
    outfile << college_getlong(p) + 1 << " ";
    while (p != NULL)
    {
        outfile << p->name << " " << p->number << " " << p->boy << " " << p->girl << " ";
        p = p->next;
    }
    outfile.close();
    cout << "学院数据保存成功!" << endl;
}
void college_read()//从文本读入学院数据
{
    int i;
    ifstream infile("College.txt", ios::in);
    infile >> i;
    while (i > 0)
    {
        College* p;
        p = new College;
        infile >> p->name >> p->number >> p->boy >> p->girl;
        p->next = head1->next;
        head1->next = p;
        i--;
    }
    cout << "学院数据读取成功!" << endl;
}
void college_output(College* p)//输出学院
{
    cout << "　学院名　　　　编号　男团总分　女团总分　总分\t\n";
    while (p)
    {
        cout << p->name << "     \t" << getint(p->number) << "\t" << p->boy << "\t" << p->girl << "\t " << (p->girl + p->boy) << endl;
        p = p->next;
    }
}
int college_isexist(int a)//检验学院是否存在
{
    int b = 0;
    College* p;
    p = head1;
    p = p->next;
    while (p)
    {
        if (p->number == a)
        {
            return 1;
        }
        p = p->next;
    }
    return 0;
}
void college_show(int a)//输出所有学院
{
    College* p;
    p = head1;
    p = p->next;
    while (p)
    {
        if (p->number == a)
        {
            cout << p->name << "　";
            return;
        }
        p = p->next;
    }
    cout << "　无　 　";
}
void college_search(int a)//按编号搜索学院
{
    College* p;
    p = head1;
    p = p->next;
    while (p)
    {
        if (p->number == a)
        {
            cout << "学院名:" << p->name << "　" << "男子团体总分:" << p->boy << "　" << "女子团体总分:" << p->girl << "　" << "总分:" << (p->boy + p->girl) << "　";
            return;
        }
        p = p->next;
    }
    cout << "无此编号";
}
void college_addmark(int a, int b, int c)//a为分数,b为学院编号,c=1表示男,c=0表示女
{
    College* p;
    p = head1;
    p = p->next;
    while (p)
    {
        if (p->number == b)
        {
            if (c == '1')
            {
                p->boy = p->boy + a;
            }
            else
            {
                p->girl = p->girl + a;
            }
        }
        p = p->next;
    }
}
void college_order(College* temp, int type) //type=0按总分,type=1按男总分,type=2按女总分,
{
    College* p, * q, * small, * temp1;
    temp1 = new College;
    temp1->next = NULL;
    p = temp;
    while (p)
    {
        small = p;
        q = p->next;
        while (q)
        {
            switch (type)
            {
            case 0:
                if ((q->boy + q->girl) < (small->girl + small->boy))
                {
                    small = q;
                }
                break;
            case 1:
                if (q->boy < small->boy)
                {
                    small = q;
                }
                break;
            case 2:
                if (q->girl < small->girl)
                {
                    small = q;
                }
                break;
            default:
                cout << "error" << endl;
            }

            if (small != p)
            {
                temp1->boy = p->boy;
                p->boy = small->boy;
                small->boy = temp1->boy;
                temp1->girl = p->girl;
                p->girl = small->girl;
                small->girl = temp1->girl;
                strcpy(temp1->name, p->name);
                strcpy(p->name, small->name);
                strcpy(small->name, temp1->name);
                temp1->number = p->number;
                p->number = small->number;
                small->number = temp1->number;    //将学院的名字互换
            }
            q = q->next;
        }
        p = p->next;
    }
}
Sport* head2;
int sport_isexist(int a)    //检查运动项目(编号)是否已经存在
{
    int b = 0;
    Sport* p;
    p = head2;
    p = p->next;
    while (p)
    {
        if (p->number == a)
        {
            return 1;
        }
        p = p->next;
    }
    return 0;
}
void sport_add()        //添加项目
{
    Sport* p;
    int mark = 0;
    p = new Sport;
    cout << "请输入项目名称:";
    cin >> p->name;
    char c;
    while (mark != 1)
    {
        cout << "请输入项目编号:";
        cin >> c;
        if (!isdigit(c))
        {
            cout << "数据非法" << endl;
        }
        else
        {
            if (sport_isexist(c))
            {
                cout << "该编号已存在" << endl;
            }
            else
            {
                mark = 1;
                p->number = c;
            }
        }
    }
    mark = 0;
    while (mark != 1)
    {
        cout << "请输入项目类型(0为女子项目,1为男子项目):";
        cin >> c;
        p->isboy = (int)(c - '0');//字符转换成数字
        if (!isdigit(c))
        {
            cout << "数据非法" << endl;
        }
        else if (p->isboy < 0 || p->isboy>1)
        {
            cout << "数据非法" << endl;
        }
        else
        {
            mark = 1;
            p->isboy = c;
        }
    }
    mark = 0;
    while (mark != 1)
    {
        cout << "请输入项目名次情况(0为取前3名,1为取前5名):";
        cin >> c;
        p->is3 = (int)(c - '0');
        if (!isdigit(c))
        {
            cout << "数据非法" << endl;
        }
        else if (p->is3 < 0 || p->is3>1)
        {
            cout << "数据非法" << endl;
        }
        else
        {
            mark = 1;
            p->is3 = c;
        }
    }
    mark = 0;
    while (mark != 1)
    {
        cout << "请输入第一名的学院的编号:";
        cin >> c;
        if (!isdigit(c))
        {
            cout << "数据非法" << endl;
        }
        else
        {
            if (!college_isexist(c))
            {
                cout << "该学院不存在,请先添加";
            }
            else
            {
                mark = 1;
                p->first = c;
                if (p->is3 == '0')
                    college_addmark(5, c, p->isboy);
                else
                    college_addmark(7, c, p->isboy);
            }
        }
    }
    mark = 0;
    while (mark != 1)
    {
        cout << "请输入第二名的学院的编号:";
        cin >> c;
        if (!isdigit(c))
        {
            cout << "数据非法" << endl;
        }
        else
        {
            if (!college_isexist(c))
            {
                cout << "该学院不存在,请先添加";
            }
            else
            {
                mark = 1;
                p->second = c;
                if (p->is3 == '0')
                    college_addmark(3, c, p->isboy);
                else
                    college_addmark(5, c, p->isboy);
            }
        }
    }
    mark = 0;
    while (mark != 1)
    {
        cout << "请输入第三名的学院的编号:";
        cin >> c;
        if (!isdigit(c))
        {
            cout << "数据非法" << endl;
        }
        else
        {
            if (!college_isexist(c))
            {
                cout << "该学院不存在,请先添加";
            }
            else
            {
                mark = 1;
                p->third = c;
                if (p->is3 == '0')
                    college_addmark(2, c, p->isboy);
                else
                    college_addmark(3, c, p->isboy);
            }
        }
    }
    mark = 0;
    if (p->is3 == '1')
    {
        while (mark != 1)
        {
            cout << "请输入第四名的学院的编号:";
            cin >> c;
            if (!isdigit(c))
            {
                cout << "数据非法" << endl;
            }
            else
            {
                if (!college_isexist(c))
                {
                    cout << "该学院不存在,请先添加";
                }
                else
                {
                    mark = 1;
                    p->fourth = c;
                    college_addmark(2, c, p->isboy);
                }
            }
        }
        mark = 0;
        while (mark != 1)
        {
            cout << "请输入第五名的学院的编号:";
            cin >> c;
            if (!isdigit(c))
            {
                cout << "数据非法" << endl;
            }
            else
            {
                if (!college_isexist(c))
                {
                    cout << "该学院不存在,请先添加" << endl;
                }
                else
                {
                    mark = 1;
                    p->fifth = c;
                    college_addmark(1, c, p->isboy);
                }
            }
        }
    }
    else
    {
        p->fourth = '0';
        p->fifth = '0';
    }
    p->next = head2->next;
    head2->next = p;
    cout << "成功添加了一个运动项目" << endl;
}
int sport_getlong(Sport* first)                //得到项目链表长度
{
    int i = 0;
    while (first->next != NULL)
    {
        i++;
        first = first->next;
    }
    return i;
}
void sport_write()                            //将项目数据写入文本文档
{
    Sport* p;
    p = head2;
    p = p->next;
    ofstream outfile("Sport.txt", ios::out);
    outfile << sport_getlong(p) + 1 << " ";
    while (p != NULL)
    {
        outfile << p->name << " " << p->number << " " << p->isboy << " " << p->is3 << " " << p->first << "  " << p->second << " " << p->third << " " << p->fourth << " " << p->fifth << " ";
        p = p->next;
    }
    outfile.close();
    cout << "体育项目数据保存成功!" << endl;
}
void sport_read()                            //从文本读取项目数据
{
    int i;
    ifstream infile("Sport.txt", ios::in);
    infile >> i;
    while (i > 0)
    {
        Sport* p;
        p = new Sport;
        infile >> p->name >> p->number >> p->isboy >> p->is3 >> p->first >> p->second >> p->third >> p->fourth >> p->fifth;
        p->next = head2->next;
        head2->next = p;
        i--;
    }
    cout << "体育项目数据读取成功!" << endl;
}
void sport_output(Sport* p)                        //输出项目的情况
{
    cout << "name  " << "\t" << "Num" << "　 " << "B/G" << "　 " << "  3/5" << "　   " << "  first" << "　　 " << "second" << "  " << "third" << "   " << "fourth" << "   " << "fifth" << " 　" << endl;
    while (p)
    {
        cout << p->name << "\t" << " " << getint(p->number) << "　  " << getint(p->isboy) << "　　   " << getint(p->is3) << "　     " << "  ";
        college_show(p->first);
        college_show(p->second);
        college_show(p->third);
        college_show(p->fourth);
        college_show(p->fifth);
        //printf("\n");
        p = p->next;
        cout << "\n";

    }
    cout << endl;
}
void sport_search(int a)                        //搜索项目
{
    Sport* p;
    p = head2;
    p = p->next;
    while (p)
    {
        if (p->number == a)
        {
            cout << "项目名:" << p->name << endl << "项目类型:";
            if (p->isboy == 1)
            {
                cout << "男子项目";
            }
            else
            {
                cout << "女子项目";
            }
            cout << endl << "第一名:";
            college_show(p->first);
            cout << endl << "第二名:";
            college_show(p->second);
            cout << endl << "第三名:";
            college_show(p->third);
            cout << endl << "第四名:";
            college_show(p->fourth);
            cout << endl << "第五名:";
            college_show(p->fifth);
            return;
        }
        p = p->next;
    }
    cout << "无此编号";
}
void main()                            //运动会程序主函数
{
    Cover();
    system("color F0");    //改变背景,前景色
    head1 = new College;
    head1->next = NULL;
    head2 = new Sport;
    head2->next = NULL;
    //school_add();
    sport_read();
    college_read();
    //sport_add();
    College* p1;
    Sport* p2;
    p1 = head1;
    p1 = p1->next;
    p2 = head2;
    p2 = p2->next;
    char choose;
    char temp;
    //string ch="  ";
    int a = 1;
    while (a != 0)
    {
        cout << endl;
        cout << "         　　　　　　 oO欢迎使用运动会分数统计系统Oo 　　　　　　 \n" << endl;
        cout << "         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "         *                                                         *" << endl;
        cout << "         *   1.输入学院名称;              2.输入运动项目;          *" << endl;
        cout << "         *                                                         *" << endl;
        cout << "         *   3.按学院编号排列;            4.按总分排列;            *" << endl;
        cout << "         *                                                         *" << endl;
        cout << "         *   5.按男团体总分排列;          6.按女团体总分排列;      *" << endl;
        cout << "         *                                                         *" << endl;
        cout << "         *   7.按项目编号查询;            8.按学院别编号查询;      *" << endl;
        cout << "         *                                                         *" << endl;
        cout << "         *                        0.退出                           *" << endl;
        cout << "         *                                                         *" << endl;
        cout << "         *      提示：首先输入学院名称及编号后才能输入运动项目     *" << endl;
        cout << "         *                                                         *" << endl;
        cout << "         * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << endl;
        cout << "                                  请选择:";
        //cin>>ch;
        //choose=int(ch[0])+int(ch[1])-'0';    //处理异常状态
        cin >> choose;
        if (!isdigit(choose))
        {
            system("cls");
            cout << "操作非法1" << endl;
        }
        else
        {
            switch (getint(choose))
            {

            case 1:
                system("cls");
                college_add();
                break;
            case 2:
                system("cls");
                cout << "当前项目:" << endl;
                sport_output(p2);
                cout << "当前学院:" << endl;
                college_output(p1);
                sport_add();
                break;
            case 3:
                system("cls");
                college_output(p1);
                break;
            case 4:
                system("cls");
                college_order(p1, 0);
                college_output(p1);
                break;
            case 5:
                system("cls");
                college_order(p1, 1);
                college_output(p1);
                break;
            case 6:
                system("cls");
                college_order(p1, 2);
                college_output(p1);
                break;
            case 7:
                system("cls");
                cout << "请输入项目编号:";
                cin >> temp;
                sport_search(temp);
                break;
            case 8:
                system("cls");
                cout << "请输入学院的编号:";
                cin >> temp;
                college_search(temp);
                break;
            case 0:
                system("cls");
                a = 0;
                break;
            default:
                system("cls");
                cout << "操作非法\n";
            }
        }
    }
    college_write();
    sport_write();
    system("exit");
}
