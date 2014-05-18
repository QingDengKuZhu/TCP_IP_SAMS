#include "UI.h"
#include "Data.h"
#include "Input.h"
#include "Output.h"
#include <windows.h>	//COORD
#include "Transmission.h"

#define		ACCOUNT_LEN	10	//帐号长度
#define		PASSWORD_LEN	10	//密码长度



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
	char account[ACCOUNT_LEN];	//存储帐号
	char password[PASSWORD_LEN];	//密码长度
	char buffer;//接收从服务器返回的帐号密码查询结果.

	system("cls");//清屏
	gotoxy(25, 5);
	printf( "欢迎来到学生成绩管理系统(V 1.0)\n" );
	gotoxy(10, 6);
	printf("-----------------------------------------------------\n");
	AccountInput(account, "请输入帐号: ", ACCOUNT_LEN);	//输入帐号
	PasswordInput(password, "请输入密码: " ,PASSWORD_LEN);	//输入密码

	//将帐号和密码发送到服务器进行验证
	if (0 == CompleteSend(sd, account, ACCOUNT_LEN) || 0 == CompleteSend(sd, password, PASSWORD_LEN))
	{
		printf("传输数据失败!\n");
		return;
	}
	
	//接收帐号密码查询结果:返回1个char值,a表示学生帐号;b表示教师帐号;c表示密码错误但是帐号存在,d表示帐号不存在.
	if (0 == CompleteRecv(sd, &buffer, 1))
	{
		printf("传输数据失败!\n");
		return;
	}
	
	//根据服务器返回的结果，判断帐号密码

	switch (buffer)
	{
	case 'a'://学生帐号
		StudentUI(sd);//进入学生界面
		getchar();
		break;
	case 'b'://教师帐号
		TeacherUI(sd);//printf("进入教师界面");
		getchar();
		break;
	case 'c'://密码错误
		system("cls");
		printf("密码错误！按回车返回欢迎界面\n");
		getchar();
		getchar();
		break;
	case 'd'://帐号不存在
		system("cls");
		printf("帐号密码不存在！按回车返回欢迎界面\n");
		getchar();
		getchar();
		break;
	}
	
	return;
}

void StudentUI(SOCKET sd)
{
	char buffer[sizeof(STUDENT)];//接受学生成绩信息
	STUDENT student;

	system("cls");
	gotoxy(10, 5);			/*在文本窗口中设置光标*/
	printf("		学生成绩管理系统--学生\n");

	if(1==CompleteRecv(sd, buffer, sizeof(STUDENT)))
	{
//		printf("接收成功!\n");
	}
	BuffertoData((char *)&student, buffer, sizeof(STUDENT)/sizeof(char));//转换
	PrintHead();
	PrintData(&student);
	
	getchar();
	return;
}

void TeacherUI(SOCKET sd)
{
	int select;
	char send;
	char rec;

	while (1)
	{
		Menu();
		printf("请输入您的选择:");
		scanf("%d", &select);

		switch (select)
		{
		case 1:
			send = 'b';
			CompleteSend(sd, &send, 1);
			Add(sd);
			CompleteRecv(sd, &rec, 1);
			if (rec =='Y')
			{
				printf("添加成功\n");
			}
			else
			{
				printf("添加失败!\n");
			}
			getchar();
			break;
		case 2:
			send = 'c';
			CompleteSend(sd, &send, 1);
			Del(sd);
			CompleteRecv(sd, &rec, 1);
			if (rec =='Y')
			{
				printf("删除成功\n");
			}
			else
			{
				printf("删除失败!\n");
			}
			getchar();
			getchar();
			break;
		case 3:	//显示
			send = 'a';
			CompleteSend(sd, &send, 1);
			ClientFromServer(sd);
			getchar();
			break;
		case 4:
			send = 'd';
			CompleteSend(sd, &send ,1);
			Modify(sd);
			CompleteRecv(sd, &rec, 1);
			if (rec =='Y')
			{
				printf("修改成功\n");
			}
			else
			{
				printf("修改失败!\n");
			}
			getchar();
			break;
		case 5:
			send = 'f';
			CompleteSend(sd, &send ,1);
			CompleteRecv(sd, &rec, 1);
			if (rec =='Y')
			{
				printf("排序成功\n");
			}
			else
			{
				printf("排序失败!\n");
			}
			getchar();
			getchar();
			break;
		case 6:
			send = 'g';
			CompleteSend(sd, &send ,1);
			RecTongji(sd);
			getchar();
		default:
			break;;
		}
	}
	return;
}

void Menu(void)
{
	system("cls");
	gotoxy(10, 5);			/*在文本窗口中设置光标*/
	printf("		学生成绩管理系统--教师\n");
	gotoxy(10, 8);
	printf("-------------------------------Menu-------------------------------\n");
	gotoxy(10, 9);
	printf("|	1 添加数据			2 删除数据	   |\n");
	gotoxy(10, 10);
	printf("|	3 显示数据			4 修改数据	   |\n");
	gotoxy(10, 11);
	printf("|	5 按总成绩降序排列		6 统计数据	   |\n");
	gotoxy(10, 14);
	printf("-------------------------------------------------------------------\n");

	return;
}