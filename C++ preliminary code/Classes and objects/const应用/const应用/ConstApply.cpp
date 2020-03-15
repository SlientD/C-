#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

int main()
{
	const int a = 3;
	int* p = (int *)(&a);
	*p = 4;
	cout << "value of p: " << *p << endl;
	cout << "value of a: " << a << endl;
	cout << "address of p: " << p << endl;
	cout << "address of a: " << &a << endl;
	return 0;
}