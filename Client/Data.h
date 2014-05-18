/************************************************************************/
/* 系统所需数据结构                                                      */
/************************************************************************/

#ifndef DATA_H
#define DATA_H


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

typedef struct tjMessage 
{
	unsigned int chinese;	//语文不及格人数
	unsigned int math;	//数学不及格人数
	unsigned int english;	//英语不及格人数
	unsigned int physics;	//物理不及格人数
	unsigned int chemistry;//化学不及格人数
	unsigned int biology;	//生物不及格人数

	unsigned int total;	//总分最高分

	char chinese_ID[10];
	char chinese_name[15];		

	//相关成绩最高的学生ID和姓名
	char math_ID[10];
	char math_name[15];		

	char english_ID[10];
	char english_name[15];		

	char physics_ID[10];
	char physics_name[15];

	char chemistry_ID[10];
	char chemistry_name[15];		
	char biology_ID[10];
	char biology_name[15];		
	char total_ID[10];
	char total_name[15];		
}TJMESSAGE;

#endif