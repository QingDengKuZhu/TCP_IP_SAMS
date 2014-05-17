#include "Data.h"
#include "Function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include "Transmission.h"
#include "test.h"

#pragma	comment(lib, "ws2_32.lib")

int IsAccount(const char account[], const char password[])
{
	LINK *pL = NULL;		/*单链表头指针*/	
	FILE *pf = NULL;		/*文件指针*/
	int count = 0;			/*保存文件中的密码条数*/
	NODE *p	= NULL;			/*结点指针*/
	NODE *r = NULL;			/*指向尾结点,若链表为空,则等于头指针*/
	int n;
	
	/*
	**初始化单链表,生成头结点.
	*/
	pL = (NODE *)malloc(sizeof(NODE));
	if (!pL)
	{
		printf("头结点分配失败!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pL->pnext = NULL;
		r = pL;
	}

	/*
	**以追加的方式打开一个二进制文件
	**可读可写,若文件不存在,则创建文
	**件.
	*/
	pf = fopen(PASSWORDPATH, "r");
	if (!pf)
	{
		printf("文件打开错误");
		exit(EXIT_FAILURE);
	}
	

	/*
	**读入数据
	*/
	while (0 == feof(pf))	/*若文件未读到尾部*/
	{
		p = (NODE *)malloc(sizeof(NODE));
		if (!p)
		{
			printf("待复制数据结点生成失败!\n");
			exit(EXIT_FAILURE);
		}
		
		/*
		**一次从文件中读取一条学生记录
		*/
		if ( 1 == fread(p, sizeof(NODE), 1, pf) )
		{
			p->pnext = NULL;
			r->pnext = p;
			r = p;
			++count;	/*文件记录加一*/
		}

	}

	fclose(pf);/*关闭文件*/

	printf("文件成功打开,当前记录共%d条\n", count);
	//getchar();		/*避免上述信息一闪而过*/
	Show(pL);

	//比较帐号密码
	p = pL->pnext;
	if (!p)
	{
		printf("没有数据!\n");
		DestroyList(&pL);
		return 4;
	}

	while(p)
	{
		if (0 == strcmp(p->data.account, account))
		{
			printf("帐号存在!\n");
			if (0 == strcmp(p->data.password, password))
			{
				printf("密码正确!\n");
				n = p->data.Type;
				DestroyList(&pL);
				return n;
			}
			else
			{
				printf("密码错误!\n");
				DestroyList(&pL);
				return 3;
			}
		}

		p = p->pnext;
	}

	printf("不存在帐号!\n");
	DestroyList(&pL);
	return 4;
}

void Student(SOCKET hClientSocket,const char account[])
{
	LINK_S *pL = NULL;		/*单链表头指针*/	
	FILE *pf = NULL;			/*文件指针*/
	int count = 0;			/*保存文件中的学生条数*/
	NODE_S *p = NULL;			/*结点指针*/
	NODE_S *r = NULL;			/*指向尾结点,若链表为空,则等于头指针*/
	char buffer[sizeof(STUDENT)];//存储待发送学生数据.
	/*
	**初始化单链表,生成头结点.
	*/
	pL = (NODE_S *)malloc(sizeof(NODE_S));
	if (!pL)
	{
		printf("头结点分配失败!\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pL->pnext = NULL;
		r = pL;
	}

	/*
	**以追加的方式打开一个二进制文件
	**可读可写,若文件不存在,则创建文
	**件.
	*/
	pf = fopen(DATAPATH, "ab+");
	if (!pf)
	{
		printf("文件打开错误");
		exit(EXIT_FAILURE);
	}
	

	/*
	**读入数据
	*/
	while (0 == feof(pf))	/*若文件未读到尾部*/
	{
		p = (NODE_S *)malloc(sizeof(NODE_S));
		if (!p)
		{
			printf("待复制数据结点生成失败!\n");
			exit(EXIT_FAILURE);
		}
		
		/*
		**一次从文件中读取一条学生记录
		*/
		if ( 1 == fread(p, sizeof(NODE_S), 1, pf) )
		{
			p->pnext = NULL;
			r->pnext = p;
			r = p;
			++count;	/*文件记录加一*/
		}

	}

	fclose(pf);/*关闭文件*/
	
//	Show_Data(pL);//测试
	printf("文件成功打开,当前记录共%d条\n", count);

	p = pL->pnext;
	while (p)
	{
		if (0 == strcmp(p->data.ID, account))
		{
			printf("找到数据...\n");
			DataToBuffer(buffer, (const char*)&(p->data), sizeof(STUDENT)/sizeof(char));
			break;
		}
		p = p->pnext;
	}
	if(1 == CompleteSend(hClientSocket, buffer, sizeof(STUDENT)))
	{
		printf("传输成功!\n");
	}
	//测试
	CompleteRecv(hClientSocket, buffer, 1);//仅仅接收反馈信息,无用.
	return;
}

void DestroyList(LINK **ppL)
{
	/*函数参数不能是LINKLIST * pL, 因为这样会导致pL不能修改,而在本函数中,头指针最后必须为NULL.*/
	NODE *q = NULL;

	while (*ppL)
	{
		q = (*ppL)->pnext;
		free(*ppL);
		*ppL = q;
	}/*退出while()循环时, *ppL一定为NULL.*/

	/*不需要再设定(*ppL)为空,因为此时*ppL已经为NULL,这是与ClearList()的区别.*/
	printf("删除链表!\n");
	return;
}

void DestroyList_s(LINK_S **ppL)
{
	/*函数参数不能是LINK_S *pL, 因为这样会导致pL不能修改,而在本函数中,头指针最后必须为NULL.*/
	NODE_S *q = NULL;

	while (*ppL)
	{
		q = (*ppL)->pnext;
		free(*ppL);
		*ppL = q;
	}/*退出while()循环时, *ppL一定为NULL.*/

	/*不需要再设定(*ppL)为空,因为此时*ppL已经为NULL,这是与ClearList()的区别.*/
	printf("删除链表!\n");
	return;
}
