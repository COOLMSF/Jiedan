//6.银行网点查询：网点导航，网点增删改 参考校园导游
// 0正门测温区；1自助服务区（ATM机）；2产品展示区；3客户等候区；4综合业务柜 ；5理财服务区； 
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<iostream>
#include<string.h>
#define MAX 20 

#define MAXINT 55555//表示极大值
int i,j;
int visited[20];
int d[20];

typedef struct ArcCell{
	int assign;//权值 
}ArcCell,adjmatrix[MAX][MAX];//邻接矩阵 
typedef struct data{
	int ID;//编号 
	char  name[30];//名称 
	char account[256]; //功能简介 
}data;//网点信息
typedef struct structure{
	data vexs[MAX];//顶点向量 
	adjmatrix arcs;// 邻接矩阵 
	int apeum,sidnum;//顶点数和边数 
}structure; 
//初始化地图 
structure initmap(){//这里为什么用结构体。用void不行吗，我不理解 
	structure a;
	a.apeum=6;//顶点个数 
	a.sidnum=8;//边的个数
	for(i=0;i<a.apeum;i++)
		a.vexs[i].ID=i;//编号
	strcpy(a.vexs[0].name,"正门测温区");
	strcpy(a.vexs[0].account,"测量体温，由此进出银行。");
	strcpy(a.vexs[1].name,"自助服务区（ATM机）");
	strcpy(a.vexs[1].account,"客户自主完成存取款、查询余额、修改密码（仅限开户地设备）、转账。");
	strcpy(a.vexs[2].name,"产品展示区");
	strcpy(a.vexs[2].account,"展示银行产品");
	strcpy(a.vexs[3].name,"等候区");
	strcpy(a.vexs[3].account,"客户休息、等待业务场地");
	strcpy(a.vexs[4].name,"综合业务柜");
	strcpy(a.vexs[4].account,"人工办理各种业务");
	strcpy(a.vexs[5].name,"理财服务区");
	strcpy(a.vexs[5].account,"理财产品介绍、推荐");
	for(i=0;i<a.apeum;i++)
		for(j=0;j<a.apeum;j++)
			a.arcs[i][j].assign=MAXINT;//初始化邻接矩阵 
	a.arcs[0][1].assign=2;a.arcs[0][3].assign=4;a.arcs[0][5].assign=6;
	a.arcs[1][5].assign=4;a.arcs[2][3].assign=1;a.arcs[3][4].assign=2;
	a.arcs[3][5].assign=2;a.arcs[4][5].assign=2;//邻接矩阵赋权值 
	for(i=0;i<a.apeum;i++)
		for(j=0;j<a.apeum;j++)
			a.arcs[j][i].assign=a.arcs[i][j].assign;
	return a;}

//查询网点信息 输出附近所有路径 
void inquire(structure a){
	j=1;
	printf("请选择查找地点:1:大门测温区；2：自助服务区；3：产品展示区；4：客户等候区；5：综合业务柜；6：理财服务区\n");
	scanf("%d",&i);
	while(j){
		if(i<=6&&i>=1){
			printf("编号  名称             简介\n");
			printf("%-2d%-18s%-40s\n",a.vexs[i-1].ID,a.vexs[i-1].name,a.vexs[i-1].account);
			j=0;}
		else {
			printf("您所输入的编号不存在，请重新输入:");
			scanf("%d",&i);}}
}
void print(structure a){//打印所有信息
	printf("编号  名称             简介\n");
	for(i=0;i<a.apeum;i++)
		printf("%-2d%-18s%-40s\n",a.vexs[i].ID,a.vexs[i].name,a.vexs[i].account);}
int locID(structure a,int b){
	for(i=0;i<a.apeum;i++)
		{if(b==a.vexs[i].ID) 
			return i;}
		printf("您输入的编号不存在，请重新输入：\n");
	 	scanf("%d",&j);
	 	locID(a,j);} 
/*int locNA(structure a,char b[]){
	for(i=0;i<a.apeum;i++)
		if(!strcmp(b,a.vexs[i].name)) return a.vexs[i].ID;
	else {char c[20];
		printf("您输入的名称有误，请重新输入：\n");
	 	scanf("%s",c);
	 	locNA(a,c);}} */
void lane(structure a,int m,int n,int k ){
	int s,x=0,t=k+1;
	if(d[k]==n){
		for(s=0;s<k;s++)
			printf("%s-->",a.vexs[d[s]].name);
		printf("%s\n\n",a.vexs[d[s]].name); 
	}
	else {
		s=0;
		while(s<a.apeum){
			if((a.arcs[d[k]][s].assign<MAXINT)&&(visited[s]==0))
			{	visited[s]=1;
				d[k+1]=s;
				lane(a,m,n,t);
				visited[s]=0;
			}
			s++;
		}
	}

}
void path(structure a){//路径 
	int q,w;
	print(a);
	printf("选择起始点编号\n");
	scanf("%d",&q);
	q=locID(a,q);
	scanf("%d",&w);
	w=locID(a,w);
	d[0]=q;
	for(i=0;i<a.apeum;i++)
		visited[i]=0;
	visited[q]=1;
	lane(a,q,w,0);}
int up(structure &a,int i,int b){
	if(b==1){
		printf("请输入修改名称\n");
		scanf("%s",&a.vexs[i].name);
		return 1;}
	else if(b==2){
		printf("请输入修改简介\n");
		scanf("%s",&a.vexs[i].account);
		return 1;}
	else {
		printf("请输入依次修改的名称、简介\n");
		scanf("%s",&a.vexs[i].name);
		scanf("%s",&a.vexs[i].account);
		return 1;
		
	}
	
}
int update(structure &a){//修改信息 
	print(a); 
	printf("请输入要修改的编号\n");
	scanf("%d",&i);
	locID(a,i);
	printf("选择修改项目：1：修改名称；2：修改简介；3：修改全部");
	scanf("%d",&j);
	while(j<1||j>3){
		printf("输入有误，请重新输入：\n");
		scanf("%d",&j);}
	up(a,i,j);} 
void enside(structure &a){//增加一条边 
	int k;
	printf("以下是现存详细信息\n");
	print(a);
	printf("请依次输入边起始点和权值\n");
	scanf("%d%d%d",&i,&j,&k);
	i=locID(a,i);j=locID(a,i);//错误的话不好区分起始点那个错误 
	a.arcs[i][j].assign=k;
	a.arcs[j][i].assign=k;
	a.sidnum++;}
void envex(structure &a){//增加一个节点 
	printf("请依次输入增加结点的编号、名称、简介\n");
	scanf("%d%s%s",&a.vexs[a.apeum].ID,&a.vexs[a.apeum].name,&a.vexs[a.apeum].account);
	a.apeum++;
	for(i=0;i<a.apeum;i++)
		{a.arcs[a.apeum][i].assign=MAXINT;
		a.arcs[i][a.apeum].assign=MAXINT;}}
void deves(structure &a){
	int k;
	printf("现在已存在的信息:\n");
	print(a);
	printf("请输入要删除的景点编号\n");
	scanf("%d",&k);
	locID(a,k);
	for(i=k;i<a.apeum-1;i++){
		strcpy(a.vexs[i].name,a.vexs[i+1].name);
		strcpy(a.vexs[i].account,a.vexs[i+1].account);}
	for(i=k;i<a.apeum-1;i++)
		for(j=0;j<a.apeum;j++)
			a.arcs[j][i]=a.arcs[j][i+1];
	a.apeum=a.apeum-1;}
void deape(structure &a){//删除一条边
	printf("现在已存在的信息:\n") ;
	printf("请依次输入要删除边的起始点\n");
	scanf("%d %d",&i,&j);
	a.arcs[i][j].assign=MAXINT;
	a.arcs[j][i].assign=MAXINT;
	a.sidnum=a.sidnum-1; 
	
}
void work(){
	structure a=initmap();
	printf("**********欢迎使用网点导航系统**********\n");
	printf("          菜               单           \n");
	printf("         ->1、网点信息介绍                \n"); 
	printf("         ->2、查询路线                     \n");
	printf("         ->3、更改图信息                   \n");
	printf("         ->4、退出                       \n");
	printf("****************************************\n");
	printf("请输入你的选择：\n");
	scanf("%d",&i);
	while(i!=4){
		switch(i){
			case 1:print(a);break;
			case 2:path(a);break;
			case 3:printf("请选择更改类型：1、修改信息；2、增加边；3、增加点\n");
				   printf("                4、删除边  ；5、删除点           \n");
				   scanf("%d",&j);
				   if(j<1||j>5){
				   		printf("输入有误,请重新输入\n");
				   		scanf("%d",&j);}
				   	else if(j==1)update(a);
				   	else if(j==2)enside(a);
				   	else if(j==3)envex(a);
				   	else if(j==4)deape(a);
				   	else if(j==5)deves(a);
				   	break;
			case 4:exit(0);
			default:printf("没有此功能，请重新输入\n");}//endswitch
		printf("选择功能：\n");
		scanf("%d",&i);}// endwhile
	
}
int main(){
work();

return 1;
	
}

		











