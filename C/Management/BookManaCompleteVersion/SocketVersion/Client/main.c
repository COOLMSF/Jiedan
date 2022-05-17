//本文件是客户机的代码
#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero
#include <arpa/inet.h>
#include <unistd.h>
/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
*/
 
#define SERVER_PORT    3333 
#define MAXBUF 1024
#define FILE_NAME_MAX_SIZE 512
 
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./%s ServerIPAddress\n",argv[0]);
        exit(1);
    }
 
    //设置一个socket地址结构client_addr,代表客户机internet地址, 端口
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr)); //把一段内存区的内容全部设置为0
    client_addr.sin_family = AF_INET;    //internet协议族
    client_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
    client_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口
    //创建用于internet的流协议(TCP)socket,用client_socket代表客户机socket
    int client_socket = socket(AF_INET,SOCK_STREAM,0);
    if( client_socket < 0)
    {
        printf("Create Socket Failed!\n");
        exit(1);
    }
    //把客户机的socket和客户机的socket地址结构联系起来
    if( bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr)))
    {
        printf("Client Bind Port Failed!\n"); 
        exit(1);
    }
 
    //设置一个socket地址结构server_addr,代表服务器的internet地址, 端口
    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    if(inet_aton(argv[1],&server_addr.sin_addr) == 0) //服务器的IP地址来自程序的参数
    {
        printf("Server IP Address Error!\n");
        exit(1);
    }
    server_addr.sin_port = htons(SERVER_PORT);
    socklen_t server_addr_length = sizeof(server_addr);
    //向服务器发起连接,连接成功后client_socket代表了客户机和服务器的一个socket连接
    if(connect(client_socket,(struct sockaddr*)&server_addr, server_addr_length) < 0)
    {
        printf("Can Not Connect To %s!\n",argv[1]);
        exit(1);
    }

    char buf[MAXBUF];
    
    // 清零
    memset(buf, 0, MAXBUF);
    
    // 获取服务器端的pre_welcome输出
    recv(client_socket, buf, MAXBUF, 0);
    // 输出到屏幕
    puts(buf);
    // 输入pre_welcome选项
    scanf("%d", buf);
    // 发送到服务器
    send(client_socket, buf, sizeof(buf), 0);

    // 接收用户名提示信息
    recv(client_socket, buf, MAXBUF, 0);
    // 打印用户提示信息
    puts(buf);
    // 输入用户名
    scanf("%s", buf);
    // 发送到服务器
    send(client_socket, buf, sizeof(buf), 0);

    // 接收密码提示信息
    recv(client_socket, buf, MAXBUF, 0);
    // 打印密码提示信息
    puts(buf);
    // 输入密码
    scanf("%s", buf);
    // 发送到服务器
    send(client_socket, buf, sizeof(buf), 0);

    // ok, 登录成功, or 失败
    



    close(client_socket);
    return 0;
}
