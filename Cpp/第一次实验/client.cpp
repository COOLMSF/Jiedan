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
   SOCKET sockClient;
   
   ret=WSAStartup(MAKEWORD(2,2),&data);
   if (SOCKET_ERROR==ret)
   {
     printf("WSAStartup 错误");
	 return -1;
   }

   sockClient=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
   if (INVALID_SOCKET==sockClient)
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
  
   printf("客户端初始化完成，正在连接服务器\n\n");
   ret=connect(sockClient,(sockaddr*)&addrServer,len);
   if (SOCKET_ERROR==ret)
   {
     printf("connect 错误");
	 return -3;
   }

   printf("连接服务器成功，下面开始通信...\n\n");

   memset(recvBuf,0,sizeof(recvBuf));
   ret=recv(sockClient,recvBuf,sizeof(recvBuf),0);
   if (SOCKET_ERROR==ret)
   {
     printf("recv 错误");
	 return -4;
   }

   printf("从服务器收到以下信息:\n%s\n\n",recvBuf);
   memset(sendBuf,0,sizeof(sendBuf));
   strcpy(sendBuf,"I am 客户端");
   ret=send(sockClient,sendBuf,strlen(sendBuf)+1,0);
   if (SOCKET_ERROR==ret)
   {
     printf("send 错误");
	 return -5;
   }

   printf("成功向服务器发送以下信息:\n%s\n\n",sendBuf);

   closesocket(sockClient);
   WSACleanup();

   system("pause");
   return 0;
}