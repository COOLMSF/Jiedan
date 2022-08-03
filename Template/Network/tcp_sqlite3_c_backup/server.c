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
#include <sqlite3.h>

// config variables for server
int port = 0;
char log_filename[100] =  "server.log";
char full_buffer[10000] = { 0 };

int callback(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
    NotUsed = 0;
    
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

		char tmp[1000]; bzero( tmp, 1000 );
        sprintf(tmp, "%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
		strcat(full_buffer, tmp);
    }
    
    printf("\n");
    strcat(full_buffer, "\n");
    
    return 0;
}
// function to read configuration file
// configuration file shoule be like
// server.conf
// port=8888
int read_config_file(const char *filename)
{
	char buffer[100]; 

	bzero( buffer, 100 );
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

int do_sql(char *sql, int socket_client)
{
    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open("test.db", &db);

	if (strstr(sql, "create")) {
		printf("Note: %s\n", sql);
		sleep(10);
	}
    
    if (rc != SQLITE_OK) {
        
		char tmp[1024]; bzero( tmp, 1024 );
        sprintf(tmp, "Cannot open database: %s\n", sqlite3_errmsg(db));
		strcat(full_buffer, tmp);

        sqlite3_close(db);
        
        return -1;
    }
    
    // char *sql = "DROP TABLE IF EXISTS Cars;" 
    //             "CREATE TABLE Cars(Id INT, Name TEXT, Price INT);" 
    //             "INSERT INTO Cars VALUES(1, 'Audi', 52642);" 
    //             "INSERT INTO Cars VALUES(2, 'Mercedes', 57127);" 
    //             "INSERT INTO Cars VALUES(3, 'Skoda', 9000);" 
    //             "INSERT INTO Cars VALUES(4, 'Volvo', 29000);" 
    //             "INSERT INTO Cars VALUES(5, 'Bentley', 350000);" 
    //             "INSERT INTO Cars VALUES(6, 'Citroen', 21000);" 
    //             "INSERT INTO Cars VALUES(7, 'Hummer', 41400);" 
    //             "INSERT INTO Cars VALUES(8, 'Volkswagen', 21600);";

	printf("Execute sql: %s\n", sql);
	rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        char tmp[256]; bzero( tmp, 256 );
        // sprintf(tmp, "Failed to select data\n");
		// strcat(full_buffer, tmp);
        sprintf(tmp, "SQL error: %s\n", err_msg);
        printf("SQL error: %s\n", err_msg);
		strcat(full_buffer, tmp);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        
        return 1;
    } 
    
    sqlite3_close(db);
}


int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 
	struct sockaddr a;

    char sendBuff[1025];
    time_t ticks; 

	read_config_file("server.conf");
	printf("Port: %d\n", port);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port); 

    if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		err(EXIT_FAILURE, "bind");
	}

    listen(listenfd, 10); 

	// open sqlite3 connection
	sqlite3 *db;
    sqlite3_stmt *res;
	char reply[1024]; bzero( reply, 1024 );


    while(1)
    {
		char recv_data[1024] = { 0 };
		char send_data[1024] = { 0 };
		pid_t pid;

        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
		
		pid = fork();
		printf("New client %d\n", pid);

		if (pid == 0) {
			while (1) {
				while (1) {
					char c;
					// recv 1 byte from socket
					recv(connfd, &c, 1, 0);
				}

				FILE *fp_log = fopen("log.txt", "a");
				fprintf(fp_log, "SQL %s\n", recv_data);
				fclose(fp_log);

				if (strstr(recv_data, "hello") != NULL) {
					strcpy(send_data, "hello");
				} else if (strstr(recv_data, "bye") != NULL) {
					strcpy(send_data, "bye");
				} else if (strstr(recv_data, "uid") != NULL) {
					sprintf(send_data, "uid=%d", connfd);
				} else if (strstr(recv_data, "time") != NULL) {
					ticks = time(NULL);
					snprintf(send_data, 1024, "%.24s\r\n", ctime(&ticks));
				} else {
					// sprintf(send_data, "SQL from client %s", recv_data);
					do_sql(recv_data, connfd);
				}

				printf("Full_buffer %s\n", full_buffer);
				strcat(full_buffer, send_data);
				send(connfd, full_buffer, strlen(full_buffer), 0);
				memset(recv_data, 0, sizeof(recv_data));
				memset(full_buffer, 0, sizeof(full_buffer));
			}
		}
    }
}
