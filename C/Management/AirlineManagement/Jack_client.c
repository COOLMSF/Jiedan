/** 客户端功能： 不断发送数据给服务器 **/

#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *routine(void *arg)
{
	int sockfd = *(int *)arg;
	
	char buf[5000];
	while(1)
	{
		bzero(buf,sizeof(buf));
		recv(sockfd,buf,sizeof(buf),0);
		
		printf("%s",buf);
		
		if(strncmp(buf,"quit",4) == 0)
		{
			close(sockfd);
			exit(0);
		}
	}
}

int main(int argc,char *argv[])  // ./Jack 192.168.21.xx(服务器的地址) 50000
{
	//1. 创建未连接套接字
	int sockfd;
	sockfd = socket(AF_INET,SOCK_STREAM,0); 
	
	//2. 拨号
	struct sockaddr_in srvaddr;
	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr,len);
	
	srvaddr.sin_family = AF_INET;  //协议
	srvaddr.sin_port = htons(atoi(argv[2])); //端口号
	inet_pton(AF_INET,argv[1],&srvaddr.sin_addr); //指定服务器的IP地址
	
	connect(sockfd,(struct sockaddr *)&srvaddr,len);
	
	//2.5 创建一个线程，用于接收数据。
	pthread_t tid;
	pthread_create(&tid,NULL,routine,(void *)&sockfd);
	
	//3. 不断发送数据给服务器
	char buf[50];
	while(1)
	{
		bzero(buf,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		
		send(sockfd,buf,strlen(buf),0);
		
		if(strncmp(buf,"quit",4) == 0)
		{
			break;
		}
	}
	
	//4. 关闭套接字
	close(sockfd);
	
	return 0;
}
















