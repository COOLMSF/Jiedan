#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

#define PORT 7777
#define BUFSZ 128
#define MAX_CLINET 10

struct _sock_info{
    int used;
    char name[20];
    int sockfd;
    struct sockaddr_in sock_addr;
};

typedef struct _sock_info Info;

int trim(char *s);
int save_file(char *s, int sockfd);

void show_Init(void);
void show_IP(Info user, int option);
void *thread_client(void *ptr);
int choose_user_num(Info *client);
