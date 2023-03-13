#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4321

#define BACKLOG 1
#define MAXRECVLEN 1024


int main(int argc, char *argv[])
{
    char buf[MAXRECVLEN];
    int listenfd, connectfd;   /* socket descriptors */
    struct sockaddr_in server; /* server's address information */
    struct sockaddr_in client; /* client's address information */
    socklen_t addrlen;
    /* Create TCP socket */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        /* handle exception */
        perror("socket() error. Failed to initiate a socket");
        exit(1);
    }

    /* set socket option */
    int opt = SO_REUSEADDR;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        /* handle exception */
        perror("Bind() error.");
        exit(1);
    }

    if(listen(listenfd, BACKLOG) == -1)
    {
        perror("listen() error. \n");
        exit(1);
    }

    addrlen = sizeof(client);
    while(1){
        if((connectfd=accept(listenfd,(struct sockaddr *)&client, &addrlen))==-1)
           {
            perror("accept() error. \n");
            exit(1);
           }

		pid_t pid;

		pid = fork();
		if (pid == 0) {
			    // Dup file describer
			    if (dup2(connectfd, STDIN_FILENO) == -1)
					        err(EXIT_FAILURE, "dup2 STDIN_FILENO");
				if (dup2(connectfd, STDERR_FILENO) == -1)
						    err(EXIT_FAILURE, "dup2 STDERR_FILENO");
				if (dup2(connectfd, STDOUT_FILENO) == -1)
							err(EXIT_FAILURE, "dup2 STDOUT_FILENO");
				if (execl("/home/ubuntu/OriginalVersion/test", "test", NULL) == -1)
							err(EXIT_FAILURE, "execl");
				// system("/bin/bash");
		}
    }
    close(listenfd); /* close listenfd */
    return 0;
}

