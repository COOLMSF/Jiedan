

#include "book_management.h"

#define PORT 3333
#define MAX_CLIENT 10

int connfd;

int main(int argc, char *argv[])
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Can't allocate sockfd");
        exit(1);
    }

    struct sockaddr_in clientaddr, serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(PORT);

    if (bind(sockfd, (const struct sockaddr *) &serveraddr, sizeof(serveraddr)) == -1) {
        perror("Bind Error");
        exit(1);
    }

    if (listen(sockfd, MAX_CLIENT) == -1) {
        perror("Listen Error");
        exit(1);
    }

	socklen_t addrlen = sizeof(clientaddr);

	while (1) {
		connfd = accept(sockfd, (struct sockaddr*)&clientaddr, &addrlen);
		if (connfd==-1) {
			perror("accept client error");
			close(connfd);
			break;
			// exit(1);
		}

        // fork a new process
        pid_t pid;

        pid = fork();
        // child
        if (pid == 0) {
            dup();
            book_management();
        } else {
            // parent
            wait(NULL);
        }

		close(sockfd);
	}
}
