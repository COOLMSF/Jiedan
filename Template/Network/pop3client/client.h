#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <b64/cencode.h>
#include <b64/cdecode.h>
#include <regex.h>
#define SIZE 100

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

void go_back(int sockfd);
char *send_command(int sockfd, char *command);
void get_user(int sockfd);
void get_pass(int sockfd);
void get_list(int sockfd);
void get_stat(int sockfd);
char *decode(const char *input);
int reg_matches(const char *str, const char *pattern);
void get_retr(int sockfd);
void save_file(char *str, char *filename);
void download(int sockfd);
void search(int sockfd);
void menu(int sockfd);
void go_back(int sockfd);
