#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#define OK 1
#define ERROR 0
#define SUCCESS 1
#define UNSUCCESS 0

#define MINSIZE 20 
#define MAXSIZE 20 
typedef int Status; 
typedef char TElemType;      //基本定义

//已订票客户的名单，带头结点双向链表实现 
typedef struct clientNodehaha
{
	char name[MAXSIZE];//姓名
	char ID_num[MAXSIZE];//证件号
	char flight_num[10];//航班号
	char time[MAXSIZE];//起飞时间
	int order_num;//订单号
	int amout;//订票数量
	int rank;//舱位等级 
	struct clientNodehaha *behind;
	struct clientNodehaha *head;
}clientList,*clientListL;
clientList *CLient;


//等待候补的客户名单，带头结点单链表 
typedef struct waitNode{
	char name[MAXSIZE];//姓名
	char ID_num[MAXSIZE];//证件号
	int amout;//订票数量

	//int rank;//舱位等级 
	struct waitNode *next;
}waitNode,*waitPtr;
waitNode *Q; 


//航班总信息链表，带头结点的单链表实现 
typedef struct Flight{
	char destination[MAXSIZE];//终点站 
	char flightId[MAXSIZE];//航班名 ，唯一 
	char planeId[MAXSIZE];//飞机号 
	char time[MAXSIZE];//起飞时间 
	float money;
	int num;//乘员余额 
	int tickets;//余票量
	clientListL CLientc;//已订票客户名单 
	waitPtr wqueue;//等候替补的客户名单 
	struct Flight *next;
}Flight,*flightList;
Flight *flight;

//生成随机数 
//初始化航班列表 
Status inItFlight(flightList &F){
	clientListL init_passengerList(clientListL &CLient);
	F = (Flight *)malloc(sizeof(Flight));
	if(NULL==F) return ERROR;
	strcpy(F->destination,"");//复制字符串 
	strcpy(F->flightId,"");
	strcpy(F->planeId,"");
	strcpy(F->time,"");
	F->money = 0.0;
	F->num=0;
	F->tickets=0;
	F->next=NULL;
	return OK;
}



//初始化乘客链表 
Status init_passengerList(clientListL &CLient){
	CLient=(clientList *)malloc(sizeof(clientList));//创建头结点
	if(NULL==CLient) return OVERFLOW ;
	CLient->behind=NULL;
	CLient->head=NULL;
	return OK;
}



//初始化候补乘客链表 
Status init_waitQueue(waitPtr &Q) {
	if(NULL==(Q=(waitNode*)malloc(sizeof(waitNode))))
	return ERROR;
	Q->next = NULL;
	strcpy(Q->name,"");
	strcpy(Q->ID_num,"");
	Q->amout = 0;
	return OK;
}



//创建航班结点
flightList creat_Flight(char *des,char *fid,char *pid,char *time,float money,int num,int tickets){
	flightList air;
	air = (Flight*)malloc(sizeof(Flight));
	if(NULL==air) return ERROR;
	strcpy(air->destination,des);
	strcpy(air->flightId,fid);
	strcpy(air->planeId,pid);
	strcpy(air->time,time);
	air->money = money;
	air->num = num;
	air->tickets = tickets;
	air->next = NULL;
	init_passengerList(air->CLientc); 
	init_waitQueue(air->wqueue);
	return air;
} 

//创建乘客结点 
clientListL creat_client(char *name,char *ID_num,char *flight_num,char *time,int order_num,int amout,int rank){
	clientListL client;
	client = (clientList*)malloc(sizeof(clientList));
	if(NULL!=client) {
		strcpy(client->name,name);
		strcpy(client->ID_num,ID_num);
		strcpy(client->flight_num,flight_num);
		strcpy(client->time,time);
	
		client->order_num = order_num;
		client->amout = amout;
		client->rank = rank;
		client->behind = NULL;
		client->head = NULL;
    }	
	return client;	
} 


//在航班总信息链表中插入新航班信息
Status insert_flight(Flight *&h, Flight *p){	
    Flight *f;
	f = h;
	if(NULL == f&&NULL == p) return ERROR;
	p->next = f->next;
	f->next = p;
	return OK;

} 



//在乘客链表中插入新结点 
Status insert_clientList(clientListL &totalList,clientListL &cp) {
	clientListL p;
	p = totalList->behind;
	if(cp==NULL) return ERROR;
	if(p==NULL) {
		totalList->behind = cp;
		cp->head = totalList;
	}
	else {
		while(p) {
			if(strcmp(p->name,cp->name)==1 ||strcmp(p->name,cp->name)==0) {
				if(p->head->head == NULL) {
					cp->head = totalList;
					cp->behind = p;
					totalList->behind = cp;
					p->head = cp;
					break;
				}
				else {
					cp->head = p->head;
					cp->behind = p;
					cp->head->behind = cp;
					p->head = cp;
					break; 
				}  
			}
			else{
				if(p->behind==NULL) {
					p->behind = cp;
					cp->head = p;
					break;
				}
			}
			p = p->behind;
		} 
	}
	return OK;
}


//创建候补乘客结点，并且将其插入链表尾部 
Status en_waitQueue(waitPtr &wqueue,char *n,int amount,char *ID_num){	
	waitNode *p;
	p=(waitNode *)malloc(sizeof(waitNode));
	if(NULL==p) return ERROR;
	strcpy(p->name,n);//名字 
	p->amout=amount;//订票数
	strcpy(p->ID_num,ID_num);
	p->next=NULL;
	waitNode *f;
	f = wqueue;
	if(NULL == f&&NULL == p) return ERROR;
	while (f->next != NULL)
	{
		f = f->next;//遍历找到尾节点 
	}
	f->next = p;
	return OK;

}


//求候补乘客人数 
int length_queue(waitPtr Q){
	//求队列深度
	int length = 0;
	waitNode *p = Q;
	while(p) {
		length++;

		p = p->next;
	}
	return length;

}


//删除航班链表结点 
int delete_flight(flightList &f,char *flightId){
	int flag = 0;
	flightList p,pr;
	p = f;
	pr = NULL;
	if(strcmp(flightId,"") == 0)return ERROR;
	while(p){
		if(strcmp(p->flightId,flightId) == 0){
			flag = 1;
			break;
		}
		pr = p;
		p = p->next;
	}
	if(flag == 1){
		pr->next = p->next;
		free(p);
	}
	
	return flag;
}



//删除乘客链表结点 
Status delete_clientList(clientListL &cl,clientListL &dp) {
	/* 删除航线总客户订单的指定订单，即双向链表的删除操作*/
	clientListL p;
	p = cl->behind;
	if(dp==NULL) return ERROR;
	if(p==dp) { //被删除结点为头节点的下一个结点 
		p = p->behind;
		cl->behind = p;
		p->head = cl;
		free(dp);
	}
	else {
		if(dp->behind!=NULL) {
			dp->behind->head=dp->head;
			dp->head->behind=dp->behind;
			free(dp); 
		}
		else{
			dp->head->behind = NULL;
			free(dp);
		}
	}
	return OK;	
}



/***下面为用户交互的函数***/ 
//查询航线 功能1 
void find(flightList air){
	void userView();
	//system("cls");//清屏代码 
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                 当前为 查询航线窗口                 *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	char destination[MAXSIZE];
	printf("请输入目的地：");
	scanf("%s",&destination);
	Flight *p;p = air->next;//从头结点后一结点开始查询
	Flight *k;k = air->next;
	int mark = 0;
	while(p){
		if(strcmp(destination,p->destination)==0){
			printf("有到达 %s 的航班\n",p->destination);
			mark = 1;
			break;
		}
		p = p->next;
	}//结束了对航班的遍历
	if(mark == 1){
		printf("%-20s%-10s%-22s%-26s%-12s%-15s%-8s\n","航班号","终点站","机型","起飞时间","票价","可乘坐旅客数","剩余票数\n");
		while(k){
			if(strcmp(destination,k->destination)==0){
				printf("%-20s%-10s%-22s%-25s%-17.2f%-15d%-8d\n",k->flightId,k->destination,k->planeId,k->time,k->money,k->num,k->tickets);
			}
			k = k->next;
		}//结束了对航班的遍历		
	}
	if(mark == 0) printf("没有去往 %s 的航班",destination);
	printf("\n输入1继续查询，输入2返回用户主页面");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("无效输入，请重输");
		scanf("%s",&l);
	}
	if(l == '1') find(air); 
	if(l == '2') userView();
}

//订票函数  
int booking(clientList *&airCLient,int amount,int sum,int order_num,char *name,char *ID_num,char *flightId,char *time){//把乘客的结点生成并接入乘客链表+接入航班结点里的乘客链表 

	clientListL pessage =  creat_client(name,ID_num,flightId,time,order_num,amount,sum);
		if(insert_clientList(airCLient,pessage) == OK){
		printf("购票成功");return OK;
    }
    else {
	//system("cls");
		printf("购票失败，钱款已退回，请联系工作人员购票");}
    }
		

//推荐路线函数		
void recommand(Flight *air,clientList *CLient,char *flightId,char *destination,int amount)
{
//根据目的地相同，航班号不同，推荐新的航班(有票时)//价格重新计算(机票数不变，舱位不变),也要生成订单号 
	int randx(); 
	flightList p;
	char name[MAXSIZE];//姓名
	char ID_num[MAXSIZE];
	int order_num;//订单号
	p = air->next;
	int mark = 0;
	if(NULL== p||NULL==air) {
		printf("没有航班信息");
		return;
	}
	while(p)
	{
	 if(strcmp(destination,p->destination) == 0&&strcmp(flightId,p->flightId) !=0&&amount<=p->tickets&&p->tickets!=0)//找到了合适的机票,购买同样的机票
		{
		  printf("请输入你的真实姓名：");
		  scanf("%s",&name);
		  printf("请输入你的手机号码：");
		  scanf("%s",&ID_num);
		  int rankx[amount];int g[amount];int sum;float money;//储存舱位拼接后的结果 		 	
		  for(int j=0;j<amount;j++)//将每个票的舱位拼接 
		   {
				printf("请输入第%d张票的舱位等级",j+1);
				scanf("%d",&rankx[j]);
				float m = p->money;	
			//	scanf("%s",&rankx[j])
				//float m = p->money;
				printf("该票为%d等票,票价为%8.2f\n",rankx[j],m*(3.0/rankx[j]));
				money += m*(3.0/rankx[j]);//票价总和 
				g[j] = rankx[j]*pow(10,amount-j-1);
				sum+=g[j];
				
			}
			printf("您需要支付%8.2f元\n",money);
			getch();	
			int d = randx();order_num =  d*10+d/2;//对订单号做简单的运算
		    if(OK == booking(p->CLientc,amount,sum,order_num,name,ID_num,p->flightId,p->time))//amout,
			{printf("你新的航班号是:%s,起飞时间为：%s,订单号为%d",p->flightId,p->time,order_num);
			p->tickets = p->tickets-amount;mark = 1;}break;
	    }
	    p = p->next;
	}
	if(mark == 0) printf("没有找到合适航班信息！！！"); 
}



//加入候补队列函数 ; 
int wiat(waitPtr &wqueue,int amount){
	// 	char name[MAXSIZE];//姓名char ID_num[MAXSIZE];//证件号int amout;//订票数量int rank;//舱位等级 ,char *n,int amount,char *ID_num,int rank
	char name[MAXSIZE];
	char ID_num[MAXSIZE];
	printf("请输入你的名字：");
	scanf("%s",&name);
	printf("请输入你的手机号码：");
	scanf("%s",&ID_num);
	if(OK == en_waitQueue(wqueue,name,amount,ID_num)) {
		//system("cls");
		printf("\t\t\t\t*******************************************************\n");
		printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
		printf("\t\t\t\t*                你已经成功加入候补名单               *\n");
		printf("\t\t\t\t*               如果您满足条件，管理员将联系您        *\n");
		printf("\t\t\t\t*                 ——————————                *\n"); 
		printf("\t\t\t\t*******************************************************\n");
	}
	else printf("加入失败"); 
} 
	

		
//订票引导函数，引用了订票函数，推荐路线函数，加入候补队列函数  用户功能2 
int bookTickets(flightList &air){
	int randx();
	//system("cls");//清屏代码 
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                   当前为 订票窗口                   *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	void userView();
	Flight *p;p = air->next;//从头结点后一结点开始查询
	Flight *k;k = air->next; 
	char flightId[MAXSIZE];//航班号 
	char flightId1[MAXSIZE];
	char destination[MAXSIZE];//目的地 
	int amount;char i;
	int flag = 0;
	char name[MAXSIZE];//姓名
	char ID_num[MAXSIZE];
	int order_num;int mark = 0;//订单号 
	int markj = 0;
	printf("你可以输入你的目的地(按1)或者航班号(按2)来查询：");
	scanf("%s",&i);
	while(i!='1'&&i!='2'){
		printf("无效输入，请重输："); 
		scanf("%s",&i);
	}
	if(i=='1'){ 
		printf("请输入目的地：");
		scanf("%s",&destination);
		printf("按任意键后输入票数，系统将为你返回查询信息\n");
		getch();
		printf("请输入要购买的票数：");
		scanf("%d",&amount);
		while(p){
		//&&amount<=p->tickets&&p->tickets!=0 
		if(strcmp(destination,p->destination)==0) flag = 1;
		if(strcmp(destination,p->destination)==0&&amount<=p->tickets&&p->tickets!=0){
			//if(amount<=p->tickets&&p->tickets!=0){
			
			if(strcmp(destination,p->destination)==0) markj = 1;//有到达这个地点的航班 
			
			int rankx[amount];int g[amount];int sum=0;float money = 0.0;//储存舱位拼接后的结果 

				printf("请输入你的真实姓名：");
				scanf("%s",&name);
				printf("请输入你的手机号码：");
				scanf("%s",&ID_num);

				printf("请分别输入你需要的舱位等级：\n");
				for(int j=0;j<amount;j++)//将每个票的舱位拼接 
					{printf("请输入第%d张票的舱位等级\n",j+1);
					 scanf("%d",&rankx[j]);
					 float m = p->money;
					 printf("该票为%d等票,票价为%8.2f\n",rankx[j],m*(3.0/rankx[j]));
					 money += m*(3.0/rankx[j]);//票价总和 
					 g[j] = rankx[j]*pow(10,amount-j-1);
	
					 sum+=g[j];
		
					}
				printf("您需要支付%8.2f元\n",money);
				getch();	
				int d = randx();order_num =  d*10+d/2;//对订单号做简单的运算

				if(OK == booking(p->CLientc,amount,sum,order_num,name,ID_num,p->flightId,p->time))
				
				 {
					printf("\n你的航班号是：%s,你的起飞时间为：%s,订单号为%d",p->flightId,p->time,order_num);
				p->tickets = p->tickets-amount;mark = 1;

				}
		
				break;
			}
			if(strcmp(destination,p->destination)==0)
			{
			strcpy(flightId1,p->flightId);
		}
			p = p->next;
		
		}//结束了对航班的遍历
		//printf("%d,flag是",flag);
		if(mark == 0&&flag == 1) {
			//这里flag == 1 ,表明航班链表里面有这个航班 
				printf("我们已经遍历了所有到达 %s 的航班，它们的余票都不满足你的需求！",destination);
				printf("\n请问你想加入到达 %s 的航班 %s 的候补名单吗（?1/2）",destination,flightId1);
		char o;
		printf("\n请输入：");
		scanf("%s",&o);
		while(o!='1'&&o!='2'){
		printf("无效输入，请重输：");
		scanf("%s",&o);
					}

		if(o == '1') {
			while(k){
		if(strcmp(flightId1,k->flightId)==0)
		{
		wiat(k->wqueue,amount) ;break;}
		k = k->next;}
			
			
		}
				//int wiat(waitQueue &wqueue,char *n,int amount,char *ID_num,int rank)
		 if(o == '2' ){
		userView();
				}
		
		}
	
		}  
	 
	if(i=='2'){//根据航班号得到目的地 
		printf("请输入航班号：");
		scanf("%s",&flightId);
		printf("按任意键后输入票数，系统将为你返回查询信息\n");
		getch();
		printf("请输入要购买的票数：");
		scanf("%d",&amount);
		while(p){
		if(strcmp(flightId,p->flightId)==0){
			flag = 1;
			if(p->tickets>=amount)
			{
			int rankx[amount];int g[amount];int sum = 0;float money = 0.0;//储存舱位拼接后的结果
				printf("请输入你的真实姓名：");
				scanf("%s",&name);
				printf("请输入你的手机号码：");
				scanf("%s",&ID_num);

				printf("请分别输入你的需要的舱位等级：");
				for(int j=0;j<amount;j++)//将每个票的舱位拼接 
					{printf("请输入第%d张票的舱位等级\n",j+1);
					 scanf("%d",&rankx[j]);
					 float m = p->money;
					 printf("该票为%d等票,票价为%8.2f\n",rankx[j],m*(3.0/rankx[j]));
					 money += m*(3.0/rankx[j]);//票价总和 
					 g[j] = rankx[j]*pow(10,amount-j-1);
					 sum+=g[j];
					}
				printf("您需要支付%8.2f元",money);
				getch();	
				int d = randx();order_num =  d*10+d/2;//对订单号做简单的运算
				if(OK == booking(p->CLientc,amount,sum,order_num,name,ID_num,p->flightId,p->time)){
				printf("\n你的起飞时间为：%s,订单号为%d",p->time,order_num);
				p->tickets = p->tickets-amount;}
			}else if(p->tickets==0)
			{printf("\n该航班已满员，请问是否需要推荐到达 %s 的其他航线?(y/n)\n",p->destination);char f;
			//recommend(air,flightId,destination,amount);
			printf("请输入：");
			scanf("%s",&f);
			while(f!='y'&&f!='n'){
				printf("无效输入，请重输：");
				scanf("%s",&f);
			}
			if(f == 'y') recommand(air,CLient,flightId,p->destination,amount);
			if(f == 'n') {
				printf("请问你想加入航班 %s 的候补队列吗(?1/2)",flightId);char t;
				printf("请输入：");
				scanf("%s",&t);
				while(t!='1'&&t!='2'){
					printf("无效输入，请重输：");
					scanf("%s",&t);
					}
				if(t == '1') wiat(p->wqueue,amount) ;
				//int wiat(waitQueue &wqueue,char *n,int amount,char *ID_num,int rank)
				if(t == '2' ){
				userView();//break;
				}
		}
			}else if(p->tickets!=0&&p->tickets<amount){
			printf("抱歉，余票仅剩 %d ,是否推荐到达 %s 的其他航线?(?y/n)",p->tickets,p->destination);char f;
			printf("请输入：");
			scanf("%s",&f);
			while(f!='y'&&f!='n'){
				printf("无效输入，请重输：");
				scanf("%s",&f);}
			if(f == 'y') recommand(air,CLient,p->flightId,p->destination,amount);
			if(f == 'n') {
				printf("请问你想加入航班 %s 的候补队列吗(?1/2)",flightId);char t;
				printf("请输入：");
				scanf("%s",&t);
				while(t!='1'&&t!='2'){
					printf("无效输入，请重输：");
					scanf("%s",&t);
					}
				if(t == '1') wiat(p->wqueue,amount) ; 
				if(t == '2' ){
				userView();break;
				}
		}
			}
		break;
		}
		p = p->next;}  
	}
	if(flag==0){printf("\n查询不到该航班！请返回确认\n");
	}
	printf("\n输入1继续购票，输入2返回用户主页面");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("无效输入，请重输");
		scanf("%s",&l);
		}
	if(l == '1') bookTickets(flight);
	if(l == '2') userView();
	 
	  
	 } 
	 
	 

//显示所有航班信息 用户功能3 
void displayAllInfo(Flight *F)
{	
	//system("cls");//清屏代码 
	void userView();
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                 以下为所有航班信息                  *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	Flight *p=F;
	int flags = 0;
   printf("%-20s%-10s%-22s%-26s%-12s%-15s%-8s\n","航班号","终点站","机型","起飞时间","票价","可乘坐旅客数","剩余票数\n");

	p = p->next;

	for(;p!=NULL;p=p->next)
	{
	printf("%-20s%-10s%-22s%-25s%-17.2f%-15d%-8d\n",p->flightId,p->destination,p->planeId,p->time,p->money,p->num,p->tickets);

	flags = 1;
			
	}
	if(flags ==0) printf("\t\t\t\t抱歉没有航班信息！！！");
	printf("\n输入1可返回用户主页面");
	char l;
	scanf("%s",&l);
	while(l!='1'){
		printf("无效输入，请重输");
		scanf("%s",&l);
		}
	if(l == '1') userView(); 

}
//显示所有航班信息 管理员功能5 
void displayAllInfo1(Flight *F)
{	
	//system("cls");//清屏代码 
	void adminhome();
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                 以下为所有航班信息                  *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	Flight *p=F;
	int flags = 0;
   printf("%-20s%-10s%-22s%-26s%-12s%-15s%-8s\n","航班号","终点站","机型","起飞时间","票价","可乘坐旅客数","剩余票数\n");

	p = p->next;

	for(;p!=NULL;p=p->next)
	{
	printf("%-20s%-10s%-22s%-25s%-17.2f%-15d%-8d\n",p->flightId,p->destination,p->planeId,p->time,p->money,p->num,p->tickets);

	flags = 1;
			
	}
	if(flags ==0) printf("\t\t\t\t抱歉没有航班信息！！！");
	printf("\n输入1可返回管理员主页面");
	char l;
	scanf("%s",&l);
	while(l!='1'){
		printf("无效输入，请重输");
		scanf("%s",&l);
		}
	if(l == '1') adminhome(); 

}


//查询订单 对应用户功能4 
void finddingdan(flightList air){
	void userView();
	//system("cls");//清屏代码 
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                 当前为 查询订单窗口                 *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	char flightId[MAXSIZE];
	char ID_num[MAXSIZE];
	printf("请输入航班号：");
	scanf("%s",&flightId);
	Flight *p;p = air->next;//从头结点后一结点开始查询
	Flight *k;k = air->next;
	int mark = 0;int q = 0;
	while(p){
		if(strcmp(flightId,p->flightId)==0){
			q = 1;
			printf("\n请输入你的名字：");
			scanf("%s",&ID_num);
			clientListL k = p->CLientc->behind;
			if(k==NULL)printf("该航班订单为空，查询不到结果");
			else{
			
			system("cls");//清屏代码 
			printf("%-20s%-22s%-22s%-26s%-12s\n","客户名字","订单号","手机号","起飞时间","票数\n");
			
			
			
			while(k){
				if(strcmp(ID_num,k->name)==0){
					mark = 1;
				printf("%-20s%-22d%-22s%-25s%-8d\n",k->name,k->order_num,k->ID_num,k->time,k->amout);
				}
				k = k->behind;
			}
			if(mark == 0) printf("该航班没有您的订单");
			
}
		break;	}
		
			p = p->next;
		
		}//结束了对航班的遍历
	if(q == 0) printf("不存在航班 %s ",flightId);
	printf("\n输入1继续查询，输入2返回用户页面");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("无效输入，请重输");
		scanf("%s",&l);
		}
	if(l == '1') finddingdan(air);
	if(l == '2') userView();
}



/***管理员交互函数***/ 
//增加航线  管理员功能1 
void addFlight(flightList &air){
	int randx();
	void adminhome();
	//system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
	printf("\t\t\t\t*            ———————————————           *\n");
	printf("\t\t\t\t*           | ！！高级权限，请谨慎操作！！|           *\n");
	printf("\t\t\t\t*            ———————————————           *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	char destination[MAXSIZE];
	char flightId[MAXSIZE];
	char planeId[MAXSIZE];
	char time[MAXSIZE];
	float money;
	int num;
	int tickets;char mark = '1';
	while(mark == '1'){
	printf("请输入终点站名：");
	scanf("%s",destination);
	printf("请输入航班号：");
	scanf("%s",flightId);
	printf("请输入飞机号：");
	scanf("%s",planeId);
	printf("请输入起飞时间(格式为cccc-ww-jj-hh:aa):");
	scanf("%s",time);
	printf("票价(精确到小数点后两位)：");
	scanf("%f",&money);
	printf("请输入乘员定额：");
	scanf("%d",&num);
	printf("请输入余票数量：");
	scanf("%d",&tickets);
	int ranxe;
	int ranx = randx();//得到随机数
	system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
	printf("\t\t\t\t*                   ———————                    *\n");
	printf("\t\t\t\t*                  | 请输入验证码 |                   *\n");
	printf("\t\t\t\t*                   ———————                    *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("验证码为：%d\n",ranx); 
	printf("在此处输入：");
	scanf("%d",&ranxe);
	while(ranx != ranxe)
	{
	 printf("验证码不正确！！！\n");
	 printf("请再次输入：");
	 scanf("%d",&ranxe);
	 printf("你输入的验证码是%d",ranxe);
	}
	
	flightList newAir = creat_Flight(destination,flightId,planeId,time,money,num,tickets);

	if(insert_flight(air,newAir) == OK){
	//system("cls");
	printf("添加航班成功");}
	
	printf("\n输入1继续录入，输入2返回管理员页面");
	printf("\n请输入：");
	scanf("%s",&mark);
	while(mark!='1'&&mark!='2'){
		printf("无效输入，请重输：");
		scanf("%s",&mark); 
	}
	
	}
	if(mark == '2') 
	adminhome();
}



//删除航线  功能2 
void deleflight(flightList &air){
	void adminhome();
	//system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
	printf("\t\t\t\t*            ———————————————           *\n");
	printf("\t\t\t\t*           | ！！高级权限，请谨慎操作！！|           *\n");
	printf("\t\t\t\t*            ———————————————           *\n");
	printf("\t\t\t\t*                 当前为删除航班窗口                  *\n");
	printf("\t\t\t\t*******************************************************\n");

	char flightId[MAXSIZE];
	printf("请输入你要删除的航班号：");
	scanf("%s",flightId);
	if(delete_flight(air,flightId) == 1){
		printf("\n删除成功！");
	}else{
		printf("\n删除失败！请输入系统存在的航班号");
		
	}
	printf("删除航班成功，输入1继续删除，输入2返回管理员页面");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("无效输入，请重输");
		scanf("%s",&l);
		}
	if(l == '1') deleflight(flight); 
	if(l == '2') adminhome();
	
}



//显示指定航线上的客户订单 功能3 
void displayClientInfo(flightList air){
	void adminhome();
	//system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
	printf("\t\t\t\t*            ———————————————           *\n");
	printf("\t\t\t\t*           | ！！高级权限，请谨慎操作！！|           *\n");
	printf("\t\t\t\t*            ———————————————           *\n");
	printf("\t\t\t\t*             当前为查看航线所有订单的窗口            *\n");
	printf("\t\t\t\t*******************************************************\n");
	int flag = 0;
	char flightId[MAXSIZE];
	printf("\n请输入航班号：");
	scanf("%s",flightId);
	printf("%s",flightId);
	flightList p = air->next;
	if(p == NULL)printf("没有航班信息");
	else{
	while(p){//找该航班信息
		if(strcmp(flightId,p->flightId) == 0){
			flag = 1;
			break;
		}p = p->next;
	}
	if(flag == 1){
		clientListL cp = p->CLientc->behind;
		if(cp == NULL){
			printf("\n该航班客户订单为空\n");
		}
		else {printf("下面为航班：%s 的所有客户名单    \n",flightId);
		printf("%-20s%-22s%-22s%-26s%-12s\n","客户名字","订单号","手机号","起飞时间","票数\n");} 
		
		while(cp){
			
		printf("%-20s%-22d%-22s%-29s%-8d\n",cp->name,cp->order_num,cp->ID_num,cp->time,cp->amout);
		cp = cp->behind;	
			
		}
	}
	else {
		printf("找不到该航班信息，请输入正确的航班号");}
	
}
	printf("输入1继续查看，输入2返回管理员页面");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("无效输入，请重输");
		scanf("%s",&l);
		}
	if(l == '1') displayClientInfo(flight); 
	if(l == '2') adminhome();
	
}



//查看指定航班的候补人员 功能4 
void displaywaitClientInfo(flightList air){
	void adminhome();
	//system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
	printf("\t\t\t\t*            ———————————————           *\n");
	printf("\t\t\t\t*           | ！！高级权限，请谨慎操作！！|           *\n");
	printf("\t\t\t\t*            ———————————————           *\n");
	printf("\t\t\t\t*             当前为查看航线候补乘客的窗口            *\n");
	printf("\t\t\t\t*******************************************************\n");
	int flag = 0;
	char flightId[MAXSIZE];
	printf("\n请输入航班号：");
	scanf("%s",flightId);
	flightList p = air->next;
	if(p == NULL)printf("没有航班信息");//一个航班都没有 
	else{
	while(p){//找该航班信息
		if(strcmp(flightId,p->flightId) == 0){
			flag = 1;
			break;
		}p = p->next;
	}
	if(flag == 1){
		waitPtr cp = p->wqueue;
		if(cp->next == NULL)
		//if(NULL == cp.rear)
		{
			printf("\n该航班候补客户名单为空\n");
		}
		else {
		cp = cp->next;
		printf("下面为航班：%s 的候补乘客数    \n",flightId);
		int length = length_queue(cp);
		printf("%d",length);
		
		
		printf("\n%-20s%-22s%-22s\n","客户名字","手机号","需要的票数\n");} 

		while(cp){
			
		printf("%-20s%-22s%-22d\n",cp->name,cp->ID_num,cp->amout);
		cp = cp->next;	
			
		}
		
		} 	
	else {
		printf("找不到该航班信息，请输入正确的航班号");}
		
}
	printf("输入1继续查看，输入2返回管理员页面：");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("无效输入，请重输");
		scanf("%s",&l);
		}
	if(l == '1') displaywaitClientInfo(flight); 
	if(l == '2') adminhome();}

 


//退票时处理，候补队列函数 
void show(flightList &air,waitNode *&Q)
{	
	int randx();
	int order_num; 
	waitNode *g;//指向该结点
	waitNode *f;//头 
	waitNode *r;//尾 
	waitNode *p;
	waitNode *d1;
	f = Q;//f指向头结点 
	g = f->next;
	

	int shijinum = 0;//符合条件的候补乘客的新订票数 
	if (Q->next == NULL) printf("候补乘客队列为空!\n");
	else{
	while (g != NULL)//循环查找，询问合适的用户 
	{   
		printf("\n现在在检索乘客  %s",g->name);
		printf("...请稍后...");
		
		if(air->tickets>=g->amout){
		d1 = Q;//余票数满足该候补乘客的要求 
			printf("\n该候补乘客满足条件！\n");
			printf("\n他的名字是 %s ，他的手机号码是 %s , 他的订票数是 %d \n",g->name,g->ID_num,g->amout);
			printf("\n请与他进行联系！！！(他的订票数可以在余票范围内进行更改)\n");
			printf("\t\t\t****************\n");
			printf("\t\t\t*  余票为:%d   *\n",air->tickets);
			printf("\t\t\t****************\n");
			printf("\n请询问其新的票数需求，和舱位需求");
			printf("\n他是否接受此次订票请求?(y/n)");
			char h;
			scanf("%s",&h);
		while(h!='y'&&h!='n'){
				printf("无效输入，请重输");
				scanf("%s",&h);
			} 
		
			if(h == 'y'){//该候补用户同意进行订票处理 
				//
				
				printf("请输入他的订票数：");
				scanf("%d",&shijinum);
				
				
				int rankx[shijinum];int g1[shijinum];int sum = 0;float money = 0.0;//储存舱位拼接后的结果
				
				
				printf("请分别输入客户需要的舱位等级：\n");
				
				
				for(int j=0;j<shijinum;j++)//将每个票的舱位拼接 
					{printf("请输入第%d张票的舱位等级\n",j+1);
					 scanf("%d",&rankx[j]);
					 float m = air->money;
					 printf("该票为%d等票,票价为%8.2f\n",rankx[j],m*(3.0/rankx[j]));
					 money += m*(3.0/rankx[j]);//票价总和 
					 g1[j] = rankx[j]*pow(10,shijinum-j-1);
					 sum+=g1[j];
					}
				printf("总费用为%8.2f元\n",money);
				getch();
				int d = randx();order_num =  d*10+d/2;//对订单号做简单的运算

				if(OK == booking(air->CLientc,shijinum,sum,order_num,g->name,g->ID_num,air->flightId,air->time)){
				printf("\n该乘客的起飞时间为：%s,订单号为%d\n",air->time,order_num);
				air->tickets = air->tickets - shijinum;//总票数变化 
				}//订票操作*/
				printf("\n!!!操作成功！！！\n");
				printf("订单号和所需费用已经发送到客户手机 %s 中！！！",g->ID_num);

				while(d1){
					if(d1->next == g){
						d1->next = g->next;
					}
					d1 = d1->next;
				}
				printf("输入1返回主页面，输入2返回管理员页面");
				char t;
				printf("请输入：");
				scanf("%s",&t);
				while(t!='1'&&t!='2'){
					printf("无效输入，请重新输入");
					scanf("%s",&t);
				
				}
				void home();
				if(t == '1') home();
				void adminhome(); 
				if(t == '2')  adminhome();

		break;					
		}
		if(h=='n'){
			printf("\n正在检索下一个候补乘客！！！");
			
		}
		
			
		
		
			}
		
		g = g->next;
		}//while到这里结束 
}

}




//退票 功能6 
int refund(flightList &air){
	void adminhome();
	//system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*               欢迎使用THIRTEEN航空系统              *\n");
	printf("\t\t\t\t*            ———————————————           *\n");
	printf("\t\t\t\t*           | ！！高级权限，请谨慎操作！！|           *\n");
	printf("\t\t\t\t*            ———————————————           *\n");
	printf("\t\t\t\t*                  当前为退票窗口                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	char flightId[MAXSIZE];
	int am;
	char name[MAXSIZE];
	printf("请输入你的名字：");
	scanf("%s",name);
	printf("请输入航班号：");
	scanf("%s",flightId);
	printf("请输入你要退订的票数：");
	scanf("%d",&am);
	flightList p = air->next;//从头结点的下一个结点开始 
	int flag = 0;
	clientListL totaList;
	clientListL totaList1;
	while(p){
		if(strcmp(p->flightId,flightId) == 0){//找到该航班结点 
			totaList = p->CLientc;//从该头结点的下一位开始
			totaList1 = p->CLientc->behind; 
		while(totaList){
			if(strcmp(totaList->name,name) == 0){//找到了该乘客结点 
				
				if(am<totaList->amout){
					totaList->amout = totaList->amout-am;//只是修改乘客结点的票数 
					p->tickets = p->tickets+am;//票数变化
					printf("\n退票成功！退款金额已经成功原路返回您的账号\n");
					show(p,p->wqueue);
				}
				else if(am == totaList->amout){//全部退票，要删除整一个结点 
					if(OK==delete_clientList(totaList1,totaList)) 
					{totaList->amout = totaList->amout-am;
					p->tickets = p->tickets+am;//票数变化
					printf("\n退票成功！退款金额已经成功原路返回您的账号\n");
					printf("现在票数为%d",p->tickets);
					show(p,p->wqueue);} 
				}
				else printf("你购买的票数没有这么多，请重新确认");
				flag = 1;
				break;
				}
			totaList = totaList->behind;
				
			}
			
		break;
		}
		p = p->next;
	}
	if(flag == 0){
		printf("找不到该订单，退票失败");
	
	}
	printf("\n输入1继续操作退票，输入2返回管理员页面：");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("无效输入，请重输");
		scanf("%s",&l);
		}
	if(l == '1') refund(flight); 
	if(l == '2') adminhome();
	
	return flag;
	
}
//普通用户登录 
void userhome(){
	void mima1(int &tags1);
	//system("cls");
	char key1[10];
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                欢迎使用THIRTEEN航空系统             *\n");
	printf("\t\t\t\t*                 ——————————                *\n");
	printf("\t\t\t\t*                | 当前身份:普通用户 |                *\n");
	printf("\t\t\t\t*                 ——————————                *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("\n");

	int tags1 = 1;
	mima1(tags1);
}



//密码
char root_key1[]="123456";
//密码函数 
void mima1(int &tags1){
	void home();
	void mixmima();
	char i;
	char key1[10];
	void userView();
	printf("按1后可输入密码，按2返回主页面:"); 
	scanf("%s",&i);
	while(i!='1'&&i!='2'){
		printf("无效输入，请重输：");
		scanf("%s",&i);
	}
	if(i=='1'){
		printf("第%d次输入密码:",tags1);
		scanf("%s",&key1);
		if (strcmp(key1, root_key1) == 0) userView();
	else{
		printf("密码错误\n");
				if(tags1>2) mixmima();//tags = 3,出现提示 
		else{++tags1;mima1(tags1);};} 
	
	}
	if(i=='2')  home();//回到主页面 
}

//普通用户界面 

void userView(){
	int i; 
	//system("cls");
	void home();
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              欢迎使用THIRTEEN航空系统               *\n");
	printf("\t\t\t\t*                 ——————————                *\n");
	printf("\t\t\t\t*                | 当前身份:普通用户 |                *\n");
	printf("\t\t\t\t*                 ——————————                *\n");
	printf("\t\t\t\t*     请选择所需业务：                                *\n");
	printf("\t\t\t\t*                   1.查询航线                        *\n");
	printf("\t\t\t\t*                   2.订购机票                        *\n");
	printf("\t\t\t\t*                   3.查看所有航班信息                *\n");
	printf("\t\t\t\t*                   4.查询订单                        *\n");
	printf("\t\t\t\t*                   5.返回主页面                      *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("请选择你的操作：");
	scanf("%d",&i);
	while(i!=1&&i!=2&&i!=3&&i!=4&&i!=5){
		printf("无效输入，请重输："); 
		scanf("%d",&i);
	}
	switch(i){
		case 1: find(flight);break;
		case 2: bookTickets(flight);break;
		case 3: displayAllInfo(flight);break;
		case 4: finddingdan(flight);break;
		case 5: home(); 
		default: printf("运行错误!\n");getchar();	}
} 




//管理员界面 
void adminhome(){
	//system("cls");
	char i;
	void home();
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                欢迎使用THIRTEEN航空系统             *\n");
	printf("\t\t\t\t*                 ——————————                *\n");
	printf("\t\t\t\t*                |  当前身份:管理员  |                *\n");
	printf("\t\t\t\t*                 ——————————                *\n");
	printf("\t\t\t\t*    请选择所需业务：                                 *\n");
	printf("\t\t\t\t*                  1.增加航线                         *\n");
	printf("\t\t\t\t*                  2.删除航线                         *\n");
	printf("\t\t\t\t*                  3.查看航班的客户订单               *\n");
	printf("\t\t\t\t*                  4.查看航班候补客户订单             *\n");
	printf("\t\t\t\t*                  5.查看所有航班                     *\n");
	printf("\t\t\t\t*                  6.退票                             *\n");
	printf("\t\t\t\t*                  7.返回主页面                       *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("请选择你的操作：");
	scanf("%s",&i);
	while(i!='1'&&i!='2'&&i!='3'&&i!='4'&&i!='5'&&i!='6'&&i!='7'){
		printf("无效输入，请重输："); 
		scanf("%s",&i);
	}
	switch(i){
		case '1': addFlight(flight);break;
		case '2': deleflight(flight);break;
		case '3': displayClientInfo(flight);break;
		case '4': displaywaitClientInfo(flight);break;
		case '5': displayAllInfo1(flight);break;
		case '6': refund(flight);break;
		case '7': home();break; 
		default: printf("运行错误!\n");getchar();
	}
	
}



//管理员密码界面 
void adminView(){
	void mima(int &tags);
	//system("cls");
	char key[10];
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                欢迎使用THIRTEEN航空系统             *\n");
	printf("\t\t\t\t*                 ——————————                *\n");
	printf("\t\t\t\t*                |  当前身份:管理员  |                *\n");
	printf("\t\t\t\t*                 ——————————                *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("\n");
	int tags = 1;
	mima(tags);
}
//char root_key[]={'a','d','m','i','n'};
//密码
char root_key[]="admin";
//密码函数 
void mima(int &tags){
	void home();
	void mixmima();
	char i;
	char key[10];
	void adminhome();
	printf("按1后可输入密码，按2返回主页面:"); 
	scanf("%s",&i);
	while(i!='1'&&i!='2'){
		printf("无效输入，请重输：");
		scanf("%s",&i);
	}
	if(i=='1'){
		printf("第%d次输入密码:",tags);
		scanf("%s",&key);
		if (strcmp(key, root_key) == 0) adminhome();
	else{
		printf("密码错误\n");
				if(tags>2) mixmima();//tags = 3,出现提示 
		else{++tags;mima(tags);};} 
	
	}
	if(i=='2')  home();//回到主页面 
}






//三次密码错误后界面 
void mixmima(){
	//system("cls");   
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*      !                                       !      *\n");
	printf("\t\t\t\t*     !!!                                     !!!     *\n");
	printf("\t\t\t\t*     !!!       您已经连续输错3次密码！       !!!     *\n");
	printf("\t\t\t\t*     !!!  请退出系统重登，或者联系技术人员   !!!     *\n");
	printf("\t\t\t\t*     !!!           更改密码                  !!!     *\n");
	printf("\t\t\t\t*      !                                       !      *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*      !                                       !      *\n");
	printf("\t\t\t\t*     !!!                                     !!!     *\n");
	printf("\t\t\t\t*******************************************************\n");
}



//主页面 
void home(){
	//system("cls");//清屏代码 
	char i;
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*               欢迎进入THIRTEEN航空系统              *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                   请选择登录身份                    *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*               用户输入1， 管理员请输入2             *\n");
	printf("\t\t\t\t*                  退出系统请输入3                    *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("请输入:");
	scanf("%s",&i);
	while(i!='1'&&i!='2'&&i!='3'){
		printf("无效输入，请重输："); 
		scanf("%s",&i);
	}
	switch(i){
		case '1': userhome();break;
		case '2': adminView();break;
		case '3': exit(0);break;
		default: printf("运行错误!\n");getchar();
	}			
}

 
//返回随机数，模拟验证码 
int randx(){
	srand((unsigned) (time(NULL)));
	int d = rand();
	return d;
}


//creat_Flight(char *des,char *fid,char *pid,char *time,float money,int num,int tickets)
Status makenode(flightList &flight){
	char des1[MAXSIZE] = "上海";char des2[MAXSIZE] = "重庆";
	char des3[MAXSIZE] = "杭州";char des4[MAXSIZE] = "成都";
	char fid1[MAXSIZE] = "A1001";char fid2[MAXSIZE] = "A1002";
	char fid3[MAXSIZE] = "A1003";char fid4[MAXSIZE] = "A1004";
	char pid1[MAXSIZE] = "B111";char pid2[MAXSIZE] = "B222"; 
	char pid3[MAXSIZE] = "F333";char pid4[MAXSIZE] = "E444";
	char time1[MAXSIZE] = "2021-01-10-21:00";char time2[MAXSIZE] = "2022-01-10-23:00";
	char time3[MAXSIZE] = "2021-01-12-23:00";char time4[MAXSIZE] = "2022-01-31-12:00";
	float money1 = 500.00; float money2 = 700.00;
	float money3 = 300.00; float money4 = 600.00;
	int num1 = 50;int num2 = 40;int num3 = 100;int num4 = 80;
	int tickets1 = 1;int tickets2 = 4;int tickets3 = 2;int tickets4 = 3;
	flightList newAir1 = creat_Flight(des1,fid1,pid1,time1,money1,num1,tickets1);
	flightList newAir2 = creat_Flight(des2,fid2,pid2,time2,money2,num2,tickets2);
	flightList newAir3 = creat_Flight(des3,fid3,pid3,time3,money3,num3,tickets3);
	flightList newAir4 = creat_Flight(des4,fid4,pid4,time4,money4,num4,tickets4);
	//if(OK == insert_flight(flight,newAir1)&&OK == insert_flight(flight,newAir2)&&OK == insert_flight(flight,newAir3)
	//	OK == insert_flight(flight,newAir4))
	if(OK == insert_flight(flight,newAir1)&&OK == insert_flight(flight,newAir2)&&OK == insert_flight(flight,newAir3)&&OK == insert_flight(flight,newAir4))
		return OK;
	else return ERROR;

} 
int main()
{
	inItFlight(flight);//创建了空的链表
	if(OK == makenode(flight))
	home();	
	
}

	



	

 




