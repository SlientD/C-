#define _CRT_SECURE_NO_WARNINGS 1
#include "classApply.h"

//Q2.2
void Person2::SetPersonInfo(const char * name, const char * gender, int age)        //结构体里的函数，定义出来一个结构体对象后，这个函数成员就可以被对象调用了
{
	strcpy(_name, name);
	strcpy(_gender, gender);
	_age = age;
}
void Person2::PrintPersonInfo()
{
	cout << _name << " " << _gender << " " << _age << endl;
}