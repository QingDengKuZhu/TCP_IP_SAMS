#ifndef FUNCTION_H
#define FUNCTION_H

#include "Data.h"

//判断接收到的帐号密码请求是否正确,若正确返回相应的帐号类型(1或2),若不正确,返回4(密码错误),5(帐号不存在)
int IsAccount(const long int account, const long int password);

#endif