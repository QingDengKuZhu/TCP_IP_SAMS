/************************************************************************/
/* 与界面有关的函数声明                                                  */
/************************************************************************/
#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>



/*
**光标定位
*/
void gotoxy(short x, short y);

/*
**欢迎界面:显示欢迎信息,版本信息,提示输入帐号密码.
*/
void WelcomeUI(SOCKET sd);

/*
**教师界面:当以教师身份登录系统后出现的界面.
*/
void TeacherUI(SOCKET sd);

/*
**学生界面:当以学生身份登录系统后出现的界面.
*/
void StudentUI(SOCKET sd);

#endif
