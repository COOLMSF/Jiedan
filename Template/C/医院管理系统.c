/*
                   程序说明:
   医院各科室的医生数量有限，因此病人到医院看病时必须排队候诊，病人的病情有轻重缓急之分，

     不能仅仅根据先来先服务的原则就诊，（例如：重症，生命垂危的病人应该先行就诊）所以在此根据病人的病情安排不同的
     优先级。 医生在就诊时，首先选择优先级别高的病人就诊，如果遇到两个病人的优先级别相同的情况，则按照先到先就诊的
     原则进行诊治。 
*/


//数据结构说明:  循环队列,队列和最大堆(优先队列)
//病人编号从10——开始。

#include<stdio.h>
// #include<malloc.h>
#include<string.h>
#include<stdlib.h>
#define LEN sizeof(jiedian)
typedef int DataType;
#define ERROR -1
#define OK 1
#define mid 0
#define zongsize 200   //总队列长度
#define MAXQSIZE 100   //最大队列长度
#define Maxsize  20    //最大堆的容量



#define Infinity 1000
#define MaxVertexNum 35
#define MAX 40
#include<stdlib.h>
// #include<conio.h>
//#include<iostream.h>




typedef struct arcell
{ //边的权值信息
    int adj;                                     //权值
}arcell, adjmatrix[MaxVertexNum][MaxVertexNum];  //图的邻接矩阵类型

typedef struct vexsinfo
{//顶点信息
          int position;                //景点编号
          char name[32];               //景点的名称
          char introduction[256];           //景点的介绍
}vexsinfo;
typedef struct mgraph
{//图结构信息
          vexsinfo vexs[MaxVertexNum];         //顶点向量【数组】
          adjmatrix arcs;                      //邻接矩阵
          int vexnum, arcnum;              //分别指定顶点数和边数
}mgraph;

//全局变量
int  visited[35];                              //用于标志是否已经访问过
int  d[35];                                    //用于存放权值或存储路径顶点编号
mgraph campus;                            //图变量（大学校园）




// (1) 对图初始化
mgraph initgraph()
{
    int i=0,j=0;
    mgraph c;
    c.vexnum =28;                                   //顶点个数
    c.arcnum =48;                                   //边的个数
    for(i=0;i<c.vexnum ;i++)                        //依次设置顶点编号
        c.vexs[i].position =i;
    //依次输入顶点信息
        strcpy(c.vexs[0].name ,"大门");
        strcpy(c.vexs[0].introduction ,"离公交站近");
        strcpy(c.vexs[1].name ,"大厅");
        strcpy(c.vexs[1].introduction ,"门诊大厅,挂号缴费取药");
        strcpy(c.vexs[2].name ,"急诊部");
        strcpy(c.vexs[2].introduction ,"急诊大楼,处理紧急严重病人");
        strcpy(c.vexs[3].name ,"住院部");
        strcpy(c.vexs[3].introduction ,"住院楼,处理那些需要长期治疗的病人");
        strcpy(c.vexs[4].name ,"门诊部");
        strcpy(c.vexs[4].introduction ,"门诊楼,对病人简单的诊断和开处方");
        strcpy(c.vexs[5].name,"行政楼");
        strcpy(c.vexs[5].introduction ,"行政办公,处理医院日常事务");
        strcpy(c.vexs[6].name ,"后勤室");
        strcpy(c.vexs[6].introduction ,"后勤办公,员工衣食以及医院办公用品存储");
        strcpy(c.vexs[7].name,"手术室");
        strcpy(c.vexs[7].introduction ,"手术,对重症者处理伤口");
        strcpy(c.vexs[8].name ,"放射科");
        strcpy(c.vexs[8].introduction ,"拍片和CT,核磁共振");
        strcpy(c.vexs[9].name, "儿科");
        strcpy(c.vexs[9].introduction ,"对儿童的病症处理");
        strcpy(c.vexs[10].name ,"口腔科");
        strcpy(c.vexs[10].introduction ,"口腔大楼,对口腔症状诊断处理");
        strcpy(c.vexs[11].name ,"药房");
        strcpy(c.vexs[11].introduction ,"病人取药和存放药材的地方");
        strcpy(c.vexs[12].name ,"皮肤科");
        strcpy(c.vexs[12].introduction ,"对皮肤出现的症状诊断开处方");
        strcpy(c.vexs[13].name ,"中医科");
        strcpy(c.vexs[13].introduction ,"通过中医的手段进行诊断开中医药材");
        strcpy(c.vexs[14].name ,"B超室");
        strcpy(c.vexs[14].introduction ,"看心脏和产前胎儿情况");
        strcpy(c.vexs[15].name ,"耳鼻喉科");
        strcpy(c.vexs[15].introduction ,"诊断耳朵鼻子喉咙有问题的病人并开处方");
        strcpy(c.vexs[16].name ,"食堂");
        strcpy(c.vexs[16].introduction ,"医生和护士吃饭的地方");
        strcpy(c.vexs[17].name ,"病案室");
        strcpy(c.vexs[17].introduction ,"存放病人档案");
        strcpy(c.vexs[18].name ,"内科");
        strcpy(c.vexs[18].introduction ,"看病人身体内部问题");
        strcpy(c.vexs[19].name ,"外科");
        strcpy(c.vexs[19].introduction ,"病人外部如烧伤,骨伤");
        strcpy(c.vexs[20].name ,"妇科");
        strcpy(c.vexs[20].introduction ,"诊断妇女身体疾病");
        strcpy(c.vexs[21].name ,"眼科");
        strcpy(c.vexs[21].introduction ,"看人体眼部疾病");
        strcpy(c.vexs[22].name ,"重症监护室");
        strcpy(c.vexs[22].introduction ,"重型病人的病房");
        strcpy(c.vexs[23].name ,"产科室");
        strcpy(c.vexs[23].introduction ,"女性疾病的病因、病理、诊断及防治，妊娠、分娩的生理和病理变化，高危妊娠及难产的预防和诊治，女性生殖内分泌，计划生育及妇女保健等");
        strcpy(c.vexs[24].name ,"普通室");
        strcpy(c.vexs[24].introduction ,"一般病人的病房");
        strcpy(c.vexs[25].name ,"院长办公室");
        strcpy(c.vexs[25].introduction ,"管理医院人员以及存放重要文件");
        strcpy(c.vexs[26].name ,"主任办公室");
        strcpy(c.vexs[26].introduction ,"管理大夫和看疑难症状的病人");
        strcpy(c.vexs[27].name ,"大夫办公室");
        strcpy(c.vexs[27].introduction ,"大夫看病以及日常用品的地方");


        //依次输入边上的权值信息
        for(i=0;i<c.vexnum ;i++)
            for(j=0;j<c.vexnum ;j++)
                c.arcs [i][j].adj =Infinity; //先初始化图的邻接矩阵

        //部分弧长

        c.arcs[0][1].adj=40;

        c.arcs[1][2].adj=30;      c.arcs[1][6].adj=25;    c.arcs[1][10].adj=10;

        c.arcs[1][24].adj=200;    c.arcs[1][20].adj=25;

        c.arcs[2][3].adj=7;       c.arcs[2][4].adj=7;     c.arcs[2][5].adj=7;

        c.arcs[4][23].adj=100;

        c.arcs[6][7].adj=8;       c.arcs[6][8].adj=9;     c.arcs[6][9].adj=7;

        c.arcs[7][8].adj=3;       c.arcs[7][9].adj=5;     c.arcs[7][21].adj=15;

        c.arcs[8][9].adj=2;

        c.arcs[9][21].adj=6;

        c.arcs[10][11].adj=5;   c.arcs[10][12].adj=4;   c.arcs[10][13].adj=7;

        c.arcs[10][14].adj=8;   c.arcs[10][15].adj=6;   c.arcs[10][16].adj=7;

        c.arcs[10][17].adj=6;    c.arcs[10][18].adj=4;    c.arcs[10][19].adj=8;

        c.arcs[11][21].adj=10;

        c.arcs[12][21].adj=13;

        c.arcs[13][21].adj=7;

        c.arcs[14][21].adj=3;

        c.arcs[15][21].adj=8;

        c.arcs[16][21].adj=10;

        c.arcs[17][21].adj=15;

        c.arcs[18][21].adj=16;

        c.arcs[19][21].adj=18;

        c.arcs[20][21].adj=25;   c.arcs[20][22].adj=8;   c.arcs[20][23].adj=10;

        c.arcs[21][22].adj=20;   c.arcs[21][23].adj=25;

        c.arcs[23][25].adj=10;

        c.arcs[23][26].adj=11;  c.arcs[23][27].adj=9;

        c.arcs[24][25].adj=5;   c.arcs[24][26].adj=6;    c.arcs[24][27].adj=5;

        c.arcs[26][27].adj=90;

        for(i=0;i<c.vexnum ;i++)                      //邻接矩阵是对称矩阵，对称赋值
            for(j=0;j<c.vexnum ;j++)
                c.arcs[j][i].adj =c.arcs[i][j].adj ;
        return c;
}//initgraph


// (2) 查找景点在图中的序号

int locatevex(mgraph c,int v)
{
    int i;
    for(i=0;i<c.vexnum ;i++)
        if(v==c.vexs[i].position)
            return i;                           //找到，返回顶点序号i

    return -1;                                  //否则，返回-1
}


//(3) 、(4) 求两景点间的所有路径

// (3) 打印序号为m,n景点间的长度不超过6个地点的路径

void path(mgraph c, int m,int n,int k)
{
    int s,x=0;
    int t=k+1;                                  //t 记载路径上下一个中间顶点在d[]数组中的下标
    if(d[k]==n && k<6)                          //d[k]存储路径顶点。若d[k]是终点n且景点个数<=6，则输出该路径
    {                                           //递归出口，找到一条路径
      for(s=0;s<k;s++)
        printf("%s--->",c.vexs[d[s]].name);     //输出该路径。s=0 时为起点m
      printf("%s",c.vexs[d[s]].name);           //输出最后一个地点名(即顶点n的名字，此时s==k)
      printf("\n\n");
    }
    else
    {
      s=0;
      while(s<c.vexnum)                         //从第m个顶点，试探至所有顶点是否有路径
      {
        if((c.arcs[d[k]][s].adj<Infinity) && (visited[s]==0)) //初态：顶点m到顶点s有边，且未被访问
        {
           visited[s]=1;
           d[k+1]=s;                //存储顶点编号s 至d[k+1]中
           path(c,m,n,t);           //求从下标为t=k+1的第d[t]个顶点开始的路径(递归调用)，同时打印出一条m至n的路径
           visited[s]=0;            //将找到的路径上顶点的访问标志重新设置为0，以用于试探新的路径
        }
        s++;                        //试探从下一个顶点 s 开始是否有到终点的路径
      }//endwhile

    }//endelse

}//endpath

//(4) 打印两景点间的景点个数不超过6的所有路径。调用(3)

int allpath(mgraph c)
{
  int k,i,j,m,n;
  printf("\n\n请输入你要查询的两个景点编号:\n\n");
  scanf("%d%d",&i,&j);
  printf("\n\n");
  m=locatevex(c,i);                         //调用(2)，确定该顶点是否存在。若存在，返回该顶点编号
  n=locatevex(c,j);
  d[0]=m;                                   //存储路径起点m (int d[]数组是全局变量)
  for(k=0;k<c.vexnum;k++)                   //全部顶点访问标志初值设为0
    visited[k]=0;
  visited[m]=1;                             //第m个顶点访问标志设置为1
  path(c,m,n,0);                            //调用(3)。k=0，对应起点d[0]==m。k为d[]数组下标
  return 1;
}


// (5) 用迪杰斯特拉算法，求出一个景点到其他景点间的最短路径，并打印

void shortestpath_dij(mgraph c)
{
  //迪杰斯特拉算法，求从顶点v0到其余顶点的最短路经及其带权长度d[v]
  //若p[v][w]为1，则w是从v0到v的最短路经上的顶点
  //final[v]类型用于设置访问标志

    int v,w,i,min,t=0,x,flag=1,v0;                //vo为起始景点的编号
    int final[35],d[35],p[35][35];
    printf("\n请输入一个起始景点的编号：");
    scanf("%d",&v0);
    printf("\n\n");
    while(v0<0||v0>c.vexnum)
    {
        printf("\n你所输入的景点编号不存在\n");
        printf("请重新输入：");
        scanf("%d",&v0);
    }//while
    for(v=0;v<c.vexnum ;v++)
    {
        final[v]=0;                               //初始化各顶点访问标志
        d[v]=c.arcs[v0][v].adj;                   //v0 到各顶点 v 的权值赋值给d[v]
        for(w=0;w<c.vexnum ;w++)                  //初始化p[][]数组，各顶点间的路径全部设置为空路径0
            p[v][w]=0;
        if(d[v]<Infinity)                         //v0 到v 有边相连，修改p[v][v0]的值为1
        {
            p[v][v0]=1;
            p[v][v]=1;                            //各顶点自己到自己要连通
        }
    }//for
    d[v0]=0;                                      //自己到自己的权值设为0
    final[v0]=1;                                  //v0的访问标志设为1，v 属于 s 集
    for(i=1;i<c.vexnum ;i++)                      //对其余c.vexnum-1个顶点w，依次求 v 到 w 的最短路径
    {
        min=Infinity;
        for(w=0;w<c.vexnum ;w++)                  //在未被访问的顶点中，查找与 v0 最近的顶点v
            if(!final[w])
                if(d[w]<min)                      //v0 到 w (有边)的权值<min
                {
                    v=w;
                    min=d[w];
                }//if
        final[v]=1;                                  //v 的访问标志设置为1，v 属于s集
        for(w=0;w<c.vexnum ;w++)                     //修改v0 到其余各顶点w 的最短路径权值d[w]
            if(!final[w]&&(min+c.arcs[v][w].adj <d[w]))  //若w 不属于s，且v 到w 有边相连
            {
                d[w]=min+c.arcs[v][w].adj;               //修改v0 到w 的权值d[w]
                for(x=0;x<c.vexnum ;x++)             //所有v0 到v 的最短路径上的顶点x，都是v0 到w 的最短路径上的顶点
                    p[w][x]=p[v][x];
                p[w][w]=1;
            }//if
    }//for
    for(v=0;v<c.vexnum ;v++)                         //输出v0 到其它顶点v 的最短路径
    {
        if(v!=v0)
            printf("%s",c.vexs[v0].name);            //输出景点v0 的景点名
        for(w=0;w<c.vexnum ;w++)                     //对图中每个顶点w，试探w 是否是v0 到v 的最短路径上的顶点
        {
            if(p[v][w] && w!=v0 && w!=v)             //若w 是且w 不等于v0，则输出该景点
                  printf("--->%s",c.vexs[w].name);

        }
        printf("---->%s",c.vexs[v].name);
        printf("\n总路线长为%d米\n\n",d[v]);



    }//for
}//shortestpath


//(6)-(11)修改图的信息。包括建图、更新信息、删除、增加结点和边

//(6) 构造图的邻接矩阵

 int creatgragh(mgraph *c)                          //建图。以图的邻接矩阵存储图
 {
    int i,j,m,n;
    int v0,v1;
    int distance;
    printf("请输入图的顶点数和边数: \n");
    scanf("%d %d",&c->vexnum ,&c->arcnum );
    printf("下面请输入景点的信息：\n");
    for(i=0;i<c->vexnum ;i++)                       //构造顶点向量(数组)
    {
        printf("请输入景点的编号：");
        scanf("%d",&c->vexs[i].position );
        printf("\n请输入景点的名称：");
        scanf("%s",c->vexs[i].name );
        printf("\n请输入景点的简介：");
        scanf("%s",c->vexs[i].introduction );
    }
    for(i=0;i<c->arcnum ;i++)                       //初始化邻接矩阵
        for(j=0;j<c->arcnum ;j++)
            c->arcs[i][j].adj =Infinity;

    printf("下面请输入图的边的信息：\n");
    for(i=1;i<=c->arcnum ;i++)                      //构造邻接矩阵
    {
        printf("\n第%d条边的起点 终点 长度为：",i);//输入一条边的起点、终点及权值
        scanf("%d %d %d",&v0,&v1,&distance);
        m=locatevex(campus,v0);
        n=locatevex(campus,v1);
        if(m>=0 && n>=0)
        {
            c->arcs[m][n].adj =distance;
            c->arcs[n][m].adj =c->arcs[m][n].adj ;
        }
    }
    return 1;
}//creatgragh


// (7) 更新图的部分信息。返回值: 1

int  newgraph(mgraph *c)
{
    int changenum;                                //计数。用于记录要修改的对象的个数
    int i,m,n,t,distance,v0,v1;
    printf("\n下面请输入你要修改的景点的个数：\n");
    scanf("%d",&changenum);
    while(changenum<0||changenum>c->vexnum )
    {
        printf("\n输入错误！请重新输入");
        scanf("%d",&changenum);
    }

    for(i=0;i<changenum;i++)
    {
        printf("\n请输入景点的编号：");
        scanf("%d",&m);
        t=locatevex(campus,m);
        printf("\n请输入景点的名称：");
        scanf("%s",c->vexs[t].name );
        printf("\n请输入景点的简介：");
        scanf("%s",c->vexs[t].introduction );
    }

    printf("\n下面请输入你要更新的边数");
    scanf("%d",&changenum);
    while(changenum<0||changenum>c->arcnum )
    {
        printf("\n输入错误！请重新输入");
        scanf("%d",&changenum);
    }

    printf("\n下面请输入更新边的信息：\n");
    for(i=1;i<=changenum ;i++)
    {
        printf("\n修改的第%d条边的起点 终点 长度为：",i);
        scanf("%d %d %d",&v0,&v1,&distance);
        m=locatevex(campus,v0);
        n=locatevex(campus,v1);
        if(m>=0 && n>=0)
        {
            c->arcs[m][n].adj =distance;
            c->arcs[n][m].adj =c->arcs[m][n].adj ;
        }
    }
    return 1;
}//newgraph

// (8) 增加一条边。返回值：1

int enarc(mgraph *c)
{
    int m,n,distance;
    printf("\n请输入边的起点和终点编号,权值：");
    scanf("%d %d %d",&m,&n,&distance);
    while(m<0||m>c->vexnum ||n<0||n>c->vexnum )
    {
        printf("输入错误，请重新输入：");
        scanf("%d %d",&m,&n);
    }
    if(locatevex(campus,m)<0)
    {
        printf("此结点%d已删除",m);
        return 1;
    }
    if(locatevex(campus,n)<0)
    {
        printf("此结点%d已被删除：",n);
        return 1;
    }
    c->arcs[m][n].adj =distance;
    c->arcs[n][m].adj =c->arcs[m][n].adj;                 //对称赋值
    return 1;
}//enarc

// (9) 增加一个结点。返回值：1

int envex(mgraph *c)
{
    int i;
    printf("请输入你要增加结点的信息：");
    printf("\n编号：");
    scanf("%d",&c->vexs[c->vexnum ].position );
    printf("名称：");
    scanf("%s",c->vexs[c->vexnum ].name );
    printf("简介：");
    scanf("%s",c->vexs[c->vexnum ].introduction) ;
    c->vexnum ++;
    for(i=0;i<c->vexnum;i++)                           //对原邻接矩阵新增加的一行及一列进行初始化
    {
        c->arcs [c->vexnum -1][i].adj=Infinity;         //最后一行(新增的一行)
        c->arcs [i][c->vexnum -1].adj=Infinity;         //最后一列(新增的一列)
    }
    return 1;
}//envex

// (10) 删除图的一个顶点。返回值：1

int delvex(mgraph *c)
{
    int i=0,j;
    int m;
    int v;
    if(c->vexnum <=0)
    {
        printf("图中已无顶点");
        return 1;
    }
    printf("\n下面请输入你要删除的景点编号：");
    scanf("%d",&v);
    while(v<0||v>c->vexnum  )
    {
        printf("\n输入错误！请重新输入");
        scanf("%d",&v);
    }
    m=locatevex(campus,v);
    if(m<0)
    {
        printf("此顶点 %d 已删除",v);
        return 1;
    }
    for(i=m;i<c->vexnum-1 ;i++)//对顶点信息所在顺序表进行删除m 点的操作
    {
        strcpy(c->vexs[i].name ,c->vexs [i+1].name );
        strcpy(c->vexs[i].introduction ,c->vexs [i+1].introduction );
    }
    //对原邻接矩阵，删除该顶点到其余顶点的邻接关系。分别删除相应的行和列
    for(i=m;i<c->vexnum-1 ;i++)                //行
        for(j=0;j<c->vexnum ;j++)              //列
            c->arcs [i][j]=c->arcs [i+1][j];    //二维数组，从第m+1行开始依次往前移一行。即删除第m 行
    for(i=m;i<c->vexnum-1 ;i++)
        for(j=0;j<c->vexnum ;j++)
            c->arcs [j][i]=c->arcs [j][i+1];    //二维数组，从第m+1列开始依次往前移一列。即删除第m 列
    c->vexnum --;
    return 1;
}//delvex

 //(11) 删除图的一条边。返回值：1

int delarc(mgraph *c)
{
    int m,n;
    int v0,v1;
    if(c->arcnum <=0)
    {
        printf("图中已无边，无法删除。");
        return 1;
    }
    printf("\n下面请输入你要删除的边的起点和终点编号：");
    scanf("%d %d",&v0,&v1);
    m=locatevex(campus,v0);
    if(m<0)
    {
        printf("此 %d 顶点已删除",v0);
        return 1;
    }
    n=locatevex(campus,v1);
    if(n<0)
    {
        printf("此 %d 顶点已删除",v1);
        return 1;
    }
    c->arcs [m][n].adj =Infinity;              //修改邻接矩阵对应的权值
    c->arcs [n][m].adj =Infinity;
    c->arcnum --;
    return 1;
}//delarc

// (12) 输出图的邻接矩阵的值

void printmatrix(mgraph c)
{
    int i,j,k=0;                              //k 用于计数，控制换行

    for(i=0;i<c.vexnum ;i++)
        for(j=0;j<c.vexnum ;j++)
        {
            if(c.arcs[i][j].adj ==Infinity)
                printf("----");
            else
                printf("%4d",c.arcs[i][j].adj);
            k++;
            if(k%c.vexnum ==0)
                printf("\n");
        }
}//printpath

//(13)图操作的主调函数。返回值：1

int changegraph(mgraph *c)
{

    int yourchoice;
    printf("\n请问是要\n\n(1)再次建图            (2)删除结点            (3)删除边\n");
    printf("\n(4)增加结点            (5)增加边              (6)更新信息\n\n(7)打印邻接矩阵        (8)返回?\n\n");

    scanf("%d",&yourchoice);
    printf("\n\n");
    while(!(yourchoice==1||yourchoice==2||yourchoice==3||yourchoice==4||yourchoice==5||yourchoice==6
          ||yourchoice==7||yourchoice==8))
    {
        printf("输入选择不明确，请重输\n");
        scanf("%d",&yourchoice);
    }
    while(1)
    {
        switch(yourchoice)
        {
            case 1:    creatgragh(c);    break;
            case 2: delvex(c);        break;
            case 3:    delarc(c);        break;
            case 4:    envex(c);        break;
            case 5:    enarc(c);        break;
            case 6: newgraph(c);    break;
            case 7: printmatrix(campus);    break;
            case 8:    return 1;
        }
        printf("\n请问是要\n\n(1)再次建图            (2)删除结点            (3)删除边\n");
        printf("\n(4)增加结点            (5)增加边              (6)更新信息\n\n(7)打印邻接矩阵        (8)返回?\n\n");

        scanf("%d",&yourchoice);
        printf("\n\n");
        while(!(yourchoice==1||yourchoice==2||yourchoice==3||yourchoice==4||yourchoice==5||yourchoice==6
              ||yourchoice==7||yourchoice==8))
        {
            printf("输入选择不明确，请重输\n");
            scanf("%d",&yourchoice);
        }
    }//endwhile(1)

    return 1;
}//changegraph

// (14) 查询两景点间的最短路径

void shortestpath_floyd(mgraph c)
{
    //用floyd算法求各对顶点v和w间的最短路经及其带权长度的d[v][w]。
    //若p[v][w][u]==1；则u是v到w的当前求得的最短路经上的顶点

    int i,j,k,d[35][35],p[35][35][35];
    int v,u,w;
    for(v=0;v<c.vexnum ;v++)            //初始化各对顶点 v，w 之间的起始距离 d[v][w] 及 路径 p[v][w][] 数组
    {
        for(w=0;w<c.vexnum ;w++)
        {
            d[v][w]=c.arcs[v][w].adj;   //d[v][w] 中存放 v 至 w 间初始权值
            for(u=0;u<c.vexnum ;u++)    //初始化最短路径 p[v][w][] 数组，第 3 个分量全部清0
                p[v][w][u]=0;
            if(d[v][w]<Infinity)        //如果 v 至 w 间有边相连
            {
                p[v][w][v]=1;           // v 是 v 至 w  最短路径上的顶点
                p[v][w][w]=1;           // w 是 v 至 w  最短路径上的顶点
            }//if
        }//for
    }//endfor

    for(u=0;u<c.vexnum ;u++) // 求v至w的最短路径及距离。对任意顶点u，试探其是否为v至w最短路径上的顶点
    {
        for(v=0;v<c.vexnum ;v++)
            for(w=0;w<c.vexnum ;w++)
              if(d[v][u]+d[u][w]<d[v][w])  //从 v 经 u 到 w 的一条路径更短
              {
                 d[v][w]=d[v][u]+d[u][w];  //修改 v 至 w 的最短路径长度
                 for(i=0;i<c.vexnum ;i++)  //修改 v 至 w 的最短路径数组。 若i是v至u的最短路径上的顶点,
                    p[v][w][i]=p[v][u][i]||p[u][w][i]; //或i是u至w的最短路径上的顶点, 则i是v至w的最短路径上的顶点
              }
    }//endfor

    printf("\n请输入出发点和目的地编号：");
    scanf("%d%d",&k,&j);
    printf("\n\n");
    while(k<0||k>c.vexnum||j<0||j>c.vexnum)
    {
        printf("\n你所输入的景点编号不存在！");
        printf("\n请重新输入出发点和目的地编号：\n\n");
        scanf("%d%d",&k,&j);
        printf("\n\n");
    }
    printf("%s",c.vexs[k].name );              //输出出发景点名称
    for(u=0;u<c.vexnum ;u++)
        if(p[k][j][u] && k!=u && j!=u)         //输出最短路径上中间景点名称
            printf("--->%s",c.vexs[u].name );
    printf("--->%s",c.vexs[j].name );          //输出目的地景点名称

    printf("\n\n\n总长为%d米\n\n\n",d[k][j]);

}//shortestpath_floyd

// (15) 查询景点的信息

void seeabout(mgraph c)
{
    int k;
    printf("\n请输入要查询的景点编号：");
    scanf("%d",&k);
    while(k<0||k>c.vexnum)
    {
        printf("\n你所输入的景点编号不存在！");
        printf("\n请重新输入：");
        scanf("%d",&k);
    }
    printf("\n\n编号：%-4d\n",c.vexs[k].position );
    printf("\n\n景点名称：%-10s\n",c.vexs[k].name );
    printf("\n\n介绍：%-80s\n\n",c.vexs[k].introduction );

}//seeabout

// (16) 显示所有景点信息

void browsecompus(mgraph c)
{
    int i;
    printf(" \n\n编号      景点名称                  简介\n");
    printf("___________________________________________________________________________________________________________\n");

    for(i=0;i<c.vexnum ;i++)
        printf("%-10d%-25s%-80s\n",c.vexs[i].position,c.vexs[i].name,c.vexs[i].introduction);
    printf("___________________________________________________________________________________________________________\n\n");

}//browsecompus




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 typedef struct binren
{
      int id;         //病人ID
}Binren;


typedef struct SqQueue
{
    Binren * base ;                //数组
    int  front;                 //头指针
    int  rear;                  // 尾指针
    int  size;                  //最大队列长度
}Queue;


//病人信息节点
typedef struct node
{    int   id;                     //病人编号
     char  name[30];               //病人姓名
     int  numroom;                 //病房
     char address[30];             //家庭地址
     int  cost;                    //花费
     struct node  *next;
}jiedian , *Jiedian;

jiedian head;


typedef struct Heapstruct
{
    DataType *Elements;      //存储堆元素的数组(存储病人ID)
    int size;                    //堆当前元素个数
    int capacity;               //堆的最大容量
}stack,* MaxHeap;



 //链表的尾插法
void insertTail(jiedian *pHead, int ID,char name[],int  numroom, char a[],int  cost  ){//尾插法
      int len;
      Jiedian t,n;
      n=(jiedian *)malloc(sizeof(LEN));
      t=pHead;
      if(n==NULL)
           printf("分配字节失败");
       n->id=ID;
       strcpy(n->name,name);
       len=strlen(name);
          if(len>0)
              strncpy(n->name,name,len);
          else
              printf("姓名输入错误");
       n->numroom=numroom;                     ////病房号输入可能存在错误，需要设计查错功能。
       strcpy(n->address,a);
       len=strlen(a);
          if(len>0)
              strncpy(n->address,a,len);
          else
              printf("地址输入错误");
          n->cost=cost;
          t->next=n;
          n->next=NULL;
          t=n->next;
  }


      //链表的遍历
void nodetest(jiedian *travel)                 //遍历输出
{

      if(travel->next)
      {     printf("病人的ID:");
            printf("%d\n",travel->next->id);
            printf("病人姓名:");
            printf("%s",travel->next->name);
            printf("病房:");
            printf("%d\n",travel->next->numroom);
            printf("家庭地址:");
            printf("%s",travel->next->address);
            printf("花费:");
            printf("%d\n",travel->next->cost);
            travel=travel->next;

      }

}


      //文本文档的处理
void  wenjianfun (Jiedian tou)                             //文件处理函数
{
         int len,x,y,id,i=1;
         char buf[30],a[30],b[30];
         FILE *fp;
         if((fp=fopen("lwk.txt","r"))==NULL)
             printf("错误");
         else
     while (!feof(fp))
     {
            memset(buf,0,sizeof(buf));
            fgets(buf,sizeof(buf),fp);
               id=atoi(buf);
            printf("%d\n",id);
            memset(buf,0,sizeof(buf));
            fgets(buf,sizeof(buf),fp);
            len=strlen(buf);
              if(len>0)
              strncpy(a,buf,30);
              printf("%s",a);
              memset(buf,0,sizeof(buf));
              fgets(buf,sizeof(buf),fp);
                   x=atoi(buf);                        //atoi为字符串转整型函数，头文件为stdlib.h
              printf("%d\n",x);
            memset(buf,0,sizeof(buf));
            fgets(buf,sizeof(buf),fp);
            len=strlen(buf);
              if(len>0)
              strncpy(b,buf,30);
            printf("%s",b);
            memset(buf,0,sizeof(buf));
              fgets(buf,sizeof(buf),fp);
                   y=atoi(buf);                        //atoi为字符串转整型函数，头文件为stdlib.h
             printf("%d\n",y);
            insertTail(tou,id,a,x,b,y);
     }
     fclose(fp);
}



//1.最大堆的创建
int  createheap(MaxHeap H )
{   //创建容量为Maxsize的空的最大堆
   H->Elements=(DataType*)malloc((Maxsize+1)*sizeof(DataType));
   H->size=0;
   H->capacity=Maxsize;
   H->Elements[0]=1000;              //定义“哨兵”为大于堆中所有可能元素的值，便于以后更快操作
   return OK;
}

//2.判断堆是否满
int Isfull(MaxHeap H)
{              //栈满返回1，否则返回0
    return H->size==H->capacity;
}

//3.判断堆是否空
int IsEmpty(MaxHeap H)
{             //返回1栈空，否则返回0
    return H->size==0;
}

//3.最大堆的插入
void insert(MaxHeap H, DataType item)
{
    int i;
    if(Isfull(H)){
        printf("最大堆已满");
    }
    i=++H->size;              //i指向插入后堆中的最后一个元素的位置
    for(; H->Elements[i/2]<item;i/=2)
        H->Elements[i]=H->Elements[i/2];         //向下过滤结点
        H->Elements[i]=item;                  //将item插入
        printf("插入成功!");
}

//4.最大堆的删除
DataType DeleteMax(MaxHeap H)
{   //从最大堆H中取出键值为最大的元素，并删除一个节点
   int parent,child;
   DataType  Maxitem, temp;
   if(IsEmpty(H))
   {
       printf("最大堆为空\n");
       return 0;
   }
   Maxitem=H->Elements[1];       //取出根结点最大值
   //用最大堆H中最后一个元素从根结点开始向上过滤下层结点
   temp=H->Elements[H->size--];
   for(parent=1;parent*2<=H->size;parent=child)
   {
      child=parent*2;
      if((child!=H->size)&&(H->Elements[child]<H->Elements[child+1]))
          child++;             //child指向左右子结点的较大者
      if(temp>=H->Elements[child]) break;
      else   //移动temp元素到下一层
         H->Elements[parent]=H->Elements[child];
   }
   H->Elements[parent]=temp;
   return Maxitem;
}




       //1.初始化队列
int InitQueue(Queue *q)
{
    q->base=(Binren*)malloc(MAXQSIZE*sizeof(Binren));
    if(!q->base)
    {
        printf("存储空间分配失败!");
        return  ERROR;
    }
    q->front=q->rear=0;
    q->size=MAXQSIZE;
    return OK;
}


    //初始化总队列**
int zongQueue(Queue *q)
{
    q->base=(Binren*)malloc(zongsize*sizeof(Binren));
    if(!q->base)
    {
        printf("存储空间分配失败!");
        return  ERROR;
    }
    q->front=q->rear=0;
    q->size=zongsize;
    return OK;
}


     //输出所有病人信息**
void print(Queue *q)
{
    while(q)
    {
     if(q->rear==q->front&&q->front!=0)
     {
         printf("所有病人ID输出结束!");
         q->front=q->rear=0;
         break;
     }
     else
         if(q->rear==0)
         {
             printf("病人档案处没有病人信息!");
             break;
         }
         else
         {
             printf("病人的ID: %d\n",q->base[q->front]);
            ++q->front;
         }
    }
}


   //2.判断队列是否为空
int EmptyQueue(Queue *q)
{
    return(q->front==q->rear);
}

   //3.获得循环队列中元素
int GetHead(Queue *q)           //???
{     int n=0,m;
    if(q->front==0)
    {
      m=q->base[q->front].id;
      ++q->front;
      return m;
    }
  else
  {
      if(q->front%q->size==n)
      {
           q->front=0;
           return mid;
      }
      else
      {
          m=q->base[q->front].id;
          ++q->front;
          return m;
      }
  }


}


  //普通队列的元素插入
void  inQueue(Queue *q,int id)
{
    if(q->rear==zongsize-1)
    {
        printf("病人档案处已满,无法存储病人档案备份!\n");
        printf("请开辟新的病人档案处!\n");
    }
    else
    {   q->base[q->rear].id=id;
        ++q->rear;
    }
}



  //4.元素插入到循环队列队尾
int EnQueue(Queue *q,int id)
{
      //队列满
    if((q->rear+1)%q->size==q->front)
    {
            return mid;
    }
    else
    {
      q->base[q->rear].id=id;
      q->rear=(q->rear+1)%q->size;
      return OK;
    }
}



//根据优先级选择队列（进入）
  void MYEnQueue(Queue *q1,MaxHeap q2,Queue *zong,DataType d,int priority)      //**
{
    int  i;
    if(priority==1)
    {
       i=EnQueue(q1,d);
       if(i==0)
       printf("循环队列已满,病人无法排队就诊!");
       inQueue(zong,d);                         //**
    }
    else
    {
        insert(q2,d);
        inQueue(zong,d);                     //**
    }
}


//根据优先级选择队列（出）
DataType MYDeQueue(Queue *q1,MaxHeap q2)
{
    DataType e;
    if(!IsEmpty(q2))
        e=DeleteMax(q2);
    else
    {    if(!EmptyQueue(q1))
            e=GetHead(q1);
        else
            return ERROR;
    }
   return e;
}



void  ziwork( )
{
     int  b=1;
     int menu,w,a;                                 //存储用户选择的菜单编号
     int priority;                             //病人看病的优先级别
     jiedian node;
     Queue q1;                               //优先级低的病人序列
     stack q2;                               //优先级高的病人序列
     Queue zong;                             //总队列
     DataType id;                             //按照病人到达医院的先后给予编号
     DataType  e;                             //病人看病的优先级别
     zongQueue(&zong);                        //初始化总队列**
     w=InitQueue(&q1);
     a=createheap(&q2);
     id=10;
     printf("**************************************  欢迎进入医院排队候诊******************************************\n");
     printf("**************************************1. 新病人加入候诊队列        *************************************\n");
     printf("**************************************2. 医生根据优先级别为病人诊治*************************************\n");
     printf("**************************************3. 输出所有就诊病人的ID      *************************************\n");
   //  printf("**************************************4. 病人信息的存储            *************************************\n");
 //    printf("**************************************5. 病人信息的输出            *************************************\n");
     printf("**************************************6. 返回上一级目录            *************************************\n");
     printf("-------------------------------------------------------------------------------------\n");

     printf("*****************************请按菜单编号选择相应的操作（只处理数值型数据）:*************************\n");
     scanf("%d",&menu);
 tuichu:  while(menu)
    {
      switch(menu)
      {
         case 1:
               system("cls");
               printf("请输入病人的优先级别(系统只设两个优先级别：1或2):");
               scanf("%d",&priority);
              // printf("请输入病人的ID:\n");
              // scanf("%d",&id);
               if(priority==1||priority==2)                   //级别输入正确
               {
                   printf("*******该病人的ID为:%d****\n",id);
                   MYEnQueue(&q1,&q2,&zong,id++,priority);              //**
               }
               else
                   printf("\n请输入病人的优先级别(系统只提供两个优先级别:1或2)\n");
                break;

        case 2:                                      //有病人出院
                system("cls");
                e=MYDeQueue(&q1,&q2);
                if(e!=-1&&e!=0)                               //队列不为空
                    printf("*********************当前被诊治病人的ID为:%d*****\n",e);
                else
                {
                    if(e==-1)
                    printf("***************无病人，队列为空**********\n");
                    else
                    printf("循环队列中再无其他病人的ID!");
                }
               break;

        case 3:
            system("cls");
            print(&zong);
            break;

        case 4:
            system("cls");
                if(b==1)
                {
                       head.numroom=0;
                       head.cost=0;
                       wenjianfun(&head);
                }
               if(b!=1)
               {
                    wenjianfun(&node);
               }
               ++b;
               break;

        case 5:
                 //***
                printf("以下输出病人的详细信息:\n");
                nodetest(&head);
                break;
        case 6:
                menu=0;
                goto  tuichu;   break;

        default:     break;
      }

          printf("**************************************  欢迎进入医院排队候诊******************************************\n");
          printf("**************************************1. 新病人加入候诊队列        *************************************\n");
          printf("**************************************2. 医生根据优先级别为病人诊治*************************************\n");
          printf("**************************************3. 输出所有就诊病人的ID      *************************************\n");
         printf("**************************************4. 病人信息的存储            *************************************\n");
         printf("**************************************5. 病人信息的输出            *************************************\n");
          printf("**************************************6. 返回上一级目录            *************************************\n");
          printf("-------------------------------------------------------------------------------------\n");
          printf("*****************************请按菜单编号选择相应的操作（只处理数值型数据）:*************************\n");

          printf("\n请输入你的选择：");
          scanf("%d",&menu);

    }

        system("cls");
}




void  mainwork( )
{

     int menu;
     campus=initgraph();
     printf("**************************************                  欢迎进入医院系统程序                       ******************************************\n");
     printf("**************************************                 1.   医院地点介绍                           ******************************************\n");
     printf("**************************************                 2.   查看路线                               ******************************************\n");
     printf("**************************************                 3.   查询地点间最短路径                      *************************************\n");
     printf("**************************************                 4.   地点信息查询                            *************************************\n");
     printf("**************************************                 5.   更改图信息                              *************************************\n");
     printf("**************************************                 6.   查询两地间可行路径                      *************************************\n");
     printf("**************************************                 7.   打印邻接矩阵                            *************************************\n");
     printf("**************************************                 8.   医院排队候诊                            *************************************\n");
     printf("**************************************                 9.       退出                                *************************************\n");
     printf("********************************************************************************************************\n");
        while(1)
     {
        printf("-------------------------------------------------------------------------------------\n");
        printf("*****************************请按菜单编号选择相应的操作（只处理数值型数据）:*************************\n");
        scanf("%d",&menu);

      switch(menu)
      {

           case 1:    system("cls");    browsecompus(campus);        break;
        case 2:    system("cls");    shortestpath_dij(campus);    break;
        case 3:    system("cls");    shortestpath_floyd(campus);    break;
        case 4:    system("cls");    seeabout(campus);            break;
        case 5:    system("cls");    changegraph(&campus);        break;
        case 6:    system("cls");  allpath(campus);             break;
        case 7: system("cls");  printmatrix(campus);         break;
        case 8: system("cls");   ziwork( );                    break;
        case 9:
              system("cls");
              printf("错误，请按菜单编号输入\n");
              exit(0);
              break;

      }

     printf("**************************************                  欢迎进入医院系统程序                      ******************************************\n");
     printf("**************************************                 1.   医院地点介绍                          ******************************************\n");
     printf("**************************************                 2.   查看游览路线                            ******************************************\n");
     printf("**************************************                 3.   查询地点间最短路径                      *************************************\n");
     printf("**************************************                 4.   地点信息查询                            *************************************\n");
     printf("**************************************                 5.   更改图信息                              *************************************\n");
     printf("**************************************                 6.   查询两地间可行路径                      *************************************\n");
     printf("**************************************                 7.   打印邻接矩阵                            *************************************\n");
     printf("**************************************                 8.   医院排队候诊                            *************************************\n");
     printf("**************************************                 9.       退出                                *************************************\n");
     printf("********************************************************************************************************\n");

    }


}


int main()
{
    system("color 1f"); //屏幕颜色设定
    system("mode con: cols=140 lines=130");
    mainwork();
}
