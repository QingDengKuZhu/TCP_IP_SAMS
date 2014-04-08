#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <WinSock2.h>
#include <stdio.h>

#define  BUFFER_SIZE		SO_MAX_MSG_SIZE	//��������С
#define  DEF_PORT			10000			//Ĭ�϶˿ں�

//���ӷ�����.
//nServerAddr: �Ϸ��ķ�������ַ(������ַ).
//nPort: �Ϸ��Ķ˿ں�(������ַ).
//���ɹ�,�������Ӿ�� ����,����INVALID_SOCKET.
SOCKET ConnectServer(u_long nServerAddr, int nPort);

//�ر�����.
//sd: �����ӵ��׽��־��.
//���ɹ�,����TRUE;���߷���FALSE.
BOOL ShutdownConnection(SOCKET sd);

//������������.
//sd: �������׽���
//data: ���������ݵĵ�ַ
//len: ���ݴ�С
//���ɹ�����,����TRUE;���߷���FALSE.
BOOL CompleteSend(SOCKET sd, const char *data, int len);

//������������.
//sd : �������׽���
//buffer : �������ݵĻ�������ַ
//len :"���ݴ�С
//���ɹ�����,����true;���߷���FALSE.
BOOL CompleteRecv(SOCKET sd, char *buffer, int len);

#endif