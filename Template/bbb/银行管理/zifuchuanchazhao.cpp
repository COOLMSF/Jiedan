#include <stdio.h>
#include <stdlib.h>
#define MAXSTRLEN 255         //最大串长
typedef char SString[MAXSTRLEN+1];   //串的定长顺序存储表示，0号单元存放串的长度
int next[MAXSTRLEN];            //KMP算法中用到的next数组

//1. 求模式串T的next函数值并存入数组next
void get_next(SString T,int next[ ])   
{   // 求模式串T的next函数值，并存入数组next
	int j=1,k=0;
	next[1]=0;
    while (j<T[0])
	{
		if (k==0 || T[k]==T[j]) 
		{
			++j; ++k; 
			if (T[j]!=T[k])  next[j]=k;
			else next[j]=next[k];
		}
		else k=next[k];
	}
}
//2. KMP匹配函数
int Index(SString S,SString T,int pos) 
{    // 利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法
     // 其中T非空，1 pos  StrLength(s)
	int i=pos,j=1;
	while (i<=S[0]&&j<=T[0])
	{
		if (j==0||S[i]==T[j]) {++i;++j;}  // 继续比较后继字符
		else j=next[j];                // 模式串向右移动
	}
   if (j>T[0])  return (i-T[0]);           // 匹配成功
   else return 0;                       // 匹配失败
}

//3. 求串长
int lenth(SString str)    
{
	int i=1;
	while(str[i]) i++;
	return(i-1);
}
//4. 查找函数
void find(char name[],SString keys) //该函数是整个程序的重要部分，对于输入的每一个
{                                    //要查找的关键字，从存储客户信息的文件中逐行读取字符串查找
	SString text; //存放从客户信息文件读取的一行字符串      
	int i=1,j=0,k;   //i用于存放行号，j用于存放列号,k用于输出格式的控制
	int n=0;  //n记录出现次数
	FILE *fp;
	if (!(fp=(fopen(name,"r")))) //打开存储客户信息的文件
	{
		printf("Open file error!\n");
		exit(0);
	}
	keys[0]=lenth(keys);        //调用lenth函数求关键字的长度
    get_next(keys,next);        //调用get_next函数求模式串（关键字）每一个字符对应的next值
    printf("\n%s出现于：\n",&keys[1]);    //打印关键字
	while (!feof(fp))        //如果还没到客户信息文件末尾
	{
		k=0;		
		fgets(&text[1],MAXSTRLEN,fp);     //从客户信息文件中读取一行字符串，存入text串中
		text[0]=lenth(text);              //求读入的串的长度
		j=Index(text,keys,j+1);        //调用KMP算法，统计关键字在该行出现的位置，若匹配不成功则返回0
		if (j!=0)
		{ printf("\trow=%d,\tcol=%d",i,j); k++; n++;}   //若匹配成功则打印行号和列号
		while(j!=0)         //若该行找到了关键字，则继续寻找看是否还能匹配成功
		{
			j=Index(text,keys,j+1); //调用KMP算法从刚找到的列号后一字符起匹配
			if (j!=0)         
			{   n++;
				printf(",%d",j); } //若匹配成功，则打印列号
		}
		i++; //行号加1，在下一行中寻找
		if (k) printf("\n");  //输出格式控
	}
	printf("%s共出现%d次\n",&keys[1],n); 
}
//5. 主函数
int main()
{
	char name[50];   //存储输入的客户信息路径字符串
	SString words[10];   //定义字符串数组，用于存储输入的关键字
	int n,i;
	printf("请输入已创建的客户信息文件的路径 (如D:\\message.txt):\n");
	scanf("%s",name);   //用户输入包含路径的文本文件名
	printf("请输入要查找的关键字n (n<10)：\n");
	scanf("%d",&n);  //用户输入要查找的关键字个数
	printf("请输入要查找的编号:\n");
	for (i=0;i<n;i++)
		scanf("%s",&words[i][1]); //用户一次性输入要查找的关键字，words[i][0]用于存放字符串的长度
	for (i=0;i<n;i++)
		find(name,words[i]);    //对于每一个关键字，调用find函数进行查找统计
	return 0; 
}
