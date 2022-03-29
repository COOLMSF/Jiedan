#include "Server.h"
#include "Tool.h"

#include <iostream>
#include <fstream>
#include <vector>

/*
Server::Server(SOCKET s)
	:server(s)
{
	maxSize = 1024;
	storePath = ".\\temp\\";
	//buf = new char[maxSize];
	userflag = false;
	passflag = false;
}
*/
Server::Server()
{
	maxSize = 1024;
	storePath = ".\\temp\\";
	//buf = new char[maxSize];
	userflag = false;
	passflag = false;
}

Server::~Server()
{
	userflag = false;
	passflag = false;
}

bool Server::welcome(SOCKET server)
{
	char *welcome = "Welcome, Plese login!\n";

	//������Ϣ���ͻ���
	int iSend = send(server, welcome, 1024, 0);
	if (iSend == SOCKET_ERROR) {
		std::cout << "send() Failed\n";
		return false;
	}

	return true;
}

int Server::running(SOCKET server)
{
	
	//while (true) {
		if (recv(server, buf, maxSize, 0) == 0) {
			std::cout << "recv() Faied!\n";
	
		}

		
		std::string paramter;
		int cmd = commandParse(buf, paramter);


		if (cmd == -1)
		{
			return -1;
		}
		switch (cmd) {
		case 0:
			if (!userflag ) {
				Login(server,paramter);
				break;
			}
		case 10:
			if (userflag && !passflag) {
				Pass(server, paramter);
				break;
			}
		case 1:
			if (userflag && passflag) {

				std::cout << "Start receive the file from client.\n";
				receiveFile(server, paramter);
				break;
			}
			else
			{
				memset(buf, 0, 1024);
				strcpy_s(buf, "Login Failed");
				send(server, buf, maxSize, 0);
				break;

			}

		case 2:
			if (userflag && passflag)
			{
				std::cout << "Start send file to client.\n";
				sendFile(server, paramter);
				break;
			}
			else
			{
				memset(buf, 0, 1024);
				strcpy_s(buf, "Login Failed");
				send(server, buf, maxSize, 0);
				break;

			}
		case 3:
			if (userflag && passflag)
			{
				std::cout << "Start Query  file to client.\n";
				QueryFile(server, paramter);
				break;
			}
			else
			{
				memset(buf, 0, 1024);
				strcpy_s(buf, "Login Failed");
				send(server, buf, maxSize, 0);
				break;

			}
		case 4:
			    std::cout << "Stop client.\n";
				
				strcpy_s(buf, "STOP");
				send(server, buf, maxSize, 0);
				shutdown(server, SD_BOTH);
				break;
	
	
		default:
			//std::cout << "Command is invalid\n";

			break;
			
		}
	//}
		return 0;
}

int Server::commandParse(char* instruck, std::string &paramter)
{
	std::string string(buf);
	//std::cout << string << std::endl;
	std::vector<std::string> command;
	Tool::splitString(string, command, std::string(" "));

	if (command.size() != 2) {
		paramter = "";
		if (command[0] == "STOP") {
			paramter = command[0];
			return 4;
		}
		return -1;
	}

	if (command[0] == "PUT") {
		paramter = command[1];
		return 1;
	}
	if (command[0] == "GET") {
		paramter = command[1];
		return 2;
	}
	if (command[0] == "QUERY") {
		paramter = command[1];
		return 3;
	}


	if (command[0] == "LOG") {
		paramter = command[1];
		return 0;
	}
	if (command[0] == "PASS") {
		paramter = command[1];
		return 10;
	}

	return -1;
}

bool Server::receiveFile(SOCKET server,std::string filename)
{
	//�������ϴ��ļ�����ͬ���ļ�
	int i = filename.find_last_of("\\");
	std::string name = filename.substr(i + 1);

	std::string filePath = storePath +  name;
	std::ofstream storeFile(filePath.c_str(), std::ios_base::binary);
	if (!storeFile) {
		std::cout << "Create file failed\n";
	}

	//�Ƚ����ļ���С��Ϣ
	memset(buf, 0, maxSize);
	recv(server, buf, 1024, 0);
	int fileSize = atoi(buf);
	std::cout << "File's size is:" << fileSize << std::endl;

	int len = 1;
	int recvCount = 0;
	//ͳ���ļ�����ʣ�µĴ�С
	int remain = fileSize;
	while (true) {
		memset(buf, 0, maxSize);
		len = recv(server, buf, 1024, 0);
		storeFile.write(buf, 1024);
		if (len == SOCKET_ERROR) {
			std::cout << "Receive occur error\n";
		}

		//���ʣ�µ�С�ڵ���0��˵���ļ�������ϣ��˳�ѭ��
		remain -= 1024;
		if(remain <= 0) {
		//if (strlen(buf) == 0) {
			break;
		}

		recvCount += strlen(buf);
		std::cout << "Receive " << recvCount << " bytes\n";
	}

	//�رղ������ļ�
	storeFile.close();
	std::cout << "Write file successful\n";

	return false;
}


bool Server::QueryFile(SOCKET server,std::string filename)
{

	std::string filePath = storePath + filename;
	std::ifstream storeFile(filePath.c_str(), std::ios_base::binary);
	if (!storeFile) {
		
		memset(buf, 0, 1024);
		strcpy_s(buf, "NO");
		send(server, buf, maxSize, 0);

	} else {
		memset(buf, 0, 1024);
		strcpy_s(buf, "YES");
		send(server, buf, maxSize, 0);


	}
	storeFile.close();
	return false;

}
bool Server::Login(SOCKET server,std::string username)
{
	if (username == "test")
	{
	

			this->userflag = true;
			memset(buf, 0, 1024);
			strcpy_s(buf, "User correct! Enter Password!");
			send(server, buf, maxSize, 0);


	}
	else
	{
		this->userflag = false;
		memset(buf, 0, 1024);
		strcpy_s(buf, "User does not exist! ");
		send(server, buf, maxSize, 0);

	}
	return false;
	
}

bool Server::Pass(SOCKET server,std::string password)
{
	if (password == "test")
	{


		this->passflag = true;
		memset(buf, 0, 1024);
		strcpy_s(buf, "Login Successded!");
		send(server, buf, maxSize, 0);


	}
	else
	{
		this->passflag = false;
		memset(buf, 0, 1024);
		strcpy_s(buf, "Login Failed! ");
		send(server, buf, maxSize, 0);

	}
	return false;

}
bool Server::sendFile(SOCKET server,std::string filename)
{
	std::string filePath = storePath + filename;
	std::ifstream file(filePath.c_str(), std::ios_base::binary);
	if (!file) {
		std::cout << "open failed!\n";


		memset(buf, 0, 1024);
		strcpy_s(buf, "Error!");
		send(server, buf, maxSize, 0);
	
		memset(buf, 0, 1024);
		strcpy_s(buf, "file does not exist!");
		send(server, buf, maxSize, 0);

		file.close();
		return false;
	}
	else {
		std::cout << "open successful\n";
	}
	//��ȡ�ļ���С
	long fileBegin = file.tellg();
	file.seekg(0, std::ios_base::end);
	long fileEnd = file.tellg();
	int fileSize = fileEnd - fileBegin;
	std::cout << "File size is " << fileEnd - fileBegin << " bytes" << std::endl;
	//���ļ���С���͸������
	_itoa_s(fileSize, buf, 10);
	send(server, buf, 1024, 0);

	//��ȡ�ļ�����
	std::cout << "��ʼ��ȡ�ļ�����" << std::endl;
	file.seekg(0, std::ios_base::beg);
	int sendCount = 0;
	while (!file.eof()) {
		memset(buf, 0, 1024);
		file.read(buf, 1024);

		int len = send(server, buf, maxSize, 0);
		if (len == SOCKET_ERROR) {
			std::cout << "Sending occur error\n";
		}

		sendCount += 1024;
		std::cout << "Send " << sendCount << "/" << fileSize << " bytes\n";
	}

	//�ر��ļ�
	file.close();
	std::cout << "Readed file succesful\n";
	return false;
}

bool Server::Start()
{

	//������ص�����
	int iPort = 5050;//������˿�
	WSADATA wsaData;//Winsock ����������
	SOCKET sListen, sAccept;//�׽ӿڹؼ���,�ֱ����ڼ����ͽ�������
	int iLen;
	int iSend;
	char buf[] = "I am a server";
	struct sockaddr_in ser, cli;//�����ַ




	std::cout << "----------------------------\n";
	std::cout << "Server waitting\n";
	std::cout << "----------------------------\n";

	//����winSocket
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Failed to load Winsock.\n";
		return false;
	}

	//����Socket
	sListen = socket(AF_INET, SOCK_STREAM, 0);
	if (sListen == INVALID_SOCKET) {
		std::cout << "socket() Failed:" << WSAGetLastError() << "\n";
		return false;
	}

	//��IP��ַ
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	ser.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sListen, (LPSOCKADDR)&ser, sizeof(ser)) == SOCKET_ERROR) {
		std::cout << "bind() Failed\n";
		return false;
	}

	//����
	if (listen(sListen, 5) == SOCKET_ERROR) {
		std::cout << "listen() Failed\n";
		return false;
		return false;
	}


	//1)��ʼ��һ���׽��ּ���fdSocket�����������׽��ַ���  
	fd_set socketSet;
	FD_ZERO(&socketSet);
	FD_SET(sListen, &socketSet);
	TIMEVAL time = { 1,0 };
	fd_set    readSet;
	FD_ZERO(&readSet);
	fd_set    writeSet;
	FD_ZERO(&readSet);


	while (true)
	{
		
		//2����fdSocket��һ������fdRead����select����  
		readSet = socketSet;
		writeSet = socketSet;

		//ͬʱ����׽��ֵĿɶ���д�ԡ�
		int   nRetAll = select(0, &readSet, &writeSet, NULL, NULL/*&time*/);//�������ó�ʱ��selectΪ����  
		if (nRetAll > 0)   //-1
		{
			//�Ƿ���ڿͻ��˵���������  
			if (FD_ISSET(sListen, &readSet))//��readset�л᷵���Ѿ����ù�listen���׽��֡�  
			{

				if (socketSet.fd_count < FD_SETSIZE)
				{
					sockaddr_in addrRemote;
					int nAddrLen = sizeof(addrRemote);
					server = accept(sListen, (sockaddr*)&addrRemote, &nAddrLen);
					if (server != INVALID_SOCKET)
					{
						FD_SET(server, &socketSet);
						//server = new Server(sClient);
			
						 welcome(server);
						 userflag = false;
						 passflag = false;
						//cout << "\n���յ����ӣ�" << inet_ntoa(addrRemote.sin_addr) << endl;
					}
				}
				else
				{
					std::cout << "���������Ѵ�����!" << std::endl;
					continue;
				}
			}


			for (int i = 0; i < socketSet.fd_count; i++)
			{
				if (FD_ISSET(socketSet.fd_array[i], &readSet))
				{
					running(socketSet.fd_array[i]);
		

				}

				if (FD_ISSET(socketSet.fd_array[i], &writeSet))
				{


				}
			}

		}
		else if (nRetAll == 0)
		{
			std::cout << "time out!\n" << std::endl;
		}
		else
		{
			std::cout << "select error! " << WSAGetLastError() << std::endl;
			Sleep(5000);
			break;
		}

		Sleep(1000);

	}

	closesocket(sListen);
	WSACleanup();


}