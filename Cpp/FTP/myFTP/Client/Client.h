#pragma once
#include <WinSock2.h>
#include <string>

class Client
{
public:
	Client();
	~Client();

	void running();
	bool uploadFile(std::string filePath);
	bool downloadFile(std::string file);
	bool QueryFile(std::string file);
	int commandParse(char* instruck, std::string &paramter);
	bool Client::Login(std::string username);
	bool Pass(std::string password);

private:
	SOCKET client;
	int maxSize;
	char buf[1024];
	//定义相应的数据
	WSADATA wsaData;
	int iPort = 5050;//对应的服务端的端口
	int iLen, iSend;
	struct sockaddr_in ser;
	std::string storePath;


};

