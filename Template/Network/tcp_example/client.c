#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1) {
		err(EXIT_FAILURE, "socket");
	}

	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(struct sockaddr_in));

	sin.sin_port = htons(3333);

	if (inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr) < 0) {
		err(EXIT_FAILURE, "inet_net_pton");
	}

	if (connect(sock_fd, (const struct sockaddr *)&sin, sizeof(struct sockaddr)) < 0) {
		err(EXIT_FAILURE, "connect");
	}

	char input[1024] = { 0 };
	char data_recv[1024] = { 0 };
	printf("Input your data:");
	scanf("%s", input);

	send(sock_fd, input, strlen(input), 0);
	recv(sock_fd, data_recv, 1024, 0);

	printf("Data from server: %s\n", data_recv);

	return 0;
}
