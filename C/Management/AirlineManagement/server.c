#include "common.h"
#include "kernel_list.h"
#include "list.h"
#include "server.h"

int broadcastMsg(char *buf, struct list_node *peer)
{
	struct list_node *p = NULL;
	
	pthread_mutex_lock(&m);
	list_for_each_entry(p,&(head->list),list)
	{
		if(p->connfd == peer->connfd)  //找到自己
		{
			continue;
		}
		
		send(p->connfd,buf,strlen(buf),0);
	}
	pthread_mutex_unlock(&m);
	
	return 0;
}


int SendMsg(char *buf, int connfd)
{
	send(connfd,buf,strlen(buf),0);
	return 0;
}

//显示当前路径函数
void CheckPath(void)
{
 //获取当前工作目录函数
    char path[100];

    //清屏函数(清空控制台)
    system("clear");

    getcwd(path, 100);
    printf("current work path:%s\n", path);
}


//初始化头节点
struct OrdinaryPassNode *QequestLinkInitNode(void)
{
    struct OrdinaryPassNode *new_node;

    new_node = malloc(sizeof(struct OrdinaryPassNode));
    if(new_node == NULL)
    {
        perror("申请内存失败");
        return NULL;
    }

    INIT_LIST_HEAD(&(new_node->Ordinary_passenger_list));//将小个结构体的上下指针指向自己
    return new_node;
}

//尾插
void InsertPassTailNode(struct OrdinaryPassNode *Ordinary_passenger_list_head, struct OrdinaryPassNode *Ordinary_passenger_insert_node)
{  
    list_add_tail(&(Ordinary_passenger_insert_node->Ordinary_passenger_list), &(Ordinary_passenger_list_head->Ordinary_passenger_list));
}

//判断这个人是否已经注册过
struct OrdinaryPassNode *FindUsers(struct OrdinaryPassNode *Ordinary_passenger_list_head, char *name)
{
	struct OrdinaryPassNode *pos,*n;
	//printf("name1 = %s\n",name);
    list_for_each_entry_safe(pos,n, &Ordinary_passenger_list_head-> Ordinary_passenger_list,  Ordinary_passenger_list)
    {	
		//printf("name = %s\n",pos->info.name);
        if(strcmp(pos->info.name,name) == 0)
		{
			return pos;
		}
        
    }	
    return NULL;
}

struct OrdinaryPassNode *FindUserID(struct OrdinaryPassNode *Ordinary_passenger_list_head, char *id)
{
	struct OrdinaryPassNode *pos,*n;
	
    list_for_each_entry_safe(pos,n, &Ordinary_passenger_list_head-> Ordinary_passenger_list,  Ordinary_passenger_list)
    {	
		
        if(strcmp(pos->info.id,id) == 0)
		{
			return pos;
		}
        
    }	
    return NULL;
}

//判断这电话号码是否已经注册过
struct OrdinaryPassNode *FindUserNum(struct OrdinaryPassNode *Ordinary_passenger_list_head, char *phone_number)
{
	struct OrdinaryPassNode *pos,*n;
	
    list_for_each_entry_safe(pos,n, &Ordinary_passenger_list_head-> Ordinary_passenger_list,  Ordinary_passenger_list)
    {	
        if(strcmp(pos->info.phone_number,phone_number) == 0)
		{
			return pos;
		}
        
    }	
    return NULL;
}

//分割
char *parting(char *data)
{
	char seqs[] = "\n";
    char *tmp;
	tmp = malloc(500*sizeof(tmp));
	data = strtok(data,seqs);
	
	return data;
}

//分割文件中中的数据
void SplitFun(struct OrdinaryPassNode *Ordinary_passenger_list_head, char *buf)
{
	//1. 为新节点申请空间。
	struct OrdinaryPassNode *new;

    new = QequestLinkInitNode();
	
	//2. 分割字符串，为新节点数据域指针域赋值。
	char seqs[] = ",";
	
    char *tmp;

	tmp = strtok(buf,seqs);
	strcpy(new->info.name,tmp);

    tmp = strtok(NULL,seqs);
	strcpy(new->info.id,tmp);
	
	tmp = strtok(NULL,seqs);
	new->info.age = atoi(tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.phone_number,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.passwd,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.pay_passwd,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.question,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.answer,tmp);

	tmp = strtok(NULL,seqs);
	new->info.balance = atoi(tmp);
	
	tmp = strtok(NULL,seqs);  
	new->info.vip= atoi(tmp);

	tmp = strtok(NULL,seqs);
	new->info.integral = atoi(tmp);

    InsertPassTailNode(Ordinary_passenger_list_head, new);
    
	return;
}

//读文件
void read_file(struct OrdinaryPassNode *Ordinary_passenger_list_head, char *filename)
{
	//1. 打开文件。
	FILE *fp = fopen(filename,"a+");
	if(fp == NULL)
		perror("打开文件错误!\n");
	
	//2. 读取文件数据。
	char buf[200] = {0};
	fread(buf,20,10,fp);
	
	//3. 关闭文件。
	fclose(fp);
	
	//4. 分割数据。
    SplitFun(Ordinary_passenger_list_head, buf);
	
	return;
}

//初始化已注册（在文件夹中的）老用户
void InitOldUser(struct OrdinaryPassNode *head)
{
	//1. 打开目录。
	DIR* dp = opendir("./user_data");
	if(dp == NULL)
		perror("打开userdata文件夹失败!\n");
        
	//2. 切换到目录下。
	chdir("./user_data");
    
	//3. 不断读取目录下的文件名。
	struct dirent *ep = NULL;

	while(1)
	{   
		ep = readdir(dp);
        
		if(ep == NULL) //读取完整个目录
		{
			break;
		}
		
		if(ep->d_name[0] == '.')
		{
			continue;
		}
		read_file(head,ep->d_name);
	}
	
	//4. 切换到上一级目录。
	chdir("..");

	
	//5. 关闭目录
	closedir(dp);
	
	return;
}

//显示单个用户信息
void printInfomation(struct OrdinaryPassNode *Ordinary_passenger_pos, int connfd)
{
	
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"名字:%s\t",Ordinary_passenger_pos->info.name);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"身份证号码:%s\t",Ordinary_passenger_pos->info.id);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"密码:%s\t",Ordinary_passenger_pos->info.passwd);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"支付密码:%s\t",Ordinary_passenger_pos->info.pay_passwd);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"年龄:%d\t",Ordinary_passenger_pos->info.age);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"电话:%s\n",Ordinary_passenger_pos->info.phone_number);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"密保问题:%s\t",Ordinary_passenger_pos->info.question);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"密保答案:%s\t",Ordinary_passenger_pos->info.answer);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"账户余额:%d\t",Ordinary_passenger_pos->info.balance);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"vip:%d\t",Ordinary_passenger_pos->info.vip);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"积分:%d\n",Ordinary_passenger_pos->info.integral);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"--------------------------------------------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
}

//遍历所有用户信息
void ShowAllUsers(struct OrdinaryPassNode *Ordinary_passenger_list_head, int connfd)
{
	struct OrdinaryPassNode *pos;

    list_for_each_entry(pos,&(Ordinary_passenger_list_head-> Ordinary_passenger_list),  Ordinary_passenger_list)
    {
        printInfomation(pos, connfd);
    }	
}

//显示余额
void CheckBalance(struct OrdinaryPassNode *Ordinary_passenger_pos, int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"名字:%s\t",Ordinary_passenger_pos->info.name);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"账户余额:%d\t",Ordinary_passenger_pos->info.balance);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"vip:%d\t",Ordinary_passenger_pos->info.vip);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"积分:%d\n",Ordinary_passenger_pos->info.integral);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"-------------------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);

}

//注册时创建文件夹
int FriendDir(char *name)
{
	char dirname[30];
	
	sprintf(dirname,"%s",name);
	
	chdir("./friends/");
	
	if(access(dirname,F_OK))
	{
		mkdir(dirname,0777);
	}
	
	chdir("../");
	
	return 0;
}

int PYQ(char *name)
{
	char dirname[30];
	
	sprintf(dirname,"%s",name);
	
	chdir("./pyq/");
	
	if(access(dirname,F_OK))
	{
		mkdir(dirname,0777);
	}
	
	chdir("../");
	
	return 0;
}

//注册
int registerPassageInformation(struct OrdinaryPassNode *Ordinary_passenger_list_head, int connfd)
{
    struct OrdinaryPassNode *new_node;

    new_node = QequestLinkInitNode();
	
	char phone_number[20];
	char pay_passwd[8];
	char buf[50];
	int age;
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"请输入你的名字:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	//scanf("%s",new_node->info.name);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(new_node->info.name,parting(buf));
	
	printf("name %s",buf);
	
	if(FindUsers(Ordinary_passenger_list_head, new_node->info.name) != NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"您已注册，请登录\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入你的密码:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(new_node->info.passwd,parting(buf));
	//scanf("%s",new_node->info.passwd);
	
	while(1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"请输入你的支付密码:\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		
		strcpy(pay_passwd,buf);
		
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"请再次输入你的支付密码:\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		
		if(strcmp(pay_passwd,buf) == 0)
		{
			strcpy(new_node->info.pay_passwd,parting(buf));
			break;
		}
		else
		{
			printf("两次密码不一样，请再次输入\n");
			printf("请重新\n");
		}
		
	}
	
	while(1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"请输入你的年龄:\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		
		strcpy(buf,parting(buf));
		
		age = atoi(buf);
		
		new_node->info.age = age;
		
		if(new_node->info.age < 150)
		{
			break;
		}
		else
		{
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"你确定你有这么老?\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"请重新输入\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
		}
		
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入你的身份证号码:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(new_node->info.id,parting(buf));
	
	if(FindUserID(Ordinary_passenger_list_head,new_node->info.id) != NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"此身份证号码已被注册\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	while(1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"请输入你的电话:\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		
		strcpy(new_node->info.phone_number,parting(buf));

		
		if(FindUserNum(Ordinary_passenger_list_head, new_node->info.phone_number) != NULL)
		{
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"此号码已被注册\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			return -1;
			
		}
		if(strlen(new_node->info.phone_number) == 11)
		{
			break;	
		}
		else
		{
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"电话号码位数不对\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"注册失败\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"请重新\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
		}	
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入你的密保问题:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(new_node->info.question,parting(buf));
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入你的密保答案:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(new_node->info.answer,parting(buf));
	printf("ans= %s",new_node->info.answer);
	
    new_node->info.balance = 0;   //初始化余额为0
	
	new_node->info.vip = 0;			//初始vip标志位为0
	
	new_node->info.integral = 0;	 //初始化积分为0

    InsertPassTailNode(Ordinary_passenger_list_head, new_node);

    FriendDir(new_node->info.name);

    PYQ(new_node->info.name);
	
    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",new_node->info.name);
    printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									new_node->info.name,
																							new_node->info.id,
																							new_node->info.age,
																							new_node->info.phone_number,
																							new_node->info.passwd,
																							new_node->info.pay_passwd,
																							new_node->info.	question,
																							new_node->info.answer,
																							new_node->info.balance,
																							new_node->info.vip,
																							new_node->info.integral);

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    
}

//登录初始化头节点
struct login_user *userListNode(void)
{
    struct login_user *new_node;

    new_node = malloc(sizeof(struct login_user));
    if(new_node == NULL)
    {
        perror("申请内存失败");
        return NULL;
    }

    INIT_LIST_HEAD(&(new_node->login_user_list));//将小个结构体的上下指针指向自己
    return new_node;
}

//遍历所有登陆者信
int allLoginUsr(struct login_user *login_user_list_head, char *name)
{
	struct login_user *pos;

    list_for_each_entry(pos,&(login_user_list_head->login_user_list),  login_user_list)
    {
		printf("login name %s\n",pos->name);
        if(strcmp(pos->name,name) == 0)
		{
			//printf("login name %s\n",pos->name);
			return -1;
		}
		
    }	
	return 0;
}

//登录尾插
void loginUserListNodeTail(struct login_user *login_user_list_head, struct login_user *login_user_insert_node)
{  
    list_add_tail(&(login_user_insert_node->login_user_list), &(login_user_list_head->login_user_list));
}

//判断是否登录成功并将用户信息存进登录链表
int loginIn(struct OrdinaryPassNode *Ordinary_passenger_list_head, struct OrdinaryPassNode *login_in_list_head, int connfd, struct login_user *login_user_list_head)
{
	
	struct login_user *new_node;

    new_node = userListNode();
	
	char name[30] = {0};
	char passwd[30] = {0};
	char buf[30];
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入账号:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(name,parting(buf));
	
	struct OrdinaryPassNode *Ordinary_passenger_pos;
	
	Ordinary_passenger_pos = FindUsers(Ordinary_passenger_list_head, name);
		
	if(Ordinary_passenger_pos == NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		printf(sendbuf,"没有此账号，请注册\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	if(allLoginUsr(login_user_list_head, name) == -1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"你已经登陆过了\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
		
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入密码:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(passwd,parting(buf));
	
	if(strcmp(passwd,Ordinary_passenger_pos->info.passwd) != 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"密码错误\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	
	stpcpy(login_in_list_head->info.name,Ordinary_passenger_pos->info.name);
	stpcpy(login_in_list_head->info.id,Ordinary_passenger_pos->info.id);
	stpcpy(login_in_list_head->info.phone_number,Ordinary_passenger_pos->info.phone_number);
	stpcpy(login_in_list_head->info.passwd,Ordinary_passenger_pos->info.passwd);
	stpcpy(login_in_list_head->info.pay_passwd,Ordinary_passenger_pos->info.pay_passwd);
	stpcpy(login_in_list_head->info.question,Ordinary_passenger_pos->info.question);
	stpcpy(login_in_list_head->info.answer,Ordinary_passenger_pos->info.answer);
	login_in_list_head->info.balance = Ordinary_passenger_pos->info.balance;
	login_in_list_head->info.vip = Ordinary_passenger_pos->info.vip;
	login_in_list_head->info.integral = Ordinary_passenger_pos->info.integral;
	login_in_list_head->info.age = Ordinary_passenger_pos->info.age;
	
	stpcpy(new_node->name,Ordinary_passenger_pos->info.name);
	
	new_node->connfd = connfd;

    loginUserListNodeTail(login_user_list_head, new_node);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"登录成功\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	return 0;
	
}

//返回登录用户的信息
struct OrdinaryPassNode *searchLoginInUser(struct OrdinaryPassNode *Ordinary_passenger_list_head, struct OrdinaryPassNode *login_in_list_head)
{
	struct OrdinaryPassNode *pos;

    list_for_each_entry(pos, &Ordinary_passenger_list_head->Ordinary_passenger_list,Ordinary_passenger_list)
    {    
        if(strcmp(pos->info.name,login_in_list_head->info.name) == 0)
        {   
			
            return pos;
        }
    }
    return NULL;
}

//修改用户信息
int passageInformation(struct OrdinaryPassNode *Ordinary_passenger_list_head, struct OrdinaryPassNode *login_in_list_head, int connfd)
{
	
	struct OrdinaryPassNode *Ordinary_passenger_pos;
	Ordinary_passenger_pos = searchLoginInUser(Ordinary_passenger_list_head, login_in_list_head);//获取登陆者信息
	
	char old_pay_passwd[8];
	char new_pay_passwd[8];
	char new_pay_passwd_twice[8];
	int a;
	char phone_number[20];
	int age;
	char old_answer[30];
	char new_question[30];
	char new_answer[30];
	char buf[50];
	
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"请选择你要修改的信息:1、电话号码  2、支付密码  3、年龄  4、验证问题\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		
		a = atoi(parting(buf));
		
		switch(a)
		{
			case 1:
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"请输入新的电话号码\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(buf,sizeof(buf));
			recv(connfd,buf,sizeof(buf),0);
			
			strcpy(phone_number,parting(buf));
			
			if(strlen(phone_number) != 11)
			{
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"位数不正确\n");
				send(connfd,sendbuf,strlen(sendbuf),0);
				break;
			}
			strcpy(Ordinary_passenger_pos->info.phone_number,phone_number);
			strcpy(login_in_list_head->info.phone_number,phone_number);
                printInfomation(Ordinary_passenger_pos, connfd);
			break;
			
			case 2:
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"请输入旧的支付密码\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(buf,sizeof(buf));
			recv(connfd,buf,sizeof(buf),0);
			
			strcpy(old_pay_passwd,parting(buf));
			
			if(strcmp(old_pay_passwd,Ordinary_passenger_pos->info.pay_passwd) != 0)
			{
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"输入原支付密码错误\n");
				send(connfd,sendbuf,strlen(sendbuf),0);
				break;
			}
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"请输入新的支付密码\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(buf,sizeof(buf));
			recv(connfd,buf,sizeof(buf),0);
			
			strcpy(new_pay_passwd,parting(buf));
			
			
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"请再次输入新的支付密码\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(buf,sizeof(buf));
			recv(connfd,buf,sizeof(buf),0);
			
			strcpy(new_pay_passwd_twice,parting(buf));
			
			
			if(strcmp(new_pay_passwd,new_pay_passwd_twice) != 0)
			{
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"确认新支付密码错误\n");
				send(connfd,sendbuf,strlen(sendbuf),0);
				break;
			}	
			strcpy(Ordinary_passenger_pos->info.pay_passwd,new_pay_passwd);
			strcpy(login_in_list_head->info.pay_passwd,new_pay_passwd);
                printInfomation(Ordinary_passenger_pos, connfd);
			break;
			
			case 3:
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"请输入修改后的年龄\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(buf,sizeof(buf));
			recv(connfd,buf,sizeof(buf),0);
			
			age = atoi(parting(buf));
			
			Ordinary_passenger_pos->info.age = age;
			login_in_list_head->info.age = age;
                printInfomation(Ordinary_passenger_pos, connfd);
			break;
			
			case 4:
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"问题%s\n",Ordinary_passenger_pos->info.question);
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"请输入原来的答案\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(buf,sizeof(buf));
			recv(connfd,buf,sizeof(buf),0);
			
			strcpy(old_answer,parting(buf));
			
			
			if(strcmp(old_answer,Ordinary_passenger_pos->info.answer) != 0)
			{
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"答案错误\n");
				send(connfd,sendbuf,strlen(sendbuf),0);
				break;
			}
			
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"请输入新的问题\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(buf,sizeof(buf));
			recv(connfd,buf,sizeof(buf),0);
			strcpy(new_question,parting(buf));
			
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"请输入新的答案\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			
			bzero(buf,sizeof(buf));
			recv(connfd,buf,sizeof(buf),0);
			strcpy(new_answer,parting(buf));
			
			strcpy(Ordinary_passenger_pos->info.question,new_question);
			strcpy(login_in_list_head->info.question,new_question);
			strcpy(Ordinary_passenger_pos->info.answer,new_answer);
			strcpy(login_in_list_head->info.answer,new_answer);
                printInfomation(Ordinary_passenger_pos, connfd);
			break;
		}
		


    

    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",Ordinary_passenger_pos->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									Ordinary_passenger_pos->info.name,
																							Ordinary_passenger_pos->info.id,
																							Ordinary_passenger_pos->info.age,
																							Ordinary_passenger_pos->info.phone_number,
																							Ordinary_passenger_pos->info.passwd,
																							Ordinary_passenger_pos->info.pay_passwd,
																							Ordinary_passenger_pos->info.	question,
																							Ordinary_passenger_pos->info.answer,
																							Ordinary_passenger_pos->info.balance,
																							Ordinary_passenger_pos->info.vip,
																							Ordinary_passenger_pos->info.integral);

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        //perror("打开用户信息文件失败(修改用户信息):");
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"打开用户信息文件失败(修改用户信息):");
		send(connfd,sendbuf,strlen(sendbuf),0);
    }
    
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    
}

//重置密码
int reset_passwd(struct OrdinaryPassNode *Ordinary_passenger_list_head, int connfd)
{
	char name[30];
	
	char answer[30];
	
	char passwd[30];
	
	char buf[50];
	
	struct OrdinaryPassNode *pos;
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入你的账号:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(name,parting(buf));
	

	pos = FindUsers(Ordinary_passenger_list_head, name);
	
	if(pos == NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,("别乱输账号(重置密码)\n"));
		send(connfd,sendbuf,strlen(sendbuf),0);
		
		return -1;
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"你的密保问题:%s\n",pos->info.question);
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入你的密保答案\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(answer,parting(buf));
	
	
	if(strcmp(answer,pos->info.answer) != 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"答案错误\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
		
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入新密码\n");	
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(passwd,parting(buf));
		
	strcpy(pos->info.passwd,passwd);
	
	char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",pos->info.name);
    printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									pos->info.name,
																							pos->info.id,
																							pos->info.age,
																							pos->info.phone_number,
																							pos->info.passwd,
																							pos->info.pay_passwd,
																							pos->info.	question,
																							pos->info.answer,
																							pos->info.balance,
																							pos->info.vip,
																							pos->info.integral);

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"打开用户信息文件失败\n");	
		send(connfd,sendbuf,strlen(sendbuf),0);
    }
    
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"修改成功\n");	
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	return 0;
	
}

//寻找登录链表
struct login_user *find_login_user(struct login_user *login_user_list_head,char *name)
{
	 struct login_user *pos,*n;
   
    list_for_each_entry_safe(pos,n, &login_user_list_head->login_user_list, login_user_list)
    {
        if(strcmp(pos->name,name) == 0)
        {
            return pos;
        }
        
    }
	return NULL;
	
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

//航班信息结构体小
struct flight_num_pas 
{
    char flight_number[20];
    char departure[20];
    char destination[20];
    char date[20];
    char model[20];
    char time[20];
    int price;
    int votes;//余票

};

//航班信息结构体大
struct flight_num_pas_node
{
    struct flight_num_pas info;
    struct list_head flight_num;

};	

//通过航班号寻找航班信息
struct flight_num_pas_node *pass_through_flight_number_pos(struct flight_num_pas_node *flight_num_list_head,char *flight_number)
{  

    struct flight_num_pas_node *pos;
	
    list_for_each_entry(pos, &flight_num_list_head->flight_num, flight_num)
    {		
		
        if(strcmp(pos->info.flight_number,flight_number) == 0)
        {
			printf("%s\n",pos->info.flight_number);
            return pos;
        }
        
    }

    return NULL;
}

//初始化航班信息头节点
struct flight_num_pas_node *request_link_flight_num_list_node(void)
{
    struct flight_num_pas_node *new_node;

    new_node = malloc(sizeof(struct flight_num_pas_node));
    if(new_node == NULL)
    {
        perror("申请内存失败");
        return NULL;
    }

    INIT_LIST_HEAD(&(new_node->flight_num));//将小个结构体的上下指针指向自己
    return new_node;
}

//航班信息尾插
void insert_flight_num_list_node_tail(struct flight_num_pas_node *flight_num_list_head, struct flight_num_pas_node *flight_num_insert_node)
{  
    list_add_tail(&(flight_num_insert_node->flight_num), &(flight_num_list_head->flight_num));
}	

//录入航班
int create_flight_num_information(struct flight_num_pas_node *flight_num_list_head,int connfd)
{
    struct flight_num_pas_node *new_node;

    new_node = request_link_flight_num_list_node();
	
	char flight_number[50];
	
	char buf[50];
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入航班号:\n");	
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(flight_number,parting(buf));
	
	
	if(pass_through_flight_number_pos(flight_num_list_head,flight_number) != NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"已有此航班号\n");	
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	strcpy(new_node->info.flight_number,flight_number);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"出发地\n");	
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(new_node->info.departure,parting(buf));
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"目的地\n");	
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(new_node->info.destination,parting(buf));
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"日期\n");	
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(new_node->info.date,parting(buf));
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"机型\n");	
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(new_node->info.model,parting(buf));
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"时间\n");	
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	strcpy(new_node->info.time,parting(buf));
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"价格\n");	
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	new_node->info.price = atoi(parting(buf));
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"余票\n");	
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	new_node->info.votes = atoi(parting(buf));
	
	
   insert_flight_num_list_node_tail(flight_num_list_head,new_node);

    char filename[100] = {0};
	sprintf(filename,"./data/%s.txt",new_node->info.flight_number);
    printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%s,%s,%s,%s,%d,%d",									new_node->info.flight_number,
																							new_node->info.departure,
																							new_node->info.destination,
																							new_node->info.date,
																							new_node->info.model,
																							new_node->info.time,
																							new_node->info.	price,
																							new_node->info.votes
																							);
																							
    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开机票信息文件失败");
    }
    
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
	
	return 0;
    
}
	
//分割航班信息文件中中的数据
void flight_num_strtok_fun(struct flight_num_pas_node *flight_num_list_head,char *buf)
{
	//1. 为新节点申请空间。
	struct flight_num_pas_node *new;

    new = request_link_flight_num_list_node();
	
	//2. 分割字符串，为新节点数据域指针域赋值。
	char seqs[] = ",";
	
    char *tmp;

	tmp = strtok(buf,seqs);
	strcpy(new->info.flight_number,tmp);

    tmp = strtok(NULL,seqs);
	strcpy(new->info.departure,tmp);

	tmp = strtok(NULL,seqs);
	strcpy(new->info.destination,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.date,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.model,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.time,tmp);
	
	tmp = strtok(NULL,seqs);
	new->info.price = atoi(tmp);

	tmp = strtok(NULL,seqs);
	new->info.votes = atoi(tmp);

    insert_flight_num_list_node_tail(flight_num_list_head,new);
    
	return;
}

//读文件
void read_flight_num_file(struct flight_num_pas_node *flight_num_list_head,char *filename)
{
	//1. 打开文件。
	FILE *fp = fopen(filename,"a+");
	if(fp == NULL)
		perror("打开文件错误!\n");
	
	//2. 读取文件数据。
	char buf[200] = {0};
	fread(buf,20,10,fp);
	
	//3. 关闭文件。
	fclose(fp);
	
	//4. 分割数据。
	flight_num_strtok_fun(flight_num_list_head,buf);
	
	return;
}

//初始化已注册（在文件夹中的）航班信息
void init_flight_num_old_usr(struct flight_num_pas_node *flight_num_list_head)
{
	//1. 打开目录。

    CheckPath();
	DIR* dp = opendir("./data");
	
	
	if(dp == NULL)
		perror("打开data文件夹失败!\n");
        
	//2. 切换到目录下。
	chdir("./data");
    
	//3. 不断读取目录下的文件名。
	struct dirent *ep = NULL;

	while(1)
	{   
		ep = readdir(dp);
        
		if(ep == NULL) //读取完整个目录
		{
			break;
		}
		
		if(ep->d_name[0] == '.')
		{
			continue;
		}
        
		
		read_flight_num_file(flight_num_list_head,ep->d_name);	
	}
	
	//4. 切换到上一级目录。
	chdir("..");

	
	//5. 关闭目录
	closedir(dp);
	
	return;
}

//初始化已删除（在文件夹中的）航班信息
void flightNumOldUsr(struct flight_num_pas_node *rm_flight_num_list_head)
{
	//1. 打开目录。

    CheckPath();
	DIR* dp = opendir("./rm_data");
	
	
	if(dp == NULL)
		perror("打开rm_data文件夹失败!\n");
        
	//2. 切换到目录下。
	chdir("./rm_data");
    
	//3. 不断读取目录下的文件名。
	struct dirent *ep = NULL;

	while(1)
	{   
		ep = readdir(dp);
        
		if(ep == NULL) //读取完整个目录
		{
			break;
		}
		
		if(ep->d_name[0] == '.')
		{
			continue;
		}
        
		
		read_flight_num_file(rm_flight_num_list_head,ep->d_name);	
	}
	
	//4. 切换到上一级目录。
	chdir("..");

	
	//5. 关闭目录
	closedir(dp);
	
	return;
}
	
//打印出一个航班信息
void flightNumInformation(struct flight_num_pas_node *flight_num_pos, int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"航班号:%s\t",flight_num_pos->info.flight_number);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"出发地:%s\t",flight_num_pos->info.departure);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"目的地:%s\t",flight_num_pos->info.destination);
	send(connfd,sendbuf,strlen(sendbuf),0);bzero(sendbuf,sizeof(sendbuf));
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"日期:%s\n",flight_num_pos->info.date);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"机型:%s\t",flight_num_pos->info.model);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"时间:%s\t",flight_num_pos->info.time);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"价格:%d\t",flight_num_pos->info.price);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"余票:%d\n",flight_num_pos->info.votes);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"-------------------------------------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);

}

//显示所有航班信息
void allFlightNum(struct flight_num_pas_node *flight_num_list_head, int connfd)
{
	struct flight_num_pas_node *pos;

    list_for_each_entry(pos, &flight_num_list_head->flight_num, flight_num)
    {
        flightNumInformation(pos, connfd);
    }
}

//通过目的地寻找航班
int destinationFindInfoListNode(struct flight_num_pas_node *flight_num_list_head, int connfd)
{  

	
	int count = 0;
    struct flight_num_pas_node *pos;
    char destination[20];
	char buf[50];
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"请输入你的目的地：\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(destination,parting(buf));

    list_for_each_entry(pos, &flight_num_list_head->flight_num, flight_num)
    {
        if(strcmp(pos->info.destination, destination) == 0)
        {
            flightNumInformation(pos, connfd);
			count++;
            //return pos; 
        }
    }
	return count;

    //return NULL;
}

//通过日期寻找航班信息
int dateFindInfoListNode(struct flight_num_pas_node *flight_num_list_head, int connfd)
{  
	int count = 0;
    struct flight_num_pas_node *pos;
    char date[20];
	char buf[50];
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"请输入你的出发日期：\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(date,parting(buf));
	
    list_for_each_entry(pos, &flight_num_list_head->flight_num, flight_num)
    {
        if(strcmp(pos->info.date,date) == 0)
        {
            flightNumInformation(pos, connfd);
			count++;
            //return pos; 
        }
    }
	return count;

    //return NULL;
}

//通过机型寻找航班信息
int flightModelFindInfoListNode(struct flight_num_pas_node *flight_num_list_head, int connfd)
{  
	int count = 0;
    struct flight_num_pas_node *pos;
    char model[20];
    char buf[50];
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"请输入你想乘坐的机型(A,B,C)：\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(model,parting(buf));

    list_for_each_entry(pos, &flight_num_list_head->flight_num, flight_num)
    {
        if(strcmp(pos->info.model,model) == 0)
        {
            flightNumInformation(pos, connfd);
			count++;
            //return pos; 
        }
    }
	return count;

    //return NULL;
}

//通过机票价格寻找航班信息
int passThroughFlightPriceFindInfoListNode(struct flight_num_pas_node *flight_num_list_head, int connfd)
{  

    struct flight_num_pas_node *pos;
    int price;
    int count = 0;
	char buf[50];
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"请输入价格：\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	price = atoi(parting(buf));

    list_for_each_entry(pos, &flight_num_list_head->flight_num, flight_num)
    {
        if(pos->info.price == price)
        {
            flightNumInformation(pos, connfd);
			count++;
            //return pos;
        }
    }
	return count;

    //return NULL;
}

//通过航班号寻找航班信息
int numberFindInfoListNode(struct flight_num_pas_node *flight_num_list_head, int connfd)
{  
	int count = 0;
    struct flight_num_pas_node *pos;
    char flight_number[20];
	char buf[50];
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"请输入航班号：\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(flight_number,parting(buf));

    list_for_each_entry(pos, &flight_num_list_head->flight_num, flight_num)
    {
        if(strcmp(pos->info.flight_number,flight_number) == 0)
        {
            flightNumInformation(pos, connfd);
			count++;
            //return pos;
        }
        
    }
	return count;

    //return NULL;
}

//移动航班信息件
int numFile(struct flight_num_pas_node *flight_num_pos, int connfd)
{      
    char buf[30];
    strcpy(buf,flight_num_pos->info.flight_number);

    char cmd[200]={0};
    
    sprintf(cmd,"cp ./data/%s.txt ./rm_data/",buf);

    system(cmd);
	
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"移动航班文件成功\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
    return 0;

}

//删文航班信息件
int aFlightNumFile(struct flight_num_pas_node *flight_num_pos, int connfd)
{      
    char buf[30];
    strcpy(buf,flight_num_pos->info.flight_number);

    char cmd[200]={0};
    
    sprintf(cmd,"rm ./data/%s.txt",buf);

    system(cmd);
	
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"删除航班文件成功\n");
	send(connfd,sendbuf,strlen(sendbuf),0);

    return 0;

}

//把已删除航班放入链表
int numInformation(struct flight_num_pas_node *rm_flight_num_list_head, struct flight_num_pas_node *flight_num_pos)
{
    struct flight_num_pas_node *new_node;

    new_node = request_link_flight_num_list_node();
	
	strcpy(new_node->info.flight_number,flight_num_pos->info.flight_number);
	
	strcpy(new_node->info.departure,flight_num_pos->info.departure);
	
	strcpy(new_node->info.destination,flight_num_pos->info.destination);
	
	strcpy(new_node->info.date,flight_num_pos->info.date);
	
	strcpy(new_node->info.model,flight_num_pos->info.model);
	
	strcpy(new_node->info.time,flight_num_pos->info.time);
	
	new_node->info.price = flight_num_pos->info.price;
	
	new_node->info.votes = flight_num_pos->info.votes;
	
   insert_flight_num_list_node_tail(rm_flight_num_list_head,new_node);

	
	return 0;
    
}

//删除航班信息
struct flight_num_pas_node *deleteFlightNumber(struct flight_num_pas_node *flight_num_list_head, char *flight_number, struct flight_num_pas_node *rm_flight_num_list_head)
{
	 struct flight_num_pas_node *pos,*n;
   
    list_for_each_entry_safe(pos,n, &flight_num_list_head->flight_num, flight_num)
    {
        if(strcmp(pos->info.flight_number,flight_number) == 0)
        {
			
            return pos;
        }
        
    }
	return NULL;
	
}



//实名认证结构体小
struct Verified_identity_pas
{
    char name[20];
    char id[20];
    int identity_info;
	int doctor_or_nurse;
	
};

//实名认证结构体大
struct Verified_identity_pas_node
{
    struct Verified_identity_pas info;
    struct list_head Verified_list;

};

//初始化实名认证头节点
struct Verified_identity_pas_node *request_Verified_link_list_node(void)
{
    struct Verified_identity_pas_node *new_node;

    new_node = malloc(sizeof(struct OrdinaryPassNode));
    if(new_node == NULL)
    {
        perror("申请内存失败");
        return NULL;
    }

    INIT_LIST_HEAD(&(new_node->Verified_list));//将小个结构体的上下指针指向自己
    return new_node;
}

//实名认证尾插
void insert_Verified_list_node_tail(struct Verified_identity_pas_node *Verified_identity_list_head, struct Verified_identity_pas_node *Verified_identity_insert_node)
{  
    list_add_tail(&(Verified_identity_insert_node->Verified_list), &(Verified_identity_list_head->Verified_list));
}

//实名认证分割
void Verified_identity_strtok_fun(struct Verified_identity_pas_node *Verified_identity_list_head,char *buf)
{
	//1. 为新节点申请空间。
	struct Verified_identity_pas_node *new;

    new = request_Verified_link_list_node();
	
	//2. 分割字符串，为新节点数据域指针域赋值。
	char seqs[] = ",";
	
    char *tmp;

	tmp = strtok(buf,seqs);
	strcpy(new->info.name,tmp);

    tmp = strtok(NULL,seqs);
	strcpy(new->info.id,tmp);
	
	tmp = strtok(NULL,seqs);
	new->info.identity_info = atoi(tmp);
	
	tmp = strtok(NULL,seqs);
	new->info.doctor_or_nurse = atoi(tmp);
   
    insert_Verified_list_node_tail(Verified_identity_list_head,new);
	
	return;
}

//读文件
void Verified_identity_read_file(struct Verified_identity_pas_node *Verified_identity_list_head,char *filename)
{
	//1. 打开文件。
	FILE *fp = fopen(filename,"r");
	if(fp == NULL)
		perror("打开文件错误!\n");
	
	//2. 读取文件数据。
	char buf[200] = {0};
	fread(buf,20,10,fp);
	
	//3. 关闭文件。
	fclose(fp);
	
	//4. 分割数据。
	Verified_identity_strtok_fun(Verified_identity_list_head,buf);
	
	return;
}

//实名认证初始化
void Verified_identity_init(struct Verified_identity_pas_node *Verified_identity_list_head)
{
	//1. 打开目录。
	DIR* dp = opendir("./Verified_identity_data");
	if(dp == NULL)
		perror("打开文件夹失败!\n");
        
	//2. 切换到目录下。
	chdir("./Verified_identity_data");
    
	//3. 不断读取目录下的文件名。
	struct dirent *ep = NULL;

	while(1)
	{   
		ep = readdir(dp);
        
		if(ep == NULL) //读取完整个目录
		{
			break;
		}
		
		if(ep->d_name[0] == '.')
		{
			continue;
		}
        
		
		Verified_identity_read_file(Verified_identity_list_head,ep->d_name);	
	}
	
	//4. 切换到上一级目录。
	chdir("..");

	
	//5. 关闭目录
	closedir(dp);
	
	return;
}

//打印一个用户的实名认证
void printer_check_identity_information(struct Verified_identity_pas_node *Verified_identity_pos,int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"名字:%s\n",Verified_identity_pos->info.name);
	send(connfd,sendbuf,strlen(sendbuf),0);bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"身份证号码:%s\n",Verified_identity_pos->info.id);
	send(connfd,sendbuf,strlen(sendbuf),0);bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"特殊身份:%d\n",Verified_identity_pos->info.identity_info);
	send(connfd,sendbuf,strlen(sendbuf),0);bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"医生或护士:%d\n",Verified_identity_pos->info.doctor_or_nurse);
	send(connfd,sendbuf,strlen(sendbuf),0);bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"-------------------------------------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);

}

//显示全部用户的实名认证
void show_all_check_identity_information(struct Verified_identity_pas_node *Verified_identity_list_head,int connfd)
{
	struct Verified_identity_pas_node *pos;

    list_for_each_entry(pos,&(Verified_identity_list_head->Verified_list),Verified_list)
	{
        printer_check_identity_information(pos,connfd);
    }	
	
}

//显示自己的实名认证
void find_check_identity_information(struct Verified_identity_pas_node *Verified_identity_list_head, struct OrdinaryPassNode *login_in_list_head, int connfd)
{
	struct Verified_identity_pas_node *pos;
	

    list_for_each_entry(pos,&(Verified_identity_list_head->Verified_list),Verified_list)
	{		
		if(strcmp(pos->info.name,login_in_list_head->info.name) == 0)
		{
			printer_check_identity_information(pos,connfd);
			
		}
        
    }	
	
}


//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//-------------------------------------------------购票-------------------------------------------------
//----------------------------------------------------------------------------------------------------

//好友链表节点
struct friends_info_list{
	
	int friends_connfd;
	char friends_name[50];
	int online;
	int blacklist;
	struct list_head friends_list;
};

//购票结构体小
struct buy_ticket
{
    char name[20];
    char id[20];
    char phone_number[20]; 
    char flight_number[20];
    char departure[20];
    char destination[20];
    char date[20];
    char model[20];
    char time[20];
    int price;
	char seat[20];
    int age;
	int insurance;
};

//购票结构体大
struct buy_ticket_node
{
    struct buy_ticket info;
    struct list_head pes_buy_ticket;

};

//买票信息创建新的节点
struct buy_ticket_node *request_buy_ticket_node(void)
{
    struct buy_ticket_node *new_node;

    new_node = malloc(sizeof(struct buy_ticket_node));
    if(new_node == NULL)
    {
        perror("申请内存失败");
        return NULL;
    }

    INIT_LIST_HEAD(&(new_node->pes_buy_ticket));//将小个结构体的上下指针指向自己
    return new_node;
}

//购票尾插
void insert_buy_ticket_list_node_tail(struct buy_ticket_node *buy_ticket_list_head, struct buy_ticket_node *buy_ticket_insert_node)
{  
    list_add_tail(&(buy_ticket_insert_node->pes_buy_ticket), &(buy_ticket_list_head->pes_buy_ticket));
}

//购票读文件创链表
void buy_ticket_strtok_fun(struct buy_ticket_node *buy_ticket_list_head,char *buf)
{
	//1. 为新节点申请空间。
	struct buy_ticket_node *new;

    new = request_buy_ticket_node();
	
	//2. 分割字符串，为新节点数据域指针域赋值。
	char seqs[] = ",";
	
    char *tmp;

	tmp = strtok(buf,seqs);
	strcpy(new->info.name,tmp);
	
    tmp = strtok(NULL,seqs);
	strcpy(new->info.id,tmp);
    
	tmp = strtok(NULL,seqs);
	new->info.age = atoi(tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.phone_number,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.flight_number,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.departure,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->info.destination,tmp);

    tmp = strtok(NULL,seqs);
	strcpy(new->info.date,tmp);

    tmp = strtok(NULL,seqs);
	strcpy(new->info.model,tmp);

    tmp = strtok(NULL,seqs);
	strcpy(new->info.time,tmp);
	
	tmp = strtok(NULL,seqs);
	new->info.price = atoi(tmp);
    
    tmp = strtok(NULL,seqs);
	strcpy(new->info.seat,tmp);
	
	
	tmp = strtok(NULL,seqs);
	new->info.insurance = atoi(tmp);
	
	
    insert_buy_ticket_list_node_tail(buy_ticket_list_head,new);
	
	return;
}

//购票读文件
void buy_ticket_read_file(struct buy_ticket_node *buy_ticket_list_head,char *filename)
{
	//1. 打开文件。
	FILE *fp = fopen(filename,"r");
	if(fp == NULL)
		perror("打开文件错误!\n");
	
	//2. 读取文件数据。
	char buf[200] = {0};
	fread(buf,20,10,fp);
	
	//3. 关闭文件。
	fclose(fp);
	
	//4. 分割数据。
	buy_ticket_strtok_fun(buy_ticket_list_head,buf);
	
	return;
}

//购票初始化
void buy_ticket_init(struct buy_ticket_node *buy_ticket_list_head)
{
	//1. 打开目录。
	DIR* dp = opendir("./ticket_data");
	if(dp == NULL)
		perror("打开文件夹失败!\n");
        
	//2. 切换到目录下。
	chdir("./ticket_data");
    
	//3. 不断读取目录下的文件名。
	struct dirent *ep = NULL;

	while(1)
	{   
		ep = readdir(dp);
        
		if(ep == NULL) //读取完整个目录
		{
			break;
		}
		
		if(ep->d_name[0] == '.')
		{
			continue;
		}
        
		
		buy_ticket_read_file(buy_ticket_list_head,ep->d_name);	
		
	}
	
	//4. 切换到上一级目录。
	chdir("..");
	
	
	//5. 关闭目录
	closedir(dp);
	
	return;
}

//判断支付密码是否正确
int pay_password(struct OrdinaryPassNode *login_in_list_head, int connfd)
{
	char pay_passwd[8];
	char buf[20];
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"请输入支付密码:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);bzero(sendbuf,sizeof(sendbuf));
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(pay_passwd,parting(buf));
	
	if(strcmp(login_in_list_head->info.pay_passwd,pay_passwd) == 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"支付密码正确\n");
		send(connfd,sendbuf,strlen(sendbuf),0);bzero(sendbuf,sizeof(sendbuf));
		return 0;
	}
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"密码错误\n");
	send(connfd,sendbuf,strlen(sendbuf),0);bzero(sendbuf,sizeof(sendbuf));
	return -1;
}

//购票通过航班号寻找航班信息
struct flight_num_pas_node *pass_through_flight_number_find_info_list_node_ticket(struct flight_num_pas_node *flight_num_list_head)
{  

    struct flight_num_pas_node *pos;
    char flight_number[20];
    printf("请输入航班号：\n");
    scanf("%s",flight_number);

    list_for_each_entry(pos, &flight_num_list_head->flight_num, flight_num)
    {
        if(strcmp(pos->info.flight_number,flight_number) == 0)
        {
            return pos;
        }
        
    }

    return NULL;
}

//查实名认证(购票)
int check_Verified(struct OrdinaryPassNode *login_in_list_head, struct Verified_identity_pas_node *Verified_identity_list_head)
{
    struct Verified_identity_pas_node *pos;
    list_for_each_entry(pos,&(Verified_identity_list_head->Verified_list),Verified_list)
	{
		if((strcmp(pos->info.name,login_in_list_head->info.name) == 0)&&(strcmp(pos->info.id,login_in_list_head->info.id) == 0))
		{
            printf("已经实名认证\n");
            return 0;    
		}
	}
    printf("还没实名认证\n");
    return -1;
}

//查实名认证特殊身份(购票)
int check_identity_info(struct OrdinaryPassNode *login_in_list_head,
								struct Verified_identity_pas_node *Verified_identity_list_head)
{
    struct Verified_identity_pas_node *pos;
    list_for_each_entry(pos,&(Verified_identity_list_head->Verified_list),Verified_list)
	{
		if((strcmp(pos->info.name,login_in_list_head->info.name) == 0)&&(strcmp(pos->info.id,login_in_list_head->info.id) == 0))
		{       
            if(pos->info.identity_info == 1)
            {
                printf("可半票购买\n");
                return 0;
            }
            printf("全票\n");
            return -1;
        }
    }
}

//查看是否重复购买同一个航班的两个位置
int check_ticket_buyer(struct buy_ticket_node *buy_ticket_list_head,char *flight_number,char *name)
{   

    struct buy_ticket_node *pos;
	list_for_each_entry(pos, &buy_ticket_list_head->pes_buy_ticket,pes_buy_ticket)
	{
		if((strcmp(pos->info.name,name) == 0) && (strcmp(pos->info.flight_number,flight_number) == 0))  //说明这个用户买过这一个航班的机票了
		{
            //printf("一个人坐两个位置这么顶?\n");
            return -1;
		}
	}

	return 0; 
}

//查看是否购有人购买了这一个位置
int check_ticket_seat(struct buy_ticket_node *buy_ticket_list_head,char *flight_number,char *seat,int connfd)
{   
	
    struct buy_ticket_node *pos;
	
	list_for_each_entry(pos, &buy_ticket_list_head->pes_buy_ticket,pes_buy_ticket)
	{	
		
		if((strcmp(pos->info.seat,seat) == 0) && 
					(strcmp(pos->info.flight_number,flight_number) == 0))  //说明这个用户买过这一个航班的机票了
		{
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"已经有人买了这个位置了\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
            return -1;
		}
	}

	return 0; 
}

//写入余票
int remaining_votes_info(struct flight_num_pas_node *flight_num_pos)
{   

    flight_num_pos->info.votes--;
 
    char filename[100] = {0};
	sprintf(filename,"./data/%s.txt",flight_num_pos->info.flight_number);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%s,%s,%s,%s,%d,%d",
                        flight_num_pos->info.flight_number,
                        flight_num_pos->info.departure,
                        flight_num_pos->info.destination,
                        flight_num_pos->info.date,
                        flight_num_pos->info.model,
                        flight_num_pos->info.time,
                        flight_num_pos->info.price,
                        flight_num_pos->info.votes);

   /* printf("%s,%s,%s,%s,%s,%s,%d,%d",
                        buy_ticket_pos->info.flight_number,
                        buy_ticket_pos->info.departure,
                        buy_ticket_pos->info.destination,
                        buy_ticket_pos->info.date,
                        buy_ticket_pos->info.model,
                        buy_ticket_pos->info.time,
                        buy_ticket_pos->info.price,
                        buy_ticket_pos->info.votes
                        );*/
    FILE *fp = fopen(filename,"w");
    
    if(fp == NULL)
    {
        perror("打开用户购票信息文件失败");
    }
    

    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);

    printf("修改余票成功\n");

}

//通过航班号寻找航班信息(买机票)
struct flight_num_pas_node *search_flight_num_info(struct flight_num_pas_node *flight_num_list_head,int connfd)
{  

    struct flight_num_pas_node *pos;
    char flight_number[20];
	char buf[50];
	
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"请输入航班号：\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(flight_number,parting(buf));
	

    list_for_each_entry(pos, &flight_num_list_head->flight_num, flight_num)
    {
        if(strcmp(pos->info.flight_number,flight_number) == 0)
        {
            return pos;
        }
    }
    return NULL;
}

//判断vip
int judging_the_identity(struct OrdinaryPassNode *login_in_list_head)
{
	if(login_in_list_head->info.vip == 1)
	{
		
		
		return 1;
		
	}
	if(login_in_list_head->info.vip == 2)
	{
		
		
		return 2;
		
	}
	return -1;
}

//买票扣款
int Operational_balance  (struct OrdinaryPassNode *Ordinary_passenger_pos, struct OrdinaryPassNode *login_in_list_head, int price, int connfd)
{

	if(login_in_list_head->info.balance < price)
	{
		
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"你不够钱喔\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		printf("你不够钱喔\n");
		return -1;
		
	}
	
    login_in_list_head->info.balance = login_in_list_head->info.balance - price;
    Ordinary_passenger_pos->info.balance = Ordinary_passenger_pos->info.balance - price;
    //printf("price = %d",loginIn->info.bal);

    

    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",login_in_list_head->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									login_in_list_head->info.name,
																							login_in_list_head->info.id,
																							login_in_list_head->info.age,
																							login_in_list_head->info.phone_number,
																							login_in_list_head->info.passwd,
																							login_in_list_head->info.pay_passwd,
																							login_in_list_head->info.	question,
																							login_in_list_head->info.answer,
																							login_in_list_head->info.balance,
																							login_in_list_head->info.vip,
																							login_in_list_head->info.integral);


    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    printf("扣款成功\n");
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
	return 0;
    
}

//买保险扣款
int Operational_balance_insurance  (struct OrdinaryPassNode *Ordinary_passenger_pos, struct OrdinaryPassNode *login_in_list_head, int price)
{


    login_in_list_head->info.balance = login_in_list_head->info.balance - price;
    Ordinary_passenger_pos->info.balance = Ordinary_passenger_pos->info.balance - price;
    //printf("price = %d",loginIn->info.bal);

    

    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",login_in_list_head->info.name);
    printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									login_in_list_head->info.name,
																							login_in_list_head->info.id,
																							login_in_list_head->info.age,
																							login_in_list_head->info.phone_number,
																							login_in_list_head->info.passwd,
																							login_in_list_head->info.pay_passwd,
																							login_in_list_head->info.	question,
																							login_in_list_head->info.answer,
																							login_in_list_head->info.balance,
																							login_in_list_head->info.vip,
																							login_in_list_head->info.integral);


    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    printf("保险扣款成功\n");
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    
}

//买票加积分
int Operational_integral(struct OrdinaryPassNode *Ordinary_passenger_pos, struct OrdinaryPassNode *login_in_list_head)
{


    login_in_list_head->info.integral = login_in_list_head->info.integral + 50;
    Ordinary_passenger_pos->info.integral = Ordinary_passenger_pos->info.integral + 50;
    //printf("price = %d",loginIn->info.bal);

    

    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",login_in_list_head->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									login_in_list_head->info.name,
																							login_in_list_head->info.id,
																							login_in_list_head->info.age,
																							login_in_list_head->info.phone_number,
																							login_in_list_head->info.passwd,
																							login_in_list_head->info.pay_passwd,
																							login_in_list_head->info.question,
																							login_in_list_head->info.answer,
																							login_in_list_head->info.balance,
																							login_in_list_head->info.vip,
																							login_in_list_head->info.integral);

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    printf("加积分成功\n");
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    
}

//买票
int buy_ticket_info(struct flight_num_pas_node *flight_num_list_head, struct OrdinaryPassNode *login_in_list_head,
                    struct buy_ticket_node *buy_ticket_list_head, struct Verified_identity_pas_node *Verified_identity_list_head,
                    struct OrdinaryPassNode *Ordinary_passenger_list_head, int connfd)
{   


    struct OrdinaryPassNode *Ordinary_passenger_pos;
    struct flight_num_pas_node *flight_num_pos;
	char seat[20] = {0};
	int line;
	char input_seat[20] = {0};
	char line_tmp[20] = {0};
	int ret;
	char buf[50];
    Ordinary_passenger_pos = searchLoginInUser(Ordinary_passenger_list_head, login_in_list_head);//获取登陆者信息

    flight_num_pos = search_flight_num_info(flight_num_list_head,connfd);//通过航班号获取里面航班信息并返回
    
	if(flight_num_pos == NULL)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"不要乱输\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
        return -1;
    }
    
    struct buy_ticket_node *new_node;

    new_node = request_buy_ticket_node();
	
	
	
    strcpy(new_node->info.flight_number,flight_num_pos->info.flight_number);
    strcpy(new_node->info.departure,flight_num_pos->info.departure);
    strcpy(new_node->info.destination,flight_num_pos->info.destination);
    strcpy(new_node->info.date,flight_num_pos->info.date);
    strcpy(new_node->info.model,flight_num_pos->info.model);
    strcpy(new_node->info.time,flight_num_pos->info.time);
	
	printf("name = %s\n",Ordinary_passenger_pos->info.name);
    //判断是否实名
    strcpy(new_node->info.name,Ordinary_passenger_pos->info.name);
	
    if(check_Verified(Ordinary_passenger_pos,Verified_identity_list_head) == -1)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"请实名\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
        return -1;
    }

	
    //判断是否残疾人军人
    if(check_identity_info(login_in_list_head,Verified_identity_list_head) == 0)
    {    
        new_node->info.price = (flight_num_pos->info.price)/2;
    }
    else
    {
		new_node->info.price = flight_num_pos->info.price;
    }
	
	if(judging_the_identity(login_in_list_head) == 1)
	{
		
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"你是白银vip\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		new_node->info.price = new_node->info.price*0.8;
	}
	if(judging_the_identity(login_in_list_head) == 2)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"你是黄金vip\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		new_node->info.price = new_node->info.price*0.7;
	}
	
    if(new_node->info.price > Ordinary_passenger_pos->info.balance)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"余额不足\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
        return -2;

    }


    if((check_ticket_buyer(buy_ticket_list_head,flight_num_pos->info.flight_number,Ordinary_passenger_pos->info.name)) == -1)//查看有没有重复购买
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"一个人坐两个位置这么顶?\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
        return -1;

    }    
    if(flight_num_pos->info.votes == 0)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"你不能走路去吗?(没票了)\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
        return -1;

    }

    strcpy(new_node->info.id,login_in_list_head->info.id);
    strcpy(new_node->info.phone_number,login_in_list_head->info.phone_number);
    new_node->info.age = login_in_list_head->info.age;
	
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请选行数\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"1 2 3 4 5 6 7 8 9 10\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	
	line = atoi(parting(buf));
	
		
	if((line > 10) || (line < 1))
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"别乱输(座位行数)\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请选座位\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"A%d  B%d  C%d  D%d  E%d\n",line,line,line,line,line);
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(input_seat,parting(buf));
	
	stpcpy(seat,input_seat);
	
	if(check_ticket_seat(buy_ticket_list_head,flight_num_pos->info.flight_number,seat,connfd) == -1)
	{
		return -1;
	}
	strcpy(new_node->info.seat,seat);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"是否需要购买保险(1、购买，0不买)\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	new_node->info.insurance = atoi(parting(buf));
	
	if(new_node->info.insurance == 1)
	{
		Operational_balance (Ordinary_passenger_pos,login_in_list_head,50,connfd);
		
	}
	else
	{
		new_node->info.insurance = 0;	
	}
	
    insert_buy_ticket_list_node_tail(buy_ticket_list_head,new_node);
	
	
    char filename[100] = {0};

	sprintf(filename,"./ticket_data/%s_%s.txt",new_node->info.name,new_node->info.flight_number);
    
    printf("%s\n",filename);
    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%s,%s,%d,%s,%d",
                        new_node->info.name,
                        new_node->info.id,
                        new_node->info.age,
                        new_node->info.phone_number,
                        new_node->info.flight_number,
                        new_node->info.departure,
                        new_node->info.destination,
                        new_node->info.date,
                        new_node->info.model,
                        new_node->info.time,
                        new_node->info.price,
						new_node->info.seat,
						new_node->info.insurance);
    
    

    FILE *fp = fopen(filename,"w+");
    if(fp == NULL)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"打开用户购票信息文件失败");
		send(connfd,sendbuf,strlen(sendbuf),0);
    }
	
	if(Operational_balance(Ordinary_passenger_pos,login_in_list_head,new_node->info.price,connfd) == -1)//扣款
	{
		return -1;
	}
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    remaining_votes_info(flight_num_pos);
	Operational_integral(Ordinary_passenger_pos,login_in_list_head);
	
	return 0;
	

    
}

//打印所有购买者
void printer_buy_ticket_information(struct buy_ticket_node *buy_ticket_list_pos,int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"姓名:%s\t",buy_ticket_list_pos->info.name);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"年龄:%d\t",buy_ticket_list_pos->info.age);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"电话:%s\t",buy_ticket_list_pos->info.phone_number);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"航班号:%s\n",buy_ticket_list_pos->info.flight_number);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"出发地:%s\t",buy_ticket_list_pos->info.departure); 
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"目的地:%s\t",buy_ticket_list_pos->info.destination);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"日期:%s\t",buy_ticket_list_pos->info.date);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"机型:%s\t",buy_ticket_list_pos->info.model);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"时间:%s\n",buy_ticket_list_pos->info.time);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"价格:%d\t",buy_ticket_list_pos->info.price);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"位置:%s\t",buy_ticket_list_pos->info.seat);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"保险:%d\n",buy_ticket_list_pos->info.insurance);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"-----------------------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
}

//打印出所有购买的票
void show_all_ticket_buyer(struct buy_ticket_node *buy_ticket_list_head,int connfd)
{
	struct buy_ticket_node *pos;

    list_for_each_entry(pos, &buy_ticket_list_head->pes_buy_ticket,pes_buy_ticket)
    {
        printer_buy_ticket_information(pos,connfd); 
    }
}

//打印自己购买的机票
int show_user_ticket_buyer(struct OrdinaryPassNode *login_in_list_head, struct buy_ticket_node *buy_ticket_list_head, int connfd)
{
	struct buy_ticket_node *pos;
    int count=0;
    list_for_each_entry(pos, &buy_ticket_list_head->pes_buy_ticket,pes_buy_ticket)
    {
        if(strcmp(login_in_list_head->info.name,pos->info.name) == 0)
        {
             printer_buy_ticket_information(pos,connfd);
             count++;

        }
    }
    return count;

}

//打印自己购买的机票(取票)
int check_in_show_user_ticket_buyer(char *name,struct buy_ticket_node *buy_ticket_list_head,int connfd)
{
	struct buy_ticket_node *pos;
    int count=0;
    list_for_each_entry(pos, &buy_ticket_list_head->pes_buy_ticket,pes_buy_ticket)
    {
        if(strcmp(name,pos->info.name) == 0)
        {
             printer_buy_ticket_information(pos,connfd);
             count++;

        }
    }
    return count;

}

//取票打印
struct buy_ticket_node *check_in_show_all_ticket_buyer(struct buy_ticket_node *buy_ticket_list_head,char *flight_number,int connfd)
{
	struct buy_ticket_node *pos,*n;

    list_for_each_entry_safe(pos, n,&buy_ticket_list_head->pes_buy_ticket,pes_buy_ticket)
    {
		if(strcmp(pos->info.flight_number,flight_number) == 0)
		{
			printer_buy_ticket_information(pos,connfd); 
			return pos;
		}
    }
	return NULL;
}

//打印发票
void printer_invoice_information(struct buy_ticket_node *buy_ticket_list_pos,int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"----------------------------发票----------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"姓名:%s\t",buy_ticket_list_pos->info.name);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"电话:%s\t",buy_ticket_list_pos->info.phone_number);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"航班号:%s\n",buy_ticket_list_pos->info.flight_number);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"价格:%d\n",buy_ticket_list_pos->info.price);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"-----------------------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
}

//发票打印寻找节点
struct buy_ticket_node *invoice_show_all_ticket_buyer(struct buy_ticket_node *buy_ticket_list_head,char *flight_number,int connfd)
{
	struct buy_ticket_node *pos,*n;

    list_for_each_entry_safe(pos, n,&buy_ticket_list_head->pes_buy_ticket,pes_buy_ticket)
    {
		if(strcmp(pos->info.flight_number,flight_number) == 0)
		{
			printer_invoice_information(pos,connfd); 
			return pos;
		}
    }
	return NULL;
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

//退票删文件
int rm_a_file(struct buy_ticket_node *buy_ticket_pos)
{      
    char buf[30];
    char buf1[30];
    strcpy(buf,buy_ticket_pos->info.name);
    strcpy(buf1,buy_ticket_pos->info.flight_number);

    char cmd[200]={0};
    
    sprintf(cmd,"rm ./ticket_data/%s_%s.txt",buf,buf1);

    system(cmd);

    printf("删除成功\n");
    return 0;

}

//返回登录用户的信息(退票)
struct OrdinaryPassNode *Refund_search_login_in_user(struct OrdinaryPassNode *Ordinary_passenger_list_head, struct OrdinaryPassNode *login_in_list_head)
{
	struct OrdinaryPassNode *pos;

    list_for_each_entry(pos, &Ordinary_passenger_list_head->Ordinary_passenger_list,Ordinary_passenger_list)
    {    
		
        if(strcmp(pos->info.name,login_in_list_head->info.name) == 0)
        {   
			
            return pos;
        }
    }
    return NULL;
}

//通过航班号寻找航班信息(退票)
struct flight_num_pas_node *Refund_search_flight_num_info(struct flight_num_pas_node *flight_num_list_head,char *flight_number)
{  

    struct flight_num_pas_node *pos;
  
    list_for_each_entry(pos, &flight_num_list_head->flight_num, flight_num)
    {
        if(strcmp(pos->info.flight_number,flight_number) == 0)
        {
            return pos;
        }
    }
    return NULL;
}

//查实名认证特殊身份(退票)
int Refund_check_identity_info(struct OrdinaryPassNode *login_in_list_head,
								struct Verified_identity_pas_node *Verified_identity_list_head)
{
    struct Verified_identity_pas_node *pos;
    list_for_each_entry(pos,&(Verified_identity_list_head->Verified_list),Verified_list)
	{
		if((strcmp(pos->info.name,login_in_list_head->info.name) == 0))
		{       
            if(pos->info.doctor_or_nurse == 1)
            {
                printf("退票免手续费\n");
                return 0;
            }
            printf("扣手续费\n");
            return -1;
		}
	}
}

//寻找退票节点
struct buy_ticket_node *find_Refund_ticket(struct OrdinaryPassNode *login_in_list_head, struct buy_ticket_node *buy_ticket_list_head, char *flight_number)
{
	struct buy_ticket_node *pos;
    int count=0;
    list_for_each_entry(pos, &buy_ticket_list_head->pes_buy_ticket,pes_buy_ticket)
    {
        if((strcmp(login_in_list_head->info.name,pos->info.name) == 0) && (strcmp(flight_number,pos->info.flight_number) == 0))
        {
             //printer_buy_ticket_information(pos,connfd);
             return pos;

        }
    }
    return NULL;

}

//退票退款
int Operational_Refund_balance(struct OrdinaryPassNode *Ordinary_passenger_pos, struct OrdinaryPassNode *login_in_list_head, int price)
{

	//CheckPath();
    login_in_list_head->info.balance = login_in_list_head->info.balance + price;
    Ordinary_passenger_pos->info.balance = Ordinary_passenger_pos->info.balance + price;
    //printf("price = %d",loginIn->info.bal);

    

    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",Ordinary_passenger_pos->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									login_in_list_head->info.name,
																							login_in_list_head->info.id,
																							login_in_list_head->info.age,
																							login_in_list_head->info.phone_number,
																							login_in_list_head->info.passwd,
																							login_in_list_head->info.pay_passwd,
																							login_in_list_head->info.	question,
																							login_in_list_head->info.answer,
																							login_in_list_head->info.balance,
																							login_in_list_head->info.vip,
																							login_in_list_head->info.integral);


    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    printf("退款成功\n");
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    
}

//写入余票(退票+1)
int Refund_remaining_votes_info(struct flight_num_pas_node *flight_num_pos)
{   

    flight_num_pos->info.votes++;
 
    char filename[100] = {0};
	sprintf(filename,"./data/%s.txt",flight_num_pos->info.flight_number);
    printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%s,%s,%s,%s,%d,%d",
                        flight_num_pos->info.flight_number,
                        flight_num_pos->info.departure,
                        flight_num_pos->info.destination,
                        flight_num_pos->info.date,
                        flight_num_pos->info.model,
                        flight_num_pos->info.time,
                        flight_num_pos->info.price,
                        flight_num_pos->info.votes
                        );

   /* printf("%s,%s,%s,%s,%s,%s,%d,%d",
                        buy_ticket_pos->info.flight_number,
                        buy_ticket_pos->info.departure,
                        buy_ticket_pos->info.destination,
                        buy_ticket_pos->info.date,
                        buy_ticket_pos->info.model,
                        buy_ticket_pos->info.time,
                        buy_ticket_pos->info.price,
                        buy_ticket_pos->info.votes
                        );*/
    FILE *fp = fopen(filename,"w");
    
    if(fp == NULL)
    {
        perror("打开用户购票信息文件失败");
    }
    

    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);

    printf("修改余票成功+1\n");

}

//退票扣积分
int Refund_Operational_integral(struct OrdinaryPassNode *Ordinary_passenger_pos, struct OrdinaryPassNode *login_in_list_head)
{


    login_in_list_head->info.integral = login_in_list_head->info.integral - 50;
    Ordinary_passenger_pos->info.integral = Ordinary_passenger_pos->info.integral - 50;
    //printf("price = %d",loginIn->info.bal);

    

    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",login_in_list_head->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									login_in_list_head->info.name,
																							login_in_list_head->info.id,
																							login_in_list_head->info.age,
																							login_in_list_head->info.phone_number,
																							login_in_list_head->info.passwd,
																							login_in_list_head->info.pay_passwd,
																							login_in_list_head->info.question,
																							login_in_list_head->info.answer,
																							login_in_list_head->info.balance,
																							login_in_list_head->info.vip,
																							login_in_list_head->info.integral);

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    printf("加积分成功\n");
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    
}

//将退票节点移除链表
void delete_Refund(struct buy_ticket_node *node)
{
    list_del(&node->pes_buy_ticket);//将小个结构体节点移除出本身所在链表
    free(node);
}

//退票
int Refund(struct flight_num_pas_node *flight_num_list_head, struct OrdinaryPassNode *login_in_list_head,
           struct buy_ticket_node *buy_ticket_list_head, struct Verified_identity_pas_node *Verified_identity_list_head,
           struct OrdinaryPassNode *Ordinary_passenger_list_head, int connfd)
{   

	struct buy_ticket_node *buy_ticket_pos;
    struct OrdinaryPassNode *Ordinary_passenger_pos;
    struct flight_num_pas_node *flight_num_pos;
	char seat[20] = {0};
	int line;
	char input_seat[20] = {0};
	char line_tmp[20] = {0};
	int ret;
	char flight_number[20];
	char buf[50];
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"请输入你要退机票的航班号\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strcpy(flight_number,parting(buf));
	
	
	buy_ticket_pos = find_Refund_ticket(login_in_list_head,buy_ticket_list_head,flight_number);//寻找要退的机票
	if(buy_ticket_pos == NULL)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"不要乱输\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
        return -1;
    }
	
    Ordinary_passenger_pos = Refund_search_login_in_user(Ordinary_passenger_list_head,login_in_list_head);//获取登陆者信息
	//printf("name = %s\n",Ordinary_passenger_pos->info.name);
    flight_num_pos = Refund_search_flight_num_info(flight_num_list_head,flight_number);//通过航班号获取里面航班信息并返回
	
	if(Refund_check_identity_info(login_in_list_head,Verified_identity_list_head) == 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"扣除0%%的手续费\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		Operational_Refund_balance  (Ordinary_passenger_pos,login_in_list_head,buy_ticket_pos->info.price);
	}
	else
	{
		buy_ticket_pos->info.price = (buy_ticket_pos->info.price)*0.95;
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"扣除5%%的手续费:%d\n",buy_ticket_pos->info.price);
		send(connfd,sendbuf,strlen(sendbuf),0);
		Operational_Refund_balance (Ordinary_passenger_pos,login_in_list_head,buy_ticket_pos->info.price);							
	}
	
	rm_a_file(buy_ticket_pos);
    //Operational_Refund_balance  (Ordinary_passenger_pos,login_in_list_head,buy_ticket_pos->info.price);
	Refund_remaining_votes_info(flight_num_pos);
	Refund_Operational_integral(Ordinary_passenger_pos,login_in_list_head);
	delete_Refund(buy_ticket_pos);
	
	return 0;
	

    
}

//退票(改签)
int Change_Refund(struct flight_num_pas_node *flight_num_list_head, struct OrdinaryPassNode *login_in_list_head,
                  struct buy_ticket_node *buy_ticket_list_head, struct Verified_identity_pas_node *Verified_identity_list_head,
                  struct OrdinaryPassNode *Ordinary_passenger_list_head, int connfd)
{   

	struct buy_ticket_node *buy_ticket_pos;
    struct OrdinaryPassNode *Ordinary_passenger_pos;
    struct flight_num_pas_node *flight_num_pos;
	char seat[20] = {0};
	int line;
	char input_seat[20] = {0};
	char line_tmp[20] = {0};
	int ret;
	char flight_number[20];
	char buf[50];
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"请输入你要退机票的航班号\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strcpy(flight_number,parting(buf));
	
	buy_ticket_pos = find_Refund_ticket(login_in_list_head,buy_ticket_list_head,flight_number);//寻找要退的机票
	if(buy_ticket_pos == NULL)
    {
        printf("不要乱输\n");
        return -1;
    }
	if(buy_ticket_pos->info.insurance == 1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"退保险成功\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		buy_ticket_pos->info.price = buy_ticket_pos->info.price + 50;
		//printf("price = %d\n",buy_ticket_pos->info.price);
	}
	
    Ordinary_passenger_pos = Refund_search_login_in_user(Ordinary_passenger_list_head,login_in_list_head);//获取登陆者信息
	//printf("name = %s\n",Ordinary_passenger_pos->info.name);
    flight_num_pos = Refund_search_flight_num_info(flight_num_list_head,flight_number);//通过航班号获取里面航班信息并返回		
	
	rm_a_file(buy_ticket_pos);
    Operational_Refund_balance(Ordinary_passenger_pos,login_in_list_head,buy_ticket_pos->info.price);
	Refund_remaining_votes_info(flight_num_pos);
	Refund_Operational_integral(Ordinary_passenger_pos,login_in_list_head);
	delete_Refund(buy_ticket_pos);
	
	return 0;
	

    
}

//改签
int Change(struct flight_num_pas_node *flight_num_list_head, struct OrdinaryPassNode *login_in_list_head,
           struct buy_ticket_node *buy_ticket_list_head,
           struct Verified_identity_pas_node *Verified_identity_list_head,
           struct OrdinaryPassNode *Ordinary_passenger_list_head, int connfd)
{   
	if(Change_Refund(flight_num_list_head,login_in_list_head,buy_ticket_list_head,
					Verified_identity_list_head,Ordinary_passenger_list_head,connfd) == -1)
	{
		return -1;	
	}
    allFlightNum(flight_num_list_head, connfd);
	if(buy_ticket_info(flight_num_list_head,login_in_list_head,buy_ticket_list_head,
						Verified_identity_list_head,Ordinary_passenger_list_head,connfd) == 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"改签成功\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
	}
	else
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"改签失败\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
	}
	
	return 0;
	
}

//买保险扣款(帮别人买票)
int help_other_Operational_balance_insurance  (struct OrdinaryPassNode *Ordinary_passenger_pos, int price)
{


    Ordinary_passenger_pos->info.balance = Ordinary_passenger_pos->info.balance - price;
    //printf("price = %d",loginIn->info.bal);

    

    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt", Ordinary_passenger_pos->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									Ordinary_passenger_pos->info.name,
																							Ordinary_passenger_pos->info.id,
																							Ordinary_passenger_pos->info.age,
																							Ordinary_passenger_pos->info.phone_number,
																							Ordinary_passenger_pos->info.passwd,
																							Ordinary_passenger_pos->info.pay_passwd,
																							Ordinary_passenger_pos->info.question,
																							Ordinary_passenger_pos->info.answer,
																							Ordinary_passenger_pos->info.balance,
																							Ordinary_passenger_pos->info.vip,
																							Ordinary_passenger_pos->info.integral);

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    printf("保险扣款成功\n");
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    
}

//买票扣款(帮别人买票)
int help_other_Operational_balance  (struct OrdinaryPassNode *Ordinary_passenger_pos, int price)
{


    
    Ordinary_passenger_pos->info.balance = Ordinary_passenger_pos->info.balance - price;
    //printf("price = %d",loginIn->info.bal);

    
    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt", Ordinary_passenger_pos->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									Ordinary_passenger_pos->info.name,
																							Ordinary_passenger_pos->info.id,
																							Ordinary_passenger_pos->info.age,
																							Ordinary_passenger_pos->info.phone_number,
																							Ordinary_passenger_pos->info.passwd,
																							Ordinary_passenger_pos->info.pay_passwd,
																							Ordinary_passenger_pos->info.question,
																							Ordinary_passenger_pos->info.answer,
																							Ordinary_passenger_pos->info.balance,
																							Ordinary_passenger_pos->info.vip,
																							Ordinary_passenger_pos->info.integral);

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    printf("买票扣款成功\n");
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    
}

//买票加积分(帮别人买票)
int help_other_Operational_integral(struct OrdinaryPassNode *Ordinary_passenger_pos)
{


    
    Ordinary_passenger_pos->info.integral = Ordinary_passenger_pos->info.integral + 50;
    //printf("price = %d",loginIn->info.bal);

    

    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt", Ordinary_passenger_pos->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									Ordinary_passenger_pos->info.name,
																							Ordinary_passenger_pos->info.id,
																							Ordinary_passenger_pos->info.age,
																							Ordinary_passenger_pos->info.phone_number,
																							Ordinary_passenger_pos->info.passwd,
																							Ordinary_passenger_pos->info.pay_passwd,
																							Ordinary_passenger_pos->info.question,
																							Ordinary_passenger_pos->info.answer,
																							Ordinary_passenger_pos->info.balance,
																							Ordinary_passenger_pos->info.vip,
																							Ordinary_passenger_pos->info.integral);

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    printf("加积分成功\n");
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    
}

//返回登录用户的信息(帮别人买票)
struct OrdinaryPassNode *help_other_search_login_in_user(struct OrdinaryPassNode *Ordinary_passenger_list_head, char *other_name)
{
	struct OrdinaryPassNode *pos;
    list_for_each_entry(pos, &Ordinary_passenger_list_head->Ordinary_passenger_list,Ordinary_passenger_list)
    {    
		
        if(strcmp(pos->info.name,other_name) == 0)
        {   
			
            return pos;
        }
    }
    return NULL;
}

//查询是否是好友才能帮其购票
int buy_ticket_friends(struct friends_info_list *friends_list_head,char *name)
{
	struct friends_info_list *pos;

    list_for_each_entry(pos, &friends_list_head->friends_list, friends_list)
    {
        if(strcmp(friends_list_head->friends_name,name) == 0)
		{
			return 0;
		}
    }
	return -1;
}

//帮别人买票
int help_other_buy_ticket_info(struct flight_num_pas_node *flight_num_list_head, struct OrdinaryPassNode *login_in_list_head,
                               struct buy_ticket_node *buy_ticket_list_head, struct Verified_identity_pas_node *Verified_identity_list_head,
                               struct OrdinaryPassNode *Ordinary_passenger_list_head, int connfd, struct friends_info_list *friends_list_head)
{   


    struct OrdinaryPassNode *Ordinary_passenger_pos;
    struct flight_num_pas_node *flight_num_pos;
	char seat[20] = {0};
	int line;
	char input_seat[20] = {0};
	char line_tmp[20] = {0};
	int ret;
	char other_name[20];
	char id[8];
	char buf[500];
	
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"购票者姓名:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strcpy(other_name,parting(buf));
	
	if(buy_ticket_friends(friends_list_head,other_name) == -1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"无中生有?\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	Ordinary_passenger_pos = help_other_search_login_in_user(Ordinary_passenger_list_head,other_name);
	
	if(Ordinary_passenger_pos == NULL)
	{
		/*bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"无中生有?\n");
		send(connfd,sendbuf,strlen(sendbuf),0);*/
		return -1;
	}
	
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"请输入购票者的身份证号码:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strcpy(id,parting(buf));
	
	printf("id = %s\n",id);
	
	printf("pos id = %s\n",Ordinary_passenger_pos->info.id);
	
	if(strcmp(Ordinary_passenger_pos->info.id,id) == 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"身份证号码输入正确\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
	}
    else
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"身份证号码输入错误\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}

    flight_num_pos = search_flight_num_info(flight_num_list_head,connfd);//通过航班号获取里面航班信息并返回
    if(flight_num_pos == NULL)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"身份证号码输入正确\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
        return -1;
    }
    
    struct buy_ticket_node *new_node;

    new_node = request_buy_ticket_node();
	
	
	
    strcpy(new_node->info.flight_number,flight_num_pos->info.flight_number);
    strcpy(new_node->info.departure,flight_num_pos->info.departure);
    strcpy(new_node->info.destination,flight_num_pos->info.destination);
    strcpy(new_node->info.date,flight_num_pos->info.date);
    strcpy(new_node->info.model,flight_num_pos->info.model);
    strcpy(new_node->info.time,flight_num_pos->info.time);
	
	printf("name = %s\n",Ordinary_passenger_pos->info.name);
    //判断是否实名
    strcpy(new_node->info.name,Ordinary_passenger_pos->info.name);
	
    if(check_Verified(Ordinary_passenger_pos,Verified_identity_list_head) == -1)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"请实名\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
        return -1;
    }

	
    //判断是否残疾人军人
    if(check_identity_info(Ordinary_passenger_pos,Verified_identity_list_head) == 0)
    {    
        new_node->info.price = (flight_num_pos->info.price)/2;
    }
    else
    {
		new_node->info.price = flight_num_pos->info.price;
    }
	
	if(judging_the_identity(Ordinary_passenger_pos) == 1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"你是白银vip\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		new_node->info.price = new_node->info.price*0.8;
	}
	if(judging_the_identity(Ordinary_passenger_pos) == 2)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"请实名\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		new_node->info.price = new_node->info.price*0.7;
	}
	
    if(new_node->info.price > Ordinary_passenger_pos->info.balance)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"余额不足\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
        return -2;

    }


    if((check_ticket_buyer(buy_ticket_list_head,flight_num_pos->info.flight_number,Ordinary_passenger_pos->info.name)) == -1)//查看有没有重复购买
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"一个人坐两个位置这么顶?\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
        return -1;

    }    
    if(flight_num_pos->info.votes == 0)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"你不能走路去吗?(没票了)\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
        return -1;

    }

    strcpy(new_node->info.id,Ordinary_passenger_pos->info.id);
    strcpy(new_node->info.phone_number,Ordinary_passenger_pos->info.phone_number);
    new_node->info.age = Ordinary_passenger_pos->info.age;
	
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请选行数\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"1 2 3 4 5 6 7 8 9 10\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	
	line = atoi(parting(buf));
	
	if((line > 10) || (line < 1))
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"别乱输(座位行数)\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请选座位\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"A%d  B%d  C%d  D%d  E%d\n",line,line,line,line,line);
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(input_seat,parting(buf));
	
	stpcpy(seat,input_seat);
	
	if(check_ticket_seat(buy_ticket_list_head,flight_num_pos->info.flight_number,seat,connfd) == -1)
	{
		return -1;
	}
	strcpy(new_node->info.seat,seat);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"是否需要购买保险(1、购买，0不买)\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	new_node->info.insurance = atoi(parting(buf));
	
	if(new_node->info.insurance == 1)
	{
		help_other_Operational_balance(Ordinary_passenger_pos,50);
		
	}
	else
	{
		new_node->info.insurance = 0;	
	}
	
    insert_buy_ticket_list_node_tail(buy_ticket_list_head,new_node);
	
	
    char filename[100] = {0};

	sprintf(filename,"./ticket_data/%s_%s.txt",new_node->info.name,new_node->info.flight_number);
    
    printf("%s\n",filename);
    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%s,%s,%d,%s,%d",
                        new_node->info.name,
                        new_node->info.id,
                        new_node->info.age,
                        new_node->info.phone_number,
                        new_node->info.flight_number,
                        new_node->info.departure,
                        new_node->info.destination,
                        new_node->info.date,
                        new_node->info.model,
                        new_node->info.time,
                        new_node->info.price,
						new_node->info.seat,
						new_node->info.insurance);
    
    

    FILE *fp = fopen(filename,"w+");
    if(fp == NULL)
    {
       // perror("打开用户购票信息文件失败");
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"打开用户购票信息文件失败");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
    }
	
   
	help_other_Operational_balance(Ordinary_passenger_pos,new_node->info.price);
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    remaining_votes_info(flight_num_pos);
	help_other_Operational_integral(Ordinary_passenger_pos);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"帮人购票成功\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	
	return 0;
	

    
}

//取票
int check_in(struct buy_ticket_node *buy_ticket_list_head,int connfd)
{
	struct buy_ticket_node *buy_ticket_pos = NULL;
	char name[20];
	char flight_number[20];
	char buf[50];
	
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"请输入你的名字\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strcpy(name,parting(buf));
	
	if(check_in_show_user_ticket_buyer(name,buy_ticket_list_head,connfd) == 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"你买票了?\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"请输入要取的航班号\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strcpy(flight_number,parting(buf));
	

	buy_ticket_pos = check_in_show_all_ticket_buyer(buy_ticket_list_head,flight_number,connfd);
	
	if(buy_ticket_pos == NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"别乱输\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
	}
	
	rm_a_file(buy_ticket_pos);
	
	delete_Refund(buy_ticket_pos);
	
	return 0;
}


//退票退款(删航班)
int delete_flight_number_Operational_Refund_balance(struct OrdinaryPassNode *Ordinary_passenger_pos, int price)
{

	//CheckPath();
    Ordinary_passenger_pos->info.balance = Ordinary_passenger_pos->info.balance + price;
    //printf("price = %d",loginIn->info.bal);

    

    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",Ordinary_passenger_pos->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									Ordinary_passenger_pos->info.name,
																							Ordinary_passenger_pos->info.id,
																							Ordinary_passenger_pos->info.age,
																							Ordinary_passenger_pos->info.phone_number,
																							Ordinary_passenger_pos->info.passwd,
																							Ordinary_passenger_pos->info.pay_passwd,
																							Ordinary_passenger_pos->info.	question,
																							Ordinary_passenger_pos->info.answer,
																							Ordinary_passenger_pos->info.balance,
																							Ordinary_passenger_pos->info.vip,
																							Ordinary_passenger_pos->info.integral);


    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    printf("(删航班)退款成功\n");
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    
}

//退票扣积分(删航班)
int delete_flight_number_Refund_Operational_integral(struct OrdinaryPassNode *Ordinary_passenger_pos)
{


    Ordinary_passenger_pos->info.integral = Ordinary_passenger_pos->info.integral - 50;
    //printf("price = %d",loginIn->info.bal);

    

    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",Ordinary_passenger_pos->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									Ordinary_passenger_pos->info.name,
																							Ordinary_passenger_pos->info.id,
																							Ordinary_passenger_pos->info.age,
																							Ordinary_passenger_pos->info.phone_number,
																							Ordinary_passenger_pos->info.passwd,
																							Ordinary_passenger_pos->info.pay_passwd,
																							Ordinary_passenger_pos->info.	question,
																							Ordinary_passenger_pos->info.answer,
																							Ordinary_passenger_pos->info.balance,
																							Ordinary_passenger_pos->info.vip,
																							Ordinary_passenger_pos->info.integral);

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    printf("加积分成功(删航班)\n");
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
    
}

//返回登录用户的信息(删航班退票)
struct OrdinaryPassNode *delete_flight_number_Refund_search_login_in_user(struct OrdinaryPassNode *Ordinary_passenger_list_head, char *name)
{
	struct OrdinaryPassNode *pos,*n;

    list_for_each_entry_safe(pos,n,&Ordinary_passenger_list_head->Ordinary_passenger_list,Ordinary_passenger_list)
    {    
		
        if(strcmp(pos->info.name,name) == 0)
        {   
            return pos;
        }
    }
    return NULL;
}

//删除航班退票单个
int delete_flight_number_Refund(struct flight_num_pas_node *flight_num_pos,
										struct buy_ticket_node *buy_ticket_pos,struct OrdinaryPassNode *Ordinary_passenger_list_head,
													char *flight_number,int connfd)
{   

    struct OrdinaryPassNode *Ordinary_passenger_pos;
	
	if(buy_ticket_pos->info.insurance == 1)
	{
		buy_ticket_pos->info.price += 100;
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"保险生效:%d\n",buy_ticket_pos->info.price);
		send(connfd,sendbuf,strlen(sendbuf),0);
	}
	
	
	
    Ordinary_passenger_pos = delete_flight_number_Refund_search_login_in_user(Ordinary_passenger_list_head,buy_ticket_pos->info.name);//获取登陆者信息

	rm_a_file(buy_ticket_pos);
	delete_flight_number_Operational_Refund_balance(Ordinary_passenger_pos,buy_ticket_pos->info.price);
	Refund_remaining_votes_info(flight_num_pos);
	delete_flight_number_Refund_Operational_integral(Ordinary_passenger_pos);
	delete_Refund(buy_ticket_pos);
	
	return 0;
	

    
}

//寻找删除航班退票节点
struct buy_ticket_node *delete_flight_number_find_Refund_ticket(struct buy_ticket_node *buy_ticket_list_head, char *flight_number, struct flight_num_pas_node *flight_num_pos,
                                                                struct OrdinaryPassNode *Ordinary_passenger_list_head, int connfd)
{
	struct buy_ticket_node *pos,*n;
    int count=0;
    list_for_each_entry_safe(pos,n, &buy_ticket_list_head->pes_buy_ticket,pes_buy_ticket)
    {
        if(strcmp(flight_number,pos->info.flight_number) == 0)
        {
			delete_flight_number_Refund(flight_num_pos,pos,Ordinary_passenger_list_head,flight_number,connfd);
             
        }
    }
    

}

//删除航班并退票
int delete_flight_number_Refund_all(struct flight_num_pas_node *flight_num_list_head,struct OrdinaryPassNode *Ordinary_passenger_list_head,
									struct buy_ticket_node *buy_ticket_list_head,struct flight_num_pas_node *rm_flight_num_list_head,int connfd)
{
	char flight_number[30];
	struct flight_num_pas_node *flight_num_pos;
	char buf[50];
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入要删除航班的航班号\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(flight_number,parting(buf));
	
	
	flight_num_pos = deleteFlightNumber(flight_num_list_head, flight_number, rm_flight_num_list_head);
	
	if(flight_num_pos == NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"没有此航班号\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	delete_flight_number_find_Refund_ticket(buy_ticket_list_head,flight_number,flight_num_pos,Ordinary_passenger_list_head,connfd);

    numFile(flight_num_pos, connfd);
    aFlightNumFile(flight_num_pos, connfd);
    numInformation(rm_flight_num_list_head, flight_num_pos);
	list_del(&flight_num_pos->flight_num);
	free(flight_num_pos);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"删除航班成功\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	return 0;
	
}


//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

//管理员信息结构体
struct admin
{
    char name[20];
    char passwd[8];
};

//管理官信息大结构体
struct admin_node
{
    struct admin info;
    struct list_head admin_list;

};

//管理员初始化头节点
struct admin_node *request_link_admin_list_node(void)
{
    struct admin_node *new_node;

    new_node = malloc(sizeof(struct admin_node));
    if(new_node == NULL)
    {
        perror("申请内存失败");
        return NULL;
    }

    INIT_LIST_HEAD(&(new_node->admin_list));//将小个结构体的上下指针指向自己
    return new_node;
}

//管理员尾插
void insert_admin_list_node_tail(struct admin_node *admin_list_head, struct admin_node *admin_insert_node)
{  
    list_add_tail(&(admin_insert_node->admin_list), &(admin_list_head->admin_list));
}

//判断这个人是否已经注册过(管理员)
struct admin_node *find_admin(struct admin_node *admin_list_head,char *name)
{
	struct admin_node *pos,*n;
	
    list_for_each_entry_safe(pos,n, &admin_list_head-> admin_list,  admin_list)
    {	
		
        if(strcmp(pos->info.name,name) == 0)
		{
			return pos;
		}
        
    }	
    return NULL;
}

//管理员注册
int register_admin_information(struct admin_node *admin_list_head,int connfd)
{
    struct admin_node *new_node;

    new_node = request_link_admin_list_node();
	
	char verify_passwd[8];
	char buf[50];
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入你的名字:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(new_node->info.name,parting(buf));
	
	if(find_admin(admin_list_head,new_node->info.name) != NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"您已注册，请登录\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		
		return -1;
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入管理员身份验证密码:");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(verify_passwd,parting(buf));
	
	
	if(strcmp(verify_passwd,"123456") != 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"验证密码错误\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入你的密码:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(new_node->info.passwd,parting(buf));
	
    insert_admin_list_node_tail(admin_list_head, new_node);

    char filename[100] = {0};
	sprintf(filename,"./admin_data/%s.txt",new_node->info.name);
    printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s",new_node->info.name,new_node->info.passwd);

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"打开用户信息文件失败\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
    }
    
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"管理员注册成功\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	return 0;
    
}

//分割文件中中的数据
void admin_strtok_fun(struct admin_node *admin_list_head,char *buf)
{
	//1. 为新节点申请空间。
	struct admin_node *new;

    new = request_link_admin_list_node();
	
	//2. 分割字符串，为新节点数据域指针域赋值。
	char seqs[] = ",";
	
    char *tmp;

	tmp = strtok(buf,seqs);
	strcpy(new->info.name,tmp);

	tmp = strtok(NULL,seqs);
	strcpy(new->info.passwd,tmp);
	
    insert_admin_list_node_tail(admin_list_head,new);
    
	return;
}

//读文件
void admin_read_file(struct admin_node *admin_list_head,char *filename)
{
	//1. 打开文件。
	FILE *fp = fopen(filename,"a+");
	if(fp == NULL)
		perror("打开文件错误!\n");
	
	//2. 读取文件数据。
	char buf[200] = {0};
	fread(buf,20,10,fp);
	
	//3. 关闭文件。
	fclose(fp);
	
	//4. 分割数据。
	admin_strtok_fun(admin_list_head,buf);
	
	return;
}

//初始化已注册（在文件夹中的）管理员
void admin_init_old_usr(struct admin_node *head)
{
	//1. 打开目录。
	DIR* dp = opendir("./admin_data");
	if(dp == NULL)
		perror("打开admindata文件夹失败!\n");
        
	//2. 切换到目录下。
	chdir("./admin_data");
    
	//3. 不断读取目录下的文件名。
	struct dirent *ep = NULL;

	while(1)
	{   
		ep = readdir(dp);
        
		if(ep == NULL) //读取完整个目录
		{
			break;
		}
		
		if(ep->d_name[0] == '.')
		{
			continue;
		}
        
		
		admin_read_file(head,ep->d_name);	
	}
	
	//4. 切换到上一级目录。
	chdir("..");

	
	//5. 关闭目录
	closedir(dp);
	
	return;
}

//判断是否登录成功并将管理员信息存进登录链表
int admin_login_in(struct admin_node *admin_list_head,struct admin_node *admin_login_in_list_head,int connfd)
{
	char name[30] = {0};
	char passwd[30] = {0};
	char buf[50];
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入你的名字:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(name,parting(buf));
	

	struct admin_node *admin_pos;
	
	admin_pos = find_admin(admin_list_head,name);
		
	if(admin_pos == NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"没有此账号(管理员)，请注册\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入密码(管理员):\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(passwd,parting(buf));
	
	
	if(strcmp(passwd,admin_pos->info.passwd) != 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"密码错误(管理员)\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	
	stpcpy(admin_login_in_list_head->info.name,admin_pos->info.name);
	stpcpy(admin_login_in_list_head->info.passwd,admin_pos->info.passwd);

	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"登录成功\n");
	send(connfd,sendbuf,strlen(sendbuf),0);

	
	return 0;
	
}

//显示单个管理员信息
void printer_admin_information(struct admin_node *admin_pos,int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"名字:%s\t",admin_pos->info.name);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"密码:%s\t\n",admin_pos->info.passwd);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"-------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);

}

//遍历所有管理员信息
void show_all_admin(struct admin_node *admin_list_head,int connfd)
{
	struct admin_node *pos;

    list_for_each_entry(pos,&(admin_list_head-> admin_list),  admin_list)
    {
        printer_admin_information(pos,connfd);
    }	
}

//开发票
int invoice(struct buy_ticket_node *buy_ticket_list_head, struct OrdinaryPassNode *login_in_list_head, int connfd)
{
	struct buy_ticket_node *buy_ticket_pos = NULL;
	char name[20];
	char flight_number[20];
	char buf[50];
	
	/*bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"请输入你的名字\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strcpy(name,parting(buf));*/
	
	if(check_in_show_user_ticket_buyer(login_in_list_head->info.name,buy_ticket_list_head,connfd) == 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"你买票了?\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"请输入要打印发票的航班号\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strcpy(flight_number,parting(buf));
	

	buy_ticket_pos = invoice_show_all_ticket_buyer(buy_ticket_list_head,flight_number,connfd);
	
	if(buy_ticket_pos == NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"别乱输\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"打印发票完成\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	
	return 0;
	

}

 




















//返回登录用户的信息(充值)
struct OrdinaryPassNode *Recharge_search_login_in_user(struct OrdinaryPassNode *Ordinary_passenger_list_head, struct OrdinaryPassNode *login_in_list_head)
{
	struct OrdinaryPassNode *pos;

    list_for_each_entry(pos, &Ordinary_passenger_list_head->Ordinary_passenger_list,Ordinary_passenger_list)
    {    
		
        if(strcmp(pos->info.name,login_in_list_head->info.name) == 0)
        {   
			
            return pos;
        }
    }
    return NULL;
}

//充值操作
int Operational_Recharge_balance(struct OrdinaryPassNode *Ordinary_passenger_pos, struct OrdinaryPassNode *login_in_list_head, int balance, int connfd)
{

	//CheckPath();
    login_in_list_head->info.balance = login_in_list_head->info.balance + balance;
    Ordinary_passenger_pos->info.balance = Ordinary_passenger_pos->info.balance + balance;
    //printf("balance = %d",loginIn->info.bal);

    

    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",Ordinary_passenger_pos->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									login_in_list_head->info.name,
																							login_in_list_head->info.id,
																							login_in_list_head->info.age,
																							login_in_list_head->info.phone_number,
																							login_in_list_head->info.passwd,
																							login_in_list_head->info.pay_passwd,
																							login_in_list_head->info.	question,
																							login_in_list_head->info.answer,
																							login_in_list_head->info.balance,
																							login_in_list_head->info.vip,
																							login_in_list_head->info.integral);


    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"充值修改余额失败\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
    }
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"充值写入成功\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
	
	return 0;
    
}

//充值 vip
int Recharge_Operational_vip(struct OrdinaryPassNode *Ordinary_passenger_pos, struct OrdinaryPassNode *login_in_list_head, int connfd)
{
	
    char filename[100] = {0};
	sprintf(filename,"./user_data/%s.txt",login_in_list_head->info.name);
    //printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%d,%s,%s,%s,%s,%s,%d,%d,%d",									login_in_list_head->info.name,
																							login_in_list_head->info.id,
																							login_in_list_head->info.age,
																							login_in_list_head->info.phone_number,
																							login_in_list_head->info.passwd,
																							login_in_list_head->info.pay_passwd,
																							login_in_list_head->info.question,
																							login_in_list_head->info.answer,
																							login_in_list_head->info.balance,
																							login_in_list_head->info.vip,
																							login_in_list_head->info.integral);

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"成为vip失败\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
		
    }
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"成为vip成功%d\n",login_in_list_head->info.vip);
	send(connfd,sendbuf,strlen(sendbuf),0);
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);
	return 0;
    
}

//充值
int Recharge(struct OrdinaryPassNode *Ordinary_passenger_list_head, struct OrdinaryPassNode *login_in_list_head, int connfd)
{
	int balance;
	char buf[100];
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"请输入要充值的金额:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	balance = atoi(parting(buf));
	
	struct OrdinaryPassNode *Ordinary_passenger_pos;
	
	Ordinary_passenger_pos = Recharge_search_login_in_user(Ordinary_passenger_list_head,login_in_list_head);
	
	if(balance > 100)
	{
		balance += 20;
	}
	if(balance > 500)
	{
		balance += 180;
	}
	if(balance > 10000)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"成为黄金会员\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		login_in_list_head->info.vip = 2;
		Ordinary_passenger_pos->info.vip = 2;
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"成为黄金会员\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
	}
	else if((balance > 5000) && (balance < 10000))
	{
		login_in_list_head->info.vip = 1;
		Ordinary_passenger_pos->info.vip = 1;
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"成为白银会员\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		
		
	}
	
	if(Recharge_Operational_vip(Ordinary_passenger_pos,login_in_list_head,connfd) == -1)
	{
		return -1;
	}
	
	if(Operational_Recharge_balance(Ordinary_passenger_pos,login_in_list_head,balance,connfd) == -1)
	{
		return -1;
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"充值成功%d\n",balance);
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	
		
	return 0;
	
}




//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
//----------------------------------------好友列表----------------------------------------------------
//----------------------------------------------------------------------------------------------------


//好友列表初始化头节点
struct friends_info_list *request_link_friends_list_node(void)
{
    struct friends_info_list *new_node;

    new_node = malloc(sizeof(struct friends_info_list));
    if(new_node == NULL)
    {
        perror("申请内存失败");
        return NULL;
    }

    INIT_LIST_HEAD(&(new_node->friends_list));//将小个结构体的上下指针指向自己
    return new_node;
}

//好友列表尾插
void insert_friend_list_node_tail(struct friends_info_list *friends_list_head, struct friends_info_list *friends_list_insert_node)
{
	printf("name %s\n",friends_list_insert_node->friends_name);
    list_add_tail(&(friends_list_insert_node->friends_list), &(friends_list_head->friends_list));
}

//好友列表分割文件中中的数据
void friends_strtok_fun(struct friends_info_list *friends_list_head,char *buf,int connfd)
{
	//1. 为新节点申请空间。
	struct friends_info_list *new;

    new = request_link_friends_list_node();
	
	char seqs[] = ",";
	
    char *tmp;

	tmp = strtok(buf,seqs);
	strcpy(new->friends_name,tmp);
	
    tmp = strtok(NULL,seqs);
	
	new->blacklist = atoi(tmp);
	
	//printf("blacklist = %d\n",new->blacklist);
	
	//strcpy(new->friends_name,buf);
	
	new->online = 0;
	
    insert_friend_list_node_tail(friends_list_head,new);
	
	return;
}

//好友列表读文件
void friends_read_file(struct friends_info_list *friends_list_head,char *filename,int connfd)
{
	//1. 打开文件。
	FILE *fp = fopen(filename,"a+");
	if(fp == NULL)
	{	
		perror("打开文件错误!\n");
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"打开%s文件失败!\n",filename);
		send(connfd,sendbuf,strlen(sendbuf),0);
		
	}
	
	
	
	//2. 读取文件数据。
	char buf[200] = {0};
	fread(buf,20,10,fp);
	
	//3. 关闭文件。
	fclose(fp);
	
	//4. 分割数据。
	friends_strtok_fun(friends_list_head,buf,connfd);
	
	
	
	return;
}

//初始化已保存的好友列表
void init_old_friend(struct friends_info_list *friends_list_head,char *name,int connfd)
{
	//1. 打开目录。
	
	char filename[50];
	
	sprintf(filename,"./friends/%s/",name);
	
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"filename %s\n",filename);
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	DIR* dp = opendir(filename);
	if(dp == NULL)
	{//perror("打开%s文件夹失败!\n",filename);
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"打开%s文件夹失败!\n",filename);
		send(connfd,sendbuf,strlen(sendbuf),0);
	}
	
	//2. 切换到目录下。
	chdir(filename);
    
	
	
	//3. 不断读取目录下的文件名。
	struct dirent *ep = NULL;

	while(1)
	{   
		ep = readdir(dp);
        
		if(ep == NULL) //读取完整个目录
		{
			break;
		}
		
		if(ep->d_name[0] == '.')
		{
			continue;
		}
        
		
		friends_read_file(friends_list_head,ep->d_name,connfd);	
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"1111111\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	//4. 切换到上一级目录。
	chdir("../..");

	
	//5. 关闭目录
	closedir(dp);
	
	return;
}

//打印出一个好友信息
void printer_friends_information(struct friends_info_list *friends_list_pos,int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"好友名:%s\n",friends_list_pos->friends_name);
	send(connfd,sendbuf,strlen(sendbuf),0);
	if(friends_list_pos->online == 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"状态:离线\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		
	}
	else if(friends_list_pos->online == 1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"状态:在线\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
	}
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"connfd:%d\n",friends_list_pos->friends_connfd);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"-------------------------------------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);

}

//显示所有好友信息
void show_all_friends(struct friends_info_list *friends_list_head,int connfd)
{
	struct friends_info_list *pos;

    list_for_each_entry(pos, &friends_list_head->friends_list, friends_list)
    {
        printer_friends_information(pos,connfd);
		pos->online = 0;		
    }
}

//寻找已经上线的好友
int find_friend_online(struct friends_info_list *friends_list_head,struct login_user *login_user_list_head,int connfd)
{

	struct friends_info_list *friends_info_pos;
	
	struct login_user *login_user_pos,*login_user_n;
	
    list_for_each_entry(friends_info_pos, &friends_list_head->friends_list, friends_list)
    {
		list_for_each_entry_safe(login_user_pos,login_user_n, &login_user_list_head->login_user_list, login_user_list)
		{
			if(strcmp(login_user_pos->name,friends_info_pos->friends_name) == 0)
			{
				friends_info_pos->online = 1;
				friends_info_pos->friends_connfd = login_user_pos->connfd;
				

			}
        
		}    
    }
}

//通知好友登录（发信息）
int send_msg_login(struct friends_info_list *friends_info_pos,char *name)
{
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"---------------------------\n");
	send(friends_info_pos->friends_connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"你的好友%s已登录\n",name);
	send(friends_info_pos->friends_connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"---------------------------\n");
	send(friends_info_pos->friends_connfd,sendbuf,strlen(sendbuf),0);
	return 0;
}

//告诉你好友你登录了
int tell_login(struct friends_info_list *friends_list_head,struct login_user *login_user_list_head,int connfd,char *name)
{
	struct friends_info_list *friends_info_pos;
	
	struct login_user *login_user_pos,*login_user_n;
	
    list_for_each_entry(friends_info_pos, &friends_list_head->friends_list, friends_list)
    {
		list_for_each_entry_safe(login_user_pos,login_user_n, &login_user_list_head->login_user_list, login_user_list)
		{
			if(strcmp(login_user_pos->name,friends_info_pos->friends_name) == 0)
			{
				friends_info_pos->friends_connfd = login_user_pos->connfd;
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"---------------------------\n");
				send(friends_info_pos->friends_connfd,sendbuf,strlen(sendbuf),0);
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"你的好友%s上线\n",name);
				send(friends_info_pos->friends_connfd,sendbuf,strlen(sendbuf),0);
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"---------------------------\n");
				send(friends_info_pos->friends_connfd,sendbuf,strlen(sendbuf),0);
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"connfd = %d\n",friends_info_pos->friends_connfd);
				send(connfd,sendbuf,strlen(sendbuf),0);
				//send_msg_login(friends_info_pos,name);
			}
        
		}    
    }

}

//告诉你好友你登录了
int tell_offline(struct friends_info_list *friends_list_head,struct login_user *login_user_list_head,int connfd,char *name)
{
	struct friends_info_list *friends_info_pos;
	
	struct login_user *login_user_pos,*login_user_n;
	
    list_for_each_entry(friends_info_pos, &friends_list_head->friends_list, friends_list)
    {
		list_for_each_entry_safe(login_user_pos,login_user_n, &login_user_list_head->login_user_list, login_user_list)
		{
			if(strcmp(login_user_pos->name,friends_info_pos->friends_name) == 0)
			{
				
				friends_info_pos->friends_connfd = login_user_pos->connfd;
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"---------------------------\n");
				send(friends_info_pos->friends_connfd,sendbuf,strlen(sendbuf),0);
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"你的好友%s已下线\n",name);
				send(friends_info_pos->friends_connfd,sendbuf,strlen(sendbuf),0);
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"---------------------------\n");
				send(friends_info_pos->friends_connfd,sendbuf,strlen(sendbuf),0);
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"connfd = %d\n",friends_info_pos->friends_connfd);
				send(connfd,sendbuf,strlen(sendbuf),0);
				//send_msg_login(friends_info_pos,name);
			}
        
		}    
    }

}

//寻找已登录的用户
struct login_user *friends_find_login_user(struct login_user *login_user_list_head,char *name)
{
	
	struct login_user *login_user_pos,*login_user_n;
	
	int count = 0;
   
		list_for_each_entry_safe(login_user_pos,login_user_n, &login_user_list_head->login_user_list, login_user_list)
		{
			if(strcmp(login_user_pos->name,name) == 0)
			{
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"login_user_pos->name = %s\n",login_user_pos->name);
				send(login_user_pos->connfd,sendbuf,strlen(sendbuf),0);
				return login_user_pos;
			}
        
		}    
    
	return NULL;
}

//加离线好友未
int add_offline_friedns(char *user_name,char *friends_name)
{
	char filename[100] = {0};
	sprintf(filename,"./offline_add/%s_%s.txt",friends_name,user_name);
    printf("%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%d,%d",1,0);

    FILE *fp = fopen(filename,"w+");
}





//好友请求
int add_request(struct login_user *login_user_list_head,char *user_name,char *friends_name,int connfd)
{
	int i;
	char buf[50];
	struct login_user *login_user_pos;
	
	login_user_pos = friends_find_login_user(login_user_list_head,friends_name);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"%s请求添加你为好友1(同意),2(不同意)\n",user_name);
	send(login_user_pos->connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(login_user_pos->connfd,buf,sizeof(buf),0);

	i = atoi(parting(buf));
	
	if(i = 1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"你和%s请求已成为你为好友\n",friends_name);
		send(login_user_pos->connfd,sendbuf,strlen(sendbuf),0);
		
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"%s已同意成为你的好友\n",user_name);
		send(connfd,sendbuf,strlen(sendbuf),0);
		return 0;
	}
	else if(i = 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"%s拒绝成为你的好友\n",friends_name);
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	
	
	
}
	
	





//加在线好友
int add_online_friends(struct login_user *login_user_list_head,char *user_name,char *friends_name,int connfd)
{
	
	if(add_request(login_user_list_head,user_name,friends_name,connfd) != 0)
	{
		return -1;
	}
	
	char filename[100] = {0};
	sprintf(filename,"./friends/%s/%s.txt",user_name,friends_name);
    printf("friends_file:%s\n",filename);

    char filedata[2000]={0};
    sprintf(filedata,"%s,%d",friends_name,1);
	
	char filename1[100] = {0};
	sprintf(filename1,"./friends/%s/%s.txt",friends_name,user_name);
    printf("friends_file1:%s\n",filename1);

    char filedata1[2000]={0};
    sprintf(filedata1,"%s,%d",user_name,1);

    FILE *fp = fopen(filename,"w+");
	FILE *fp1 = fopen(filename1,"w+");
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"写入成功\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	
	fwrite(filedata,strlen(filedata),1,fp);
	fwrite(filedata1,strlen(filedata1),1,fp1);
    fclose(fp1);
	fclose(fp);
	
	
	return 0;

}

//加好友
int add_friends(struct friends_info_list *friends_list_head,struct login_user *login_user_list_head,struct OrdinaryPassNode *Ordinary_passenger_list_head,
						int connfd,char *user_name)
{
	char buf[50];
	char friends_name[50];
	
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入你要添加好友的名字\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strcpy(friends_name,parting(buf));
	
	if(strcmp(user_name,friends_name) == 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"自己加自己？\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	
	if(FindUsers(Ordinary_passenger_list_head, friends_name) == NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"本服务器没有此用户\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	if(find_login_user(login_user_list_head,friends_name) == NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"此用户未登录\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		//add_offline_friedns(user_name,friends_name);
		return -1;
	}
	
	if(add_online_friends(login_user_list_head,user_name,friends_name,connfd) == -1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"好友添加失败\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"好友添加成功\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	return 0;
	
	
}


//清除所有好友信息
void free_all_friends(struct friends_info_list *friends_list_head,int connfd)
{
	struct friends_info_list *pos,*n;

    list_for_each_entry_safe(pos,n,&friends_list_head->friends_list, friends_list)
    {
        free(pos);	
    }
}

//通过名字寻找好友信息
struct friends_info_list *find_friends_blacklist(struct friends_info_list *friends_list_head,char *name,int connfd)
{
	struct friends_info_list *pos;

    list_for_each_entry(pos, &friends_list_head->friends_list, friends_list)
    {
        if(pos->blacklist == 0)
		{
			return pos;
		}
    }
	return NULL;
}


//给好友(发信息)
int send_msg_to_friends(struct friends_info_list *friends_list_head, struct login_user *login_user_list_head, struct OrdinaryPassNode *login_in_list_head, int connfd)
{
	char friends_name[50];
	struct login_user *login_user_pos;
	char buf[50];
	char buf1[50];
	
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"请输入需要聊天的好友\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);

	strcpy(friends_name,parting(buf));
	if(strcmp(friends_name,login_in_list_head->info.name) == 0)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"自己和自己聊天？\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	

	
	login_user_pos = find_login_user(login_user_list_head,friends_name);
	
	
	if(login_user_pos == NULL)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"你确定和和离线好友聊天？\n");
		send(connfd,sendbuf,strlen(sendbuf),0);
		return -1;
	}
	
	while(1)
	{
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"给%s发信息:\n",friends_name);
		send(connfd,sendbuf,strlen(sendbuf),0);
		
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		
		strcpy(buf1,parting(buf));
		
		if(strncmp(buf1,"q1",2) == 0)
		{
			break;
		}
		
		bzero(buf1,sizeof(buf1));
		sprintf(buf1,"来自%s发信息:%s\n",login_in_list_head->info.name,buf);

        SendMsg(buf1, login_user_pos->connfd);
		
	}
	
	return 0;
	
}

struct Circle_of_friends{
	
char name[50];
char content[50];
char time[100];
struct list_head Circle_of_friends_list;

};

struct Circle_of_friends *request_link_Circle_of_friends_list_node(void)
{
    struct Circle_of_friends *new_node;

    new_node = malloc(sizeof(struct Circle_of_friends));
    if(new_node == NULL)
    {
        perror("申请内存失败");
        return NULL;
    }

    INIT_LIST_HEAD(&(new_node->Circle_of_friends_list));//将小个结构体的上下指针指向自己
    return new_node;
}

void insert_Circle_of_friends_list_node_tail(struct Circle_of_friends *Circle_of_friends_list_head, struct Circle_of_friends *Circle_of_friends_list_insert_node)
{
	//printf("name %s\n",Circle_of_friends_list_insert_node->friends_name);
    list_add_tail(&(Circle_of_friends_list_insert_node->Circle_of_friends_list), &(Circle_of_friends_list_head->Circle_of_friends_list));
}

//好友列表分割文件中中的数据
void Circle_of_friends_strtok_fun(struct Circle_of_friends *Circle_of_friends_list_head,char *buf,struct Circle_of_friends *Circle_of_friends_others_list_head,int connfd)
{
	//1. 为新节点申请空间。
	struct Circle_of_friends *new;

    new = request_link_Circle_of_friends_list_node();
	
	struct Circle_of_friends *new_others;

    new_others = request_link_Circle_of_friends_list_node();
	
	char seqs[] = ",";
	
    char *tmp;
	
	tmp = malloc(500*sizeof(buf));

	tmp = strtok(buf,seqs);
	strcpy(new->name,tmp);
	strcpy(new_others->name,tmp);
	
    tmp = strtok(NULL,seqs);
	strcpy(new->content,tmp);
	strcpy(new_others->content,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->time,tmp);
	strcpy(new_others->time,tmp);
	
	//strcpy(new->friends_name,buf);
	
    insert_Circle_of_friends_list_node_tail(Circle_of_friends_list_head,new);
	
	insert_Circle_of_friends_list_node_tail(Circle_of_friends_others_list_head,new_others);
	
	return;
}

void Circle_of_friends_read_file(struct Circle_of_friends *Circle_of_friends_list_head,
									char *filename,struct Circle_of_friends *Circle_of_friends_others_list_head,int connfd)
{
	//1. 打开文件。
	FILE *fp = fopen(filename,"a+");
	if(fp == NULL)
	{	
		perror("打开文件错误!\n");
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"打开%s文件失败!\n",filename);
		send(connfd,sendbuf,strlen(sendbuf),0);
		
	}
	
	//2. 读取文件数据。
	char buf[200] = {0};
	fread(buf,20,10,fp);
	
	//3. 关闭文件。
	fclose(fp);
	
	//4. 分割数据。
	Circle_of_friends_strtok_fun(Circle_of_friends_list_head,buf,Circle_of_friends_others_list_head,connfd);
	
	return;
}

void init_old_Circle_of_friends(struct Circle_of_friends *Circle_of_friends_list_head,struct OrdinaryPassNode *login_in_list_head,
										struct Circle_of_friends *Circle_of_friends_others_list_head,int connfd)
{
	//1. 打开目录。
	
	char filename[50];
	
	sprintf(filename,"./pyq/%s/",login_in_list_head->info.name);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"filename %s\n",filename);
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	DIR* dp = opendir(filename);
	if(dp == NULL)
	{
		//perror("打开%s文件夹失败!\n",filename);
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"打开%s文件夹失败!\n",filename);
		send(connfd,sendbuf,strlen(sendbuf),0);
	}
	
	//2. 切换到目录下。
	chdir(filename);
    
	
	//3. 不断读取目录下的文件名。
	struct dirent *ep = NULL;

	while(1)
	{   
		ep = readdir(dp);
        
		if(ep == NULL) //读取完整个目录
		{
			break;
		}
		
		if(ep->d_name[0] == '.')
		{
			continue;
		}
		
		
     
		Circle_of_friends_read_file(Circle_of_friends_list_head,ep->d_name,Circle_of_friends_others_list_head,connfd);	
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"19852\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	//4. 切换到上一级目录。
	chdir("../..");

	
	//5. 关闭目录
	closedir(dp);
	
	return;
}








//好友的好友列表分割文件中中的数据
void Circle_of_friends_strtok_fun_others(char *buf,struct Circle_of_friends *Circle_of_friends_others_list_head,int connfd)
{
	//1. 为新节点申请空间。
	struct Circle_of_friends *new;

    new = request_link_Circle_of_friends_list_node();
	
	char seqs[] = ",";
	
    char *tmp;
	
	tmp = malloc(500*sizeof(buf));

	tmp = strtok(buf,seqs);
	strcpy(new->name,tmp);
	
    tmp = strtok(NULL,seqs);
	strcpy(new->content,tmp);
	
	tmp = strtok(NULL,seqs);
	strcpy(new->time,tmp);
	
	
	//strcpy(new->friends_name,buf);
	
 
	
	insert_Circle_of_friends_list_node_tail(Circle_of_friends_others_list_head,new);
	
	return;
}

void Circle_of_friends_read_file_others(char *filename,struct Circle_of_friends *Circle_of_friends_others_list_head,int connfd)
{
	//1. 打开文件。
	FILE *fp = fopen(filename,"a+");
	if(fp == NULL)
	{	
		perror("打开文件错误!\n");
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"打开%s文件失败!\n",filename);
		send(connfd,sendbuf,strlen(sendbuf),0);
		
	}
	
	//2. 读取文件数据。
	char buf[200] = {0};
	fread(buf,20,10,fp);
	
	//3. 关闭文件。
	fclose(fp);
	
	//4. 分割数据。
	Circle_of_friends_strtok_fun_others(buf,Circle_of_friends_others_list_head,connfd);
	
	
	return;
}


void init_old_Circle_of_friends_others(struct Circle_of_friends *Circle_of_friends_others_list_head,
									char *name,int connfd)
{
	//1. 打开目录。
	
	char filename[50];
	
	sprintf(filename,"./pyq/%s/",name);
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"filename %s\n",filename);
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	DIR* dp = opendir(filename);
	if(dp == NULL)
	{
		//perror("打开%s文件夹失败!\n",filename);
		bzero(sendbuf,sizeof(sendbuf));
		sprintf(sendbuf,"打开%s文件夹失败!\n",filename);
		send(connfd,sendbuf,strlen(sendbuf),0);
	}
	
	//2. 切换到目录下。
	chdir(filename);
    
	
	//3. 不断读取目录下的文件名。
	struct dirent *ep = NULL;

	while(1)
	{   
		ep = readdir(dp);
        
		if(ep == NULL) //读取完整个目录
		{
			break;
		}
		
		if(ep->d_name[0] == '.')
		{
			continue;
		}
		
		
        
		Circle_of_friends_read_file_others(ep->d_name,Circle_of_friends_others_list_head,connfd);
	}
	
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"19852\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	//4. 切换到上一级目录。
	chdir("../..");

	
	//5. 关闭目录
	closedir(dp);
	
	return;
}

char *get_now_time(void)
{
	struct   tm     *ptm;
	long       ts;
	int         y,m,d,h,n,s;

	ts   =   time(NULL);
	ptm   =   localtime(&ts);

	y   =   ptm-> tm_year+1900;     //年
	m   =   ptm-> tm_mon+1;             //月
	d   =   ptm-> tm_mday;               //日
	h   =   ptm-> tm_hour;               //时
	n   =   ptm-> tm_min;                 //分
	s   =   ptm-> tm_sec; 

	char *buf;
	buf = malloc(500*sizeof(buf));
	time_t   timep;   
    time   (&timep);   
	printf("%d\n",y);
    sprintf(buf,"%d_%d_%d_%d_%d_%d",y,m,d,h,n,s);
	
	return buf;
}


		
int pyq(struct Circle_of_friends *Circle_of_friends_list_head, struct OrdinaryPassNode *login_in_list_head, int connfd)
{
	struct Circle_of_friends *new_node;

    new_node = request_link_Circle_of_friends_list_node();
	
	char buf[50];
	
	
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"内容:\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	//scanf("%s",new_node->info.name);
	
	bzero(buf,sizeof(buf));
	recv(connfd,buf,sizeof(buf),0);
	
	strcpy(new_node->content,parting(buf));
	
	strcpy(new_node->name,login_in_list_head->info.name);
	
	strcpy(new_node->time,get_now_time());
	
    char filename[1000] = {0};
	sprintf(filename,"./pyq/%s/%s.txt",new_node->name,get_now_time());
	
	bzero(sendbuf,sizeof(sendbuf));
    sprintf(sendbuf,"name:%s\n",filename);
	send(connfd,sendbuf,strlen(sendbuf),0);

	
    char filedata[2000]={0};
    sprintf(filedata,"%s,%s,%s",new_node->name,new_node->content,get_now_time());

    FILE *fp = fopen(filename,"w+");
    
    if(fp == NULL)
    {
        perror("打开用户信息文件失败");
    }
    
	insert_Circle_of_friends_list_node_tail(Circle_of_friends_list_head,new_node);
	
    fwrite(filedata,strlen(filedata),1,fp);
    fclose(fp);

}

void printer_Circle_of_friends_information(struct Circle_of_friends *Circle_of_friends_pos,int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"--------------------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"内容:%s\n",Circle_of_friends_pos->content);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"时间:%s\n",Circle_of_friends_pos->time);
	send(connfd,sendbuf,strlen(sendbuf),0);
   	sprintf(sendbuf,"-----------------------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
}

struct Circle_of_friends *show_my_Circle_of_friends(struct Circle_of_friends *Circle_of_friends_list_head,int connfd)
{
	struct Circle_of_friends *pos,*n;

    list_for_each_entry_safe(pos, n,&Circle_of_friends_list_head->Circle_of_friends_list,Circle_of_friends_list)
    {
		printer_Circle_of_friends_information(pos,connfd);
    }
	return NULL;
}




void init_all_friends_Circle_of_friends(struct Circle_of_friends *Circle_of_friends_others_list_head,struct friends_info_list *friends_list_head,int connfd)
{
	struct friends_info_list *pos;

    list_for_each_entry(pos, &friends_list_head->friends_list, friends_list)
    {
        init_old_Circle_of_friends_others(Circle_of_friends_others_list_head,pos->friends_name,connfd);	
    }
}
	
void printer_Circle_of_friends_others_information(struct Circle_of_friends *Circle_of_friends_others_pos,int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"--------------------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"名字:%s\n",Circle_of_friends_others_pos->name);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"内容:%s\n",Circle_of_friends_others_pos->content);
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"时间:%s\n",Circle_of_friends_others_pos->time);
	send(connfd,sendbuf,strlen(sendbuf),0);
   	sprintf(sendbuf,"-----------------------------------------------------------\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
}


struct Circle_of_friends *print_Circle_of_friends_others(struct Circle_of_friends *Circle_of_friends_others_list_head,int connfd)
{
	struct Circle_of_friends *pos,*n;

    list_for_each_entry_safe(pos, n,&Circle_of_friends_others_list_head->Circle_of_friends_list,Circle_of_friends_list)
    {
		printer_Circle_of_friends_others_information(pos,connfd);
    }
	return NULL;
}

struct Circle_of_friends *free_Circle_of_friends_others(struct Circle_of_friends *Circle_of_friends_others_list_head)
{
	struct Circle_of_friends *pos,*n;

    list_for_each_entry_safe(pos, n,&Circle_of_friends_others_list_head->Circle_of_friends_list,Circle_of_friends_list)
    {
		free(pos);
    }
	return NULL;
}


//通过名字寻找好友信息
struct friends_info_list *find_friends(struct friends_info_list *friends_list_head,char *name,int connfd)
{
	struct friends_info_list *pos;

    list_for_each_entry(pos, &friends_list_head->friends_list, friends_list)
    {
        if(strcmp(name,pos->friends_name) == 0)
		{
			return pos;
		}
    }
	return NULL;
}




































//聊天界面
void friends_menu(int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"====================聊天界面=====================\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                         \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                   1. 聊天                 \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                   2. 好友列表		             \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                   3. 添加好友                      \n"); 
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
	sprintf(sendbuf,"                   4. 刷新好友列表                      \n"); 
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                   0. 返回                    \n");
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                             \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"==================================================\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	return;

}

//管理员界面
void admin_menu(int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"====================管理员界面=====================\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                         \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                   1. 录入航班                 \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                   2. 删除航班		             \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                   3. 查询已删除航班                      \n"); 
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                   0. 返回                    \n");
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                             \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"==================================================\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	return;

}

//购票界面
void buy_ticket_menu(int connfd)
{
	
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"==========购票界面==============\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                         \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      1. 航班号买票                 \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      2. 查询自己购买的机票	             \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      3. 退票                         \n"); 
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      4. 改签                    \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      5. 帮别人买票                    \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      0. 返回                             \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                        \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"===============================================\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
 
}

//其他方式查航班信息界面
void check_ticket_menu(int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"=================登录界面=====================\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                         \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      1. 通过目的地寻找航班信息                 \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      2. 通过日期寻找航班信息 		             \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      3. 通过机型寻找航班信息                       \n"); 
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      4. 通过机票价格寻找航班信息                    \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      5. 通过航班号寻找航班信息                    \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"      0. 返回                             \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                        \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"===============================================\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
   	
	return;

}

//登录后主界面
void ticket_menu(int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"====================登录界面=====================\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                         \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"               1. 显示所有机票            \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"               2. 其他方式查机票        \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"               3. 查实名信息              \n"); 
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"               4. 购票                   \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"               5. 查余额、积分、vip                \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"               6. 充值                   \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"               7. 查询自己信息                \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"               8. 修改自己信息               \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"               9. 打印发票               \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"               10.聊天                     \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                      \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"==================================================\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
   
	return;

}

//登录主界面
void login_menu(int connfd)
{
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"========注册界面========\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                         \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"        1. 注册                 \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"        2. 登录		             \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"        3. 忘记密码                      \n"); 
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"        4. 管理员注册                    \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"        5. 管理员登录                    \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"        6. 取票                    \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"        quit(返回)              \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"                                        \n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	bzero(sendbuf,sizeof(sendbuf));
   	sprintf(sendbuf,"=========================\n");
	send(connfd,sendbuf,strlen(sendbuf),0);
	
	return;

}








//聊天界面switch
int friends_switch(struct friends_info_list *friends_list_head, int connfd, struct login_user *login_user_list_head, struct OrdinaryPassNode *login_in_list_head,
                   struct OrdinaryPassNode *Ordinary_passenger_list_head, struct Circle_of_friends *Circle_of_friends_list_head, struct Circle_of_friends *Circle_of_friends_others_list_head)
{
	
	
	int a;
	char buf[50];
	while(1)
	{
		friends_menu(connfd);
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		a = atoi(buf);
		switch(a)
		{
			case 1:	
			send_msg_to_friends(friends_list_head,login_user_list_head,login_in_list_head,connfd);
			break;
			case 2:
			find_friend_online(friends_list_head,login_user_list_head,connfd);
			show_all_friends(friends_list_head,connfd);
			break;
			case 3:
			add_friends(friends_list_head,login_user_list_head,Ordinary_passenger_list_head,
						connfd,login_in_list_head->info.name);
			break;
			case 4:
			free_all_friends(friends_list_head,connfd);
			init_old_friend(friends_list_head,login_in_list_head->info.name,connfd);
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"刷新成功\n");
			send(connfd,sendbuf,strlen(sendbuf),0);
			break;
			case 0:
			goto flight_num_end;
			break;
			
		}	
			
	}
flight_num_end:
	


	return 0;
}

//管理员登录后界面switch
int admin_switch(struct OrdinaryPassNode *Ordinary_passenger_list_head, struct OrdinaryPassNode *login_in_list_head,
                 struct flight_num_pas_node *flight_num_list_head,
                 struct Verified_identity_pas_node *Verified_identity_list_head,
                 struct buy_ticket_node *buy_ticket_list_head, struct admin_node *admin_list_head, struct admin_node *admin_login_in_list_head,
                 struct flight_num_pas_node *rm_flight_num_list_head, int connfd)
{
	int a;
	char buf[50];
	while(1)
	{
		admin_menu(connfd);
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		a = atoi(buf);
		switch(a)
		{
			case 1:
			create_flight_num_information(flight_num_list_head,connfd);
			break;
			case 2:
                allFlightNum(flight_num_list_head, connfd);
			delete_flight_number_Refund_all(flight_num_list_head,Ordinary_passenger_list_head,buy_ticket_list_head,rm_flight_num_list_head,connfd);
			break;
			case 3:
                allFlightNum(rm_flight_num_list_head, connfd);
			break;
			/*case 4:
			delete_flight_number_Refund(flight_num_list_head,Ordinary_passenger_list_head,buy_ticket_list_head);
			break;
			/*case 5:
			if(admin_login_in(admin_list_head,admin_login_in_list_head) == 0)
			{
				
				create_flight_num_information(struct flight_num_pas_node *flight_num_list_head)
			}
			break;
			case 10:
			ShowAllUsers(Ordinary_passenger_list_head);
			//reset_passed(Ordinary_passenger_list_head);
			break;
			case 11:
			show_all_admin(admin_list_head);
			break;*/
			
			case 0:
			goto end;
			break;
			
		}	
	}
end:
return 0;
	//destroy_link_list(Ordinary_passenger_list_head);
}
	
//买票switch
int buy_ticket(struct flight_num_pas_node *flight_num_list_head, struct OrdinaryPassNode *login_in_list_head,
               struct buy_ticket_node *buy_ticket_list_head, struct Verified_identity_pas_node *Verified_identity_list_head,
               struct OrdinaryPassNode *Ordinary_passenger_list_head, int connfd, struct friends_info_list *friends_list_head)
{
	int a;
	char buf[50];
	while(1)
	{
		buy_ticket_menu(connfd);
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		a = atoi(buf);
		switch(a)
		{
			case 1:
                allFlightNum(flight_num_list_head, connfd);
			if(buy_ticket_info(flight_num_list_head,login_in_list_head,
							buy_ticket_list_head,Verified_identity_list_head,
													Ordinary_passenger_list_head,connfd) == 0)
													{
														bzero(sendbuf,sizeof(sendbuf));
														sprintf(sendbuf,"购票成功\n");
														send(connfd,sendbuf,strlen(sendbuf),0);
														
													}
			break;
			case 2:
			if(show_user_ticket_buyer(login_in_list_head,buy_ticket_list_head,connfd) == 0)
			{
				printf("你买票了吗?\n");
				break;
			}
			break;
			case 3:
			if(show_user_ticket_buyer(login_in_list_head,buy_ticket_list_head,connfd) == 0)
			{
				printf("你买票了吗?\n");
				break;
			}
			Refund(flight_num_list_head,login_in_list_head,
							buy_ticket_list_head,Verified_identity_list_head,
													Ordinary_passenger_list_head,connfd);
			break;
			case 4:
			if(show_user_ticket_buyer(login_in_list_head,buy_ticket_list_head,connfd) == 0)
			{
				printf("你买票了吗?\n");
				break;
			}
			Change(flight_num_list_head,login_in_list_head,
							buy_ticket_list_head,Verified_identity_list_head,
													Ordinary_passenger_list_head,connfd);
			break;
			case 5:
                allFlightNum(flight_num_list_head, connfd);
			help_other_buy_ticket_info(flight_num_list_head,login_in_list_head,
							buy_ticket_list_head,Verified_identity_list_head,
													Ordinary_passenger_list_head,connfd,friends_list_head);
			break;
			case 6:
			
			break;
			case 7:
			
			break;
			case 8:
		
			break;
			case 10:
	
			break;
			case 0:
			goto flight_num_end;
			break;
			
		}	
	}
flight_num_end:
	return 0;
}

//其他方式航班信息界面switch
int check_flight_num_switch(struct flight_num_pas_node *flight_num_list_head,int connfd)
{
	int a;
	char buf[50];
	while(1)
	{
		check_ticket_menu(connfd);
		
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		a = atoi(buf);
		
		switch(a)
		{
			case 1:
			if(destinationFindInfoListNode(flight_num_list_head, connfd) == 0)//通过目的地寻找航班信息
			{
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"无匹配航班\n");
				send(connfd,sendbuf,strlen(sendbuf),0);
				
			}
			break;
			case 2:																					
			if(dateFindInfoListNode(flight_num_list_head, connfd) == 0)//通过日期寻找航班信息
			{
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"无匹配航班\n");
				send(connfd,sendbuf,strlen(sendbuf),0);
				
			}
			break;
			case 3:
			if(flightModelFindInfoListNode(flight_num_list_head, connfd) == 0)//通过机型寻找航班信息
			{
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"无匹配航班\n");
				send(connfd,sendbuf,strlen(sendbuf),0);
				
			}
			break;
			case 4:
			if(passThroughFlightPriceFindInfoListNode(flight_num_list_head, connfd) == 0)//通过机票价格寻找航班信息
			{
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"无匹配航班\n");
				send(connfd,sendbuf,strlen(sendbuf),0);
				
			}
			break;
			case 5:
			if(numberFindInfoListNode(flight_num_list_head, connfd) == 0)//通过航班号寻找航班信息
			{
				bzero(sendbuf,sizeof(sendbuf));
				sprintf(sendbuf,"无匹配航班\n");
				send(connfd,sendbuf,strlen(sendbuf),0);
				
			}
			break;
			case 6:
			
			break;
			case 7:
			
			break;
			case 8:
		
			break;
			case 10:
	
			break;
			case 0:
			goto flight_num_end;
			break;
			
		}	
	}
flight_num_end:
	return 0;
}

//登录后界面switch
int flight_num_switch(struct flight_num_pas_node *flight_num_list_head, struct Verified_identity_pas_node *Verified_identity_list_head,
                      struct OrdinaryPassNode *login_in_list_head, struct buy_ticket_node *buy_ticket_list_head,
                      struct OrdinaryPassNode *Ordinary_passenger_list_head, int connfd, struct login_user *login_user_list_head)
{
	
	struct login_user *login_user_pos  = NULL;
	
	login_user_pos = find_login_user(login_user_list_head,login_in_list_head->info.name);
	
	struct friends_info_list *friends_list_head = NULL;
	
	friends_list_head = request_link_friends_list_node();
	
	init_old_friend(friends_list_head,login_in_list_head->info.name,connfd);
	
	tell_login(friends_list_head,login_user_list_head,connfd,login_in_list_head->info.name);
	
	struct Circle_of_friends *Circle_of_friends_list_head = NULL;
	
	Circle_of_friends_list_head = request_link_Circle_of_friends_list_node();
	

	struct Circle_of_friends *Circle_of_friends_others_list_head = NULL;
	
	Circle_of_friends_others_list_head = request_link_Circle_of_friends_list_node();
	
	init_old_Circle_of_friends(Circle_of_friends_list_head,login_in_list_head,Circle_of_friends_others_list_head,connfd);
	
	init_all_friends_Circle_of_friends(Circle_of_friends_others_list_head,friends_list_head,connfd);
	
	int a;
	char buf[50];
	while(1)
	{
		ticket_menu(connfd);
		bzero(buf,sizeof(buf));
		recv(connfd,buf,sizeof(buf),0);
		a = atoi(buf);
		switch(a)
		{
			case 1:
                allFlightNum(flight_num_list_head, connfd);
			break;
			case 2:
			check_flight_num_switch(flight_num_list_head,connfd);
			break;
			case 3:
			//show_all_check_identity_information(Verified_identity_list_head,connfd);
			//ShowAllUsers(Ordinary_passenger_list_head);
			//reset_passwd(Ordinary_passenger_list_head);
			find_check_identity_information(Verified_identity_list_head,login_in_list_head,connfd);
			break;
			case 4:
			if(pay_password(login_in_list_head,connfd) == -1)
			{
				break;
			}	
			buy_ticket(flight_num_list_head,login_in_list_head,
							buy_ticket_list_head,Verified_identity_list_head,
													Ordinary_passenger_list_head,connfd,friends_list_head);
													
			break;
			case 5:
                CheckBalance(login_in_list_head, connfd);
			break;
			case 6:
			if(pay_password(login_in_list_head,connfd) == -1)
			{
				break;
			}	
			Recharge(Ordinary_passenger_list_head,login_in_list_head,connfd);
			break;
			case 7:
                printInfomation(login_in_list_head, connfd);
			break;
			case 8:
                passageInformation(Ordinary_passenger_list_head, login_in_list_head, connfd);
			break;
			case 9:
			invoice(buy_ticket_list_head,login_in_list_head,connfd);
			break;
			case 10:
			friends_switch(friends_list_head,connfd,login_user_list_head,login_in_list_head,Ordinary_passenger_list_head,
								Circle_of_friends_list_head,Circle_of_friends_others_list_head);
			//ShowAllUsers(Ordinary_passenger_list_head);
			//reset_passwd(Ordinary_passenger_list_head);
			break;
			case 0:
			goto flight_num_end;
			break;
			
		}	
	}
flight_num_end:
	
	tell_offline(friends_list_head,login_user_list_head,connfd,login_in_list_head->info.name);
	list_del(&login_user_pos->login_user_list);
	free(login_user_pos);

	return 0;
}








//子线程
void *routine(void *arg)
{
	
	//线程功能： 不断监听这个客户端说的话
	struct list_node *peer = (struct list_node *)arg;
	

	struct OrdinaryPassNode *login_in_list_head  = NULL;
	login_in_list_head = QequestLinkInitNode();
	
	struct OrdinaryPassNode *Ordinary_passenger_list_head  = NULL;
	Ordinary_passenger_list_head = peer->Ordinary_passenger_list_head;
	
	struct flight_num_pas_node *flight_num_list_head  = NULL;
	flight_num_list_head = peer->flight_num_list_head;
	
	
	struct Verified_identity_pas_node *Verified_identity_list_head = NULL;
	Verified_identity_list_head = peer->Verified_identity_list_head;

	struct buy_ticket_node *buy_ticket_list_head = NULL;
	buy_ticket_list_head = peer->buy_ticket_list_head;
	

	struct admin_node *admin_list_head = NULL;
	admin_list_head = peer->admin_list_head;
	
	
	struct admin_node *admin_login_in_list_head  = NULL;
	admin_login_in_list_head = peer->admin_login_in_list_head;

	
	struct flight_num_pas_node *rm_flight_num_list_head = NULL;
	rm_flight_num_list_head = peer->rm_flight_num_list_head;
	
	struct login_user *login_user_list_head  = NULL;
	login_user_list_head = peer->login_user_list_head;
	
	

	
	char buf[50];
	char *tmp = NULL;
	int recv_id;
	int a;
	
	while(1)
	{
		
			bzero(sendbuf,sizeof(sendbuf));
			sprintf(sendbuf,"..............\n\n\n");
			send(peer->connfd,sendbuf,strlen(sendbuf),0);
			sleep(1);
			
			login_menu(peer->connfd);
			bzero(buf,sizeof(buf));
			recv(peer->connfd,buf,sizeof(buf),0);
			
			if(strncmp(buf,"quit",4) == 0)
			{
				a = 0;
			}
			else
			{
				a = atoi(buf);
			}
			
			switch(a)
			{
				case 1:
                    registerPassageInformation(Ordinary_passenger_list_head, peer->connfd);
				break;
				case 2:
				if(loginIn(Ordinary_passenger_list_head, login_in_list_head, peer->connfd, login_user_list_head) == 0)
				{
					flight_num_switch(flight_num_list_head,Verified_identity_list_head,
								login_in_list_head,buy_ticket_list_head,
												Ordinary_passenger_list_head,peer->connfd,login_user_list_head);
				}
				break;
				case 3:
				//ShowAllUsers(Ordinary_passenger_list_head);
				reset_passwd(Ordinary_passenger_list_head,peer->connfd);
				break;
				case 4:
				register_admin_information(admin_list_head,peer->connfd);
				break;
				case 5:
				if(admin_login_in(admin_list_head,admin_login_in_list_head,peer->connfd) == 0)
				{
					admin_switch(Ordinary_passenger_list_head,login_in_list_head,
										flight_num_list_head,
										Verified_identity_list_head,
										buy_ticket_list_head,admin_list_head,admin_login_in_list_head,rm_flight_num_list_head,peer->connfd);
				}
				break;
				case 6:
				check_in(buy_ticket_list_head,peer->connfd);
				//reset_passwd(Ordinary_passenger_list_head);
				break;
				/*case 10:
				ShowAllUsers(Ordinary_passenger_list_head);
				//reset_passwd(Ordinary_passenger_list_head);
				break;
				case 11:
				show_all_admin(admin_list_head);
				break;*/
				 
				case 0:
				
				goto end;
				break;
				
			}
	}
end:

				
				
				close(peer->connfd);
				
				pthread_mutex_lock(&m);
				list_del(&(peer->list));
				pthread_mutex_unlock(&m);		
				
				free(peer);	
				
				pthread_exit(NULL);
				
}



int main(int argc,char *argv[])  //  ./server 50001
{

	//乘客链表创建、初始化
	struct OrdinaryPassNode *Ordinary_passenger_list_head  = NULL;
	Ordinary_passenger_list_head = QequestLinkInitNode();

    InitOldUser(Ordinary_passenger_list_head);

//------------------------------------------------------------------------------


	//航班信息的链表
	struct flight_num_pas_node *flight_num_list_head = NULL;
	flight_num_list_head = request_link_flight_num_list_node();

	init_flight_num_old_usr(flight_num_list_head);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

	//实名认证链表
	struct Verified_identity_pas_node *Verified_identity_list_head = NULL;
	Verified_identity_list_head = request_Verified_link_list_node();

	Verified_identity_init(Verified_identity_list_head);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
	//购票链表
	struct buy_ticket_node *buy_ticket_list_head = NULL;
	buy_ticket_list_head = request_buy_ticket_node();


	buy_ticket_init(buy_ticket_list_head);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
	//管理员注册链表
	struct admin_node *admin_list_head = NULL;
	admin_list_head = request_link_admin_list_node();


	admin_init_old_usr(admin_list_head);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

	//管理员登录后的链表
	struct admin_node *admin_login_in_list_head  = NULL;
	admin_login_in_list_head = request_link_admin_list_node();

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


		//已删除航班信息的链表
	struct flight_num_pas_node *rm_flight_num_list_head = NULL;
	rm_flight_num_list_head = request_link_flight_num_list_node();

    flightNumOldUsr(rm_flight_num_list_head);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

	struct login_user *login_user_list_head  = NULL;
	login_user_list_head = userListNode();



	//1. 初始化链表
	head = init_list_head();

	//2. 创建TCP套接字
	int sockfd = socket(AF_INET,SOCK_STREAM,0);

	//3. 绑定IP地址与端口号
	struct sockaddr_in srvaddr;
	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr,len);

	srvaddr.sin_family = AF_INET;  //协议
	srvaddr.sin_port = htons(atoi(argv[1])); //端口号
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址

	bind(sockfd,(struct sockaddr *)&srvaddr,len);

	//4. 设置监听套接字。
	listen(sockfd,5);

	//5. 不断等待客户端的连接
	int connfd;
	struct sockaddr_in cliaddr;
	struct list_node *new = NULL;
	pthread_t tid;
	while(1)
	{
		connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);

		if(connfd > 0)  //说明真的有人连接进来了
		{
			//6. 先打印一下是谁连接进来的
			printf("new connection: %s->%d\n",inet_ntoa(cliaddr.sin_addr),connfd);

			//7. 将该已连接套接字尾插到链表中。
			new = malloc(sizeof(struct list_node));
			if(new != NULL)
			{
				//8. 为数据域赋值。
				new->connfd = connfd;
					//乘客链表创建、初始化


	new->Ordinary_passenger_list_head = Ordinary_passenger_list_head;

//------------------------------------------------------------------------------

	//航班信息的链表


	new->flight_num_list_head = flight_num_list_head;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

	//实名认证链表


	new->Verified_identity_list_head = Verified_identity_list_head;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
	//购票链表


	new->buy_ticket_list_head = buy_ticket_list_head;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
	//管理员注册链表


	new->admin_list_head = admin_list_head;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

	//管理员登录后的链表


	new->admin_login_in_list_head = admin_login_in_list_head;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
	//已删除航班信息的链表

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


	new->rm_flight_num_list_head = rm_flight_num_list_head;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

	new->login_user_list_head = login_user_list_head;




				//9. 尾插。
				pthread_mutex_lock(&m);
				list_add_tail(&(new->list),&(head->list));
				pthread_mutex_unlock(&m);

				//10. 为这个新的客户端分配一个线程。
				pthread_create(&tid,NULL,routine,(void *)new);
			}
		}

		//11. 继续第5步即可。
	}

	return 0;
}