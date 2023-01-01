#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>

#define ISspace(x) isspace((int)(x))

#define SERVER_STRING "Hello from server\r\n"

void HandleAcceptRequest(void *);
void HandleBadRequest(int);
void SendData(int, FILE *);
void HandleDonotExe(int);
void ErrMessg(const char *);
void ExeCGI(int, const char *, const char *, const char *);
int  ReadLineSock(int, char *, int);
void headers(int, const char *);
void HandleNotFound(int);
void SaveFile(int, const char *);
int  startup(u_short *);
void unimplemented(int);