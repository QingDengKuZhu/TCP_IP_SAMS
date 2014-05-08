#include "Transmission.h"
#include <stdio.h>

SOCKET BindListen(void)
{
	struct sockaddr_in serv_addr = {0};	/*本地套接字地址(服务器端套接字地址)*/

	SOCKET hListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == hListenSock)
	{
		printf("socket error  : %d\n", WSAGetLastError());
		return INVALID_SOCKET;
	}

	/************************************************************************/
	/* 填充本地套接字地址                                                                     */
	/************************************************************************/
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(DEF_PORT);
	serv_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	if (SOCKET_ERROR == bind(hListenSock, (const struct sockaddr *)&serv_addr,sizeof(struct sockaddr)))
	{
		printf("bind error : %d\n", WSAGetLastError());
		return INVALID_SOCKET;
	}

	/************************************************************************/
	/* 开始监听(将其设置为监听状态)                                                                     */
	/************************************************************************/
	if (SOCKET_ERROR == listen(hListenSock, SOMAXCONN))
	{
		printf("listen error : %d\n", WSAGetLastError());
		closesocket(hListenSock);
		return INVALID_SOCKET;
	}


	return hListenSock;
}

SOCKET AccepctConnection(SOCKET hListenSocket)
{
	struct sockaddr_in client_addr = {0};
	int addr_len = (int)sizeof(struct sockaddr_in);

	SOCKET hClientSocket = accept(hListenSocket, (struct sockaddr *)&client_addr, &addr_len);
	if (INVALID_SOCKET == hClientSocket)
	{
		printf("accept error : %d\n", WSAGetLastError());
		return INVALID_SOCKET;
	}

	return hClientSocket;
}

int ShutdownConnection(SOCKET hClientSocket)
{
	char buff[BUFFER_SIZE];
	int result = 0;

	if (SOCKET_ERROR == shutdown(hClientSocket, SD_SEND))
	{
		printf("shutdown error : %d\n", WSAGetLastError());
		return -1;
	}

	do 
	{
		result = recv(hClientSocket, buff, BUFFER_SIZE, 0);
		if (SOCKET_ERROR == result)
		{
			printf("recv error : %d\n", WSAGetLastError());
			return -1;
		}
		else
		{
			printf("%d unexpected bytes received !\n", result);
		}
	} while (0 != result);

	/************************************************************************/
	/* 关闭套接字                                                                     */
	/************************************************************************/
	if (SOCKET_ERROR == closesocket(hClientSocket))
	{
		printf("closesock error : %d\n", WSAGetLastError());

		return -1;
	}

	return 1;


}

int ProcessConnection(SOCKET hClientSocket)
{
	return 0;
}

void DoWork(void)
{
	SOCKET hListenSocket;
	SOCKET hClientSocket;

	hListenSocket =  BindListen();

	if (INVALID_SOCKET == hListenSocket)
	{
		return;
	}
	printf("Server is Running...\n");

	while (1)
	{
		/************************************************************************/
		/* 第一阶段,接受一个客户端连接                                                                     */
		/************************************************************************/
		hClientSocket = AccepctConnection(hListenSocket);
		if (INVALID_SOCKET == hClientSocket)
		{
			break;
		}

		/************************************************************************/
		/* 第二阶段,服务一个客户端连接                                                                     */
		/************************************************************************/
		if (-1 == ProcessConnection(hClientSocket))
		{
			break;
		}

		/************************************************************************/
		/* 第三阶段, 关闭一个客户端连接                                                                     */
		/************************************************************************/
		if (-1 == ShutdownConnection(hClientSocket))
		{
			break;
		}
	}

	/************************************************************************/
	/* 关闭监听套接字                                                             */
	/************************************************************************/
	if (SOCKET_ERROR ==closesocket(hListenSocket))
	{
		printf("closesocket error : %d\n", WSAGetLastError());
	}

	printf("成功关闭服务器端!\n");

	return;
}