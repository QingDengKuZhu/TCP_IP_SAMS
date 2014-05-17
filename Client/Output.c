#include <stdio.h>
#include <stdlib.h>
#include "Output.h"
#include "Data.h"


void PrintHead(void)
{
	printf("      ----------------------------学生成绩----------------------------------  \n");
	printf("     |    学号     |      姓名     | 语文|数学|  英语 |   物理  |  化学  |生物 |平均分| \n");

	return;
}

void PrintData(STUDENT *pdata)
{ 
	printf("ID : %s ", pdata->ID);
	printf("name:%s ", pdata->name);
	printf("chinese : %d ", pdata->chinese);
	printf("math : %d ", pdata->math);
	printf("english : %d ", pdata->english);
	printf("physics : %d ", pdata->physics);
	printf("chemistry : %d", pdata->chemistry);
	printf("biology : %d", pdata->biology);
	printf("total : %d", pdata->total);
	printf("\n");
	
	return;
}


