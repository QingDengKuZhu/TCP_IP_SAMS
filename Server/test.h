#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>

void Show(LINK *pL);

void Show_Data(LINK_S *pL);

void Add(LINK *pL);

void Save(LINK *pL);

void Del(LINK *pL);

void AccountInput(char account[], const char notice[], const size_t len);

void PasswordInput(char password[], const char notcie[], const size_t len);

int TypeInput(const char notice[]);


#endif 