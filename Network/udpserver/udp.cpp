#include <iostream>
#include <thread>
#include <string>

#include "CServer_UDP.h"

using namespace std;

int main()
{
	CServer_UDP server_UDP;

	thread recProc(&CServer_UDP::RecMsg, &server_UDP);

	while (1)
	{
		string content = "";
		cin >> content;
		server_UDP.SendMsg(content.c_str());
	
	}
	return 0;
}