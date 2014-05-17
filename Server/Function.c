﻿#include "Data.h"
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
	STUDENT *p = NULL;
	FILE *pf = NULL;		/*文件指针*/
	char buffer[sizeof(STUDENT)];

	p = (STUDENT *)malloc(sizeof(STUDENT));
	if (!p)
	{
		printf("头结点分配失败!\n");
		exit(EXIT_FAILURE);
	}
	/*
	** 以追加的方式打开一个二进制文件,可读可写,若文件不存在,则创建文件
	*/
	pf = fopen(DATAPATH, "ab+");//最后必须修改为只读模式
	if (!pf)
	{
		printf("文件打开错误!\n");
		exit(EXIT_FAILURE);
	}
	
	/*
	** 读入数据
	*/
	while (0 == feof(pf))	/*若文件未读到尾部*/
	{
		
		/*
		** 一次从文件中读取一条学生记录
		*/
		if ( 1 == fread(p, sizeof(NODE), 1, pf))
		{
			if (0 == strcmp(account, p->ID))/*帐号存在*/
			{
				DataToBuffer(buffer, (const char *)p, sizeof(STUDENT));
				CompleteSend(hClientSocket, buffer, sizeof(STUDENT));
				
				fclose(pf);
				return;
			}
		}
	}

	strcpy(p->ID, account);
	p->biology = 0;
	p->chemistry = 0;
	p->chinese = 0;
	p->physics = 0;
	strcpy(p->name, '\0');
	p->total = 0;
	p->english = 0;
	p->math = 0;

	DataToBuffer(buffer, (const char *)p, sizeof(STUDENT));
	CompleteSend(hClientSocket, buffer, sizeof(STUDENT));
	
	fclose(pf);
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
