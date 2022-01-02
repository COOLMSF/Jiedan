#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 名字长度为32
 */
#define NAME_LEN 32
#define MAX_STR 255

typedef struct _Device {
	char id[MAX_STR];
    char type[MAX_STR];
	char device_name[MAX_STR];
	char brand_name[MAX_STR];
	double price;
	char buy_date[MAX_STR];
	char is_bad[MAX_STR];
	struct _Device *next;
}Node, *LinkList;

int welcome_menu(char *choice, LinkList head);
int init(LinkList *head);
int add(LinkList head);
int del(LinkList head);
int modify(LinkList head);
int query(LinkList head);
int save(LinkList head);
int list(LinkList head);
/*
 * 遍历链表,列出信息
 */
int list(LinkList head)
{
	Node *cur = NULL;
	
	printf("\tid\t\t\t种类\t\t\t设备名称\t\t\t品牌名称\t\t\t价格\t\t\t购入日期\t\t\t是否报废\n");
	
	cur = head->next;
	while (cur != NULL) {
		printf("\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%lf\t\t\t%s\t\t\t%s\n", cur->id,
		 cur->type, cur->device_name, cur->brand_name, cur->price, cur->buy_date, cur->is_bad);
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

	printf("请输入要查询的设备名或者id号:\n");
	scanf("%s", q_name);
    // 指向头节点的下一个指针
	cur = head->next;
    // 遍历链表
	while (cur != NULL) {
        // 找到对应名字的节点
		if ((0 == strcmp(q_name, cur->device_name)) || (0 == strcmp(q_name, cur->id))) {
            // 输出信息
			printf("查询到的信息如下:\n");
			printf("\tid\t\t设备名\t\t类型\t\t品牌名\t\t价格\t\t购入日期\t\t是否报废\n");
			printf("\t%s\t\t%s\t\t%s\t\t%s\t\t%lf\t\t%s\t\t%s\n", cur->id, 
			cur->device_name, cur->type, cur->brand_name, cur->price, cur->buy_date, cur->is_bad);
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
	fprintf(w_file, "\tid\t\t设备名\t\t类型\t\t品牌名\t\t价格\t\t购入日期\t\t是否报废\n");
	cur = head->next;
	while (cur != NULL) {
		fprintf(w_file, "\t%s\t\t%s\t\t%s\t\t%s\t\t%lf\t\t%s\t\t%s\n", 
		cur->id, cur->device_name, cur->type, cur->brand_name, cur->price, cur->buy_date, cur->is_bad);
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
	printf("请输入要删除的设备名:\n");
	scanf("%s", d_name);
	
    // 指向头节点的下一个节点
	cur = head->next;
	pre = head;
    // 遍历所有节点，找到要删除的节点
	while (cur != NULL) {
		if (0 == (strcmp(d_name, cur->device_name))) {
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

	printf("请输入设备id:\n");
	scanf("%s", newnode->id);
	printf("请输入设备名称:\n");
	scanf("%s", newnode->device_name);
	printf("请输入类型:\n");
	scanf("%s", newnode->type);
	printf("请输入品牌名:\n");
	scanf("%s", newnode->brand_name);
	printf("请输入设备价格:\n");
	scanf("%lf", &newnode->price);
	printf("请输入购入日期:\n");
	scanf("%s", newnode->buy_date);
	printf("是否报废:\n");
	scanf("%s", newnode->is_bad);


	/*头插法*/
	newnode->next = head->next;
	head->next = newnode;
	return 0;
}


/*
 * 修改
 */
int modify(LinkList head)
{
	Node *cur = NULL;
	char m_name[NAME_LEN];	

	printf("请输入要修改的设备名:\n");
	scanf("%s", m_name);
    
    // 遍历链表
	cur = head->next;
	while (cur != NULL) {
		if (0 == (strcmp(m_name, cur->device_name))) {
			printf("请重新输入设备名:");
			scanf("%s", cur->device_name);
			printf("请重新输入设备编号:");
			scanf("%s", cur->id);
			printf("修改成功!\n");
			return 0;
		}
		cur = cur->next;
	}

	printf("未找到设备:%s\n", m_name);

	return 0;
}



/*
 * 欢迎界面
 */
int welcome_menu(char *choice, LinkList head)
{
menu:
	printf("-----------------------------------------------------\n");
	printf("\t\t\t设备管理系统\t\t\t\n");
	printf("\n");
	printf("\t\t\t1.查询设备\n");
	printf("\t\t\t2.增加设备\n");
	printf("\t\t\t3.编辑设备\n");
	printf("\t\t\t4.删除设备\n");
	printf("\t\t\t5.退出设备管理系统\n");
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
	strcpy((*head)->id,"\0");
	strcpy((*head)->brand_name,"\0");
	strcpy((*head)->buy_date,"\0");
	strcpy((*head)->device_name,"\0");
	strcpy((*head)->is_bad,"\0");
	strcpy((*head)->type,"\0");
	(*head)->next = NULL;

	return 0;
}

// 主函数
int main()
{
	LinkList head = NULL;
	char choice = '\0';

	init(&head);
	welcome_menu(&choice, head);
		
	return EXIT_SUCCESS;
}


