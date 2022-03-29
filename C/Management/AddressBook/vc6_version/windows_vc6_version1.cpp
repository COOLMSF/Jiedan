#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ADDRESS
{
	char name[10];
	char tele[12];
	char add[50];
	char group[50];
}ADDRESS;

ADDRESS Capa[30];                             //结构体数组
ADDRESS Temp[30];                             //用于保存输入的结构体数组

int Search_Name(char a[],int num[]);          //按姓名逐个查找
void NameRes();                               //按姓名查找
int Search_Group(char a[]);                   //按群组逐个查找
void GroupRes();                              //按群组查找
void Order(ADDRESS *p,int pnum);              //排序函数
int AddressList();
int Menu();                                   //菜单函数
void ReMenu();                                //返回菜单函数
int Get(char *fileName);                      //读入函数
void Trans(ADDRESS a);                        //传输函数
void Edit(char a[]);                          //修改函数
void Add();                                   //添加函数
void ShowAll(ADDRESS *p,int pnum);            //显示通讯录中所有信息
void ShowOne(ADDRESS *p,int pnum);		      //逐个显示联系人信息
void DelectOne();                             //删除单个词条
void DelectAll();                             //删除全部词条
int Save(char* fileName);                     //保存函数
int TotalNum=0;

int Get(char *fileName)                                          //文件数据获取函数
{
	FILE *pFile = fopen(fileName,"r");
	if(!pFile)
	{
		return 0;
	}
	char str[200];
	while(fgets(str,200,pFile))                                  //从文件中读入数据流存入数组str中
	{
		ADDRESS data;
		sscanf(str,"%s",data.name);                              //从字符串中读入信息存到结构体中
		sscanf(str+strlen(data.name)+1,"%s",data.tele);
		sscanf(str+strlen(data.name)+1+strlen(data.tele)+1,"%s",data.add);
		sscanf(str+strlen(data.name)+1+strlen(data.tele)+1+strlen(data.add)+1,"%s",data.group);
		Trans(data);                                             //调用函数，将结构体信息存入结构体数组中
	}
	fclose(pFile);
	return 1;
}


void Trans(ADDRESS a)                   //传输函数，将结构体ADDRESS信息存入结构体数组Capa中
{
	Capa[TotalNum] = a;
	TotalNum++;
	Order(Capa,TotalNum);
}


void Order(ADDRESS *p,int pnum)         //按照姓名拼音排序
{
	int i,j,m;
	ADDRESS temp;
	for(i=0;i<pnum;i++)
	{
		m=i;
		for(j=0;j<i;j++)
		{
			if(strcmp(p[j].name,p[m].name)>0)
			{
				m=j;
				temp=p[i];
				p[i]=p[m];
				p[m]=temp;
			}
		}
	}
}


int Search_Name(char a[],int num[])                                                   //按姓名逐个查找
{
	int i,j=-1;
	for(i=0;i<TotalNum;i++)
	{
		if(strcmp(Capa[i].name,a)==0)
			num[++j]=i;
	}
	return j;
}


void NameRes()                                                       //按名字查找
{

	int n,m;
	int num[50]={-1};
	char a[100];
	printf("    请输入联系人姓名：");
	gets(a);
	n=Search_Name(a,num);
	if(n==-1)
	{
		fflush(stdin);
		printf("    不存在该联系人，请重新输入！\n");
		printf("    是否返回主菜单？1：返回，2：继续");
		char go[50];
		gets(go);
		int i = 0;
		while(go[i]==' ')
			i++;
		if(go[i]=='1')
		{
			fflush(stdin);                          //清空输入缓存
			ReMenu();
		}
		else
			NameRes();
	}
	else
	{
		fflush(stdin);
		for(m=0;m<=n;m++)
		{
			printf("    联系人序号：%d\n",m);
			printf("    联系人姓名：%s\n",Capa[num[m]].name);
			printf("    联系人电话号码：%s\n",Capa[num[m]].tele);
			printf("    联系人地址：%s\n",Capa[num[m]].add);
			printf("    联系人群组：%s\n",Capa[num[m]].group);
		}
		printf("    1.继续查找  0.返回主菜单\n");
		while(1)
		{
			printf("    请选择：");
			char go[50];
			gets(go);
			int i = 0;
			while(go[i]==' ')
				i++;
			if(go[i]=='1')
			{
				fflush(stdin);
				NameRes();
				return;
			}
			else if(go[i]=='0')
			{
				ReMenu();
				return;
			}
			else
			{
				printf("    输入不合法。");
				continue;
			}
		}
	}
}


int Search_Group(char a[])                                //按群组逐个查找
{
	int i,r=0;
	for(i=0;i<TotalNum;i++)
	{
		if(strcmp(Capa[i].group,a)==0)
		{
			Temp[r] = Capa[i];
			r++;
		}
	}
	return r;
}


void GroupRes()                                     //按群组查找
{
	printf("    请输入要查找的群组名称：");
	char a[100];
	int num[50]={-1};
	gets(a);
	int n;
	n = Search_Group(a);
	if(!n)
	{
		fflush(stdin);
		printf("    该群组下没有联系人！\n");
		printf("    是否返回主菜单？1：返回，2：继续");
		char go[50];
		gets(go);
		int i = 0;
		while(go[i]==' ')
			i++;
		if(go[i]=='1')
		{
			fflush(stdin);
			ReMenu();
		}
		else
			GroupRes();
	}
	else
	{
		fflush(stdin);
		ShowAll(Temp,n);                           //输出该群组所有联系人信息
	}
}


void Edit(char a[])           //修改联系人函数
{
	int n,m,p;
	int num[50]={-1};
	n=Search_Name(a,num);
    while(1)
		{
			m=0;
			for(m=0;m<=n;m++)
			{
				printf("    \n联系人序号：%4d\n",m);
				printf("    联系人姓名：%s\n",Capa[num[m]].name);
				printf("    联系人电话号码：%s\n",Capa[num[m]].tele);
				printf("    联系人地址：%s\n",Capa[num[m]].add);
				printf("    联系人群组：%s\n",Capa[num[m]].group);
			}
			if(m<=n+1)
			{
				printf("    \n请选择要修改的联系人序号：");
				scanf("%d",&p);
				fflush(stdin);
			}
			if(p>=0&&p<=m)
			{
				printf("    \n请选择要修改的项目：\n1.联系人姓名\n2.联系人电话号码\n3.联系人地址\n4.联系人群组\n0.返回主菜单\n");
				printf("    请选择：");
				char go[100];
				gets(go);
				int i = 0;
				while(go[i]==' ')                      //无效输入，读入下一字符
					i++;
				if(go[i]=='1')
				{
					printf("    填入修改后的联系人姓名：");
					gets(Capa[num[p]].name);
					Order(Capa,TotalNum);
					fflush(stdin);
					printf("    修改成功！返回主菜单\n");
					fflush(stdin);
					ReMenu();
					break;
				}
				else if(go[i]=='2')
				{
					printf("    填入修改后的联系人电话号码：");
					gets(Capa[num[p]].tele);
					fflush(stdin);
					printf("    修改成功！返回主菜单\n");
					fflush(stdin);
					ReMenu();
					break;
				}
				else if(go[i]=='3')
				{
					printf("    填入修改后的联系人地址：");
					gets(Capa[num[p]].add);
					fflush(stdin);
					printf("    修改成功！返回主菜单\n");
					fflush(stdin);
					ReMenu();
					break;
				}
				else if(go[i]=='4')
				{
					printf("    填入修改后的联系人群组：");
					gets(Capa[num[p]].group);
					fflush(stdin);
					printf("    修改成功！返回主菜单\n");
					fflush(stdin);
					ReMenu();
					break;
				}
				else if(go[i]=='0')
				{
					fflush(stdin);
					ReMenu();
					break;
				}
				else                                       //差错控制
				{
					fflush(stdin);
					printf("    输入命令不合法！请重新输入！\n");
				}
			}
			else
			{
				fflush(stdin);
				printf("    输入命令不合法！请重新输入！\n");
				scanf("%d",&p);
				fflush(stdin);
			}
		}
}


void Add()     //添加联系人函数
{
	while(1)
	{
		char a[30];
		int num[50]={-1};
		printf("    请输入要添加的联系人姓名：");
		gets(a);
		fflush(stdin);
		if(Search_Name(a,num)==-1)                 //在原数组中没有与新添加的姓名重叠的情况
		{
			strcpy(Capa[TotalNum].name,a);     //把数组a中的内容复制到结构体数组中的name数组
			printf("    联系人电话：");
			gets(Capa[TotalNum].tele);
			printf("    联系人地址：");
			gets(Capa[TotalNum].add);
			printf("    联系人组别：");
			gets(Capa[TotalNum].group);
			TotalNum++;
			Order(Capa,TotalNum);
			printf("    联系人添加成功！");
			printf("    按任意键返回主菜单：");
			if(getchar())                     //任意键返回
				ReMenu();                     //调用返回菜单函数
			break;
		}
		else
		{
			printf("    提示：已经存在该用户名" );
			printf("    1.替换已存在的用户  2.重新添加联系人 3. 新建重名的联系人 0.返回主菜单\n " );
			printf("    请选择：");
			char go[100];
			gets(go);
			int i=0;
			while(go[i]==' ')
				i++;
			if(go[i]=='1')
			{
				Edit(a);
				break;
			}
			else if(go[i]=='2')
			{
				fflush(stdin);
				continue;
			}
			else if(go[i]=='0')
			{
				fflush(stdin);
				ReMenu();
			}
			else if(go[i]=='3')
			{
				strcpy(Capa[TotalNum].name,a);     //把数组a中的内容复制到结构体数组中的name数组
				printf("    联系人电话：");
				gets(Capa[TotalNum].tele);
				printf("    联系人地址：");
				gets(Capa[TotalNum].add);
				printf("    联系人组别：");
				gets(Capa[TotalNum].group);
				TotalNum++;
				Order(Capa,TotalNum);
				printf("    联系人添加成功！");
				fflush(stdin);
				printf("    按任意键返回主菜单：");
				if(getchar())                      //任意键返回
				{
					fflush(stdin);
					ReMenu();
				}
			}
		}
	}
}


void ShowOne(ADDRESS *p,int pnum)											//逐个显示联系人信息
{
	int j=0;
	int i;
	while(j<pnum)
	{
		printf("\n\n");
		printf("    --------------------------------------------------------\n" );
		printf("\t姓名	     电话号码          地址           群组 \n" );
		printf("    --------------------------------------------------------\n" );
		printf("  %10s   %15s   %10s	%10s\n",p[j].name,p[j].tele,p[j].add,p[j].group);
		printf("    --------------------------------------------------------\n" );
		printf("    返回主菜单0 上一页1   下一页2   当前页数： %d   共 %d 页\n" ,j+1,pnum);
		printf("    翻页控制:");
		char go[100];
		gets(go);
		fflush(stdin);
		i = 0;
		while(go[i]==' ')
			i++;
		if(go[i]=='1')
		{
			fflush(stdin);
			if(j>1)
				j--;
			else
			{
				printf("\n当前已为第一页!\n\n\n");
			}
		}
		else if(go[i]=='2')
		{
			fflush(stdin);
			if(j+1<pnum)
				j++;
			else
			{
				printf("\n当前已为最后一页!\n\n\n");
			}
		}
		else if(go[i]=='0')
		{
			fflush(stdin);
			ReMenu();
			break;
		}
		else
		{
			fflush(stdin);
			printf("    提示：输入指令不合法，请重新输入！\n");
			continue;
		}
	}
}


void ShowAll(ADDRESS *p,int pnum)		//显示全部联系人信息
{
	int pagenumber = 1;
	while(pagenumber)
	{
		printf("    --------------------------------------------------------\n" );//显示通讯录标题信息
		printf("\t姓名	     电话号码          地址           群组 \n" );
		printf("    --------------------------------------------------------\n" );
		int i;
		int end;
		if(pagenumber*10>pnum)          //每页显示10条记录
			end = pnum%10;
		else
			end = 10;
		for(i=0+(pagenumber-1)*10;i<end+(pagenumber-1)*10;i++)
		{
			printf("  %10s   %15s   %10s	%10s\n",p[i].name,p[i].tele,p[i].add,p[i].group); //输出联系人信息
		}
		printf("    --------------------------------------------------------\n" );
		printf("    返回主菜单0 上一页1   下一页2              当前页数： %d\n" ,pagenumber);
		printf("    翻页控制:");
		char go[100];
		gets(go);
		i = 0;
		while(go[i]==' ')                                     //读取空格之后的有效数据
			i++;
		if(go[i]=='1')
		{
			fflush(stdin);
			if(pagenumber>1)
				pagenumber--;
			else
			{
				printf("\n当前已为第一页!\n\n\n");
			}
		}
		else if(go[i]=='2')
		{
			fflush(stdin);
			if(pagenumber*10<pnum)
				pagenumber++;
			else
			{
				printf("\n当前已为最后一页!\n\n\n");
			}
		}
		else if(go[i]=='0')
		{
			fflush(stdin);
			ReMenu();
			break;
		}
		else
		{
			fflush(stdin);
			printf("    提示：输入指令不合法，请重新输入！\n");
			continue;
		}
	}
}


void DelectOne()                                  //删除单个联系人
{
	char a[100];
	int num[50]={-1};
	int m,p;
	printf("    请输入要删除的联系人的姓名：");
	gets(a);
	int n;
	n = Search_Name(a,num);
	if(n==-1)
	{
		fflush(stdin);
		printf("    不存在该联系人！2：重新输入  0：返回主菜单");
		char go[100];
		fflush(stdin);
		gets(go);
		fflush(stdin);
		int i=0;
		while(go[i]==' ')
			i++;
		if(go[i]=='2')
		{
			DelectOne();
		}
		else if(go[i]=='0')
		{
			ReMenu();
		}
	}
	else
	{
		for(m=0;m<=n;m++)
		{
			printf("    联系人序号：%4d\n",m);
			printf("    联系人姓名：%s\n",Capa[num[m]].name);
			printf("    联系人电话号码：%s\n",Capa[num[m]].tele);
			printf("    联系人地址：%s\n",Capa[num[m]].add);
			printf("    联系人群组：%s\n",Capa[num[m]].group);
		}
abc:	printf("    请输入要删除的联系人序号：");
		scanf("%d",&p);
		fflush(stdin);
		if(p>=0&&p<=m)
		{
			printf("    确定要删除当前联系人信息吗？");
			printf("    1.是 2.否   0.返回主菜单\n");
			while(1)
			{
				printf("    请选择：");
				char go[100];
				gets(go);
				int i = 0;
				while(go[i]==' ')
					i++;
				if(go[i]=='1')
				{
					int i;
					for(i=num[p]+1;i<TotalNum;i++)
					{
						Capa[i-1] = Capa[i];
					}
					TotalNum--;
					printf("    联系人删除成功！2：继续删除 0：返回主菜单   ");
				}
				else if(go[i]=='2')
				{
					DelectOne();
					return;
				}
				else if(go[i]=='0')
				{
					ReMenu();
					return;
				}
				else
				{
					printf("    输入命令不合法！2:重新输入！0:返回主菜单   ");
					continue;
				}
			}
		}
		else
		{
			fflush(stdin);
			printf("    输入命令不合法！请重新输入！\n");
			scanf("%d",&p);
			fflush(stdin);
			goto abc;

		}
	}
}


void DelectAll()                                                /*删除全部联系人信息*/
{
	printf("    确定要删除全部的联系人信息么？\n");
	printf("    1.是 2.否    0.返回主菜单\n");
	while(1)
	{
		printf("    请选择：");
		char go[100];
		gets(go);
		int i = 0;
		while(go[i]==' ')
			i++;
		if(go[i]=='1')
		{
			TotalNum = 0;
			printf("    联系人删除成功！\n");

			printf("    返回主菜单请输入1.");
			char go[100];
			fflush(stdin);
			gets(go);
			fflush(stdin);
			int i=0;
			while(go[i]==' ')
				i++;
			if(go[i]=='1')
			{
				ReMenu();
			}
		}
		else if(go[i]=='2')
		{
			ReMenu();
			return;
		}
		else if(go[i]=='0')
		{
			ReMenu();
			return;
		}
		else
		{
			printf("    输入命令不合法！请重新输入！\n");
			continue;
		}
	}
}


int Save(char *fileName)                                                     //保存至文件函数
{
	FILE *pFile = fopen(fileName,"w");
	if(!pFile)
	{
		return 0;
	}
	int i = 0;
	while(i<TotalNum)
	{
		fprintf(pFile,"%s\t%s\t%s\t%s\n",Capa[i].name,Capa[i].tele,Capa[i].add,Capa[i].group); //数据写在文件中
		i++;
	}
	fclose(pFile);
	return 1;
}

int AddressList()
{
    puts("    --------------------------------------------------------");
	puts("");
	puts("                      cxh的手机通讯录                       ");
	puts("");
	puts("    --------------------------------------------------------");
	ShowAll(Capa,TotalNum);
}

int Menu()                 //用户菜单界面
{
	printf("       ｜         功能列表如下：       ｜\n");
	printf("       ｜   1.按照群组查询联系人信息； ｜\n");
	printf("       ｜   2.按照姓名查询联系人信息； ｜\n");
	printf("       ｜   3.添加新的联系人信息；     ｜\n");
	printf("       ｜   4.删除指定的联系人信息；   ｜\n");
	printf("       ｜   5.删除全部的联系人信息；   ｜\n");
	printf("       ｜   6.查询全部联系人信息；     ｜\n");
	printf("       ｜   7.逐个显示全部联系人信息； ｜\n");
	printf("       ｜   0.退出该系统并保存文件；   ｜\n");
	printf("                按数字选择功能:");
	char go[100];
	gets(go);
	int i = 0;
	while(go[i]==' ')
		i++;
	if(go[i]>='0'&&go[i]<='8')
		return go[i]-'0';
	else
	{
		fflush(stdin);
		printf("    提示：输入指令不合法，请重新输入！\n");
		Menu();
	}
}

void ReMenu()                             //当操作为返回时的界面函数
{
	fflush(stdin);
	switch(Menu())                        //调用菜单函数，根据用户输入进行选择语句
	{
	case 1:
		fflush(stdin);
		GroupRes();                       //按群组查询
		break;
	case 2:
		fflush(stdin);
		NameRes();                        //按姓名查询
		break;
	case 3:
		fflush(stdin);
		Add();                            //添加联系人
		break;
	case 4:                               //删除一个联系人
		fflush(stdin);
		DelectOne();
		break;
	case 5:                               //删除全部联系人
		fflush(stdin);
		DelectAll();
		break;
	case 6:                               //查询全部联系人
		fflush(stdin);
		ShowAll(Capa,TotalNum);
		break;
	case 7:
		fflush(stdin);
		ShowOne(Capa,TotalNum);
	case 0:                                  //退出并保存
		Save("Contact.txt");
		exit(0);
		break;
	default:
		fflush(stdin);
		printf("    提示：输入指令不合法，请重新输入！\n");
		Menu();
	}
}

int main()
{
	Get("Contact.txt");
	Order(Capa,TotalNum);
	AddressList();
	switch(Menu())
	{
	case 1:                             //按群组查找
		fflush(stdin);
		GroupRes();
		break;
	case 2:                             //按姓名查询
		fflush(stdin);
		NameRes();
		break;
	case 3:                             //添加联系人
		fflush(stdin);
		Add();
		break;
	case 4:                             // 删除指定联系人
		fflush(stdin);
		DelectOne();
		break;
	case 5:                             //删除全部联系人
		fflush(stdin);
		DelectAll();
		break;
	case 6:
		fflush(stdin);
		ShowAll(Capa,TotalNum);         //显示全部联系人
		break;
	case 7:                             //逐个显示全部联系人
		fflush(stdin);
		ShowOne(Capa,TotalNum);
	case 0:                             //退出并保存
		Save("Contact.txt");
		exit(0);
		break;
	}
}
