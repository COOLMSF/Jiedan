#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int choice = 0;

/*
 * ���ֳ���Ϊ32
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
 * ��������,�г���
 Ϣ
 */
int list(LinkList head)
{
	Node *cur = NULL;
	
//	printf("\tid\t\t\t����\t\t\t�豸����\t\t\tƷ������\t\t\t�۸�\t\t\t��������\t\t\t�Ƿ񱨷�\n");
	
	cur = head->next;
	while (cur != NULL) {
			// printf("��ѯ������Ϣ����:\n");
			printf("id:%s\n�豸��:%s\n����:%s\nƷ����:%s\n�۸�:%lf\n��������:%s\n�Ƿ񱨷�:%s\n", cur->id, 
			cur->device_name, cur->type, cur->brand_name, cur->price, cur->buy_date, cur->is_bad);
		// printf("\t%s\t\t\t%s\t\t\t%s\t\t\t%s\t\t\t%lf\t\t\t%s\t\t\t%s\n", cur->id,
		 // cur->type, cur->device_name, cur->brand_name, cur->price, cur->buy_date, cur->is_bad);
		cur = cur->next;
	}

	return 0;
}

/*
 * ��ѯ��Ϣ
 */
int query(LinkList head)
{
	Node *cur = NULL;
	char q_name[NAME_LEN] = { 0 };
	
	printf("������Ҫ��ѯ���豸������id��:\n");
	 //getchar();
	scanf("%s", q_name);
    // ָ��ͷ�ڵ����һ��ָ��
	cur = head->next;
    // ��������
	while (cur != NULL) {
        // �ҵ���Ӧ���ֵĽڵ�
		if ((0 == strcmp(q_name, cur->device_name)) || (0 == strcmp(q_name, cur->id))) {
            // �����Ϣ
			printf("��ѯ������Ϣ����:\n");
			printf("id:%s\n�豸��:%s\n����:%s\nƷ����:%s\n�۸�:%lfs\n��������:%s\n�Ƿ񱨷�s:%s\n", 
				cur->id, cur->device_name, cur->type, cur->brand_name, cur->price, cur->buy_date, cur->is_bad);
			return 0;
		}
		cur = cur->next;
	}
	
	printf("���ݿ��������Ϣ!\n");
	return 0;
}
/*
 * ���浽�ļ�
 */
int save(LinkList head)
{
	Node *cur = NULL;
	FILE *w_file = NULL;

    // ���ļ�
	w_file = fopen("data.txt", "wt");
	if (!w_file) {
		perror("fopen");
		exit(-1);
	}

    // ����ָ�룬��������������Ϣ���ļ�
	fprintf(w_file, "\tid\t\t�豸��\t\t����\t\tƷ����\t\t�۸�\t\t��������\t\t�Ƿ񱨷�\n");
	cur = head->next;
	while (cur != NULL) {
		fprintf(w_file, "\t%s\t\t%s\t\t%s\t\t%s\t\t%lf\t\t%s\t\t%s\n", cur->id, cur->device_name, cur->type, cur->brand_name, cur->price, cur->buy_date, cur->is_bad);
		cur = cur->next;
	}
	
	printf("�������ݳɹ�!\n");

	return 0;
}


/*
 * ɾ��
 */
int del(LinkList head)
{
	char d_name[NAME_LEN] = { 0 };
	Node *cur = NULL;
	Node *pre = NULL;
	//list(head);
	printf("������Ҫɾ�����豸��:\n");
	scanf("%s", d_name);
	
    // ָ��ͷ�ڵ����һ���ڵ�
	cur = head->next;
	pre = head;
    // �������нڵ㣬�ҵ�Ҫɾ���Ľڵ�
	while (cur != NULL) {
		if (0 == (strcmp(d_name, cur->device_name))) {
			pre->next = cur->next;
			free(cur);
		}
		pre = pre->next;
		cur = cur->next;
		break;
	}

	// printf("ɾ���ɹ���\n");

	return 0;
}



/*
 * ����
 */
int add(LinkList head)
{
	Node *newnode = NULL;	

	if (!(newnode = (Node *)malloc(sizeof(Node)))) {
		perror("malloc");
	}

	printf("�������豸id:\n");
	scanf("%s", newnode->id);
	printf("�������豸����:\n");
	scanf("%s", newnode->device_name);
	printf("����������:\n");
	scanf("%s", newnode->type);
	printf("������Ʒ����:\n");
	scanf("%s", newnode->brand_name);
	printf("�������豸�۸�:\n");
	scanf("%lf", &newnode->price);
	printf("�����빺������:\n");
	scanf("%s", newnode->buy_date);
	printf("�Ƿ񱨷�:\n");
	scanf("%s", newnode->is_bad);


	/*ͷ�巨*/
	newnode->next = head->next;
	head->next = newnode;
	return 0;
}


/*
 * �޸�
 */
int modify(LinkList head)
{
	Node *cur = NULL;
	char m_name[NAME_LEN];	

	printf("������Ҫ�޸ĵ��豸��:\n");
	scanf("%s", m_name);
    
    // ��������
	cur = head->next;
	while (cur != NULL) {
		if (0 == (strcmp(m_name, cur->device_name))) {
			printf("�����������豸��:");
			scanf("%s", cur->device_name);
			printf("�����������豸���:");
			scanf("%s", cur->id);
			printf("�޸ĳɹ�!\n");
			return 0;
		}
		cur = cur->next;
	}

	printf("δ�ҵ��豸:%s\n", m_name);

	return 0;
}



/*
 * ��ӭ����
 */
int welcome_menu(char *c, LinkList head)
{
menu:
	printf("-----------------------------------------------------\n");
	printf("\t\t\t�豸����ϵͳ\t\t\t\n");
	printf("\n");
	printf("\t\t\t1.��ѯ�豸\n");
	printf("\t\t\t2.�����豸\n");
	printf("\t\t\t3.�༭�豸\n");
	printf("\t\t\t4.ɾ���豸\n");
	// printf("\t\t\t5.�����ļ�\n");
	printf("\t\t\t5.�˳��豸����ϵͳ\n");
	printf("-----------------------------------------------------\n");

	choice = getchar();
	printf("choice = %c\n", choice);
	setbuf(stdin, NULL);
	
	// system("cls");
	// list(head);
	switch (choice) {
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
			printf("�����ѡ����������������!\n");
			goto menu;
	}
	getchar();
	goto menu;

	return 0;
}

/*
 * �����ʼ��
 */
int init(LinkList *head)
{
    // �����ڴ�
	*head = (LinkList)malloc(sizeof(Node));
    // ��ʼ��
	strcpy((*head)->id,"\0");
	strcpy((*head)->brand_name,"\0");
	strcpy((*head)->buy_date,"\0");
	strcpy((*head)->device_name,"\0");
	strcpy((*head)->is_bad,"\0");
	strcpy((*head)->type,"\0");
	(*head)->next = NULL;

	return 0;
}

// ������
int main()
{
	LinkList head = NULL;


	init(&head);
	welcome_menu(NULL, head);
		
	return EXIT_SUCCESS;
}


