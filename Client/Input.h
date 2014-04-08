#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

//返回满足条件的分数(0<=分数<=maxnumber)
unsigned int NumberInput(const char notice[], const unsigned int maxnumber);

//将满足条件(长度为len)的帐号输入到account中.
void AccountInput(char account[], const char notice[], const size_t len);

//将满足条件(长度为len)的密码保存在password中
void PasswordInput(char password[], const char notcie[], const size_t len);

//将满足条件的输入(长度为len)存储在ID中.
void IDInput(char ID[], const char notice[], const size_t len);

#endif