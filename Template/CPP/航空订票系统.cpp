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
typedef char TElemType;      //��������

//�Ѷ�Ʊ�ͻ�����������ͷ���˫������ʵ�� 
typedef struct clientNodehaha
{
	char name[MAXSIZE];//����
	char ID_num[MAXSIZE];//֤����
	char flight_num[10];//�����
	char time[MAXSIZE];//���ʱ��
	int order_num;//������
	int amout;//��Ʊ����
	int rank;//��λ�ȼ� 
	struct clientNodehaha *behind;
	struct clientNodehaha *head;
}clientList,*clientListL;
clientList *CLient;


//�ȴ��򲹵Ŀͻ���������ͷ��㵥���� 
typedef struct waitNode{
	char name[MAXSIZE];//����
	char ID_num[MAXSIZE];//֤����
	int amout;//��Ʊ����

	//int rank;//��λ�ȼ� 
	struct waitNode *next;
}waitNode,*waitPtr;
waitNode *Q; 


//��������Ϣ������ͷ���ĵ�����ʵ�� 
typedef struct Flight{
	char destination[MAXSIZE];//�յ�վ 
	char flightId[MAXSIZE];//������ ��Ψһ 
	char planeId[MAXSIZE];//�ɻ��� 
	char time[MAXSIZE];//���ʱ�� 
	float money;
	int num;//��Ա��� 
	int tickets;//��Ʊ��
	clientListL CLientc;//�Ѷ�Ʊ�ͻ����� 
	waitPtr wqueue;//�Ⱥ��油�Ŀͻ����� 
	struct Flight *next;
}Flight,*flightList;
Flight *flight;

//��������� 
//��ʼ�������б� 
Status inItFlight(flightList &F){
	clientListL init_passengerList(clientListL &CLient);
	F = (Flight *)malloc(sizeof(Flight));
	if(NULL==F) return ERROR;
	strcpy(F->destination,"");//�����ַ��� 
	strcpy(F->flightId,"");
	strcpy(F->planeId,"");
	strcpy(F->time,"");
	F->money = 0.0;
	F->num=0;
	F->tickets=0;
	F->next=NULL;
	return OK;
}



//��ʼ���˿����� 
Status init_passengerList(clientListL &CLient){
	CLient=(clientList *)malloc(sizeof(clientList));//����ͷ���
	if(NULL==CLient) return OVERFLOW ;
	CLient->behind=NULL;
	CLient->head=NULL;
	return OK;
}



//��ʼ���򲹳˿����� 
Status init_waitQueue(waitPtr &Q) {
	if(NULL==(Q=(waitNode*)malloc(sizeof(waitNode))))
	return ERROR;
	Q->next = NULL;
	strcpy(Q->name,"");
	strcpy(Q->ID_num,"");
	Q->amout = 0;
	return OK;
}



//����������
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

//�����˿ͽ�� 
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


//�ں�������Ϣ�����в����º�����Ϣ
Status insert_flight(Flight *&h, Flight *p){	
    Flight *f;
	f = h;
	if(NULL == f&&NULL == p) return ERROR;
	p->next = f->next;
	f->next = p;
	return OK;

} 



//�ڳ˿������в����½�� 
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


//�����򲹳˿ͽ�㣬���ҽ����������β�� 
Status en_waitQueue(waitPtr &wqueue,char *n,int amount,char *ID_num){	
	waitNode *p;
	p=(waitNode *)malloc(sizeof(waitNode));
	if(NULL==p) return ERROR;
	strcpy(p->name,n);//���� 
	p->amout=amount;//��Ʊ��
	strcpy(p->ID_num,ID_num);
	p->next=NULL;
	waitNode *f;
	f = wqueue;
	if(NULL == f&&NULL == p) return ERROR;
	while (f->next != NULL)
	{
		f = f->next;//�����ҵ�β�ڵ� 
	}
	f->next = p;
	return OK;

}


//��򲹳˿����� 
int length_queue(waitPtr Q){
	//��������
	int length = 0;
	waitNode *p = Q;
	while(p) {
		length++;

		p = p->next;
	}
	return length;

}


//ɾ������������ 
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



//ɾ���˿������� 
Status delete_clientList(clientListL &cl,clientListL &dp) {
	/* ɾ�������ܿͻ�������ָ����������˫�������ɾ������*/
	clientListL p;
	p = cl->behind;
	if(dp==NULL) return ERROR;
	if(p==dp) { //��ɾ�����Ϊͷ�ڵ����һ����� 
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



/***����Ϊ�û������ĺ���***/ 
//��ѯ���� ����1 
void find(flightList air){
	void userView();
	//system("cls");//�������� 
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                 ��ǰΪ ��ѯ���ߴ���                 *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	char destination[MAXSIZE];
	printf("������Ŀ�ĵأ�");
	scanf("%s",&destination);
	Flight *p;p = air->next;//��ͷ����һ��㿪ʼ��ѯ
	Flight *k;k = air->next;
	int mark = 0;
	while(p){
		if(strcmp(destination,p->destination)==0){
			printf("�е��� %s �ĺ���\n",p->destination);
			mark = 1;
			break;
		}
		p = p->next;
	}//�����˶Ժ���ı���
	if(mark == 1){
		printf("%-20s%-10s%-22s%-26s%-12s%-15s%-8s\n","�����","�յ�վ","����","���ʱ��","Ʊ��","�ɳ����ÿ���","ʣ��Ʊ��\n");
		while(k){
			if(strcmp(destination,k->destination)==0){
				printf("%-20s%-10s%-22s%-25s%-17.2f%-15d%-8d\n",k->flightId,k->destination,k->planeId,k->time,k->money,k->num,k->tickets);
			}
			k = k->next;
		}//�����˶Ժ���ı���		
	}
	if(mark == 0) printf("û��ȥ�� %s �ĺ���",destination);
	printf("\n����1������ѯ������2�����û���ҳ��");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("��Ч���룬������");
		scanf("%s",&l);
	}
	if(l == '1') find(air); 
	if(l == '2') userView();
}

//��Ʊ����  
int booking(clientList *&airCLient,int amount,int sum,int order_num,char *name,char *ID_num,char *flightId,char *time){//�ѳ˿͵Ľ�����ɲ�����˿�����+���뺽������ĳ˿����� 

	clientListL pessage =  creat_client(name,ID_num,flightId,time,order_num,amount,sum);
		if(insert_clientList(airCLient,pessage) == OK){
		printf("��Ʊ�ɹ�");return OK;
    }
    else {
	//system("cls");
		printf("��Ʊʧ�ܣ�Ǯ�����˻أ�����ϵ������Ա��Ʊ");}
    }
		

//�Ƽ�·�ߺ���		
void recommand(Flight *air,clientList *CLient,char *flightId,char *destination,int amount)
{
//����Ŀ�ĵ���ͬ������Ų�ͬ���Ƽ��µĺ���(��Ʊʱ)//�۸����¼���(��Ʊ�����䣬��λ����),ҲҪ���ɶ����� 
	int randx(); 
	flightList p;
	char name[MAXSIZE];//����
	char ID_num[MAXSIZE];
	int order_num;//������
	p = air->next;
	int mark = 0;
	if(NULL== p||NULL==air) {
		printf("û�к�����Ϣ");
		return;
	}
	while(p)
	{
	 if(strcmp(destination,p->destination) == 0&&strcmp(flightId,p->flightId) !=0&&amount<=p->tickets&&p->tickets!=0)//�ҵ��˺��ʵĻ�Ʊ,����ͬ���Ļ�Ʊ
		{
		  printf("�����������ʵ������");
		  scanf("%s",&name);
		  printf("����������ֻ����룺");
		  scanf("%s",&ID_num);
		  int rankx[amount];int g[amount];int sum;float money;//�����λƴ�Ӻ�Ľ�� 		 	
		  for(int j=0;j<amount;j++)//��ÿ��Ʊ�Ĳ�λƴ�� 
		   {
				printf("�������%d��Ʊ�Ĳ�λ�ȼ�",j+1);
				scanf("%d",&rankx[j]);
				float m = p->money;	
			//	scanf("%s",&rankx[j])
				//float m = p->money;
				printf("��ƱΪ%d��Ʊ,Ʊ��Ϊ%8.2f\n",rankx[j],m*(3.0/rankx[j]));
				money += m*(3.0/rankx[j]);//Ʊ���ܺ� 
				g[j] = rankx[j]*pow(10,amount-j-1);
				sum+=g[j];
				
			}
			printf("����Ҫ֧��%8.2fԪ\n",money);
			getch();	
			int d = randx();order_num =  d*10+d/2;//�Զ��������򵥵�����
		    if(OK == booking(p->CLientc,amount,sum,order_num,name,ID_num,p->flightId,p->time))//amout,
			{printf("���µĺ������:%s,���ʱ��Ϊ��%s,������Ϊ%d",p->flightId,p->time,order_num);
			p->tickets = p->tickets-amount;mark = 1;}break;
	    }
	    p = p->next;
	}
	if(mark == 0) printf("û���ҵ����ʺ�����Ϣ������"); 
}



//����򲹶��к��� ; 
int wiat(waitPtr &wqueue,int amount){
	// 	char name[MAXSIZE];//����char ID_num[MAXSIZE];//֤����int amout;//��Ʊ����int rank;//��λ�ȼ� ,char *n,int amount,char *ID_num,int rank
	char name[MAXSIZE];
	char ID_num[MAXSIZE];
	printf("������������֣�");
	scanf("%s",&name);
	printf("����������ֻ����룺");
	scanf("%s",&ID_num);
	if(OK == en_waitQueue(wqueue,name,amount,ID_num)) {
		//system("cls");
		printf("\t\t\t\t*******************************************************\n");
		printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
		printf("\t\t\t\t*                ���Ѿ��ɹ����������               *\n");
		printf("\t\t\t\t*               �������������������Ա����ϵ��        *\n");
		printf("\t\t\t\t*                 ��������������������                *\n"); 
		printf("\t\t\t\t*******************************************************\n");
	}
	else printf("����ʧ��"); 
} 
	

		
//��Ʊ���������������˶�Ʊ�������Ƽ�·�ߺ���������򲹶��к���  �û�����2 
int bookTickets(flightList &air){
	int randx();
	//system("cls");//�������� 
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                   ��ǰΪ ��Ʊ����                   *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	void userView();
	Flight *p;p = air->next;//��ͷ����һ��㿪ʼ��ѯ
	Flight *k;k = air->next; 
	char flightId[MAXSIZE];//����� 
	char flightId1[MAXSIZE];
	char destination[MAXSIZE];//Ŀ�ĵ� 
	int amount;char i;
	int flag = 0;
	char name[MAXSIZE];//����
	char ID_num[MAXSIZE];
	int order_num;int mark = 0;//������ 
	int markj = 0;
	printf("������������Ŀ�ĵ�(��1)���ߺ����(��2)����ѯ��");
	scanf("%s",&i);
	while(i!='1'&&i!='2'){
		printf("��Ч���룬�����䣺"); 
		scanf("%s",&i);
	}
	if(i=='1'){ 
		printf("������Ŀ�ĵأ�");
		scanf("%s",&destination);
		printf("�������������Ʊ����ϵͳ��Ϊ�㷵�ز�ѯ��Ϣ\n");
		getch();
		printf("������Ҫ�����Ʊ����");
		scanf("%d",&amount);
		while(p){
		//&&amount<=p->tickets&&p->tickets!=0 
		if(strcmp(destination,p->destination)==0) flag = 1;
		if(strcmp(destination,p->destination)==0&&amount<=p->tickets&&p->tickets!=0){
			//if(amount<=p->tickets&&p->tickets!=0){
			
			if(strcmp(destination,p->destination)==0) markj = 1;//�е�������ص�ĺ��� 
			
			int rankx[amount];int g[amount];int sum=0;float money = 0.0;//�����λƴ�Ӻ�Ľ�� 

				printf("�����������ʵ������");
				scanf("%s",&name);
				printf("����������ֻ����룺");
				scanf("%s",&ID_num);

				printf("��ֱ���������Ҫ�Ĳ�λ�ȼ���\n");
				for(int j=0;j<amount;j++)//��ÿ��Ʊ�Ĳ�λƴ�� 
					{printf("�������%d��Ʊ�Ĳ�λ�ȼ�\n",j+1);
					 scanf("%d",&rankx[j]);
					 float m = p->money;
					 printf("��ƱΪ%d��Ʊ,Ʊ��Ϊ%8.2f\n",rankx[j],m*(3.0/rankx[j]));
					 money += m*(3.0/rankx[j]);//Ʊ���ܺ� 
					 g[j] = rankx[j]*pow(10,amount-j-1);
	
					 sum+=g[j];
		
					}
				printf("����Ҫ֧��%8.2fԪ\n",money);
				getch();	
				int d = randx();order_num =  d*10+d/2;//�Զ��������򵥵�����

				if(OK == booking(p->CLientc,amount,sum,order_num,name,ID_num,p->flightId,p->time))
				
				 {
					printf("\n��ĺ�����ǣ�%s,������ʱ��Ϊ��%s,������Ϊ%d",p->flightId,p->time,order_num);
				p->tickets = p->tickets-amount;mark = 1;

				}
		
				break;
			}
			if(strcmp(destination,p->destination)==0)
			{
			strcpy(flightId1,p->flightId);
		}
			p = p->next;
		
		}//�����˶Ժ���ı���
		//printf("%d,flag��",flag);
		if(mark == 0&&flag == 1) {
			//����flag == 1 ,������������������������� 
				printf("�����Ѿ����������е��� %s �ĺ��࣬���ǵ���Ʊ���������������",destination);
				printf("\n����������뵽�� %s �ĺ��� %s �ĺ�������?1/2��",destination,flightId1);
		char o;
		printf("\n�����룺");
		scanf("%s",&o);
		while(o!='1'&&o!='2'){
		printf("��Ч���룬�����䣺");
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
	 
	if(i=='2'){//���ݺ���ŵõ�Ŀ�ĵ� 
		printf("�����뺽��ţ�");
		scanf("%s",&flightId);
		printf("�������������Ʊ����ϵͳ��Ϊ�㷵�ز�ѯ��Ϣ\n");
		getch();
		printf("������Ҫ�����Ʊ����");
		scanf("%d",&amount);
		while(p){
		if(strcmp(flightId,p->flightId)==0){
			flag = 1;
			if(p->tickets>=amount)
			{
			int rankx[amount];int g[amount];int sum = 0;float money = 0.0;//�����λƴ�Ӻ�Ľ��
				printf("�����������ʵ������");
				scanf("%s",&name);
				printf("����������ֻ����룺");
				scanf("%s",&ID_num);

				printf("��ֱ����������Ҫ�Ĳ�λ�ȼ���");
				for(int j=0;j<amount;j++)//��ÿ��Ʊ�Ĳ�λƴ�� 
					{printf("�������%d��Ʊ�Ĳ�λ�ȼ�\n",j+1);
					 scanf("%d",&rankx[j]);
					 float m = p->money;
					 printf("��ƱΪ%d��Ʊ,Ʊ��Ϊ%8.2f\n",rankx[j],m*(3.0/rankx[j]));
					 money += m*(3.0/rankx[j]);//Ʊ���ܺ� 
					 g[j] = rankx[j]*pow(10,amount-j-1);
					 sum+=g[j];
					}
				printf("����Ҫ֧��%8.2fԪ",money);
				getch();	
				int d = randx();order_num =  d*10+d/2;//�Զ��������򵥵�����
				if(OK == booking(p->CLientc,amount,sum,order_num,name,ID_num,p->flightId,p->time)){
				printf("\n������ʱ��Ϊ��%s,������Ϊ%d",p->time,order_num);
				p->tickets = p->tickets-amount;}
			}else if(p->tickets==0)
			{printf("\n�ú�������Ա�������Ƿ���Ҫ�Ƽ����� %s ����������?(y/n)\n",p->destination);char f;
			//recommend(air,flightId,destination,amount);
			printf("�����룺");
			scanf("%s",&f);
			while(f!='y'&&f!='n'){
				printf("��Ч���룬�����䣺");
				scanf("%s",&f);
			}
			if(f == 'y') recommand(air,CLient,flightId,p->destination,amount);
			if(f == 'n') {
				printf("����������뺽�� %s �ĺ򲹶�����(?1/2)",flightId);char t;
				printf("�����룺");
				scanf("%s",&t);
				while(t!='1'&&t!='2'){
					printf("��Ч���룬�����䣺");
					scanf("%s",&t);
					}
				if(t == '1') wiat(p->wqueue,amount) ;
				//int wiat(waitQueue &wqueue,char *n,int amount,char *ID_num,int rank)
				if(t == '2' ){
				userView();//break;
				}
		}
			}else if(p->tickets!=0&&p->tickets<amount){
			printf("��Ǹ����Ʊ��ʣ %d ,�Ƿ��Ƽ����� %s ����������?(?y/n)",p->tickets,p->destination);char f;
			printf("�����룺");
			scanf("%s",&f);
			while(f!='y'&&f!='n'){
				printf("��Ч���룬�����䣺");
				scanf("%s",&f);}
			if(f == 'y') recommand(air,CLient,p->flightId,p->destination,amount);
			if(f == 'n') {
				printf("����������뺽�� %s �ĺ򲹶�����(?1/2)",flightId);char t;
				printf("�����룺");
				scanf("%s",&t);
				while(t!='1'&&t!='2'){
					printf("��Ч���룬�����䣺");
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
	if(flag==0){printf("\n��ѯ�����ú��࣡�뷵��ȷ��\n");
	}
	printf("\n����1������Ʊ������2�����û���ҳ��");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("��Ч���룬������");
		scanf("%s",&l);
		}
	if(l == '1') bookTickets(flight);
	if(l == '2') userView();
	 
	  
	 } 
	 
	 

//��ʾ���к�����Ϣ �û�����3 
void displayAllInfo(Flight *F)
{	
	//system("cls");//�������� 
	void userView();
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                 ����Ϊ���к�����Ϣ                  *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	Flight *p=F;
	int flags = 0;
   printf("%-20s%-10s%-22s%-26s%-12s%-15s%-8s\n","�����","�յ�վ","����","���ʱ��","Ʊ��","�ɳ����ÿ���","ʣ��Ʊ��\n");

	p = p->next;

	for(;p!=NULL;p=p->next)
	{
	printf("%-20s%-10s%-22s%-25s%-17.2f%-15d%-8d\n",p->flightId,p->destination,p->planeId,p->time,p->money,p->num,p->tickets);

	flags = 1;
			
	}
	if(flags ==0) printf("\t\t\t\t��Ǹû�к�����Ϣ������");
	printf("\n����1�ɷ����û���ҳ��");
	char l;
	scanf("%s",&l);
	while(l!='1'){
		printf("��Ч���룬������");
		scanf("%s",&l);
		}
	if(l == '1') userView(); 

}
//��ʾ���к�����Ϣ ����Ա����5 
void displayAllInfo1(Flight *F)
{	
	//system("cls");//�������� 
	void adminhome();
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                 ����Ϊ���к�����Ϣ                  *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	Flight *p=F;
	int flags = 0;
   printf("%-20s%-10s%-22s%-26s%-12s%-15s%-8s\n","�����","�յ�վ","����","���ʱ��","Ʊ��","�ɳ����ÿ���","ʣ��Ʊ��\n");

	p = p->next;

	for(;p!=NULL;p=p->next)
	{
	printf("%-20s%-10s%-22s%-25s%-17.2f%-15d%-8d\n",p->flightId,p->destination,p->planeId,p->time,p->money,p->num,p->tickets);

	flags = 1;
			
	}
	if(flags ==0) printf("\t\t\t\t��Ǹû�к�����Ϣ������");
	printf("\n����1�ɷ��ع���Ա��ҳ��");
	char l;
	scanf("%s",&l);
	while(l!='1'){
		printf("��Ч���룬������");
		scanf("%s",&l);
		}
	if(l == '1') adminhome(); 

}


//��ѯ���� ��Ӧ�û�����4 
void finddingdan(flightList air){
	void userView();
	//system("cls");//�������� 
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                 ��ǰΪ ��ѯ��������                 *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	char flightId[MAXSIZE];
	char ID_num[MAXSIZE];
	printf("�����뺽��ţ�");
	scanf("%s",&flightId);
	Flight *p;p = air->next;//��ͷ����һ��㿪ʼ��ѯ
	Flight *k;k = air->next;
	int mark = 0;int q = 0;
	while(p){
		if(strcmp(flightId,p->flightId)==0){
			q = 1;
			printf("\n������������֣�");
			scanf("%s",&ID_num);
			clientListL k = p->CLientc->behind;
			if(k==NULL)printf("�ú��ඩ��Ϊ�գ���ѯ�������");
			else{
			
			system("cls");//�������� 
			printf("%-20s%-22s%-22s%-26s%-12s\n","�ͻ�����","������","�ֻ���","���ʱ��","Ʊ��\n");
			
			
			
			while(k){
				if(strcmp(ID_num,k->name)==0){
					mark = 1;
				printf("%-20s%-22d%-22s%-25s%-8d\n",k->name,k->order_num,k->ID_num,k->time,k->amout);
				}
				k = k->behind;
			}
			if(mark == 0) printf("�ú���û�����Ķ���");
			
}
		break;	}
		
			p = p->next;
		
		}//�����˶Ժ���ı���
	if(q == 0) printf("�����ں��� %s ",flightId);
	printf("\n����1������ѯ������2�����û�ҳ��");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("��Ч���룬������");
		scanf("%s",&l);
		}
	if(l == '1') finddingdan(air);
	if(l == '2') userView();
}



/***����Ա��������***/ 
//���Ӻ���  ����Ա����1 
void addFlight(flightList &air){
	int randx();
	void adminhome();
	//system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
	printf("\t\t\t\t*            ������������������������������           *\n");
	printf("\t\t\t\t*           | �����߼�Ȩ�ޣ��������������|           *\n");
	printf("\t\t\t\t*            ������������������������������           *\n");
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
	printf("�������յ�վ����");
	scanf("%s",destination);
	printf("�����뺽��ţ�");
	scanf("%s",flightId);
	printf("������ɻ��ţ�");
	scanf("%s",planeId);
	printf("���������ʱ��(��ʽΪcccc-ww-jj-hh:aa):");
	scanf("%s",time);
	printf("Ʊ��(��ȷ��С�������λ)��");
	scanf("%f",&money);
	printf("�������Ա���");
	scanf("%d",&num);
	printf("��������Ʊ������");
	scanf("%d",&tickets);
	int ranxe;
	int ranx = randx();//�õ������
	system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
	printf("\t\t\t\t*                   ��������������                    *\n");
	printf("\t\t\t\t*                  | ��������֤�� |                   *\n");
	printf("\t\t\t\t*                   ��������������                    *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("��֤��Ϊ��%d\n",ranx); 
	printf("�ڴ˴����룺");
	scanf("%d",&ranxe);
	while(ranx != ranxe)
	{
	 printf("��֤�벻��ȷ������\n");
	 printf("���ٴ����룺");
	 scanf("%d",&ranxe);
	 printf("���������֤����%d",ranxe);
	}
	
	flightList newAir = creat_Flight(destination,flightId,planeId,time,money,num,tickets);

	if(insert_flight(air,newAir) == OK){
	//system("cls");
	printf("��Ӻ���ɹ�");}
	
	printf("\n����1����¼�룬����2���ع���Աҳ��");
	printf("\n�����룺");
	scanf("%s",&mark);
	while(mark!='1'&&mark!='2'){
		printf("��Ч���룬�����䣺");
		scanf("%s",&mark); 
	}
	
	}
	if(mark == '2') 
	adminhome();
}



//ɾ������  ����2 
void deleflight(flightList &air){
	void adminhome();
	//system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
	printf("\t\t\t\t*            ������������������������������           *\n");
	printf("\t\t\t\t*           | �����߼�Ȩ�ޣ��������������|           *\n");
	printf("\t\t\t\t*            ������������������������������           *\n");
	printf("\t\t\t\t*                 ��ǰΪɾ�����ര��                  *\n");
	printf("\t\t\t\t*******************************************************\n");

	char flightId[MAXSIZE];
	printf("��������Ҫɾ���ĺ���ţ�");
	scanf("%s",flightId);
	if(delete_flight(air,flightId) == 1){
		printf("\nɾ���ɹ���");
	}else{
		printf("\nɾ��ʧ�ܣ�������ϵͳ���ڵĺ����");
		
	}
	printf("ɾ������ɹ�������1����ɾ��������2���ع���Աҳ��");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("��Ч���룬������");
		scanf("%s",&l);
		}
	if(l == '1') deleflight(flight); 
	if(l == '2') adminhome();
	
}



//��ʾָ�������ϵĿͻ����� ����3 
void displayClientInfo(flightList air){
	void adminhome();
	//system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
	printf("\t\t\t\t*            ������������������������������           *\n");
	printf("\t\t\t\t*           | �����߼�Ȩ�ޣ��������������|           *\n");
	printf("\t\t\t\t*            ������������������������������           *\n");
	printf("\t\t\t\t*             ��ǰΪ�鿴�������ж����Ĵ���            *\n");
	printf("\t\t\t\t*******************************************************\n");
	int flag = 0;
	char flightId[MAXSIZE];
	printf("\n�����뺽��ţ�");
	scanf("%s",flightId);
	printf("%s",flightId);
	flightList p = air->next;
	if(p == NULL)printf("û�к�����Ϣ");
	else{
	while(p){//�Ҹú�����Ϣ
		if(strcmp(flightId,p->flightId) == 0){
			flag = 1;
			break;
		}p = p->next;
	}
	if(flag == 1){
		clientListL cp = p->CLientc->behind;
		if(cp == NULL){
			printf("\n�ú���ͻ�����Ϊ��\n");
		}
		else {printf("����Ϊ���ࣺ%s �����пͻ�����    \n",flightId);
		printf("%-20s%-22s%-22s%-26s%-12s\n","�ͻ�����","������","�ֻ���","���ʱ��","Ʊ��\n");} 
		
		while(cp){
			
		printf("%-20s%-22d%-22s%-29s%-8d\n",cp->name,cp->order_num,cp->ID_num,cp->time,cp->amout);
		cp = cp->behind;	
			
		}
	}
	else {
		printf("�Ҳ����ú�����Ϣ����������ȷ�ĺ����");}
	
}
	printf("����1�����鿴������2���ع���Աҳ��");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("��Ч���룬������");
		scanf("%s",&l);
		}
	if(l == '1') displayClientInfo(flight); 
	if(l == '2') adminhome();
	
}



//�鿴ָ������ĺ���Ա ����4 
void displaywaitClientInfo(flightList air){
	void adminhome();
	//system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
	printf("\t\t\t\t*            ������������������������������           *\n");
	printf("\t\t\t\t*           | �����߼�Ȩ�ޣ��������������|           *\n");
	printf("\t\t\t\t*            ������������������������������           *\n");
	printf("\t\t\t\t*             ��ǰΪ�鿴���ߺ򲹳˿͵Ĵ���            *\n");
	printf("\t\t\t\t*******************************************************\n");
	int flag = 0;
	char flightId[MAXSIZE];
	printf("\n�����뺽��ţ�");
	scanf("%s",flightId);
	flightList p = air->next;
	if(p == NULL)printf("û�к�����Ϣ");//һ�����඼û�� 
	else{
	while(p){//�Ҹú�����Ϣ
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
			printf("\n�ú���򲹿ͻ�����Ϊ��\n");
		}
		else {
		cp = cp->next;
		printf("����Ϊ���ࣺ%s �ĺ򲹳˿���    \n",flightId);
		int length = length_queue(cp);
		printf("%d",length);
		
		
		printf("\n%-20s%-22s%-22s\n","�ͻ�����","�ֻ���","��Ҫ��Ʊ��\n");} 

		while(cp){
			
		printf("%-20s%-22s%-22d\n",cp->name,cp->ID_num,cp->amout);
		cp = cp->next;	
			
		}
		
		} 	
	else {
		printf("�Ҳ����ú�����Ϣ����������ȷ�ĺ����");}
		
}
	printf("����1�����鿴������2���ع���Աҳ�棺");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("��Ч���룬������");
		scanf("%s",&l);
		}
	if(l == '1') displaywaitClientInfo(flight); 
	if(l == '2') adminhome();}

 


//��Ʊʱ�����򲹶��к��� 
void show(flightList &air,waitNode *&Q)
{	
	int randx();
	int order_num; 
	waitNode *g;//ָ��ý��
	waitNode *f;//ͷ 
	waitNode *r;//β 
	waitNode *p;
	waitNode *d1;
	f = Q;//fָ��ͷ��� 
	g = f->next;
	

	int shijinum = 0;//���������ĺ򲹳˿͵��¶�Ʊ�� 
	if (Q->next == NULL) printf("�򲹳˿Ͷ���Ϊ��!\n");
	else{
	while (g != NULL)//ѭ�����ң�ѯ�ʺ��ʵ��û� 
	{   
		printf("\n�����ڼ����˿�  %s",g->name);
		printf("...���Ժ�...");
		
		if(air->tickets>=g->amout){
		d1 = Q;//��Ʊ������ú򲹳˿͵�Ҫ�� 
			printf("\n�ú򲹳˿�����������\n");
			printf("\n���������� %s �������ֻ������� %s , ���Ķ�Ʊ���� %d \n",g->name,g->ID_num,g->amout);
			printf("\n������������ϵ������(���Ķ�Ʊ����������Ʊ��Χ�ڽ��и���)\n");
			printf("\t\t\t****************\n");
			printf("\t\t\t*  ��ƱΪ:%d   *\n",air->tickets);
			printf("\t\t\t****************\n");
			printf("\n��ѯ�����µ�Ʊ�����󣬺Ͳ�λ����");
			printf("\n���Ƿ���ܴ˴ζ�Ʊ����?(y/n)");
			char h;
			scanf("%s",&h);
		while(h!='y'&&h!='n'){
				printf("��Ч���룬������");
				scanf("%s",&h);
			} 
		
			if(h == 'y'){//�ú��û�ͬ����ж�Ʊ���� 
				//
				
				printf("���������Ķ�Ʊ����");
				scanf("%d",&shijinum);
				
				
				int rankx[shijinum];int g1[shijinum];int sum = 0;float money = 0.0;//�����λƴ�Ӻ�Ľ��
				
				
				printf("��ֱ�����ͻ���Ҫ�Ĳ�λ�ȼ���\n");
				
				
				for(int j=0;j<shijinum;j++)//��ÿ��Ʊ�Ĳ�λƴ�� 
					{printf("�������%d��Ʊ�Ĳ�λ�ȼ�\n",j+1);
					 scanf("%d",&rankx[j]);
					 float m = air->money;
					 printf("��ƱΪ%d��Ʊ,Ʊ��Ϊ%8.2f\n",rankx[j],m*(3.0/rankx[j]));
					 money += m*(3.0/rankx[j]);//Ʊ���ܺ� 
					 g1[j] = rankx[j]*pow(10,shijinum-j-1);
					 sum+=g1[j];
					}
				printf("�ܷ���Ϊ%8.2fԪ\n",money);
				getch();
				int d = randx();order_num =  d*10+d/2;//�Զ��������򵥵�����

				if(OK == booking(air->CLientc,shijinum,sum,order_num,g->name,g->ID_num,air->flightId,air->time)){
				printf("\n�ó˿͵����ʱ��Ϊ��%s,������Ϊ%d\n",air->time,order_num);
				air->tickets = air->tickets - shijinum;//��Ʊ���仯 
				}//��Ʊ����*/
				printf("\n!!!�����ɹ�������\n");
				printf("�����ź���������Ѿ����͵��ͻ��ֻ� %s �У�����",g->ID_num);

				while(d1){
					if(d1->next == g){
						d1->next = g->next;
					}
					d1 = d1->next;
				}
				printf("����1������ҳ�棬����2���ع���Աҳ��");
				char t;
				printf("�����룺");
				scanf("%s",&t);
				while(t!='1'&&t!='2'){
					printf("��Ч���룬����������");
					scanf("%s",&t);
				
				}
				void home();
				if(t == '1') home();
				void adminhome(); 
				if(t == '2')  adminhome();

		break;					
		}
		if(h=='n'){
			printf("\n���ڼ�����һ���򲹳˿ͣ�����");
			
		}
		
			
		
		
			}
		
		g = g->next;
		}//while��������� 
}

}




//��Ʊ ����6 
int refund(flightList &air){
	void adminhome();
	//system("cls");
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*               ��ӭʹ��THIRTEEN����ϵͳ              *\n");
	printf("\t\t\t\t*            ������������������������������           *\n");
	printf("\t\t\t\t*           | �����߼�Ȩ�ޣ��������������|           *\n");
	printf("\t\t\t\t*            ������������������������������           *\n");
	printf("\t\t\t\t*                  ��ǰΪ��Ʊ����                     *\n");
	printf("\t\t\t\t*******************************************************\n");
	char flightId[MAXSIZE];
	int am;
	char name[MAXSIZE];
	printf("������������֣�");
	scanf("%s",name);
	printf("�����뺽��ţ�");
	scanf("%s",flightId);
	printf("��������Ҫ�˶���Ʊ����");
	scanf("%d",&am);
	flightList p = air->next;//��ͷ������һ����㿪ʼ 
	int flag = 0;
	clientListL totaList;
	clientListL totaList1;
	while(p){
		if(strcmp(p->flightId,flightId) == 0){//�ҵ��ú����� 
			totaList = p->CLientc;//�Ӹ�ͷ������һλ��ʼ
			totaList1 = p->CLientc->behind; 
		while(totaList){
			if(strcmp(totaList->name,name) == 0){//�ҵ��˸ó˿ͽ�� 
				
				if(am<totaList->amout){
					totaList->amout = totaList->amout-am;//ֻ���޸ĳ˿ͽ���Ʊ�� 
					p->tickets = p->tickets+am;//Ʊ���仯
					printf("\n��Ʊ�ɹ����˿����Ѿ��ɹ�ԭ·���������˺�\n");
					show(p,p->wqueue);
				}
				else if(am == totaList->amout){//ȫ����Ʊ��Ҫɾ����һ����� 
					if(OK==delete_clientList(totaList1,totaList)) 
					{totaList->amout = totaList->amout-am;
					p->tickets = p->tickets+am;//Ʊ���仯
					printf("\n��Ʊ�ɹ����˿����Ѿ��ɹ�ԭ·���������˺�\n");
					printf("����Ʊ��Ϊ%d",p->tickets);
					show(p,p->wqueue);} 
				}
				else printf("�㹺���Ʊ��û����ô�࣬������ȷ��");
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
		printf("�Ҳ����ö�������Ʊʧ��");
	
	}
	printf("\n����1����������Ʊ������2���ع���Աҳ�棺");
	char l;
	scanf("%s",&l);
	while(l!='1'&&l!='2'){
		printf("��Ч���룬������");
		scanf("%s",&l);
		}
	if(l == '1') refund(flight); 
	if(l == '2') adminhome();
	
	return flag;
	
}
//��ͨ�û���¼ 
void userhome(){
	void mima1(int &tags1);
	//system("cls");
	char key1[10];
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                ��ӭʹ��THIRTEEN����ϵͳ             *\n");
	printf("\t\t\t\t*                 ��������������������                *\n");
	printf("\t\t\t\t*                | ��ǰ���:��ͨ�û� |                *\n");
	printf("\t\t\t\t*                 ��������������������                *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("\n");

	int tags1 = 1;
	mima1(tags1);
}



//����
char root_key1[]="123456";
//���뺯�� 
void mima1(int &tags1){
	void home();
	void mixmima();
	char i;
	char key1[10];
	void userView();
	printf("��1����������룬��2������ҳ��:"); 
	scanf("%s",&i);
	while(i!='1'&&i!='2'){
		printf("��Ч���룬�����䣺");
		scanf("%s",&i);
	}
	if(i=='1'){
		printf("��%d����������:",tags1);
		scanf("%s",&key1);
		if (strcmp(key1, root_key1) == 0) userView();
	else{
		printf("�������\n");
				if(tags1>2) mixmima();//tags = 3,������ʾ 
		else{++tags1;mima1(tags1);};} 
	
	}
	if(i=='2')  home();//�ص���ҳ�� 
}

//��ͨ�û����� 

void userView(){
	int i; 
	//system("cls");
	void home();
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*              ��ӭʹ��THIRTEEN����ϵͳ               *\n");
	printf("\t\t\t\t*                 ��������������������                *\n");
	printf("\t\t\t\t*                | ��ǰ���:��ͨ�û� |                *\n");
	printf("\t\t\t\t*                 ��������������������                *\n");
	printf("\t\t\t\t*     ��ѡ������ҵ��                                *\n");
	printf("\t\t\t\t*                   1.��ѯ����                        *\n");
	printf("\t\t\t\t*                   2.������Ʊ                        *\n");
	printf("\t\t\t\t*                   3.�鿴���к�����Ϣ                *\n");
	printf("\t\t\t\t*                   4.��ѯ����                        *\n");
	printf("\t\t\t\t*                   5.������ҳ��                      *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("��ѡ����Ĳ�����");
	scanf("%d",&i);
	while(i!=1&&i!=2&&i!=3&&i!=4&&i!=5){
		printf("��Ч���룬�����䣺"); 
		scanf("%d",&i);
	}
	switch(i){
		case 1: find(flight);break;
		case 2: bookTickets(flight);break;
		case 3: displayAllInfo(flight);break;
		case 4: finddingdan(flight);break;
		case 5: home(); 
		default: printf("���д���!\n");getchar();	}
} 




//����Ա���� 
void adminhome(){
	//system("cls");
	char i;
	void home();
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                ��ӭʹ��THIRTEEN����ϵͳ             *\n");
	printf("\t\t\t\t*                 ��������������������                *\n");
	printf("\t\t\t\t*                |  ��ǰ���:����Ա  |                *\n");
	printf("\t\t\t\t*                 ��������������������                *\n");
	printf("\t\t\t\t*    ��ѡ������ҵ��                                 *\n");
	printf("\t\t\t\t*                  1.���Ӻ���                         *\n");
	printf("\t\t\t\t*                  2.ɾ������                         *\n");
	printf("\t\t\t\t*                  3.�鿴����Ŀͻ�����               *\n");
	printf("\t\t\t\t*                  4.�鿴����򲹿ͻ�����             *\n");
	printf("\t\t\t\t*                  5.�鿴���к���                     *\n");
	printf("\t\t\t\t*                  6.��Ʊ                             *\n");
	printf("\t\t\t\t*                  7.������ҳ��                       *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("��ѡ����Ĳ�����");
	scanf("%s",&i);
	while(i!='1'&&i!='2'&&i!='3'&&i!='4'&&i!='5'&&i!='6'&&i!='7'){
		printf("��Ч���룬�����䣺"); 
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
		default: printf("���д���!\n");getchar();
	}
	
}



//����Ա������� 
void adminView(){
	void mima(int &tags);
	//system("cls");
	char key[10];
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                ��ӭʹ��THIRTEEN����ϵͳ             *\n");
	printf("\t\t\t\t*                 ��������������������                *\n");
	printf("\t\t\t\t*                |  ��ǰ���:����Ա  |                *\n");
	printf("\t\t\t\t*                 ��������������������                *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("\n");
	int tags = 1;
	mima(tags);
}
//char root_key[]={'a','d','m','i','n'};
//����
char root_key[]="admin";
//���뺯�� 
void mima(int &tags){
	void home();
	void mixmima();
	char i;
	char key[10];
	void adminhome();
	printf("��1����������룬��2������ҳ��:"); 
	scanf("%s",&i);
	while(i!='1'&&i!='2'){
		printf("��Ч���룬�����䣺");
		scanf("%s",&i);
	}
	if(i=='1'){
		printf("��%d����������:",tags);
		scanf("%s",&key);
		if (strcmp(key, root_key) == 0) adminhome();
	else{
		printf("�������\n");
				if(tags>2) mixmima();//tags = 3,������ʾ 
		else{++tags;mima(tags);};} 
	
	}
	if(i=='2')  home();//�ص���ҳ�� 
}






//��������������� 
void mixmima(){
	//system("cls");   
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*      !                                       !      *\n");
	printf("\t\t\t\t*     !!!                                     !!!     *\n");
	printf("\t\t\t\t*     !!!       ���Ѿ��������3�����룡       !!!     *\n");
	printf("\t\t\t\t*     !!!  ���˳�ϵͳ�صǣ�������ϵ������Ա   !!!     *\n");
	printf("\t\t\t\t*     !!!           ��������                  !!!     *\n");
	printf("\t\t\t\t*      !                                       !      *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*      !                                       !      *\n");
	printf("\t\t\t\t*     !!!                                     !!!     *\n");
	printf("\t\t\t\t*******************************************************\n");
}



//��ҳ�� 
void home(){
	//system("cls");//�������� 
	char i;
	printf("\t\t\t\t*******************************************************\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*               ��ӭ����THIRTEEN����ϵͳ              *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*                   ��ѡ���¼���                    *\n");
	printf("\t\t\t\t*                                                     *\n");
	printf("\t\t\t\t*               �û�����1�� ����Ա������2             *\n");
	printf("\t\t\t\t*                  �˳�ϵͳ������3                    *\n");
	printf("\t\t\t\t*******************************************************\n");
	printf("������:");
	scanf("%s",&i);
	while(i!='1'&&i!='2'&&i!='3'){
		printf("��Ч���룬�����䣺"); 
		scanf("%s",&i);
	}
	switch(i){
		case '1': userhome();break;
		case '2': adminView();break;
		case '3': exit(0);break;
		default: printf("���д���!\n");getchar();
	}			
}

 
//�����������ģ����֤�� 
int randx(){
	srand((unsigned) (time(NULL)));
	int d = rand();
	return d;
}


//creat_Flight(char *des,char *fid,char *pid,char *time,float money,int num,int tickets)
Status makenode(flightList &flight){
	char des1[MAXSIZE] = "�Ϻ�";char des2[MAXSIZE] = "����";
	char des3[MAXSIZE] = "����";char des4[MAXSIZE] = "�ɶ�";
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
	inItFlight(flight);//�����˿յ�����
	if(OK == makenode(flight))
	home();	
	
}

	



	

 




