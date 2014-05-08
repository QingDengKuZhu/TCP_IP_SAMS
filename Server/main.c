#include "Transmission.h"
#include <WinSock2.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

/************************************************************************/
/* 服务器主体函数                                                        */
/************************************************************************/
int main(void)
{
	/*初始化Winsock库*/
	WSADATA wsa_data = {0};
	
	if (SOCKET_ERROR ==WSAStartup(MAKEWORD(2, 2), &wsa_data))
	{
		printf("WSAStartup error : %d \n", WSAGetLastError());
		return EXIT_FAILURE;
	}

	/*调用服务器主体函数*/
	DoWork();

	/*卸载winsock库*/
	WSACleanup();
	return EXIT_SUCCESS;
}