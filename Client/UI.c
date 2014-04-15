#include "UI.h"
#include "Data.h"
#include "Input.h"
#include "Output.h"
#include <windows.h>	//COORD
#include "Transmission.h"

#define		ACCOUNT_LEN	9	//帐号长度
#define		PASSWORD_LEN	9	//密码长度



void gotoxy(short x, short y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//设置光标位置
	
	return;
}


void WelcomeUI(SOCKET sd)
{
	char account[ACCOUNT_LEN + 1];	//存储帐号
	char password[PASSWORD_LEN +1];	//密码长度
	char buffer[ACCOUNT_LEN + PASSWORD_LEN + 1];//传输数据缓冲区

	system("cls");//清屏
	gotoxy(25, 5);
	printf( "欢迎来到学生成绩管理系统(V 1.0)\n" );
	gotoxy(10, 6);
	printf("-----------------------------------------------------\n");
	AccountInput(account, "请输入帐号: ", sizeof(account)/sizeof(char)-1);	//输入帐号
	PasswordInput(password, "请输入密码: " ,sizeof(password)/sizeof(char)-1);	//输入密码
	strcpy(buffer, account);
	strcat(buffer, password);//刚好填满(包括'\0')

	//将帐号和密码发送到服务器进行验证
	if (0 == CompleteSend(sd, buffer, sizeof(buffer)/sizeof(char)))
	{
		printf("传输数据失败!\n");
		return;
	}
	
	//接收帐号密码查询结果:返回两个char值buffer[0]表示密码帐号是否正确('Y':正确, 'N':错误),buffer[1]表示帐号类型('S':学生, 'T':老师)
	if (0 == CompleteRecv(sd, buffer, 2))
	{
		printf("传输数据失败!\n");
		return;
	}
	
	//判断密码帐号是否正确
	if ('Y' != buffer[0])
	{
		printf("密码帐号错误!\n");
		return;
	}

	//判断帐号类型
	if ('S' == buffer[1])
	{
		StudentUI(sd);
	}
	else if ('T' == buffer[1])
	{
	//	TeacherUI(sd);
	}

	return;
}

void StudentUI(SOCKET sd)
{
	char sendmessage[2] = {'S', '\0'};
	char buffer[sizeof(STUDENT)];//接受学生成绩信息
	STUDENT student;

	system("cls");
	printf("学生成绩管理系统--学生\n");
	CompleteSend(sd, sendmessage, 2);
	CompleteRecv(sd, buffer, sizeof(STUDENT)/sizeof(char));
	BuffertoData((char *)&student, buffer, sizeof(student)/sizeof(char));//转换
	PrintHead();
	PrintData(&student);

	return;
}