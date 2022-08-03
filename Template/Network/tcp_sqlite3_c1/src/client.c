#include "client.h"

#define SERVER_PORT 3333
#define SERVER_ADDR "127.0.0.1"
#define BUFSIZE 1024

int server_port = SERVER_PORT;
char server_addr[BUFSIZE] = SERVER_ADDR;

int main(int argc, char **argv)
{
	// addr and port are given
	if (argc == 2) {
		server_port = atoi(argv[2]);

		// use strcpy will cause buffer overflow,
		// because argv[1] is user controlled string
		// don not use strcpy
		strncpy(server_addr, argv[1], BUFSIZE);

		printf("server_port: %d\n", server_port);
		printf("server_addr: %s\n", server_addr);
	}

	// create socket
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	// check socket error
	if (sock_fd == -1) {
		err(EXIT_FAILURE, "socket");
	}

	// addr info
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(struct sockaddr_in));

	// host to network conversion
	sin.sin_port = htons(SERVER_PORT);

	// addr host to network conversion
	if (inet_pton(AF_INET, server_addr, &sin.sin_addr) < 0) {
		err(EXIT_FAILURE, "inet_net_pton");
	}

	// connect to server with addr and port
	if (connect(sock_fd, (const struct sockaddr *)&sin, sizeof(struct sockaddr)) < 0) {
		err(EXIT_FAILURE, "connect");
	}

	while (1) {
		char input[BUFSIZE] = { 0 };
		char data_recv[BUFSIZE] = { 0 };
		printf("Input SQL:");
		// scanf("%s", input);
		fgets(input, BUFSIZE, stdin);

		send(sock_fd, input, strlen(input), 0);
		puts("Command is sent");
		recv(sock_fd, data_recv, BUFSIZE, 0);
		printf("Result:\n %s\n", data_recv);
	}

	return 0;
}
