#include "Transmission.h"
#include <stdlib.h>
#include <stdio.h>
#include <WinSock2.h>
#include "Output.h"
#include "Input.h"

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

void ClientFromServer(SOCKET sd)
{
	char buffer[sizeof(STUDENT)];//接受学生成绩信息
	STUDENT student;
	char *studentend = "000000000";
//	int i = 0;
	system("cls");
	PrintHead();
	while (1)
	{
		if(1 != CompleteRecv(sd, buffer, sizeof(STUDENT)))
		{
//			++i;		printf("接收成功!\n");
		}
		BuffertoData((char *)&student, buffer, sizeof(STUDENT)/sizeof(char));//转换
		if (0 == strcmp(student.ID, studentend))
		{
			break;
		}
//		printf("调用PrintfData函数\n");
		PrintData(&student);

	}
//	printf("接收了%d次\n", i);
	getchar();
	return;

}

//添加数据
void Add(SOCKET sd)
{
	STUDENT data;
	char buffer[sizeof(STUDENT)];

	IDInput(data.ID, "ID: ", 10);
	NameInput(data.name, "name: ", 15);
	data.chinese = NumberInput("chinese: ", 100);
	data.math = NumberInput("math: ", 100);
	data.english = NumberInput("english: ", 100);
	data.physics = NumberInput("physics: ", 100);
	data.chemistry = NumberInput("chemistry: ", 100);
	data.biology = NumberInput("biology: ", 100);
	data.total = data.chinese+data.math+data.english+data.physics+data.chemistry+data.biology;

	DataToBuffer(buffer, (const char*)&data, sizeof(STUDENT)/sizeof(char));
	if(0 == CompleteSend(sd, buffer, sizeof(STUDENT)))
	{
		printf("传输失败!\n");
	}
	return;
}

void Del(SOCKET sd)
{
	char ID[10];
	IDInput(ID, "待删除ID:", 10);
	if(0 == CompleteSend(sd, ID, 10))
	{
		printf("传输失败!\n");
	}

	return;
}

void Modify(SOCKET sd)
{
	STUDENT data;
	char buffer[sizeof(STUDENT)];

	IDInput(data.ID, "带修改学生ID: ", 10);
//	NameInput(data.name, "name: ", 15);
	strcpy(data.name, "abc");
	data.chinese = NumberInput("chinese: ", 100);
	data.math = NumberInput("math: ", 100);
	data.english = NumberInput("english: ", 100);
	data.physics = NumberInput("physics: ", 100);
	data.chemistry = NumberInput("chemistry: ", 100);
	data.biology = NumberInput("biology: ", 100);
	data.total = data.chinese+data.math+data.english+data.physics+data.chemistry+data.biology;

	DataToBuffer(buffer, (const char*)&data, sizeof(STUDENT)/sizeof(char));
	if(0 == CompleteSend(sd, buffer, sizeof(STUDENT)))
	{
		printf("传输失败!\n");
	}
	return;

}

void RecTongji(SOCKET sd)
{
	TJMESSAGE tjmessage;
	char buffer[sizeof(TJMESSAGE)];
	CompleteRecv(sd, buffer, sizeof(TJMESSAGE));
	BuffertoData((char *)&tjmessage, buffer, sizeof(TJMESSAGE));
	system("cls");
	gotoxy(10, 8);
	printf("------------------------统计信息-------------------------\n");
	printf("总分最高为%d\n", tjmessage.total);

	printf("语文不及格%d人.\n数学不及格%d人\n外语不及格%d人\n物理不及格%d人\n化学不及格%d人\n生物不及格%d人\n",
		tjmessage.chinese, tjmessage.math, tjmessage.english, tjmessage.physics, tjmessage.chemistry, tjmessage.biology);
	
	printf("语文单科最高ID: %s, 姓名: %s\n", tjmessage.chinese_ID, tjmessage.chinese_name);
	printf("数学单科最高ID: %s, 姓名: %s\n", tjmessage.math_ID, tjmessage.math_name);
	printf("外语单科最高ID: %s, 姓名: %s\n", tjmessage.english_ID, tjmessage.english_name);
	printf("物理单科最高ID: %s, 姓名: %s\n", tjmessage.physics_ID, tjmessage.physics_name);
	printf("化学单科最高ID: %s, 姓名: %s\n", tjmessage.chemistry_ID, tjmessage.chemistry_name);
	printf("生物单科最高ID: %s, 姓名: %s\n", tjmessage.biology_ID, tjmessage.biology_name);	
	printf("总成绩分最高ID: %s, 姓名: %s\n", tjmessage.total_ID, tjmessage.total_name);
	getchar();
	return;
}

void Found(SOCKET sd)
{
	char ID[10];
	IDInput(ID, "查找ID:", 10);
	if(0 == CompleteSend(sd, ID, 10))
	{
		printf("传输失败!\n");
	}

	return;
}