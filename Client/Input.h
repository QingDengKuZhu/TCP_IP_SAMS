#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>

//�������������ķ���(0<=����<=maxnumber)
unsigned int NumberInput(const char notice[], const unsigned int maxnumber);

//����������(����Ϊlen)���ʺ����뵽account��.
void AccountInput(char account[], const char notice[], const size_t len);

//����������(����Ϊlen)�����뱣����password��
void PasswordInput(char password[], const char notcie[], const size_t len);

//����������������(����Ϊlen)�洢��ID��.
void IDInput(char ID[], const char notice[], const size_t len);

#endif