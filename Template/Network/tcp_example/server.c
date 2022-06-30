#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <err.h>

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 
	struct sockaddr a;

    char sendBuff[1025];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(3333); 

    if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		err(EXIT_FAILURE, "bind");
	}

    listen(listenfd, 10); 

    while(1)
    {
		char recv_data[1024] = { 0 };
		char send_data[1024] = { 0 };
		pid_t pid;

        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
		
		pid = fork();

		if (pid == 0) {
		recv(connfd, recv_data, 1024, 0);

		// if (strcmp(recv_data, "liu") == 0) {
		// 	strcpy(send_data, "You are connected!\n");
		// } else {
		// 	strcpy(send_data, "Sorry, you are not the user\n");
		// }

			if (strstr(recv_data, "hello") != NULL) {
				strcpy(send_data, "hello");
			} else if (strstr(recv_data, "uid") != NULL) {
				sprintf(send_data, "uid=%d", connfd);
			} else if (strstr(recv_data, "time") != NULL) {
				ticks = time(NULL);
				snprintf(send_data, 1024, "%.24s\r\n", ctime(&ticks));
			} else {
				sprintf(send_data, "消息收到:%s", recv_data);
			}

		send(connfd, send_data, strlen(send_data), 0);
        close(connfd);
		}
    }
}
