#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

//在定义指针变量时，要给指针一个指向，否则指针可能会没有合法的指向，变成一个野指针。在c语言中，我们用NULL给没有指向的指针赋初值
//NULL实际上是一个宏，NULL被定义为字面常量0，或者被定义为无类型指针(void*)的常量。因而会遇见一些不符人意的情况
//如：
void f(int)
{
	cout << "f(int)" << endl;
}
void f(int*)
{
	cout << "f(int*)" << endl;
}
int main()
{
	f(0);                    //调用的是第一个函数
	f(NULL);                 //调用的依旧是第一个函数，然而我们将NULL赋给指针，在传NULL指针的时候，其实我们是想让他进入第二个函数的
	f((int*)NULL);
	//因而c++引入了nullptr，专门代表一个指针空值常量。
	int *ptr = nullptr;
	f(ptr);                //会发现他是进入了第二个函数
	//nullptr是有类型的，其类型为nullptr_t，仅仅可以被隐式转化为指针类型，nullptr_t被定义在头文件中：typedef decltype(nullptr) nullptr_t;
	    //用nullptr表示指针空值不用包含头文件，因为nullptr是C++11作为新关键字引入的。
		// 在C++11中，sizeof(nullptr) 与 sizeof((void*)0)所占的字节数相同。指针占的字节数都为4
		//为了提高代码的健壮性，在后续表示指针空值时建议最好使用nullptr。
	return 0;
}

