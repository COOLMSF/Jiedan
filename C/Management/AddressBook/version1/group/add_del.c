/*
 * Description: 初始化
 */
int init(LinkList *head)
{
	*head = (LinkList)malloc(sizeof(Node));
	strcpy((*head)->number,"\0");
	strcpy((*head)->name,"\0");
	(*head)->next = NULL;

	return 0;
}

/*
 * Description:　增加
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
 * Description: 删除
 */
int del(LinkList head)
{
	char d_name[NAME_LEN];
	Node *cur = NULL;
	Node *pre = NULL;
	list(head);
	printf("请输入要删除的联系人姓名:\n");
	scanf("%s", d_name);
	
	cur = head->next;
	pre = head;
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
