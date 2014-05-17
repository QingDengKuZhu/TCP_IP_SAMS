#include "Data.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PASSWORD	"PASSWORD"

void Show(LINK * pL)
{
	NODE *p = pL->pnext;
	if (!p)
	{
		printf("无密码记录\n");
	}
	else
	{
		printf("帐号密码为:\n");
		while (p)
		{
			printf("%d,   |%s,    |%s\n", p->data.Type, p->data.account, p->data.password);
			p = p->pnext;
		}
	}

	return;
}

void Show_Data(LINK_S *pL)
{
	NODE_S *p = pL->pnext;
	if (!p)
	{
		printf("无成绩记录\n");
	}
	else
	{
		printf("成绩为:\n");
		while (p)
		{
			printf("ID:%s  name:%s\nchinese:%d, math:%d, english:%d, physics:%d, chemistry:%d, biology:%d, total:%d\n", p->data.ID, p->data.name, p->data.chinese, p->data.math, p->data.english, p->data.physics, p->data.chemistry, p->data.biology, p->data.total);
			p = p->pnext;
		}
	}

	return;
}
void AccountInput(char account[], const char notice[], const size_t len)
{
	char t[256];
	do 
	{
		printf(notice);
		scanf("%s", t);
		if (strlen(t) != len-1)
		{
			printf("\n帐号需要%d位!!!\n", len-1);
		}
	} while (strlen(t) != len-1);

	strcpy(account, t);//该操作执行完成后,account[len-1] = '\0'

	return;
}

void PasswordInput(char password[], const char notice[], const size_t len)
{
	char t[256];
	do 
	{
		printf(notice);
		scanf("%s", t);
		if (strlen(t) != len-1)
		{
			printf("\n密码需要%d位!!!\n", len-1);
		}
	} while (strlen(t) != len-1);

	strcpy(password, t);//该操作完成以后,password[len-1] = '\0'

	return;
}

void Save(LINK *pL)
{
	FILE* fp;
	NODE *p;
	int count=0;
	fp=fopen(PASSWORD,"wb");/*以只写方式打开二进制文件*/
	
	if(fp==NULL) /*打开文件失败*/
	{
		printf("\n=====>文件打开错误!\n");
		getchar();
		return ;
	}

	p=pL->pnext;

	while(p)
	{
		if(fwrite(p,sizeof(NODE),1,fp)==1)/*每次写一条记录或一个节点信息至文件*/
		{ 
			p=p->pnext;
			count++;
		}
		else
		{
			break;
		}
	}
	if(count>0)
	{
		getchar();
		printf("\n\n\n\n\n=====>save file complete,total saved's record number is:%d\n",count);
		getchar();
	}
	else
	{
		system("cls");
		printf("the current link is empty,no password is saved!\n");
		getchar();
	}
	fclose(fp); /*关闭此文件*/

	return;
}

void Add(LINK *pL)
{
	NODE *p = pL;
	NODE *q = pL->pnext;
	NODE *pNew = (NODE *)malloc(sizeof(NODE));
	if (!pNew)
	{
		printf("动态内存分配失败!\n");
		return;
	}
	
	AccountInput((pNew->data).account, "account:", ACCOUNT_LEN);
	PasswordInput((pNew->data).password, "password:", PASSWORD_LEN);
	(pNew->data).Type = TypeInput("type:");
	
	p->pnext = pNew;
	pNew->pnext = q;
	printf("成功!\n");
	return;
}

int TypeInput(const char notice[])
{
	unsigned  t; /*临时保存输入的数据*/
	unsigned n;	 /*保存scanf的返回值*/
	do
	{
		printf(notice);		/*显示提示*/
		n = scanf("%d", &t);	/*输入分数,当输入的不是int型时,n!=0*/
		fflush(stdin);
		/*
		**判断分数是否在合理范围内
		*/
		if ( t>2 || t<1  || n != 1)
		{
			printf("\n 类型需要在[1,2]范围内!!!\n");
		}
	}while ( t>2 || t<1 || n != 1);

	return t;
}

void Del(LINK *pL)
{
	NODE *p = pL->pnext;
	NODE *q = pL;
	int cur = 1;
	int pos;
	printf("请输入删除位置:");
	scanf("%d", &pos);

	if (pos < 1)	/*判断插入点是否合理.*/
	{
		printf("输入错误!\n");
		return;
	}

	while (p)
	{
		if (cur == pos)	/*找到删除结点,此时p指向删除结点,q指向删除结点的前一个结.*/
		{
			q->pnext = p->pnext;
			free(p);
			printf("删除成功!\n");
			return;
		}

		q = p;
		p = p->pnext;
		++cur;
	}

	printf("删除失败!\n");
	return;
}

