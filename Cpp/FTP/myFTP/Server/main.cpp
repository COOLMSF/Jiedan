#define   _WINSOCK_DEPRECATED_NO_WARNINGS
#include <Winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>
#include <thread>
#include <vector>
#include <MSWSock.h>  
#include <stdio.h>  
#include <map>  
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Mswsock.lib")  
using namespace std;

#include "Server.h"



void main()
{
	Server* s = new Server();
		s->Start();

}
