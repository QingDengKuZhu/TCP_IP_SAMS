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


#endif