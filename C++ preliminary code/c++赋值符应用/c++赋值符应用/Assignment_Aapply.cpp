#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>    //�⺯������c��ͬ����û�к�׺��
using namespace std;   //�ÿ⺯���е������ռ�std

int main(){
	int x,y,z;
	cin >> x;        //�൱��scanf
	cout << x<<endl;       //�൱��printf ,endl�൱�ڻ���

	//cin��cout������������һ������������һ�������÷���scanf��printf��Ҫ���
	cin >> x >> y>>z;
	cout << "The number is " << x << " " << y << " " << z<<endl;

	system("pause");
	return 0;

}

