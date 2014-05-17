#include "Transmission.h"
#include <stdlib.h>
#include <stdio.h>
#include <WinSock2.h>

SOCKET ConnectServer(u_long nServerAddr, int nPort)
{

	struct sockaddr_in AddrServer;

	SOCKET sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sd)
	{
		printf("socket error : %d\n", WSAGetLastError());
		return INVALID_SOCKET;
	}

	//填充服务器端套接字地址
	AddrServer.sin_family = AF_INET;
	AddrServer.sin_addr.S_un.S_addr = htonl(nServerAddr);
	AddrServer.sin_port = htons(nPort);

	//连接服务器
	if (SOCKET_ERROR == connect(sd, (const struct sockaddr*)&AddrServer, sizeof(struct sockaddr_in)))
	{
		printf("connect error : %d\n", WSAGetLastError());
		
		return INVALID_SOCKET;
	}

	return sd;
}

int ShutdownConnection(SOCKET sd)
{
	char buffer[SO_MAX_MSG_SIZE];
	int result = 0;
	if(SOCKET_ERROR == shutdown(sd, SD_SEND))
	{
		printf("shutdown error : %d\n", WSAGetLastError());
		return 0;
	}

	do 
	{
		result = recv(sd, buffer, SO_MAX_MSG_SIZE, 0);
		if (SOCKET_ERROR == result)
		{
			printf("recv error : %d\n", WSAGetLastError());
			return 0;
		}
		else if (result > 0)
		{
			printf("%d unexpected bytes received.\n", result);
		}

	} while (result != 0);

	if (SOCKET_ERROR == closesocket(sd))
	{
		printf("closesocket error : %d\n", WSAGetLastError());
		return 0;
	}

	return 1;
}

int CompleteSend(SOCKET sd, const char *data, int len)
{
	int idex = 0;

	while (idex < len)
	{
		int nTemp = send(sd, data+idex, len-idex, 0);
		if (nTemp > 0)
		{
			idex += nTemp;
		}
		else
		{
			printf("send error : %d\n", WSAGetLastError());
			return 0;
		}
	}

	return 1;	//当传入的len为0时,将执行此语句
}

int CompleteRecv(SOCKET sd, char *buffer, int len)
{
	int idex = 0;

	while (idex < len)
	{
		int nTemp = recv(sd, buffer+idex, len-idex, 0);
		if (nTemp == SOCKET_ERROR)
		{
			printf("recv error : %d\n", WSAGetLastError());

			return 0;
		}
		else if (nTemp > 0)
		{
			idex += nTemp;
		}
		else
		{
			printf("Connection closed unexpectedly by peer.\n");

			return 1;
		}
	}
	//当传入的len为0时,将执行此语句

	return 1;
}

void BuffertoData(char *pstudent, const char buffer[], size_t stlen)
{
	size_t i;
	for (i=0; i<stlen; ++i)
	{
		*(pstudent+i) = buffer[i];
	}

	return;
}

void DataToBuffer(char buffer[], const char *pstudent, size_t stlen)
{
	size_t i;
	for (i=0; i<stlen; ++i)
	{
		buffer[i] = *(pstudent+i);
	}

	return;
}