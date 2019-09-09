#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

int TestAuto()
{
	return 3;
}
////Q5:auto不能作为函数的参数
//void TestAuto1(auto a)     //auto不可在此处用，不可做形参，因为编译器无法对a的实际类型进行推导。若可以是auto那么就没重载什么事情了，传什么值auto变什么类型？
//{
//
//}
int main()
{
	//Q1:c++11规定：auto可作为一个新的类型指示符来指示编译器，auto声明的变量必须由编译器在编译时期推导而得。
	auto a = 1.3;
	int b = 2;
	auto c = b;
	auto d = 'd';
	auto e = TestAuto();
	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;
	cout << typeid(d).name() << endl;
	cout << typeid(e).name() << endl;     //typeid(变量).name()是求变量的类型的
	

	//Q2:使用auto定义变量时必须对其进行初始化，在编译阶段编译器需要根据初始化表达式来推导auto的实际类型。
	//auto e;      //会通不过编译，因为auto不知道e是什么类型，因而无法定义


	//Q3:auto与指针引用结合：用auto声明指针类型时，用auto和auto*没有任何区别，但用auto声明引用类型时则必须加&，不加&就是普通类型变量
	int x = 1;
	auto px = &x;
	auto *ppx = &x;
	auto& rx = x;
	auto rrx = x;
	

	cout << typeid(px).name() << endl;
	cout << typeid(ppx).name() << endl;
	cout << typeid(rx).name() << endl;
	cout << typeid(rrx).name() << endl;
	rx = 3;
	cout << x << endl;        //x发生了变化说明是引用
	rrx = 2;
	cout << x << endl;        //x未发生变化，说明不是引用

	//Q4:auto在同一行定义多个变量
	//当在同一行声明多个变量时，这些变量必须是相同的类型，否则编译器将会报错，因为编译器实际只对第一个类型进行推导，然后用推导出来的类型定义其他变量。
	auto f = 1, g = 2;
	//auto h = 1, i = 2.3; //编译会报错，h和i类型不同

	//Q6:auto不能直接用来声明数组
	int h[] = { 1, 2, 3 };
	//auto t[] = { 4，5，6 };//编译时会发生错误

	
	
	system("pause");
	return 0;
}