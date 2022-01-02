#include "stdio.h"
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")
#define SERVERIP    "127.0.0.1"
#define SERVERPORT  6666
int main(void)
{
   int ret;
   char sendBuf[512],recvBuf[512];
   WSADATA data;
   SOCKET sockListen,sockTongxun;
   
   ret=WSAStartup(MAKEWORD(2,2),&data);
   if (SOCKET_ERROR==ret)
   {
     printf("WSAStartup 错误");
	 return -1;
   }

   sockListen=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
   if (INVALID_SOCKET==sockListen)
   {
      printf("socket 错误");
	 return -2;
   }

   struct sockaddr_in addrServer;
   int len;
   addrServer.sin_addr.S_un.S_addr=inet_addr(SERVERIP);
   addrServer.sin_family=AF_INET;
   addrServer.sin_port=htons(SERVERPORT);
   len=sizeof(sockaddr);
   ret=bind(sockListen,(sockaddr*)&addrServer,len);
   if (SOCKET_ERROR==ret)
   {
     printf("bind 错误");
	 return -3;
   }

   ret=listen(sockListen,1);
   if (SOCKET_ERROR==ret)
   {
     printf("listen 错误");
	 return -4;
   }

   printf("服务器启动成功，正在监听...\n\n");

  struct sockaddr_in addrClient;
  len=sizeof(sockaddr);
  sockTongxun=accept(sockListen,(sockaddr*)&addrClient,&len);
  if (INVALID_SOCKET==sockTongxun)
   {
      printf("accept 错误");
	 return -5;
   }

  printf("接收一个客户端连接，下面开始通信\n\n");
 
  memset(sendBuf,0,sizeof(sendBuf));

   strcpy(sendBuf,"Welcome to tcpserver");
   ret=send(sockTongxun,sendBuf,strlen(sendBuf)+1,0);
    if (SOCKET_ERROR==ret)
   {
     printf("send 错误");
	 return -6;
   }

	printf("向客户端成功发送以下信息:\n%s\n\n",sendBuf);

   memset(recvBuf,0,sizeof(recvBuf));
   ret=recv(sockTongxun,recvBuf,sizeof(recvBuf),0);
  if (SOCKET_ERROR==ret)
   {
     printf("recv 错误");
	 return -7;
   }

  printf("从客户端收到以下信息:\n%s\n\n",recvBuf);

  closesocket(sockListen);
  closesocket(sockTongxun);
  
  WSACleanup();

  system("pause");

return 0;

}