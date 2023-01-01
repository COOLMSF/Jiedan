#include "func.h"

void HandleAcceptRequest(void *arg)
{
	int	numchars;
	char	ReceievedBuf[1024], HTTPMethod[255], HTTPURL[255], FilePath[512];
	int	client = *(int *)arg;
	size_t 	i, j;
	i = 0; j = 0;
	struct	stat st;
	int	cgi = 0;	
	char	*QueryString = NULL;
	numchars = ReadLineSock(client, ReceievedBuf, sizeof(ReceievedBuf));
	fprintf(stdout,"%s\n",ReceievedBuf);
	while (!ISspace(ReceievedBuf[j]) && (i < sizeof(HTTPMethod) - 1))
	{
		HTTPMethod[i] = ReceievedBuf[j];
		i++; j++;
	}
	HTTPMethod[i] = '\0';
	if (strcasecmp(HTTPMethod, "GET") && strcasecmp(HTTPMethod, "POST"))
	{
		unimplemented(client);
		return;
	}
	if (strcasecmp(HTTPMethod, "POST") == 0)
		cgi = 1;
	/* HTTPURL */
	i = 0;
	while (ISspace(ReceievedBuf[j]) && (j < sizeof(ReceievedBuf)))
		j++;
	while (!ISspace(ReceievedBuf[j]) && (i < sizeof(HTTPURL) - 1) && (j < sizeof(ReceievedBuf)))
	{
		HTTPURL[i] = ReceievedBuf[j];
		i++; j++;
	}
	HTTPURL[i] = '\0';
	/* 'GET' Request with query string */
	if (strcasecmp(HTTPMethod, "GET") == 0)
	{
		QueryString = HTTPURL;
		while ((*QueryString != '?') && (*QueryString != '\0'))
			QueryString++;
		if (*QueryString == '?')
		{
			cgi = 1;
			*QueryString = '\0';
			QueryString++;
		}
	}

	sprintf(FilePath, "www%s", HTTPURL);

	/* HTTPURL is '/' */
	if (FilePath[strlen(FilePath) - 1] == '/')
		strcat(FilePath, "index.html");

	if (stat(FilePath, &st) == -1) {
		while ((numchars > 0) && strcmp("\n", ReceievedBuf))  /* read & discard headers */
			numchars = ReadLineSock(client, ReceievedBuf, sizeof(ReceievedBuf));
		HandleNotFound(client);
	}
	else
	{
		if ((st.st_mode & S_IFMT) == S_IFDIR)
			strcat(FilePath, "/index.html");
		if ((st.st_mode & S_IXUSR)
		 || (st.st_mode & S_IXGRP)
		 || (st.st_mode & S_IXOTH))
			cgi = 1;
		if (!cgi)
			SaveFile(client, FilePath);
		else
			ExeCGI(client, FilePath, HTTPMethod, QueryString);
	}

	close(client);
}

void HandleBadRequest(int client)
{
	char ReceievedBuf[1024];

	sprintf(ReceievedBuf, "HTTP/1.0 400 BAD REQUEST\r\n");
	send(client, ReceievedBuf, sizeof(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "Content-type: text/html\r\n");
	send(client, ReceievedBuf, sizeof(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "\r\n");
	send(client, ReceievedBuf, sizeof(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "<P>Your browser sent a bad request, ");
	send(client, ReceievedBuf, sizeof(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "such as a POST without a Content-Length.\r\n");
	send(client, ReceievedBuf, sizeof(ReceievedBuf), 0);
}

void SendData(int client, FILE *resource)
{
	char ReceievedBuf[1024];

	fgets(ReceievedBuf, sizeof(ReceievedBuf), resource);
	while (!feof(resource))
	{
		send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
		fgets(ReceievedBuf, sizeof(ReceievedBuf), resource);
	}
}

void HandleDonotExe(int client)
{
	char ReceievedBuf[1024];

	sprintf(ReceievedBuf, "HTTP/1.0 500 Internal Server Error\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "Content-type: text/html\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "<P>Error prohibited CGI execution.\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
}

void ErrMessg(const char *sc)
{
	perror(sc);
	exit(1);
}

void ExeCGI(int client, const char *FilePath,
		const char *HTTPMethod, const char *QueryString)
{
	char	ReceievedBuf[1024];
	int	cgi_output[2];
	int	cgi_input[2];
	pid_t	pid;
	int	status;
	int	i;
	char	c;
	int	numchars = 1;
	int	content_length = -1;

	ReceievedBuf[0] = 'A'; ReceievedBuf[1] = '\0';
	if (strcasecmp(HTTPMethod, "GET") == 0)
	{
		while ((numchars > 0) && strcmp("\n", ReceievedBuf))  /* read & discard headers */
			numchars = ReadLineSock(client, ReceievedBuf, sizeof(ReceievedBuf));
	}
	else    /* POST */
	{
		numchars = ReadLineSock(client, ReceievedBuf, sizeof(ReceievedBuf));
		while ((numchars > 0) && strcmp("\n", ReceievedBuf))
		{
			ReceievedBuf[15] = '\0';
			if (strcasecmp(ReceievedBuf, "Content-Length:") == 0)
				content_length = atoi(&(ReceievedBuf[16]));
			numchars = ReadLineSock(client, ReceievedBuf, sizeof(ReceievedBuf));
		}
		if (content_length == -1) {
			HandleBadRequest(client);
			return;
		}
	}

	sprintf(ReceievedBuf, "HTTP/1.0 200 OK\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);

	if (pipe(cgi_output) < 0) {
		HandleDonotExe(client);
		return;
	}
	if (pipe(cgi_input) < 0) {
		HandleDonotExe(client);
		return;
	}

	if ( (pid = fork()) < 0 ) {
		HandleDonotExe(client);
		return;
	}
	if (pid == 0)
	{/* child: CGI script */
		char	meth_env[255];
		char	query_env[255];
		char	length_env[255];

		dup2(cgi_output[1], 1);
		dup2(cgi_input[0], 0);
		close(cgi_output[0]);
		close(cgi_input[1]);
		sprintf(meth_env, "REQUEST_METHOD=%s", HTTPMethod);
		putenv(meth_env);
		if (strcasecmp(HTTPMethod, "GET") == 0) {
			sprintf(query_env, "QUERY_STRING=%s", QueryString);
			putenv(query_env);
		}
		else {   /* POST */
			sprintf(length_env, "CONTENT_LENGTH=%d", content_length);
			putenv(length_env);
		}
		execl(FilePath, FilePath, NULL);
		exit(0);
	}
	else
	{/* parent */
		close(cgi_output[1]);
		close(cgi_input[0]);
		if (strcasecmp(HTTPMethod, "POST") == 0)
			for (i = 0; i < content_length; i++) {
				recv(client, &c, 1, 0);
				write(cgi_input[1], &c, 1);
			}
		while (read(cgi_output[0], &c, 1) > 0)
			send(client, &c, 1, 0);

		close(cgi_output[0]);
		close(cgi_input[1]);
		waitpid(pid, &status, 0);
	}
}

int ReadLineSock(int sock, char *ReceievedBuf, int size)
{
	int i = 0;
	char c = '\0';
	int n;

	while ((i < size - 1) && (c != '\n'))
	{
		n = recv(sock, &c, 1, 0);
		if (n > 0)
		{
			if (c == '\r')
			{
				n = recv(sock, &c, 1, MSG_PEEK);
				if ((n > 0) && (c == '\n'))
					recv(sock, &c, 1, 0);
				else
					c = '\n';
			}
			ReceievedBuf[i] = c;
			i++;
		}
		else
			c = '\n';
	}
	ReceievedBuf[i] = '\0';

	return(i);
}

void headers(int client, const char *filename)
{
	char ReceievedBuf[1024];
	(void)filename;  /* could use filename to determine file type */

	strcpy(ReceievedBuf, "HTTP/1.0 200 OK\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	strcpy(ReceievedBuf, SERVER_STRING);
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "Content-Type: text/html\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	strcpy(ReceievedBuf, "\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
}

void HandleNotFound(int client)
{
	char ReceievedBuf[1024];

	sprintf(ReceievedBuf, "HTTP/1.0 404 NOT FOUND\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, SERVER_STRING);
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "Content-Type: text/html\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "<HTML><TITLE>Not Found</TITLE>\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "<BODY><P>The server could not fulfill\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "your request because the resource specified\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "is unavailable or nonexistent.\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "</BODY></HTML>\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
}

void SaveFile(int client, const char *filename)
{
	FILE	*resource = NULL;
	int	numchars = 1;
	char	ReceievedBuf[1024];


	ReceievedBuf[0] = 'A'; ReceievedBuf[1] = '\0';
	while ((numchars > 0) && strcmp("\n", ReceievedBuf))  /* read & discard headers */
		numchars = ReadLineSock(client, ReceievedBuf, sizeof(ReceievedBuf));

	resource = fopen(filename, "r");
	if (resource == NULL)
		HandleNotFound(client);
	else
	{
		headers(client, filename);
		SendData(client, resource);
	}
	fclose(resource);
}

int startup(u_short *port)
{
	int httpd = 0;
	struct sockaddr_in name;

	httpd = socket(PF_INET, SOCK_STREAM, 0);
	if (httpd == -1)
	  {
		ErrMessg("socket");
	  }

	memset(&name, 0, sizeof(name));
	name.sin_family = AF_INET;
	name.sin_port = htons(*port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0)
	  {
		ErrMessg("bind");
	  }

	if (*port == 0)  /* if dynamically allocating a port */
	  {
		socklen_t namelen = sizeof(name);
		if (getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1)
			ErrMessg("getsockname");
		*port = ntohs(name.sin_port);
	  }

	if (listen(httpd, 5) < 0)
	  {
		ErrMessg("listen");
	  }

	return(httpd);
}

void unimplemented(int client)
{
	char ReceievedBuf[1024];

	sprintf(ReceievedBuf, "HTTP/1.0 501 Method Not Implemented\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, SERVER_STRING);
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "Content-Type: text/html\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "</TITLE></HEAD>\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "<BODY><P>HTTP request HTTPMethod not supported.\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
	sprintf(ReceievedBuf, "</BODY></HTML>\r\n");
	send(client, ReceievedBuf, strlen(ReceievedBuf), 0);
}