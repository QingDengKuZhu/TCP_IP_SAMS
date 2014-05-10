#include "Data.h"
#include "Function.h"
#include <stdio.h>
#include <stdlib.h>

int IsAccount(const long int account, const long int password)
{
	ACCOUNT *p = NULL;
	FILE *pf = NULL;		/*文件指针*/
	
	p = (ACCOUNT *)malloc(sizeof(ACCOUNT));
	if (!p)
	{
		printf("头结点分配失败!\n");
		exit(EXIT_FAILURE);
	}
	/*
	** 以追加的方式打开一个二进制文件,可读可写,若文件不存在,则创建文件
	*/
	pf = fopen(PASSWORDPATH, "ab+");//最后必须修改为只读模式
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
			if (account == p->account )/*帐号存在*/
			{
				if (password == p->password)/*密码正确,返回帐号类型*/
				{
					return p->Type;
				}
				else	/*密码错误*/
				{
					return 4;
				}
			}
			else	/*帐号不存在*/
			{
				return 5;
			}
		}
	}

	fclose(pf);	/*关闭文件*/
	return 5;
}