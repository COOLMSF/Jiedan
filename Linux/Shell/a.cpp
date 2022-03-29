
#include <stdio.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

#include <iostream>
using namespace std;

char *trim_newline(char *p)
{
	char *new_p = p;
	int i = 0;
	char *new_array = (char *)malloc(100);
	memset(new_array, 0, 100);
	
	while (*new_p != '\0') {
		if (*new_p == '\n' || *new_p == ' ') {
			new_p++;
			continue;
		}
		new_array[i] = *new_p;
		new_p++;
		i++;
	}
	return new_array;
}

void remove_spaces(char* s) {
    char* d = s;
    do {
        while (*d == ' ' || *d == '\n') {
            ++d;
        }
    } while (*s++ = *d++);
}

int main(void)
{


	// printing current working directory
	while (true) {
		char input[100];
		char address[100];
		char input2[100];
     char *array[100];
	
		printf("minishell:");
		printf("%s", getcwd(address, 100));
		printf("$");
		cin >> input;

		if (input[0] == 'c' && input[1] == 'd') {
			cin >> input2;

			if (chdir(input2) == 0) {
				getcwd(input2, 100);
				chdir(input2);

			}
			else {
				printf("Error\n");

			}
		}
		else if (input[0] == 'd' && input[1] == 'i' && input[2] == 'r') {

			DIR* dir;
			struct dirent* ptr;
			int i;
			dir = opendir(address);
			while ((ptr = readdir(dir)) != NULL)
			{
				printf("%s\n", ptr->d_name);
			}
			closedir(dir);

		}
		else if (input[0] == 'r' && input[1] == 'u' && input[2] == 'n') {
   


 
  char str[100];
  char *p = NULL;
  char *temp;
  int i = 0;

  fgets(str, 100, stdin);  // Use fgets instead of gets.

  p = strtok(str," ");
 printf ("%s",str);
  cout<< endl;
  
  // char* o="peter";
  // array[i]=o;
  // printf ("%s",array[i]);
  // cout << endl;
 
  while (p != NULL) {
     printf("%d",i);
     cout << endl;

	remove_spaces(p);

    array[i++] = p;
    p = strtok(NULL, " ");
  }
  array[i] = NULL;
	
	
 
	printf ("--- Process %d is running\n", getpid());
   
			pid_t pid;
			int status = 0;
			pid = fork();

			if (pid > 0) // parent process: after child process finishes, the parent process continues
			{
				// pid = wait(&status);
				printf("--- End of Parent Process %d\n", getpid());
			}
			else if (pid == 0) // child process
			{
				// char *temp_str = remove_spaces(str);
				remove_spaces(str);
				if (execvp(str, array) < 0) //execute the program called "counting"
					printf("execvp is failed for process. \n");

			}
			else // fork failed
			{
				printf("fork is failed!\n");
				exit(EXIT_FAILURE);
			}
	// exit (EXIT_SUCCESS);
		}

	}
	return 0;
}


