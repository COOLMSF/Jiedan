/*
 * CS252: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#include "command.hh"

Command::Command()
{
	// Create available space for one simple command
	_numOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numOfSimpleCommands = 0;
	_outFile = 0;
	_inFile = 0;
	_errFile = 0;
	_background = 0;
}

void Command::insertSimpleCommand( SimpleCommand * simpleCommand ) {
	if ( _numOfAvailableSimpleCommands == _numOfSimpleCommands ) {
		_numOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			_numOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}

	_simpleCommands[ _numOfSimpleCommands ] = simpleCommand;
	_numOfSimpleCommands++;
}

void Command::clear() {
	for ( int i = 0; i < _numOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}

		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}

	if ( _outFile ) {
		free( _outFile );
	}

	if ( _inFile && (_inFile != _outFile) ) {
		free( _inFile );
	}

	if ( _errFile && (_errFile != _outFile) && (_errFile != _inFile) ) {
		free( _errFile );
	}

	_numOfSimpleCommands = 0;
	_outFile = 0;
	_inFile = 0;
	_errFile = 0;
	_background = 0;
}

void Command::print() {
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");

	for ( int i = 0; i < _numOfSimpleCommands; i++ ) {
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
		printf("\n");
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inFile?_inFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");
	printf( "\n\n" );

}

void Command::execute() {
	// Don't do anything if there are no simple commands
	if ( _numOfSimpleCommands == 0 ) {
		prompt();
		return;
	}

	// Print contents of Command data structure
	//print();

	// Add ion here
	// For every simple command fork a new process
	// Setup i/o redirection
	// and call exec

	// Initialize file descriptors.
	int tempStdIn = -1, tempStdOut = -1, tempStdErr = -1;
	int inFileFd = -1, outFileFd = -1, errFileFd = -1;

	// Make a link back to the original standard I/O.
	tempStdIn = dup(0);
	tempStdOut = dup(1);
	tempStdErr = dup(2);

	// Load the input file if available.
	if (_inFile && _inFile[0]) {
		inFileFd = open(_inFile, O_RDONLY);
	} else {
		inFileFd = dup(tempStdIn);
	}

	// Load the error file if available.
	if (_errFile && _errFile[0]) {
		if (_appendErr) {
			errFileFd = open(_errFile, O_CREAT | O_RDWR | O_APPEND, 0664);
		} else {
			errFileFd = open(_errFile, O_CREAT | O_RDWR | O_TRUNC, 0664);
		}
	} else {
		errFileFd = dup(tempStdErr);
	}

	// Errors always go to the same place, regardless of piping.
	dup2(errFileFd, 2);
	close(errFileFd);
	errFileFd = -2;

	// Iterate over simple commands.
	for ( int i = 0; i < _numOfSimpleCommands; i++ ) {
		// Load in the next input file (works with piping).


		//lastArg = _simpleCommands[i]->_arguments[_simpleCommands[i]->_numOfArguments];

		dup2(inFileFd, 0);
		close(inFileFd);
		inFileFd = -2;

		if (i == _numOfSimpleCommands - 1) {
			// Load the output file if available on the last simple command.
			if (_outFile && _outFile[0]) {
				if (_appendOut) {
					outFileFd = open(_outFile, O_CREAT | O_RDWR | O_APPEND, 0664);
				} else {
					outFileFd = open(_outFile, O_CREAT | O_RDWR | O_TRUNC, 0664);
				}
			} else {
				outFileFd = dup(tempStdOut);
			}
		} else {
			// Pipe if not the last command.
			int fdPipe[2];
			pipe(fdPipe);

			outFileFd = fdPipe[1];
			inFileFd = fdPipe[0];
		}

		// Redirect the output (works with piping).
		dup2(outFileFd, 1);
		close(outFileFd);
		outFileFd = -2;

		if (strcmp(_simpleCommands[i]->_arguments[0], "exit") == 0) {
			exit(0);
		//} else if (strcmp(_simpleCommands[i]->_arguments[0], "printenv") == 0) {

		} else if (strcmp(_simpleCommands[i]->_arguments[0], "setenv") == 0) {
			setenv(_simpleCommands[i]->_arguments[1],
					_simpleCommands[i]->_arguments[2], 1);
		} else if (strcmp(_simpleCommands[i]->_arguments[0], "unsetenv") == 0) {
			unsetenv(_simpleCommands[i]->_arguments[1]);
		//} else if (strcmp(_simpleCommands[i]->_arguments[0], "source") == 0) {
			//printf("NOT YET IMPLEMENTED");
		} else if (strcmp(_simpleCommands[i]->_arguments[0], "cd") == 0) {
			if (_simpleCommands[i]->_arguments[1] && _simpleCommands[i]->_arguments[1][0]) {
				if(chdir(_simpleCommands[i]->_arguments[1]) != 0) {
					perror("cd");
				}
			} else {
				if(chdir(getenv("HOME")) != 0) {
					perror("cd");
				}
			}

		} else {
			// Fork the process and execute.
			int pid = fork();
			if (pid == 0) {
				// Child process.
				//printf("Forking execution: %s", _simpleCommands[i]->_arguments[0]);
				//if (strcmp(_simpleCommands[i]->_arguments[0], "printenv") == 0) {
					//char **environment_value = environ;
					//while (*environment_value != NULL) {
						//printf("%s\n", *environment_value);
						//environment_value++;
					//}
					//exit(0);
				//} else {
					execvp(_simpleCommands[i]->_arguments[0], _simpleCommands[i]->_arguments);
					//fprintf(stderr, "Error while executing binary: \"%s\"\n", _simpleCommands[i]->_arguments[0]);
					perror("execvp");
					exit(1);
				//}
			} else if (pid < 0) {
				// Error while forking.
				perror("fork");
				exit(2);
			} else {
				// Parent process.
				if (! _background) {
					waitpid(pid, NULL, 0);
				}
			}
		}
	}

	// Clean up file descriptors and references.
	if (inFileFd <= -2) {
		dup2(tempStdIn, 0);
		close(tempStdIn);
		tempStdIn = -2;
	}

	if (outFileFd <= -2) {
		dup2(tempStdOut, 1);
		close(outFileFd);
		tempStdOut = -2;
	}

	if (errFileFd <= -2) {
		dup2(tempStdErr, 2);
		close(errFileFd);
		tempStdErr = -2;
	}

	// Clear to prepare for next command
	clear();

	// Print new prompt
	prompt();
}

// Shell implementation

void Command::prompt() {
	if ( isatty(0) ) {
		char* promptStr = getenv("PROMPT");
		printf("%s", promptStr);
		fflush(stdout);
	}
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;
