#ifndef OUTPUT_H
#define OUTPUT_H

#include "Data.h"

/*
**格式化输出表头,当表格形式输出用户信息时输出表头信息.
*/
void PrintHead(void);

/*
**格式化输出接收缓冲区中的一条信息(一个学生信息)
*/
void PrintData(STUDENT *pdata);

#endif
