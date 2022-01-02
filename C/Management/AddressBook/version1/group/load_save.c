/*
 * Description: 加载
 */
int load(LinkList head)
{
	FILE *r_file = NULL;
	Node *newnode = NULL;

	r_file = fopen("data.txt", "rt");
	if (!r_file) {
		perror("fopen");
		r_file = fopen("data.txt", "wt");
		fclose(r_file);
		return 0;
	}
	
	
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

#ifdef DEBUG
	list(head);
#endif 


	return 0;
}

/*
 * Description: 保存
 */
int save(LinkList head)
{
	Node *cur = NULL;
	FILE *w_file = NULL;

	w_file = fopen("./data.txt", "wt");
	if (!w_file) {
		perror("fopen");
		exit(-1);
	}

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
 * Description: 列出信息
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
