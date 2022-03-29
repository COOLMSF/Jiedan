#include "Client.h"
#include "Tool.h"

#include <iostream>
#include <WS2tcpip.h>
#include <fstream>
#include <direct.h>
#include <fstream>


Client::Client()
{
	storePath = ".\\temp\\";
	maxSize = 1024;
	
}


Client::~Client()
{
	
	//关闭连接并退出
	closesocket(client);
	//关闭 Winsock
	WSACleanup();
}


void Client::running()
{

	memset(buf, 0, sizeof(buf));
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "Failed to load Winsock\n";
		system("pause");
		return;
	}

	char addr[20] = "";
	std::ifstream file("client.ini");
	if (file)
	{
		file.getline(addr, 19);
	}
	file.close();
	


	//创建Socket
	ser.sin_family = AF_INET;
	ser.sin_port = htons(iPort);
	inet_pton(AF_INET, addr, (void*)&ser.sin_addr.s_addr);
	client = socket(AF_INET, SOCK_STREAM, 0);
	if (client == INVALID_SOCKET) {
		std::cout << "socket() Failed\n";
		system("pause");
		return;
	}

	//连接并进行简单的操作
	if (connect(client, (struct sockaddr*)&ser, sizeof(ser)) == INVALID_SOCKET) {
		std::cout << "connect() Failed\n";
		system("pause");
		return;
	}
	else {
		//接收服务端发送的数据
		iLen = recv(client, buf, maxSize, 0);
		if (iLen == 0) {
			system("pause");
			return;
		}
		else if (iLen == SOCKET_ERROR) {
			std::cout << "recv() Failed\n";
			system("pause");
			return;
		}
		std::cout << "Successfully connected to the service!" << buf << std::endl;
	}
	
	while (true) {
		//输入相应的数据发送给服务端
		std::cout << ">>";
		std::cin.getline(buf, 1024);

		std::string paramter;
		int cmd = commandParse(buf, paramter);

		switch (cmd) {
		case 0:
			send(client, buf, 1024, 0);
			Login(paramter);
			break;
		case 10:
			send(client, buf, 1024, 0);
			Pass(paramter);
			break;
		case 1:
			std::cout << "Start download the file from client.\n";
			send(client, buf, 1024, 0);
			downloadFile(paramter);
			break;

		case 2:
			std::cout << "Start upload file to server.\n";
			send(client, buf, 1024, 0);
			uploadFile(paramter);
			break;

		case 3:
			std::cout << "Start query file to server.\n";
			send(client, buf, 1024, 0);
			QueryFile(paramter);
			break;
		case 4:
			std::cout << "Stop server.\n";
			send(client, buf, 1024, 0);
			memset(buf, 0, 1024);
		
			recv(client, buf, maxSize, 0);
			if (!strcmp(buf, "STOP"))
			{
				shutdown(client, SD_BOTH);
			}

			
			break;

		default:
			std::cout << "Command is invalid\n";
	
		}
	}

}


bool Client::uploadFile(std::string filePath)
{

	std::ifstream file(filePath.c_str(), std::ios_base::binary);

	if (!file) {
		std::cout << "file open failed.\n";
		return false;
	}
	else {
		std::cout << "open successful\n";
	}

	//获取文件大小
	long fileBegin = file.tellg();
	file.seekg(0, std::ios_base::end);
	long fileEnd = file.tellg();
	int fileSize = fileEnd - fileBegin;
	std::cout << "File size is " << fileEnd-fileBegin << " bytes" << std::endl;
	//将文件大小发送给服务端
	_itoa_s(fileSize, buf, 10);
	send(client, buf, 1024, 0);

	//读取文件内容
	std::cout << "开始读取文件内容" << std::endl;
	file.seekg(0, std::ios_base::beg);
	int sendCount = 0;
	while(!file.eof()) {
		memset(buf, 0, 1024);
		file.read(buf, 1024);

		int len = send(client, buf, maxSize, 0);
		if (len == SOCKET_ERROR) {
			std::cout << "Sending occur error\n";
		}

		sendCount += 1024;
		std::cout << "Send " << sendCount << "/" << fileSize << " bytes\n";
	}

	//关闭文件
	file.close();
	std::cout << "Readed file succesful\n";

	return false;
}

bool Client::downloadFile(std::string file)
{
	

	std::string filePath = storePath + file;
	std::ofstream storeFile(filePath.c_str(), std::ios_base::binary);
	if (!storeFile) {
		std::cout << "Create file failed\n";
	}

	//先接收文件大小信息
	memset(buf, 0, maxSize);
	recv(client, buf, 1024, 0);
	int fileSize = atoi(buf);
	std::cout << "File's size is:" << fileSize << std::endl;

	int len = 1;
	int recvCount = 0;
	//统计文件传输剩下的大小
	int remain = fileSize;
	while (true) {
		memset(buf, 0, maxSize);
		len = recv(client, buf, 1024, 0);
		storeFile.write(buf, 1024);
		if (len == SOCKET_ERROR) {
			std::cout << "Receive occur error\n";
		}

		//如果剩下的小于等于0，说明文件传输完毕，退出循环
		remain -= 1024;
		if (remain <= 0) {
			//if (strlen(buf) == 0) {
			break;
		}

		recvCount += strlen(buf);
		std::cout << "Receive " << recvCount << " bytes\n";
	}

	//关闭并保存文件
	storeFile.close();
	std::cout << "Write file successful\n";



	return false;
}

bool Client::QueryFile(std::string file)
{
	int len;
	send(client, file.c_str(), 1024, 0);
	memset(buf, 0, maxSize);
	len = recv(client, buf, 1024, 0);
	if (len == SOCKET_ERROR) {
		std::cout << "Receive occur error\n";
	}
	else
	{
		std::cout << buf << std::endl;
	}


	return false;

	
}

bool Client::Login(std::string username)
{
	int len;
	send(client, username.c_str(), 1024, 0);
	memset(buf, 0, maxSize);
	len = recv(client, buf, 1024, 0);
	if (len == SOCKET_ERROR) {
		std::cout << "Receive occur error\n";
		return false;
	}
	else
	{
		std::cout << buf << std::endl;
	}
	return true;

}
bool Client::Pass(std::string password)
{
	int len;
	send(client, password.c_str(), 1024, 0);
	memset(buf, 0, maxSize);
	len = recv(client, buf, 1024, 0);
	if (len == SOCKET_ERROR) {
		std::cout << "Receive occur error\n";
		return false;
	}
	else
	{
		std::cout << buf << std::endl;
	}
	return true;

}

int Client::commandParse(char * instruck, std::string & paramter)
{
	std::string string(buf);
	//std::cout << string;
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
	if (command[0] == "LOG") {
		paramter = command[1];
		return 0;
	}

	if (command[0] == "PUT") {
		paramter = command[1];
		return 2;
	}
	if (command[0] == "GET") {
		paramter = command[1];
		return 1;
	}

	if (command[0] == "QUERY") {
		paramter = command[1];
		return 3;
	}

	if (command[0] == "PASS") {
		paramter = command[1];
		return 10;
	}


	return 0;
}
