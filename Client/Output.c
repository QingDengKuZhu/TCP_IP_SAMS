#include <stdio.h>
#include <stdlib.h>
#include "Output.h"
#include "Data.h"


void PrintHead(void)
{
	printf("      ----------------------------学生成绩----------------------------------  \n");
	printf("     |  学号   |      姓名     |语文|数学|英语|物理|化学|生物|总分| \n");

	return;
}

void PrintData(STUDENT *pdata)
{	
	printf("      ");
	printf("%-10s ", pdata->ID);
	printf("%-15s ", pdata->name);
	printf("%-4d ", pdata->chinese);
	printf("%-4d ", pdata->math);
	printf("%-4d ", pdata->english);
	printf("%-4d ", pdata->physics);
	printf("%-4d", pdata->chemistry);
	printf(" %-4d", pdata->biology);
	printf(" %-4d", pdata->total);
	printf("\n");
	
	return;
}


