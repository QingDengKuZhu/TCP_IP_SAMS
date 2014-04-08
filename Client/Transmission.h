#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <WinSock2.h>
#include <stdio.h>

#define  BUFFER_SIZE		SO_MAX_MSG_SIZE	//缓冲区大小
#define  DEF_PORT			10000			//默认端口号

//连接服务器.
//nServerAddr: 合法的服务器地址(主机地址).
//nPort: 合法的端口号(主机地址).
//若成功,返回连接句柄 否者,返回INVALID_SOCKET.
SOCKET ConnectServer(u_long nServerAddr, int nPort);

//关闭连接.
//sd: 已连接的套接字句柄.
//若成功,返回TRUE;否者返回FALSE.
BOOL ShutdownConnection(SOCKET sd);

//完整发送数据.
//sd: 已连接套接字
//data: 待发送数据的地址
//len: 数据大小
//若成功发送,返回TRUE;否者返回FALSE.
BOOL CompleteSend(SOCKET sd, const char *data, int len);

//完整接收数据.
//sd : 已连接套接字
//buffer : 接收数据的缓冲区地址
//len :"数据大小
//若成功接收,返回true;否者返回FALSE.
BOOL CompleteRecv(SOCKET sd, char *buffer, int len);

#endif