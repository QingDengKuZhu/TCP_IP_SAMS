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
	printf("%s", pdata->ID);
	printf("%s", pdata->name);
	printf("%d", pdata->chinese);
	printf("%d", pdata->math);
	printf("%d", pdata->english);
	printf("%d", pdata->physics);
	printf("%d", pdata->chemistry);
	printf("%d", pdata->biology);
	printf("\n");
	
	return;
}


