#include "server.h"

#define BUFSIZE 1024

// config variables for server
int port = 0;
char dataToSend[BUFSIZE] = { 0 };

int fetchData(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
    NotUsed = 0;

	printf("argc: %d\n, argv: %s\n", argc, argv[0]);
    
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

		char tmp[BUFSIZE]; bzero( tmp, BUFSIZE );
        sprintf(tmp, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		strcat(dataToSend, tmp);
    }
    
    printf("\n");
    strcat(dataToSend, "\n");
    
    return 0;
}

int getDataFromConfig(const char *filename) {
	char buffer[BUFSIZE]; 
	bzero( buffer, BUFSIZE );
	
	FILE *fp_config = fopen(filename, "r");
	if (fp_config == NULL)
		err(EXIT_FAILURE, "can not open config file");

	while (fgets(buffer, sizeof(buffer), fp_config) != NULL)
	{
		char *p = buffer;
		int c = 0;
		if (strstr(buffer, "port=") != NULL) {
			for (int i = 0; i < strlen(buffer); i++) {
				if (buffer[i] == '=')
					break;
				c++;
			}
			// get port number
			port = atoi(&buffer[c+1]);
			break;
		}
	}
}

int executeSqlCommand(char *sql, int socket_client) {
    sqlite3 *db;
    char *sqliteErrorMessage = 0;
    
	// open databases
    int sqliteHandler = sqlite3_open("../database/sqlite3.db", &db);
	// check database error
    if (sqliteHandler != SQLITE_OK) {
		char tmp[BUFSIZE] = { 0 };
        sprintf(tmp, "Cannot open database: %s\n", sqlite3_errmsg(db));
		strcat(dataToSend, tmp);
        sqlite3_close(db);
        return -1;
    }

	// execute sqlite command
	sqliteHandler = sqlite3_exec(db, sql, fetchData, 0, &sqliteErrorMessage);
	// check sqlite error
    if (sqliteHandler != SQLITE_OK ) {
        char tmp[BUFSIZE]; bzero( tmp, BUFSIZE );
        printf("Failed to select data\n");
		// strcat(dataToSend, tmp);
        sprintf(tmp, "SQL error: %s\n", sqliteErrorMessage);
        printf("SQL error: %s\n", sqliteErrorMessage);
		strcat(dataToSend, tmp);

        sqlite3_free(sqliteErrorMessage);
        sqlite3_close(db);
        
        return -1;
    } 
    
    sqlite3_close(db);
}

int main(int argc, char *argv[])
{
    struct sockaddr_in servAddr; 
    int listenfd = 0, connfd = 0;

	// init to zero
    char sendBuff[BUFSIZE] = { 0 };
    time_t ticks; 
	
	// Read from configuration file
	getDataFromConfig("../config/server.conf");

	// Create socket 
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
	// We must set them to zero,
	// some system will zero them automatically
	// which may contains random values
    memset(&servAddr, '0', sizeof(servAddr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

	// use ipv4
    servAddr.sin_family = AF_INET;
	// set address, host to network conversion
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// set port, host to network conversion
    servAddr.sin_port = htons(port); 

	// bind socket to address
    if (bind(listenfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		err(EXIT_FAILURE, "bind");
	}

	// set for backlog
    listen(listenfd, 10); 

	// open sqlite3 connection
	sqlite3 *db;
    sqlite3_stmt *res;
	char reply[BUFSIZE]; bzero( reply, BUFSIZE );


    while(1)
    {
		char recvedData[BUFSIZE] = { 0 };
		char sendData[BUFSIZE] = { 0 };
		pid_t pid;

		// wait for clients
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
		
		// create new process for a new client
		pid = fork();

		if (pid == 0) {
			while (1) {
				while (1) {
					char c[2];
					// recv 1 byte from socket
					recv(connfd, &c, 1, 0);
					if (c[0] == '\n') break;
					c[1] = '\0';
					strcat(recvedData, c);
				}
				printf("Recv data: %s\n", recvedData);

				FILE *fp_log = fopen("result.log", "a");
				fprintf(fp_log, "SQL %s\n", recvedData);
				fclose(fp_log);
				executeSqlCommand(recvedData, connfd);
				strcat(dataToSend, sendData);
				printf("Data to send: %s\n", dataToSend);
				if (strlen(dataToSend) < 5) { 
					send(connfd, "Success", strlen("Success"), 0);
				} else {
					send(connfd, dataToSend, strlen(dataToSend), 0);
				}
				memset(sendData, 0, sizeof(sendData));
				memset(recvedData, 0, sizeof(recvedData));
				memset(dataToSend, 0, sizeof(dataToSend));
			}
		}
    }
}
