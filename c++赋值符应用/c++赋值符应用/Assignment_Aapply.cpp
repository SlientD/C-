#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>    //库函数，与c不同的是没有后缀了
using namespace std;   //用库函数中的命名空间std

int main(){
	int x,y,z;
	cin >> x;        //相当于scanf
	cout << x<<endl;       //相当于printf ,endl相当于换行

	//cin和cout还可以连输入一长串，或输入一长串，用法比scanf和printf都要灵活
	cin >> x >> y>>z;
	cout << "The number is " << x << " " << y << " " << z<<endl;

	system("pause");
	return 0;

}

