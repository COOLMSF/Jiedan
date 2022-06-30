#include "command.hh"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>

int yyparse(void);

extern "C" void interrupt_process( int )
{
	printf("\n");
	Command::_currentCommand.prompt();
}

extern "C" void slay_process( int )
{
	int status;
	pid_t pid;

	pid = wait3(&status, 0, NULL);

	while(waitpid(-1, NULL, WNOHANG) > 0);

	if (pid > 0) {
		printf("%d exited.\n", pid);
	}
}

int main() {
	struct sigaction ctrlc;
	ctrlc.sa_handler = interrupt_process;
	sigemptyset(&ctrlc.sa_mask);
	ctrlc.sa_flags = SA_RESTART;

	if(sigaction(SIGINT, &ctrlc, NULL)){
		perror("sigaction");
		exit(2);
	}

	struct sigaction zombieslayer;
	zombieslayer.sa_handler = slay_process;
	sigemptyset(&zombieslayer.sa_mask);
	zombieslayer.sa_flags = SA_RESTART;

	if(sigaction(SIGCHLD, &zombieslayer, NULL)){
		perror("sigaction");
		exit(3);
	}

	setenv("PROMPT", "rubbish> ", 1);

	char* rcPath = (char *) malloc(sizeof(char) * 128);
	strcpy(rcPath, getenv("HOME"));
	strcat(rcPath, "/.shellrc");

	// TODO: Fix source.
	if (0 && access(rcPath, F_OK) != -1) {
		SimpleCommand* sourceCommand = new SimpleCommand();
		char* srcStr = strdup("source");
		sourceCommand->insertArgument(srcStr);
		sourceCommand->insertArgument(rcPath);
		Command::_currentCommand.insertSimpleCommand(sourceCommand);
		//Command::_currentCommand.print();
		//fprintf(stderr, "Sourcing %s ...\n", rcPath);
		Command::_currentCommand.execute();
	} else {
		// Create this file?
		Command::_currentCommand.prompt();
	}

	yyparse();
}
