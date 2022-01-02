/*
 * Descritpion: 欢迎界面
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
	
	system("cls");
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
