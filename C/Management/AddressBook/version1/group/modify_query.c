/*
 * Description:　修改
 */
int modify(LinkList head)
{
	Node *cur = NULL;
	char m_name[NAME_LEN];	

	printf("请输入要修改的联系人姓名:\n");
	scanf("%s", m_name);

	cur = head->next;
	while (cur != NULL) {
		if (0 == (strcmp(m_name, cur->name))) {
			printf("请重新输入姓名:");
			scanf("%s", cur->name);
			printf("请重新输入电话号码:");
			scanf("%s", cur->number);
			printf("修改成功!\n");
			
		#ifdef DEBUG
			list(head);
		#endif
			return 0;
		}
		cur = cur->next;
	}

	printf("未找到联系人:%s\n", m_name);

	return 0;
}

/*
 * Description: 查询
 */
int query(LinkList head)
{
	Node *cur = NULL;
	char q_name[NAME_LEN];

	printf("请输入要查询的联系人姓名或号码:\n");
	scanf("%s", q_name);
	cur = head->next;
	while (cur != NULL) {
		if ((0 == strcmp(q_name, cur->name)) || (0 == strcmp(q_name, cur->number))) {
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
