#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>  
using namespace std;
const int a = 3;       //��ʱa��ȫ�ֱ���
int main()
{
	//int a = 2;
	int* p = (int *)(&a);
	*p = 4;        //�ᷢ������ʱ����
	cout << "value of p: " << *p << endl;
	cout << "value of a: " << a << endl;
	cout << "address of p: " << p << endl;
	cout << "address of a: " << &a << endl;

	return 0;
}