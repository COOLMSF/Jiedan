
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <err.h>

#include "readFile.h"

#define	SA      struct sockaddr

#define	MAXLINE	8192	/* max text line length */
// #define	MAXLINE	100000	/* max text line length */

#define SMTP    587
#define POP3    110

#define HELP  "\nYou Can:\n\n\t [ 0 ] Read NEW mail                    \
               \n\t [ 1 ] Read OLD mail.\n\t [ 2 ] Send mail.          \
               \n\t [ 3 ] Delete NEW mail.\n\t [ 4 ] Delete OLD mail.  \
               \n\t [ 5 ] Get mail size.\n\t [ 6 ] Search Topic.  \
               \n\t [ 7 ] Search Text.\n\t \
               \n\t [ 88 ] Exit.\n\nYour option: "

// #define HELP  "\nYou Can:\n\n\t [ 0 ] Read NEW mail                    \
               \n\t [ 1 ] Read OLD mail.\n\t [ 2 ] Send mail.          \
               \n\t [ 3 ] Delete NEW mail.\n\t [ 4 ] Delete OLD mail.  \
               \n\t [ 0 ] Exit.\n\nYour option: "

void getMailSize()
{
	DIR *p = opendir("../MAILS/");
	
	if (!p) {
		err(EXIT_FAILURE, "opendir");
	}

	size_t cnt = 1;
	size_t total_size = 0;
	struct dirent *dp;
	while ((dp = readdir(p)) != NULL) {
		if (strstr(dp->d_name, "NMAILS")) {
			continue;
		} else {
			char *prefix = "../MAILS/";
			char filename[1024] = { 0 };
			struct stat file_info;
			
			strcat(filename, prefix);
			strcat(filename, dp->d_name);

			if (stat(filename, &file_info) < 0) {
				err(EXIT_FAILURE, "stat");
			}

			printf("File Info:\n");
			printf("num:%d\tsize:%d\n", cnt, file_info.st_size);
			cnt++;
			total_size += file_info.st_size;
		}
	}
}

int searchTextInFile(char *str, char *file_name)
{
	FILE *fp = NULL;
	char buf[1024] = { 0 };

	fp = fopen(file_name, "r");
	if (fp == NULL) {
		err(EXIT_FAILURE, "fopen");
	}

	while (fread(buf, 1024, 1, fp) > 0) {
		if (strstr(buf, str)) {
			return 1;
		}
	}

	return 0;
}

void searchTextInDir()
{
	char *prefix = "../MAILS/";
	DIR *dp = opendir(prefix);
	struct dirent *dir_info = NULL;
	char full_name[1024] = { 0 };
	char input[1024] = { 0 };

	printf("Input text that you search:");
	scanf("%s", input);


	if (dp == NULL) {
		err(EXIT_FAILURE, "opendir");
	}

	while ((dir_info = readdir(dp)) != NULL) {
		strcat(full_name, prefix);
		strcat(full_name, dir_info->d_name);

		if (searchTextInFile(input, full_name) > 0) {
			printf("Text found at %s\n", full_name);
		}
		memset(full_name, 0, sizeof(full_name));
	}
}

void searchTopic()
{
	char *prefix = "../MAILS/";
	DIR *dp = opendir(prefix);
	struct dirent *dir_info = NULL;
	char full_name[1024] = { 0 };
	char input[1024] = { 0 };
	char temp[1024] = { 0 };

	printf("Input topic that you search:");
	scanf("%s", input);

	strcat(temp, "Subject: ");
	strcat(temp, input);


	if (dp == NULL) {
		err(EXIT_FAILURE, "opendir");
	}

	while ((dir_info = readdir(dp)) != NULL) {
		if (strcmp(".", dir_info->d_name) == 0 || strcmp("..", dir_info->d_name) == 0) {
			continue;
		}

		strcat(full_name, prefix);
		strcat(full_name, dir_info->d_name);
		// printf("%s\n", full_name);

		if (searchTextInFile(temp, full_name) > 0) {
			printf("Text found at %s\n", full_name);
		}
		// memset(temp, 0, sizeof(temp));
		memset(full_name, 0, sizeof(full_name));
	}
}

int main()
{

  
    printf( "Welcome to the experimental pop3 client\n\n" );

    // read IP addresses
    char * inServer  = ( char * ) malloc( sizeof ( char ) * 12 );
    char * outServer = ( char * ) malloc( sizeof ( char ) * 12 );
    // readConfFile( "../client.txt", inServer, outServer );

    int	sockfd = checkConn( inServer, POP3 );
    if( sockfd == -1 ) return 0;

    // log in
    char User[ 50 ], Pass[ 50 ];
    do
    {
        bzero( User, 50 );
        printf( "Your user: " );
        scanf("%s", User );

        bzero( Pass, 50 );
        printf( "Your pass: " );
        scanf("%s", Pass );
    }
    while ( ! checkUser( User, Pass, sockfd ) );

    // show headers
    getRemoteHeaders( sockfd, NULL, NULL, NULL );

    // options

    int option = 0;

    while ( 1 )
    {
        printf( HELP );
        scanf( "%d", &option );

        switch( option )
        {
            case 0:  readNewMail( sockfd );       break;
            case 1:  readOldMail();               break;
            case 2:  sendMail( outServer, SMTP, User, Pass ); break;
            case 3:  delFromServer( sockfd );     break;
            case 4:  delFromLocal( sockfd );      break;
			case 5:  getMailSize(); break;
	    	case 6:  searchTopic(); break;
	    	case 7:  searchTextInDir(); break;
            case 88:  send( sockfd, "QUIT\x0d\x0a", strlen( "QUIT\x0d\x0a" ), 0 ); return 0;
            default: printf( "\nIt's been an error with your selection:" );
        }
    }

    return 0;
}
