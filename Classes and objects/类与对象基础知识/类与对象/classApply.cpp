#define _CRT_SECURE_NO_WARNINGS 1
#include "classApply.h"

//Q2.2
void Person2::SetPersonInfo(const char * name, const char * gender, int age)        //�ṹ����ĺ������������һ���ṹ���������������Ա�Ϳ��Ա����������
{
	strcpy(_name, name);
	strcpy(_gender, gender);
	_age = age;
}
void Person2::PrintPersonInfo()
{
	cout << _name << " " << _gender << " " << _age << endl;
}