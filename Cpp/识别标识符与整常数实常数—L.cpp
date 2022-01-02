/*实验一
   读入一行或多行由“#”结尾的C程序，识别并输出其中的标识符和常数。
例如输入：
void main()
{ int x1,x2,y;
  x1=34;
  x2=56.78;
  y=x1+x2*3; 
}#
输出:(标识符,void)(标识符,main)(标识符,int)(标识符,x1)(标识符,x2)(标识符,y)(标识符,x1)(常数,34)(标识符,x2)(常数,56.78)(标识符,y)
(标识符,x1)(标识符,x2)(常数,3) 
*/
#include <iostream>
#include <string.h>
using namespace std;

//函数声明
void input(char b[]);
int SaveBid(char a[], int i,  struct node Id[], int N);
int SaveNum(char a[], int i, struct node Num[], int N);
int Isletter (char a[], int i);
int IsNum(char a[], int i);
void Compile(char a[], struct node Id[], struct node Num[]);
void output(struct node Id[], struct node Num[]);

const int SIZE=300;
const int size=20;

struct node
{	char list[size];
	int flag;	//flag=0代表没有小数点，即整常数
};
int IdLen=0;   //所有标识符的个数，包括重复的
int NumLen=0;  //所有常数的个数，包括重复的和整常数、实常数
struct node Id[SIZE/2], Num[SIZE/2];

void main()
{	char a[SIZE];

	cout <<"请输入源程序代码，并以'#'号结束：" <<endl;
	input(a);
	Compile(a, Id , Num);
	output(Id, Num);
}

void input(char b[])
{// 将输入的源代码保存在数组b中，以"#"结束
	int i=0;
	char c=getchar();
	while(c != '#')
	{   b[i++]=c;
		c=getchar();
	}
	b[i]='#';
}
int SaveBid(char a[], int i,  struct node Id[], int N)
{//已经识别数组a中从下标i（数组a的下标）开始将是标识符，读取该单词并将其保存在//数组Id中，从下标N（数组Id的下标）开始存放。返回该标识符的长度。

	//完成该函数
}

int SaveNum(char a[], int i, struct node Num[], int N)
{//已经识别数组a中接下来是常数，识别其并将其保存在数组Num中
 //返回此次保存的常数的长度

	//完成该函数
}

int Isletter(char a[], int i)
{//若以字母开头，就认为接下来是一个标识符
	char c=a[i];
	if(c>='a' && c<='z' || c>='A' && c<='Z' || c=='_' )
	    return 1;
	return 0;
}

int IsNum(char a[], int i)
{//判断接下来是否为一个常数
	if(a[i]>='0' && a[i]<='9')
		return 1;
	return 0;
}

void Compile(char a[], struct node Id[], struct node Num[])
{
	//请完成该函数
}

void output(struct node Id[], struct node Num[])
{
	int i, j;
	cout<<"标识符：";
	for(i=0; i<IdLen; i++)
	{int flag1=0;
	 for(j=i+1; j<IdLen;j++)
			if(!strcmp(Id[i].list, Id[j].list))   //如果两字符串相等，则不输出
			{
				 flag1=1;  //相等
				 break;
			}
		if(flag1 !=1)//不相等，即没有重复标识符，可以输出
		{int k=0;
		 while(Id[i].list[k] != '#')
				{
					cout <<Id[i].list[k];
					k++;
				}
		  cout << "  ";
		}
	  }
	  cout<<endl;

	cout<<"整常数：";
	for(i=0; i<NumLen; i++)
	{int flag2=0;
	 if(Num[i].flag !=1)
		for(j=i+1; j<NumLen;j++)
				if(!strcmp(Num[i].list, Num[j].list))
				{
					flag2=1; break;
				}
		if(flag2 !=1 && Num[i].flag !=1)
		{int k=0;
		 while(Num[i].list[k] != '#')
			{
						cout <<Num[i].list[k];
						k++;
			}
		  cout << "  ";
		 }
	   }
	cout << endl;

	cout <<"实常数：";
	for(i=0; i<NumLen; i++)
	{int flag3=0;
	 if(Num[i].flag ==1)
		 for(j=i+1; j<NumLen;j++)
		     if(!strcmp(Num[i].list, Num[j].list))
				{flag3=1;  break;}

		   if(flag3 !=1 && Num[i].flag==1)
			{int k=0;
			 while(Num[i].list[k] != '#')
			 {
						cout <<Num[i].list[k];
						k++;
			 }
			 cout << " ";
			}
		}
	  cout <<endl;
}
