/************************************************************************/
/* ������йصĺ�������                                                  */
/************************************************************************/
#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>

/*
**��궨λ
*/
void gotoxy(short x, short y);

/*
**��ӭ����:��ʾ��ӭ��Ϣ,�汾��Ϣ,��ʾ�����ʺ�����.
*/
void WelcomeUI(SOCKET sd);

/*
**��ʦ����:���Խ�ʦ��ݵ�¼ϵͳ����ֵĽ���.
*/
void TeacherUI(SOCKET sd);

/*
**ѧ������:����ѧ����ݵ�¼ϵͳ����ֵĽ���.
*/
void StudentUI(SOCKET sd);

#endif
