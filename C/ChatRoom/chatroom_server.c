#include "server.h"

Info client[MAX_CLINET];

/* ================================================ */

int main(void)
{
    /* Initialization */

    Info server;
    int i, id;

    bzero(&server, sizeof(server));                     // set host to zero.
    server.sock_addr.sin_family = PF_INET;
    server.sock_addr.sin_port = htons(PORT);            // set socket PORT
    server.sock_addr.sin_addr.s_addr = INADDR_ANY;

    int addrlen = sizeof(struct sockaddr_in);
    pthread_t tid[MAX_CLINET];

    for(i = 0; i < MAX_CLINET; i++){
        client[i].used = 0;
    }

    /* socket() - Create an endpoint for communication. */

    if ((server.sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket() is ERROR");
        exit(0);
    }

    /* bind() - Bind a name to a socket */

    int optval = 1;

    setsockopt(server.sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));    // set address can be reused.
    signal(SIGPIPE,SIG_IGN);            // ignore signal pipe

    if (bind(server.sockfd, (struct sockaddr*)&server.sock_addr, sizeof(server.sock_addr)) == -1){
        perror("bind() is ERROR");
        exit(0);
    }

    /* listen() - Listen for connections on a socket */

    if (listen(server.sockfd, MAX_CLINET) == -1){        // listen to socket with max 10 connections.
        perror("listen() is ERROR");
        exit(0);
    }

    /* Ready for providing service */

    show_Init();               // show welcome message

    while(1){

        /* accept() - Accept a connection on a socket */

        if((id = choose_user_num(client)) == MAX_CLINET){
            printf("\n\nFull Connection...\n\n");
            exit(0);
        }

        //printf("\n\nID = %d\n\n", id);

        if((client[id].sockfd = accept(server.sockfd, (struct sockaddr*)&client[id].sock_addr, &addrlen)) == -1){
            perror("accept() is ERROR");
            exit(0);
        }

        /* Service thread for client (Receive) */

        pthread_create(&tid[id], NULL, thread_client, &client[id]);

        //show_IP(client[id], 1);

        /* Service thread (Send messages to clients) */

    }


    /* Close the server */

    close(server.sockfd);

    return 0;
}

