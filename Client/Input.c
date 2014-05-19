#include "Input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int NumberInput(const char notice[], const unsigned int maxnumber)
{
	unsigned int t;//临时保存输入的数据
	unsigned int n;//保存scanf的返回值

	do 
	{
		printf(notice);//显示提示信息
		n = scanf("%d", &t);
		fflush(stdin);

		//判断分数是否在合理的范围内
		if (t>maxnumber || t<0 || n!=1)
		{
			printf("\n分数需要在[0,100]范围内!!!\n");
		}

	} while (t>maxnumber || t<0 || n!=1);

	return t;
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

void IDInput(char ID[], const char notice[], const size_t len)
{
	char t[256];
	do 
	{
		printf(notice);
		scanf("%s", t);
		if (strlen(t) != len-1  || IsDigit(t, len-1)==0 )
		{
			printf("\n密码需要%d位,且必须全部以数字组成!!!\n", len-1);
		}
	} while (strlen(t) != len-1|| IsDigit(t, len-1)==0);

	strcpy(ID, t);//该操作完成以后,ID[len-1] = '\0'

	return;
}

int IsDigit(const char *str, const size_t len)
{
	unsigned int i;
	for (i=0; i < len; i++)
	{ 
		if (str[i] > '9' || str[i] < '0')
		{
			return 0;
		}
	}
	return 1;
}

void NameInput(char name[], const char notice[], const size_t maxlen)
{
	char t[256];
	do 
	{
		printf(notice);
		scanf("%s", t);
		if (strlen(t) > maxlen-1)
		{
			printf("\n姓名最多%d位!!!\n", maxlen-1);
		}
	} while (strlen(t) > maxlen-1);

	strcpy(name, t);//该操作执行完成后,account[len-1] = '\0'
}
