const char * usage =
"                                                               \n"
"myhttpd:							\n"
"                                                               \n"
"Simple server program that hosts web files via HTTP sockets    \n"
"                                                               \n"
"To use it in one window type:                                  \n"
"                                                               \n"
"   myhttpd [-f|-t|-p] [port]                                   \n"
"                                                               \n"
"Where 1024 < port < 65536. If port is not specified, it will   \n"
"default to port 1337						\n"
"                                                               \n"
"The default option is to handle HTTP requests iteratively.	\n"
" -f Handles HTTP requests with processes (safe)		\n"
" -t Handles HTTP requests with threads (fast)			\n"
" -p Handles HTTP requests with a thread pool			\n"
"                                                               \n";

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/file.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <dirent.h>
#include <dlfcn.h>

#define SECRET_KEY "s3$4m3"
#define SERVER "CS 252 Lab 5"
#define HOST "data.cs.purdue.edu"

#define M_ITERATIVE 0
#define M_PROCESS 1
#define M_THREAD 2
#define M_POOL 3

// Used to point to the httprun function in dynamic librarys.
typedef void (*httprunfunc)(int ssock, const char* querystring);

// Used for sorting directory listings.
typedef struct FileEntry {
  char name[128];
  char modDate[32];
  char listing[512];
  int size;
} FileEntry;

// Statistics structure for storing data across threads and processes.
typedef struct Statistics {
  time_t startTime;
  unsigned int requests;
  long double minService;
  long double maxService;
  char minServiceUrl[512];
  char maxServiceUrl[512];
} Statistics;

int QueueLength = 5;
int poolSize = 5;
int port = 1337;
int mode = M_ITERATIVE;
int killServer = 0;
Statistics* stats;

// Processes time request
void* processHTTPRequest( void* socket );
void serveFileAtPath(char* directory, int fd, char* query);
char* getMIMEType(char* filename);
char* getHTTPCode(int code);
char* getCodePage(int code);
void sendError(int fd, int code);
void terminateSocket(int sock);
void* acceptHTTPSockets(void* socket);
extern "C" void slay_process(int);
void printUsage();
void sendDirectoryListing(int fd, DIR* dirPtr, char* directoryStr, char* query);
char* getIconType(char* filename);
void sendRedirect(int fd, int code, char* point);
void serveCGIScript(char* filepath, int fd, char* query);
int dateSort(const void* a, const void* b);
int alphabeticSort(const void* a, const void* b);
int sizeSort(const void* a, const void* b);
void sendStatistics(int fd);

// Displays how to operate the HTTP server.
void printUsage()
{
  fprintf(stderr, "%s", usage);
}

// Acknowledge that zombie processes are now defunct.
extern "C" void slay_process(int)
{
  int status;
  pid_t pid;

  pid = wait3(&status, 0, NULL);

  while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main( int argc, char ** argv )
{
  stats = (Statistics *) mmap(NULL, sizeof(Statistics), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
  time(&(stats->startTime));

  // Cleanup zombie processes.
  struct sigaction zombieslayer;
  zombieslayer.sa_handler = slay_process;
  sigemptyset(&zombieslayer.sa_mask);
  zombieslayer.sa_flags = SA_RESTART;

  if(sigaction(SIGCHLD, &zombieslayer, NULL)){
    perror("sigaction");
    exit(11);
  }

  // Ignore broken pipes.
  // NOTE: also tried
  // signal(SIGPIPE, SIG_IGN);
  struct sigaction bpipe;
  bpipe.sa_handler = SIG_IGN;
  sigemptyset(&bpipe.sa_mask);
  bpipe.sa_flags = SA_RESTART;

  if(sigaction(SIGPIPE, &bpipe, NULL)){
    perror("sigaction");
    exit(12);
  }

  // Parse the arguments.
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0 ) {
      mode = M_PROCESS;
    } else if (strcmp(argv[i], "-t") == 0) {
      mode = M_THREAD;
    } else if (strcmp(argv[i], "-p") == 0) {
      mode = M_POOL;

    } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
      printUsage();
      exit(0);
    } else {
      // Assume port
      port = atoi(argv[i]);
      if (port <= 1024 || port >= 65536) {
	printUsage();
	exit(9);
      }
    }
  }

  // Set the IP address and port for this server.
  struct sockaddr_in serverIPAddress;
  memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
  serverIPAddress.sin_family = AF_INET;
  serverIPAddress.sin_addr.s_addr = INADDR_ANY;
  serverIPAddress.sin_port = htons((u_short) port);

  // Allocate a socket.
  int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
  if ( masterSocket < 0) {
    perror("socket");
    exit(2);
  }

  // Set socket options to reuse port. Otherwise we will
  // have to wait about 2 minutes before reusing the sae port number.
  int optval = 1;
  int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR,
		       (char *) &optval, sizeof( int ) );

  if (err) {
    perror("setsockopt");
    exit (3);
  }

  // Bind the socket to the IP address and port.
  int error = bind( masterSocket,
		    (struct sockaddr *)&serverIPAddress,
		    sizeof(serverIPAddress) );
  if ( error ) {
    perror("bind");
    exit(4);
  }

  // Put socket in listening mode and set the
  // size of the queue of unprocessed connections.
  error = listen( masterSocket, QueueLength);
  if ( error ) {
    perror("listen");
    exit(5);
  }

  if (mode == M_ITERATIVE) {
    printf("Started HTTP server on port %d with iterative mode enabled ...\n", port);
  } else if (mode == M_PROCESS) {
    printf("Started HTTP server on port %d with process mode enabled ...\n", port);
  } else if (mode == M_THREAD) {
    printf("Started HTTP server on port %d with thread mode enabled ...\n", port);
  } else if (mode == M_POOL) {
    printf("Started HTTP server on port %d with thread pool mode enabled ...\n", port);
  }

  // If the proper mode is set, spool up a thread pool.
  if (mode == M_POOL) {
    pthread_t threads[poolSize];
    for (int i = 0; i < poolSize; i++) {
      pthread_create(&threads[i], NULL, acceptHTTPSockets, (void *) &masterSocket);
    }
  }

  // For the main thread, even if there is a thread pool.
  acceptHTTPSockets((void *) &masterSocket);
}

// Loop to continually accept new sockets; used while threading.
void* acceptHTTPSockets(void* sockPtr)
{
  int masterSocket = *((int *) sockPtr);

  while ( 1 ) {
    // Accept incoming connections.
    struct sockaddr_in clientIPAddress;
    int alen = sizeof( clientIPAddress );
    int slaveSocket = accept( masterSocket,
			      (struct sockaddr *)&clientIPAddress,
			      (socklen_t*)&alen);

    if ( slaveSocket < 0 ) {
      perror( "accept" );
      exit(6);
    }

    //printf("Connection from %s\n", inet_ntoa(clientIPAddress.sin_addr));

    // We malloc this so threads don't step on each other's toes.
    int* sock = (int *) malloc(sizeof(int) * 1);
    sock[0] = slaveSocket;

    // Handle the request as specified by the server mode.
    if (mode == M_PROCESS) {
      int pid = fork();
      if (pid == 0) {
	processHTTPRequest( (void *) sock );
	exit(0);
      }
      // Close dangling data after the fork.
      close(slaveSocket);
      free(sock);
      sock = NULL;
    } else if (mode == M_THREAD) {
      pthread_t thread;
      pthread_attr_t attr;
      pthread_attr_init(&attr);
      // Set the thread to detached so it cleans itself up.
      pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
      pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
      pthread_create(&thread, &attr, processHTTPRequest, (void *) sock);
    } else if (mode == M_POOL || mode == M_ITERATIVE) {
      // Thread pools will handle requests in the same manner as an iterative
      // server would.
      processHTTPRequest( (void *) sock );
    }
  }
}

void* processHTTPRequest( void* fdPtr )
{
  // Update some statistics.
  stats->requests += 1;
  clock_t startClock = clock();

  // Pull the socket out from the format specified by the thread.
  int fd = *((int *) fdPtr);

  const int BufferSize = 1024 * 64;
  char buffer[ BufferSize + 1 ];
  int bufferLength = 0;
  int bytesRead = 0;

  // Currently character read.
  unsigned char newChar;

  // Last character read.
  unsigned char lastChar = 0;

  while ( bufferLength < BufferSize &&
	  ( bytesRead = read( fd, &newChar, sizeof(newChar) ) ) > 0 ) {

    if ( lastChar == '\015' && newChar == '\012' ) {
      // Discard previous <CR> from name.
      bufferLength--;
      break;
    }

    buffer[bufferLength] = newChar;
    bufferLength++;

    lastChar = newChar;
  }

  // Make places to store the request in pieces.
  char* method = (char *) malloc(sizeof(char) * 128);
  char* directory = (char *) malloc(sizeof(char) * 1024);
  char* protocol = (char *) malloc(sizeof(char) * 128);
  char* filepath;
  char* query;
  int cgiScriptRunning = 0;

  // Parse the request header sent through the socket.
  sscanf(buffer, "%s %s %s", method, directory, protocol);
  char* orgDir = directory;

  // Check for necessary method, protocol, and legal directory.
  if (strcmp(method, "GET") == 0 && (strcmp(protocol, "HTTP/1.0") == 0 || strcmp(protocol, "HTTP/1.1") == 0)) {
    if (directory[0] == '/') {
      int i = 1;
      while ( !(directory[i] == '/' || directory[i] == '\0') ) {
	i++;
      }

      char* queryStart = strchr(directory, '?');
      if (queryStart != NULL) {
	query = strdup(queryStart + 1);
	*queryStart = '\0'; // Truncate this off so the chars don't bleed into filepath.
      }

      if (directory[i] == '\0') {
	filepath = strdup("/");
      } else {
	filepath = strdup(directory + i);
      }

      directory[i] = '\0';
      directory++;

      if (strcmp(directory, SECRET_KEY) == 0) {
	// Key is correct, proceed.
	directory--;
	directory += i;
	serveFileAtPath(filepath, fd, query);
      } else if (strcmp(directory, "log") == 0) {
	// Point to the access log saved to file.
	char accessStr[32];
	strcpy(accessStr, "access.log");
	serveFileAtPath(accessStr, fd, query);
      } else if (strcmp(directory, "stats") == 0) {
	// Serve up the statistics we've collected.
	sendStatistics(fd);
      } else if (strcmp(directory, "cgi-bin") == 0) {
	// Execute a CGI script.
	char* cgiFilePath = (char *) malloc(sizeof(char) * 128);
	strcpy(cgiFilePath, "http-root-dir/cgi-bin");
	strcat(cgiFilePath, filepath);

	cgiScriptRunning = 1;
	serveCGIScript(cgiFilePath, fd, query);

	free(cgiFilePath);
	cgiFilePath = NULL;
      } else if (strcmp(directory, "favicon.ico") == 0) {
	// We ignore the Favicons because they will quickly shut down the server.
	printf("404 Response for Favicon (ignoring): %s\n", directory);
	sendError(fd, 404);
      } else {
	// Reject invalid keys.
	printf("Invalid secret key: %s\nSending code 403 payload ...\n", directory);
	sendError(fd, 403);
	printf("Shutting down the server for security ...\n");
	terminateSocket(fd);
	exit(7);
      }
    } else {
      // Illegal directory format.
      printf("File Not Found: %s\nSending code 404 payload ...\n", directory);
      sendError(fd, 404);
    }
  }

  // Retrieve an IP address string for statistics...
  struct sockaddr_in addr;
  socklen_t addressSize = sizeof(struct sockaddr_in);
  getpeername(fd, (struct sockaddr *) &addr, &addressSize);
  char ipAddress[24];
  strcpy(ipAddress, inet_ntoa(addr.sin_addr));

  // Cleanup the socket and the request information.
  if (!cgiScriptRunning) {
    terminateSocket(fd);
  }

  // Save timings.
  clock_t endClock = clock();
  long double record = ((long double) (endClock - startClock)) / CLOCKS_PER_SEC;
  if (record < stats->minService || stats->minServiceUrl[0] == '\0') {
    stats->minService = record;
    sprintf(stats->minServiceUrl, "http://%s:%d%s%s", HOST, port, orgDir, filepath);
    printf("New min record: Spent %Lf loading %s\n", stats->minService, stats->minServiceUrl);
  }
  if (record > stats->maxService || stats->maxServiceUrl[0] == '\0') {
    stats->maxService = record;
    sprintf(stats->maxServiceUrl, "http://%s:%d%s%s", HOST, port, orgDir, filepath);
    printf("New max record: Spent %Lf loading %s\n", stats->minService, stats->maxServiceUrl);
  }

  // Log IP address and requested file to access log.
  FILE* logFile = fopen("access.log", "a+");
  flock(fileno(logFile), LOCK_EX);
  fprintf(logFile, "%s %s%s\n", ipAddress, directory, filepath);
  flock(fileno(logFile), LOCK_UN);
  fclose(logFile);

  free(query);
  query = NULL;
  free(filepath);
  filepath = NULL;
  free(fdPtr);
  fdPtr = NULL;
  free(method);
  method = NULL;
  free(orgDir);
  orgDir = NULL;
  directory = NULL;
  free(protocol);
  protocol = NULL;
}

// Formats the header for a valid HTTP/1.0 response.
void sendHeader(int fd, unsigned int code, char* filename)
{
  char protoCode[128];
  const char* server = "Server: CS 252 Lab 5\r\n";
  char content[128];
  char* codeText = getHTTPCode(code);

  sprintf(protoCode, "HTTP/1.0 %d %s\r\n", code, codeText);
  write(fd, protoCode, strlen(protoCode));

  write(fd, server, strlen(server));

  char* mime = getMIMEType(filename);
  sprintf(content, "Content-Type: %s\r\n", mime);

  write(fd, content, strlen(content));
  const char* end = "\r\n";
  write(fd, end, strlen(end));

  free(codeText);
  codeText = NULL;
  free(mime);
  mime = NULL;
}

// Use HTTP to serve up a local file to a remote machine.
void serveFileAtPath(char* directory, int fd, char* query)
{
  char trueDirectory[512];

  // Check for illegal traversal of directories.
  if (strstr(directory, "..") != NULL) {
    printf("Forbidden: %s\nSending code 403 payload ...\n", directory);
    sendError(fd, 403);
    return;
  }

  // Autocomplete to index.html if the root is given, otherwise expand the
  // path to htdocs.
  if (strcmp(directory, "/") == 0) {
    sprintf(trueDirectory, "http-root-dir/htdocs/index.html");
  } else if (strstr(directory, "/icons") != NULL
      || strstr(directory, "/cgi-bin") != NULL
      || strstr(directory, "/cgi-src") != NULL) {
    sprintf(trueDirectory, "http-root-dir%s", directory);
  } else if (strstr(directory, "access.log") != NULL) {
    sprintf(trueDirectory, "access.log");
  } else if (strstr(directory, "http-root-dir/htdocs/") != NULL) {
    sprintf(trueDirectory, "%s", directory);
  } else {
    // Should include a / inside directory.
    sprintf(trueDirectory, "http-root-dir/htdocs%s", directory);
  }

  int requested = open(trueDirectory, O_RDONLY);
  DIR * requestedFolder = opendir(trueDirectory);

  // Test for a folder.
  if (requestedFolder != NULL) {
    if (directory[strlen(directory) - 1] != '/') {
      // Trailing / missing, redirect to the folder, not file.
      char corrected[512];
      sprintf(corrected, "http://%s:%d/%s%s/", HOST, port, SECRET_KEY, directory);
      printf("301 Response for Directory: %s -> %s\n", directory, corrected);
      sendRedirect(fd, 301, corrected);
    } else {
      // Serve up a generated directory listing.
      printf("200 Response for Directory: %s\n", trueDirectory);
      sendDirectoryListing(fd, requestedFolder, trueDirectory, query);
    }

    if (closedir(requestedFolder) < 0) {
      perror("closedir");
      exit(13);
    }

    if (close(requested) < 0) {
      perror("close");
      exit(14);
    }
  } else if (requested >= 0) { // Test that we can open the file.
    // Send the appropriate headers (including MIME type).
    printf("200 Response for: %s\n", trueDirectory);
    sendHeader(fd, 200, trueDirectory);

    // Perform a buffered file read -> socket write.
    char buffer[1024 * 32];
    while ( 1 ) {
      int bytesRead = read(requested, buffer, sizeof(buffer));
      if (bytesRead == 0) {
	break;
      } else if (bytesRead < 0) {
	perror("fread");
	if (mode != M_PROCESS) {
	  return;
	} else {
	  exit(8);
	}
      }

      char* bufferPtr = buffer;
      while(bytesRead > 0) {
	int bytesWritten = write(fd, bufferPtr, bytesRead);
	if (bytesWritten <= 0) {
	  perror("write");
	  if (mode != M_PROCESS) {
	    return;
	  } else {
	    exit(9);
	  }
	}

	bytesRead -= bytesWritten;
	bufferPtr += bytesWritten;
      }
    }

    if (close(requested) < 0) {
      perror("close");
      exit(10);
    }

    // End the transmission.
    write(fd, "\r\n\r\n", strlen("\r\n\r\n"));
  } else {
    printf("File Not Found: %s\nSending code 404 payload ...\n", trueDirectory);
    sendError(fd, 404);
    return;
  }
}

// Execute a script or SO safely within a process.
void serveCGIScript(char* filepath, int fd, char* query)
{
  int fileTest = open(filepath, O_RDONLY);

  if (fileTest > 0) {
    printf("200 Response for CGI Script: %s\n", filepath);

    // Fork off a process for safety.
    int pid = fork();
    if (pid == 0) {
      // Store the query into the environment.
      setenv("REQUEST_METHOD", "GET", 1);
      if (query != NULL && query[0] != '\0') {
	setenv("QUERY_STRING", query, 1);
      }

      // Write the HTTP headers.
      char protoCode[128];
      const char* server = "Server: CS 252 Lab 5\r\n";
      char content[128];
      char* codeText = getHTTPCode(200);

      sprintf(protoCode, "HTTP/1.0 %d %s\r\n", 200, codeText);
      write(fd, protoCode, strlen(protoCode));

      write(fd, server, strlen(server));

      free(codeText);
      codeText = NULL;

      if (strstr(filepath, ".so") == NULL) {
	// Redirect the streams and execute the script.
	dup2(fd, 1);
	dup2(fd, 2);

	char* const* args = NULL;
	execvp(filepath, args);

	perror("execvp");
      } else {
	// Load the dynamic library and execute `httprun`.
	void* lib = dlopen(filepath, RTLD_LAZY);
	if (lib == NULL) {
	  perror("dlopen");
	  exit(1);
	}

	httprunfunc libHttpRun = (httprunfunc) dlsym(lib, "httprun");
	if (libHttpRun == NULL) {
	  perror("dlsym");
	  exit(2);
	}

	libHttpRun(fd, query);

	if (dlclose(lib) != 0) {
	  perror("dlclose");
	  exit(3);
	}
      }
    }
    // Don't close this socket; must persist and be killed after process dies.
    int status = 0;
    waitpid(pid, &status, 0);
    terminateSocket(fd);
  } else {
    printf("CGI Script Not Found: %s\nSending code 404 payload ...\n", filepath);
    sendError(404, fd);
  }

  close(fileTest);
}

// Sends aggregate statistics for the web server.
void sendStatistics(int fd) {
  printf("200 Response for Server Status\n");
  char filename[32];
  strcpy(filename, "statistics.html");

  char protoCode[128];
  const char* server = "Server: CS 252 Lab 5\r\n";
  char content[128];
  char location[256];
  char* codeText = getHTTPCode(200);

  sprintf(protoCode, "HTTP/1.0 %d %s\r\n", 200, codeText);
  write(fd, protoCode, strlen(protoCode));

  write(fd, server, strlen(server));

  char* mime = getMIMEType(filename);
  sprintf(content, "Content-Type: %s\r\n", mime);

  write(fd, content, strlen(content));
  const char* end = "\r\n";
  write(fd, end, strlen(end));

  free(codeText);
  codeText = NULL;
  free(mime);
  mime = NULL;

  char* payload = (char *) malloc(sizeof(char) * 1024);

  char addressStr[128];
  sprintf(addressStr, "%s Server at %s Port %d", SERVER, HOST, port);

  time_t instant;
  time(&instant);
  double diffTime = difftime(instant, stats->startTime);
  sprintf(payload,
      "<html><head> \
      <title>Statistics</title> \
      </head><body> \
      <h1>CS 252 Lab Server Status for %s</h1> \
      <dl> \
      <dt>Author: Max O'Cull</dt> \
      <dt>Uptime: %d seconds</dt> \
      <dt>Requests: %d</dt> \
      <dt>Minimum Service Time: %f seconds</dt> \
      <dt>Maximum Service Time: %f seconds</dt> \
      <dt>Minimum Service URL: %s</dt> \
      <dt>Maximum Service URL: %s</dt> \
      </dl> \
      <hr> \
      <address>%s</address> \
      </body></html>",
      HOST, (int) diffTime, stats->requests, (double) stats->minService, (double) stats->maxService, stats->minServiceUrl, stats->maxServiceUrl, addressStr);

  write(fd, payload, strlen(payload));
  free(payload);
  payload = NULL;

  write(fd, "\r\n\r\n", strlen("\r\n\r\n"));
}

// Convert the file extension into a MIME type.
char* getMIMEType(char* filename)
{
  char* type = NULL;
  char* ext = strchr(filename, '.');

  if (ext == NULL) {
    type = strdup("text/plain");
    return type;
  }

  ext++;

  if (strcmp(ext, "html") == 0) {
    type = strdup("text/html");
  } else if (strcmp(ext, "gif") == 0) {
    type = strdup("image/gif");
  } else if (strcmp(ext, "png") == 0) {
    type = strdup("image/png");
  } else if (strcmp(ext, "svg") == 0) {
    type = strdup("image/svg+xml");
  } else {
    type = strdup("text/plain");
  }

  return type;
}

// Convert the file extension into a representative icon.
char* getIconType(char* filename)
{
  char* type = NULL;
  char* ext = strchr(filename, '.');
  if (ext == NULL) {
    type = strdup("/icons/unknown.gif");
    return type;
  }

  ext++;

  if (strcmp(ext, "html") == 0) {
    type = strdup("/icons/text.gif");
  } else if (strcmp(ext, "gif") == 0) {
    type = strdup("/icons/image.gif");
  } else if (strcmp(ext, "png") == 0) {
    type = strdup("/icons/image.gif");
  } else if (strcmp(ext, "svg") == 0) {
    type = strdup("/icons/image.gif");
  } else {
    type = strdup("/icons/unknown.gif");
  }

  return type;
}

// Convert an HTTP code to a human readable name.
char* getHTTPCode(int code)
{
  switch(code) {
    case 200:
      return strdup("OK");
    case 301:
      return strdup("Moved Permanently");
    case 302:
      return strdup("Found");
    case 400:
      return strdup("Bad Request");
    case 403:
      return strdup("Forbidden");
    case 404:
      return strdup("Not Found");
    case 500:
      return strdup("Internal Server Error");
    case 501:
      return strdup("Not Implemented");
  }
  return strdup("Unknown");
}

// Generate HTML source for an HTTP error code page.
char* getCodePage(int code)
{
  char* page = (char *) malloc(sizeof(char) * 512);
  char addressStr[128];

  sprintf(addressStr, "%s Server at %s Port %d", SERVER, HOST, port);

  char* httpText = getHTTPCode(code);

  sprintf(page,
      "<html><head> \
      <title>%d %s</title> \
      </head><body> \
      <h1>%s</h1> \
      <hr> \
      <address>%s</address> \
      </body></html>", code, httpText, httpText, addressStr);

  free(httpText);
  httpText = NULL;

  return page;
}

// Send an error code page to the client.
void sendError(int fd, int code)
{
  char dir[32];
  sprintf(dir, "error.html");
  sendHeader(fd, code, dir);

  char* payload = getCodePage(code);
  write(fd, payload, strlen(payload));
  free(payload);
  payload = NULL;

  write(fd, "\r\n\r\n", strlen("\r\n\r\n"));
}

// Sends a specially crafted page with HTTP header to redirect the browser
// to another location.
void sendRedirect(int fd, int code, char* point)
{
  char filename[32];
  strcpy(filename, "redirect.html");

  char protoCode[128];
  const char* server = "Server: CS 252 Lab 5\r\n";
  char content[128];
  char location[256];
  char* codeText = getHTTPCode(code);

  sprintf(protoCode, "HTTP/1.0 %d %s\r\n", code, codeText);
  write(fd, protoCode, strlen(protoCode));

  write(fd, server, strlen(server));

  sprintf(location, "Location: %s\r\n", point);
  write(fd, location, strlen(location));

  char* mime = getMIMEType(filename);
  sprintf(content, "Content-Type: %s\r\n", mime);

  write(fd, content, strlen(content));
  const char* end = "\r\n";
  write(fd, end, strlen(end));

  free(codeText);
  codeText = NULL;
  free(mime);
  mime = NULL;

  char* payload = getCodePage(code);
  write(fd, payload, strlen(payload));
  free(payload);
  payload = NULL;

  write(fd, "\r\n\r\n", strlen("\r\n\r\n"));
}

// Constructs an HTML page with links to all resources within a directory.
void sendDirectoryListing(int fd, DIR* dirPtr, char* directory, char* query)
{
  char dir[32];
  sprintf(dir, "directory.html");
  sendHeader(fd, 200, dir);

  char* page = (char *) malloc(sizeof(char) * 1024 * 64);
  char addressStr[128];
  char sortOrder = 'D';

  sprintf(addressStr, "%s Server at %s Port %d", SERVER, HOST, port);

  if (query == NULL || query[0] == '\0' || strstr(query, "O=D") != NULL) {
    sortOrder = 'A';
  }

  sprintf(page,
    "<html><head> \
      <title>Index of %s</title> \
    </head><body> \
    <h1>Index of %s</h1> \
    <table> \
      <tr><th valign=\"top\"><img src=\"/%s/icons/blank.gif\"></th><th><a href=\"?C=N;O=%c\">Name</a></th><th><a href=\"?C=M;O=%c\">Last modified</a></th><th><a href=\"?C=S;O=%c\">Size</a></th><th><a href=\"?C=D;O=A\">Description</a></th></tr> \
      <tr><th colspan=\"5\"><hr></th></tr> \
      <tr><td valign=\"top\"><img src=\"/%s/icons/back.gif\"></td><td><a href=\"../\">Parent Directory</a></td><td>&nbsp;</td><td align=\"right\">  - </td><td>&nbsp;</td></tr>",
    directory, directory, SECRET_KEY, sortOrder, sortOrder, sortOrder, SECRET_KEY);

  struct dirent** fileList;
  int fileCount = scandir(directory, &fileList, NULL, alphasort);
  FileEntry files[128];
  int entryIndex = 0;

  // Store all of the data into structures and sort it later.
  for (int i = 0; i < fileCount; i++) {
    char* filename = fileList[i]->d_name;
    if (filename[0] != '.') { // Ignore hidden files.
      char listing[512];
      char* iconDir = getIconType(filename);
      char fileSize[32];
      char timeStamp[64];
      char optDirSlash[2];

      char filePath[256];
      sprintf(filePath, "%s%s", directory, filename);

      // For retrieving modification times.
      struct stat statBuf;
      stat(filePath, &statBuf);

      // Get file length.
      FILE* file = fopen(filePath, "r");
      if (file <= 0) {
	perror("fopen");
      }
      fseek(file, 0L, SEEK_END);
      long size = ftell(file);
      if (size == -1L) {
	perror("ftell");
      }
      fclose(file);

      // Override based on directory / file.
      if (fileList[i]->d_type == DT_DIR)
      {
	free(iconDir);
	iconDir = strdup("/icons/menu.gif");
	strcpy(fileSize, "-");
	optDirSlash[0] = '/';
	optDirSlash[1] = '\0';

	size = -1;
      } else {
	sprintf(fileSize, "%d", (int) size);
	optDirSlash[0] = '\0';
      }

      strftime(timeStamp, 64, "%F %R", localtime(&(statBuf.st_mtime)));

      sprintf(listing, "<tr><td valign=\"top\"><img src=\"/%s%s\"></td><td><a href=\"%s%s\">%s</a></td><td align=\"right\">%s</td><td align=\"right\">%s</td><td>&nbsp;</td></tr>",
	  SECRET_KEY, iconDir, filename, optDirSlash, filename, timeStamp, fileSize);

      strcpy(files[entryIndex].name, filename);
      strcpy(files[entryIndex].listing, listing);
      strcpy(files[entryIndex].modDate, timeStamp);
      files[entryIndex].size = (int) size;
      entryIndex++;

      free(iconDir);
      iconDir = NULL;
    }

    free(fileList[i]);
    fileList[i] = NULL;
  }

  free(fileList);
  fileList = NULL;

  // Sort type and direction based on query.
  if (query == NULL || query[0] == '\0' || strstr(query, "C=N") != NULL) {
    qsort((void *) files, entryIndex, sizeof(FileEntry), alphabeticSort);
  } else if (strstr(query, "C=M") != NULL) {
    qsort((void *) files, entryIndex, sizeof(FileEntry), dateSort);
  } else if (strstr(query, "C=S") != NULL) {
    qsort((void *) files, entryIndex, sizeof(FileEntry), sizeSort);
  }

  if (query == NULL || query[0] == '\0' || strstr(query, "O=A") != NULL) {
    for (int i = 0; i < entryIndex; i++) {
      strcat(page, files[i].listing);
    }
  } else {
    for (int i = entryIndex; i >= 0; i--) {
      strcat(page, files[i].listing);
    }
  }

  char ending[512];
  sprintf(ending,
    "<tr><th colspan=\"5\"><hr></th></tr> \
    </table> \
    <address>%s</address> \
    </body></html>",
    addressStr
  );

  strcat(page, ending);

  write(fd, page, strlen(page));
  write(fd, "\r\n\r\n", strlen("\r\n\r\n"));
}

// Gracefully end a socket connection.
void terminateSocket(int sock)
{
  // Ask to shutdown...
  shutdown(sock, SHUT_RDWR);

  // Wait until we can't read anything from the socket...
  char buff;
  while (read(sock, (void *) &buff, sizeof(char)) > 0) {
    // Don't busy-wait!
    pthread_yield();
  }

  // Close the socket, the connection has fully ended.
  close(sock);
}

// For directory listings; sorts dates-times.
int dateSort(const void* a, const void* b) {
  FileEntry* fileA = (FileEntry *) a;
  FileEntry* fileB = (FileEntry *) b;

  return strcmp(fileA->modDate, fileB->modDate);
}

// For directory listings; sorts names alphabetically.
int alphabeticSort(const void* a, const void* b) {
  FileEntry* fileA = (FileEntry *) a;
  FileEntry* fileB = (FileEntry *) b;

  return strcmp(fileA->name, fileB->name);
}

// For directory listings; sorts file sizes.
int sizeSort(const void* a, const void* b) {
  FileEntry* fileA = (FileEntry *) a;
  FileEntry* fileB = (FileEntry *) b;

  return (fileA->size) - (fileB->size);
}
