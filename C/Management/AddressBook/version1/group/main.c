int main(int argc, char *argv[])
{
	LinkList head = NULL;
	char choice = '\0';

	init(&head);
	load(head);
	welcome_menu(&choice, head);
		
	return EXIT_SUCCESS;
}
