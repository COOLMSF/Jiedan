//6.���������ѯ�����㵼����������ɾ�� �ο�У԰����
// 0���Ų�������1������������ATM������2��Ʒչʾ����3�ͻ��Ⱥ�����4�ۺ�ҵ��� ��5��Ʒ������� 
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<iostream>
#include<string.h>
#define MAX 20 

#define MAXINT 55555//��ʾ����ֵ
int i,j;
int visited[20];
int d[20];

typedef struct ArcCell{
	int assign;//Ȩֵ 
}ArcCell,adjmatrix[MAX][MAX];//�ڽӾ��� 
typedef struct data{
	int ID;//��� 
	char  name[30];//���� 
	char account[256]; //���ܼ�� 
}data;//������Ϣ
typedef struct structure{
	data vexs[MAX];//�������� 
	adjmatrix arcs;// �ڽӾ��� 
	int apeum,sidnum;//�������ͱ��� 
}structure; 
//��ʼ����ͼ 
structure initmap(){//����Ϊʲô�ýṹ�塣��void�������Ҳ���� 
	structure a;
	a.apeum=6;//������� 
	a.sidnum=8;//�ߵĸ���
	for(i=0;i<a.apeum;i++)
		a.vexs[i].ID=i;//���
	strcpy(a.vexs[0].name,"���Ų�����");
	strcpy(a.vexs[0].account,"�������£��ɴ˽������С�");
	strcpy(a.vexs[1].name,"������������ATM����");
	strcpy(a.vexs[1].account,"�ͻ�������ɴ�ȡ���ѯ���޸����루���޿������豸����ת�ˡ�");
	strcpy(a.vexs[2].name,"��Ʒչʾ��");
	strcpy(a.vexs[2].account,"չʾ���в�Ʒ");
	strcpy(a.vexs[3].name,"�Ⱥ���");
	strcpy(a.vexs[3].account,"�ͻ���Ϣ���ȴ�ҵ�񳡵�");
	strcpy(a.vexs[4].name,"�ۺ�ҵ���");
	strcpy(a.vexs[4].account,"�˹��������ҵ��");
	strcpy(a.vexs[5].name,"��Ʒ�����");
	strcpy(a.vexs[5].account,"��Ʋ�Ʒ���ܡ��Ƽ�");
	for(i=0;i<a.apeum;i++)
		for(j=0;j<a.apeum;j++)
			a.arcs[i][j].assign=MAXINT;//��ʼ���ڽӾ��� 
	a.arcs[0][1].assign=2;a.arcs[0][3].assign=4;a.arcs[0][5].assign=6;
	a.arcs[1][5].assign=4;a.arcs[2][3].assign=1;a.arcs[3][4].assign=2;
	a.arcs[3][5].assign=2;a.arcs[4][5].assign=2;//�ڽӾ���Ȩֵ 
	for(i=0;i<a.apeum;i++)
		for(j=0;j<a.apeum;j++)
			a.arcs[j][i].assign=a.arcs[i][j].assign;
	return a;}

//��ѯ������Ϣ �����������·�� 
void inquire(structure a){
	j=1;
	printf("��ѡ����ҵص�:1:���Ų�������2��������������3����Ʒչʾ����4���ͻ��Ⱥ�����5���ۺ�ҵ���6����Ʒ�����\n");
	scanf("%d",&i);
	while(j){
		if(i<=6&&i>=1){
			printf("���  ����             ���\n");
			printf("%-2d%-18s%-40s\n",a.vexs[i-1].ID,a.vexs[i-1].name,a.vexs[i-1].account);
			j=0;}
		else {
			printf("��������ı�Ų����ڣ�����������:");
			scanf("%d",&i);}}
}
void print(structure a){//��ӡ������Ϣ
	printf("���  ����             ���\n");
	for(i=0;i<a.apeum;i++)
		printf("%-2d%-18s%-40s\n",a.vexs[i].ID,a.vexs[i].name,a.vexs[i].account);}
int locID(structure a,int b){
	for(i=0;i<a.apeum;i++)
		{if(b==a.vexs[i].ID) 
			return i;}
		printf("������ı�Ų����ڣ����������룺\n");
	 	scanf("%d",&j);
	 	locID(a,j);} 
/*int locNA(structure a,char b[]){
	for(i=0;i<a.apeum;i++)
		if(!strcmp(b,a.vexs[i].name)) return a.vexs[i].ID;
	else {char c[20];
		printf("������������������������룺\n");
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
void path(structure a){//·�� 
	int q,w;
	print(a);
	printf("ѡ����ʼ����\n");
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
		printf("�������޸�����\n");
		scanf("%s",&a.vexs[i].name);
		return 1;}
	else if(b==2){
		printf("�������޸ļ��\n");
		scanf("%s",&a.vexs[i].account);
		return 1;}
	else {
		printf("�����������޸ĵ����ơ����\n");
		scanf("%s",&a.vexs[i].name);
		scanf("%s",&a.vexs[i].account);
		return 1;
		
	}
	
}
int update(structure &a){//�޸���Ϣ 
	print(a); 
	printf("������Ҫ�޸ĵı��\n");
	scanf("%d",&i);
	locID(a,i);
	printf("ѡ���޸���Ŀ��1���޸����ƣ�2���޸ļ�飻3���޸�ȫ��");
	scanf("%d",&j);
	while(j<1||j>3){
		printf("�����������������룺\n");
		scanf("%d",&j);}
	up(a,i,j);} 
void enside(structure &a){//����һ���� 
	int k;
	printf("�������ִ���ϸ��Ϣ\n");
	print(a);
	printf("�������������ʼ���Ȩֵ\n");
	scanf("%d%d%d",&i,&j,&k);
	i=locID(a,i);j=locID(a,i);//����Ļ�����������ʼ���Ǹ����� 
	a.arcs[i][j].assign=k;
	a.arcs[j][i].assign=k;
	a.sidnum++;}
void envex(structure &a){//����һ���ڵ� 
	printf("�������������ӽ��ı�š����ơ����\n");
	scanf("%d%s%s",&a.vexs[a.apeum].ID,&a.vexs[a.apeum].name,&a.vexs[a.apeum].account);
	a.apeum++;
	for(i=0;i<a.apeum;i++)
		{a.arcs[a.apeum][i].assign=MAXINT;
		a.arcs[i][a.apeum].assign=MAXINT;}}
void deves(structure &a){
	int k;
	printf("�����Ѵ��ڵ���Ϣ:\n");
	print(a);
	printf("������Ҫɾ���ľ�����\n");
	scanf("%d",&k);
	locID(a,k);
	for(i=k;i<a.apeum-1;i++){
		strcpy(a.vexs[i].name,a.vexs[i+1].name);
		strcpy(a.vexs[i].account,a.vexs[i+1].account);}
	for(i=k;i<a.apeum-1;i++)
		for(j=0;j<a.apeum;j++)
			a.arcs[j][i]=a.arcs[j][i+1];
	a.apeum=a.apeum-1;}
void deape(structure &a){//ɾ��һ����
	printf("�����Ѵ��ڵ���Ϣ:\n") ;
	printf("����������Ҫɾ���ߵ���ʼ��\n");
	scanf("%d %d",&i,&j);
	a.arcs[i][j].assign=MAXINT;
	a.arcs[j][i].assign=MAXINT;
	a.sidnum=a.sidnum-1; 
	
}
void work(){
	structure a=initmap();
	printf("**********��ӭʹ�����㵼��ϵͳ**********\n");
	printf("          ��               ��           \n");
	printf("         ->1��������Ϣ����                \n"); 
	printf("         ->2����ѯ·��                     \n");
	printf("         ->3������ͼ��Ϣ                   \n");
	printf("         ->4���˳�                       \n");
	printf("****************************************\n");
	printf("���������ѡ��\n");
	scanf("%d",&i);
	while(i!=4){
		switch(i){
			case 1:print(a);break;
			case 2:path(a);break;
			case 3:printf("��ѡ��������ͣ�1���޸���Ϣ��2�����ӱߣ�3�����ӵ�\n");
				   printf("                4��ɾ����  ��5��ɾ����           \n");
				   scanf("%d",&j);
				   if(j<1||j>5){
				   		printf("��������,����������\n");
				   		scanf("%d",&j);}
				   	else if(j==1)update(a);
				   	else if(j==2)enside(a);
				   	else if(j==3)envex(a);
				   	else if(j==4)deape(a);
				   	else if(j==5)deves(a);
				   	break;
			case 4:exit(0);
			default:printf("û�д˹��ܣ�����������\n");}//endswitch
		printf("ѡ���ܣ�\n");
		scanf("%d",&i);}// endwhile
	
}
int main(){
work();

return 1;
	
}

		











