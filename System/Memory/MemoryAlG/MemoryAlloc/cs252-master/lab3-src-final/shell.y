
/*
 * CS-252
 * shell.y: parser for shell
 *
 * This parser compiles the following grammar:
 *
 *	cmd [arg]* [> filename]
 *
 * you must extend it to understand the complete shell grammar
 *
 */

%code requires
{
#include <string>

#if __cplusplus > 199711L
#define register      // Deprecated in C++11 so remove the keyword
#endif
}

%union
{
  char        *string_val;
  // Example of using a c++ type in yacc
  std::string *cpp_string;
}

%token <string_val> WORD
%token <string_val> SUBCOMMAND
%token NOTOKEN NEWLINE PIPE GREAT LESS GREATGREAT TWOGREAT GREATAMP GREATGREATAMP AMP

%{
//#define yylex yylex
#include <cstdio>
#include "command.hh"
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <dirent.h>

//#define DEBUG_YAK
#ifdef DEBUG_YAK
#   define DEBUG_PRINT(x) printf x
#else
#   define DEBUG_PRINT(X) do {} while(0)
#endif

/*extern char* lastArg = NULL;*/

void yyerror(const char * s);
int yylex(void);
//void myunputc(int, char* );

int alphaCaseCompare(const dirent** a, const dirent** b) {
  /*int rank = strcasecmp((*a)->d_name, (*b)->d_name);*/
  /*if (rank == 0) {*/
    /*return -1 * strcmp((*a)->d_name, (*b)->d_name);*/
  /*}*/

  /*return rank;*/

  return strcmp((*a)->d_name, (*b)->d_name);
}

#define MAXFILENAME 1024
int expandWildcard(char* prefix, char* suffix) {
  /*fprintf(stderr, "-> %s, %s\n", prefix, suffix);*/
  int sum = 0;

  if (suffix == NULL || suffix[0] == 0) {
    // suffix is empty. Put prefix in argument.
    Command::_currentSimpleCommand->insertArgument(strdup(prefix));
    /*fprintf(stderr, "Insert argument\n");*/
    return 1;
  }

  // Obtain the next component in the suffix
  // Also advance suffix.
  char * s = strchr(suffix, '/');
  char component[MAXFILENAME];
  memset(component, 0, MAXFILENAME * (sizeof component[0]));

  if (s != NULL) {
    // Copy up to the first "/"
    strncpy(component, suffix, s - suffix);
    suffix = s + 1;
  } else {
    // Last part of path. Copy whole thing.
    strcpy(component, suffix);
    suffix = suffix + strlen(suffix);
  }

  // Now we need to expand the component
  char newPrefix[MAXFILENAME];
  memset(newPrefix, 0, MAXFILENAME * (sizeof newPrefix[0]));

  if ( strchr(component, '*') == NULL && strchr(component, '?') == NULL) {
    // component does not have wildcards
    sprintf(newPrefix,"%s/%s", prefix, component);
    return expandWildcard(newPrefix, suffix);
  }

  // Component has wildcards
  // Convert component to regular expression
  /*char * expbuf = compile( [> ... <] )*/
  char* dir = (char *) malloc(sizeof(char) * 1024);
  // If prefix is empty then list current directory
  if ( prefix == NULL || prefix[0] == 0 ) {
    prefix = strdup(".");
  }

  dir = prefix;

  DIR * d = opendir(dir);
  if (d == NULL) {
    return sum;
  }

  struct dirent** namelist;
  int nameCount = scandir(dir, &namelist, NULL, alphasort);
  /*dirent* ent;*/

  // Now we need to check what entries match
  /*while ((ent = readdir(d)) != NULL) {*/
  for(int i = 0; i < nameCount; i++) {
    // Check if name matches
    char* filename = namelist[i]->d_name;
    /*if (advance(ent->d_name, expbuf) ) {*/
    int result = fnmatch(component, filename, FNM_PATHNAME | FNM_PERIOD);
    /*fprintf(stderr, "%s vs %s -> %d\n", component, ent->d_name, result);*/

    if (result == 0) {
      // Entry matches. Add name of entry
      // that matches to the prefix and
      // call expandWildcard(..) recursively
      if (strcmp(prefix, ".") == 0) {
        sprintf(newPrefix,"%s", filename);
      } else if (strcmp(prefix, "/") == 0) {
        sprintf(newPrefix, "%s%s", prefix, filename);
      } else {
        sprintf(newPrefix,"%s/%s", prefix, filename);
      }

      /*fprintf(stderr, "%s\n", newPrefix);*/
      sum += expandWildcard(newPrefix, suffix);
    }
    free(namelist[i]);
    namelist[i] = NULL;
  }

  free(namelist);
  namelist = NULL;

  /*free(newPrefix);*/
  /*newPrefix = NULL;*/
  /*free(component);*/
  /*component = NULL;*/
  /*closedir(d);*/
  return sum;
}

void substringVariable(char* str) {
  char* dollar = strchr(str, '$');
  char* prefix = NULL;
  char* suffix = NULL;

  if (dollar != NULL && dollar[1] == '{') {
    char* varname = dollar + 2;
    while (dollar[0] != '}' && dollar[0] != '\0') {
      dollar++;
    }

    if (dollar[0] == '\0') {
      return;
    }

    dollar[0] = '\0';
    varname = strdup(varname);
    dollar[0] = '}';

    suffix = strdup(dollar + 1);
    dollar = strchr(str, '$');
    dollar[0] = '\0';
    prefix = strdup(str);
    dollar[0] = '$';

    free(str);
    char* value = getenv(varname);
    str = (char *) malloc(sizeof(char) * (strlen(prefix) + strlen(value) + strlen(suffix) + 1));
    strcpy(str, prefix);
    strcat(str, value);
    strcat(str, suffix);

    substringVariable(str);
  }
}

void expandString(char* str) {
  // Check for variables.
  substringVariable(str);

  // Check for wildcards.
  if (strchr(str, '*') != NULL || strchr(str, '?') != NULL) {
    int sum = 0;
    char* prefix = NULL;
    char* suffix = NULL;

      char* split = (char *) strchr(str, '*');
    if (strchr(str, '/') != NULL) {
      if (split == NULL) {
        split = (char *) strchr(str, '?');
      }
      while (split[0] != '/') {
        split--;
      }

      suffix = strdup(++split);
      split--;
      if (split != str) {
        split[0] = '\0';
        prefix = strdup(str);
        split[0] = '/';
      } else {
        char temp = split[1];
        split[1] = '\0';
        prefix = strdup(str);
        split[1] = temp;
      }
    } else {
      suffix = strdup(str);
    }

    /*fprintf(stderr, "%s, %s (%s)\n", prefix, suffix, split);*/

    sum = expandWildcard(prefix, suffix);
    if (sum <= 0) {
      Command::_currentSimpleCommand->insertArgument(str);
    }
  } else {
    Command::_currentSimpleCommand->insertArgument(str);
  }
}

%}

%%

goal:
  commands
  ;

commands:
  command
  | commands command
  ;

command:
  simple_command
  ;

simple_command:
  command_and_args pipe_opt_list iomodifier_opt_list NEWLINE {
    if (! Command::_currentCommand._parseFailure) {
      DEBUG_PRINT(("   Yacc: Execute command\n"));
      /*Command::_currentCommand.print();*/
      Command::_currentCommand.execute();
    }
  }
  | command_and_args pipe_opt_list iomodifier_opt_list AMP NEWLINE {
    if (! Command::_currentCommand._parseFailure) {
      DEBUG_PRINT(("   Yacc: Execute background command\n"));
      Command::_currentCommand._background = 1;
      Command::_currentCommand.execute();
    }
  }
  | NEWLINE {
      Command::_currentCommand.execute();
  }
  | error NEWLINE { yyerrok; }
  ;

command_and_args:
  command_word argument_list {
    Command::_currentCommand.insertSimpleCommand( Command::_currentSimpleCommand );
  }
  ;

argument_list:
  argument_list argument
  | /* can be empty */
  ;

argument:
  WORD {
    char* cleaned = (char *) malloc(sizeof(char) * ( strlen($1)));
    int orgIndex = 0;
    int cleanIndex = 0;

    for ( ; orgIndex < strlen($1) ; ) {
      if ($1[orgIndex] == '\\') {
        orgIndex++;
      }

      cleaned[cleanIndex] = $1[orgIndex];

      if ($1[orgIndex] == '\0') {
        break;
      }

      orgIndex++;
      cleanIndex++;
    }
    cleaned[cleanIndex] = '\0';


    if (cleaned[0] == '~') {
      char* expanded = (char *) malloc(sizeof(char) * (strlen(cleaned) + 64));
      if (cleaned[1] == '/') {
        strcpy(expanded, getenv("HOME"));
        strcat(expanded, cleaned + 1);
      } else if (cleaned[1] == '\0') {
        strcpy(expanded, getenv("HOME"));
      } else {
        char* namestr = NULL;
        char* name = (char *) strchr(cleaned, '/');
        if (name != NULL) {
          while (name[0] != '~') {
            name--;
          }
          name++;
          char* slash = (char *) strchr(cleaned, '/');
          slash[0] = '\0';
          namestr = strdup(cleaned + 1);
          slash[0] = '/';
        } else {
          namestr = strdup(cleaned + 1);
        }

        /*fprintf(stderr, "%s\n", namestr);*/
        strcpy(expanded, "/homes/");
        strcat(expanded, namestr);
        if (name != NULL) {
          strcat(expanded, "/");
          strcat(expanded, cleaned + 1);
        }
      }
      free(cleaned);
      cleaned = expanded;
      /*fprintf(stderr, "expanded: %s\n", cleaned);*/
    }

    DEBUG_PRINT(("   Yacc: insert argument \"%s\"\n", cleaned ));
    expandString(cleaned);
    /*Command::_currentSimpleCommand->insertArgument( cleaned );*/
  }
  ;

command_word:
  WORD {
    DEBUG_PRINT(("   Yacc: insert command \"%s\"\n", $1));
    Command::_currentSimpleCommand = new SimpleCommand();
    /*expandString($1);*/
    Command::_currentSimpleCommand->insertArgument( $1 );
  }
  ;

iomodifier_opt_list:
  iomodifier_opt_list iomodifier_opt
  | /* can be empty */
  ;

iomodifier_opt:
  GREAT WORD {
    if (Command::_currentCommand._outFile && Command::_currentCommand._outFile[0]) {
      yyerror("Ambiguous output redirect\n");
      Command::_currentCommand._parseFailure = 1;
    }
    DEBUG_PRINT(("   Yacc: insert output \"%s\"\n", $2));
    Command::_currentCommand._outFile = $2;
  }
  | LESS WORD {
    if (Command::_currentCommand._inFile && Command::_currentCommand._inFile[0]) {
      yyerror("Ambiguous input redirect\n");
      Command::_currentCommand._parseFailure = 1;
    }
    DEBUG_PRINT(("   Yacc: insert input \"%s\"\n", $2));
    Command::_currentCommand._inFile = $2;
  }
  | TWOGREAT WORD {
    if (Command::_currentCommand._errFile && Command::_currentCommand._errFile[0]) {
      yyerror("Ambiguous error redirect\n");
      Command::_currentCommand._parseFailure = 1;
    }
    DEBUG_PRINT(("   Yacc: insert stderr \"%s\"\n", $2));
    Command::_currentCommand._errFile = $2;
  }
  | GREATAMP WORD {
    if (Command::_currentCommand._errFile && Command::_currentCommand._errFile[0]
        && Command::_currentCommand._outFile && Command::_currentCommand._outFile[0]) {
      yyerror("Ambiguous output and error redirect\n");
      Command::_currentCommand._parseFailure = 1;
    }
    DEBUG_PRINT(("   Yacc: insert output and error \"%s\"\n", $2));
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._errFile = $2;
    Command::_currentCommand._mergeOutErr = 1;
  }
  | GREATGREAT WORD {
    if (Command::_currentCommand._outFile && Command::_currentCommand._outFile[0]) {
      yyerror("Ambiguous append output redirect\n");
      Command::_currentCommand._parseFailure = 1;
    }
    DEBUG_PRINT(("   Yacc: append output \"%s\"\n", $2));
    Command::_currentCommand._appendOut = 1;
    Command::_currentCommand._outFile = $2;
  }
  | GREATGREATAMP WORD {
    if (Command::_currentCommand._errFile && Command::_currentCommand._errFile[0]
        && Command::_currentCommand._outFile && Command::_currentCommand._outFile[0]) {
      yyerror("Ambiguous append output and error redirect\n");
      Command::_currentCommand._parseFailure = 1;
    }
    DEBUG_PRINT(("   Yacc: append output and error \"%s\"\n", $2));
    Command::_currentCommand._appendOut = 1;
    Command::_currentCommand._appendErr = 1;
    Command::_currentCommand._outFile = $2;
    Command::_currentCommand._errFile = $2;
    Command::_currentCommand._mergeOutErr = 1;
  }
  ;

pipe_opt_list:
  pipe_opt_list pipe_opt
  | /* can be empty */
  ;

pipe_opt:
  PIPE command_and_args {
    DEBUG_PRINT(("   Yacc: pipe command\n"));
    /* insert magic */
  }
  ;

%%

void yyerror(const char * s)
{
  fprintf(stderr,"%s", s);
}

#if 0
main()
{
  yyparse();
}
#endif
