#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;


void Fun1(int x, int y, int z){
	cout << x <<" "<< y <<" "<< z<<endl;
}

//缺省参数：缺省参数是声明或定义函数时为函数的参数指定一个默认值，在调用该函数时，如果没有指定实参则采用该默认值，否则使用指定的实参.
//缺省参数必须为常量或全局变量！！
//缺省参数分为全缺省函数和半缺省函数：
//全缺省参数：在没有传实参时，用默认的参数。
void Fun2(int x=1, int y=2, int z=3){
	cout << x << " " << y << " " << z << endl;
}

//半缺省参数：1. 半缺省参数必须从右往左依次来给出，不能间隔着给，就是前面的可以省略，但一旦给值，后面的都必须都给值

void Fun3(int x , int y = 2, int z = 3){         //至少传一个形参过来给x
	cout << x << " " << y << " " << z << endl;
}

// 为了防止如果声明与定义位置提供的值不同，那编译器就无法确定到底该用那个缺省值，因而缺省参数不能在函数声明和定义中同时出现。
//最好在声明时赋予缺省值，因为在不知道源代码的情况下，仍可以看到缺省参数
void Fun4(int x, int y = 2, int z = 3);
void Fun4(int x, int y , int z ){         
	cout << x << " " << y << " " << z << endl;
}


int main()
{
	Fun1(1, 2, 3);
	Fun2();
	Fun2(10);        //先赋值给a，因为半缺省参数前面的可以省略，所以在不知道函数是不是半缺省参数的情况下，实参要赋从第一个形参开始赋值
	Fun2(10, 20);
	Fun2(10, 20, 30);
	Fun3(10);

	
	system("pause");
	return 0;
}