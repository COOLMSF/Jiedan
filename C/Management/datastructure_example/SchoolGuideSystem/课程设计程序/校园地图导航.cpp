#include <string.h> 
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define Max 20000		//定义路径最大值 

typedef struct ArcCell{
	int adj;  				//相邻接的景点之间的路程
}ArcCell;   				//定义边的类型
typedef struct VertexType{	//存储景点信息的结构体 
	int number;  			//景点编号
    char name[100];  		//景点名称
    char description[1000]; //景点描述 
}VertexType;   				//定义顶点的类型 
typedef struct{
	VertexType vex[20]; 	//图中的顶点，即为景点 
    ArcCell view[20][20]; 	//图中的边，即为景点间的距离
    int vexnum,arcnum; 		//图中顶点数，边数 
}MGraph;   					//定义图的类型 

MGraph MG;   				//把图定义为全局变量

int NUM=9;			//当前景点的数量 
int P[20][20];
int p[20];			//全局数组，用来存放路径上的各顶点
int visited[20];	//全局数组，用来记录各顶点被访问的情况
int a=0;			//全局变量，用来记录每对顶点之间的所有路径的条数
long int D[20];  	//辅助变量存储最短路径长度
int x[20]={0}; 
char userName[15]={"admin"},pwd[7]={"123456"},newPwd[7];//username[15]原始账号，pwd[7]原始密码,pwd1修改密码时的比较 
char c;	//方便用户的使用，按下任意键可以返回 

void CreateUDN(int v,int a); 		//造图函数，地图初始化 
void narrate();   					//说明函数，显示校园的景点 
void shortRoad(int num); 		//最短路径函数
void output(int sight1,int sight2); //输出函数
void search();   					//查询景点信息
char SearchMenu();  				//查询子菜单
void HaMiTonian(int);   			//图的遍历
void Searchpath1(MGraph g);			//查询两个景点间的所有路径
void disppath(MGraph g,int i,int j);
void path(MGraph g,int i,int j,int k);//确定路径上第k+1个顶点的序号
void NextValue(int);   
void display(); 					//显示遍历结果
int  Addnewsight(int n); 			//添加新的景点和路径
int  Deletesight(int n); 			//删除景点和路径
void Changesight(); 				//修改景点和路径
char Changemenu();  				//修改路径或顶点的选择菜单
char Sightmenu();  					//选择需该景点的菜单
void login();						//用户登录界面 
void homePage();					//系统主菜单 
void quit();						//程序退出界面 
void map();							//校园地图界面 
int main(){ 			//主函数 
	CreateUDN(NUM,11);	//初始化 
    //login();
	homePage(); 
}
void login(){   		//登录界面
	int i=0,k=0,j;		//i是循环变量,k是判断输入三次密码，j是输入密码时的循环  
	system("color 3f");	//系统函数，color显示颜色,3湖蓝色，f是亮白色 
	printf("\n\n");
	printf("\t 系统默认用户名：admin,密码：123456\n");
	printf("\t┏—————————————————————————————-┓\n");
	printf("\t┃ **********************************************************┃\n");
	printf("\t┃ ***┏————————————————————————-┓ ***┃\n");
	printf("\t┃ ***┃ ************************************************┃ ***┃\n");
	printf("\t┃ ***┃ ***                                          ***┃ ***┃\n");
	printf("\t┃ ***┃ ***         欢迎使用校园导游程序系统         ***┃ ***┃\n");
	printf("\t┃ ***┃ ***                                          ***┃ ***┃\n");
	printf("\t┃ ***┃ ***                姓名                      ***┃ ***┃\n");
	printf("\t┃ ***┃ ***                                          ***┃ ***┃\n");
	printf("\t┃ ***┃ ***                枕月                      ***┃ ***┃\n");
	printf("\t┃ ***┃ ***                                          ***┃ ***┃\n"); 
	printf("\t┃ ***┃ ***            2021年12月3日                 ***┃ ***┃\n");
	printf("\t┃ ***┃ ***                                          ***┃ ***┃\n");
	printf("\t┃ ***┃ ************************************************┃ ***┃\n");
	printf("\t┃ ***┗————————————————————————-┛ ***┃\n");
	printf("\t┃ **********************************************************┃\n");
	printf("\t┗—————————————————————————————-┛\n");
	char userName1[15];   //定义与原始密码相比较的变量 
	for(i=0;i<3;i++){
		printf("\n请输入用户名:");
		gets(userName1);
		printf("\n请输入6位密码:");
		for(j=0;j<100;j++){
			newPwd[j]=getch();
			if(newPwd[j]=='\r')
			break;
			printf("*");	
		}
		newPwd[j]='\0';
	if((strcmp(userName,userName1)==0)&&(strcmp(pwd,newPwd)==0)){
		printf("\n\n您已经成功登录");
		k=1; 
		for(i=0;i<20;i++){
			printf(".");
			Sleep(100);
		} 
		system("cls");
		homePage();			//跳转到主界面 
		break;
	}
	else  printf("\n用户名或密码无效请重新输入:\n");
	continue;
	}
	if(k==0) 
	printf("\n连续输入错误3次将退出程序\n");
	Sleep(2000);		//程序暂停函数（单位毫秒），本次暂停2000毫秒 
	quit();				//连续三次错误跳转退出界面 
}	
void homePage(){
	int cmd; //用户选择的编号 
	int v0,v1;
	while(1){
		printf("\n\n");
		printf("\t┏——————————————————————————————-┓\n");
		printf("\t┃ ╔========================================================╗  ┃\n");
		printf("\t┃ ║          欢 迎 使 用 校 园 地 图 导 航 系 统           ║  ┃\n");
		printf("\t┃ ╚========================================================╝  ┃\n");
		printf("\t┃ *********************************************************** ┃\n"); 
		printf("\t┃ *                          *                              * ┃\n"); 
		printf("\t┃ *         1.景点信息查询   *      2.景点最短路径          * ┃\n"); 
		printf("\t┃ *                          *                              * ┃\n"); 
		printf("\t┃ *********************************************************** ┃\n"); 
		printf("\t┃ *                          *                              * ┃\n"); 
		printf("\t┃ *         3.两景点的路径   *      4.校园地图显示          * ┃\n"); 
		printf("\t┃ *                          *                              * ┃\n"); 
		printf("\t┃ *********************************************************** ┃\n"); 
		printf("\t┃ *                          *                              * ┃\n");
		printf("\t┃ *         5.景点路径添加   *      6.退出信息删除          * ┃\n");
		printf("\t┃ *                          *                              * ┃\n");
		printf("\t┃ *********************************************************** ┃\n");
		printf("\t┃ *                          *                              * ┃\n");
		printf("\t┃ *         7.景点路径修改   *      8.退出信息系统          * ┃\n");
		printf("\t┃ *                          *                              * ┃\n");
		printf("\t┃ *********************************************************** ┃\n");  
		printf("\t┗——————————————————————————————-┛\n"); 
		printf("\t请选择功能 1 - 8 :");
        scanf("%d",&cmd);
		getchar();
		system("cls");
        switch(cmd){
        	case 1:search();break;
			case 2:
				system("cls");
				//narrate();
            	printf("\n\n\t\t\t请选择起点景点（0～%d）：",NUM-1);
            	scanf("%d",&v0);
            	printf("\t\t\t请选择终点景点（0～%d）：",NUM-1);
            	scanf("%d",&v1);
            	shortRoad(v0);  /* 计算两个景点之间的最短路径 */
            	output(v0,v1);     /* 输出结果 */
            	printf("\n\n\t\t\t\t请按任意键继续...\n");
            	getchar();
            	getchar();break;
			case 3:
				system("cls");
            	narrate();
        		x[0]=1;   
            	Searchpath1(MG);
            	printf("\n\n\t\t\t\t请按任意键继续...\n");
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
			default:printf("\n 非法操作,请重新输入！\n");
		}
			system("pause");
			system("cls");
    }	
}
void map(){						      //浏览校园地图
	system("cls");
	printf("\t\n                            重庆师范大学                               \n");
	printf("\t-------------------------------------------------------------------------\n");
	printf("\t|      -----------------           ‖         ------------   ‖         |\n");
	printf("\t|      |       10.     |           ‖         |9. 美术学院 | ‖         |\n");
	printf("\t|      |   音乐学院    |           ‖         ------------   ‖         |\n");
	printf("\t|      -----------------           ‖                        ‖--------||\n");
	printf("\t|==================================‖========================‖|   雅  ||\n");
	printf("\t|                 ‖    |               |  ‖     ---------- ‖| 8.风  ||\n");
	printf("\t|     ----------  ‖    |        6.     |  ‖     |        | ‖|   苑  ||\n");
	printf("\t|     |        |  ‖    |     图书馆    |  ‖     |7.三食堂| ‖|-------||\n");
	printf("\t|     |5.一食堂|  ‖    |               |  ‖     |        | ‖         |\n");
	printf("\t|     |--------|  ‖    |---------------|  ‖     |--------| ‖         |\n");
	printf("\t|                 ‖                       ‖                ‖         |\n");
	printf("\t|=======================================================================|\n");
	printf("\t|  |  足  |   |         ‖ ‖            ‖            ‖               |\n");
	printf("\t|  |4.球  |   |--------|‖ ‖            ‖            ‖               |\n");
	printf("\t|  |  场  |   |        |‖ ‖            ‖     校     ‖               |\n");
	printf("\t|  |------|   |    弘  |‖ ‖=========== ‖   3.友     ‖               |\n");
	printf("\t|             | 2. 徳  |‖ ‖            ‖     会     ‖               |\n");
	printf("\t|             |    楼  |‖ ‖            ‖     堂     ‖               |\n");
	printf("\t|=======================================================================|\n");
	printf("\t|                         ----------------                              |\n");
	printf("\t|                         |              |                              |\n");
	printf("\t|                         |    1.正门    |                              |\n");
	printf("\t-------------------------------------------------------------------------\n");
	printf("\n\t                按任意键返回主菜单.                    \n");
	c=getch();system("cls");	
	homePage();
	
}
void quit(){	//退出程序界面 
	system("cls");
	printf("\n\n\t┏—————————————————————————————┓\n");
	printf("\t┃ *********************************************************┃\n"); 
	printf("\t┃ *                       谢谢使用本程序                  *┃\n"); 
	printf("\t┃ *********************************************************┃\n");
	printf("\t┗—————————————————————————————┛\n\n");
	exit(0);	
} 
char SearchMenu(){  /* 查询子菜单 */
	char c;
 	int flag;
 	do{
  		flag=1;
  		system("cls");
  		printf("\n\t\t\t┏————————————————┑\n");
  		printf("\t\t\t┃                                ┃\n");
  		printf("\t\t\t┃      1、按照景点编号查询       ┃\n");
  		printf("\t\t\t┃      2、按照景点名称查询       ┃\n");
  		printf("\t\t\t┃      3、返回主菜单             ┃\n");
  		printf("\t\t\t┃                                ┃\n");
  		printf("\t\t\t┗————————————————┛\n");
  		printf("\t\t\t\t请输入您的选择：");
  		scanf("%c",&c);
  		if(c=='1'||c=='2'||c=='3')
   		flag=0;
 	}while(flag);
 	return c;
}
void search(){  /* 查询景点信息 */
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
   			printf("\n\n\t\t请输入您要查找的景点编号：");
   			scanf("%d",&num);
   			for(i=0;i<NUM;i++){
    			if(num==MG.vex[i].number){
     				printf("\n\n\t\t\t您要查找景点信息如下:");
     				printf("\n\n\t\t\t景点名称：%-25s\n",MG.vex[i].name);
     				printf("\n\n\t\t\t景点介绍：%-25s\n\n",MG.vex[i].description);
     				printf("\n\t\t\t按任意键返回...");
     				getchar();
     				getchar();
     				break;
    			}
   			}
   		if(i==NUM){
    		printf("\n\n\t\t\t没有找到！");
    		printf("\n\n\t\t\t按任意键返回...");
    		getchar();
    		getchar();
   			}break;
 	 case '2':
   		system("cls");
   		printf("\n\n\t\t请输入您要查找的景点名称：");
   		scanf("%s",name);
   		for(i=0;i<NUM;i++){
    		if(!strcmp(name,MG.vex[i].name)){
     			printf("\n\n\t\t\t您要查找景点信息如下:");
     			printf("\n\n\t\t\t景点名称：%-25s\n",MG.vex[i].name);
     			printf("\n\n\t\t\t景点介绍：%-25s\n\n",MG.vex[i].description);
     			printf("\n\t\t\t按任意键返回...");
     			getchar();
     			getchar();break;
    		}
   		}
   		if(i==NUM){
    		printf("\n\n\t\t\t没有找到！");
    		printf("\n\n\t\t\t按任意键返回...");
    		getchar();
    		getchar();
   			}break;
  		}
 	}while(c!='3');
}
void CreateUDN(int v,int a){	//造图函数，给景点初始化 
	int i,j;
	MG.vexnum=v;  	//初始化结构体中的景点数
	MG.arcnum=a;	//初始化结构体的边数 
	for(i=0;i<20;++i) MG.vex[i].number=i; //初始化每一个景点的编号
 	strcpy(MG.vex[0].name,"学校正门");
	strcpy(MG.vex[0].description,"位于重庆市沙坪坝区大学城中路37号，交通便利。");
	strcpy(MG.vex[1].name,"弘德楼");
 	strcpy( MG.vex[1].description,"弘德楼作为我校的主教学楼， 共有139间教室， 可容11800位学子入座。");
 	strcpy(MG.vex[2].name,"校友会堂");
 	strcpy(MG.vex[2].description,"这是一个让广大校友回到母校聚集一堂，这里寄托了重师就是我的家的美好心愿。");
 	strcpy(MG.vex[3].name,"足球场");
 	strcpy(MG.vex[3].description,"这是重师学子强身健体的地方，丰富课余生活。");
 	strcpy(MG.vex[4].name,"一食堂");
 	strcpy(MG.vex[4].description,"这是重师学子最喜欢的一食堂。");
 	strcpy(MG.vex[5].name,"图书馆");
	strcpy(MG.vex[5].description,"历史悠久，文化积淀。供同学安静学习的环境。");
 	strcpy(MG.vex[6].name,"三食堂");
 	strcpy(MG.vex[6].description,"这是重师学子最朴素的三食堂。");
 	strcpy(MG.vex[7].name,"雅风苑");
 	strcpy(MG.vex[7].description,"这是女生宿舍，离南门最近，离宏德楼最远的宿舍。");
 	strcpy(MG.vex[8].name,"美术学院");
 	strcpy(MG.vex[8].description,"这是重师学美术学子上课的地方。");
 	//这里把所有的边假定为20000，含义是这两个景点之间是不可到达 */
	 for(i=0;i<20;++i)
  		for(j=0;j<20;++j) 
   			MG.view[i][j].adj=Max;
   /*下边是可直接到达的景点间的距离，由于两个景点间距离是互相的，所以要对图中对称的边同时赋值。*/
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
void narrate(){ 	//说明函数，介绍每个景点 
 	int i,k=0;
 	printf("\n\t***************欢迎使用重庆师范大学校园导游程序**************\n");
 	printf("\t__________________________________________________________________\n");
 	printf("\t 景点名称\t\t\t景点描述\t\t\t\n");
 	printf("\t________________________|_________________________\n");
 	for(i=0;i<NUM;i++){ 
  		printf("\t(%2d )%-10s\t\t|    %-8s\n",i,MG.vex[i].name,MG.vex[i].description); //输出景点列表
  		k=k+1;
 	}
 	printf("\t________________________|_________________________\n");
}
void shortRoad(int num){ 		//迪杰斯特拉算法最短路径函数 num为入口点的编号 
 	int v,w,i,t;  		// i、w和v为计数变量 
 	int final[20];
 	int min;
 	for(v=0;v<NUM;v++){
  		final[v]=0; 	 			//假设从顶点num到顶点v没有最短路径 
  		D[v]=MG.view[num][v].adj;	//将与之相关的权值放入D中存放
  		for(w=0;w<NUM;w++) 			//设置为空路径 
   			P[v][w]=0;
  			if(D[v]<20000){  		//存在路径 
   				P[v][num]=1; 		//存在标志置为一 
   				P[v][v]=1; 			//自身到自身
  			}
 	}
 	D[num]=0;
 	final[num]=1;      //初始化num顶点属于S集合
	 /* 开始主循环，每一次求得num到某个顶点的最短路径，并将其加入到S集合 */
 	for(i=0;i<NUM;++i){     	// 其余MG.vexnum-1个顶点 
  		min=Max;     			//当前所知离顶点num的最近距离 
  		for(w=0;w<NUM;++w)
   			if(!final[w])    	//w顶点在v-s中 
    			if(D[w]<min){   //w顶点离num顶点更近 
     				v=w;
     				min=D[w];
    			} 
    	final[v]=1;  			 // 离num顶点更近的v加入到s集合 
    	for(w=0;w<NUM;++w)  	//更新当前最短路径极其距离 
     	if(!final[w]&&((min+MG.view[v][w].adj)<D[w])){		//不在s集合，并且比以前所找到的路径都短就更新当前路径
      		D[w]=min+MG.view[v][w].adj;
      		for(t=0;t<NUM;t++)
       			P[w][t]=P[v][t];
      		P[w][w]=1;
    	 }
 	}
}
void output(int sight1,int sight2){    //输出函数
	int a,b,c,d,q=0;
    a=sight2;    /* 将景点二赋值给a */
    if(a!=sight1)    /* 如果景点二不和景点一输入重合，则进行... */
	{
		printf("\n\t从%s到%s的最短路径是",MG.vex[sight1].name,MG.vex[sight2].name);/* 输出提示信息 */ 
        printf("\t(最短距离为 %dm.)\n\n\t",D[a]);  /* 输出sight1到sight2的最短路径长度，存放在D[]数组中 */
        printf("\t%s",MG.vex[sight1].name);   /* 输出景点一的名称 */
        d=sight1;      /* 将景点一的编号赋值给d */
        for(c=0;c<NUM;++c)
		{
           gate:;        /* 标号，可以作为goto语句跳转的位置 */
           P[a][sight1]=0;
           for(b=0;b<NUM;b++)
		   {
			   if(MG.view[d][b].adj<20000&&P[a][b])  /* 如果景点一和它的一个临界点之间存在路径且最短路径 */
			   {
				   printf("-->%s",MG.vex[b].name);  /* 输出此节点的名称 */
                   q=q+1;     /* 计数变量加一，满8控制输出时的换行 */
                   P[a][b]=0;
                   d=b;     /* 将b作为出发点进行下一次循环输出，如此反复 */
                   if(q%8==0) printf("\n");
                   goto gate;
			   }
		   }
		}
	}
 }
void Searchpath1(MGraph g)/*查询两个景点间的所有路径*/
{
	int l=0;
	int k=0;
	int i,j;
	 printf("选择出发景点：");
	 scanf("%d",&i);
	 printf("选择目地景点：");
	 scanf("%d",&j);
	 for(;k<g.vexnum;k++)/*g.vexnumber表示网中的顶点个数*/
		 if(i==g.vex[k].number) i=k;/*在网中找到其编号与输入的出发景点的编号相同的顶点*/ 
		 for(;l<g.vexnum;l++)
			 if(j==g.vex[l].number) j=l;/*在网中找到其编号与输入的目地景点的编号相同的顶点*/ \
				 printf("\n从%s到%s的所有游览路径有:\n\n",g.vex[i].name,g.vex[j].name);/*输出出发景点和目地景点的名称*/
			 disppath(g,i,j);/*调用disppath函数,用来输出两个景点间的所有路径*/
}
void disppath(MGraph g,int i,int j)
{
	int k;
	p[0]=i;
	for(k=0;k<g.vexnum;k++)
		visited[i]=0;/*初始化各顶点的访问标志位，即都为未访问过的*/
	a=0;/*初始化路径的条数*/
	path(g,i,j,0);/*通过调用path函数，找到从vi到vj的所有路径并输出*/
}
void path(MGraph g,int i,int j,int k)
/*确定路径上第k+1个顶点的序号*/
{
	int s;
	if(p[k]==j)/*找到一条路径*/
	{
		a++;/*路径的条数值加1*/
		printf("第%d条:\t",a);
		for(s=0;s<=k-1;s++)/*输出一条路径*/
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
		if(s!=i)/*保证找到的是简单路径*/
		{
			if(g.view[p[k]][s].adj!=Max&&visited[s]==0)
				/*当vk与vs之间有边存在且vs未被访问过*/
			{
				visited[s]=1;/*置访问标志位为1,即已访问的*/
				p[k+1]=s;/*将顶点s加入到p数组中*/
                path(g,i,j,k+1);/*递归调用之*/
                visited[s]=0;/*重置访问标志位为0，即未访问的，以便该顶点能被重新使用*/
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
		printf("请输入新景点的名称：\n");
		scanf("%s",&name);
		printf("请输入新景点的相关信息：\n");
		scanf("%s",&description);
		strcpy(MG.vex[n].name,name);
	    strcpy(MG.vex[n].description,description);
		MG.vex[n].number=n;
		for(i=0;i<n;i++)
		{   system("cls");
            narrate();
			printf("请输入此景点到第%d个景点的距离（单位：m）（同一景点或不可到达用20000表示）：\n",i);
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
             printf("\n\n\t\t请输入您要删除景点的编号：");
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
     printf("\n\t\t\t按任意键返回...");
     getchar();
     getchar();
     break;
   if(i==NUM)
   {
    printf("\n\n\t\t\t没有找到！");
    printf("\n\n\t\t\t按任意键返回...");
    getchar();
    getchar();
   }
   break;
  case '2':
   system("cls");
   narrate();
   printf("\n\n\t\t请输入您要删除景点的名称：");
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
     printf("\n\t\t\t按任意键返回...");
     getchar();
     getchar();
     break;
   if(i==NUM)
   {
    printf("\n\n\t\t\t没有找到！");
    printf("\n\n\t\t\t按任意键返回...");
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
  printf("\n\t\t\t┏━━━━━━━━━━━━━━━┑\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┃      1、修改景点信息         ┃\n");
  printf("\t\t\t┃      2、修改道路信息         ┃\n");
  printf("\t\t\t┃      e、返回                 ┃\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┗━━━━━━━━━━━━━━━┛\n");
  printf("\t\t\t\t请输入您的选择：");
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
  printf("\n\t\t\t┏━━━━━━━━━━━━━━━┑\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┃      1、修改景点名称         ┃\n");
  printf("\t\t\t┃      2、修改景点描述         ┃\n");
  printf("\t\t\t┃      e、返回                 ┃\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┗━━━━━━━━━━━━━━━┛\n");
  printf("\t\t\t\t请输入您的选择：");
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
             printf("\n\n\t\t请输入您要修改的景点编号：");
             scanf("%d",&num);
             for(i=0;i<NUM;i++)
			 {
				 if(MG.vex[i].number==num)
				 {
					 q=Sightmenu();
					 if(q=='1')
					 {
						 printf("请输入修改后的景点名称：\n");
                         scanf("%s",&name);
						 strcpy(MG.vex[num].name,name);
						 printf("\t\t\t\t修改成功！\n");
					 }
					 else if(q=='2')
					 {
						 printf("请输入修改后的景点信息：\n");
						 scanf("%s",&description);
						 strcpy(MG.vex[num].description,description);
						 printf("\t\t\t\t修改成功！\n");
					 }
					 else if(q=='e')
						 p=Changemenu();
				 }
			}		
     printf("\n\t\t按任意键返回...");
     getchar();
     getchar();
     break;
   if(i==NUM)
   {
    printf("\n\n\t\t\t\t没有找到！");
    printf("\n\n\t\t\t按任意键返回...");
    getchar();
    getchar();
   }
   break;
 	case '2':
			printf("\t\t请输入道路一侧的景点序号：");
			scanf("%d",&a);
			printf("\t\t请输入道路另一侧的景点序号：");
			scanf("%d",&b);
			printf("\t\t请输入修改后的道路长度：");
			scanf("%d",&length);
			MG.view[a][b].adj=MG.view[b][a].adj=length;
			printf("\t\t\t\t修改成功！\n");
            printf("\t\t");
			getchar();
			system("PAUSE");
			break;	
	}
}	
