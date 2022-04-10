#include <string.h> 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define Max 20000		//����·�����ֵ 

typedef struct ArcCell{
	int adj;  				//���ڽӵľ���֮���·��
}ArcCell;   				//����ߵ�����
typedef struct VertexType{	//�洢������Ϣ�Ľṹ�� 
	int number;  			//������
    char name[100];  		//��������
    char description[1000]; //�������� 
}VertexType;   				//���嶥������� 
typedef struct{
	VertexType vex[20]; 	//ͼ�еĶ��㣬��Ϊ���� 
    ArcCell view[20][20]; 	//ͼ�еıߣ���Ϊ�����ľ���
    int vexnum,arcnum; 		//ͼ�ж����������� 
}MGraph;   					//����ͼ������ 

MGraph MG;   				//��ͼ����Ϊȫ�ֱ���

int NUM=9;			//��ǰ��������� 
int P[20][20];
int p[20];			//ȫ�����飬�������·���ϵĸ�����
int visited[20];	//ȫ�����飬������¼�����㱻���ʵ����
int a=0;			//ȫ�ֱ�����������¼ÿ�Զ���֮�������·��������
long int D[20];  	//���������洢���·������
int x[20]={0}; 
char userName[15]={"admin"},pwd[7]={"123456"},newPwd[7];//username[15]ԭʼ�˺ţ�pwd[7]ԭʼ����,pwd1�޸�����ʱ�ıȽ� 
char c;	//�����û���ʹ�ã�������������Է��� 

void CreateUDN(int v,int a); 		//��ͼ��������ͼ��ʼ�� 
void narrate();   					//˵����������ʾУ԰�ľ��� 
void shortRoad(int num); 		//���·������
void output(int sight1,int sight2); //�������
void search();   					//��ѯ������Ϣ
char SearchMenu();  				//��ѯ�Ӳ˵�
void HaMiTonian(int);   			//ͼ�ı���
void Searchpath1(MGraph g);			//��ѯ��������������·��
void disppath(MGraph g,int i,int j);
void path(MGraph g,int i,int j,int k);//ȷ��·���ϵ�k+1����������
void NextValue(int);   
void display(); 					//��ʾ�������
int  Addnewsight(int n); 			//����µľ����·��
int  Deletesight(int n); 			//ɾ�������·��
void Changesight(); 				//�޸ľ����·��
char Changemenu();  				//�޸�·���򶥵��ѡ��˵�
char Sightmenu();  					//ѡ����þ���Ĳ˵�
void login();						//�û���¼���� 
void homePage();					//ϵͳ���˵� 
void quit();						//�����˳����� 
void map();							//У԰��ͼ���� 
int main(){ 			//������ 
	CreateUDN(NUM,11);	//��ʼ�� 
    //login();
	homePage(); 
}
void login(){   		//��¼����
	int i=0,k=0,j;		//i��ѭ������,k���ж������������룬j����������ʱ��ѭ��  
	system("color 3f");	//ϵͳ������color��ʾ��ɫ,3����ɫ��f������ɫ 
	printf("\n\n");
	printf("\t ϵͳĬ���û�����admin,���룺123456\n");
	printf("\t������������������������������������������������������������-��\n");
	printf("\t�� **********************************************************��\n");
	printf("\t�� ***��������������������������������������������������-�� ***��\n");
	printf("\t�� ***�� ************************************************�� ***��\n");
	printf("\t�� ***�� ***                                          ***�� ***��\n");
	printf("\t�� ***�� ***         ��ӭʹ��У԰���γ���ϵͳ         ***�� ***��\n");
	printf("\t�� ***�� ***                                          ***�� ***��\n");
	printf("\t�� ***�� ***                ����                      ***�� ***��\n");
	printf("\t�� ***�� ***                                          ***�� ***��\n");
	printf("\t�� ***�� ***                ����                      ***�� ***��\n");
	printf("\t�� ***�� ***                                          ***�� ***��\n"); 
	printf("\t�� ***�� ***            2021��12��3��                 ***�� ***��\n");
	printf("\t�� ***�� ***                                          ***�� ***��\n");
	printf("\t�� ***�� ************************************************�� ***��\n");
	printf("\t�� ***��������������������������������������������������-�� ***��\n");
	printf("\t�� **********************************************************��\n");
	printf("\t������������������������������������������������������������-��\n");
	char userName1[15];   //������ԭʼ������Ƚϵı��� 
	for(i=0;i<3;i++){
		printf("\n�������û���:");
		gets(userName1);
		printf("\n������6λ����:");
		for(j=0;j<100;j++){
			newPwd[j]=getch();
			if(newPwd[j]=='\r')
			break;
			printf("*");	
		}
		newPwd[j]='\0';
	if((strcmp(userName,userName1)==0)&&(strcmp(pwd,newPwd)==0)){
		printf("\n\n���Ѿ��ɹ���¼");
		k=1; 
		for(i=0;i<20;i++){
			printf(".");
			Sleep(100);
		} 
		system("cls");
		homePage();			//��ת�������� 
		break;
	}
	else  printf("\n�û�����������Ч����������:\n");
	continue;
	}
	if(k==0) 
	printf("\n�����������3�ν��˳�����\n");
	Sleep(2000);		//������ͣ��������λ���룩��������ͣ2000���� 
	quit();				//�������δ�����ת�˳����� 
}	
void homePage(){
	int cmd; //�û�ѡ��ı�� 
	int v0,v1;
	while(1){
		printf("\n\n");
		printf("\t��������������������������������������������������������������-��\n");
		printf("\t�� �X========================================================�[  ��\n");
		printf("\t�� �U          �� ӭ ʹ �� У ԰ �� ͼ �� �� ϵ ͳ           �U  ��\n");
		printf("\t�� �^========================================================�a  ��\n");
		printf("\t�� *********************************************************** ��\n"); 
		printf("\t�� *                          *                              * ��\n"); 
		printf("\t�� *         1.������Ϣ��ѯ   *      2.�������·��          * ��\n"); 
		printf("\t�� *                          *                              * ��\n"); 
		printf("\t�� *********************************************************** ��\n"); 
		printf("\t�� *                          *                              * ��\n"); 
		printf("\t�� *         3.�������·��   *      4.У԰��ͼ��ʾ          * ��\n"); 
		printf("\t�� *                          *                              * ��\n"); 
		printf("\t�� *********************************************************** ��\n"); 
		printf("\t�� *                          *                              * ��\n");
		printf("\t�� *         5.����·�����   *      6.�˳���Ϣɾ��          * ��\n");
		printf("\t�� *                          *                              * ��\n");
		printf("\t�� *********************************************************** ��\n");
		printf("\t�� *                          *                              * ��\n");
		printf("\t�� *         7.����·���޸�   *      8.�˳���Ϣϵͳ          * ��\n");
		printf("\t�� *                          *                              * ��\n");
		printf("\t�� *********************************************************** ��\n");  
		printf("\t��������������������������������������������������������������-��\n"); 
		printf("\t��ѡ���� 1 - 8 :");
        scanf("%d",&cmd);
		getchar();
		system("cls");
        switch(cmd){
        	case 1:search();break;
			case 2:
				system("cls");
				//narrate();
            	printf("\n\n\t\t\t��ѡ����㾰�㣨0��%d����",NUM-1);
            	scanf("%d",&v0);
            	printf("\t\t\t��ѡ���յ㾰�㣨0��%d����",NUM-1);
            	scanf("%d",&v1);
            	shortRoad(v0);  /* ������������֮������·�� */
            	output(v0,v1);     /* ������ */
            	printf("\n\n\t\t\t\t�밴���������...\n");
            	getchar();
            	getchar();break;
			case 3:
				system("cls");
            	narrate();
        		x[0]=1;   
            	Searchpath1(MG);
            	printf("\n\n\t\t\t\t�밴���������...\n");
            	getchar();
            	getchar();break;
			case 4:map();break;
			case 5:
				system("cls");
	        	narrate();
	        	NUM=Addnewsight(NUM);
	        	system("cls");
	        	narrate();break; 
			case 6:NUM=Deletesight(NUM);break; 
			case 7:Changesight();break; 
			case 8:quit();break;
			default:printf("\n �Ƿ�����,���������룡\n");
		}
			system("pause");
			system("cls");
    }	
}
void map(){						      //���У԰��ͼ
	system("cls");
	printf("\t\n                            ����ʦ����ѧ                               \n");
	printf("\t-------------------------------------------------------------------------\n");
	printf("\t|      -----------------           ��         ------------   ��         |\n");
	printf("\t|      |       10.     |           ��         |9. ����ѧԺ | ��         |\n");
	printf("\t|      |   ����ѧԺ    |           ��         ------------   ��         |\n");
	printf("\t|      -----------------           ��                        ��--------||\n");
	printf("\t|==================================��========================��|   ��  ||\n");
	printf("\t|                 ��    |               |  ��     ---------- ��| 8.��  ||\n");
	printf("\t|     ----------  ��    |        6.     |  ��     |        | ��|   Է  ||\n");
	printf("\t|     |        |  ��    |     ͼ���    |  ��     |7.��ʳ��| ��|-------||\n");
	printf("\t|     |5.һʳ��|  ��    |               |  ��     |        | ��         |\n");
	printf("\t|     |--------|  ��    |---------------|  ��     |--------| ��         |\n");
	printf("\t|                 ��                       ��                ��         |\n");
	printf("\t|=======================================================================|\n");
	printf("\t|  |  ��  |   |         �� ��            ��            ��               |\n");
	printf("\t|  |4.��  |   |--------|�� ��            ��            ��               |\n");
	printf("\t|  |  ��  |   |        |�� ��            ��     У     ��               |\n");
	printf("\t|  |------|   |    ��  |�� ��=========== ��   3.��     ��               |\n");
	printf("\t|             | 2. ��  |�� ��            ��     ��     ��               |\n");
	printf("\t|             |    ¥  |�� ��            ��     ��     ��               |\n");
	printf("\t|=======================================================================|\n");
	printf("\t|                         ----------------                              |\n");
	printf("\t|                         |              |                              |\n");
	printf("\t|                         |    1.����    |                              |\n");
	printf("\t-------------------------------------------------------------------------\n");
	printf("\n\t                ��������������˵�.                    \n");
	c=getch();system("cls");	
	homePage();
	
}
void quit(){	//�˳�������� 
	system("cls");
	printf("\n\n\t��������������������������������������������������������������\n");
	printf("\t�� *********************************************************��\n"); 
	printf("\t�� *                       ллʹ�ñ�����                  *��\n"); 
	printf("\t�� *********************************************************��\n");
	printf("\t��������������������������������������������������������������\n\n");
	exit(0);	
} 
char SearchMenu(){  /* ��ѯ�Ӳ˵� */
	char c;
 	int flag;
 	do{
  		flag=1;
  		system("cls");
  		printf("\n\t\t\t������������������������������������\n");
  		printf("\t\t\t��                                ��\n");
  		printf("\t\t\t��      1�����վ����Ų�ѯ       ��\n");
  		printf("\t\t\t��      2�����վ������Ʋ�ѯ       ��\n");
  		printf("\t\t\t��      3���������˵�             ��\n");
  		printf("\t\t\t��                                ��\n");
  		printf("\t\t\t������������������������������������\n");
  		printf("\t\t\t\t����������ѡ��");
  		scanf("%c",&c);
  		if(c=='1'||c=='2'||c=='3')
   		flag=0;
 	}while(flag);
 	return c;
}
void search(){  /* ��ѯ������Ϣ */
 	int num;
 	int i;
 	char c;
 	char name[20]; 
 	do{
  		system("cls");
  		c=SearchMenu();
  		switch (c){
  			case '1':  
   			system("cls");
   			printf("\n\n\t\t��������Ҫ���ҵľ����ţ�");
   			scanf("%d",&num);
   			for(i=0;i<NUM;i++){
    			if(num==MG.vex[i].number){
     				printf("\n\n\t\t\t��Ҫ���Ҿ�����Ϣ����:");
     				printf("\n\n\t\t\t�������ƣ�%-25s\n",MG.vex[i].name);
     				printf("\n\n\t\t\t������ܣ�%-25s\n\n",MG.vex[i].description);
     				printf("\n\t\t\t�����������...");
     				getchar();
     				getchar();
     				break;
    			}
   			}
   		if(i==NUM){
    		printf("\n\n\t\t\tû���ҵ���");
    		printf("\n\n\t\t\t�����������...");
    		getchar();
    		getchar();
   			}break;
 	 case '2':
   		system("cls");
   		printf("\n\n\t\t��������Ҫ���ҵľ������ƣ�");
   		scanf("%s",name);
   		for(i=0;i<NUM;i++){
    		if(!strcmp(name,MG.vex[i].name)){
     			printf("\n\n\t\t\t��Ҫ���Ҿ�����Ϣ����:");
     			printf("\n\n\t\t\t�������ƣ�%-25s\n",MG.vex[i].name);
     			printf("\n\n\t\t\t������ܣ�%-25s\n\n",MG.vex[i].description);
     			printf("\n\t\t\t�����������...");
     			getchar();
     			getchar();break;
    		}
   		}
   		if(i==NUM){
    		printf("\n\n\t\t\tû���ҵ���");
    		printf("\n\n\t\t\t�����������...");
    		getchar();
    		getchar();
   			}break;
  		}
 	}while(c!='3');
}
void CreateUDN(int v,int a){	//��ͼ�������������ʼ�� 
	int i,j;
	MG.vexnum=v;  	//��ʼ���ṹ���еľ�����
	MG.arcnum=a;	//��ʼ���ṹ��ı��� 
	for(i=0;i<20;++i) MG.vex[i].number=i; //��ʼ��ÿһ������ı��
 	strcpy(MG.vex[0].name,"ѧУ����");
	strcpy(MG.vex[0].description,"λ��������ɳƺ������ѧ����·37�ţ���ͨ������");
	strcpy(MG.vex[1].name,"���¥");
 	strcpy( MG.vex[1].description,"���¥��Ϊ��У������ѧ¥�� ����139����ң� ����11800λѧ��������");
 	strcpy(MG.vex[2].name,"У�ѻ���");
 	strcpy(MG.vex[2].description,"����һ���ù��У�ѻص�ĸУ�ۼ�һ�ã������������ʦ�����ҵļҵ�������Ը��");
 	strcpy(MG.vex[3].name,"����");
 	strcpy(MG.vex[3].description,"������ʦѧ��ǿ����ĵط����ḻ�������");
 	strcpy(MG.vex[4].name,"һʳ��");
 	strcpy(MG.vex[4].description,"������ʦѧ����ϲ����һʳ�á�");
 	strcpy(MG.vex[5].name,"ͼ���");
	strcpy(MG.vex[5].description,"��ʷ�ƾã��Ļ�������ͬѧ����ѧϰ�Ļ�����");
 	strcpy(MG.vex[6].name,"��ʳ��");
 	strcpy(MG.vex[6].description,"������ʦѧ�������ص���ʳ�á�");
 	strcpy(MG.vex[7].name,"�ŷ�Է");
 	strcpy(MG.vex[7].description,"����Ů�����ᣬ���������������¥��Զ�����ᡣ");
 	strcpy(MG.vex[8].name,"����ѧԺ");
 	strcpy(MG.vex[8].description,"������ʦѧ����ѧ���Ͽεĵط���");
 	//��������еı߼ٶ�Ϊ20000������������������֮���ǲ��ɵ��� */
	 for(i=0;i<20;++i)
  		for(j=0;j<20;++j) 
   			MG.view[i][j].adj=Max;
   /*�±��ǿ�ֱ�ӵ���ľ����ľ��룬�����������������ǻ���ģ�����Ҫ��ͼ�жԳƵı�ͬʱ��ֵ��*/
  	MG.view[0][1].adj=MG.view[1][0].adj=50;
  	MG.view[1][3].adj=MG.view[3][1].adj=70;
 	MG.view[0][6].adj=MG.view[3][0].adj=250;
  	MG.view[1][4].adj=MG.view[4][1].adj=80;
  	MG.view[2][4].adj=MG.view[4][2].adj=100;
  	MG.view[3][5].adj=MG.view[5][3].adj=90;
  	MG.view[5][2].adj=MG.view[2][5].adj=100;
  	MG.view[4][6].adj=MG.view[6][4].adj=75;
  	MG.view[4][7].adj=MG.view[7][4].adj=300;
  	MG.view[2][7].adj=MG.view[7][2].adj=400;
  	MG.view[7][8].adj=MG.view[8][7].adj=40;
}
void narrate(){ 	//˵������������ÿ������ 
 	int i,k=0;
 	printf("\n\t***************��ӭʹ������ʦ����ѧУ԰���γ���**************\n");
 	printf("\t__________________________________________________________________\n");
 	printf("\t ��������\t\t\t��������\t\t\t\n");
 	printf("\t________________________|_________________________\n");
 	for(i=0;i<NUM;i++){ 
  		printf("\t(%2d )%-10s\t\t|    %-8s\n",i,MG.vex[i].name,MG.vex[i].description); //��������б�
  		k=k+1;
 	}
 	printf("\t________________________|_________________________\n");
}
void shortRoad(int num){ 		//�Ͻ�˹�����㷨���·������ numΪ��ڵ�ı�� 
 	int v,w,i,t;  		// i��w��vΪ�������� 
 	int final[20];
 	int min;
 	for(v=0;v<NUM;v++){
  		final[v]=0; 	 			//����Ӷ���num������vû�����·�� 
  		D[v]=MG.view[num][v].adj;	//����֮��ص�Ȩֵ����D�д��
  		for(w=0;w<NUM;w++) 			//����Ϊ��·�� 
   			P[v][w]=0;
  			if(D[v]<20000){  		//����·�� 
   				P[v][num]=1; 		//���ڱ�־��Ϊһ 
   				P[v][v]=1; 			//��������
  			}
 	}
 	D[num]=0;
 	final[num]=1;      //��ʼ��num��������S����
	 /* ��ʼ��ѭ����ÿһ�����num��ĳ����������·������������뵽S���� */
 	for(i=0;i<NUM;++i){     	// ����MG.vexnum-1������ 
  		min=Max;     			//��ǰ��֪�붥��num��������� 
  		for(w=0;w<NUM;++w)
   			if(!final[w])    	//w������v-s�� 
    			if(D[w]<min){   //w������num������� 
     				v=w;
     				min=D[w];
    			} 
    	final[v]=1;  			 // ��num���������v���뵽s���� 
    	for(w=0;w<NUM;++w)  	//���µ�ǰ���·��������� 
     	if(!final[w]&&((min+MG.view[v][w].adj)<D[w])){		//����s���ϣ����ұ���ǰ���ҵ���·�����̾͸��µ�ǰ·��
      		D[w]=min+MG.view[v][w].adj;
      		for(t=0;t<NUM;t++)
       			P[w][t]=P[v][t];
      		P[w][w]=1;
    	 }
 	}
}
void output(int sight1,int sight2){    //�������
	int a,b,c,d,q=0;
    a=sight2;    /* ���������ֵ��a */
    if(a!=sight1)    /* �����������;���һ�����غϣ������... */
	{
		printf("\n\t��%s��%s�����·����",MG.vex[sight1].name,MG.vex[sight2].name);/* �����ʾ��Ϣ */ 
        printf("\t(��̾���Ϊ %dm.)\n\n\t",D[a]);  /* ���sight1��sight2�����·�����ȣ������D[]������ */
        printf("\t%s",MG.vex[sight1].name);   /* �������һ������ */
        d=sight1;      /* ������һ�ı�Ÿ�ֵ��d */
        for(c=0;c<NUM;++c)
		{
           gate:;        /* ��ţ�������Ϊgoto�����ת��λ�� */
           P[a][sight1]=0;
           for(b=0;b<NUM;b++)
		   {
			   if(MG.view[d][b].adj<20000&&P[a][b])  /* �������һ������һ���ٽ��֮�����·�������·�� */
			   {
				   printf("-->%s",MG.vex[b].name);  /* ����˽ڵ������ */
                   q=q+1;     /* ����������һ����8�������ʱ�Ļ��� */
                   P[a][b]=0;
                   d=b;     /* ��b��Ϊ�����������һ��ѭ���������˷��� */
                   if(q%8==0) printf("\n");
                   goto gate;
			   }
		   }
		}
	}
 }
void Searchpath1(MGraph g)/*��ѯ��������������·��*/
{
	int l=0;
	int k=0;
	int i,j;
	 printf("ѡ��������㣺");
	 scanf("%d",&i);
	 printf("ѡ��Ŀ�ؾ��㣺");
	 scanf("%d",&j);
	 for(;k<g.vexnum;k++)/*g.vexnumber��ʾ���еĶ������*/
		 if(i==g.vex[k].number) i=k;/*�������ҵ�����������ĳ�������ı����ͬ�Ķ���*/ 
		 for(;l<g.vexnum;l++)
			 if(j==g.vex[l].number) j=l;/*�������ҵ������������Ŀ�ؾ���ı����ͬ�Ķ���*/ \
				 printf("\n��%s��%s����������·����:\n\n",g.vex[i].name,g.vex[j].name);/*������������Ŀ�ؾ��������*/
			 disppath(g,i,j);/*����disppath����,���������������������·��*/
}
void disppath(MGraph g,int i,int j)
{
	int k;
	p[0]=i;
	for(k=0;k<g.vexnum;k++)
		visited[i]=0;/*��ʼ��������ķ��ʱ�־λ������Ϊδ���ʹ���*/
	a=0;/*��ʼ��·��������*/
	path(g,i,j,0);/*ͨ������path�������ҵ���vi��vj������·�������*/
}
void path(MGraph g,int i,int j,int k)
/*ȷ��·���ϵ�k+1����������*/
{
	int s;
	if(p[k]==j)/*�ҵ�һ��·��*/
	{
		a++;/*·��������ֵ��1*/
		printf("��%d��:\t",a);
		for(s=0;s<=k-1;s++)/*���һ��·��*/
		{
			printf("%s",g.vex[p[s]].name);
			printf("->");
		}
		//cout<<g.vex[p[s]].name;
		printf("%s\n",g.vex[p[s]].name);                    
	}
	s=0;
	while(s<g.vexnum)
	{
		if(s!=i)/*��֤�ҵ����Ǽ�·��*/
		{
			if(g.view[p[k]][s].adj!=Max&&visited[s]==0)
				/*��vk��vs֮���бߴ�����vsδ�����ʹ�*/
			{
				visited[s]=1;/*�÷��ʱ�־λΪ1,���ѷ��ʵ�*/
				p[k+1]=s;/*������s���뵽p������*/
                path(g,i,j,k+1);/*�ݹ����֮*/
                visited[s]=0;/*���÷��ʱ�־λΪ0����δ���ʵģ��Ա�ö����ܱ�����ʹ��*/
			}
		}
		s++;
	}
}
int Addnewsight(int n)
{
	int i;
	char name[100],description[1000];
	int length;
		printf("�������¾�������ƣ�\n");
		scanf("%s",&name);
		printf("�������¾���������Ϣ��\n");
		scanf("%s",&description);
		strcpy(MG.vex[n].name,name);
	    strcpy(MG.vex[n].description,description);
		MG.vex[n].number=n;
		for(i=0;i<n;i++)
		{   system("cls");
            narrate();
			printf("������˾��㵽��%d������ľ��루��λ��m����ͬһ����򲻿ɵ�����20000��ʾ����\n",i);
			scanf("%d",&length);
			if(length!=20000)
				MG.arcnum++;
			MG.view[n][i].adj=MG.view[i][n].adj=length;
		}
		n++;
		MG.vexnum++;
	return n;
}
int Deletesight(int n)
{
	int i;
	int j;
	char c;
	int num;
	char name[20];
		system("cls");
        c=SearchMenu();
        switch (c)
		{
         case '1':  
			 system("cls");
             narrate();
             printf("\n\n\t\t��������Ҫɾ������ı�ţ�");
             scanf("%d",&num);
             for(i=0;i<NUM;i++)
			 {
				 if(num==MG.vex[i].number)
				 {
					 for(j=0;j<NUM;j++)
					 {
						 if(MG.view[i][j].adj!=20000)
							 MG.arcnum--;
						 MG.view[i][j].adj=MG.view[j][i].adj=20000;
					 }
					
				 }
			}
			 for(;num<NUM;num++)
					{
						strcpy(MG.vex[num].name,MG.vex[num+1].name);
						strcpy(MG.vex[num].description,MG.vex[num+1].description);
					}
					 n--;
     printf("\n\t\t\t�����������...");
     getchar();
     getchar();
     break;
   if(i==NUM)
   {
    printf("\n\n\t\t\tû���ҵ���");
    printf("\n\n\t\t\t�����������...");
    getchar();
    getchar();
   }
   break;
  case '2':
   system("cls");
   narrate();
   printf("\n\n\t\t��������Ҫɾ����������ƣ�");
   scanf("%s",name);
   for(i=0;i<NUM;i++)
   {
    if(!strcmp(name,MG.vex[i].name))
    {
		 num=i;
		 for(j=0;j<NUM;j++)
		 {
			if(MG.view[i][j].adj!=20000)
			    MG.arcnum--;
			MG.view[i][j].adj=MG.view[j][i].adj=20000;
		 }
	}
   }
   for(;num<NUM;num++)
		 {
			 strcpy(MG.vex[num].name,MG.vex[num+1].name);
			 strcpy(MG.vex[num].description,MG.vex[num+1].description);
		 }
		 n--;
     printf("\n\t\t\t�����������...");
     getchar();
     getchar();
     break;
   if(i==NUM)
   {
    printf("\n\n\t\t\tû���ҵ���");
    printf("\n\n\t\t\t�����������...");
  getchar();
    getchar();
   }
   break;
  }
		return n;
}
char Changemenu()
{
char c;
 int flag;
 do{
  flag=1;
  system("cls");
  narrate();
  printf("\n\t\t\t����������������������������������\n");
  printf("\t\t\t��                              ��\n");
  printf("\t\t\t��      1���޸ľ�����Ϣ         ��\n");
  printf("\t\t\t��      2���޸ĵ�·��Ϣ         ��\n");
  printf("\t\t\t��      e������                 ��\n");
  printf("\t\t\t��                              ��\n");
  printf("\t\t\t����������������������������������\n");
  printf("\t\t\t\t����������ѡ��");
  scanf("%c",&c);
  if(c=='1'||c=='2'||c=='e')
   flag=0;
 }while(flag);
 return c;
}
char Sightmenu()
{
	char c;
	int flag;
	do{
		flag=1;
		system("cls");
        narrate();
  printf("\n\t\t\t����������������������������������\n");
  printf("\t\t\t��                              ��\n");
  printf("\t\t\t��      1���޸ľ�������         ��\n");
  printf("\t\t\t��      2���޸ľ�������         ��\n");
  printf("\t\t\t��      e������                 ��\n");
  printf("\t\t\t��                              ��\n");
  printf("\t\t\t����������������������������������\n");
  printf("\t\t\t\t����������ѡ��");
  scanf("%c",&c);
  if(c=='1'||c=='2'||c=='e')
   flag=0;
 }while(flag);
 return c;
}
void Changesight()
{
	int a,b,length;
	char name[100];
	char description[1000];
	char p;
	char q;
	int i;
	int num;	
	p=Changemenu();
	switch(p)
	{
	case'1':
		system("cls");
             narrate();
             printf("\n\n\t\t��������Ҫ�޸ĵľ����ţ�");
             scanf("%d",&num);
             for(i=0;i<NUM;i++)
			 {
				 if(MG.vex[i].number==num)
				 {
					 q=Sightmenu();
					 if(q=='1')
					 {
						 printf("�������޸ĺ�ľ������ƣ�\n");
                         scanf("%s",&name);
						 strcpy(MG.vex[num].name,name);
						 printf("\t\t\t\t�޸ĳɹ���\n");
					 }
					 else if(q=='2')
					 {
						 printf("�������޸ĺ�ľ�����Ϣ��\n");
						 scanf("%s",&description);
						 strcpy(MG.vex[num].description,description);
						 printf("\t\t\t\t�޸ĳɹ���\n");
					 }
					 else if(q=='e')
						 p=Changemenu();
				 }
			}		
     printf("\n\t\t�����������...");
     getchar();
     getchar();
     break;
   if(i==NUM)
   {
    printf("\n\n\t\t\t\tû���ҵ���");
    printf("\n\n\t\t\t�����������...");
    getchar();
    getchar();
   }
   break;
 	case '2':
			printf("\t\t�������·һ��ľ�����ţ�");
			scanf("%d",&a);
			printf("\t\t�������·��һ��ľ�����ţ�");
			scanf("%d",&b);
			printf("\t\t�������޸ĺ�ĵ�·���ȣ�");
			scanf("%d",&length);
			MG.view[a][b].adj=MG.view[b][a].adj=length;
			printf("\t\t\t\t�޸ĳɹ���\n");
            printf("\t\t");
			getchar();
			system("PAUSE");
			break;	
	}
}	
