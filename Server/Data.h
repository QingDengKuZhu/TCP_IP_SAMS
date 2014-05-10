/************************************************************************/
/* 系统所需数据结构                                                      */
/************************************************************************/

#ifndef DATA_H
#define DATA_H

#define  PASSWORDPATH	"PASSWORD"
#define	DATAPATH		"DATAPATH"
#define		ACCOUNT_LEN	9	//帐号长度
#define		PASSWORD_LEN	9	//密码长度


//学生数据结构
typedef struct Stutent
{
	char ID[10];			//学号位数为9,最后一位存放'\0'.
	char name[15];		//姓名最多14位.最后一位存放'\0'.

	unsigned int chinese;	//语文成绩
	unsigned int math;	//数学成绩
	unsigned int english;	//英语成绩
	unsigned int physics;	//物理成绩
	unsigned int chemistry;//化学成绩
	unsigned int biology;	//生物成绩

	unsigned int total;	//总分

} STUDENT;

//帐号密码
typedef struct Account
{
	int Type;	/*帐号类型, 1表示学生帐号,2表示教师帐号*/
	char account[ACCOUNT_LEN + 1];	/*学生帐号就是学号,+1是因为末尾'\0'*/
	char password[PASSWORD_LEN + 1];
}ACCOUNT;

/*
**链表结构
*/
typedef struct Node
{
	STUDENT data;
	struct Node *pnext;

}NODE, LINK;

#endif