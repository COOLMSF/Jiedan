#pragma once

#include <Winsock2.h>
#include <string>

class Server
{
public:
	//Server(SOCKET s);
	Server();
	~Server();

	//欢迎函数
	bool welcome(SOCKET server);
	//服务端运行函数
	int running(SOCKET server);
	//命令解析函数
	int commandParse(char* instruck, std::string &paramter);
	//文件接收函数
	bool receiveFile(SOCKET server,std::string filename);
	//文件发送
	bool sendFile(SOCKET server,std::string filename);
	//请求文件
	bool QueryFile(SOCKET server,std::string filename);
	//登录
	bool Login(SOCKET server,std::string username);
	//密码
	bool Pass(SOCKET server,std::string password);
	bool Start();

private:
	SOCKET server;
	int maxSize;
	char buf[1024];
	std::string storePath;
	bool userflag;
	bool passflag;

};

