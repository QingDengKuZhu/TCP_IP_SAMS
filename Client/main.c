#include "Data.h"
#include "Input.h"
#include "Output.h"
#include "Transmission.h"
#include "UI.h"
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(void)
{
	//初始化Winsock资源
	WSADATA wsadata;
	u_long nServerAddr = ntohl(inet_addr("127.0.0.1"));//服务器地址
	int nPort = DEF_PORT;	//服务器端口

	if (SOCKET_ERROR == WSAStartup(MAKEWORD(2, 2), &wsadata))
	{
		printf("WSAStartup error : %d\n", WSAGetLastError());
		
		return EXIT_FAILURE;
	}

	while (TRUE)
	{
		//连接服务器
		SOCKET sd = ConnectServer(nServerAddr, nPort);
		if (INVALID_SOCKET == sd)
		{
			printf("尝试连接服务器失败!\n");
			break;
		}

		WelcomeUI(sd);//进入欢迎界面;
		ShutdownConnection(sd);
	}


	if (SOCKET_ERROR == WSACleanup())
	{
		printf("WSAClearnup error: %d\n", WSAGetLastError());
		
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}