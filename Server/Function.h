#ifndef FUNCTION_H
#define FUNCTION_H

#include "Data.h"

//判断接收到的帐号密码请求是否正确,若正确返回相应的帐号类型(1或2),若不正确,返回3(密码错误),4(帐号不存在)
int IsAccount(const char account[], const char password[]);

//当以学生身份登录服务器时,调用此函数.
void Student(SOCKET hClientSocket);

//当以教师身份登录服务器时,调用此函数.
void	Teacher(SOCKET hClientSocket);
#endif