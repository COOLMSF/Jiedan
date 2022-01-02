
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "CServer_UDP.h"

#include <iostream>

#pragma comment(lib, "ws2_32.lib")


CServer_UDP::CServer_UDP() :m_terminal(false)
{
	//必须进行如下初始化， 否则socket()会返回10093错误
	//初始化WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) //通过一个进程初始化ws2_32.dll
	{
		std::cout << "Initialize WSA failed" << std::endl;
		return;
	}
	//初始化UDDP套接字
	m_sServer = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in m_SocAddrserver;
	m_SocAddrserver.sin_addr.S_un.S_addr = 0;//htonl(INADDR_ANY);
	m_SocAddrserver.sin_family = AF_INET;
	m_SocAddrserver.sin_port = htons(8090);

	int ret = bind(m_sServer, (sockaddr*)&m_SocAddrserver, sizeof(m_SocAddrserver));
	if (ret == -1)
	{
		std::cout << "bind failed!" << std::endl;
		WSACleanup();
	}
	else
	{
		//此处必须赋初值，不然会导致服务器端无法正常发送
		int len_Client = sizeof(sockaddr);
		char recBuf[1025];
		int len = recvfrom(m_sServer, recBuf, 1024, 0, (sockaddr*)&m_SocAddrClient, &len_Client);
		if (len > 0)
		{
			recBuf[len] = '\0';
			std::cout << "Client say:" << recBuf << std::endl;
		}
	}


}
void CServer_UDP::SendMsg(const char sendBuf[])
{
	BYTE m_bySendBuf[1024];
	m_bySendBuf[1] = 0x5B;

	int ret = sendto(m_sServer, sendBuf, strlen(sendBuf), 0, (sockaddr*)&m_SocAddrClient, sizeof(m_SocAddrClient));
	if (ret == -1)
	{
		std::cout << "send failed" << std::endl;
		std::cout << GetLastError() << std::endl;
	}
}
void CServer_UDP::RecMsg()
{
	char recBuf[1025];
	while (!m_terminal)
	{
		int len_Client = sizeof(sockaddr);
		//std::cout << "Begin rec...(server)" << std::endl;
		int len = recvfrom(m_sServer, recBuf, 1024, 0, (sockaddr*)&m_SocAddrClient, &len_Client);
		if (len > 0)
		{
			recBuf[len] = '\0';
			std::cout << "Client say:" << recBuf << std::endl;
		}
	}

}
CServer_UDP::~CServer_UDP()
{
	closesocket(m_sServer);
	WSACleanup();

}