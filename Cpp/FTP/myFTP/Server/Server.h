#pragma once

#include <Winsock2.h>
#include <string>

class Server
{
public:
	//Server(SOCKET s);
	Server();
	~Server();

	//��ӭ����
	bool welcome(SOCKET server);
	//��������к���
	int running(SOCKET server);
	//�����������
	int commandParse(char* instruck, std::string &paramter);
	//�ļ����պ���
	bool receiveFile(SOCKET server,std::string filename);
	//�ļ�����
	bool sendFile(SOCKET server,std::string filename);
	//�����ļ�
	bool QueryFile(SOCKET server,std::string filename);
	//��¼
	bool Login(SOCKET server,std::string username);
	//����
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

