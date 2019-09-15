#define _CRT_SECURE_NO_WARNINGS 1

#include "inlineFileTest.h"
//Q2:反汇编比较一下两者有什么不同
int Add1(int a, int b)      //会发现有push call这一步，即压栈过程
{
	return a + b;
}
inline int Add2(int a, int b)    //直接在主函数中进行替换然后赋值
{
	return a + b;
}


int main()
{
	//Q1：引入const：在c++中，const修饰的变量，有常量的特性，也有宏的特性，只不过替换是在编译的时候，且会参与检测
	//在c中是没有编译检测的这一过程，所以仍会修改
	//宏是在预处理是替换的不可参与编译
	const int a = 10;
	int *p = (int *)&a;
	*p = 100;
	cout<<a<<" "<<*p<<endl;     //会发现a在此处打印的是10，*p打印的是100。因为在编译检测中，判断a为不可修改的变量因而不可以修改
	

	//Q2：内联函数是什么：以inline修饰的函数叫做内联函数，编译时C++编译器会在调用内联函数的地方展开，没有函数压栈的开销，内联函数提升程序运行的效率。
	//他与const一样也是在编译时将函数替换，减少了在函数调用时形成栈帧这一步
	int ret = 0;
	ret = Add1(1, 2);
	ret = Add2(3, 4);
	//inline只是适用于简短的代码，如果代码很长或者调用函数在和循环体内，编译器会自动优化，忽略掉内联

	//Q3： inline不建议声明和定义分离，分离会导致链接错误。因为inline被展开，就没有函数地址了，链接就会找不到。
	//因而内联函数具有文件作用域，只能在本文件使用，其他文件不能用
	F(10);      //会报错找不到。。 链接错误：main.obj : error LNK2019: 无法解析的外部符号 "void __cdecl F(int)" (?F@@YAXH@Z)，该符号在函数 _main 中被引用
		

	return 0;
	system("pause");
}