#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <WinSock2.h>
#include <stdio.h>
#include "Data.h"

#define  BUFFER_SIZE		SO_MAX_MSG_SIZE	//缓冲区大小
#define  DEF_PORT			10000			//默认端口号

//连接服务器.
//nServerAddr: 合法的服务器地址(主机地址).
//nPort: 合法的端口号(主机地址).
//若成功,返回连接句柄 否者,返回INVALID_SOCKET.
SOCKET ConnectServer(u_long nServerAddr, int nPort);

//关闭连接.
//sd: 已连接的套接字句柄.
//若成功,返回1;否者返回0.
int ShutdownConnection(SOCKET sd);

//完整发送数据.
//sd: 已连接套接字
//data: 待发送数据的地址
//len: 数据大小
//若成功发送,返回1;否者返回0.
int CompleteSend(SOCKET sd, const char *data, int len);

//完整接收数据.
//sd : 已连接套接字
//buffer : 接收数据的缓冲区地址
//len :"数据大小
//若成功接收,返回1;否者返回0.
int CompleteRecv(SOCKET sd, char *buffer, int len);

//将接收到的缓冲区中的数据转换成STUDENT格式的数据
void BuffertoData(char *pstudent, const char buffer[], size_t stlen);

//将STUDENT的数据转换以便传输
void DataToBuffer(char buffer[], const char *pstudent, size_t stlen);

//从服务器接收大量STUDENT类型数据并显示出来.
void ClientFromServer(SOCKET sd);

void Add(SOCKET sd);

void Del(SOCKET sd);

void Modify(SOCKET sd);
#endif