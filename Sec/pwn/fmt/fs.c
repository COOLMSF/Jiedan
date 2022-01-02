#include <stdio.h>
char passwd[80];


void main() {

	printf("Please enter password:");
	if (login() == 'T')
		welcome();
	else 
		quit();
}

int  login()
{
	int success = 'F';
	int *t = &success;
	gets(passwd);
	printf("Password entered:");
	printf(passwd);
	printf("\n");
	return *t;

}
void welcome()
{
	printf("welcome, you are logged in!\n");
	exit(0);
}
void quit()
{
	printf("Sorry,password is incorrect.\n");
	exit(1);
}
