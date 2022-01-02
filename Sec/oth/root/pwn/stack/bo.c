#include <stdio.h>

void main()
{
    printf("Please enter password: ");
    if (login() == 'T')
        welcome();
    else 
      quit();
}

int login()
{
	int success = 'F';
	char passwd[80];
	gets(passwd);
	return success;
}

void welcome()
{
	printf("welcome, you are logged in!\n");
	exit(0);
}

void quit()
{
	printf("The Password is incorrect.\n");
	exit(1);
}
