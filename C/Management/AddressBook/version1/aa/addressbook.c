#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 名字长度为32
 */
#define NAME_LEN 32

/*
 * 电话长度为32
 */
#define NUMBER_LEN 32

/*
 * 定义联系人节点
 */
typedef struct contact_person{
	char number[NUMBER_LEN];
	char name[NAME_LEN];
	struct contact_person *next;
}Node, *LinkList;

/*
 * 遍历链表,列出信息
 */
int list(LinkList head)
{
	Node *cur = NULL;
	
	printf("\t姓名\t\t\t号码\n");
	
	cur = head->next;
	while (cur != NULL) {
		printf("\t%s\t\t%s\n", cur->name, cur->number);	
		cur = cur->next;
	}

	return 0;
}

/*
 * 查询信息
 */
int query(LinkList head)
{
	Node *cur = NULL;
	char q_name[NAME_LEN];

	printf("请输入要查询的联系人姓名或号码:\n");
	scanf("%s", q_name);
    // 指向头节点的下一个指针
	cur = head->next;
    // 遍历链表
	while (cur != NULL) {
        // 找到对应名字的节点
		if ((0 == strcmp(q_name, cur->name)) || (0 == strcmp(q_name, cur->number))) {
            // 输出信息
			printf("查询到的联系人信息如下:\n");
			printf("\t姓名\t\t号码\n");
			printf("\t%s\t\t%s\n", cur->name, cur->number);
			return 0;
		}
		cur = cur->next;
	}
	
	printf("数据库无相关信息!\n");

	return 0;
}
/*
 * 保存到文件
 */
int save(LinkList head)
{
	Node *cur = NULL;
	FILE *w_file = NULL;

    // 打开文件
	w_file = fopen("data.txt", "wt");
	if (!w_file) {
		perror("fopen");
		exit(-1);
	}

    // 遍历指针，保存所有链表信息到文件
	cur = head->next;
	while (cur != NULL) {
		fprintf(w_file, "%s\t%s\n", cur->name, cur->number);
		printf("正在写入数据: %s\t%s...\n", cur->name, cur->number);
		cur = cur->next;
	}
	
	printf("保存数据成功!\n");

	return 0;
}


/*
 * 删除
 */
int del(LinkList head)
{
	char d_name[NAME_LEN];
	Node *cur = NULL;
	Node *pre = NULL;
	list(head);
	printf("请输入要删除的联系人姓名:\n");
	scanf("%s", d_name);
	
    // 指向头节点的下一个节点
	cur = head->next;
	pre = head;
    // 遍历所有节点，找到要删除的节点
	while (cur != NULL) {
		if (0 == (strcmp(d_name, cur->name))) {
			printf("将要删除联系人:%s 号码:%s\n", cur->name, cur->number);
			pre->next = cur->next;
			free(cur);
		}
		pre = pre->next;
		cur = cur->next;
	}

	printf("删除成功！\n");

	return 0;
}



/*
 * 增加
 */
int add(LinkList head)
{
	Node *newnode = NULL;	

	if (!(newnode = (Node *)malloc(sizeof(Node)))) {
		perror("malloc");
	}

	printf("请输入联系人姓名:\n");
	scanf("%s", newnode->name);
	printf("请输入联系人号码:\n");
	scanf("%s", &newnode->number);

	if (strlen(newnode->number) == 11) {
		/*头插法*/
		newnode->next = head->next;
		head->next = newnode;
	} else {
		printf("请输入正确的电话\n");
		printf("程序即将退出\n");
		exit(-1);
	}
	

	return 0;
}


/*
 * 修改
 */
int modify(LinkList head)
{
	Node *cur = NULL;
	char m_name[NAME_LEN];	

	printf("请输入要修改的联系人姓名:\n");
	scanf("%s", m_name);
    
    // 遍历链表
	cur = head->next;
	while (cur != NULL) {
		if (0 == (strcmp(m_name, cur->name))) {
			printf("请重新输入姓名:");
			scanf("%s", cur->name);
			printf("请重新输入电话号码:");
			scanf("%s", cur->number);
			printf("修改成功!\n");
			return 0;
		}
		cur = cur->next;
	}

	printf("未找到联系人:%s\n", m_name);

	return 0;
}



/*
 * 欢迎界面
 */
int welcome_menu(char *choice, LinkList head)
{
menu:
	printf("-----------------------------------------------------\n");
	printf("\t\t\t通讯录管理系统\t\t\t\n");
	printf("\n");
	printf("\t\t\t1.查询联系人\n");
	printf("\t\t\t2.增加联系人\n");
	printf("\t\t\t3.编辑联系人\n");
	printf("\t\t\t4.删除联系人\n");
	printf("\t\t\t5.退出通讯录系统\n");
	printf("-----------------------------------------------------\n");

	*choice = getchar();
	printf("choice = %c\n", *choice);
	setbuf(stdin, NULL);
	
	// system("cls");
	list(head);
	switch (*choice) {
		case '1': 
			query(head); 
			break;
		case '2': 
			add(head); 
			save(head); 
			break;
		case '3': 
			modify(head); 
			save(head);
			break;
		case '4': 
			del(head);
			save(head);
			break;
		case '5':
			exit(0);
		default : 
			printf("输入的选项有误，请重新输入!\n");
			goto menu;
	}
	getchar();
	goto menu;

	return 0;
}

/*
 * 链表初始化
 */
int init(LinkList *head)
{
    // 分配内存
	*head = (LinkList)malloc(sizeof(Node));
    // 初始化
	strcpy((*head)->number,"\0");
	strcpy((*head)->name,"\0");
	(*head)->next = NULL;

	return 0;
}

/*
 * 加载文件到内存
 */
int load(LinkList head)
{
	FILE *r_file = NULL;
	Node *newnode = NULL;

    // 打开文件
	r_file = fopen("data.txt", "rt");
	if (!r_file) {
		perror("fopen");
		r_file = fopen("data.txt", "wt");
		fclose(r_file);
		return 0;
	}
	
	
    // 直到文件末尾
	while (!feof(r_file)) {
		if (!(newnode = (Node *)malloc(sizeof(Node)))) {
			perror("malloc");
			exit(-1);
		}
		fscanf(r_file, "%s\t%s\n", newnode->name, newnode->number);
		printf("读入数据:%s\t%s...\n", newnode->name, newnode->number);
		newnode->next = head->next;
		head->next = newnode;
	}
	printf("读入数据完毕!\n");

	fclose(r_file);

	return 0;
}

// 主函数
int main()
{
	LinkList head = NULL;
	char choice = '\0';

	init(&head);
	load(head);
	welcome_menu(&choice, head);
		
	return EXIT_SUCCESS;
}


