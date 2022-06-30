#include "client.h"

// get content of email
int main()
{
  char buf[1024];
  printf("Welecom to pop3 client\n");
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in servaddr;
  if (sockfd < 0)
  {
    printf("socket error\n");
    return 1;
  }
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(110);

  struct hostent *host = gethostbyname("pop.163.com");
  if (host == NULL)
  {
    printf("gethostbyname error\n");
    return 1;
  }
  printf("address: %s\n", inet_ntoa(*(struct in_addr *)host->h_addr));
  servaddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)host->h_addr));
  int i = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  read(sockfd, buf, sizeof(buf));
  memset(buf, 0, sizeof(buf));
  if (i < 0)
  {
    printf("connect error\n");
    return 1;
  }

  printf("Socket Connected\n");

  get_user(sockfd);
  get_pass(sockfd);

  // test_get_user(sockfd);
  // test_get_pass(sockfd);

  clrscr();
  menu(sockfd);
  return 0;
}
