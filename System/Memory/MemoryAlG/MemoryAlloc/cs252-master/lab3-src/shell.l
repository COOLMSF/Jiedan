
/*
 *
 * CS-252 Fall 2017
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

#include <cstring>
#include "y.tab.hh"
#include <sys/wait.h>

static  void yyunput (int c,char *buf_ptr  );

void myunputc(int c) {
  unput(c);
}

int caughtSource = 0;

%}

%%

\n {
  return NEWLINE;
}

[ \t] {
  /* Discard spaces and tabs */
}

"|" {
  return PIPE;
}

">" {
  return GREAT;
}

"<" {
  return LESS;
}

">>" {
  return GREATGREAT;
}

"2>" {
  return TWOGREAT;
}

">&" {
  return GREATAMP;
}

">>&" {
  return GREATGREATAMP;
}

"&" {
  return AMP;
}

\`.*\` {
  //char* substr = (char *) malloc(sizeof(char) * ((size_t) strlen(yytext) - 2));
  char* yyclone = strdup(yytext);
  char substr[1024];
  memcpy(substr, &yyclone[1], strlen(yyclone) - 2);
  substr[strlen(yyclone) - 1] = '\0';
  /*fprintf(stderr, "|%s|", substr);*/
  //yylval.string_val = substr;

  int tempStdIn = dup(0);
  int tempStdOut = dup(1);

  int fdPipeInput[2];
  int fdPipeOutput[2];
  pipe(fdPipeInput);
  pipe(fdPipeOutput);

  //char* line = (char *) malloc(sizeof(char) * ((size_t) strlen(substr) + 6));
  /*char line[1024];*/
  /*strcat(line, substr);*/
  /*strcat(line, "\nexit\n");*/
  /*fprintf(stderr, "|%s|", line);*/
  /*printf("%s", line);*/
  write(fdPipeInput[1], substr, strlen(substr));
  write(fdPipeInput[1], "\nexit\n", strlen("\nexit\n"));
  /*write(fdPipeInput[1], line, strlen(line));*/
  close(fdPipeInput[1]); // Close the write end, we're done with it.

  // Feed input string to subshell.
  dup2(fdPipeInput[0], 0);
  close(fdPipeInput[0]);
  fdPipeInput[0] = -2;

  // Feed output from subshell.
  dup2(fdPipeOutput[1], 1);
  close(fdPipeOutput[1]);
  fdPipeOutput[1] = -2;

  int pid = fork();
  if (pid == 0) {
    char** arguments = NULL;
    /*fprintf(stderr, "executing shell inside fork\n");*/
    execvp("/proc/self/exe", arguments);
    perror("execvp");
    exit(4);
  } else if (pid < 0) {
    perror("subshell fork");
    exit(3);
  } else {
    /*fprintf(stderr, "forked to pid %d\n", pid);*/
    waitpid(pid, NULL, 0);
    /*fprintf(stderr, "fork finished\n");*/
  }

  dup2(tempStdIn, 0);
  close(tempStdIn);
  tempStdIn = -2;

  dup2(tempStdOut, 1);
  close(tempStdOut);
  tempStdOut = -2;
  /*fprintf(stderr, "cleanup complete\n");*/

  char readChar = '*';
  char buffer[1024 * 1024]; // = (char *) malloc(sizeof(char) * 1024);
  int buffUsed = 0;
  int buffSize = 1024;

  while(read(fdPipeOutput[0], &readChar, 1)) {
    if (readChar == '\n') {
      readChar = ' ';
    }
    buffer[buffUsed] = readChar;
    buffUsed++;

    /*if (buffUsed + 2 >= buffSize) {*/
      /*buffer = (char *) realloc(buffer, 2 * buffSize);*/
      /*buffSize = buffSize * 2;*/
    /*}*/
  }
  close(fdPipeOutput[0]);

  buffer[buffUsed] = '\n';
  buffer[buffUsed + 1] = '\0'; // Add the null terminator.
  /*fprintf(stderr, "|%s|", buffer);*/

  // Feed the chars back into the main shell's lexxer (backwards).
  int outLength = strlen(buffer);
  for (int i = outLength; i >= 0; i--) {
    unput(buffer[i]);
  }
  /*fprintf(stderr, "unput complete\n");*/

  /*free(buffer);*/
  /*buffer = NULL;*/
  /*free(line);*/
  /*line = NULL;*/
  /*free(substr);*/
  /*substr = NULL;*/
  //return SUBCOMMAND;
}

\".*\" {
  char* yyclone = strdup(yytext);
  char* substr = (char *) malloc(sizeof(char) * ((size_t) strlen(yyclone) - 2));
  memcpy(substr, &yyclone[1], strlen(yyclone) - 2);
  substr[strlen(yyclone) - 1] = '\0';
  yylval.string_val = substr;
  return WORD;
}

\\[^ \t\n]+ {
  /*char* substr = (char *) malloc(sizeof(char) * ((size_t) strlen(yytext) - 1));*/
  /*memcpy(substr, &yytext[1], strlen(yytext) - 1);*/
  /*yylval.string_val = substr;*/
  yylval.string_val = strdup(yytext);
  return WORD;
}

(\\[^ \t\n]|[^ \t\n\\><&|]+)+ {
  /* Assume that file names have only alpha chars */
  yylval.string_val = strdup(yytext);

  if (strcmp(yytext, "source") == 0 && caughtSource == 0) {
    caughtSource = 1;
  } else if (caughtSource == 1) {
    char* filename = strdup(yytext);

    FILE* file = fopen(filename, "r");

    char readChar = '*';
    char buffer[1024 * 1024]; // = (char *) malloc(sizeof(char) * 1024);
    int buffUsed = 0;
    int buffSize = 1024;

    while(1 == 1) {
      readChar = fgetc(file);
      if (feof(file)) {
        break;
      }
      buffer[buffUsed] = readChar;
      buffUsed++;

      /*if (buffUsed + 2 >= buffSize) {*/
        /*buffer = (char *) realloc(buffer, 2 * buffSize);*/
        /*buffSize = buffSize * 2;*/
      /*}*/
    }

    fclose(file);

    buffer[buffUsed] = '\0';

    // Feed the chars back into the main shell's lexxer (backwards).
    int outLength = strlen(buffer);
    for (int i = outLength; i >= 0; i--) {
      unput(buffer[i]);
    }
    /*fprintf(stderr, "unput complete\n");*/
    caughtSource = 0;
  } else {
    /*fprintf(stderr, "yytext: |%s|\n", yytext);*/
    return WORD;
  }
}
