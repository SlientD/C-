#ifndef _CLASSAPPLY_H_
#define _CLASSAPPLY_H_
#include <iostream>
using namespace std;

//Q2.2
class Person2{
public:
	void Person2::SetPersonInfo(const char * name, const char * gender, int age);
	void Person2::PrintPersonInfo();
private:
	char _name[20];
	char _gender[4];
	int _age;
};



#endif 
