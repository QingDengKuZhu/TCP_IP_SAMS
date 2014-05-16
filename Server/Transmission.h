#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include "stdio.h"
#include <WinSock2.h>
#define  BUFFER_SIZE		SO_MAX_MSG_SIZE	/*默认缓冲区大小*/
#define  DEF_PORT			10000			/*默认端口*/

#pragma	comment(lib, "ws2_32.lib")

/************************************************************************/
/* 创建一个监听套接字并把本地套接字地址绑定到该监听套接字                   */
/************************************************************************/
SOCKET BindListen(void);

/************************************************************************/
/* 接受客户端的连接请求                                                  */
/************************************************************************/
SOCKET AccepctConnection(SOCKET hListenSocket);

/************************************************************************/
/* 接收客户端操作请求并返回操作结果 (失败返回-1)                           */
/************************************************************************/
int ProcessConnection(SOCKET hClientSocket);

/************************************************************************/
/* 关闭当前客户端连接 (失败返回-1)                                        */
/************************************************************************/
int ShutdownConnection(SOCKET hClientSocket);

/************************************************************************/
/* 服务器主函数                                                          */
/************************************************************************/
void DoWork(void);

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


#endif