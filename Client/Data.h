/************************************************************************/
/* ϵͳ�������ݽṹ                                                      */
/************************************************************************/

#ifndef DATA_H
#define DATA_H


//ѧ�����ݽṹ

typedef struct stutent
{
	char ID[10];			//ѧ��λ��Ϊ9,���һλ���'\0'.
	char name[15];		//�������14λ.���һλ���'\0'.

	unsigned int chinese;	//���ĳɼ�
	unsigned int math;	//��ѧ�ɼ�
	unsigned int english;	//Ӣ��ɼ�
	unsigned int science;	//���۳ɼ�

	unsigned int total;	//�ܷ�
	double	ave;			//ƽ����

}STUDENT;


#endif