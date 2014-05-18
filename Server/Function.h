#ifndef FUNCTION_H
#define FUNCTION_H

#include "Data.h"
#include <WinSock2.h>

//判断接收到的帐号密码请求是否正确,若正确返回相应的帐号类型(1或2),若不正确,返回3(密码错误),4(帐号不存在)
int IsAccount(const char account[], const char password[]);

//当以学生身份登录服务器时,调用此函数.
void Student(SOCKET hClientSocket, const char account[]);

//当以教师身份登录服务器时,调用此函数.
void	Teacher(SOCKET hClientSocket);

//删除单链表
void DestroyList(LINK **ppL);

void DestroyList_s(LINK_S **ppL);

//将单链表的内容发送到客户端
void ServerToClient(SOCKET hClientSocket, LINK_S *pL);

//添加成绩记录.成功返回1,否则为0;
int AddData(SOCKET hclientSocket, LINK_S *pL);

//删除成绩记录,成功和返回1,否者返回0;
int DelData(SOCKET hclientSocket, LINK_S *pL);

//修改成绩记录
int ModifyData(SOCKET hclientSocket, LINK_S *pL);

//将成绩按照总分降序排列
int SortData(SOCKET hclientSocket, LINK_S *pL);

void Tongji(SOCKET hclientSocket, LINK_S *pL);

//保存数据
void SaveData(LINK_S *pL);
#endif