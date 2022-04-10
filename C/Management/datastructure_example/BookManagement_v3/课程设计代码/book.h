#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

using namespace std;
typedef struct book //图书
{
	char title[100];  //书名
	char isbn[100];  //书号
	char author[100];  //作者
	char publisher[100];  //出版社
	char publishtime[100];//出版日期
	int value;  //单价
	int cnt; //书籍数量
	struct book* next;  //下一本书籍
}Book;




